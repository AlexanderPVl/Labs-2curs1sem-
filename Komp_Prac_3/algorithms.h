#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <math.h>

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

template<typename T>
T module(T var) { return (var > 0) ? var : -var; }

const double _eps = 1E-12;

#endif
