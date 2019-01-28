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

	void print_to_file(const char* name, const char* type);
	void read_from_file(const char* name, const char* type);

	void reset(int dim);

	bool is_empty() const;
	template<typename U>
	int is_compatible_with(const unlim_vector<U> &vect) const; // 0 - not compatible, 1 - full compatibility, 2 - not empty, equal size, but different types
	int get_dimention() const;
	double p_norme(int p) const;
	T max_norme() const;
	template<typename U>
	double scalar_product(unlim_vector<U> &vect) const;
	template<typename U>
	double angle_to(unlim_vector<U> &vect) const;
	void print(const char *str = "") const;
	int set(const vector<T> &vect);
	template<typename U>
	unlim_vector<U> convert_to(_type<U>&) const;
	template<typename U>
	unlim_vector<U> convert_to() const;

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

unlim_vector<char> empty_unlim_vector;

template<typename T>
unlim_vector<T>::unlim_vector() : vector_s(), vector_p(vector_s) {
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	empty = true;
	dimention = 0;
}

template<typename T>
unlim_vector<T>::unlim_vector(int dim_) : vector_p(vector_s) {
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	if (dim_ > 0) {
		vector_s.assign(dim_, (T)0);
		dimention = dim_;
		empty = false;
	}
	else {
		dimention = 0;
		empty = true;
	}
}

template<typename T>
void unlim_vector<T>::reset(int dim_) {
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	if (dim_ > 0) {
		vector_s.assign(dim_, (T)0);
		dimention = dim_;
		empty = false;
	}
	else {
		dimention = 0;
		empty = true;
	}
}

template<typename T>
unlim_vector<T>::unlim_vector(const vector<T> &vect) : vector_s(vect), vector_p(vector_s) {
	if (!int_convertable<T>()) throw except_vrong_type<T>();
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
	if (!int_convertable<T>()) throw except_vrong_type<T>();
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
	if (empty || dimention == 0)
		throw except_empty_container("Incorrect data or vector is empty", empty, dimention);
	for (auto it : vector_p) { d += (T)pow(it, p); }
	return pow((double)d, 1 / (double)p);
}

template<typename T>
T unlim_vector<T>::max_norme() const {
	T max = 0;
	if (empty || dimention == 0)
		throw except_empty_container("Incorrect data or vector is empty", empty, dimention);
	for (auto it : vector_p) { if (max < module(it))max = module(it); }
	return max;
}

template<typename T>
template<typename U>
double unlim_vector<T>::scalar_product(unlim_vector<U> &vect) const {
	if (!int_convertable<U>()) throw except_vrong_type<U>();
	double sum = 0;
	if (empty || vect.is_empty())
		throw except_empty_container("Vector is empty");
	if (dimention != vect.get_dimention())
		throw except_non_compatible("Vector have dimmerent dimentions");
	for (int i = 0; i < dimention; ++i) {
		sum += vector_s[i] * vect.vector_p[i];
	}
	return sum;
}

template<typename T>
template<typename U>
double unlim_vector<T>::angle_to(unlim_vector<U> &vect) const {
	if (!int_convertable<U>()) throw except_vrong_type<U>();
	if (empty || vect.is_empty())
		throw except_empty_container("Vector is empty");
	if (dimention != vect.get_dimention())
		throw except_non_compatible("Vector have dimmerent dimentions");
	double _arcos;
	_arcos = acos(scalar_product(vect) / (p_norme(2) * vect.p_norme(2)));
	return _arcos * 180 / PI;
}

template<typename T>
void unlim_vector<T>::print(const char *str) const {
	if (empty) {
		cout << "{ }";
		return;
	}
	int i = 0, size = vector_s.size();
	/*if (!size) {
	cout << "{ }";
	return;
	}*/
	cout << str << "{ ";
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
	}
	else {
		vector_s.empty();
		dimention = vect.size();
		vector_s.insert(vector_s.begin(), vect.begin(), vect.end());
		empty = false;
		return 1;
	}
	return 2;
}

template<typename T>
template<typename U>
unlim_vector<U> unlim_vector<T>::convert_to(_type<U>&) const {
	if (!int_convertable<U>()) throw except_vrong_type<T>();
	unlim_vector<U> empty_vect;
	vector<U> buf_vect;
	if (empty) return empty_vect;
	for (auto it : vector_s){
		buf_vect.push_back((U)it);
	}
	unlim_vector<U> new_vect(buf_vect);
	return new_vect;
}

