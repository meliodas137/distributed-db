#include "distributedDB/data_manager/DataManager.hpp"

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

int DataManager::getDataSnapshot(int dataId, int time){
    //return data value at time 
    return dataMap[dataId]->getDataSnapshot(time);
};

}