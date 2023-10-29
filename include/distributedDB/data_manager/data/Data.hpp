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
#include <unordered_map>

using namespace std;

namespace distributedDB {
class Data {
private: 
  int id;

public:
  Data(int id);
};
}
#endif 