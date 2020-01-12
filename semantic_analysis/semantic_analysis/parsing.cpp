#include<iostream>
#include<string>
#include<map>
#include<iterator>
#include<stack>
#include<iomanip>
#include<algorithm>
#include"parsing.h"

using namespace std;

map<char, map<char, string>> LL_table;				// LL1预测分析表
map<char, map<char, vector<int>>> LL_actionNum;		// 动作表
tac currentTac;										// 当前即将要加入四元式组中的四元式
vector<tac> tacVector;								// 四元式组，存储生成的四元式
vector<tac> Otruelist;								// 真链
vector<tac> Ofalselist;								// 假链
int tacIndex = 0;									// 四元式索引
int resultNum = 0;

// ***有关属性的全局变量***
string Bvalue;
string Cvalue;
string Dvalue;
string Mvalue;
string Evalue;
string Nvalue;
string Hvalue;
string Ivalue;
string Jvalue;
string Ovalue;
string C0value;	// 用于O->CJC,C零表示产生式右部的前一个C
string Mi;
string Ms;
string M1s;
string Ni;
string Ns;
string N1s;
int M1gotostm;
int M2gotostm;
string gvalue;	// 记录赋值语句的g的值
// ***------------------***

void init() {

	/* a~e和i为自底向上执行的动作，其余为自顶向下执行的动作，
	由于要在下推栈中加入数字，但0~9不够使用，所以采用文法中没有使用到的字符进行代替
	在写代码的过程中不断地修改bug，所以字母的顺序有些不对
	不改回正确的顺序是因为已经写过了每个字母对应的动作，在进行更改，过于麻烦
	主要的原因是考试太多，时间太紧了
	*/
	LL_table['A']['w'] = "w0(P)1{B;}a";
	LL_table['B']['g'] = "gj=C2";		// j为后续添加，所以这里放了j
	LL_table['C']['f'] = "D3Mb";
	LL_table['C']['g'] = "D3Mb";
	LL_table['C']['('] = "D3Mb";
	LL_table['M'][')'] = "5";
	LL_table['M'][';'] = "5";
	LL_table['M']['+'] = "HD4Mc";
	LL_table['M']['-'] = "HD4Mc";
	LL_table['M']['>'] = "5";
	LL_table['M']['<'] = "5";
	LL_table['M']['m'] = "5";
	LL_table['M']['n'] = "5";
	LL_table['D']['f'] = "E6Nd";
	LL_table['D']['g'] = "E6Nd";
	LL_table['D']['('] = "E6Nd";
	LL_table['N'][';'] = "8";
	LL_table['N']['+'] = "8";
	LL_table['N']['-'] = "8";
	LL_table['N']['*'] = "IE7Ne";
	LL_table['N']['/'] = "IE7Ne";
	LL_table['N']['#'] = "8";
	LL_table['N']['>'] = "8";
	LL_table['N']['<'] = "8";
	LL_table['N']['m'] = "8";
	LL_table['N']['n'] = "8";
	LL_table['N'][')'] = "8";
	LL_table['E']['f'] = "f";
	LL_table['E']['g'] = "g";
	LL_table['E']['('] = "(C)9";
	LL_table['H']['+'] = "+";
	LL_table['H']['-'] = "-";
	LL_table['I']['*'] = "*";
	LL_table['I']['/'] = "/";
	LL_table['J']['>'] = ">";
	LL_table['J']['<'] = "<";
	LL_table['J']['m'] = "m";			// >=号用m代替
	LL_table['J']['n'] = "n";			// <=号用n代替
	LL_table['P']['f'] = "ChJCi";
	LL_table['P']['g'] = "ChJCi";
	LL_table['P']['('] = "ChJCi";
	// ****** ----------------- ******

}

bool chIsActionNum(char ch) {
	if ((ch >= '0' && ch <= '9') || (ch >= 'a'&& ch <= 'e') || ch == 'h' || ch == 'i' || ch == 'j') {
		return true;
	}
	return false;
}

void getValueByType_currNode(inputStringNode currentNode) {
	char ch = currentNode.type;
	// 如果输入串的类型是以下中的一个，则进行赋值
	switch (ch)
	{
	case 'f':case 'g':
		Evalue = currentNode.value;
		//gvalue = currentNode.value;
		Evalue = currentNode.value;
		break;
	case '+':case '-':
		Hvalue = currentNode.value;
		break;
	case '*':case '/':
		Ivalue = currentNode.value;
		break;
	case '>':case '<':case 'm':case 'n':
		Jvalue = currentNode.value;
		break;
	default:
		break;
	}

}

string newtemp() {
	string temp = "T" + to_string(resultNum);
	resultNum++;
	return temp;
}

void backpatch(vector<tac> true_false_List, int index) {
	for (unsigned int i = 0; i < true_false_List.size(); i++) {
		for (unsigned int j = 0; j < tacVector.size(); j++) {
			if (true_false_List[i].lable == tacVector[j].lable) {
				tacVector[j].result = to_string(index);
			}
		}

	}
}