template<typename T>
template<typename U>
unlim_vector<U> unlim_vector<T>::convert_to() const {
	if (!int_convertable<U>()) throw except_vrong_type<T>();
	unlim_vector<U> empty_vect;
	vector<U> buf_vect;
	if (empty) return empty_vect;
	for (auto it : vector_s){
		buf_vect.push_back((U)it);
	}
	unlim_vector<U> new_vect(buf_vect);
	return new_vect;
}

template<typename T>
template<class Iter, class BinaryFunction>
int unlim_vector<T>::for_each(Iter it, BinaryFunction f) {
	for (it = vector_s.begin(); it < vector_s.end(); ++it){ f(it); }
	return 0;
}

template<typename T>
template<class Iter, class BinaryFunction>
int unlim_vector<T>::for_(Iter first, Iter last, BinaryFunction f) {
	for (; first != last; ++first){ f(first); }
	return 0;
}

// OPERATORS =============================================================================

template<typename T>
unlim_vector<T> operator + (const unlim_vector<T> &vect1, const unlim_vector<T> &vect2) {
	unlim_vector<T> vect(vect1);
	if (!vect1.is_compatible_with(vect2)) return empty_unlim_vector.convert_to<T>();
	if (vect.get_dimention() != vect2.get_dimention()) return empty_unlim_vector.convert_to<T>();
	int dim = vect.get_dimention();
	for (int i = 0; i < dim; ++i){ vect.vector_p[i] += vect2.vector_p[i]; }
	return vect;
}

template<typename T>
unlim_vector<T> operator - (const unlim_vector<T> &vect1, const unlim_vector<T> &vect2) {
	unlim_vector<T> vect(vect1);
	if (!vect1.is_compatible_with(vect2)) return empty_unlim_vector.convert_to<T>();
	if (vect.get_dimention() != vect2.get_dimention()) return empty_unlim_vector.convert_to<T>();
	int dim = vect.get_dimention();
	for (int i = 0; i < dim; ++i){ vect.vector_p[i] -= vect2.vector_p[i]; }
	return vect;
}

template<typename T, typename D>
unlim_vector<T> operator * (const unlim_vector<T> &vect1, D mul) {
	unlim_vector<T> vect(vect1);
	if (vect1.is_empty() || vect1.get_dimention() == 0) return empty_unlim_vector.convert_to<T>();
	int dim = vect.get_dimention();
	for (int i = 0; i < dim; ++i){ vect.vector_p[i] = (int)(vect.vector_p[i] * mul); }
	return vect;
}

template<typename T, typename D>
unlim_vector<T> operator * (D mul, const unlim_vector<T> &vect1) {
	unlim_vector<T> vect(vect1);
	if (vect1.is_empty() || vect1.get_dimention() == 0) return empty_unlim_vector.convert_to<T>();
	int dim = vect.get_dimention();
	for (int i = 0; i < dim; ++i){ vect.vector_p[i] = (int)(vect.vector_p[i] * mul); }
	return vect;
}

template<typename D>
unlim_vector<D> operator * (const unlim_vector<int> &vect1, D mul) {
	unlim_vector<D> vect;
	if (vect1.is_empty() || vect1.get_dimention() == 0)
		return empty_unlim_vector.convert_to<D>();
	vect.vector_p.insert(vect.vector_p.begin(), vect1.vector_p.begin(), vect1.vector_p.end());
	int dim = vect1.get_dimention();
	for (int i = 0; i < dim; ++i){ vect.vector_p[i] = (D)vect.vector_p[i] * mul; }
	return vect;
}

template<typename D>
unlim_vector<D> operator * (D mul, const unlim_vector<int> &vect1) {
	unlim_vector<D> vect(vect1);
	if (vect1.is_empty() || vect1.get_dimention() == 0)
		return empty_unlim_vector.convert_to<D>();
	vect.vector_p.insert(vect.vector_p.begin(), vect1.vector_p.begin(), vect1.vector_p.end());
	int dim = vect1.get_dimention();
	for (int i = 0; i < dim; ++i){ vect.vector_p[i] = (D)vect.vector_p[i] * mul; }
	return vect;
}

/*template<typename T>
unlim_vector<T> operator * (unlim_vector<T> v1, unlim_vector<T> v2) {
if (!int_convertable<T>()) throw except_vrong_type<T>();
if (v1.is_empty() || v2.is_empty || v1.is_compatible_with(v2)) return empty_unlim_vector.convert_to<D>();
if (v1.get_dimention() != 3) return empty_unlim_vector.convert_to<T>();
unlim_vector<T> v(3);
return v;
}*/

