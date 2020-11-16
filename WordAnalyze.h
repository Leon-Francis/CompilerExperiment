#include <fstream>
#include <iostream>
#include "Tokenise.h"

using namespace std;

void readFile(string inPath, string outPath)
{
    ifstream inFile(inPath.c_str());
    if (!inFile.is_open())
    {
        cerr << "open file failed!" << endl;
        exit(-1);
    }
    char textChar;
    while (getchar(inFile)
    {
        
    }
    inFile.close();
}