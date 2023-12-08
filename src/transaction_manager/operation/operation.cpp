#include "distributedDB/transaction_manager/operation/Operation.hpp"

namespace distributedDB {

Operation::Operation(int dataId, int val, OpType type): dataId(dataId), value(val), type(type){};
Operation::Operation(int dataId, int val, int readManagerId, OpType type): dataId(dataId), value(val), type(type), readManagerId(readManagerId){};
Operation::Operation(int dataId, int val, vector<int> writeManagerIds, OpType type): dataId(dataId), value(val), type(type), writeManagerIds(writeManagerIds){};

int Operation::getDataId(){
    return dataId;
}

int Operation::getValue(){
    return value;
}

vector<int> Operation::getWriteManagerIds(){
    return writeManagerIds;
}

// bool Operation::isReadType(){
//     return type == OpType::READ;
// }

// bool Operation::isWriteType(){
//     return type == OpType::WRITE;
// }
}