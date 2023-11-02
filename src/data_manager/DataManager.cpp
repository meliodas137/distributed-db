#include "distributedDB/data_manager/DataManager.hpp"

#include <iostream>

namespace distributedDB {

DataManager::DataManager(vector<int> &dataitems) {
    for(auto &item: dataitems) {
        dataMap[item] = new Data(item);
       // cout<<"adding data item "<<item<<endl;
    }
};

void DataManager::setDataSnapshot(int dataId, int value, int time){
    //set data value at given time
    dataMap[dataId]->setDataSnapshot(time, value);
};

pair<int,int> DataManager::getDataSnapshot(int dataId, int time){
    //return data value at time 
    //cout << "searching for data item" << dataId << endl;
    return dataMap[dataId]->getDataSnapshot(time);
};

bool DataManager::isDown() {
    return status == Status::Down;
}


void DataManager::upStatus(int upTime){
    if(status == Status::Down) {
        lastUpTime = upTime;
    }
    status = Status::Up;
};

void DataManager::downStatus(int downTime){
    if(status == Status::Up) {
        upHistory.emplace_back(make_pair(lastUpTime, downTime));
    }
    status = Status::Down;
};

}