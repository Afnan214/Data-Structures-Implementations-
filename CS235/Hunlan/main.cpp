#include "members.h"
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[])
{
    MyManager engine;
    MyParser parser;
    std::string line;

    std::string file_name = argv[1];
    std::ifstream file(file_name);
    if (file.is_open())
    {
        bool shouldContinue{true};
        while (shouldContinue && std::getline(file, line))
        {

            shouldContinue = engine.process(parser(line));
        }
    }
    else
    {
        cout << "unable to open file";
    }
    return 0;
    file.close();
}