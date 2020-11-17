/*
 * @Author: Leon-Francis
 * @Contact: 15290552788@163.com
 * @Date: 2020-11-17 19:34:49
 * @LastEditTime: 2020-11-17 20:08:39
 * @LastEditors: Leon-Francis
 * @Description: 
 * @FilePath: /CompilerExperment/Tokenise.h
 * @(C)Copyright 2019-2020, Leon-Francis
 */
#include <vector>
#include <string>
#define KEYWORDNUM 24
#define OPERATORWORDNUM 14
#define DELIMETERNUM 8
using namespace std;

typedef struct
{
    string name;
    int code;
} Word;

typedef struct
{
    int label;    //单词序号
    string name;  //单词本身
    int code;     //单词种别编码
    int addr = 0; //单词在符号表中的指针
} WordToken;

typedef struct
{
    int number;      //序号
    string name[30]; //名字
    string type;     //类型

} WordSymble;

vector<WordToken> wordToken;
vector<WordSymble> wordSymble;

Word keyWord[24] = {{"begin", 1}, {"end", 2}, {"interger", 3}, {"char", 4}, {"bool", 5}, {"real", 6}, {"input", 7}, {"output", 8}, {"program", 9}, {"read", 10}, {"write", 11}, {"for", 12}, {"to", 13}, {"while", 14}, {"do", 15}, {"repeat", 16}, {"until", 17}, {"if", 18}, {"then", 19}, {"else", 20}, {"true", 21}, {"false", 22}, {"var", 23}, {"const", 24}};
Word operatorWord[14] = {{"+", 25}, {"-", 26}, {"*", 27}, {"/", 28}, {"=", 29}, {"<", 30}, {">", 31}, {"and", 32}, {"or", 33}, {"not", 34}, {"<=", 35}, {">=", 36}, {"<>", 37}, {":=", 38}};
Word delimeter[8] = {{"(", 44}, {")", 45}, {":", 46}, {".", 47}, {";", 48}, {",", 49}, {"\'", 51}, {"\"", 52}};
