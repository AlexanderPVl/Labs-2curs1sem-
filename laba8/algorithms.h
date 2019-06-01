#pragma once

#include <string>
#include <ostream>

#include "exceptions.h"

using namespace std;

//

template<class T>
T dummy(T t){ return t; };
template<class T>
T square(T t){ return t*t; }

//

template<class T>
struct list_s{
	list_s(initializer_list<T> list) {
		int size = list.size();
		data = new T[size];
		int i = 0;
		for (auto it = list.begin(); it != list.end(); ++it, ++i) data[i] = *it;
	}
	T operator [](int i){ return data[i]; }
	T* data;
	size_t size;
};

template<class T>
void copy_tf(T* to, T* from, int n){
	for (int i = 0; i < n; ++i){
		to[i] = from[i];
	}
}

template<class T>
void copy_tf_with_allocation(T** to, T* from, int n){
	if (*to != nullptr) delete[] *to;
	*to = new T[n];
	for (int i = 0; i < n; ++i){
		(*to)[i] = from[i];
	}
}

template<class T>
void add_tf(T* to, T* from, int n){
	for (int i = 0; i < n; ++i){
		to[i] += from[i];
	}
}

template<class T>
void sub_tf(T* to, T* from, int n){
	for (int i = 0; i < n; ++i){
		to[i] -= from[i];
	}
}

template<class T, class Func>
void apply_tf(T* to, int n, Func f){
	for (int i = 0; i < n; ++i){
		to[i] = f(to[i]);
	}
}

template<class T, class Func>
T acummulate_tf(T* arr, T init_state, int n, Func f){
	T sum = init_state;
	for (int i = 0; i < n; ++i){ sum += f(arr[i]); }
	return sum;
}

template<class T>
T acummulate_tf(T* arr, T init_state, int n){
	T sum = init_state;
	for (int i = 0; i < n; ++i){ sum += arr[i]; }
	return sum;
}

template<class T>
void print_tf(T* arr, int n){
	for (int i = 0; i < n; ++i)
		cout << arr[i] << " ";
	cout << endl;
}

//

template<class T>
T* make_array(initializer_list<T> list){
	int size = list.size();
	T* newarr = new int[size];
	int i = 0;
	for (auto it = list.begin(); it != list.end(); ++it, ++i) newarr[i] = *it;
	return newarr;
}


template<class Func>
Func return_func_type(Func *f) { return f; }

// returns type of parameter if it equals to expected else returns decltype(nan)

template<class T>
T is_of_type(T*) { return; }

template<class T>
decltype(nan) is_of_type(void*) { return nan; }

template<class T>
decltype(nan) is_of_type(...) { return nan; }

// executes f if Compared_type equals to argument type

template<class Ret_type, class Func, class Compared_type, class ... Args>
Ret_type do_if_of_type(const char* message, Func *f, Compared_type*, Args ... args) { cout << "> " << message << endl; return f(args ...); }

template<class Ret_type, class Func, class Compared_type, class ... Args>
decltype(nan) do_if_of_type(const char* message, Func *f, void*, Args ... args) { cout << "> " << message << endl; return nan; }

template<class Ret_type, class Func, class Compared_type>
decltype(nan) do_if_of_type(const char* message, Func *f, ...) { cout << "> " << message << endl; return nan; }

// returns last element in parameter pack

template<class T>
T return_last(T t) { return t; }

template<class T, class ... Remainder>
auto return_last(T t, Remainder ... rem) -> decltype(return_last(rem ...)) { return return_last(rem ...); }

template<class T>
decltype(dummy<T>) return_last() { return dummy<T>; }

template<class T>
T return_on_pos(T t) { return t; }

template<class T, class ... Remainder>
T return_on_pos(int pos, T t, Remainder ... rem) { if (pos <= 0) return t; pos -= 1; return return_on_pos(pos, rem ...); }

// hz chto takoe, ne rabotaet

template<class T, class U>
T return_this(T t, T u) { return t; }

template<class T, class U>
U return_this(T t, U u) { return u; }

// transform parameter pack to different types

template<class T>
T* param_pack_toarray(int iter, T* arr, T t){
	arr[iter] = t;
	return arr;
}

template<class T, class ... Remainder>
T* param_pack_toarray(int iter, T* arr, T t, Remainder ... rem){
	arr[iter] = t;
	iter += 1;
	param_pack_toarray(iter, arr, rem ...);
	return arr;
}

template<class Func, class T> // executes Func f with parameter pack reestablished from array arr
void func_with_pack_args(Func f, int* iter, int max_iter, T* arr){ if (*iter >= max_iter) return; *iter += 1; func_with_pack_args(f, iter, max_iter, arr, arr[*iter]); }

template<class Func, class T, class ... Args>
void func_with_pack_args(Func f, int* iter, int max_iter, T* arr, Args ... args){
	if (*iter > max_iter) { f(args ...); }
	*iter += 1; func_with_pack_args(f, iter, max_iter, arr, args ...);
}

// special types

template<class L, class R>
struct type_list{
	typedef L left;
	typedef R right;
};

