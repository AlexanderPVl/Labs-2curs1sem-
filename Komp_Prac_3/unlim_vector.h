#ifndef UNLIM_VECTOR_H
#define UNLIM_VECTOR_H

#include <vector>
#include "algorithms.h"
#include "exceptions.h"

template<typename T> class unlim_vector;

template<typename T>
class unlim_vector {
public:
	unlim_vector();
	unlim_vector(int dim_);
	unlim_vector(const vector<T> &vect);
	unlim_vector(const unlim_vector<T> &vect);
	~unlim_vector() = default;

	typedef vector<T> t;

	bool is_empty() const;
	template<typename U>
	int is_compatible_with(const unlim_vector<U> &vect) const; // 0 - not compatible, 1 - full compatibility, 2 - compatible, but different types
	int get_dimention() const;
	double p_norme(int p) const;
	void print() const;
	int set(const vector<T> &vect);

	template<class Iter, class BinaryFunction>
	int for_each(Iter it, BinaryFunction f);
	template<class Iter, class BinaryFunction>
	int for_(Iter first, Iter last, BinaryFunction f);

	vector<T> &vector_p;
private:
	vector<T> vector_s;
	int dimention;
	bool empty;
};

template<typename T>
unlim_vector<T>::unlim_vector() : vector_s(), vector_p(vector_s) {
	empty = true;
	dimention = 0;
}

template<typename T>
unlim_vector<T>::unlim_vector(int dim_) : vector_p(vector_s) {
	if (dim_ > 0) {
		vector_s.assign(dim_, (T)0);
		empty = false;
	} else {
		dimention = 0;
		empty = true;
	}
}

template<typename T>
unlim_vector<T>::unlim_vector(const vector<T> &vect) : vector_s(vect), vector_p(vector_s) {
	dimention = vect.size();
	if (vect.empty()){
		dimention = 0;
		empty = true;
	}
	else{
		dimention = vect.size();
		empty = false;
	}
}

template<typename T>
unlim_vector<T>::unlim_vector(const unlim_vector<T> &vect) : vector_s(vect.vector_s), vector_p(vector_s) {
	empty = vect.empty;
	dimention = vect.dimention;
}

template<typename T>
bool unlim_vector<T>::is_empty() const { return empty; }

template<typename T>
template<typename U>
int unlim_vector<T>::is_compatible_with(const unlim_vector<U> &vect) const {
	if (empty || vect.is_empty())return 0;
	if (dimention != vect.get_dimention())return 0;
	if (typeid(T) == typeid(U)) return 1;
	return 2;
}

template<typename T>
int unlim_vector<T>::get_dimention() const {
	return dimention;
}

template<typename T>
double unlim_vector<T>::p_norme(int p) const {
	T d = 0;
	if (dimention == 0) return 0;
	for (auto it : vector_p) { d += it*it; }
	return sqrt((double)d);
}

template<typename T>
void unlim_vector<T>::print() const {
	int i = 0, size = vector_s.size();
	if (!size) {
		cout << "{ }";
		return;
	}
	cout << "{ ";
	for (unsigned int i = 0; i < vector_s.size() - 1; ++i){
		cout << vector_s[i] << ", ";
	}
	cout << vector_s[size - 1] << " }";
}

template<typename T>
int unlim_vector<T>::set(const vector<T> &vect) {
	if (vect.empty()) {
		vector_s.clear();
		dimention = 0;
		empty = true;
		return 0;
	} else {
		vector_s.empty();
		dimention = vect.size();
		vector_s.insert(vector_s.begin(), vect.begin(), vect.end());
		empty = false;
		return 1;
	}
	return 2;
}

template<typename T>
template<class Iter, class BinaryFunction>
int unlim_vector<T>::for_each(Iter it, BinaryFunction f) {
	for (it = vector_s.begin(); it < vector_s.end(); ++it){ f(it); }
	return 0;
}

template<typename T>
template<class Iter, class BinaryFunction>
int unlim_vector<T>::for_(Iter first, Iter last, BinaryFunction f){
	for (; first != last; ++first){ f(first); }
	return 0;
}

template<typename T>
unlim_vector<T> operator + (const unlim_vector<T> &vect1, const unlim_vector<T> &vect2) {
	unlim_vector<T> empty;
	unlim_vector<T> vect(vect1);
	if (!vect1.is_compatible_with(vect2)) return empty;
	if (vect.get_dimention() != vect2.get_dimention()) return empty;
	int dim = vect.get_dimention();
	for (int i = 0; i < dim; ++i){ vect.vector_p[i] += vect2.vector_p[i]; }
	return vect;
}

template<typename T>
unlim_vector<T> operator - (const unlim_vector<T> &vect1, const unlim_vector<T> &vect2) {
	unlim_vector<T> empty;
	unlim_vector<T> vect(vect1);
	if (!vect1.is_compatible_with(vect2)) return empty;
	if (vect.get_dimention() != vect2.get_dimention()) return empty;
	int dim = vect.get_dimention();
	for (int i = 0; i < dim; ++i){ vect.vector_p[i] -= vect2.vector_p[i]; }
	return vect;
}

template<typename T, typename D>
unlim_vector<T> operator * (const unlim_vector<T> &vect1, D mul) {
	unlim_vector<T> empty;
	unlim_vector<T> vect(vect1);
	if (vect1.is_empty() || vect1.get_dimention() == 0) return empty;
	int dim = vect.get_dimention();
	for (int i = 0; i < dim; ++i){ vect.vector_p[i] = (int)(vect.vector_p[i] * mul); }
	return vect;
}

template<typename D>
unlim_vector<D> operator * (const unlim_vector<int> &vect1, D mul) {
	unlim_vector<D> empty;
	unlim_vector<D> vect;
	if (vect1.is_empty() || vect1.get_dimention() == 0)
		return empty;
	vect.vector_p.insert(vect.vector_p.begin(), vect1.vector_p.begin(), vect1.vector_p.end());
	int dim = vect1.get_dimention();
	for (int i = 0; i < dim; ++i){ vect.vector_p[i] = (D)vect.vector_p[i] * mul; }
	return vect;
}

#endif
