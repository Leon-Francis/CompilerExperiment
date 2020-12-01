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
#include "GrammerAnalyze.h"
#ifndef KEYWORDNUM
#include "Tokenize.h"
#endif
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

void ReversePushStack(stack<NodePointer> &tokenStack, NodePointer pointer)
{
    for (int t = pointer->childs.size() - 1; t >= 0; t--)
    {
        tokenStack.push(pointer->childs[t]);
    }
}

NodePointer CreateTree(vector<WordToken> wordToken)
{
    //根节点
    NodePointer root = new Node;
    root->name = "Program";
    NodePointer p = root;
    stack<NodePointer> tokenStack;
    tokenStack.push(root);
    int index = 0;
    bool result = true;
    while (index < wordToken.size())
    {
        for (int i = 0; i < productions.size(); i++)
        {
            if (tokenStack.top()->name == productions[i].production)
            {
                tokenStack.pop();
                //判断是否有多个产生式
                if (productions[i].result.size() > 1)
                {
                    int firstIndex = 0;
                    bool match = false;
                    for (firstIndex = 0; firstIndex < productions[i].first.size(); firstIndex++)
                    {
                        for (int j = 0; j < productions[i].first[firstIndex].size(); j++)
                        {
                            if (wordToken[index].name == productions[i].first[firstIndex][j] || (wordToken[index].code == 81 && productions[i].first[firstIndex][j] == "id") || ((wordToken[index].code == 82 || wordToken[index].code == 83) && productions[i].first[firstIndex][j] == "digit"))
                            {
                                match = true;
                                break;
                            }
                        }
                        if (match)
                        {
                            break;
                        }
                    }
                    for (int j = 0; j < productions[i].result[firstIndex].size(); j++)
                    {
                        NodePointer temp = new Node;
                        temp->name = productions[i].result[firstIndex][j].second;
                        temp->type = productions[i].result[firstIndex][j].first;
                        p->childs.push_back(temp);
                        temp->parents = p;
                    }
                }
                else
                {
                    for (int j = 0; j < productions[i].result[0].size(); j++)
                    {
                        NodePointer temp = new Node;
                        temp->name = productions[i].result[0][j].second;
                        temp->type = productions[i].result[0][j].first;
                        p->childs.push_back(temp);
                        temp->parents = p;
                    }
                }
                ReversePushStack(tokenStack, p);
                break;
            }
        }
        while (!tokenStack.empty() && tokenStack.top()->type == 1)
        {
            if (tokenStack.top()->name == wordToken[index].name || (wordToken[index].code == 81 && tokenStack.top()->name == "id") || ((wordToken[index].code == 82 || wordToken[index].code == 83) && tokenStack.top()->name == "digit"))
            {
                tokenStack.pop();
                index++;
            }
            else if (tokenStack.top()->name == "empty")
            {
                tokenStack.pop();
            }
            else
            {
                cout << "Production Error" << endl;
                return NULL;
            }
        }
        if (!tokenStack.empty())
        {
            p = tokenStack.top();
        }
    }
    if (tokenStack.empty())
    {
        cout << "Create grammer tree complete!" << endl;
        return root;
    }
    else
    {
        cout << "Create grammer tree Error" << endl;
        return NULL;
    }
}
