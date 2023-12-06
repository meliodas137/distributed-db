//===----------------------------------------------------------------------===//
//                         distributedDB
//
// distributedDB/transaction_manager/operation/operation.hpp
//
//
//===----------------------------------------------------------------------===//

#ifndef OPERATION_H
#define OPERATION_H

#pragma once

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

namespace distributedDB {

enum OpType {
  READ,
  WRITE
};
class Operation {
private: 
  int dataId;
  int value;
  OpType type;
  int readManagerId; //-1 means local read
  vector<int> writeManagerIds;

public:
  Operation(int dataId, int value, OpType type);
  Operation(int dataId, int value, int readManagerId, OpType type);
  Operation(int dataId, int value, vector<int> writeManagerIds, OpType type);
  int getDataId();
  int getValue();
  vector<int> getWriteManagerIds();
  bool isReadType();
  bool isWriteType();
};
}
#endif 