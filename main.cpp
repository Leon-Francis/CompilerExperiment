/*
 * @Author: Leon-Francis
 * @Contact: 15290552788@163.com
 * @Date: 2020-12-01 16:21:13
 * @LastEditTime: 2020-12-02 10:46:25
 * @LastEditors: Leon-Francis
 * @Description: 顶层文件
 * @FilePath: /CompilerExperment/main.cpp
 * @(C)Copyright 2019-2020, Leon-Francis
 */

#include "WordAnalyze.h"
#include "GrammerTree.h"
#include <iostream>
#include <vector>

using namespace std;

void readFile(string inPath, vector<string> &allText);

int main(int argc, char const *argv[])
{
    cout << "Input program path:";
    string inPath;
    inPath = "D:\\TestCode.txt";
    vector<string> allText;
    readFile(inPath, allText);
    text2Token(allText);
    printAll();
    cout << endl;
    cout << endl;
    cout << endl;
    initProduction();
    NodePointer root;
    root = CreateTree(wordToken);
    CalculateAttr(root);
    Print4Element(root);
    return 0;
}
