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
    Production statementClosure = {"StatementClosure", {{{0, "StatementSen"}, {0, "StatementClosure"}}, {{1, "empty"}}}};
    productions.push_back(statementClosure);
    Production statementSen = {"StatementSen", {{{0, "Statement"}, {1, ";"}}}};
    productions.push_back(statementSen);
    Production statement = {"Statement", {{{0, "Type"}, {0, "Variable"}, {0, "InitValue"}, {0, "VariableClosure"}}}, StatementFunc};
    productions.push_back(statement);
    Production variableClosure = {"VariableClosure", {{{0, "Variable"}, {0, "InitValue"}, {0, "VariableClosure"}}, {{1, "empty"}}}, VariableClosureFunc};
    productions.push_back(variableClosure);
    Production type = {"Type", {{{1, "int"}, {1, "char"}, {1, "double"}, {1, "float"}, {1, "long"}, {1, "short"}}}};
    productions.push_back(type);
    Production variable = {"Variable", {{{1, "id"}}}, VariableFunc};
    productions.push_back(variable);
    Production initValue = {"InitValue", {{{1, "="}, {0, "Expression"}}, {{1, "empty"}}}, InitValueFunc};
    productions.push_back(initValue);
    Production expression = {"Expression", {{{0, "Factor"}, {0, "Item"}}}, ExpressionFunc};
    productions.push_back(expression);
    Production factor = {"Factor", {{{0, "FactorExpression"}, {0, "FactorExpressionRecursion"}}}, FactorFunc};
    productions.push_back(factor);
    Production factorExpression = {"FactorExpression", {{{1, "("}, {0, "Expression"}, {1, ")"}}, {{0, "Variable"}}, {{0, "Digit"}}}, FactorExpressionFunc};
    productions.push_back(factorExpression);
    Production digit = {"Digit", {{{1, "digit"}}}, DigitFunc};
    productions.push_back(digit);
    Production factorExpressionRecursion = { "FactorExpressionRecursion", {{{1, "*"}, {0, "FactorExpression"}, {0, "FactorExpressionRecursion"}}, {{1, "/"}, {0, "FactorExpression"}, {0, "FactorExpressionRecursion"}}, {{1, "empty"}}}, FactorExpressionRecursionFunc};
    productions.push_back(factorExpressionRecursion);
    Production item = {"Item", {{{1, "+"}, {0, "Factor"}, {0, "Item"}}, {{1, "-"}, {0, "Factor"}, {0, "Item"}}, {{1, "empty"}}}, ItemFunc};
    productions.push_back(item);
    Production functionClosure = {"FunctionClosure", {{{0, "AssignmentStatement"}, {0, "M"}, {0, "FunctionClosure"}}, {{0, "WhileCycle"}, {0, "M"}, {0, "FunctionClosure"}}, {{0, "IfStatement"}, {0, "M"}, {0, "FunctionClosure"}}, {{1, "empty"}}}, FunctionClosure};
    productions.push_back(functionClosure);
    Production assignmentStatement = {"AssignmentStatement", {{{0, "Variable"}, {1, "="}, {0, "Expression"}, {1, ";"}}}, AssignmentStatement};
    productions.push_back(assignmentStatement);
    Production boolStatement = {"BoolStatement", {{{0, "BoolItem"}, {0, "BoolStatementClosure"}}}, BoolStatement};
    productions.push_back(boolStatement);
    Production m = {"M", {{{1, "empty"}}}, M};
    productions.push_back(m);
    Production boolStatementClosure = {"BoolStatementClosure", {{{1, "||"}, {0, "M"}, {0, "BoolItem"}, {0, "BoolStatementClosure"}}, {{1, "empty"}}}, BoolStatementClosure};
    productions.push_back(boolStatementClosure);
    Production boolItem = {"BoolItem", {{{0, "BoolFactor"}, {0, "BoolItemClosure"}}}, BoolItem};
    productions.push_back(boolItem);
    Production boolItemClosure = {"BoolItemClosure", {{{1, "&&"}, {0, "M"}, {0, "BoolFactor"}, {0, "BoolItemClosure"}}, {{1, "empty"}}}, BoolItemClosure};
    productions.push_back(boolItemClosure);
    Production boolFactor = {"BoolFactor", {{{0, "Expression"}, {0, "BoolSymbol"}, {0, "Expression"}}, {{1, "!"}, {0, "BoolFactor"}}}, BoolFactor};
    productions.push_back(boolFactor);
    Production boolSymbol = {"BoolSymbol", {{{1, "<"}}, {{1, ">"}}, {{1, "=="}}, {{1, "!="}}}};
    productions.push_back(boolSymbol);
    Production whileCycle = {"WhileCycle", {{{1, "while"}, {1, "("}, {0, "M"}, {0, "BoolStatement"}, {1, ")"}, {1, "{"}, {0, "M"}, {0, "ProgramBody"}, {1, "}"}}}, WhileCycle};
    productions.push_back(whileCycle);
    Production ifStatement = {"IfStatement", {{{1, "if"}, {1, "("}, {0, "BoolStatement"}, {1, ")"}, {1, "{"}, {0, "M"}, {0, "ProgramBody"}, {1, "}"}, {0, "ElseStatement"}}}, IfStatement};
    productions.push_back(ifStatement);
    Production elseStatement = {"ElseStatement", {{{0, "N"}, {1, "else"}, {1, "{"}, {0, "M"}, {0, "ProgramBody"}, {1, "}"}}, {{1, "empty"}}}};
    productions.push_back(elseStatement);
}


