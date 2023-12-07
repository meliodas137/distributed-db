#include "distributedDB/transaction_manager/TransactionManager.hpp"
#include "distributedDB/utils/utils.hpp"

#include <iostream>

using namespace std;

namespace distributedDB {

TransactionManager::TransactionManager(int dmCount, int varCount, vector<vector<pair<int, bool>>> &dmToVarlist): dmCount(dmCount), dmToVarList(dmToVarlist){
    varToDmList = vector<vector<int>>(varCount+1, vector<int>());
    incrementClock();
    for(int i = 0; i <= dmCount; i++) {
        //cout<<"creating manager "<<i<<endl;
        managers.emplace_back(DataManager(dmToVarList[i]));

        for(auto &var: dmToVarList[i]) {
            // cout<<var<<endl;
            varToDmList[var.first].emplace_back(i);
        }
    }
}

int TransactionManager::incrementClock() {
    return ++globalClock;
};

int TransactionManager::decrementClock() {
    return --globalClock;
};

void TransactionManager::beginTransaction(int transactionId) {
    runningTransactions[transactionId] = new Transaction(transactionId, incrementClock());
};

string TransactionManager::endTransaction(int transactionId){ 
    incrementClock();
    auto &transaction = runningTransactions[transactionId];
    runningTransactions.erase(transactionId);
    transaction->setCommitTime(globalClock);
    
    //abort conditions: first committer wins, rwrw edges, if t writes to any site s and s fails before t commits

    if(safeTransaction(commitedTransactions, *transaction, managers)) {

        addInCommittedMap(commitedTransactions, *transaction);

        if(hasRWRWCycle(commitedTransactions, transactionId)){
            removeFromCommittedMap(commitedTransactions, *transaction);
            return "T" + to_string(transactionId) + " aborts";
        }
    }
    else{
        return "T" + to_string(transactionId) + " aborts";
    }
    commitTransaction(*transaction);
    return "T" + to_string(transactionId) + " commits";
};

void TransactionManager::commitTransaction(Transaction &transaction){ 
    //do the actual commit  
    for(auto op: transaction.getAllWriteOperations()){
        auto dataId = op.getDataId();
        auto dataVal = op.getValue();
        for(auto &dm: op.getWriteManagerIds()){
            if(!managers[dm].isDown()){
                managers[dm].setDataSnapshot(dataId, dataVal, globalClock);
            }
        }
    }
    
}

string TransactionManager::readData(int transactionId, int dataId){ 
    incrementClock();
    //check if given transaction is currently running
    if (runningTransactions.find(transactionId) == runningTransactions.end()){
        return "Given transaction is currently not running.";
    }
    
    string returnMsg = "Transaction T" + to_string(transactionId) + " read variable x" + to_string(dataId) + " as ";
    auto &trans = runningTransactions[transactionId];

    int result, dmId = -1;
    int found = 0; // 0 means waiting 1 means item found and -1 means all sites down
    vector<int> canReadFrom = {}; //empty means that data can't be read from any site, hence transaction should abort

    //read from a local copy if possible
    if (trans->hasLocalCopy(dataId, result)){
        found = 1;
    }
    else {
        for(auto &dm: varToDmList[dataId]) {
            if(managers[dm].canReadDataItem(dataId, trans->getBeginTime(), result)){
                canReadFrom.emplace_back(dm);
                if(!managers[dm].isDown()){
                    found = 1;
                    dmId = dm;
                    break;
                }
                
            }
        }
    }
    
    if(found) {
        returnMsg = returnMsg + to_string(result);
        trans->addReadOperation(dataId, dmId, result, globalClock);

    } else if (!canReadFrom.empty()){
        // Wait for at least one site to be up
        runningTransactions.erase(transactionId);

        trans->setPendingOperation({OpType::READ, dataId});
        pendingTransactions[dataId].emplace_back(trans);

        returnMsg = "Waiting for any relevant site to be up";
    }
    else{
        //abort transaction
        runningTransactions.erase(transactionId);
        returnMsg = "T" + to_string(transactionId) + " aborts.";
    }

    return returnMsg;
};

string TransactionManager::writeData(int transactionId, int dataId, int dataValue){
    incrementClock();
     //check if given transaction is currently running
    if (runningTransactions.find(transactionId) == runningTransactions.end()){
        return "Given transaction is currently not running.";
    }

    auto &trans = runningTransactions[transactionId];
    string returnMsg = "Transaction T" + to_string(transactionId) + " wrote variable x" + to_string(dataId) + " to sites: ";

    // track which sites does t writes to, add to pending if no sites are up
    vector<int> writesTo = {};
    for(auto &dm: varToDmList[dataId]) {
        if(!managers[dm].isDown()){
            writesTo.emplace_back(dm);
        }
    }

    if(writesTo.empty()){
        //add to pending operations
        runningTransactions.erase(transactionId);

        trans->setPendingOperation({OpType::WRITE, dataId, dataValue});
        pendingTransactions[dataId].emplace_back(trans);

        returnMsg = "Waiting for any relevant site to be up.";
    }
    else{
        runningTransactions[transactionId]->addWriteOperation(dataId, writesTo, dataValue, globalClock);
        for(int dm: writesTo){
            returnMsg = returnMsg + to_string(dm) + " ";
        }
    }

    return returnMsg;
};

string TransactionManager::recoverDataManager(int dataManagerId){ 
    incrementClock();

    if(!managers[dataManagerId].isDown()){
        return "Site " + to_string(dataManagerId) + " is already up.";
    }
    managers[dataManagerId].upStatus(globalClock);

    //run any pending transactions that depend on data items of the current site
    for(auto &var: dmToVarList[dataManagerId]){
        auto &dataId = var.first;
        while (!pendingTransactions[dataId].empty()){
            auto &trans = pendingTransactions[dataId].back();
            pendingTransactions[dataId].pop_back(); //remove from pending
            runningTransactions[trans->t_id] = trans; //add to running

            decrementClock();  // to avoid multiple increments
            
            //run the pending operation
            auto op = trans->getPendingOperation();
            if(op[0] == OpType::READ){
                cout << readData(trans->t_id, op[1]) << endl;
            }
            else{
                cout << writeData(trans->t_id, op[1], op[2]) << endl;
            }
        }

    }
    return "Site " + to_string(dataManagerId) + " has recovered and all possible pending operations have completed.";
};

string TransactionManager::failDataManager(int dataManagerId){ 
    incrementClock();
    if(managers[dataManagerId].isDown()){
        return "Site " + to_string(dataManagerId) + " is already down.";
    }
    managers[dataManagerId].downStatus(globalClock);
    return "Site " + to_string(dataManagerId) + " has went down.";
};

string TransactionManager::dumpData(){ 
    incrementClock();

    for(int dm = 1; dm <= dmCount; dm++){
        cout << "site " << dm << " -"; 
        for(auto &var: dmToVarList[dm]){
            cout << " x" << var.first << ": " << managers[dm].getDataSnapshot(var.first, globalClock).second << ",";
        };
        cout << endl;
    };

    return "";

};

}




