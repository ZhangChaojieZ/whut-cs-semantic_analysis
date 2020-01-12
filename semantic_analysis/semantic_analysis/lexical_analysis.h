#pragma once
#include<iostream>
#include<string>
#include<map>
#include<vector>
#include"data_structure.h"
using namespace std;

//	保留字、标识符、数字的词法分析程序
//int KeyIdentNumAnalysis(string strKeyNumIdWord, string& strTemp, map<string, int> &outMap);
int KeyIdentNumAnalysis(string strKeyNumIdWord, string &strTemp, vector<inputStringNode> &inputStr);
// 关键字词法分析
int KeywordAnalysis(string strKeyword);
// 标识符词法分析
int IdentAnalysis(string strIdent);
// 数字词法分析
int NumberAnalysis(string strNum);
// 运算符词法分析
int OperatorAnalysis(string strOperator);
// 界限符词法分析
int BaundaryAnlysis(string strBaundary);
// 判断是否是运算符
bool IsOperator(char ch);
// 用于判断将操作符加入到语法分析的输入串中
void addOpter_inputString(vector<inputStringNode> &inputStr,string  strOperator);
// 用于判断将界符加入到语法分析的输入串中
void addBaun_inputString(vector<inputStringNode> &inputStr, string  strBaun);
// 词法分析程序
//int LexAnalysis(int &wordIndex, char &ch, string &strWord, string &strOperator, string &strBaun, string &strTemp, map<string,int> &outMap)
int LexAnalysis(int &wordIndex, char &ch, string &strWord, string &strOperator, string &strBaun, string &strTemp, vector<inputStringNode> &inputStr);