void performActionNum(char topch) {
	switch (topch) {
	case '0':M1gotostm = tacIndex; break;
	case '1':M2gotostm = tacIndex; break;
		// 生成四元式
	case '2':
		Bvalue = Cvalue;
		currentTac.lable = tacIndex;
		currentTac.op = '=';
		currentTac.par1 = Cvalue;
		currentTac.par2 = "";
		currentTac.result = gvalue;
		tacVector.push_back(currentTac);
		tacIndex++;
		//Bvalue = currentTac.result;
		break;
	case '3':Mi = Dvalue; break;
		// 生成四元式
	case '4':
		currentTac.lable = tacIndex;
		currentTac.op = Hvalue.at(0);
		currentTac.par1 = Mi;
		currentTac.par2 = Dvalue;
		currentTac.result = newtemp();
		tacVector.push_back(currentTac);
		tacIndex++;
		Mi = currentTac.result;
		break;
	case '5':Ms = Mi; break;
	case '6':Ni = Evalue; break;
		// 生成四元式
	case '7':
		currentTac.lable = tacIndex;
		currentTac.op = Ivalue.at(0);
		currentTac.par1 = Ni;
		currentTac.par2 = Evalue;
		currentTac.result = newtemp();
		tacVector.push_back(currentTac);
		tacIndex++;
		Ni = currentTac.result;
		break;
	case '8':Ns = Ni; break;
	case '9':Evalue = Cvalue; break;
	case 'a':
		// 执行完循环体跳转到while判断的条件位置，接着进行判断是否继续循环
		currentTac.lable = tacIndex;
		currentTac.op = 'J';
		currentTac.par1 = "";
		currentTac.par2 = "";
		currentTac.result = to_string(M1gotostm);
		tacVector.push_back(currentTac);
		tacIndex++;

		// 整个while语句执行完之后的下一步
		currentTac.lable = tacIndex;
		currentTac.op = ' ';
		currentTac.par1 = "";
		currentTac.par2 = "";
		currentTac.result = "";
		tacVector.push_back(currentTac);
		tacIndex++;

		// 回填
		backpatch(Otruelist, M2gotostm);
		backpatch(Ofalselist, tacIndex - 1);
	case 'b':Cvalue = Ms; break;
	case 'c':Ms = Ms; break;
	case 'd':Dvalue = Ns; break;
	case 'e':Ns = Ns; break;
	case 'h':
		C0value = Cvalue;
		break;
		// 生成四元式
	case 'i':
		currentTac.lable = tacIndex;
		currentTac.op = Jvalue.at(0);
		currentTac.par1 = C0value;
		currentTac.par2 = Cvalue;
		currentTac.result = newtemp();
		tacVector.push_back(currentTac);
		tacIndex++;
		Ovalue = currentTac.result;

		// 判断为真,添加跳转语句
		currentTac.lable = tacIndex;
		currentTac.op = 'T';
		currentTac.par1 = currentTac.result;
		currentTac.par2 = "";
		tacVector.push_back(currentTac);
		tacIndex++;

		// 添加到真链
		Otruelist.push_back(currentTac);

		// 判断为假，添加跳转语句
		currentTac.lable = tacIndex;
		currentTac.op = 'F';
		currentTac.par1 = currentTac.result;
		currentTac.par2 = "";
		tacVector.push_back(currentTac);
		tacIndex++;

		// 添加到假链
		Ofalselist.push_back(currentTac);
		break;
	case 'j':gvalue = Evalue; break;
	}
}

void printTac() {
	cout << endl << "生成的四元式如下：" << endl;
	for (unsigned int i = 0; i < tacVector.size(); i++) {
		cout << tacVector[i].lable << "\t";
		if (tacVector[i].op == 'T' || tacVector[i].op == 'F') {
			cout << "Jump" << tacVector[i].op << "\t" << tacVector[i].par1
				<< "\t" << tacVector[i].par2 << "\t" << tacVector[i].result << endl;
		}
		else if (tacVector[i].op == 'j') {
			cout << "Jump" << "\t" << tacVector[i].par1
				<< "\t" << tacVector[i].par2 << "\t" << tacVector[i].result << endl;
		}
		else if (tacVector[i].op == 'm') {
			cout << ">=" << "\t" << tacVector[i].par1
				<< "\t" << tacVector[i].par2 << "\t" << tacVector[i].result << endl;
		}
		else if (tacVector[i].op == 'n') {
			cout << "<=" << "\t" << tacVector[i].par1
				<< "\t" << tacVector[i].par2 << "\t" << tacVector[i].result << endl;
		}
		else {
			cout << tacVector[i].op << "\t" << tacVector[i].par1
				<< "\t" << tacVector[i].par2 << "\t" << tacVector[i].result << endl;
		}
	}
}

