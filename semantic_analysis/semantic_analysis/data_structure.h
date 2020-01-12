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

// 类型对应，1-标识符，2-常数，3-关键字，4-运算符，5-界符,-1表示继续读取下一个字符，0表示错误
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
	char type;			// 对应的文法符号
	string value;		// 本身的值（在源程序中的值）

};

struct tac
{
	int lable;			// 四元式表号，方便查找
	char op;			// 操作符
	string par1;		// 操作数1
	string par2;		// 操作数2
	string result;		// 运算结果
};