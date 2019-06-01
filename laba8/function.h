#pragma once

#include "algorithms.h"
#include <fstream>

template<class Arg, class Res>
struct pair_s{
	pair_s(){};
	pair_s(Arg arg, Res res) : argument(arg), result(res){}
	Arg argument;
	Res result;
};

template<class Arg, class Res>
void operator << (ostream &ost, pair_s<Arg, Res> ps){
	cout << "{ " << ps.argument << ", " << ps.result << " }" << endl;
}

template<class Arg, class Res>
void print(pair_s<Arg, Res> ps){
	cout << "{ " << ps.argument << ", " << ps.result << " }" << endl;
}

template<class Arg, class Res>
struct pair_l{
	pair_l() = default;
	pair_l(Arg arg, Res res) : argument(arg), result(res){}
	void operator = (pair_l pl){
		argument = pl.argument;
		result = pl.result;
	}
	void operator = (pair_s<Arg, Res> ps) { argument = ps.argument, result = ps.result; }
	Arg argument;
	Res result;
};

template<class Arg, class Res>
ostream& operator << (ostream& ost, pair_s<Arg, Res> pr){
	ost << "<" << pr.argument << ", " << pr.result << "> ";
	return ost;
}

template<class T>
struct tuple_s{
	tuple_s() : data(nullptr), size(0){}
	tuple_s(T arr[]) {
		size = sizeof(arr) / sizeof(arr[0]);
		data = new T[size];
		for (int i = 0; i < size; ++i) data[i] = arr[i];
	}
	tuple_s(initializer_list<T> list) {
		size = list.size();
		data = new T[size];
		int i = 0;
		for (auto it = list.begin(); it != list.end(); ++it, ++i) data[i] = *it;
	}
	tuple_s(T* arr, int n){
		size = n;
		data = new T[n];
		for (int i = 0; i < n; ++i) data[i] = arr[i];
	}
	tuple_s(tuple_s tupl, int n ...){
		if (decltype(n) == decltype(nan)) n = tupl.size;
		size = (n < tupl.size) ? n : tupl.size;
		data = new T[n];
		for (int i = 0; i < n; ++i) data[i] = tupl.data[i];
	}
	~tuple_s(){ if (!data) delete[] data; }
	T& operator [](unsigned int i) {
		if (size <= i) throw except_index_out_of_range(i);
		return data[i];
	}
	void add(T elem){
		if (!data) {
			data = new T[1]; data[0] = elem;
			size = 1;
			return;
		}
		T* buff = new T[size];
		copy_tf(buff, data, size);
		delete[] data;
		++size;
		data = new T[size];
		copy_tf(data, buff, size - 1);
		data[size - 1] = elem;
		delete[] buff;
	}
	void operator = (T arr[]) {
		size = sizeof(arr) / sizeof(arr[0]);
		data = new T[size];
		for (int i = 0; i < size; ++i) data[i] = arr[i];
	}
	bool operator = (tuple_s tupl){
		size = tupl.size;
		if (!data) delete[] data;
		data = new T[size];
		for (int i = 0; i < size; ++i) data[i] = tupl[i];
	}
	bool operator < (tuple_s tupl) {
		if (size != tupl.size) throw except_non_compatible("unable to compare tuple_ss (different dimentions)");
		for (int i = 0; i < size; ++i){ if (data[i] >= tupl.data[i]) return false; }
		return true;
	}
	bool operator >(tuple_s tupl) {
		if (size != tupl.size) throw except_non_compatible("unable to compare tuple_ss (different dimentions)");;
		for (int i = 0; i < size; ++i){ if (data[i] <= tupl.data[i]) return false; }
		return true;
	}
	bool operator == (tuple_s tupl) {
		if (size != tupl.size) return false;
		for (int i = 0; i < size; ++i){ if (data[i] != tupl.data[i]) return false; }
		return true;
	}
	bool operator != (tuple_s tupl) {
		bool bl = false;
		if (size != tupl.size) return true;
		for (int i = 0; i < size; ++i){ if (data[i] != tupl.data[i]) fl = true; }
		return bl;
	}
	template<class UnaryOperator>
	void for_each_apply(UnaryOperator f) { for (int i = 0; i < size; ++i) f(data[i]); }
	template<class UnaryOperator>
	void for_each_transform(UnaryOperator f) { for (int i = 0; i < size; ++i) data[i] = f(data[i]); }
	template<class BinaryOperator>
	void for_each_operate(BinaryOperator f, tuple_s tupl) { for (unsigned int i = 0; i < size; ++i) data[i] = f(data[i], tupl.data[i]); }
	void print() { for (int i = 0; i < size; ++i) { cout << data[i] << ", "; } }
	T* data;
	size_t size;
};

template<class T>
ostream& operator << (ostream& ost, tuple_s<T> tupl){
	for (unsigned int i = 0; i < tupl.size; ++i){
		ost << tupl.data[i] << endl;
	}
	ost << endl;
	return ost;
}

