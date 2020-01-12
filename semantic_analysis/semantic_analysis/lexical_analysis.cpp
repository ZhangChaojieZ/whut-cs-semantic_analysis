#include<iostream>
#include<string>
#include"lexical_analysis.h"
//#include"data_structure.h"
using namespace std;
inputStringNode inputNode;

//	�����֡���ʶ�������ֵĴʷ���������
int KeyIdentNumAnalysis(string strKeyNumIdWord, string &strTemp, vector<inputStringNode> &inputStr) {

	if (KeywordAnalysis(strKeyNumIdWord) != ERROR) {
		strTemp = strKeyNumIdWord;
		//cout << strTemp << "\tK" << endl;
		
		if(strKeyNumIdWord=="while") {
			inputNode.type = 'w';
			cout << strTemp << "\tw" << endl;
		}
		else { 
			inputNode.type = 'K'; 
			cout << strTemp << "\tK" << endl;
		}
		inputNode.value = strKeyNumIdWord;
		inputStr.push_back(inputNode);
		return KEYWORD;
	}
	else if (IdentAnalysis(strKeyNumIdWord) != ERROR) {
		strTemp = strKeyNumIdWord;
		cout << strTemp << "\tg" << endl;
		inputNode.type = 'g';
		inputNode.value = strKeyNumIdWord;
		inputStr.push_back(inputNode);
		return IDENT;
	}
	else if (NumberAnalysis(strKeyNumIdWord) != ERROR) {
		strTemp = strKeyNumIdWord;
		cout << strTemp << "\tf" << endl;
		inputNode.type = 'f';
		inputNode.value = strKeyNumIdWord;
		inputStr.push_back(inputNode);
		return CONSTANT;
	}
	else {
		// cout << "��������" << endl;
		return ERROR;
	}
}

// �ؼ��ִʷ�����
int KeywordAnalysis(string strKeyword) {
	const char* strchar = strKeyword.c_str();
	char ch = strchar[0];

	if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z')) {
		for (int i = 0; i < CHKEYLEFTNUM; i++) {
			if (strKeyword == chKeyWord[i]) {
				return KEYWORD;
			}
		}
	}
	return ERROR;
}

// ��ʶ���ʷ�����
int IdentAnalysis(string strIdent) {
	const char* strchar = strIdent.c_str();
	char ch = strchar[0];

	if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z')) {
		for (int i = 0; i < CHKEYLEFTNUM; i++) {
			if (strIdent == chKeyWord[i]) {
				return 0;
			}
		}
		return IDENT;
	}
	return ERROR;
}

// ���ִʷ�����
int NumberAnalysis(string strNum) {
	const char* strchar = strNum.c_str();
	char ch;
	int d = 0;
	int sum = 0;

	for (unsigned int i = 0; i < strNum.length(); i++) {
		ch = strchar[i];
		if (ch >= '0'&&ch <= '9') {
			d = strchar[i] - 48;	// ��Ϊ�ַ�'0'��ASCII��ֵΪ48
			sum = sum * 10 + d;
		}
		else {
			return ERROR;
		}
	}
	return sum;
}

// ������ʷ�����
int OperatorAnalysis(string strOperator) {
	for (int i = 0; i < CHOPERNUM; i++) {
		if (strOperator == chOperatorWord[i]) {
			cout << strOperator << "\t" << strOperator << endl;
			return OPERATOR;
		}
	}
	return ERROR;
}

// ���޷��ʷ�����
int BaundaryAnlysis(string strBaundary) {
	for (int i = 0; i < CHBAUNNUM; i++) {
		if (strBaundary == chBaundaryWord[i]) {
			//string strTemp2 = "( '" + strBaundary + "' , " + "5" + " )";
			cout << strBaundary << "\t" << strBaundary << endl;
			return BAUNDARY;
		}
	}
	return ERROR;
}

