#include "distributedDB/transaction_manager/transaction/Transaction.hpp"
#include <iostream>

using namespace std;
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

void Transaction::addEdge(int t_id, EdgeType type){

    for(auto &edge: outEdges) {
        // Edge already in the list
        if(edge.first == t_id && edge.second == type) {
            return;
        }
    }

    outEdges.emplace_back(make_pair(t_id, type));
}

void Transaction::removeEdges(int t_id){
    outEdges.erase(remove(outEdges.begin(), outEdges.end(), make_pair(t_id, EdgeType::READ_WRITE)), outEdges.end());
    outEdges.erase(remove(outEdges.begin(), outEdges.end(), make_pair(t_id, EdgeType::WRITE_READ)), outEdges.end());
    outEdges.erase(remove(outEdges.begin(), outEdges.end(), make_pair(t_id, EdgeType::WRITE_WRITE)), outEdges.end());
}

vector<pair<int, EdgeType>> Transaction::getEdges(){
    return outEdges;
}

void Transaction::addWriteOperation(int dataId, vector<int> dmIds, int value, int time){
    writeSet[time] = dataId;
    writeOps.emplace_back(Operation(dataId, value, dmIds, OpType::WRITE));
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

vector<int> Transaction::getPendingOperation(){
    return pendingOperation;
}
   
void Transaction::setPendingOperation(vector<int> op){
    pendingOperation = op;
}

int Transaction::getWriteTime(int op_id){
    for(auto &p: writeSet) {
        if(op_id == p.second) {
            return p.first;
        }
    }
    return -1;
}
int Transaction::getReadTime(int op_id){
    for(auto &p: readSet) {
        if(op_id == p.second) {
            return p.first;
        }
    }
    return -1;
}

unordered_map<int, int> Transaction::getReadSet(){
    return readSet;
};

unordered_map<int, int> Transaction::getWriteSet(){
    return writeSet;
};

}