template<class T1, class T2>
tuple_s<pair_s<T1, T2>> tuple_product(tuple_s<T1> t1, tuple_s<T2> t2){
	if (t1.size != t2.size) throw except_non_compatible("tuples dimentions are different");
	tuple_s<pair_s<T1, T2>> new_tuple;
	for (unsigned int i = 0; i < t1.size; ++i)
		new_tuple.add(pair_s<T1, T2>(t1[i], t2[i]));

	return new_tuple;
}

template<class Arg, class Res>
class continuous_function_on_linear_space{
	typedef Arg arg_type;
public:
	continuous_function_on_linear_space();
private:

};

template<class Arg, class Res>
continuous_function_on_linear_space<Arg, Res>::continuous_function_on_linear_space(){

}

template<class Ret, class Func, class ... Args>
class function{
public:
	function() : args_len(sizeof ... (Args)) {}
	Ret operator ()(Args ... args) { return f(args ...); }

	double integrate(double llim, double rlim, double step){
		double integ = 0;
		double t = llim;
		while (t < rlim){
			integ += step * f(t + step / 2);
			t += step;
		}
		return integ;
	}
	double derivative(double t, double step){
		return (f(t + step) - f(t)) / (step);
	}
	template<class ... T>
	tuple_s<double> grad(double step, T ... args){
		double* arr = new double[args_len];
		param_pack_toarray(0, arr, args ...);
		for (int i = 0; i < args_len; ++i){
			arr[i] = i;
		}
		tuple_s<double> tupl(arr, args_len);
		delete[] arr;
		return tupl;
	}

	const size_t args_len;
private:
	Func f;
};

template<class Func>
class runge_kutti{
public:
	runge_kutti(double t0_, vectorn y0_, int n) : y0(y0_) {
		t0 = t0_;
	}
	pair_l<pair_s<double, vectorn>*, int> approximate(double t_lim, double h, int max_pair_cnt = -1){
		int i = 0;
		int iter_cnt;
		if (max_pair_cnt >= 0) iter_cnt = max_pair_cnt;
		else iter_cnt = (t_lim - t0) / h;
		pair_s<double, vectorn>* pair_arr = new pair_s<double, vectorn>[max(max_pair_cnt, iter_cnt + 1)];
		vectorn yn(y0);
		double tn = t0;
		pair_arr[0] = pair_s<double, vectorn>(t0, y0);
		vectorn k1(y0), k2(y0), k3(y0), k4(y0), buf(y0);
			while (tn < t_lim && i++ < iter_cnt){
			k1 = f(tn, yn);
			buf = sum(yn, h / 2 * k1);
			k2 = f(tn + h / 2, buf);
			buf = sum(yn, h / 2 * k2);
			k3 = f(tn + h / 2, buf);
			buf = sum(yn, h*k3);
			k4 = f(tn + h, buf);
			yn = sum(yn, h / 6 * sum(k1, k2, k3, k4));
			tn = tn + h;
			pair_arr[i] = pair_s<double, vectorn>(tn, yn);
		}

		pair_l<pair_s<double, vectorn>*, int> ret(pair_arr, i);
		return ret;
	}
private:
	double t0;
	vectorn y0;
	Func f;
};

class diff_equation{
public:
	typedef vectorn(*func_type)(double, initializer_list<vectorn>);
	diff_equation(initializer_list<func_type> list) : func_list(list) {}

private:
	initializer_list<func_type> func_list;
};

template<class Arg, class Val>
class dots_function{
public:
	dots_function() : arr_len(0), arr(nullptr) {}
	~dots_function() { delete[] arr; }
	void write_to_file(const char* name){
		fstream f("functions_folder/" + name, ios::binary);
		pair_s<Arg, Val>* curr = arr;
		size_t remain = arr_len;
		size_t iter_cnt = 1000;
		Arg* buff_arg[1000];
		Arg* buff_res[1000];

		if (remain < iter_cnt) iter_cnt = remain;
		for (int i = 0; i < iter_cnt; ++i){
			buff_arg[i] = (*(curr + i)).argument;
			buff_res[i] = (*(curr + i)).result;
		}

		if (remain < 1000) remain = 0;
		else remain -= 1000;
		for (int i = 0; i < iter_cnt; ++i){
			f.write((Arg*)buff_arg + i, sizeof(Arg));
			f.write((Val*)buff_res + i, sizeof(Val));
		}
		f.close();
	}
	void operator = (pair_l<pair_s<Arg, Val>*, int> pl) {
		arr_len = pl.result;
		arr = new pair_s<Arg, Val>[arr_len];
		//copy_tf_with_allocation(&arr, pl.argument, arr_len);
		copy_tf(arr, pl.argument, arr_len);
	}
	void prints(){
		for (int i = 0; i < arr_len; ++i){
			cout << "{ " << arr[i].argument << ", " << arr[i].result << " }" << endl;
		}
	}
	size_t arr_len;
private:
	pair_s<Arg, Val>* arr;
};
