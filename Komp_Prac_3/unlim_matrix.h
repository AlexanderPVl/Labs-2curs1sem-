#ifndef UNLIM_MATRIX_H
#define UNLIM_MATRIX_H

#include "unlim_vector.h"

template<typename T>
class unlim_matrix{
public:
	unlim_matrix();
	unlim_matrix(int row_, int col_);
	unlim_matrix(vector<vector<T> > matr);
	unlim_matrix(vector<vector<T> > &matr);
	unlim_matrix(vector<vector<T> > &matr, bool ref_only); // forbid using object-copying constructor
	unlim_matrix(unlim_matrix<T> &matr);
	~unlim_matrix() = default;

	int get_row_cnt() const;
	int get_col_cnt() const;
	void set_row_cnt(int cnt);
	void set_col_cnt(int cnt);
	void set_correct(bool correct_);
	void set_empty(bool empty_);

	bool is_correct() const;
	bool is_empty() const;
	template<typename U>
	int is_compatible_with(const unlim_matrix<U> &vect) const;
	template<typename U>
	unlim_matrix<U> convert_to(_type<U>&);
	void print(char sep = ' ', int setw_arg = 1) const;

	template<typename U>
	unlim_matrix<U> hadamard_product(unlim_matrix<U> &matr) const;

	vector<vector <T> > &matrix_p;
private:
	vector<vector <T> > matrix_s;
	int row_cnt;
	int col_cnt;
	bool correct; // if empty => not correct
	bool empty;
};

unlim_matrix<char> empty_unlim_matrix;

//< CONSTRUCTORS===============================================================

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
	correct = true;
	for (auto it : matr){
		if (it.size() != col) { correct = false; }
	}
	if (correct == false){
		row_cnt = 0;
		col_cnt = 0;
	} else {
		row_cnt = matr.size();
		col_cnt = matr[0].size();
	}
}

template<typename T>
unlim_matrix<T>::unlim_matrix(vector<vector<T> > &matr) : matrix_s(matr), matrix_p(matrix_s) {
	int col;
	if (matr.empty()) { empty = true; }
	else empty = false;
	col = matr[0].size();
	for (auto it : matr){
		if (it.size() != col) { correct = false; }
	}
}

template<typename T>
unlim_matrix<T>::unlim_matrix(vector<vector<T> > &matr, bool ref_only) : matrix_s(matr), matrix_p(matrix_s) {
	int col;
	if (matr.empty()) { empty = true; }
	else empty = false;
	col = matr[0].size();
	for (auto it : matr){
		if (it.size() != col) { correct = false; }
	}
}

template<typename T>
unlim_matrix<T>::unlim_matrix(unlim_matrix<T> &matr) : matrix_s(matr.matrix_s), matrix_p(matrix_s) {
	empty = matr.empty;
	correct = matr.correct;
	row_cnt = 0;
	col_cnt = 0;
	if (!empty && correct) {
		row_cnt = matr.row_cnt;
		col_cnt = matr.col_cnt;
	}
}

//CONSTRUCTORS=============================================================== />

template<typename T>
int unlim_matrix<T>::get_row_cnt() const { return row_cnt; }

template<typename T>
int unlim_matrix<T>::get_col_cnt() const { return col_cnt; }

template<typename T>
void unlim_matrix<T>::set_row_cnt(int cnt) { row_cnt = cnt; }

template<typename T>
void unlim_matrix<T>::set_col_cnt(int cnt) { col_cnt = cnt; }

template<typename T>
void unlim_matrix<T>::set_correct(bool correct_) { correct = correct_; }

template<typename T>
void unlim_matrix<T>::set_empty(bool empty_) { empty = empty_; }

template<typename T>
bool unlim_matrix<T>::is_correct() const { return correct; }

template<typename T>
bool unlim_matrix<T>::is_empty() const { return empty; }

template<typename T>
template<typename U>
int unlim_matrix<T>::is_compatible_with(const unlim_matrix<U> &vect) const {

}

template<typename T>
template<typename U>
unlim_matrix<U> unlim_matrix<T>::convert_to(_type<U>&){
	int i, j;
	vector<vector<U> > buf_matr;
	unlim_matrix<U> empty_matr;
	if (empty || !correct)return empty_matr;
	for (i = 0; i < row_cnt; ++i){
		buf_matr.push_back(vector<U>());
		for (j = 0; j < col_cnt; ++j){
			buf_matr[i].push_back((U)matrix_s[i][j]);
		}
	}
	for (i = 0; (unsigned int)i < buf_matr.size(); ++i){
		for (j = 0; (unsigned int)j < buf_matr[0].size(); ++j){ buf_matr[i][j] = (U)matrix_s[i][j]; }
	}
	unlim_matrix<U> new_matr(buf_matr, true);
	new_matr.set_empty(empty);
	new_matr.set_correct(correct);
	new_matr.set_row_cnt(row_cnt);
	new_matr.set_col_cnt(col_cnt);
	return new_matr;
}

template<typename T>
void unlim_matrix<T>::print(char sep, int setw_arg) const {
	if (empty & !row_cnt && !col_cnt) {
		cout << "{ }";
	} else if (empty || !correct) {
		return;
	}
	for (auto v : matrix_s){
		for (auto vv : v){ cout << left << setw(setw_arg); cout << vv << sep; }
		cout << "\n";
	}
	cout << endl;
}

template<typename T>
template<typename U>
unlim_matrix<U> unlim_matrix<T>::hadamard_product(unlim_matrix<U> &matr) const {
	int i, j;
	unlim_matrix<U> conv_matr(matr.convert_to(_type<U>()));
	if (empty || conv_matr.is_empty()) { return empty_unlim_matrix.convert_to(_type<U>()); }
	if (row_cnt != conv_matr.get_row_cnt() || col_cnt != conv_matr.get_col_cnt()) { return empty_unlim_matrix.convert_to(_type<U>()); }
	unlim_matrix<U> new_matr(row_cnt, col_cnt);
	for (i = 0; i < row_cnt; ++i){
		for (j = 0; j < col_cnt; ++j){
			new_matr.matrix_p[i][j] = (U)matrix_p[i][j] * conv_matr.matrix_p[i][j];
		}
	}
	return new_matr;
}

// OPERATORS ======================================================
template<typename T, typename U>
unlim_matrix<T> operator + (unlim_matrix<T> &matr1, unlim_matrix<U> &matr2) {
	unlim_matrix<T> matr(matr1);
	if (matr1.is_empty() || matr2.is_empty() || !matr1.is_correct() || !matr2.is_correct()) return empty_unlim_matrix.convert_to(_type<T>);
}

#endif
