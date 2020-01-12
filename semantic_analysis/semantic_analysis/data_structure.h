#pragma once
#include<iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;

#define CHKEYLEFTNUM 13
#define CHKEYRIGHTNUM 10
#define CHOPERNUM 11
#define CHBAUNNUM 7

// ���Ͷ�Ӧ��1-��ʶ����2-������3-�ؼ��֣�4-�������5-���,-1��ʾ������ȡ��һ���ַ���0��ʾ����
#define READ -1
#define IDENT 1
#define CONSTANT 2
#define KEYWORD 3
#define OPERATOR 4
#define BAUNDARY 5
#define ERROR 0

static char chKeyWord[CHKEYLEFTNUM][CHKEYRIGHTNUM] = { "const", "var","procedure","begin","end","odd","if","then","call","while","do","read","write" };
static char chOperatorWord[CHOPERNUM][CHOPERNUM] = { "+","-","*","/","=","#","<",">",":=",">=","<=" };	// '<=',,'>='
static char chBaundaryWord[CHBAUNNUM][CHBAUNNUM] = { "(",")",",",";",".","{","}" };
static char chOperator[] = { '+','-','*','/','<','>','=',':','#' };

struct inputStringNode
{
	char type;			// ��Ӧ���ķ�����
	string value;		// �����ֵ����Դ�����е�ֵ��

};

struct tac
{
	int lable;			// ��Ԫʽ��ţ��������
	char op;			// ������
	string par1;		// ������1
	string par2;		// ������2
	string result;		// ������
};