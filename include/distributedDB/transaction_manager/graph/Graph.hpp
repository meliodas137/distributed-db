//===----------------------------------------------------------------------===//
//                         distributedDB
//
// distributedDB/transaction_manager/graph/Graph.hpp
//
//
//===----------------------------------------------------------------------===//

#ifndef GRAPH_H
#define GRAPH_H

#pragma once
#include <unordered_map>
#include <utility>
#include <vector>
#include <iostream>

using namespace std;

namespace distributedDB {

enum EdgeType{
    READ,
    WRITE,
};

class Graph {
private: 
    unordered_map<int, vector<pair<int, EdgeType>>> adjacencyList;

public:
    Graph();
    void addReadEdge(int fromTransactionId, int toTransactionId);
    void addWriteEdge(int fromTransactionId, int toTransactionId);
    void removeTransactionNode(int transactionId);
    bool hasRWRWCycle();
    void printGraph();
};
}
#endif          