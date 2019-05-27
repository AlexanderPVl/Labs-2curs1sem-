#include "function.h"

int main(){
	auto a = [](int a, int b, int c){ return a + b + c; };
	auto b = [](double t){return t * t * t - t * t + 2; };
	auto c = [](double x, double y){return x * y; };
	function<int, decltype(a), int, int, int> f1;
	function<double, decltype(b), double> f2;
	function<double, decltype(c), double, double> f3;
	cout << "f1(1, 2, 3) = " << f1(1, 2, 3) << endl;
	cout << "arguments count of f1: " << f1.args_len << endl;
	//cout << "integrate f1: " << f1.integrate(1, 2, 3, 1, 2, 3) << endl;
	cout << "integrate f2: " << f2.integrate(0, 7.5255, 0.000001) << endl;
	cout << "derivative of f2 in 5: " << f2.derivative(3.785, 0.000001) << endl;
	cout << "gradient of f3 in (3, 3): {"; f3.grad(0.000001, 3.0, 3.0).print(); cout << "}" << endl;

	return 0;
}