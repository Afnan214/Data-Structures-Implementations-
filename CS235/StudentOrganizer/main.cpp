#include "StudOrganizer.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int main()
{
    MyManager engine;

    MyParser parser;
    std::string userInput;
    bool shouldStop{false};
    while (!shouldStop)
    {
        getline(cin, userInput);
        shouldStop = engine.process(parser(userInput));
    }
    return 0;
}