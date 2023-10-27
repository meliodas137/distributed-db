#include <stdio.h>
#include <iostream>
#include <distributedDB/test.hpp>

using namespace distributedDB;

int main(int argc, char *argv[]) {
    std::cout<<"Main Compiled Successfully!\n";
    PrintPrompt pr = PrintPrompt();
    pr.printing();
    return 0;
}

