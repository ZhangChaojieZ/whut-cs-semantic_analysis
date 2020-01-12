#include<iostream>
#include<string>
#include<map>
#include<iterator>
#include<stack>
#include<iomanip>
#include<algorithm>
#include"parsing.h"

using namespace std;

map<char, map<char, string>> LL_table;				// LL1Ԥ�������
map<char, map<char, vector<int>>> LL_actionNum;		// ������
tac currentTac;										// ��ǰ����Ҫ������Ԫʽ���е���Ԫʽ
vector<tac> tacVector;								// ��Ԫʽ�飬�洢���ɵ���Ԫʽ
vector<tac> Otruelist;								// ����
vector<tac> Ofalselist;								// ����
int tacIndex = 0;									// ��Ԫʽ����
int resultNum = 0;

// ***�й����Ե�ȫ�ֱ���***
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
string C0value;	// ����O->CJC,C���ʾ����ʽ�Ҳ���ǰһ��C
string Mi;
string Ms;
string M1s;
string Ni;
string Ns;
string N1s;
int M1gotostm;
int M2gotostm;
string gvalue;	// ��¼��ֵ����g��ֵ
// ***------------------***

void init() {

	/* a~e��iΪ�Ե�����ִ�еĶ���������Ϊ�Զ�����ִ�еĶ�����
	����Ҫ������ջ�м������֣���0~9����ʹ�ã����Բ����ķ���û��ʹ�õ����ַ����д���
	��д����Ĺ����в��ϵ��޸�bug��������ĸ��˳����Щ����
	���Ļ���ȷ��˳������Ϊ�Ѿ�д����ÿ����ĸ��Ӧ�Ķ������ڽ��и��ģ������鷳
	��Ҫ��ԭ���ǿ���̫�࣬ʱ��̫����
	*/
	LL_table['A']['w'] = "w0(P)1{B;}a";
	LL_table['B']['g'] = "gj=C2";		// jΪ������ӣ������������j
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
	LL_table['J']['m'] = "m";			// >=����m����
	LL_table['J']['n'] = "n";			// <=����n����
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
	// ������봮�������������е�һ��������и�ֵ
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
		// ������Ԫʽ
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
		// ������Ԫʽ
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
		// ������Ԫʽ
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
		// ִ����ѭ������ת��while�жϵ�����λ�ã����Ž����ж��Ƿ����ѭ��
		currentTac.lable = tacIndex;
		currentTac.op = 'J';
		currentTac.par1 = "";
		currentTac.par2 = "";
		currentTac.result = to_string(M1gotostm);
		tacVector.push_back(currentTac);
		tacIndex++;

		// ����while���ִ����֮�����һ��
		currentTac.lable = tacIndex;
		currentTac.op = ' ';
		currentTac.par1 = "";
		currentTac.par2 = "";
		currentTac.result = "";
		tacVector.push_back(currentTac);
		tacIndex++;

		// ����
		backpatch(Otruelist, M2gotostm);
		backpatch(Ofalselist, tacIndex - 1);
	case 'b':Cvalue = Ms; break;
	case 'c':Ms = Ms; break;
	case 'd':Dvalue = Ns; break;
	case 'e':Ns = Ns; break;
	case 'h':
		C0value = Cvalue;
		break;
		// ������Ԫʽ
	case 'i':
		currentTac.lable = tacIndex;
		currentTac.op = Jvalue.at(0);
		currentTac.par1 = C0value;
		currentTac.par2 = Cvalue;
		currentTac.result = newtemp();
		tacVector.push_back(currentTac);
		tacIndex++;
		Ovalue = currentTac.result;

		// �ж�Ϊ��,�����ת���
		currentTac.lable = tacIndex;
		currentTac.op = 'T';
		currentTac.par1 = currentTac.result;
		currentTac.par2 = "";
		tacVector.push_back(currentTac);
		tacIndex++;

		// ��ӵ�����
		Otruelist.push_back(currentTac);

		// �ж�Ϊ�٣������ת���
		currentTac.lable = tacIndex;
		currentTac.op = 'F';
		currentTac.par1 = currentTac.result;
		currentTac.par2 = "";
		tacVector.push_back(currentTac);
		tacIndex++;

		// ��ӵ�����
		Ofalselist.push_back(currentTac);
		break;
	case 'j':gvalue = Evalue; break;
	}
}

