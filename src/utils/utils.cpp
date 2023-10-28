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
}