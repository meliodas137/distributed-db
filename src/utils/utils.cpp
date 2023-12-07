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
    if(commitedTransactions.empty()) return true; 
    
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

bool hasRWRWCycle(unordered_map<int, Transaction*> &commitedTransactions, int t_id) {
    // TODO: Handle proper cycle abort checks
    if(t_id < 0) return false;
    
    auto root = commitedTransactions[t_id];
    return false;
}

void addInCommittedMap(unordered_map<int, Transaction*> &commitedTransactions, Transaction &t) {
    commitedTransactions[t.t_id] = &t; // TODO: iterate over committed Transaction and remove it's edges
}

void removeFromCommittedMap(unordered_map<int, Transaction*> &commitedTransactions, Transaction &t) {
    commitedTransactions.erase(t.t_id); // TODO: iterate over committed Transaction and remove it's edges
    delete(&t);

}

}