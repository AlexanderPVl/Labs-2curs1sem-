#include "function.h"

int main(){
	tuple_s<int> tupl1({ 1, 2, 3, 4, 5, 6, 7 });
	tuple_s<int> tupl2(tupl1);
	tuple_s<double> tupl3({ 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7 });

	tupl2.for_each_operate([](int i, int j){return i + j; }, tupl1);

	cout << tupl1;
	cout << tupl2;

	tuple_s<pair_s<double, pair_s<int, int>>> tuplprod = tuple_product(tupl3, tuple_product(tupl1, tupl2));
	cout << tuplprod;

	auto a = [](int a, int b, int c){ return a + b + c; };
	auto b = [](double c){return 2 * c; };
	function<int, decltype(a), int, int, int> f1;
	function<double, decltype(b), double> f2;
	cout << f1(1, 2, 3) << endl;
	cout << f1.args_len << endl;
	cout << "integrate f1: " << f1.integrate(1, 2, 3, 1, 2, 3);
	cout << "integrate f2: " << f2.integrate(0, 1);

	cout << return_last(1, 12.7, string("rty123")) << endl;

	cout << return_last(1) << endl;

	return 0;
}