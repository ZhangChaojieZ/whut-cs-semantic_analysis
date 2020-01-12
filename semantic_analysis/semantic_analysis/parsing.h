#pragma once
#include<iostream>
#include<string>
#include<stack>
#include<vector>
//#include"data_structure.h"
#include"lexical_analysis.h"

using namespace std;

// 初始化
void init();
// 判断栈顶元素是否是要执行的动作的标号
bool chIsActionNum(char ch);
// 根据输入符号的类型，将输入符号的值赋给对应的非终结符
void getValueByType_currNode(inputStringNode currentNode);
// 返回一个新的结果变量，表示四元式的结果
string newtemp();
// 回填
void backpatch(vector<tac> true_false_List, int index);
// 执行相应的动作
void performActionNum(char topch);
// 输出四元式
void printTac();
// 语法分析程序
bool parser(vector<inputStringNode> inputStr);