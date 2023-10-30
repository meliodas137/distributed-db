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

}