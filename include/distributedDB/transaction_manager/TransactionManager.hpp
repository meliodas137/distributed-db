//===----------------------------------------------------------------------===//
//                         distributedDB
//
// distributedDB/transaction_manager/TransactionManager.hpp
//
//
//===----------------------------------------------------------------------===//

#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#pragma once

#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

namespace distributedDB {
class TransactionManager {
  public:
    TransactionManager(int dmCount, unordered_map<int, vector<int>> &dmToVarlist);
    string beginTransaction(int transactionId);
    string endTransaction(int transactionId);
    string readData(int transactionId, int dataId);
    string writeData(int transactionId, int dataId, int dataValue);
    string recoverDataManager(int dataManagerId);
    string failDataManager(int dataManagerId);
    string dumpData();
  
};
}
#endif 