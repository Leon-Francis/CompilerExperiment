/*
 * @Author: Leon-Francis
 * @Contact: 15290552788@163.com
 * @Date: 2020-11-30 12:16:37
 * @LastEditTime: 2020-11-30 12:16:37
 * @LastEditors: Leon-Francis
 * @Description: 语法树
 * @FilePath: /CompilerExperment/GrammerTree.h
 * @(C)Copyright 2019-2020, Leon-Francis
 */
#include <string>
#include <vector>
using namespace std;
#define BEGINADDR 100
int tempnum = 0;

typedef struct
{
    int addr;
    string op;
    string num1;
    string num2;
    string num3;
} OutputResult;
vector<OutputResult> outputResult;
int address = BEGINADDR;

typedef struct Node
{
    //属性
    string name = "";
    string place = "";
    int symbleIndex = -1;
    bool complete = true;
    int type = 0;
    vector<int> trueaddr;
    vector<int> falseaddr;
    vector<int> nextaddr;
    int printAddress = -1;
    int quad = -1;

    //指针
    struct Node *parents;
    vector<struct Node *> childs;

} * NodePointer;

NodePointer root;

string newTemp()
{
    return "T" + to_string(tempnum++);
}

void BackPatch(vector<int> backAddr, int quad)
{
    for (int i = 0; i < backAddr.size(); i++)
    {
        outputResult[backAddr[i] - BEGINADDR].num3 = to_string(quad);
    }
}

void Merge(vector<int> e1, vector<int> e3)
{
    for (int i = 0; i < e1.size(); i++)
    {
        bool ifMerge = true;
        for (int j = 0; j < e3.size(); j++)
        {
            if (e1[i] == e3[j])
            {
                ifMerge = false;
                break;
            }
        }
        if (ifMerge)
        {
            e3.push_back(e1[i]);
        }
    }
}

void StatementFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[2]->childs[0]->name != "empty")
    {
        if (pointer->printAddress == -1)
        {
            pointer->printAddress = address;
            address++;
        }
        if (pointer->childs[1]->place != "")
        {
        }
        else
        {
            pointer->complete = false;
        }
    }

    if (print)
    {
        if (pointer->childs[2]->childs[0]->name != "empty")
        {
            OutputResult temp;
            temp.addr = pointer->printAddress;
            temp.op = ":=";
            temp.num1 = pointer->childs[2]->place;
            temp.num2 = "__";
            temp.num3 = pointer->childs[1]->place;
            outputResult.push_back(temp);
        }
    }
}

void VariableClosureFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[1]->childs[0]->name != "empty")
    {
        if (pointer->printAddress == -1)
        {
            pointer->printAddress = address;
            address++;
        }
        if (pointer->childs[0]->place != "")
        {
        }
        else
        {
            pointer->complete = false;
        }
    }

    if (print)
    {
        if (pointer->childs[1]->place != "")
        {
            OutputResult temp;
            temp.addr = pointer->printAddress;
            temp.op = ":=";
            temp.num1 = pointer->childs[1]->place;
            temp.num2 = "__";
            temp.num3 = pointer->childs[0]->place;
            outputResult.push_back(temp);
        }
    }
}

void VariableFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    pointer->place = pointer->childs[0]->place;
}

void InitValueFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[0]->name == "empty")
    {
        return;
    }
    if (pointer->childs[1]->place != "")
    {
        pointer->place = pointer->childs[1]->place;
    }
    else
    {
        pointer->complete = false;
    }
}

void ExpressionFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[0]->place != "")
    {
        if (pointer->childs[1]->childs[0]->name != "empty")
        {
            if (pointer->printAddress == -1)
            {
                pointer->printAddress = address;
                address++;
            }
            if (pointer->childs[1]->place != "")
            {
                if (pointer->place == "")
                {
                    pointer->place = newTemp();
                }
            }
            else
            {
                pointer->complete = false;
            }
        }
        else
        {
            pointer->place = pointer->childs[0]->place;
        }
    }
    else
    {
        pointer->complete = false;
    }
    if (print)
    {
        if (pointer->childs[1]->childs[0]->name != "empty")
        {
            OutputResult temp;
            temp.addr = pointer->printAddress;
            temp.op = pointer->childs[1]->childs[0]->name;
            temp.num1 = pointer->childs[0]->place;
            temp.num2 = pointer->childs[1]->place;
            temp.num3 = pointer->place;
            outputResult.push_back(temp);
        }
    }
}

void FactorFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[0]->place != "")
    {
        if (pointer->childs[1]->childs[0]->name != "empty")
        {
            if (pointer->printAddress == -1)
            {
                pointer->printAddress = address;
                address++;
            }
            if (pointer->childs[1]->place != "")
            {
                if (pointer->place == "")
                {
                    pointer->place = newTemp();
                }
            }
            else
            {
                pointer->complete = false;
            }
        }
        else
        {
            pointer->place = pointer->childs[0]->place;
        }
    }
    else
    {
        pointer->complete = false;
    }
    if (print)
    {
        if (pointer->childs[1]->childs[0]->name != "empty")
        {
            OutputResult temp;
            temp.addr = pointer->printAddress;
            temp.op = pointer->childs[1]->childs[0]->name;
            temp.num1 = pointer->childs[0]->place;
            temp.num2 = pointer->childs[1]->place;
            temp.num3 = pointer->place;
            outputResult.push_back(temp);
        }
    }
}

void FactorExpressionFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[0]->name == "(")
    {
        if (pointer->childs[1]->place != "")
        {
            pointer->place = pointer->childs[1]->place;
        }
        else
        {
            pointer->complete = false;
        }
    }
    else if (pointer->childs[0]->name == "Variable")
    {
        if (pointer->childs[0]->place != "")
        {
            pointer->place = pointer->childs[0]->place;
        }
        else
        {
            pointer->complete = false;
        }
    }
    else
    {
        if (pointer->childs[0]->place != "")
        {
            pointer->place = pointer->childs[0]->place;
        }
        else
        {
            pointer->complete = false;
        }
    }
}

void DigitFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    pointer->place = pointer->childs[0]->place;
}

void FactorExpressionRecursionFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[0]->name == "empty")
    {
        return;
    }
    if (pointer->childs[1]->place != "")
    {
        if (pointer->childs[2]->childs[0]->name != "empty")
        {
            if (pointer->printAddress == -1)
            {
                pointer->printAddress = address;
                address++;
            }
            if (pointer->childs[2]->place != "")
            {
                if (pointer->place == "")
                {
                    pointer->place = newTemp();
                }
            }
            else
            {
                pointer->complete = false;
            }
        }
        else
        {
            pointer->place = pointer->childs[0]->place;
        }
    }
    else
    {
        pointer->complete = false;
    }
    if (print)
    {
        if (pointer->childs[2]->childs[0]->name != "empty")
        {
            OutputResult temp;
            temp.addr = pointer->printAddress;
            temp.op = pointer->childs[2]->childs[0]->name;
            temp.num1 = pointer->childs[1]->place;
            temp.num2 = pointer->childs[2]->place;
            temp.num3 = pointer->place;
            outputResult.push_back(temp);
        }
    }
}

void ItemFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[0]->name == "empty")
    {
        return;
    }
    if (pointer->childs[1]->place != "")
    {
        if (pointer->childs[2]->childs[0]->name != "empty")
        {
            if (pointer->printAddress == -1)
            {
                pointer->printAddress = address;
                address++;
            }
            if (pointer->childs[2]->place != "")
            {
                if (pointer->place == "")
                {
                    pointer->place = newTemp();
                }
            }
            else
            {
                pointer->complete = false;
            }
        }
        else
        {
            pointer->place = pointer->childs[0]->place;
        }
    }
    else
    {
        pointer->complete = false;
    }
    if (print)
    {
        if (pointer->childs[2]->childs[0]->name != "empty")
        {
            OutputResult temp;
            temp.addr = pointer->printAddress;
            temp.op = pointer->childs[2]->childs[0]->name;
            temp.num1 = pointer->childs[1]->place;
            temp.num2 = pointer->childs[2]->place;
            temp.num3 = pointer->place;
            outputResult.push_back(temp);
        }
    }
}

