#include "distributedDB/transaction_manager/operation/Operation.hpp"

namespace distributedDB {

Operation::Operation(int dataId, int val, OpType type): dataId(dataId), value(val), type(type){};
Operation::Operation(int dataId, int val, int dmId, OpType type): dataId(dataId), value(val), type(type), managerId(dmId){};

int Operation::getDataId(){
    return dataId;
}

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