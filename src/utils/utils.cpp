#include <iostream>
#include "distributedDB/utils/utils.hpp"
using namespace std;

namespace distributedDB {
string findAndReplaceAll(string s, string toReplace, string replaceWith){
    //Reference: https://stackoverflow.com/questions/5878775/how-to-find-and-replace-string

    string buf;
    size_t pos = 0;
    size_t prevPos;

    // Reserves rough estimate of final size of string.
    buf.reserve(s.size());

    while (true) {
        prevPos = pos;
        pos = s.find(toReplace, pos);
        if (pos == std::string::npos)
            break;
        buf.append(s, prevPos, pos - prevPos);
        buf += replaceWith;
        pos += toReplace.size();
    }

    buf.append(s, prevPos, s.size() - prevPos);
    s.swap(buf);
    return s;
}

bool safeTransaction(unordered_map<int, Transaction*> &commitedTransactions, Transaction &t, vector<DataManager> &managers) {
    // Checking if anyone of the sites are up after the write and before the commit
    for(auto &op: t.getAllWriteOperations()) {
        for(auto &id: op.getWriteManagerIds()) {
            if(!managers[id].siteUpSince(t.getWriteTime(op.getDataId()))) {
                return false;
            } 
        }
    }

    // Checking if any transaction committed before this transaction and wrote on same site id
    for(auto &p: commitedTransactions) {
        auto trans = p.second;
        if(trans->getCommitTime() >= t.getBeginTime()) {
            for(auto &op: trans->getAllWriteOperations()) {
                if(t.getWriteTime(op.getDataId()) != -1) {
                    return false;
                }
            }
        }
    }

    return true;
}


bool dfs(unordered_map<int, Transaction*> &commitedTransactions, int t_id, unordered_map<int, int> reached, int rwcount){
    bool consecutiveRWRW = true;
    if(rwcount < 2) {
        consecutiveRWRW = false;
    }
    for(auto &edge:commitedTransactions[t_id]->getEdges()) {
        if(edge.second == READ_WRITE) {
            rwcount++;
        } else if(rwcount < 2) {
            rwcount = 0;
        }

        if(reached[edge.first]) {
            if(consecutiveRWRW || rwcount >= 2) return true;
            else continue;
        }
        reached[edge.first] = 1;

        if(dfs(commitedTransactions, edge.first, reached, rwcount)){
            return true;
        }

        reached[edge.first] = 0;
        if(edge.second == READ_WRITE) {
            rwcount--;
        }
    }
    return false;
}

bool hasRWRWCycle(unordered_map<int, Transaction*> &commitedTransactions, int t_id) {
    //cout << "checking rwrw cycle" <<endl;

    if(t_id < 0) return false;
    
    auto root = commitedTransactions[t_id];

    int rwcount = 0;
    
    unordered_map<int, int> reached;

    for(auto &t: commitedTransactions) {
        reached[t.second->t_id] = 0;
    }
    reached[t_id] = 1;

    for(auto &edge:root->getEdges()) {
        if(edge.second == READ_WRITE) {
            rwcount++;
        }
        reached[edge.first] = 1;
        if(dfs(commitedTransactions, edge.first, reached, rwcount)){
            return true;
        }
        reached[edge.first] = 0;
        if(edge.second == READ_WRITE) {
            rwcount--;
        }
    }

    return false;
}

void addInCommittedMap(unordered_map<int, Transaction*> &commitedTransactions, Transaction &t) {
    // iterate over committed Transaction to identify and add rw, ww and wr edges
    //cout << "adding in commited map" <<endl;
    for(auto trans: commitedTransactions){
        for(auto &read: t.getReadSet()){
            if(trans.second -> getWriteTime(read.second) != -1){ //t reads trans writes
                if(trans.second->getCommitTime() < t.getBeginTime()){ 
                    // trans commits before t begins, add edge trans --wr--> t
                    //cout << "trans --wr--> t" <<endl;
                    trans.second->addEdge(t.t_id, EdgeType::WRITE_READ);
                }
                else{
                    // trans commits after t begins, add edge t --rw--> trans
                    //cout << "t --rw--> trans" <<endl;
                    t.addEdge(trans.second->t_id, EdgeType::READ_WRITE);
                }
            }
        }

        for(auto &read: t.getWriteSet()){
            if(trans.second -> getReadTime(read.second) != -1){ //t writes trans reads
                // t always commits after trans begins, add edge trans --rw--> t
                //cout << "trans --rw--> t" <<endl;
                trans.second->addEdge(t.t_id, EdgeType::READ_WRITE);               
            }
        }

        for(auto &read: t.getWriteSet()){
            if(trans.second -> getWriteTime(read.second) != -1){ //t writes trans writes
                // t always commits after trans commits, add edge trans --ww--> t
                //cout << "trans --ww--> t" <<endl;
                trans.second->addEdge(t.t_id, EdgeType::WRITE_WRITE);
            }
        }
       
    }

    //add to committed map
    commitedTransactions[t.t_id] = &t;
}

void removeFromCommittedMap(unordered_map<int, Transaction*> &commitedTransactions, Transaction &t) {
    //remove from committed map
    commitedTransactions.erase(t.t_id);
    for(auto trans: commitedTransactions){
        trans.second->removeEdges(t.t_id);
    }
    delete(&t);

}

}