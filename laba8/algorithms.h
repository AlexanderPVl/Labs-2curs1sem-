#pragma once

#include <string>

template<class T>
void copy_tf(T* to, T* from, int n){
	for (int i = 0; i < n; ++i){
		to[i] = from[i];
	}
}

// returns type of parameter if it equals to expected else returns decltype(nan)

template<class T>
T is_of_type(T*) { return; }

template<class T>
decltype(nan) is_of_type(void*) { return nan; }

template<class T>
decltype(nan) is_of_type(...) { return nan; }

// do_if_of_type

template<class T>
void do_if_of_type(T*) { return; }

template<class T>
void do_if_of_type(void*) { return nan; }

template<class T>
void do_if_of_type(...) { return nan; }

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
