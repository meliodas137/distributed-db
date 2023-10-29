#include "distributedDB/transaction_manager/TransactionManager.hpp"

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

string TransactionManager::beginTransaction(int transactionId) {
    incrementClock();
    return "Not Implemented Error.";
};

string TransactionManager::endTransaction(int transactionId){ 
    return "Not Implemented Error.";
    };

string TransactionManager::readData(int transactionId, int dataId){ 
    incrementClock();
    // cout << dataId << endl;
    // cout << managers[1].getDataSnapshot(dataId, globalClock) << endl;
    return "Not Implemented Error.";
};

string TransactionManager::writeData(int transactionId, int dataId, int dataValue){
    incrementClock();
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




