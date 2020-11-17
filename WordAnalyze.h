/*
 * @Author: Leon-Francis
 * @Contact: 15290552788@163.com
 * @Date: 2020-11-17 19:34:49
 * @LastEditTime: 2020-11-17 20:08:49
 * @LastEditors: Leon-Francis
 * @Description: 
 * @FilePath: /CompilerExperment/WordAnalyze.h
 * @(C)Copyright 2019-2020, Leon-Francis
 */
#include <fstream>
#include <iostream>
#include <vector>
#include "Tokenize.h"

using namespace std;

void readFile(string inPath, vector<string> allText)
{
    ifstream inFile(inPath.c_str());
    if (!inFile.is_open())
    {
        cerr << "open file failed!" << endl;
        exit(-1);
    }
    string temp;
    while (getline(inFile, temp))
    {
        allText.push_back(temp);
    }
    inFile.close();
    cout << "original programs are as follows:" << endl;
    cout << endl;
    for (int i = 0; i < allText.size(); i++)
    {
        cout << allText[i] << endl;
    }
    return;
}

int isKeyWord(string str)
{
    if (str != "")
    {
        for (int i = 0; i < KEYWORDNUM; i++)
        {
            if (str == keyWord[i].name)
            {
                return keyWord[i].code;
            }
        }
    }
    return -1;
}

int isOperator(string str)
{
    if (str != "")
        for (int i = 0; i < OPERATORWORDNUM; i++)
        {
            {
                if (str == operatorWord[i].name.c_str())
                {
                    return operatorWord[i].code;
                }
            }
        }
    return -1;
}

int isDelimeter(string str)
{
    if (str != "")
    {
        for (int i = 0; i < DELIMETERNUM; i++)
        {
            if (str == delimeter[i].name)
            {
                return delimeter[i].code;
            }
        }
    }
    return -1;
}

void text2Token(vector<string> allText)
{
    for (int lineI = 0; lineI < allText.size(); lineI++)
    {
        string lineText = allText[lineI];
        string word = "";
        int index = 0;
        while (index != lineText.size())
        {
            if (isspace(lineText[index]))
            {
                index++;
                continue;
            }
            while (!isspace(lineText[index]) && !isDelimeter(lineText.substr(index, 1)))
            {
                word.push_back(lineText[index]);
                index++;
            }
            //TODO: 对word的分析
            if (isspace(lineText[index]))
            {
                index++;
                continue;
            }
            if (isDelimeter(lineText.substr(index, 1)))
            {
                //TODO: 将界符插入符号表
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    cout << "Input program path:";
    string inPath;
    cin >> inPath;
    vector<string> allText;
    readFile(inPath, allText);
    return 0;
}
