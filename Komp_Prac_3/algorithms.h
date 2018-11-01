#ifndef ALGORITHMS_H
#define ALGORITHMS_H

template<class InputIt, class BinaryFunction>
int range_for(const InputIt first, const InputIt last, BinaryFunction f)
{
	Input it;
	for (it = first, it < last, ++it) f(it);
}

class NullType{};
struct EmptyType{};

template<class T>
struct type_set{
	type_set() {};
	typedef T type;
};

template<class T, class U>
struct TypeList{
	typedef T head;
	typedef U tail;
};

template<class T1, class T2, class T3>
struct TypeList3{
	typedef T1 u1;
	typedef T2 u2;
	typedef T3 u3;
};

#endif
