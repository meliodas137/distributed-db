#include "distributedDB/transaction_manager/TransactionManager.hpp"
#include "distributedDB/utils/utils.hpp"

#include <iostream>

using namespace std;

namespace distributedDB {

TransactionManager::TransactionManager(int dmCount, int varCount, vector<vector<int>> &dmToVarlist): dmCount(dmCount), dmToVarList(dmToVarlist){
    varToDmList = vector<vector<int>>(varCount+1, vector<int>());
    incrementClock();
    for(int i = 0; i <= dmCount; i++) {
        //cout<<"creating manager "<<i<<endl;
        managers.emplace_back(DataManager(dmToVarList[i]));

        for(auto &var: dmToVarList[i]) {
            // cout<<var<<endl;
            varToDmList[var].emplace_back(i);
        }
    }
}

int TransactionManager::incrementClock() {
    return ++globalClock;
};

void TransactionManager::beginTransaction(int transactionId) {
    runningTransactions[transactionId] = new Transaction(transactionId, incrementClock());
};

string TransactionManager::endTransaction(int transactionId){ 
    incrementClock();
    auto &transaction = runningTransactions[transactionId];
    runningTransactions.erase(transactionId);
    
    //abort conditions: first committer wins, rwrw edges, if t writes to any site s and s fails before t commits

    if(safeTransaction(commitedTransactions, *transaction)) {

        addInCommittedMap(commitedTransactions, *transaction);

        if(hasRWRWCycle(commitedTransactions, transactionId)){
            removeFromCommittedMap(commitedTransactions, *transaction);
            return "T" + to_string(transactionId) + " aborts";
        }
    }

    return "T" + to_string(transactionId) + " commits";
};

string TransactionManager::readData(int transactionId, int dataId){ 
    incrementClock();
    //check if given transaction is currently running
    if (runningTransactions.find(transactionId) == runningTransactions.end()){
        return "Given transaction is currently not running.";
    }
    
    string returnMsg = "Transaction T" + to_string(transactionId) + " read variable x" + to_string(dataId) + " as ";
    auto &trans = runningTransactions[transactionId];
    // cout << dataId << endl;
    // cout << managers[1].getDataSnapshot(dataId, globalClock) << endl;

    //read from a local copy if possible
    int result, dmId = -1;
    int found = 0; // 0 means waiting 1 means item found and -1 means all sites down

    if (trans->hasLocalCopy(dataId, result)){
        found = 1;
    }
    else {
        for(auto &dm: varToDmList[dataId]) {
            // if(managers[dm].isDown()) {
            //     continue;
            // }
            // found = -1;
            if(managers[dm].canReadDataItem(dataId, trans->getBeginTime(), result)){
                found = 1;
                dmId = dm;
                break;
            }
        }
    }
    
    if(found) {
        returnMsg = returnMsg + to_string(result);
        trans->addReadOperation(dataId, dmId, result, globalClock);

    } else {
        // Wait for at least one site to be up
        runningTransactions.erase(transactionId);
        pendingTransactions[dataId] = trans;

        returnMsg = "Waiting for the site to be up";
    }

    return returnMsg;
};

string TransactionManager::writeData(int transactionId, int dataId, int dataValue){
    incrementClock();
     //check if given transaction is currently running
    if (runningTransactions.find(transactionId) == runningTransactions.end()){
        return "Given transaction is currently not running.";
    }
    runningTransactions[transactionId]->addWriteOperation(dataId, dataValue, globalClock);
    //managers[1].setDataSnapshot(dataId, dataValue, globalClock);
    return "Not Implemented Error.";
};

string TransactionManager::recoverDataManager(int dataManagerId){ 
    incrementClock();
    if(!managers[dataManagerId].isDown()){
        return "Site " + to_string(dataManagerId) + " is already up.";
    }
    managers[dataManagerId].upStatus(globalClock);
    //TODO run any pending transactions that depend on current site, and move it to runningtransaction if unblocked
    return "Site " + to_string(dataManagerId) + " has recovered and all passible pending operations have completed.";
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
        for(auto &id: dmToVarList[dm]){ // TODO: add commas between each dataId
            cout << " x" << id << ": " << managers[dm].getDataSnapshot(id, globalClock).second;
        };
        cout << endl;
    };

    return "";

};

}




