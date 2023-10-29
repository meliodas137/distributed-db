#include "distributedDB/data_manager/DataManager.hpp"

namespace distributedDB {

DataManager::DataManager(vector<int> &dataitems) {
    for(auto &item: dataitems) {
        dataMap[item] = new Data(item);
        // cout<<"adding data item "<<item<<endl;
    }
};

}