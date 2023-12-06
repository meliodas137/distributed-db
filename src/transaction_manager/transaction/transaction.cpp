#include "distributedDB/transaction_manager/transaction/Transaction.hpp"
#include <iostream>
namespace distributedDB {

Transaction::Transaction(int t_id, int beginTime): t_id(t_id), beginTime(beginTime) {};

void Transaction::setCommitTime(int time) {
    commitTime = time;
}

int Transaction::getCommitTime() {
    return commitTime;
}

int Transaction::getBeginTime() {
    return beginTime;
}

bool Transaction::inReadSet(int dataId) {
    if(readSet.empty() || readSet.find(dataId) == readSet.end()) {
        return false;
    }
    return true;
}

bool Transaction::inWriteSet(int dataId) {
    if(writeSet.empty() || writeSet.find(dataId) == writeSet.end()) {
        return false;
    }
    return true;
}

void Transaction::addEdge(int t_id, EdgeType type){

    for(auto &edge: outEdges) {
        // Edge already in the list
        if(edge.first == t_id && edge.second == type) {
            return;
        }
    }

    outEdges.emplace_back(make_pair(t_id, type));
}

vector<pair<int, EdgeType>> Transaction::getEdges(){
    return outEdges;
}

void Transaction::addWriteOperation(int dataId, int value, int time){
    writeSet[time] = dataId;
    writeOps.emplace_back(Operation(dataId, value, OpType::WRITE));
}

void Transaction::addReadOperation(int dataId, int dmId, int val, int time){
    readSet[time] = dataId;
    readOps.emplace_back(Operation(dataId, val, dmId, OpType::READ)); 
    // TODO: Read value from the correct data item before storing it in the op
    // Read from the writeOps value for first
}

bool Transaction::hasLocalCopy(int dataId, int &localVal){
    // traverse in reverse order to find latest written copy
    for( int opIdx = writeOps.size()-1; opIdx >= 0; opIdx-- ) { 
        if( writeOps[opIdx].getDataId() == dataId ){
            localVal = writeOps[opIdx].getValue(); //set localVal if local copy found
            return true;
        } 
    }

    return false;
}

vector<Operation> Transaction::getAllWriteOperations(){
    return writeOps;
}
   
}