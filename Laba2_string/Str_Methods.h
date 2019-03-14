#pragma once

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int FindDigit(string &str, int n);
int ReturnNumber(string StrToSrch, string &num, string &ToPut, int n);
bool IsBinary(char c);
int Pow(int a, int b);
int BinStrToInt(string &str);
int SkipDigits(string &str, int pos);
int DeleteNuls(string &str);

typedef struct{
	string  Num;
	int  NumCnt;
} Num_Struct;

class Num_Array{
private:
	Num_Struct * NumStrctArr;
	int Cnt;
public:
	Num_Array();
	~Num_Array();
	bool IfNumExists(string &num);
	void AddNumber(string &num);
	void MakeArrFromStr(string &str);
	void Print();
	void IncrNumbers(string &str);
	void ReplaceBinary(string &str){
		int ind = -1;
		int i = 0, bufint;
		string num="";
		while (FindDigit(str, ind + 1) != -1) {
			ind = FindDigit(str, ind + 1);
			i = ind;
			if (!IsBinary(str[i])){
				ind = SkipDigits(str, i);
				continue;
			}
			for (i = ind; i < str.length(); ++i){
				if (!IsBinary(str[i])){
					//++i;
					break;
				}

				num.append(1, str[i]);
			}
			if (isdigit(str[i])){
				ind = SkipDigits(str, i);
				i = ind;
				num.erase();
				continue;
			}
			bufint = num.length();
			DeleteNuls(num);
			str.replace(ind, bufint, to_string(BinStrToInt(num)));
			i = ind;
			num.erase(); 
		}
	}
};
