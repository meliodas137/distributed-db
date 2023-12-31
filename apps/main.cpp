#include <stdio.h>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>

#include "distributedDB/transaction_manager/TransactionManager.hpp"
#include "distributedDB/utils/utils.hpp"

namespace distributedDB {};
using namespace distributedDB;
using namespace std;

TransactionManager initializeTM() {
    //initialize transaction manager
    int dmCount = 10;
    int varCount = 20;

    vector<vector<pair<int, bool>>> dmToVarList(dmCount+1, vector<pair<int, bool>>()); 
    for(int var = 1; var <= varCount; var++){
        //odd variables will go to var%10 th data site
        if(var%2){
            int dm = var%10 + 1;
            dmToVarList[dm].emplace_back(make_pair(var, true));
        }
        //even variables will go to all data sites
        else {
            for(int dm = 1; dm <= dmCount; dm++){
                dmToVarList[dm].emplace_back(make_pair(var, false));
            };
        }        
    };

    // TransactionManager tm(dmCount, dmToVarList);
    return TransactionManager(dmCount, varCount, dmToVarList);
}

string runCommand(TransactionManager &tm, vector<string> &cmdArgs) {
    string formatError = "Invalid Command Format.";

    if(cmdArgs.empty()) {
        return "INVALID COMMAND";
    }

    try{
        if (cmdArgs[0] == "begin"){
            if(cmdArgs.size() != 2) {
                throw invalid_argument(formatError);
            }
            int transactionId = stoi(cmdArgs[1]);
            return tm.beginTransaction(transactionId);
        }
        else if (cmdArgs[0] == "end"){
            if(cmdArgs.size() != 2) {
                throw invalid_argument(formatError);
            }
            int transactionId = stoi(cmdArgs[1]);
            return tm.endTransaction(transactionId);
        }
        else if (cmdArgs[0] == "dump"){
            if(cmdArgs.size() != 1) {
                throw invalid_argument(formatError);
            }
            return tm.dumpData();
        }
        else if (cmdArgs[0] == "fail"){
            if(cmdArgs.size() != 2) {
                throw invalid_argument(formatError);
            }
            int dataManagerId = stoi(cmdArgs[1]);
            return tm.failDataManager(dataManagerId);
        }
        else if (cmdArgs[0] == "recover"){
            if(cmdArgs.size() != 2) {
                throw invalid_argument(formatError);
            }
            int dataManagerId = stoi(cmdArgs[1]);
            return tm.recoverDataManager(dataManagerId);
        }
        else if (cmdArgs[0] == "R"){
            if(cmdArgs.size() != 3) {
                throw invalid_argument(formatError);
            }
            int transactionId = stoi(cmdArgs[1]);
            int dataId = stoi(cmdArgs[2]);
            
            return tm.readData(transactionId, dataId);
        }
        else if (cmdArgs[0] == "W"){
            if(cmdArgs.size() != 4) {
                throw invalid_argument(formatError);
            }
            int transactionId = stoi(cmdArgs[1]);
            int dataId = stoi(cmdArgs[2]);
            int dataValue = stoi(cmdArgs[3]);
            
            return tm.writeData(transactionId, dataId, dataValue);
        }
    }
    catch(const std::exception &exc){
        std::cerr << exc.what();
        return "";
    }
    return "INVALID COMMAND";
}

int main(int argc, char *argv[]) {
    TransactionManager tm = initializeTM();

    string inputCmd;
    string arg;

    while(1){
        getline(cin, inputCmd);
        //replace all deliminators with space in input command
        inputCmd = findAndReplaceAll(inputCmd, "(", " ");
        inputCmd = findAndReplaceAll(inputCmd, ",", " ");
        inputCmd = findAndReplaceAll(inputCmd, ")", " ");
        inputCmd = findAndReplaceAll(inputCmd, "T", " ");
        inputCmd = findAndReplaceAll(inputCmd, "x", " ");

        istringstream is(inputCmd);
        vector<string> cmdArgs;
        while(getline(is, arg, ' ')){
            if(arg != "") {
                cmdArgs.push_back(arg);
            }  
        }
        cout << runCommand(tm, cmdArgs) << endl;
        if(cin.eof()) return 0;
    }

    return 0;
}

