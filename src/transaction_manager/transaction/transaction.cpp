#include "distributedDB/transaction_manager/transaction/Transaction.hpp"

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

bool Transaction::inReadSet(int t_id) {
    if(readSet.empty() || readSet.find(t_id) == readSet.end()) {
        return false;
    }
    return true;
}

bool Transaction::inWriteSet(int t_id) {
    if(writeSet.empty() || writeSet.find(t_id) == writeSet.end()) {
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

void Transaction::addReadOperation(int dataId, int time){
    readSet[time] = dataId;
    readOps.emplace_back(Operation(dataId, 0, OpType::READ)); 
    //TODO: Read value from the correct data item before storing it in the op
    // Read from the writeOps value for first
}

}