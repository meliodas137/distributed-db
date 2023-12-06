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

#include <vector>
#include <string>
#include <unordered_map>
#include "distributedDB/data_manager/DataManager.hpp"
//#include "distributedDB/transaction_manager/graph/Graph.hpp"
#include "distributedDB/transaction_manager/transaction/Transaction.hpp"
#include "distributedDB/transaction_manager/operation/operation.hpp"

using namespace std;

namespace distributedDB {
class TransactionManager {
private: 
  vector<vector<pair<int, bool>>> dmToVarList = {};
  vector<vector<int>> varToDmList = {};
  int dmCount;
  vector<DataManager> managers = {};
  unordered_map<int, vector<Transaction>> transactions;
  int globalClock = 0;

public:
  unordered_map<int, Transaction*> commitedTransactions; // (T_id, T)
  unordered_map<int, Transaction*> runningTransactions; // (T_id, T)
  unordered_map<int, vector<Transaction*>> pendingTransactions; // (x_id, [T1, T2]) -> T1 and T2 waiting on x_id

  //Graph* serializationGraph = new Graph();

private:
  int incrementClock();
  int decrementClock();
  void commitTransaction(Transaction &transaction);

public:
  TransactionManager(int dmCount, int varCount, vector<vector<pair<int, bool>>> &dmToVarlist);
  void beginTransaction(int transactionId);
  string endTransaction(int transactionId);
  string readData(int transactionId, int dataId);
  string writeData(int transactionId, int dataId, int dataValue);
  string recoverDataManager(int dataManagerId);
  string failDataManager(int dataManagerId);
  string dumpData();

};
}
#endif 