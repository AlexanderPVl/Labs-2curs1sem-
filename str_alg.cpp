#include "str_alg.h"

ostream &operator << (ostream &ost, vector<string> str){
	for (auto v : str) { cout << v << " "; }
	return ost;
}

ostream &operator << (ostream &ost, set<char> st){
	for (auto c : st) { cout << c << " "; }
	return ost;
}

void func4(vector<string> &vs_, set<char> &s_, const char* srch_str_){
	for (string s : vs_){
		for (char c : s) s_.insert(c);
	}
	for (vector<string>::iterator it = vs_.begin(); it != vs_.end();)
	{
		if (!strpbrk((*it).c_str(), srch_str_)) { it = vs_.erase(it); }
		else ++it;
	}
}

void enter_vs(vector<string> &vs){
	string buf; vs.clear();
	do{
		cin >> buf;
		vs.push_back(buf);
	} while (cin.peek() != '\n');
}

void intersection(){
	const char* digit_str = "123456789";
	vector<string> str1;
	vector<string> str2;
	vector<char> symb1;
	vector<char> symb2;
	set<char> set1;
	set<char> set2;
	set<char> set;
	
	bool fl;

	enter_vs(str1);
	enter_vs(str2);

	func4(str1, set1, digit_str);
	func4(str2, set2, digit_str);

	set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(set, set.end()));

	cout << "symb1: " << set1 << endl;
	cout << "symb2: " << set2 << endl;
	cout << "intersection: " << set << endl;
	cout << "string 1: " << str1 << endl;
	cout << "string 2: " << str2 << endl;
}