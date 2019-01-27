#include <iomanip>
#include <iostream>
#include "unlim_vector.h"
#include "derivative_matrix.h"

typedef unlim_vector<double>::t::iterator d_vect_iterator;
typedef unlim_vector<float>::t::iterator f_vect_iterator;
typedef unlim_vector<int>::t::iterator i_vect_iterator;

void vector_test() {
	std::cout << "===============Vector test===============" << std::endl << endl;
	/*unlim_vector<int> a;
	unlim_vector<int> e1({ 1, 0, 0 });
	unlim_vector<int> e2({ 0, 1, 0 });
	unlim_vector<int> e3({ 0, 0, 1 });
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
	cout << ">> angle: " << e1.angle_to(e2);
	std::cout << std::endl << std::endl;

	unlim_vector<float> d({ 1.1F, 2.2F, 3.3F });
	d.convert_to(_type<int>()).print();
	cout << endl << "scalar product: "<< d.scalar_product(unlim_vector<int>({ 1, 2, 3 }));
	cout << ((-1)*a).max_norme() << endl;
	cout << unlim_vector<int>({ 1, 1 }).p_norme(2);
	cout << endl;

	(e1 * e2).print();*/

	unlim_vector<double> c({ 1.32, 2.23, 0.1, 0.2, 0.33334 });
	unlim_vector<double> v1({ 1, 2, 3, 4, 5, 6, 7, 8 });
	unlim_vector<double> v2({ 1, 4, 5, 6, 7, 8 });
	unlim_vector<double> v3({ 9, 8, 7, 6, 5 });

	c.print_to_file("c", "txt");
	c.print_to_file("c", "bin");
	v1.read_from_file("c", "txt");
	v2.read_from_file("c", "bin");
	c.print("c:	");	cout << endl;
	v1.print("v1:	");	cout << endl;
	v2.print("v2:	"); cout << endl;

	v3 << "buf_vector";
	v1 >> "buf_vector";

	v3.print("v3:	"); cout << endl;
	v1.print("v1:	"); cout << endl;

	//FILE* f = fopen("vectors//test_file.bin", "w");
	//ofstream ofs("vectors//test_file", ios::binary);
	//ifstream ifs("vectors//test_file", ios::binary);

	//v3 << ofs;
	//v2 >> ifs;
	v2.print("v2:	"); cout << endl;

	cout << endl;
}

