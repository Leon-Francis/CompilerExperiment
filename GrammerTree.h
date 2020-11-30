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
int tempnum = 0;

typedef struct
{
    int addr;
    string output;
} OutputResult;
vector<OutputResult> outputResult;
int address = 100;

typedef struct Node
{
    //属性
    string name = "";
    string place = "";
    int symbleIndex = -1;
    bool complete = false;
    //指针
    struct Node *parents;
    vector<struct Node *> childs;

} * NodePointer;

NodePointer root;

string newTemp()
{
    return "T" + to_string(tempnum++);
}

void StatementFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[1]->place != "")
    {
        ;
    }
    else
    {
        pointer->complete = false;
    }

    if (print)
    {
        if (pointer->childs[2]->place != "")
        {
            OutputResult temp;
            temp.addr = address;
            temp.output = "(:=, " + pointer->childs[2]->place + ", _, " + pointer->childs[1]->place + ")\n";
            outputResult.push_back(temp);
            address++;
        }
    }
}

void VariableClosureFunc(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[0]->place != "")
    {
        ;
    }
    else
    {
        pointer->complete = false;
    }

    if (print)
    {
        if (pointer->childs[1]->place != "")
        {
            OutputResult temp;
            temp.addr = address;
            temp.output = "(:=, " + pointer->childs[1]->place + ", _, " + pointer->childs[0]->place + ")\n";
            outputResult.push_back(temp);
            address++;
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
            temp.addr = address;
            temp.output = "(" + pointer->childs[1]->childs[0]->name + ", " + pointer->childs[0]->place + ", " + pointer->childs[1]->place + ", " + pointer->place + ")\n";
            outputResult.push_back(temp);
            address++;
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
            temp.addr = address;
            temp.output = "(" + pointer->childs[1]->childs[0]->name + ", " + pointer->childs[0]->place + ", " + pointer->childs[1]->place + ", " + pointer->place + ")\n";
            outputResult.push_back(temp);
            address++;
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
            temp.addr = address;
            temp.output = "(" + pointer->childs[2]->childs[0]->name + ", " + pointer->childs[1]->place + ", " + pointer->childs[2]->place + ", " + pointer->place + ")\n";
            outputResult.push_back(temp);
            address++;
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
            temp.addr = address;
            temp.output = "(" + pointer->childs[2]->childs[0]->name + ", " + pointer->childs[1]->place + ", " + pointer->childs[2]->place + ", " + pointer->place + ")\n";
            outputResult.push_back(temp);
            address++;
        }
    }
}

void AssignmentStatement(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if(pointer->childs[0]->place != "" && pointer->childs[2]->place != "")
    {

    }
    else
    {
        pointer->complete = false;
    }
    if(print)
    {
        OutputResult temp;
        temp.addr = address;
        temp.output = "(:=, " + pointer->childs[2]->place + ", _ , " + pointer->childs[0]->place + ")\n";
        outputResult.push_back(temp);
        address++;
    }
}