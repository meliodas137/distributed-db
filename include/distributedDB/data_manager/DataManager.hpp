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

enum Status {
    Up,
    Down
};
class DataManager {

private:
    unordered_map<int, Data*> dataMap;
    Status status = Status::Up;
    vector<pair<int,int>> upHistory = {};
    int lastUpTime = 1;

public:
    DataManager(vector<int> &dataItems);
    void setDataSnapshot(int time, int value, int dataId);
    pair<int,int> getDataSnapshot(int time, int dataId);
    bool canReadDataItem(int dataId, int beginTime, int &result);
    void upStatus(int upTime);
    void downStatus(int downTime);
    bool isDown();
};
}