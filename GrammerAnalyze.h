/*
 * @Author: Leon-Francis
 * @Contact: 15290552788@163.com
 * @Date: 2020-11-30 12:16:24
 * @LastEditTime: 2020-11-30 22:51:56
 * @LastEditors: Leon-Francis
 * @Description: 文法产生式
 * @FilePath: /undefinedd:/CodingMore/CompilerExperment/GrammerAnalyze.h
 * @(C)Copyright 2019-2020, Leon-Francis
 */
#include "GrammerTree.h"
#include <string>
#include <vector>
using namespace std;

typedef struct
{
    string production = "";
    vector<vector<pair<int, string>>> result;
    void (*func)(NodePointer pointer, bool print) = NULL;
} Production;

vector<Production> productions;

void initProduction()
{
    Production program = {"Program", {{{1, "int"}, {1, "main"}, {1, "("}, {1, ")"}, {1, "{"}, {0, "ProgramBody"}, {1, "}"}}}};
    productions.push_back(program);
    Production programBody = {"ProgramBody", {{{0, "StatementClosure"}, {0, "FunctionClosure"}}}};
    productions.push_back(programBody);
    Production statementClosure = {"StatementClosure", {{{0, "StatementSen"}, {0, "StatementClosure"}}, {{0, "Empty"}}}};
    productions.push_back(statementClosure);
    Production statementSen = {"StatementSen", {{{0, "Statement"}, {1, ";"}}}};
    productions.push_back(statementSen);
    Production statement = {"Statement", {{{0, "Type"}, {0, "Variable"}, {0, "InitValue"}, {0, "VariableClosure"}}}, StatementFunc};
    productions.push_back(statement);
    Production variableClosure = {"VariableClosure", {{{0, "Variable"}, {0, "InitValue"}, {0, "VariableClosure"}}, {{0, "Empty"}}}, VariableClosureFunc};
    productions.push_back(variableClosure);
    Production type = {"Type", {{{1, "int"}, {1, "char"}, {1, "double"}, {1, "float"}, {1, "long"}, {1, "short"}}}};
    productions.push_back(type);
    Production initValue = {"InitValue", {{{1, "="}, {0, "Expression"}}, {{0, "Empty"}}}, InitValue};
    productions.push_back(initValue);
    Production expression = {"Expression", {{{0, "Factor"}, {0, "Item"}}}, Expression};
    productions.push_back(expression);
    Production factor = {"Factor", {{{0, "FactorExpression"}, {0, "FactorExpressionRecursion"}}}, };
}


