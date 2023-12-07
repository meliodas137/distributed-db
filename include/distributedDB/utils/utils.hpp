//===----------------------------------------------------------------------===//
//                         distributedDB
//
// distributedDB/utils/utils.hpp
//
//
//===----------------------------------------------------------------------===//

#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include "distributedDB/transaction_manager/transaction/transaction.hpp"

using namespace std;

namespace distributedDB {

string findAndReplaceAll(string s, string toReplace, string replaceWith);
bool safeTransaction(unordered_map<int, Transaction*> &commitedTransactions, Transaction &transaction, vector<DataManager> &managers);
bool hasRWRWCycle(unordered_map<int, Transaction*> &commitedTransactions, int t_id);
void removeFromCommittedMap(unordered_map<int, Transaction*> &commitedTransactions, Transaction &t);
void addInCommittedMap(unordered_map<int, Transaction*> &commitedTransactions, Transaction &t);
}

#endif 