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

vectorn func1(double t, initializer_list<vectorn> list){
	return vectorn(0, 3);
}

vectorn func2(double t, initializer_list<vectorn> list){
	return vectorn(0, 3);
}

vectorn func3(double t, initializer_list<vectorn> list){
	return vectorn(0, 3);
}

vectorn force1(double t, vectorn &pos){
	vectorn v(pos.dir(vectorn(0, 3)));
	v[2] = 0;
	return v;
}

vectorn force2(double t, vectorn &pos){
	return pos.dir(vectorn(0, 3));
}

vectorn force3(double t, vectorn &pos){
	double x = 0;
	double y = 0;
	double z = -9.87;
	vectorn v({ x, y, z });
	return v;
}

void physics_test(bool to_exucute){
	if (!to_exucute) return;
	typedef vectorn (*func_type)(double, vectorn&);

	vectorn v0(0, 3);
	vectorn v1({ 3, 6.75, 2 });
	vectorn v2({ 4.82, 7, 1.15 });
	vectorn v3({ 9.9, 8.5, 3.678 });

	vectorn initpos(0, 3);
	vectorn initvel(1, 3);

	double dtime = 0.01;
	double *G = new double;
	double *time = new double;
	*G = 6.77 * 10E-11;
	*time = 0;
	particle<func_type> part1(initpos, initvel, 1, { force1, force2, force3 }, G, time);
	for (int i = 0; i < 1000; ++i){
		part1.apply_forces(nullptr, 0, dtime);
		part1.get_position().prints("current position: ");
		*time += dtime;
	}
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
	runge_kutti<decltype(f1)> de(0, vectorn(0, 3), 3);
	
	pair_s<double, vectorn>* solve;
	int data_cnt;
	pair_l<pair_s<double, vectorn>*, int> res = de.approximate(0.2, 0.001, -1);
	solve = res.argument;
	data_cnt = res.result;
	cout << data_cnt << endl;
	for (int i = 0; i < data_cnt; ++i){
		//print(solve[i]);
		cout << "{ " << solve[i].argument << "\t,";
		solve[i].result.prints();
		//cout << " }" << endl;
	}
	delete[] res.argument;

	diff_equation de1({ func1, func2, func3 });

	typedef vectorn f_type(double, initializer_list<vectorn>);
}

int main(){
	sample_test(0);
	physics_test(1);
	different_equat(0);

	return 0;
}