void matrix_test() {
	std::cout << endl << "===============Matrix test===============" << std::endl << endl;

	//FILE* f = fopen("matrices//test_file.txt", "w");
	//if (!f) throw except_empty_container("empty file");

	/*unlim_matrix<int> matr1(3, 3);
	unlim_matrix<float> matr2({ { 1.1f, 2, 3 },
	{ 2, 3.3f, 4 },
	{ 3, 4, 5.5f } });
	cout << ">> Matrix 1 (int):" << endl; matr1.print(' ', 3);
	cout << ">> Matrix 2 (float):" << endl; matr2.print(' ', 3);
	cout << ">> Hadamard product (matr1 * matr2):" << endl; matr2.hadamard_product(matr1).print(' ', 7);
	cout << ">> Matrix 2 convert from \'float\' to \'int\':" << endl; matr2.convert_to<int>().print(' ', 2);
	(matr2 + matr2).convert_to<int>().print();
	cout << ">> 7 * matr2:" << endl; (7 * matr2).print();
	cout << ">> tr(matr) = " << matr2.trace() << endl;
	cout << ">> tr({{1,1,1},{2,2,2},{3,3,3}}) = " << unlim_matrix<int>({ { 1, 1, 1 }, { 2, 2, 2 }, { 3, 3, 3 } }).trace();
	cout << endl;
	unlim_matrix<int> matr3({ { 1, 2, 3 }, { 2, 3, 4 }, { 3, 4, 5 }, { 4, 5, 6 } });
	unlim_matrix<int> matr4({ { 1, 2, 3, 4 }, { 2, 3, 4, 5 }, { 3, 4, 5, 6 } });
	cout << ">> matr3 * matr4:" << endl; (matr3 * matr4).print();
	matr3.print();
	matr3.algebr_compl(1, 1).print();
	unlim_matrix<int> matr5({ { 75, 35, 42, 87 }, { 24, 64, 58, 97 }, { 41, 25, 46, 88 }, { 64, 34, 31, 65 } });
	cout << ">> matr5 (int): " << endl; matr5.print();
	cout << ">> det(matr5) = " << determinant<int>(matr5) << endl << endl;
	unlim_ident_matrix<int> i_4(4);
	cout << ">> Product of identical matrixand some other matrix:" << endl; (i_4 * matr5).print();
	cout << ">> matr2 * matr2: " << endl; (matr2 * matr2).print();
	cout << ">> frobenius norme of matr2: " << matr2.frobenius_norme();
	unlim_matrix<double> inv_matr2(inverse<float>(matr2));
	cout << endl << ">> matr2^(-1):" << endl; inv_matr2.print();
	cout << ">> matr2 * matr2^(-1): " << endl; (matr2 * inv_matr2).print();
	unlim_matrix<double> d_matr2 = matr2.convert_to<double>();
	unlim_matrix<double> d_matr6 = d_matr2 * inv_matr2;
	cout << ">> 10^6 * matr2 * matr2^(-1): " << endl;
	(d_matr6 * 1000000).convert_to<int>().print();
	cout << ">> is {{1,2,3},{2,1,2},{3,2,1}} symmetric?: ";
	cout << unlim_matrix<int>({ { 1, 2, 3 }, { 2, 1, 2 }, { 3, 2, 1 } }).is_symmetric();
	cout << endl;
	unlim_symmetric_matrix<int> a(unlim_matrix<int>({ { 1, 2, 3 }, { 2, 1, 2 }, { 3, 2, 1 } }));
	unlim_symmetric_matrix<int> b(a);
	a.print();*/

	unlim_matrix<int> i_matr1({ { 1, 1, 1 }, { 0, 2, 2 }, { 0, 0, 3 } });
	unlim_matrix<int> i_matr2({ { 1, 2, 2 }, { 2, 4, 4 }, { 1, 2, 3 } });
	unlim_matrix<int> i_matr3({ { 1, 2, 5 }, { 5, 4, 4 }, { 5, 5, 5 } });

	/*unlim_upptriang_matrix<int> uptr1(i_matr1);
	unlim_lowtriang_matrix<int> lotr1(i_matr2);
	uptr1.print();
	lotr1.print();
	(lotr1 + uptr1).print();
	matr5.transpose().print();
	unlim_vector<int> i_vect1({ 1, 2, 3 });
	(matr3 * i_vect1).print();
	cout << endl;
	cout << "\nRank = " << matr_rank(i_matr2);
	//determinant<int>(matr3);
	inverse<int>(matr5).print();*/
	
	unlim_matrix<float> matr2({ { 1.1f, 2, 3 }, { 2, 3.3f, 4 }, { 3, 4, 5.5f } });

	i_matr1.print_to_file("int_matrix_19", "txt");
	i_matr2.read_from_file("int_matrix_19", "txt");

	cout << "i_matr2:" << endl; i_matr2.print();
	cout << endl;
	cout << "i_matr1:" << endl; i_matr1.print();

	i_matr3 << "new_matrix";
	i_matr2 >> "new_matrix";

	cout << "i_matr2:" << endl; i_matr2.print();

	ofstream ofs("matrices\\int_matrix_2", ios::binary);
	ifstream ifs("matrices\\int_matrix_2", ios::binary);

	i_matr1 << ofs;
	i_matr2 >> ifs;

	cout << "i_matr2:" << endl; i_matr2.print();

	cout << endl << "===============End of test===============" << endl;
	
}

void convert_to_int() {
	cout << "Checking convertability of standart types to int (0 - false, 1 - true)";
	cout << endl << "char to int: " << int_convertable<char>();
	cout << endl << "float to int: " << int_convertable<float>();
	cout << endl << "double to int: " << int_convertable<double>();
	cout << endl << "void to int: " << int_convertable<void>();
	cout << endl << endl;
}

int main() {
	cout << "Program start." << endl << endl;

	system("MD vectors");
	system("MD matrices");

	convert_to_int();
	vector_test();
	matrix_test();

	cout << endl << endl << "Program ran to the end" << endl;

	return 0;
}