template<class F1, class F2, class F3>
struct func_tuple{
	func_tuple() {}
	template<int IND = 0>
	int get(){ return -1; }
	template<int IND = 1>
	F1 get(){ return; }
	template<int IND = 2>
	F2 get(){ return; }
	template<int IND = 3>
	F3 get(){ return; }
	F1 f1;
	F2 f2;
	F3 f3;
	F1 get_1(){ return f1; }
	F2 get_2(){ return f2; }
	F3 get_3(){ return f3; }
	//typedef type_list<type_list<T1, T2>, T3> tlist;
};

class vectorn{
public:
	vectorn(initializer_list<double> list, int size_ = 3);
	vectorn(const vectorn&);
	vectorn(int init, int size_);
	vectorn(){ size = 0; data = nullptr; }
	void add(vectorn);
	void add(double*);
	void operator += (vectorn);
	void operator -= (vectorn);
	void operator -= (double*);
	void operator *= (double);
	void operator /= (double);
	void operator = (vectorn);
	double& operator [](int);
	double* get_data();
	double norm();
	double dist(vectorn);
	vectorn dir(vectorn);
	void normalize();
	void prints(const char* str = "");
	int get_size() const { return size; }
private:
	size_t size;
	double* data;
};

vectorn::vectorn(initializer_list<double> list, int size_) {
	size = size_;
	data = new double[size];
	int i = 0;
	for (auto it = list.begin(); it != list.end() && i < size; ++it, ++i) data[i] = *it;
}
vectorn::vectorn(const vectorn &v) {
	size = v.size;
	data = new double[size];
	for (int i = 0; i < size; ++i) data[i] = v.data[i];
}
vectorn::vectorn(int init, int size_){
	size = size_;
	data = new double[size];
	for (int i = 0; i < size; ++i) data[i] = init;
}
void vectorn::add(vectorn v){
	if (size != v.size) return;
	add_tf(data, v.data, size);
}
void vectorn::add(double* data_){
	add_tf(data, data_, size);
}
void vectorn::operator += (vectorn v){
	if (size != v.size) return;
	add_tf(data, v.data, size);
}
void vectorn::operator -= (vectorn v){
	if (size != v.size) return;
	sub_tf(data, v.data, size);
}
void vectorn::operator -= (double* data_){
	sub_tf(data, data_, size);
}
void vectorn::operator *= (double d){
	apply_tf(data, size, [d](double it){ return it * d; });
}
void vectorn::operator /= (double d){
	apply_tf(data, size, [d](double it){ return it / d; });
}
void vectorn::operator = (vectorn v){
	if (data == nullptr || size != v.size){
		data = new double[v.size];
		size = v.size;
	}
	for (int i = 0; i < size; ++i){
		data[i] = v.data[i];
	}
}
double& vectorn::operator [](int i){ return data[i]; }
double* vectorn::get_data(){ return data; }
double vectorn::norm(){
	return sqrt(acummulate_tf<double>(data, 0, size, square<double>));
}
double vectorn::dist(vectorn v){
	vectorn vv(v);
	vv -= data;
	return vv.norm();
}
vectorn vectorn::dir(vectorn v){
	vectorn dir_(v);
	dir_ -= data;
	dir_.normalize();
	return dir_;
}
void vectorn::normalize(){
	double norm_ = norm();
	if (norm_ == 0) return;
	apply_tf(data, size, [norm_](double d){ return d / norm_; });
}
void vectorn::prints(const char* str){
	if (strcmp(str, "")){
		cout << str << ": ";
	}
	cout << "{ " ;
	for (int i = 0; i < size - 1; ++i){
		cout << data[i] << ", ";
	}
	cout << data[size - 1] << " }" << endl;
}

vectorn operator * (double d, const vectorn &vec){
	int dim = vec.get_size();
	vectorn newvec(vec);
	newvec *= d;
	return newvec;
}

vectorn operator * (const vectorn &vec, double d){
	int dim = vec.get_size();
	vectorn newvec(vec);
	newvec *= d;
	return newvec;
}

vectorn operator / (const vectorn &vec, double d){
	int dim = vec.get_size();
	vectorn newvec(vec);
	newvec /= d;
	return newvec;
}

vectorn operator / (double d, const vectorn &vec){
	int dim = vec.get_size();
	vectorn newvec(vec);
	newvec /= d;
	return newvec;
}

vectorn operator + (const vectorn &v1, const vectorn &v2){
	int dim = v1.get_size();
	vectorn newvec(v1);
	newvec += v2;
	return newvec;
}

vectorn operator - (const vectorn &v1, const vectorn &v2){
	int dim = v1.get_size();
	vectorn newvec(v1);
	newvec -= v2;
	return newvec;
}

vectorn sum(vectorn v){
	return v;
}

template<class ... Vec>
vectorn sum(vectorn v, Vec ... vecs){
	vectorn newvec(v);
	newvec + sum(vecs ...);
	return newvec;
}

void operator << (ostream &ost, vectorn v){
	cout << "{ ";
	size_t dim = v.get_size();
	for (int i = 0; i < dim - 1; ++i){
		cout << v[i] << ", ";
	}
	cout << v[dim - 1] << " }" << endl;
}



int min(int num){ return num; }

template<class ... Nums >
int min(int num, Nums ... nums){
	if (num < min(nums ...))
		return num;
	else
		return min(nums ...);
}

int max(int num){ return num; }

template<class ... Nums >
int max(int num, Nums ... nums){
	if (num > max(nums ...))
		return num;
	else
		return max(nums ...);
}
