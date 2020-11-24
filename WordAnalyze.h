/*
 * @Author: Leon-Francis
 * @Contact: 15290552788@163.com
 * @Date: 2020-11-17 19:34:49
 * @LastEditTime: 2020-11-24 20:00:54
 * @LastEditors: Leon-Francis
 * @Description: 
 * @FilePath: /CompilerExperment/WordAnalyze.h
 * @(C)Copyright 2019-2020, Leon-Francis
 */
#include "Tokenize.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void readFile(string inPath, vector<string> allText)
{
    //TODO: 由于时间有限，暂时写不了预处理过程
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

int isKeyWord(string str, int index) //最大匹配
{
    if (str != "")
    {
        for (int i = 0; i < KEYWORDNUM; i++)
        {
            for (int j = min(KEYWORDMAXLEN, int(str.size()) - index); j > 0; j--)
            {
                if (str.substr(index, j) == delimeter[i].name)
                {
                    return delimeter[i].code;
                }
            }
        }
    }
    return -1;
}

int isOperator(string str, int index) //最大匹配
{
    if (str != "")
        for (int i = 0; i < OPERATORWORDNUM; i++)
        {
            for (int j = min(OPERATORWORDMAXLEN, int(str.size()) - index); j > 0; j--)
            {
                if (str.substr(index, j) == delimeter[i].name)
                {
                    return delimeter[i].code;
                }
            }
        }
    return -1;
}

int isDelimeter(string str, int index) //最大匹配
{
    if (str != "")
    {
        for (int i = 0; i < DELIMETERNUM; i++)
        {
            for (int j = min(DELIMETERMAXLEN, int(str.size()) - index); j > 0; j--)
            {
                if (str.substr(index, j) == delimeter[i].name)
                {
                    return delimeter[i].code;
                }
            }
        }
    }
    return -1;
}

string isId(string str, int index)
{
    if (str != "")
    {
        if (isalpha(str[index]) || str[index] == '_')
        {
            int num = 1;
            while ((index + num < str.size()) && (isalpha(str[index + num]) || isdigit(str[index + num]) || str[index + num] == '_'))
            {
                num++;
            }
            return str.substr(index, num);
        }
    }
    return "";
}

string isInteger(string str, int index)
{
    if (str != "")
    {
        if (isdigit(str[index]))
        {
            int num = 1;
            while ((index + num < str.size()) && isdigit(str[index + num]))
            {
                num++;
            }
            return str.substr(index, num);
        }
    }
    return "";
}

string isRealNum(string str, int index)
{
    if (str != "")
    {
        if (isdigit(str[index]))
        {
            int num = 1;
            while (isdigit(str[index + num]))
            {
                num++;
            }
            if (str[index + num] == 'E' || str[index + num] == 'e')
            {
                num++;
                if (isdigit(str[index + num]))
                {
                    num++;
                    while (isdigit(str[index + num]))
                    {
                        num++;
                    }
                    return str.substr(index, num);
                }
            }
            else if (str[index + num] == '.')
            {
                num++;
                while (isdigit(str[index + num]))
                {
                    num++;
                }
                if(str[index+num]=='E' || str[index+num]=='e')
                {
                    
                }
                else
                {
                    return str.substr(index, num);
                }
            }
        }
        else if (str[index] == '.')
        {
            int num = 1;
        }
    }
    return "";
}

int code2Len(int code)
{
    if (code <= KEYWORDNUM)
    {
        return keyWord[code - keyWord[0].code].name.size();
    }
    else if (code <= KEYWORDNUM + OPERATORWORDNUM)
    {
        return operatorWord[code - operatorWord[0].code].name.size();
    }
    else
    {
        return delimeter[code - delimeter[0].code].name.size();
    }
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
            if (isKeyWord(lineText, index))
            {
                //TODO: 将关键字插入到Token表
                continue;
            }
            if (isOperator(lineText, index))
            {
                //TODO: 将运算符插入到Token表
                continue;
            }
            if (isDelimeter(lineText, index))
            {
                //TODO: 将界符插入Token表
                continue;
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