unlim_vector<int> operator * (unlim_vector<int> &v1, unlim_vector<int> &v2) {
	if (!int_convertable<int>()) throw except_vrong_type<int>();
	if (v1.is_empty() || v2.is_empty() || !v1.is_compatible_with(v2)) return empty_unlim_vector.convert_to<int>();
	if (v1.get_dimention() != 3) return empty_unlim_vector.convert_to<int>();
	unlim_vector<int> v(3);
	v.vector_p[0] = v1.vector_p[1] * v2.vector_p[2] - v1.vector_p[2] * v2.vector_p[1];
	v.vector_p[1] = v1.vector_p[0] * v2.vector_p[2] - v1.vector_p[2] * v2.vector_p[0];
	v.vector_p[2] = v1.vector_p[0] * v2.vector_p[1] - v1.vector_p[1] * v2.vector_p[0];
	return v;
}

template<typename T>
void unlim_vector<T>::print_to_file(const char* name, const char* type) {
	if (string(type) == string("bin")){
		string str = string("vectors\\").append(name);
		ofstream f(name, ios::binary);
		if (!f) throw except_empty_container("empty file");

		f.write((char*)&dimention, sizeof(int));

		for (int i = 0; i < dimention; ++i) {
			f.write((char*)&vector_p[i], sizeof(vector_p[i]));
		}
		f.close();
	}
	if (string(type) == string("txt")){
		string str = string("vectors\\").append(name).append(".txt");

		ofstream f(str, ios::out);
		if (!f) throw except_empty_container("empty file");
		f << dimention << ' ';

		for (int i = 0; i < dimention; ++i){
			f << vector_p[i] << ' ';
		}
		f.close();
	}
}

template<typename T>
void unlim_vector<T>::read_from_file(const char* name, const char* type) {
	if (string(type) == string("bin")){
		int dim = 0;
		string str = string("vectors\\").append(name);

		ifstream f(name, ios::binary);
		if (!f) throw except_empty_container("empty file");
		f.read((char*)&dim, sizeof(int));

		reset(dim);
		for (int i = 0; i < dim; ++i){
			f.read((char*)&vector_p[i], sizeof(vector_p[i]));
		}
		f.close();
	}
	if (string(type) == string("txt")){
		int dim = 0;
		string str = string("vectors\\").append(name).append(".txt");

		ifstream f(str, ios::in);
		if (!f) throw except_empty_container("empty file");
		f >> dim;

		reset(dim);
		for (int i = 0; i < dim; ++i){
			f >> vector_p[i];
		}
		f.close();
	}
}

template<typename T>
void operator << (unlim_vector<T> &vec, const char* name) {
	int dim = vec.get_dimention();
	string str = string("matrices\\").append(name);
	ofstream f(name, ios::binary);
	if (!f) throw except_empty_container("empty file");

	f.write((char*)&dim, sizeof(int));

	for (int i = 0; i < dim; ++i) {
		f.write((char*)&(vec.vector_p[i]), sizeof(vec.vector_p[i]));
	}
	f.close();
}

template<typename T>
void operator >> (unlim_vector<T> &vec, const char* name) {
	int dim = 0;
	string str = string("matrices\\").append(name);

	ifstream f(name, ios::binary);
	if (!f) throw except_empty_container("empty file");
	f.read((char*)&dim, sizeof(int));

	vec.reset(dim);
	for (int i = 0; i < dim; ++i){
		f.read((char*)&vec.vector_p[i], sizeof(vec.vector_p[i]));
	}
	f.close();
}

template<typename T>
void operator << (unlim_vector<T> &vec, ofstream &f) {
	int dim = vec.get_dimention();
	if (!f) throw except_empty_container("empty file");

	f.write((char*)&dim, sizeof(int));

	for (int i = 0; i < dim; ++i) {
		f.write((char*)&vec.vector_p[i], sizeof(vec.vector_p[i]));
	}
	f.close();
}

template<typename T>
void operator >> (unlim_vector<T> &vec, ifstream &f) {
	int dim = 0;
	if (!f) throw except_empty_container("empty file");

	f.read((char*)&dim, sizeof(int));

	vec.reset(dim);
	for (int i = 0; i < dim; ++i){
		f.read((char*)&vec.vector_p[i], sizeof(vec.vector_p[i]));
	}
	f.close();
}

#endif
