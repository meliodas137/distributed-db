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
  int managerId; //-1 means local read

public:
  Operation(int dataId, int value, OpType type);
  Operation(int dataId, int value, int dmId, OpType type);
  int getDataId();
  int getValue();
  bool isReadType();
  bool isWriteType();
};
}
#endif 