void AssignmentStatement(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->printAddress == -1)
    {
        pointer->printAddress = address;
        address++;
    }
    if (pointer->childs[0]->place != "" && pointer->childs[2]->place != "")
    {
    }
    else
    {
        pointer->complete = false;
    }
    if (print)
    {
        OutputResult temp;
        temp.addr = pointer->printAddress;
        temp.op = ":=";
        temp.num1 = pointer->childs[2]->place;
        temp.num2 = "__";
        temp.num3 = pointer->childs[0]->place;
        outputResult.push_back(temp);
    }
}

void BoolStatement(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[1]->childs[0]->name != "empty")
    {
        if (pointer->childs[0]->complete && pointer->childs[1]->complete)
        {
            pointer->falseaddr = pointer->childs[1]->falseaddr;
            Merge(pointer->childs[0]->trueaddr, pointer->trueaddr);
            Merge(pointer->childs[1]->trueaddr, pointer->trueaddr);
            BackPatch(pointer->childs[0]->falseaddr, pointer->childs[1]->childs[1]->quad);
        }
        else
        {
            pointer->complete = false;
        }
    }
    else
    {
        if (pointer->childs[0]->complete)
        {
            pointer->trueaddr = pointer->childs[0]->trueaddr;
            pointer->falseaddr = pointer->childs[0]->falseaddr;
        }
        else
        {
            pointer->complete = false;
        }
    }
}

void M(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->quad == -1)
    {
        pointer->quad = address;
    }
}

void N(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->nextaddr.size() == 0)
    {
        pointer->nextaddr.push_back(address);
    }
    if (pointer->printAddress == -1)
    {
        pointer->printAddress = address;
        address++;
    }
    if(print)
    {
        OutputResult temp;
        temp.addr = pointer->printAddress;
        temp.op = "j";
        temp.num1 = "__";
        temp.num2 = "__";
        temp.num3 = "0";
        outputResult.push_back(temp);
    }
}

void BoolStatementClosure(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[3]->childs[0]->name != "empty")
    {
        if (pointer->childs[2]->complete && pointer->childs[3]->complete)
        {
            pointer->falseaddr = pointer->childs[3]->falseaddr;
            Merge(pointer->childs[2]->trueaddr, pointer->trueaddr);
            Merge(pointer->childs[3]->trueaddr, pointer->trueaddr);
            BackPatch(pointer->childs[2]->falseaddr, pointer->childs[3]->childs[1]->quad);
        }
        else
        {
            pointer->complete = false;
        }
    }
    else
    {
        if (pointer->childs[2]->complete)
        {
            pointer->trueaddr = pointer->childs[2]->trueaddr;
            pointer->falseaddr = pointer->childs[2]->falseaddr;
        }
        else
        {
            pointer->complete = false;
        }
    }
}

void BoolItem(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[1]->childs[0]->name != "empty")
    {
        if (pointer->childs[0]->complete && pointer->childs[1]->complete)
        {
            pointer->trueaddr = pointer->childs[1]->trueaddr;
            Merge(pointer->childs[0]->falseaddr, pointer->falseaddr);
            Merge(pointer->childs[1]->falseaddr, pointer->falseaddr);
            BackPatch(pointer->childs[0]->falseaddr, pointer->childs[1]->childs[1]->quad);
        }
        else
        {
            pointer->complete = false;
        }
    }
    else
    {
        if (pointer->childs[0]->complete)
        {
            pointer->trueaddr = pointer->childs[0]->trueaddr;
            pointer->falseaddr = pointer->childs[0]->falseaddr;
        }
        else
        {
            pointer->complete = false;
        }
    }
}