bool parser(vector <inputStringNode> inputStr) {
	init();							// 进行初始化，初始化预测分析表
	stack<int> analysis_stack;		// 分析栈
	char inputCh;					// 表示每次输入的的符号
	char topCh;						// 分析栈栈顶元素
	int inputStrIndex = 0;			// 遍历访问inputStr，初始值为0
	string strProductionRight;		// 产生式的右部

	analysis_stack.push('#');
	analysis_stack.push('A');
	map<char, string>::iterator iter;

	//********附送内容，用于输出预测分析法的推导过程
	string analysis_str("#A");	// 下推栈里面的内容
	string input_str;		// 输入流的内容
	int input_strIndex = 0;		// 遍历访问input_str，初始值为0
	int step = 0;

	for (unsigned int m = 0; m < inputStr.size(); m++) {
		input_str.push_back(inputStr[m].type);
	}
	//********附送内容

	cout << setiosflags(ios::left) << setw(3) << "   " << "\t" << setw(30) << "--下推栈--" << "\t" << resetiosflags(ios::left);
	cout << setiosflags(ios::right) << setw(30) << "--输入串--" << resetiosflags(ios::right) << "\t";
	//cout << setiosflags(ios::left) << setw(20) << "--推导步/语义动作--" << resetiosflags(ios::left) << endl;
	cout << "\t  --推导步/语义动作--" << endl;

	while (true) {

		inputCh = inputStr[inputStrIndex].type;			// 输入符号
		topCh = analysis_stack.top();					// 得到分析栈栈顶元素
		//cout << inputStr[inputStrIndex].type<<"\t"<<topCh << endl;

		iter = LL_table[topCh].find(inputCh);			// 用于判断预测分析表中是否存在对应关系
		if (chIsActionNum(topCh)) {
			// 输出分析过程
			cout << setiosflags(ios::left) << setw(3) << step++ << "\t" << setw(30) << analysis_str << "\t" << resetiosflags(ios::left);
			cout << setiosflags(ios::right) << setw(32) << input_str.substr(input_strIndex) << resetiosflags(ios::right) << "\t";
			cout << "\t" << "执行" << topCh << endl;
			analysis_str.erase(analysis_str.size() - 1);
			//*************

			// 执行相应的动作
			performActionNum(topCh);
			analysis_stack.pop();
		}
		else if (topCh == inputCh) {	// 语法分析成功结束标志
			if (topCh == '#') {
				// 输出分析过程
				cout << setiosflags(ios::left) << setw(3) << step++ << "\t" << setw(30) << analysis_str << "\t" << resetiosflags(ios::left);
				cout << setiosflags(ios::right) << setw(32) << input_str.substr(input_strIndex) << resetiosflags(ios::right) << "\t";
				cout << "\t" << "成功返回" << endl;
				//*************

				cout << endl << "语法分析正确，进行语义分析" << endl;
				printTac();
				return true;
			}
			// 输出分析过程
			cout << setiosflags(ios::left) << setw(3) << step++ << "\t" << setw(30) << analysis_str << "\t" << resetiosflags(ios::left);
			cout << setiosflags(ios::right) << setw(32) << input_str.substr(input_strIndex) << resetiosflags(ios::right) << "\t";
			cout << "\t" << "匹配当前字符串" << endl;

			input_strIndex++;	// 位置后移一位，用于输出输入串的内容
			analysis_str.erase(analysis_str.size() - 1);
			//*************

			getValueByType_currNode(inputStr[inputStrIndex]);	// 传递属性给终结符
			// 输入符号与栈顶符号相同，则匹配
			analysis_stack.pop();
			inputStrIndex++;
			continue;
		}
		// 如果栈顶符号与输入符号不匹配，栈顶符号出栈，查找是否存在可用的产生式，如果有，逆序产生式左部逆序进栈；否则报错
		else if (iter != LL_table[topCh].end()) {
			strProductionRight = LL_table[topCh][inputCh];

			// 输出分析过程
			cout << setiosflags(ios::left) << setw(3) << step++ << "\t" << setw(30) << analysis_str << "\t" << resetiosflags(ios::left);
			cout << setiosflags(ios::right) << setw(32) << input_str.substr(input_strIndex) << resetiosflags(ios::right) << "\t";
			cout << "\t" << topCh << "->" << strProductionRight << endl;
			analysis_str.erase(analysis_str.size() - 1);	// 字符串做同样动作,删除最后一个字符
			//*************

			reverse(strProductionRight.begin(), strProductionRight.end());	// 逆序准备入栈
			// 栈顶元素出栈，产生式右部逆序入栈
			analysis_stack.pop();

			
			for (unsigned int i = 0; i < strProductionRight.length(); i++) {
				char c = strProductionRight.at(i);
				analysis_stack.push(strProductionRight.at(i));
				analysis_str.push_back(strProductionRight.at(i));
			}
		}
		else {
			cout << inputCh << "输入错误！" << endl;
			return false;
		}
	}
	return true;
}