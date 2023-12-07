//===----------------------------------------------------------------------===//
//                         distributedDB
//
// distributedDB/transaction_manager/transaction/transaction.hpp
//
//
//===----------------------------------------------------------------------===//

#ifndef TRANSACTION_H
#define TRANSACTION_H

#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "distributedDB/transaction_manager/operation/operation.hpp"

using namespace std;

namespace distributedDB {

enum EdgeType{
    READ_WRITE,
    WRITE_READ,
    WRITE_WRITE
};
class Transaction {
public:
  int t_id;

private: 
  int beginTime;
  int commitTime;
  vector<int> pendingOperation;
  unordered_map<int, int> readSet; // (time, dataId)
  unordered_map<int, int> writeSet; // (time, dataId)
  vector<pair<int, EdgeType>> outEdges;
  vector<Operation> readOps;
  vector<Operation> writeOps;

public:
  Transaction(int t_id, int beginTime);
  void setCommitTime(int time);
  int getCommitTime();
  int getBeginTime();
  void addEdge(int t_id, EdgeType type);
  void addReadOperation(int dataId, int dmId, int val, int time);
  void addWriteOperation(int dataId, vector<int> dmIds, int value, int time);
  bool hasLocalCopy(int dataId, int &localVal);
  vector<Operation> getAllWriteOperations();
  vector<pair<int, EdgeType>> getEdges();
  vector<int> getPendingOperation();
  void setPendingOperation(vector<int>);
  int getWriteTime(int op_id);
  int getReadTime(int op_id);
};
}
#endif 