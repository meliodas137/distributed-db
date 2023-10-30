#include "distributedDB/transaction_manager/operation/operation.hpp"

namespace distributedDB {

Operation::Operation(int data, int val, OpType type): data(data), value(val), type(type){};

int Operation::getValue(){
    return value;
}

bool Operation::isReadType(){
    return type == OpType::READ;
}

bool Operation::isWriteType(){
    return type == OpType::WRITE;
}
}