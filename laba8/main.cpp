#include "function.h"

int main(){
	auto a = [](int a, int b, int c){ return a + b + c; };
	auto b = [](double c){return 2 * c; };
	function<int, decltype(a), int, int, int> f1;
	function<double, decltype(b), double> f2;
	cout << "f1(1, 2, 3) = " << f1(1, 2, 3) << endl;
	cout << "arguments count of f1: " << f1.args_len << endl;
	cout << "integrate f1: " << f1.integrate(1, 2, 3, 1, 2, 3) << endl;
	cout << "integrate f2: " << f2.integrate(0, 1) << endl;

	double d = 3;

	cout << return_last(1, 12.7, string("rty123")) << endl;

	cout << return_last(1) << endl;

	return 0;
}