#include<string>
using namespace std;

typedef struct WordToken
{
    int label;
    string name[30];
    int code;
    int addr = 0;
} WT;

typedef struct WordSymble
{
    int number;
    string name[30];
    int type;

} WS;
