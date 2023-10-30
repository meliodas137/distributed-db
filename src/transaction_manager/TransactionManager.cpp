#include "distributedDB/transaction_manager/TransactionManager.hpp"
#include "distributedDB/utils/utils.hpp"

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
    runningTransactions[transactionId]->addReadOperation(dataId, globalClock);
    // cout << dataId << endl;
    // cout << managers[1].getDataSnapshot(dataId, globalClock) << endl;
    return "Not Implemented Error.";
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
    return "Not Implemented Error.";
};

}




