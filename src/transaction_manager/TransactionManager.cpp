#include "distributedDB/transaction_manager/TransactionManager.hpp"
#include "distributedDB/utils/utils.hpp"

#include <iostream>

using namespace std;

namespace distributedDB {

TransactionManager::TransactionManager(int dmCount, vector<vector<int>> &dmToVarlist): dmCount(dmCount), dmToVarList(dmToVarlist){
    for(int i = 0; i <= dmCount; i++) {
        //cout<<"creating manager "<<i<<endl;
        managers.emplace_back(DataManager(dmToVarList[i]));
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
    
    string returnMsg = "Transaction T" + to_string(transactionId) + " read variable x" + to_string(dataId) + " as ";
    runningTransactions[transactionId]->addReadOperation(dataId, globalClock);
    // cout << dataId << endl;
    // cout << managers[1].getDataSnapshot(dataId, globalClock) << endl;

    //read from a local copy if possible
    int localVal;
    if (runningTransactions[transactionId]->hasLocalCopy(dataId, localVal)){
        returnMsg = returnMsg + to_string(localVal);
    }
    else{
        //TODO
        returnMsg = "Not Found Locally.";

    }
    
    return returnMsg;
};

string TransactionManager::writeData(int transactionId, int dataId, int dataValue){
    incrementClock();
    runningTransactions[transactionId]->addWriteOperation(dataId, dataValue, globalClock);
    //managers[1].setDataSnapshot(dataId, dataValue, globalClock);
    return "Not Implemented Error.";
};

string TransactionManager::recoverDataManager(int dataManagerId){ 
    incrementClock();
    return "Not Implemented Error.";
};

string TransactionManager::failDataManager(int dataManagerId){ 
    incrementClock();
    return "Not Implemented Error.";
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




