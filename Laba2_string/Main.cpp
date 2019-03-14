#include "Str_methods.h"

using namespace std;

int main(){
	string Str1 = "yyy1yyy1hhh2222hhh2222aaa123aaa123bbb234bbb234ccc345ccc345ddd456eee567fff";
	string Str2 = "00011abc1010def000310ff0010ff0010";
	string NumBuf = "";
	Num_Array Array;

	Array.MakeArrFromStr(Str1);

	cout << "Str1 = " << Str1 << endl;
	cout << "Str2 = " << Str2 << endl;

	Array.IncrNumbers(Str1);
	Array.ReplaceBinary(Str2);
	cout << endl;

	cout << "Str1 after incrementing: " << Str1 << endl;
	cout << "Str1 after replacing binary numbers: " << Str2 << endl;

	return 0;
}
