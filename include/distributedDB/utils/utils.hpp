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
bool safeTransaction(Transaction &transaction, vector<Transaction> &commitedTransactions);
bool hasRWRWCycle(vector<Transaction> &commitedTransactions, int rootIdx);

}

#endif 