#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "distributedDB/transaction_manager/TransactionManager.hpp"

using namespace std;

namespace distributedDB {
TransactionManager::TransactionManager(int dmCount, unordered_map<int, vector<int>> dmToVarlist){};
string TransactionManager::beginTransaction(int transactionId){ return "Not Implemented Error.";};
string TransactionManager::endTransaction(int transactionId){ return "Not Implemented Error.";};
string TransactionManager::readData(int transactionId, int dataId){ return "Not Implemented Error.";};
string TransactionManager::writeData(int transactionId, int dataId, int dataValue){ return "Not Implemented Error.";};
string TransactionManager::recoverDataManager(int dataManagerId){ return "Not Implemented Error.";};
string TransactionManager::failDataManager(int dataManagerId){ return "Not Implemented Error.";};
string TransactionManager::dumpData(){ return "Not Implemented Error.";};
}




