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
  bool inReadSet(int dataId);
  bool inWriteSet(int dataId);
  void addEdge(int t_id, EdgeType type);
  void addReadOperation(int dataId, int time);
  void addWriteOperation(int dataId, int value, int time);
  bool hasLocalCopy(int dataId, int &localVal);
  vector<pair<int, EdgeType>> getEdges();
};
}
#endif 