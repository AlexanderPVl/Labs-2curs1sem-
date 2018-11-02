#ifndef UNLIM_MATRIX_H
#define UNLIM_MATRIX_H

#include "unlim_vector.h"

template<typename T>
class unlim_matrix{
public:
	unlim_matrix();
	unlim_matrix(int row_, int col_);
	unlim_matrix(vector<vector<T> > matr);

	bool is_correct() const;
	bool is_empty() const;
	void print() const;

	template<typename U>
	unlim_matrix<U> hadamard_product(unlim_matrix<U> matr) const;

	vector<vector <T> > &matrix_p;
private:
	vector<vector <T> > matrix_s;
	int row_cnt;
	int col_cnt;
	bool correct; // if empty => not correct
	bool empty;
};

unlim_matrix<char> empty_unlim_matrix;

template<typename T>
unlim_matrix<T>::unlim_matrix() : matrix_s(), matrix_p(matrix_s) {
	row_cnt = 0;
	col_cnt = 0;
	empty = true;
	correct = false;
}

template<typename T>
unlim_matrix<T>::unlim_matrix(int row_, int col_) : matrix_p(matrix_s) {
	int i;
	row_cnt = row_;
	col_cnt = col_;
	if (row_ == 0 || col_ == 0){
		empty = true;
		correct = false;
	}
	else {
		empty = false;
		correct = true;
		for (i = 0; i < row_; ++i){
			matrix_s.push_back(vector<T>(col_, 0));
		}
	}
}

template<typename T>
unlim_matrix<T>::unlim_matrix(vector<vector<T> > matr) : matrix_s(matr), matrix_p(matrix_s) {
	int col;
	if (matr.empty()) { empty = true; }
	else empty = false;
	col = matr[0].size();
	for (auto it : matr){
		if (it.size() != col) { correct = false; }
	}
}

template<typename T>
bool unlim_matrix<T>::is_correct() const { return correct; }

template<typename T>
bool unlim_matrix<T>::is_empty() const { return empty; }

template<typename T>
void unlim_matrix<T>::print() const {
	if (empty & !row_cnt && !col_cnt) {
		cout << "{ }";
	} else if (empty || !correct) {
		return;
	}
	for (auto v : matrix_s){
		for (auto vv : v){ cout << vv << " "; }
		cout << "\n";
	}
	cout << endl;
}

template<typename T>
template<typename U>
unlim_matrix<U> unlim_matrix<T>::hadamard_product(unlim_matrix<U> matr) const {
	if (empty || matr.empty)
		throw except_empty_container("Empty matrix");
	if (row_cnt != matr.row_cnt || col_cnt != matr.col_cnt)
		throw except_non_compatible("Different dimentions");
}

//HADAMARD_PRODUCT_SPECIALIZATION ======================

/*template<typename T>
template<int>
unlim_matrix<int> hadamard_product(unlim_matrix<int> matr) const {


}*/

//HADAMARD_PRODUCT_SPECIALIZATION ======================

#endif
