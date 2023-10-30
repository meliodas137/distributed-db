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
  int data;
  int value;
  OpType type;

public:
  Operation(int data, int value, OpType type);
  int getValue();
  bool isReadType();
  bool isWriteType();
};
}
#endif 