void printTac() {
	cout << endl << "���ɵ���Ԫʽ���£�" << endl;
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
	init();							// ���г�ʼ������ʼ��Ԥ�������
	stack<int> analysis_stack;		// ����ջ
	char inputCh;					// ��ʾÿ������ĵķ���
	char topCh;						// ����ջջ��Ԫ��
	int inputStrIndex = 0;			// ��������inputStr����ʼֵΪ0
	string strProductionRight;		// ����ʽ���Ҳ�

	analysis_stack.push('#');
	analysis_stack.push('A');
	map<char, string>::iterator iter;

	//********�������ݣ��������Ԥ����������Ƶ�����
	string analysis_str("#A");	// ����ջ���������
	string input_str;		// ������������
	int input_strIndex = 0;		// ��������input_str����ʼֵΪ0
	int step = 0;

	for (unsigned int m = 0; m < inputStr.size(); m++) {
		input_str.push_back(inputStr[m].type);
	}
	//********��������

	cout << setiosflags(ios::left) << setw(3) << "   " << "\t" << setw(30) << "--����ջ--" << "\t" << resetiosflags(ios::left);
	cout << setiosflags(ios::right) << setw(30) << "--���봮--" << resetiosflags(ios::right) << "\t";
	//cout << setiosflags(ios::left) << setw(20) << "--�Ƶ���/���嶯��--" << resetiosflags(ios::left) << endl;
	cout << "\t  --�Ƶ���/���嶯��--" << endl;

	while (true) {

		inputCh = inputStr[inputStrIndex].type;			// �������
		topCh = analysis_stack.top();					// �õ�����ջջ��Ԫ��
		//cout << inputStr[inputStrIndex].type<<"\t"<<topCh << endl;

		iter = LL_table[topCh].find(inputCh);			// �����ж�Ԥ����������Ƿ���ڶ�Ӧ��ϵ
		if (chIsActionNum(topCh)) {
			// �����������
			cout << setiosflags(ios::left) << setw(3) << step++ << "\t" << setw(30) << analysis_str << "\t" << resetiosflags(ios::left);
			cout << setiosflags(ios::right) << setw(32) << input_str.substr(input_strIndex) << resetiosflags(ios::right) << "\t";
			cout << "\t" << "ִ��" << topCh << endl;
			analysis_str.erase(analysis_str.size() - 1);
			//*************

			// ִ����Ӧ�Ķ���
			performActionNum(topCh);
			analysis_stack.pop();
		}
		else if (topCh == inputCh) {	// �﷨�����ɹ�������־
			if (topCh == '#') {
				// �����������
				cout << setiosflags(ios::left) << setw(3) << step++ << "\t" << setw(30) << analysis_str << "\t" << resetiosflags(ios::left);
				cout << setiosflags(ios::right) << setw(32) << input_str.substr(input_strIndex) << resetiosflags(ios::right) << "\t";
				cout << "\t" << "�ɹ�����" << endl;
				//*************

				cout << endl << "�﷨������ȷ�������������" << endl;
				printTac();
				return true;
			}
			// �����������
			cout << setiosflags(ios::left) << setw(3) << step++ << "\t" << setw(30) << analysis_str << "\t" << resetiosflags(ios::left);
			cout << setiosflags(ios::right) << setw(32) << input_str.substr(input_strIndex) << resetiosflags(ios::right) << "\t";
			cout << "\t" << "ƥ�䵱ǰ�ַ���" << endl;

			input_strIndex++;	// λ�ú���һλ������������봮������
			analysis_str.erase(analysis_str.size() - 1);
			//*************

			getValueByType_currNode(inputStr[inputStrIndex]);	// �������Ը��ս��
			// ���������ջ��������ͬ����ƥ��
			analysis_stack.pop();
			inputStrIndex++;
			continue;
		}
		// ���ջ��������������Ų�ƥ�䣬ջ�����ų�ջ�������Ƿ���ڿ��õĲ���ʽ������У��������ʽ�������ջ�����򱨴�
		else if (iter != LL_table[topCh].end()) {
			strProductionRight = LL_table[topCh][inputCh];

			// �����������
			cout << setiosflags(ios::left) << setw(3) << step++ << "\t" << setw(30) << analysis_str << "\t" << resetiosflags(ios::left);
			cout << setiosflags(ios::right) << setw(32) << input_str.substr(input_strIndex) << resetiosflags(ios::right) << "\t";
			cout << "\t" << topCh << "->" << strProductionRight << endl;
			analysis_str.erase(analysis_str.size() - 1);	// �ַ�����ͬ������,ɾ�����һ���ַ�
			//*************

			reverse(strProductionRight.begin(), strProductionRight.end());	// ����׼����ջ
			// ջ��Ԫ�س�ջ������ʽ�Ҳ�������ջ
			analysis_stack.pop();

			
			for (unsigned int i = 0; i < strProductionRight.length(); i++) {
				char c = strProductionRight.at(i);
				analysis_stack.push(strProductionRight.at(i));
				analysis_str.push_back(strProductionRight.at(i));
			}
		}
		else {
			cout << inputCh << "�������" << endl;
			return false;
		}
	}
	return true;
}