void BoolItemClosure(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[3]->childs[0]->name != "empty")
    {
        if (pointer->childs[2]->complete && pointer->childs[3]->complete)
        {
            pointer->trueaddr = pointer->childs[3]->trueaddr;
            Merge(pointer->childs[2]->falseaddr, pointer->falseaddr);
            Merge(pointer->childs[3]->falseaddr, pointer->falseaddr);
            BackPatch(pointer->childs[2]->falseaddr, pointer->childs[3]->childs[1]->quad);
        }
        else
        {
            pointer->complete = false;
        }
    }
    else
    {
        if (pointer->childs[2]->complete)
        {
            pointer->trueaddr = pointer->childs[2]->trueaddr;
            pointer->falseaddr = pointer->childs[2]->falseaddr;
        }
        else
        {
            pointer->complete = false;
        }
    }
}

void BoolFactor(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[0]->name != "!")
    {
        if (pointer->trueaddr.size() == 0)
        {
            pointer->trueaddr.push_back(address);
            pointer->falseaddr.push_back(address + 1);
        }
        if (pointer->printAddress == -1)
        {
            pointer->printAddress = address;
            address++;
            address++;
        }
    }
    else
    {
        if (pointer->childs[1]->complete)
        {
            pointer->trueaddr = pointer->childs[1]->falseaddr;
            pointer->falseaddr = pointer->childs[1]->trueaddr;
        }
        else
        {
            pointer->complete = false;
        }
    }
    if (print)
    {
        if (pointer->childs[0]->name != "!")
        {
            OutputResult temp;
            temp.addr = pointer->printAddress;
            temp.op = "j";
            if (pointer->childs[1]->name == "<")
            {
                temp.op += "b";
            }
            else if (pointer->childs[1]->name == ">")
            {
                temp.op += "a";
            }
            else if (pointer->childs[1]->name == "==")
            {
                temp.op += "z";
            }
            else
            {
                temp.op += "nz";
            }
            temp.num1 = pointer->childs[0]->place;
            temp.num2 = pointer->childs[2]->place;
            temp.num3 = "0";
            outputResult.push_back(temp);
            OutputResult temp1;
            temp1.addr = pointer->printAddress + 1;
            temp1.op = "j";
            temp1.num1 = "__";
            temp1.num2 = "__";
            temp1.num3 = "0";
            outputResult.push_back(temp1);
        }
    }
}

void FunctionClosure(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if(pointer->childs[0]->name != "empty")
    {
        BackPatch(pointer->childs[0]->nextaddr, pointer->childs[1]->quad);
    }
}

void WhileCycle(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->printAddress == -1)
    {
        pointer->printAddress = address;
        address++;
    }
    BackPatch(pointer->childs[7]->nextaddr, pointer->childs[2]->quad);
    BackPatch(pointer->childs[3]->trueaddr, pointer->childs[6]->quad);
    pointer->nextaddr = pointer->childs[3]->falseaddr;
    if(print)
    {
        OutputResult temp;
        temp.addr = pointer->printAddress;
        temp.op = "j";
        temp.num1 = "__";
        temp.num2 = "__";
        temp.num3 = to_string(pointer->childs[2]->quad);
        outputResult.push_back(temp);
    }
}

void IfStatement(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if(pointer->childs[8]->childs[0]->name != "empty")
    {
        BackPatch(pointer->childs[2]->trueaddr, pointer->childs[5]->quad);
        BackPatch(pointer->childs[2]->falseaddr, pointer->childs[8]->childs[3]->quad);
        Merge(pointer->childs[6]->nextaddr, pointer->nextaddr);
        Merge(pointer->childs[8]->childs[0]->nextaddr, pointer->nextaddr);
        Merge(pointer->childs[8]->childs[4]->nextaddr, pointer->nextaddr);
    }
    else
    {
        BackPatch(pointer->childs[2]->trueaddr, pointer->childs[5]->quad);
        Merge(pointer->childs[2]->falseaddr, pointer->nextaddr);
        Merge(pointer->childs[6]->nextaddr, pointer->nextaddr);
    }
    
}