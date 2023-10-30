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
  unordered_map<int, int> readSet;
  unordered_map<int, int> writeSet;
  vector<pair<int, EdgeType>> outEdges;

public:
  Transaction(int t_id, int beginTime);
  void setCommitTime(int time);
  int getCommitTime();
  int getBeginTime();
  bool inReadSet(int t_id);
  bool inWriteSet(int t_id);
  void addEdge(int t_id, EdgeType type);
  vector<pair<int, EdgeType>> getEdges();
};
}
#endif 