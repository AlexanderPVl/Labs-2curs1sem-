#include <iomanip>
#include <iostream>
#include "unlim_vector.h"
#include "unlim_matrix.h"

typedef unlim_vector<double>::t::iterator d_vect_iterator;
typedef unlim_vector<float>::t::iterator f_vect_iterator;
typedef unlim_vector<int>::t::iterator i_vect_iterator;

template<class T>
void print(_type<T>){
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

	unlim_vector<float> d({ 1.1F, 2.2F, 3.3F });
	d.convert_to(_type<int>()).print();
	cout << endl << "scalar product: "<< d.scalar_product(unlim_vector<int>({ 1, 2, 3 }));
	cout << endl;
}

void matrix_test() {
	std::cout << endl << "===============Matrix test===============" << std::endl;
	unlim_matrix<int> matr1(3, 3);
	unlim_matrix<float> matr2({ { 1.1f, 2, 3 },
	                            { 2, 3.3f, 4 },
							    { 3, 4, 5.5f } });
	cout << "Matrix 1 (int):" << endl; matr1.print(' ', 3);
	cout << "Matrix 2 (float):" << endl; matr2.print(' ', 3);
	cout << "Hadamard product:" << endl; matr2.hadamard_product(matr1).print(' ', 7);
	cout << "Matrix 2 convert from \'float\' to \'int\':" << endl; matr2.convert_to(_type<int>()).print(' ', 2);
}

int main() {
	vector_test();
	matrix_test();
	print<int>(_type<int>());

	return 0;
}
