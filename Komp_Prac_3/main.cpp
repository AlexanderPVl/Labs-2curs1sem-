#include <iomanip>
#include <iostream>
#include "unlim_vector.h"
#include "unlim_matrix.h"

typedef unlim_vector<double>::t::iterator d_vect_iterator;
typedef unlim_vector<float>::t::iterator f_vect_iterator;
typedef unlim_vector<int>::t::iterator i_vect_iterator;

template<class T>
void print(type_set<T>){
	cout << typeid(T).name();
}

void vector_test() {
	std::cout << "===============Vector test===============" << std::endl;
	unlim_vector<int> a;
	a.print();
	std::cout << std::endl;
	unlim_vector<double> b(5);
	b.print();
	std::cout << std::endl;
	//std::vector<double> v = {1,2,3,4,5,6,7,8};
	unlim_vector<double> c({ 1, 2, 0, 0, 0 });

	unlim_vector<double>::t::iterator it = c.vector_p.begin();
	c.for_each(it, [](d_vect_iterator it){*it = *it + 2; });
	c.for_(c.vector_p.begin() + 2, c.vector_p.end(), [](d_vect_iterator it){*it = *it - 7; });
	c.print();
	std::cout << std::endl << c.p_norme(2) << std::endl;
	(c + c).print(); std::cout << std::endl;
	std::cout << c.is_compatible_with(c) << std::endl;
	a.set({ 1, 2, 3 });
	(a * 3.414).print();
	cout << endl;

	std::cout << std::endl << std::endl;

	unlim_vector<int> d({ 1, 2, 3 });
}

void matrix_test() {
	std::cout << "===============Matrix test===============" << std::endl;
	unlim_matrix<int> matr1(3, 4);
	unlim_matrix<int> matr2({ { 1, 2, 3 }, { 2, 3, 4 }, { 3, 4, 5 } });
	matr1.print();
	matr2.print();

}

int main() {
	vector_test();
	matrix_test();
	print<int>(type_set<int>());

	return 0;
}
