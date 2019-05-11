#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <math.h>
#include <Windows.h>

#define TYPELIST_3(T1, T2, T3) TypeList< T1, TypeList<T2, T3> >
#define PI 3.1415926535

template<class InputIt, class BinaryFunction>
int range_for(const InputIt first, const InputIt last, BinaryFunction f)
{
	Input it;
	for (it = first, it < last, ++it) f(it);
}

class NullType{};
struct EmptyType{};

template<class T>
struct _type{
	_type() = default;
	typedef T type;
};

typedef char Small;
struct Big{ char dummy[2]; };
Small TestU(int);
Big TestU(...);
template<class T>
T make_t();
template<class T>
bool int_convertable() { return sizeof(TestU(make_t<T>())) == 1; }
template<>
bool int_convertable<void>() { return 0; }

template<class T, class U>
struct TypeList{
	typedef T head;
	typedef U tail;
};

template<class T>
struct three_tuple
{
	three_tuple(){ is_empty = true; }
	three_tuple(T t1_, T t2_, T t3_){ t1 = t1_, t2 = t2_, t3 = t3_; is_empty = false; }
	void print(){ cout << t1 << endl << t2 << endl << t3 << endl; }
	void operator = (three_tuple<T> t){ t1 = t.t1; t2 = t.t2; t3 = t.t3; is_empty = t.is_empty; }
	T operator [](int j) { if (j == 0) return t1; if (j == 1) return t2; if (j == 2) return t3; throw except_index_out_of_range(j); }
	T t1, t2, t3;
	bool is_empty;
};

template<typename T>
T module(T var) { return (var > 0) ? var : -var; }

const double _eps = 1E-12;

#endif