// �ж��Ƿ���������ַ�
bool IsOperator(char ch) {
	for (int i = 0; i < CHOPERNUM; i++) {
		if (ch == chOperator[i]) {
			return true;
		}
	}
	return false;
}

void addOpter_inputString(vector<inputStringNode> &inputStr,string strOperator) {
	if (strOperator == "=" || strOperator == "+" || strOperator == "-" || strOperator == "*" || strOperator == "/" || strOperator == ">" || strOperator == "<") {
		inputNode.type = strOperator.at(0);
		inputNode.value = strOperator;
		inputStr.push_back(inputNode);
	}
	else if (strOperator == ">=") {
		inputNode.type = 'm';
		inputNode.value = "m";
		inputStr.push_back(inputNode);
	}
	else if (strOperator == "<=") {
		inputNode.type = 'n';
		inputNode.value = "n";
		inputStr.push_back(inputNode);
	}
}

void addBaun_inputString(vector<inputStringNode> &inputStr, string  strBaun) {
	if (strBaun == ";" || strBaun == "(" || strBaun == ")" || strBaun == "{" || strBaun == "}") {
		inputNode.type = strBaun.at(0);
		inputNode.value = strBaun;
		inputStr.push_back(inputNode);
	}
	else {
		inputNode.type = 'B';
		inputNode.value = strBaun;
		inputStr.push_back(inputNode);
	}
}

