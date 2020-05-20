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
		ifs.get(ch);//получаем символ из файла
		if (ifs.eof()) break;
		s[i++] = ch;//переписываем полученный символ в строку
	}
	s[i] = '\0';//закрываям строку

	return true;
}

std::string toLowerCase(std::string str)
{//перевод строки в нижний регистр
	std::string result = "";
	//Перевод строки посимвольно в нижний регистр
	for (auto& c : str) {
		c = tolower(c);//перевод символа в нижний регистр
		result += c;//добавление к строке
	}
	return result;
}
void zamena(std::string &str, std::string old, std::string sNew)
{//замена  старой подстроки на новую
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
{//удаление лишних пробелов 
	int len = strlen(str);
	char *s = (char*)malloc(len);
	int inx, i;
	for (inx = 0, i = 0; i < len - 1; i++) {

		//удаление пробелов и переноса в начале строки
		if (inx == 0) {
			//пропускаем табуляцию или пробел в начале строки, чтобы не переписывать их
			while (i < len && (str[i] == ' ' || str[i] == '\t')) i++;
		}

		if ((str[i] == ' ' && str[i + 1] != ' ') || str[i] != ' ')
			s[inx++] = str[i];
	}
	//закрываем строку
	s[inx] = '\0';
	strcpy(str, s);//копируем строку обратно
	free(s);//освобождение памяти
}
std::string setCaseToFirstLetter(std::string str)
{//замена первой буквы на заглавную
	int len = str.length();
	bool bFirstLetter = true;
	int nPos = 0;
	int ntmp;
	//смотрим есть ли точка в конце строки если нет - ставим
	ntmp = len - 1;
	while (ntmp >= 0) {
		if (str[ntmp] == ' ') {
			str = str.substr(0, ntmp);//уберем пробел
			ntmp--;//двигаемся к началу строки	
		}
		else {
			if (str[ntmp] == '.' || str[ntmp] == '!' || str[ntmp] == '?') break;//точка или ! или ? вконце строки есть
			str += '.';//добавим точку в конец строки как окончание предложения
			break;
		}
	}
	for (int i = 0; i < len; i++) { //перебор строки 
		if (bFirstLetter) {//перевод первого символа строки в верхний регистр
			if (str[i] != ' ') {
				bFirstLetter = false;
				str[i] = toupper(str[i]);
			}
		}
		else {//поиск конца предложения, для присвоения символу верхнего регистра	
			int point = str.find('.', nPos);//если .
			int voskl = str.find('!', nPos);//есл !
			int question = str.find('?', nPos);//если ?
			char currChar = '.';//текущий символ
			if (point >= 0) {// точка
				if ((voskl < 0 && question < 0) || (voskl < 0 && question >= 0 && point < question) ||
					(voskl >= 0 && question < 0 && point < voskl) || (voskl >= 0 && question >= 0 && point < voskl && point < question)) {
					nPos = point;
					currChar = '.';
				}
			}
			if (voskl >= 0) {//воскл
				if ((point < 0 && question < 0) || (point < 0 && question >= 0 && voskl < question) ||
					(point >= 0 && question < 0 && voskl < point) || (point >= 0 && question >= 0 && voskl < point && voskl < question)) {
					nPos = voskl;
					currChar = '!';
				}
			}
			if (question >= 0) {//вопрос
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
				ntmp++;//переход к следующему символу
				i = ntmp;
			}
		}
	}
	return str;
}
void saveFile(char name[], char str[])
{//запись файла
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
	std::cout << "Текст из файла:\n";
	std::cout << str << std::endl;
	std::string s = str;
	//перевод строки в нижний регистр
	s = toLowerCase(s);
	//добавление пробелов после запятых, точек, вопросительных и восклицательных знаков
	zamena(s, ",", ", ");
	zamena(s, ".", ". ");
	zamena(s, "!", "! ");
	zamena(s, "?", "? ");
	strcpy(str, s.c_str());
	//удаление лишних пробелов в строке
	removeSpaces(str);
	//замена в каждом предложении строки, первую букву на заглавную
	s = str;
	s = setCaseToFirstLetter(s);//первый сисвол в начале предложения с большой строки

	strcpy(str, s.c_str());
	saveFile("output.txt", str);//запись строки в файл
	std::cout << "\nТекст после изменений:\n";
	std::cout << str << std::endl;

	std::cout << std::endl;
	system("pause");
}
