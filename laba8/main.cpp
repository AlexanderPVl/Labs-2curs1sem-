#include "function.h"
#include "physics.h"

void sample_test(bool to_exucute){
	if (!to_exucute) return;
	auto a = [](int a, int b, int c){ return a + b + c; };
	auto b = [](double t){return t * t * t - t * t + 2; };
	auto c = [](double x, double y){return x * y; };
	function<int, decltype(a), int, int, int> f1;
	function<double, decltype(b), double> f2;
	function<double, decltype(c), double, double> f3;
	cout << "f1(1, 2, 3) = " << f1(1, 2, 3) << endl;
	cout << "arguments count of f1: " << f1.args_len << endl;
	cout << "integrate f2: " << f2.integrate(0, 7.5255, 0.000001) << endl;
	cout << "derivative of f2 in 5: " << f2.derivative(3.785, 0.000001) << endl;
	cout << "gradient of f3 in (3, 3): {"; f3.grad(0.000001, 3.0, 3.0).print(); cout << "}" << endl;
}

void physics_test(bool to_exucute){
	if (!to_exucute) return;

	vectorn v0(0, 3);
	vectorn v1({ 3, 6.75, 2 });
	vectorn v2({ 4.82, 7, 1.15 });
	vectorn v3({ 9.9, 8.5, 3.678 });

	auto f1 = [](vectorn pos, double t){
		double x = pos[0] + pos[1] / t + pos[2] / (t * t);
		double y = pos[0] + pos[1] + pos[2] * t;
		double z = pos[0] * pos[1] * pos[2] * t;
		vectorn v({ x, y, z });
		return v;
	};
	auto f2 = [](vectorn pos, double t){
		double x = 3;
		double y = pos[0] + pos[1] + pos[2] / t;
		double z = 5;
		vectorn v({ x, y, z });
		v / (t + 0.4);
		return v;
	};
	auto f3 = [](vectorn pos, double t){
		double x = 1;
		double y = 2;
		double z = pos[0] * pos[1] / t + pos[2] / t;
		vectorn v({ x, y, z });
		v / (t + 1);
		return v;
	};

	func_tuple<decltype(f1), decltype(f2), decltype(f3)> tupl1;
	tupl1.get_3()(v1, 26).prints();
}

void different_equat(bool to_exucute){
	if (!to_exucute) return;

	auto f1 = [](double t, vectorn vec){
		double x = 1 + vec[0];
		double y = 1.5 + vec[1];
		double z = 2 + vec[2];
		vectorn res({ x, y, z });
		res * t;
		return res;
	};
	diff_equation<decltype(f1)> de(0, vectorn(0, 3), 3);
	
	pair_s<double, vectorn>* solve;
	int data_cnt;
	pair_l<pair_s<double, vectorn>*, int> res = de.approximate(1, 0.001, -1);
	solve = res.argument;
	data_cnt = res.result;
	cout << data_cnt << endl;
	for (int i = 0; i < data_cnt; ++i){
		//print(solve[i]);
		cout << "{ " << solve[i].argument << "\t,";
		solve[i].result.prints();
		cout << " }" << endl;
	}
}

int main(){
	sample_test(0);
	physics_test(0);
	different_equat(1);

	return 0;
}