// �ʷ���������
int LexAnalysis(int &wordIndex, char &ch, string &strWord,
	string &strOperator, string &strBaun, string &strTemp, vector<inputStringNode> &inputStr) {
	int temp;
	// ���˵��ո񡢻��з����Ʊ�� 
	if (ch != ' '&&ch != '\n'&&ch != '\t') {
		// ����Ƿǿո��Ʊ�����س������������������ַ�������ӵ�strWord�ַ�����
		if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || (ch >= '0'&&ch <= '9')) {
			strWord += ch;
			//�����жϲ������Ƿ���>=,<=,:=��
			if (strOperator != "") {
				wordIndex++;		// ����ȷ�������λ��
				if (OperatorAnalysis(strOperator) != 0) {					
					addOpter_inputString(inputStr, strOperator);
					//inputStr.push_back(strOperator.at(0));
					strOperator = "";
				}
				else {
					strOperator = "";
					cout << "��" << wordIndex << "�����ʷ�������" << endl;
					return ERROR;
				}
			}
			return READ;
		}
		// ����ǲ���������ӵ�strOpertor�ַ�����
		else if (IsOperator(ch)) {
			wordIndex++;
			strOperator += ch;
			/* Ҫ�ж�strWord�ַ����Ƿ�Ϊ�գ����ܻ���������ո��Ʊ�����س��������
			 * ���������ո�ȷָ������ᱻʶ��Ϊ�ָ���������ִ���ַ����ʷ������ӳ���
			 * ����ʶ�𵽵�һ���ո�ʱ���Ѿ�ִ�й��ʷ������ӳ���Ӧ�������ظ�ִ��
			 * ����Ҫ�ж�strWord�ַ����Ƿ�Ϊ�գ���Ϊ��ֵ����ִ�дʷ������ӳ��򣻷�ִ֮�дʷ������ӳ���
			 * �·��ж�strWord�ַ����Ƿ�Ϊ�յ�Ŀ���������
			*/
			if (!(strWord == "")) {
				wordIndex++;
				// �����������ָ��ʶ�����ؼ��ֵȣ�ҲҪ��strWord���ж�
				temp = KeyIdentNumAnalysis(strWord, strTemp, inputStr);
				if (temp != 0) {
					strWord = "";
					//return temp;
					//return READ;
				}
				else {
					strWord = "";
					cout << "��" << wordIndex << "�����ʷ�������" << endl;
					return ERROR;
				}
			}

			// ���ܻ����>=,<=,:=�����ͣ��������һ���ж�
			if (ch == '<' || ch == '>' || ch == ':') {
				wordIndex--;
				return READ;
			}

			if (OperatorAnalysis(strOperator) != 0) {
				addOpter_inputString(inputStr, strOperator);
				//inputStr.push_back(strOperator.at(0));
				strOperator = "";
				return OPERATOR;
			}

		}
		else if (ch == '(' || ch == ')' || ch == ',' || ch == ';' || ch == '.' || ch == '{' || ch == '}') {
			strBaun += ch;
			//�����жϲ������Ƿ���>=,<=,:=��
			if (strOperator != "") {
				wordIndex++;
				if (OperatorAnalysis(strOperator) != 0) {
					addOpter_inputString(inputStr, strOperator);
					//inputStr.push_back(strOperator.at(0));
					strOperator = "";
				}
				else {
					strOperator = "";
					cout << "��" << wordIndex << "�����ʷ�������" << endl;
					return ERROR;
				}
			}

			if (!(strWord == "")) {
				wordIndex++;
				// ���������ָ��ʶ�����ؼ��ֵȣ�ҲҪ��strWord���ж�
				temp = KeyIdentNumAnalysis(strWord, strTemp, inputStr);
				if (temp != 0) {
					strWord = "";
					//return temp;
					//return READ;
				}
				else {
					strWord = "";
					cout << "��" << wordIndex - 1 << "�����ʷ�������" << endl;
					return ERROR;
				}

			}

			if (BaundaryAnlysis(strBaun) != 0) {
				wordIndex++;
				// �߽��������ʱ��ΪB
				addBaun_inputString(inputStr, strBaun);
				//inputStr.push_back(strBaun.at(0));
				strBaun = "";
				return BAUNDARY;
			}
			else {
				strBaun = "";
				cout << "��" << wordIndex << "�����ʷ�������" << endl;
				return ERROR;
			}

		}
		else {

			if (int(ch) != -1) {	//ch==-1,���ʾ�����ļ�ĩβ
				strWord = "";
				cout << "��" << wordIndex << "�����ʴ���" << endl;
				return 0;
			}
			else {
				//�����жϲ������Ƿ���>=,<=,:=��
				if (strOperator != "") {
					wordIndex++;
					if (OperatorAnalysis(strOperator) != 0) {
						addOpter_inputString(inputStr, strOperator);
						//inputStr.push_back(strOperator.at(0));
						strOperator = "";
					}
					else {
						strOperator = "";
						cout << "��" << wordIndex << "�����ʷ�������" << endl;
						return ERROR;
					}
				}

				if (!(strWord == "")) {
					wordIndex++;
					// �����ļ�ĩβʱ��Ӧ�ö��ַ������дʷ�����
					temp = KeyIdentNumAnalysis(strWord, strTemp, inputStr);
					if (temp != 0) {
						strWord = "";
						return temp;
						//return READ;
					}
					else {
						strWord = "";
						cout << "��" << wordIndex << "�����ʷ�������" << endl;
						return 0;
					}
				}
			}
		}
	}
	else {
		//�����жϲ������Ƿ���>=,<=,:=��
		if (strOperator != "") {
			wordIndex++;
			if (OperatorAnalysis(strOperator) != 0) {
				addOpter_inputString(inputStr, strOperator);
				//inputStr.push_back(strOperator.at(0));
				strOperator = "";
			}
			else {
				strOperator = "";
				cout << "��" << wordIndex << "�����ʷ�������" << endl;
				return ERROR;
			}
		}

		if (!(strWord == "")) {
			wordIndex++;
			// �ٴ������ո���ַ�ʱ��Ӧ�ö��ַ������дʷ�����
			temp = KeyIdentNumAnalysis(strWord, strTemp, inputStr);
			if (temp != 0) {
				strWord = "";
				return temp;
			}
			else {
				strWord = "";
				cout << "��" << wordIndex << "�����ʷ�������" << endl;
				return 0;
			}
		}
	}
	return READ;
}