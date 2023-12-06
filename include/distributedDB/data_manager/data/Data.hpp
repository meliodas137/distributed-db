//===----------------------------------------------------------------------===//
//                         distributedDB
//
// distributedDB/transaction_manager/data/data.hpp
//
//
//===----------------------------------------------------------------------===//

#ifndef DATA_H
#define DATA_H

#pragma once

#include <vector>
#include <string>
#include <utility>

#include <unordered_map>

using namespace std;

namespace distributedDB {
class Data {
private: 
  int id;
  vector<pair<int, int>> history = {};
public:
  bool isUniqueToDm = false; //tracks non replicated data items

private:
  pair<int,int> searchInHistory(int time);

public:
  Data(int id, bool isUnique);
  void setDataSnapshot(int time, int value);
  pair<int,int> getDataSnapshot(int time);

};
}
#endif 