#include "nums.h"

template<class T>
ostream &operator << (ostream &ost, vector<T> str){
	for (auto c : str) { cout << c << " "; }
	return ost;
}

void rand_gen()
{
	random_device rd;
	default_random_engine gen(rd());
	uniform_int_distribution<> dist(1, 100);

	vector<int> nums;

	for (int i = 0; i < 20; ++i) {
		nums.push_back(dist(gen));
	}
	for (vector<int>::iterator it = nums.begin(); it != nums.end(); (*it % 6) ? it = nums.erase(it) : ++it){}
	cout << nums;
}

bool is_polyndrome(int t){
	typedef string::iterator s_iterator;
	typedef reverse_iterator<string::iterator> rs_iterator;
	string buf = to_string(t);
	int i = 0;
	string rbuf(buf.rbegin(), buf.rend() - buf.length() / 2);
	for (auto c : rbuf){
		if (buf[i++] != c) return false;
	}
	cout << rbuf;
	return true;
}

void odometer(){
	int num;
	cout << "Enter polyndrome greater then 15951" << endl;
	do{
		cin >> num;
		if (num > 15951 && is_polyndrome(num)) break;
		if (num <= 15951) cout << "enter bigger number" << endl;
		if (!is_polyndrome(num)) cout << "enter polyndrome" << endl;
	} while (num <= 15951 || !is_polyndrome(num));
	cout << "average speed: " << (num - 15951.0) / 2 << " km/h" << endl;
}
