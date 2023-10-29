#include "distributedDB/transaction_manager/graph/Graph.hpp"

using namespace std;

namespace distributedDB {

Graph::Graph(){};


void Graph::addReadEdge(int fromTransactionId, int toTransactionId){
    auto edge = make_pair(toTransactionId, EdgeType::READ);
    adjacencyList[fromTransactionId].emplace_back(edge);
};

void Graph::addWriteEdge(int fromTransactionId, int toTransactionId){
    auto edge = make_pair(toTransactionId, EdgeType::WRITE);
    adjacencyList[fromTransactionId].emplace_back(edge);
};

void Graph::removeTransactionNode(int transactionId){
    adjacencyList.erase(transactionId); //remove all edges from the given transaction

    //remove all edges to the given transaction
    //TODO
    // for (auto it = adjacencyList.begin(); it != adjacencyList.end(); it++) {
    //     for (int i = 0, i < it->second.size(); i++){
    //         if ( it->second[i].first == transactionId ){
    //             it->second.erase(i);
    //         };
    //     };
    // };
};

bool Graph::hasRWRWCycle(){
    cout << "Not Implemented Error" << endl;
    return false;
};

void Graph::printGraph(){
    for (auto it = adjacencyList.begin(); it != adjacencyList.end(); it++) {
        cout << "Edges from " << it->first << ": ";
        for (auto &edge: it->second){
            cout << edge.first << " type: " << edge.second << " ";           
        };
        cout << endl;
    };
};
};