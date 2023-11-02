//===----------------------------------------------------------------------===//
//                         distributedDB
//
// distributedDB/data_manager/DataManager.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once
#include <vector>
#include <iostream>
#include <unordered_map>
#include "distributedDB/data_manager/data/Data.hpp"

namespace distributedDB{
class DataManager {

private:
    unordered_map<int, Data*> dataMap;

public:
    DataManager(vector<int> &dataItems);
    void setDataSnapshot(int time, int value, int dataId);
    pair<int,int> getDataSnapshot(int time, int dataId);
};
}