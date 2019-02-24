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
	string buf;
	while (t){
		buf.append(to_string(t % 10));
		t /= 10;
	}
	int len = buf.length();
	for (int i = 0; i < len; ++i){ if (buf[i] != buf[len - i - 1]) return false; }
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