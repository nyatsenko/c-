#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>

bool readFile(std::string path, char *s) {
	std::ifstream ifs(path);
	if (ifs.fail()) return false;
	char ch;
	int i = 0;
	while (true) {
		ifs.get(ch);//�������� ������ �� �����
		if (ifs.eof()) break;
		s[i++] = ch;//������������ ���������� ������ � ������
	}
	s[i] = '\0';//��������� ������

	return true;
}

std::string toLowerCase(std::string str)
{//������� ������ � ������ �������
	std::string result = "";
	//������� ������ ����������� � ������ �������
	for (auto& c : str) {
		c = tolower(c);//������� ������� � ������ �������
		result += c;//���������� � ������
	}
	return result;
}
void zamena(std::string &str, std::string old, std::string sNew)
{//������  ������ ��������� �� �����
	std::string s, o;//str/old
	s = toLowerCase(str);
	o = toLowerCase(old);
	int len = sNew.length();
	int nPos = s.find(old.c_str());

	while (nPos >= 0) {
		str = s.replace(nPos, len, sNew);
		nPos = s.find(old.c_str(), nPos + 1);
	}
}
void removeSpaces(char *str)
{//�������� ������ �������� 
	int len = strlen(str);
	char *s = (char*)malloc(len);
	int inx, i;
	for (inx = 0, i = 0; i < len - 1; i++) {

		//�������� �������� � �������� � ������ ������
		if (inx == 0) {
			//���������� ��������� ��� ������ � ������ ������, ����� �� ������������ ��
			while (i < len && (str[i] == ' ' || str[i] == '\t')) i++;
		}

		if ((str[i] == ' ' && str[i + 1] != ' ') || str[i] != ' ')
			s[inx++] = str[i];
	}
	//��������� ������
	s[inx] = '\0';
	strcpy(str, s);//�������� ������ �������
	free(s);//������������ ������
}
std::string setCaseToFirstLetter(std::string str)
{//������ ������ ����� �� ���������
	int len = str.length();
	bool bFirstLetter = true;
	int nPos = 0;
	int ntmp;
	//������� ���� �� ����� � ����� ������ ���� ��� - ������
	ntmp = len - 1;
	while (ntmp >= 0) {
		if (str[ntmp] == ' ') {
			str = str.substr(0, ntmp);//������ ������
			ntmp--;//��������� � ������ ������	
		}
		else {
			if (str[ntmp] == '.' || str[ntmp] == '!' || str[ntmp] == '?') break;//����� ��� ! ��� ? ������ ������ ����
			str += '.';//������� ����� � ����� ������ ��� ��������� �����������
			break;
		}
	}
	for (int i = 0; i < len; i++) { //������� ������ 
		if (bFirstLetter) {//������� ������� ������� ������ � ������� �������
			if (str[i] != ' ') {
				bFirstLetter = false;
				str[i] = toupper(str[i]);
			}
		}
		else {//����� ����� �����������, ��� ���������� ������� �������� ��������	
			int point = str.find('.', nPos);//���� .
			int voskl = str.find('!', nPos);//��� !
			int question = str.find('?', nPos);//���� ?
			char currChar = '.';//������� ������
			if (point >= 0) {// �����
				if ((voskl < 0 && question < 0) || (voskl < 0 && question >= 0 && point < question) ||
					(voskl >= 0 && question < 0 && point < voskl) || (voskl >= 0 && question >= 0 && point < voskl && point < question)) {
					nPos = point;
					currChar = '.';
				}
			}
			if (voskl >= 0) {//�����
				if ((point < 0 && question < 0) || (point < 0 && question >= 0 && voskl < question) ||
					(point >= 0 && question < 0 && voskl < point) || (point >= 0 && question >= 0 && voskl < point && voskl < question)) {
					nPos = voskl;
					currChar = '!';
				}
			}
			if (question >= 0) {//������
				if ((voskl < 0 && point < 0) || (voskl < 0 && point >= 0 && question < point) ||
					(voskl >= 0 && point < 0 && question < voskl) || (voskl >= 0 && point >= 0 && question < voskl && question < point)) {
					nPos = question;
					currChar = '?';
				}
			}
			ntmp = nPos;
			if (ntmp == -1) return str;
			while (ntmp < len) {
				if (str[ntmp] != ' ' && (str[ntmp] != currChar)) {
					str[ntmp] = toupper(str[ntmp]);
					nPos++;
					i = ntmp;
					break;
				}
				ntmp++;//������� � ���������� �������
				i = ntmp;
			}
		}
	}
	return str;
}
void saveFile(char name[], char str[])
{//������ �����
	FILE *f;
	f = fopen(name, "w");
	fprintf(f, "%s", str);
	fclose(f);
}
int main()
{
	
	setlocale(LC_ALL, "RU");
	char *str = new char[1000];
	readFile("input.txt", str);
	std::cout << "����� �� �����:\n";
	std::cout << str << std::endl;
	std::string s = str;
	//������� ������ � ������ �������
	s = toLowerCase(s);
	//���������� �������� ����� �������, �����, �������������� � ��������������� ������
	zamena(s, ",", ", ");
	zamena(s, ".", ". ");
	zamena(s, "!", "! ");
	zamena(s, "?", "? ");
	strcpy(str, s.c_str());
	//�������� ������ �������� � ������
	removeSpaces(str);
	//������ � ������ ����������� ������, ������ ����� �� ���������
	s = str;
	s = setCaseToFirstLetter(s);//������ ������ � ������ ����������� � ������� ������

	strcpy(str, s.c_str());
	saveFile("output.txt", str);//������ ������ � ����
	std::cout << "\n����� ����� ���������:\n";
	std::cout << str << std::endl;

	std::cout << std::endl;
	system("pause");
}
