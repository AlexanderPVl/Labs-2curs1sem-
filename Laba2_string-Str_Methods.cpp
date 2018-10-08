#include "Str_Methods.h"

Num_Array::Num_Array(){
	NumStrctArr = NULL;
	Cnt = 0;
}
Num_Array::~Num_Array(){
	if (NumStrctArr){
		delete[] NumStrctArr;
		NumStrctArr = NULL;
		Cnt = 0;
	}
}
bool Num_Array::IfNumExists(string &num){
	int i;
	if (!NumStrctArr)return false;
	for (i = 0; i < Cnt; ++i){
		if (NumStrctArr[i].Num == num)return true;
	}
	return false;
}
void Num_Array::AddNumber(string &num){
	int i;
	if (!NumStrctArr){
		NumStrctArr = new Num_Struct[1];
		NumStrctArr[0].Num = num;
		NumStrctArr[0].NumCnt = 1;
		Cnt++;
		return;
	}
	for (i = 0; i < Cnt; ++i){
		if (NumStrctArr[i].Num == num){
			NumStrctArr[i].NumCnt++;
			return;
		}
	}
	Num_Struct * NewNumStrctArr = new Num_Struct[Cnt + 1];
	for (i = 0; i < Cnt; ++i){
		NewNumStrctArr[i] = NumStrctArr[i];
	}
	NumStrctArr = NewNumStrctArr;
	NumStrctArr[Cnt].Num = num;
	NumStrctArr[Cnt].NumCnt = 1;
	Cnt++;
}
void Num_Array::Print(){
	int i;
	if (!NumStrctArr){
		cout << "Array is empty" << endl;
		return;
	}
	else {
		cout << endl;
		for (i = 0; i < Cnt; ++i){
			cout << i + 1 << ") " << NumStrctArr[i].Num << " : " << NumStrctArr[i].NumCnt << endl;
		}
		cout << endl;
	}
}
void Num_Array::MakeArrFromStr(string &str){
	int i = 0;
	int ind = -1, len = str.length();
	string num = "";
	while (ind < len){
		ind = FindDigit(str, ind + 1);
		if (ind == -1)break;
		for (i = ind; ind < len && isdigit(str[i]); ++i) {
			num.append(1, str[i]);
		}
		ind = i;
		AddNumber(num);
		num.erase();
	}
}
void Num_Array::IncrNumbers(string &str){
	int i = 0, bufint;
	int ind, len = str.length();
	string bufstr;
	for (i = 0; i < Cnt; ++i){
		if (NumStrctArr[i].NumCnt < 2)continue;
		ind = 0;
		while (ind < len){
			if (str.find(NumStrctArr[i].Num, ind + 1) == string::npos)break;
			ind = str.find(NumStrctArr[i].Num, ind + 1);
			bufint = atoi(NumStrctArr[i].Num.c_str()) + 1;
			bufstr = to_string(bufint);
			str.replace(ind, NumStrctArr[i].Num.length(), bufstr);
		}
	}
}

int FindDigit(string &str, int n){ // возвращает индекс первого вхождения цифры в строке начиная с индекса n
	int i = n;
	int len = str.length();
	if (n >= len)return -1;
	while (i < len && !isdigit(str[i])) ++i;
	return (0 <= i && i < len) ? i : -1;
}

int ReturnNumber(string StrToSrch, string &num, string &ToPut, int n){ //находит число num в строке StrToSrch, пишет его в строку ToPut, возвращает индекс num в строке 
	int i = 0, len = StrToSrch.length();
	int ind = 0;
	while (ind < len){
		ind = StrToSrch.find(num, ind);
		i = ind;
		while (isdigit(StrToSrch[i])){
			++i;
		}
	}
	return n;
}

bool IsBinary(char c) { return (c == '0' || c == '1'); }

int Pow(int a, int b){
	int i = 1;
	while ((b--) > 0)i *= a;
	return i;
}

int BinStrToInt(string &str){
	int len = str.length();
	int sum = 0;
	for (int i = 1; i <= len; ++i){
		sum += (str[len - i] - '0')*Pow(2, (i - 1));
	}
	return sum;
}

int SkipDigits(string &str, int pos){
	int len = str.length();
	while (isdigit(str[pos++])){
		if (pos >= len)break;
	}
	return pos;
}

int DeleteNuls(string &str){
	int i, len = str.length();
	for (i = 0; str[i] == '0'; ++i)if (i == len){ str.erase(); return len - 1; }
	str.erase(0, i);
	return i;
}
