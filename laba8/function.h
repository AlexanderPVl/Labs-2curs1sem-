#pragma once

#include <ostream>

#include "algorithms.h"
#include "exceptions.h"

template<class Arg, class Res>
struct pair_s{
	pair_s() = default;
	pair_s(Arg arg, Res res) : argument(arg), result(res){}
	Arg argument;
	Res result;
	typedef Arg arg_type;
	typedef Res res_type;
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
	Ret operator ()(Args ... args) { return func(args ...); }
	/*
	auto integrate(Args ... llim, Args ... rlim) -> decltype(is_of_type<double>(&llim ...)) {
		if (args_len != 1) return return_this(nan, 2.0);
		double dllim = return_last(llim ...);
		double drlim = return_last(rlim ...);
		//return (drlim - dllim) * func((drlim - dllim) / 2);
		return return_this(1, nan);
	}
	*/
	
	template<class Func, class ... Args>
	double integrate(Func f, Args ... args){
		auto res = do_if_of_type<double, decltype(return_func_type(__integrate__)), double>("trying to execute f1::integrate", __integrate__, args ..., args ...);
		//if (decltype(nan) == double) { cout << ">> non executed!" << endl; }
		//else { cout << ">> executed!" << endl; }
		return 1;
	}
	double __integrate__(double llim, double rlim){
		return rlim - llim;
	}

	const size_t args_len;
private:
	Func func;
};