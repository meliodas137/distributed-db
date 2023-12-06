#include "distributedDB/data_manager/data/Data.hpp"

#include <iostream>

namespace distributedDB {

Data::Data(int id, bool isUnique): id(id), isUniqueToDm(isUnique){
    // initialize data value at time 0
    setDataSnapshot(0, 10*id); 
};

void Data::setDataSnapshot(int time, int value){
    //set data value at given time
    auto data = make_pair(time, value);
    history.emplace_back(data);
};

pair<int,int> Data::getDataSnapshot(int time){
    //return data value at time 
    return searchInHistory(time);
};

pair<int,int> Data::searchInHistory(int time){
    //apply binary search to find data at time in history
    int start = 0;
    int end = history.size()-1;
    int mid;

    while (start <= end) {
		if( start == end ){
            if( history[start].first <= time ){
                return history[start];
            }
            break;
        }

        mid = start + (end - start) / 2;

        if( time < history[mid].first ){
            end = mid;
        }
        else{
            start = mid+1;
        }
    }
    
    return history[mid];
};


}