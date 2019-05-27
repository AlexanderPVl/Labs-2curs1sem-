#pragma once

#include <string>

template<class T>
void copy_tf(T* to, T* from, int n){
	for (int i = 0; i < n; ++i){
		to[i] = from[i];
	}
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

// hz chto takoe, ne rabotaet

template<class T, class U>
T return_this(T t, T u) { return t; }

template<class T, class U>
U return_this(T t, U u) { return u; }

// transform parameter pack to different types

template<class T>
T* param_pack_toarray(int* iter, T* arr, T t){
	arr[*iter] = t;
	return arr;
}

template<class T, class ... Remainder>
T* param_pack_toarray(int* iter, T* arr, T t, Remainder ... rem){
	arr[*iter] = t;
	*iter += 1;
	param_pack_toarray(iter, arr, rem ...);
	return arr;
}