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

string outputResult = "";

typedef struct Node
{
    //属性
    string name = "";
    int code = -1;
    string place = "";
    int type = -1;
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

    if (print == true)
    {
        if (pointer->childs[2]->place != "")
        {
            outputResult += "(:=, " + pointer->childs[1]->place + ", _, " + pointer->childs[0]->place + ")\n";
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

    if (print == true)
    {
    }
}

void InitValue(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[0]->name == "Empty")
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

void Expression(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[0]->place != "")
    {
        if (pointer->childs[1]->childs[0]->name != "Empty")
        {
            if (pointer->childs[1]->place != "")
            {
                pointer->place = newTemp();
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
    if (print == true)
    {
        if (pointer->childs[1]->childs[0]->name != "Empty")
        {
            outputResult += "(" + pointer->childs[1]->childs[0]->name + ", " + pointer->childs[0]->place + ", " + pointer->childs[1]->place + ", " + pointer->place + ")\n";
        }
    }
}

void Factor(NodePointer pointer, bool print = false)
{
    pointer->complete = true;
    if (pointer->childs[0]->place != "")
    {
        if (pointer->childs[1]->childs[0]->name != "Empty")
        {
            if (pointer->childs[1]->place != "")
            {
                pointer->place = newTemp();
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
    if (print == true)
    {
        if (pointer->childs[1]->childs[0]->name != "Empty")
        {
            outputResult += "(" + pointer->childs[1]->childs[0]->name + ", " + pointer->childs[0]->place + ", " + pointer->childs[1]->place + ", " + pointer->place + ")\n";
        }
    }
}