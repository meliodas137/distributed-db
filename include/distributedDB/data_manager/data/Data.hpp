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
  Data(int id);
  void setDataSnapshot(int time, int value);
  pair<int,int> getDataSnapshot(int time);

private:
  pair<int,int> searchInHistory(int time);
};
}
#endif 