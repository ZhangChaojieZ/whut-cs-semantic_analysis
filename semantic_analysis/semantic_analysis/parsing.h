#pragma once
#include<iostream>
#include<string>
#include<stack>
#include<vector>
//#include"data_structure.h"
#include"lexical_analysis.h"

using namespace std;

// ��ʼ��
void init();
// �ж�ջ��Ԫ���Ƿ���Ҫִ�еĶ����ı��
bool chIsActionNum(char ch);
// ����������ŵ����ͣ���������ŵ�ֵ������Ӧ�ķ��ս��
void getValueByType_currNode(inputStringNode currentNode);
// ����һ���µĽ����������ʾ��Ԫʽ�Ľ��
string newtemp();
// ����
void backpatch(vector<tac> true_false_List, int index);
// ִ����Ӧ�Ķ���
void performActionNum(char topch);
// �����Ԫʽ
void printTac();
// �﷨��������
bool parser(vector<inputStringNode> inputStr);