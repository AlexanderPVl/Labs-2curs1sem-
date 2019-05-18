#ifndef UNLIM_MATRIX_H
#define UNLIM_MATRIX_H

#include "unlim_vector.h"
#include <future>
#include <mutex>

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

	void print_to_file(const char* name, const char* type); // "bin" or "txt"
	void read_from_file(const char* name, const char* type);

	int get_row_cnt() const;
	int get_col_cnt() const;
	void set_row_cnt(int cnt);
	void set_col_cnt(int cnt);
	void set_correct(bool correct_);
	void set_empty(bool empty_);
	void reset(int row_, int col_);
	void reset(vector<vector<T> > &matr);
	void append_row(vector<T> v);
	void append_col(vector<T> v);
	void add_row_to_row(int i, int j, double mult = 1, int start_from = 0);
	void mult_row_on(int row, double n);

	bool is_correct() const;
	bool is_empty() const;
	bool is_square() const;
	bool is_identical() const;
	bool is_symmetric() const;
	bool is_upptriangle() const;
	bool is_lowtriangle() const;
	template<typename U>
	int is_compatible_with(const unlim_matrix<U> &matr) const;
	template<typename U>
	unlim_matrix<U> convert_to();
	template<typename U>
	unlim_matrix<U> convert_to(_type<U>&);
	unlim_vector<T> convert_to_vector();
	void print(char sep = ' ', int setw_arg = 1) const;
	T row_sum(int j);
	T col_sum(int j);

	template<typename U>
	unlim_matrix<U> hadamard_product(unlim_matrix<U> &matr) const;
	double frobenius_norme() const;
	T trace() const;
	unlim_matrix<T> algebr_compl(int row, int col);
	unlim_matrix<T> transpose();
	int rank() const;
	friend T determinant(unlim_matrix<T>& matr);
	friend unlim_matrix<double> inverse(unlim_matrix<T> &matr);
	void make_identical(int n);

	vector<T>& operator [](int ind);
	vector<T> operator ()(int ind);
	void operator = (unlim_matrix<T> &matr);
	void operator = (unlim_vector<T> &v);
	void operator = (vector<T> &v);
	void operator / (T);

	vector<vector <T> > &matrix_p;
protected:
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
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	row_cnt = 0;
	col_cnt = 0;
	empty = true;
	correct = false;
}

template<typename T>
unlim_matrix<T>::unlim_matrix(int row_, int col_) : matrix_p(matrix_s) {
	if (!int_convertable<T>()) throw except_vrong_type<T>();
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
void unlim_matrix<T>::reset(int row_, int col_) {
	matrix_s.clear();
	if (!int_convertable<T>()) throw except_vrong_type<T>();
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
void unlim_matrix<T>::reset(vector<vector<T> > &matr) {
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	int col;
	if (matr.empty()) { empty = true; }
	else empty = false;
	correct = true;
	col = matr[0].size();
	for (auto it : matr){
		if (it.size() != col) { correct = false; }
	}
	if (correct == false){
		row_cnt = 0;
		col_cnt = 0;
	}
	else {
		row_cnt = matr.size();
		col_cnt = matr[0].size();
	}
	reset(row_cnt, col_cnt);
	for (int i = 0; i < row_cnt; ++i){
		for (int j = 0; j < col_cnt; ++j){
			matrix_s[i][j] = matr[i][j];
		}
	}
}

template<typename T>
void unlim_matrix<T>::append_row(vector<T> v){
	if (empty){
		reset(1, v.size());
		for (int i = 0; i < col_cnt; ++i) matrix_s[0][i] = v[i];
		return;
	}
	if (v.size() != col_cnt) return;
	unlim_matrix<T> buf(matrix_s, 1);
	buf.reset(row_cnt + 1, col_cnt);
	for (int i = 0; i < row_cnt; ++i){
		for (int j = 0; j < col_cnt; ++j){
			buf[i][j] = matrix_s[i][j];
		}
	}
	for (int i = 0; i < col_cnt; ++i) buf[row_cnt][i] = v[i];
	reset(row_cnt + 1, col_cnt);
	for (int i = 0; i < row_cnt; ++i){
		for (int j = 0; j < col_cnt; ++j){
			matrix_s[i][j] = buf[i][j];
		}
	}
}

template<typename T>
void unlim_matrix<T>::append_col(vector<T> v){
	if (empty){
		reset(v.size(), 1);
		for (int i = 0; i < row_cnt; ++i) matrix_s[i][0] = v[i];
		return;
	}
	if (v.size() != row_cnt) return;
	unlim_matrix<T> buf(matrix_s, 1);
	buf.reset(row_cnt, col_cnt + 1);
	for (int i = 0; i < row_cnt; ++i){
		for (int j = 0; j < col_cnt; ++j){
			buf[i][j] = matrix_s[i][j];
		}
	}
	for (int i = 0; i < row_cnt; ++i) buf[i][col_cnt] = v[i];
	reset(row_cnt, col_cnt + 1);
	for (int i = 0; i < row_cnt; ++i){
		for (int j = 0; j < col_cnt; ++j){
			matrix_s[i][j] = buf[i][j];
		}
	}
}

template<typename T>
void unlim_matrix<T>::add_row_to_row(int i, int j, double mult, int start_from){
	if (i >= row_cnt || j >= row_cnt) return;
	for (int k = start_from; k < col_cnt; ++k){
		matrix_p[j][k] += matrix_p[i][k] * mult;
	}
}

template<typename T>
void unlim_matrix<T>::mult_row_on(int row, double n){
	for (int k = 0; k < col_cnt; ++k){
		matrix_p[row][k] *= n;
	}
}

template<typename T>
unlim_matrix<T>::unlim_matrix(vector<vector<T> > matr) : matrix_s(matr), matrix_p(matrix_s) {
	if (!int_convertable<T>()) throw except_vrong_type<T>();
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
	}
	else {
		row_cnt = matr.size();
		col_cnt = matr[0].size();
	}
}

template<typename T>
unlim_matrix<T>::unlim_matrix(vector<vector<T> > &matr) : matrix_s(matr), matrix_p(matrix_s) {
	if (!int_convertable<T>()) throw except_vrong_type<T>();
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
	if (!int_convertable<T>()) throw except_vrong_type<T>();
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
	if (!int_convertable<T>()) throw except_vrong_type<T>();
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
bool unlim_matrix<T>::is_square() const {
	if (empty || !correct || row_cnt != col_cnt) return false;
	else return true;
}

template<typename T>
bool unlim_matrix<T>::is_identical() const {
	if (!is_square()) return false;
	int i, j;
	for (i = 0; i < row_cnt; ++i) {
		for (j = 0; j < i; ++j) { if (matrix_s[i][j] != 0) return false; }
		for (j = i + 1; j < col_cnt; ++j) { if (matrix_s[i][j] != 0) return false; }
		if (matrix_s[i][i] != 1)return false;
	}
	return true;
}

template<typename T>
bool unlim_matrix<T>::is_symmetric() const {
	if (!is_square()) return false;
	int i, j;
	for (i = 0; i < row_cnt; ++i) {
		for (j = 0; j < i; ++j) { if (matrix_s[i][j] != matrix_s[j][i]) return false; }
	}
	return true;
}

template<typename T>
bool unlim_matrix<T>::is_upptriangle() const {
	if (!is_square()) return false;
	int i, j;
	for (i = 0; i < row_cnt; ++i) {
		for (j = 0; j < i; ++j) { if (matrix_s[i][j] != 0) return false; }
	}
	return true;
}

template<typename T>
bool unlim_matrix<T>::is_lowtriangle() const {
	if (!is_square()) return false;
	int i, j;
	for (i = 0; i < row_cnt; ++i) {
		for (j = i + 1; j < col_cnt; ++j) { if (matrix_s[i][j] != 0) return false; }
	}
	return true;
}

template<typename T>
template<typename U>
int unlim_matrix<T>::is_compatible_with(const unlim_matrix<U> &matr) const {
	if (empty || matr.is_empty() || !correct || !matr.is_correct()) return 0;
	if (typeid(T) == typeid(U)) return 1;
	else return 2;
}

template<typename T>
template<typename U>
unlim_matrix<U> unlim_matrix<T>::convert_to(){
	if (!int_convertable<U>()) throw except_vrong_type<T>();
	int i, j;
	vector<vector<U> > buf_matr;
	unlim_matrix<U> empty_matr;
	if (!int_convertable<U>()) throw except_vrong_type<U>();
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
template<typename U>
unlim_matrix<U> unlim_matrix<T>::convert_to(_type<U>&){
	if (!int_convertable<U>()) throw except_vrong_type<T>();
	int i, j;
	vector<vector<U> > buf_matr;
	unlim_matrix<U> empty_matr;
	if (!int_convertable<U>()) throw except_vrong_type<U>();
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
unlim_vector<T> unlim_matrix<T>::convert_to_vector(){
	if (row_cnt != 1 && col_cnt != 1 || !col_cnt || !row_cnt) return empty_unlim_vector.convert_to<T>();
	unlim_vector<T> v(max(row_cnt, col_cnt));
	if (row_cnt == 1){
		for (int i = 0; i < col_cnt; ++i) v[i] = matrix_s[0][i];
	}
	if (col_cnt == 1){
		for (int i = 0; i < row_cnt; ++i) v[i] = matrix_s[i][0];
	}
	return v;
}

template<typename T>
void unlim_matrix<T>::print(char sep, int setw_arg) const {
	if (empty || !correct) {
		cout << "{ }";
		return;
	}
	for (auto v : matrix_s){
		for (auto vv : v){ cout << left << setw(setw_arg); cout << vv << sep; }
		cout << "\n";
	}
	cout << endl;
}

template<typename T>
T unlim_matrix<T>::row_sum(int j){
	if (j >= row_cnt || j < 0) throw except_index_out_of_range(j);
	T sum = 0;
	for (int i = 0; i < col_cnt; ++i){
		sum += matrix_s[j][i];
	}
	return sum;
}

template<typename T>
T unlim_matrix<T>::col_sum(int j){
	if (j >= col_cnt || j < 0) throw except_index_out_of_range(j);
	T sum = 0;
	for (int i = 0; i < row_cnt; ++i){
		sum += matrix_s[i][j];
	}
	return sum;
}

template<typename T>
template<typename U>
unlim_matrix<U> unlim_matrix<T>::hadamard_product(unlim_matrix<U> &matr) const {
	int i, j;
	unlim_matrix<U> conv_matr(matr.convert_to<U>());
	if (empty || conv_matr.is_empty()) { return empty_unlim_matrix.convert_to<U>(); }
	if (row_cnt != conv_matr.get_row_cnt() || col_cnt != conv_matr.get_col_cnt()) { return empty_unlim_matrix.convert_to<U>(); }
	unlim_matrix<U> new_matr(row_cnt, col_cnt);
	for (i = 0; i < row_cnt; ++i){
		for (j = 0; j < col_cnt; ++j){
			new_matr.matrix_p[i][j] = (U)matrix_p[i][j] * conv_matr.matrix_p[i][j];
		}
	}
	return new_matr;
}

template<typename T>
double unlim_matrix<T>::frobenius_norme() const {
	if (empty || !correct) throw except_empty_container();
	double sum = 0;
	for (auto v : matrix_s){
		for (auto vv : v){
			sum += vv*vv;
		}
	}
	return sqrt(sum);
}

template<typename T>
T unlim_matrix<T>::trace() const {
	int i;
	T sum = 0;
	if (!is_square()) throw except_non_compatible("Matrix is not square");
	else {
		for (i = 0; i < row_cnt; ++i) {
			sum += matrix_s[i][i];
		}
	}
	return sum;
}

template<typename T>
unlim_matrix<T> unlim_matrix<T>::algebr_compl(int row, int col) {
	if (empty || !correct) return empty_unlim_matrix.convert_to<T>();
	if (row < 0 || row_cnt <= row) throw except_index_out_of_range(row);
	if (col < 0 || col_cnt <= col) throw except_index_out_of_range(col);
	unlim_matrix<T> new_matr(row_cnt - 1, col_cnt - 1);
	int i, j;
	for (i = 0; i < row; ++i){
		for (j = 0; j < col; ++j){
			new_matr.matrix_s[i][j] = matrix_s[i][j];
		}
		for (j = col + 1; j < col_cnt; ++j){
			new_matr.matrix_s[i][j - 1] = matrix_s[i][j];
		}
	}
	for (i = row + 1; i < row_cnt; ++i){
		for (j = 0; j < col; ++j){
			new_matr.matrix_s[i - 1][j] = matrix_s[i][j];
		}
		for (j = col + 1; j < col_cnt; ++j){
			new_matr.matrix_s[i - 1][j - 1] = matrix_s[i][j];
		}
	}
	return new_matr;
}

template<typename T>
unlim_matrix<T> unlim_matrix<T>::transpose() {
	if (empty || !correct) return empty_unlim_matrix.convert_to<T>();
	unlim_matrix<T> transp(col_cnt, row_cnt);
	int i, j;
	for (i = 0; i < row_cnt; ++i) {
		for (j = 0; j < col_cnt; ++j) {
			transp.matrix_p[j][i] = matrix_s[i][j];
		}
	}
	transp.empty = false;
	transp.correct = true;
	return transp;
}

template<typename T>
int unlim_matrix<T>::rank() const {

}

// OPERATORS ======================================================

template<typename T>
ostream& operator << (ostream& ost, unlim_matrix<T>& matr) {
	if (matr.is_empty() || !matr.is_correct()) {
		ost << "{ }";
		return ost;
	}
	for (auto v : matr.matrix_p){
		for (auto vv : v){ ost << vv << " "; }
		ost << "\n";
	}
	ost << endl;
	return ost;
}

template<typename T>
void unlim_matrix<T>::operator = (unlim_matrix<T> &matr) {
	correct = matr.correct;
	//matrix_s(matr.matrix_s);
	reset(matr.matrix_p);
	for (int i = 0; i < row_cnt; ++i){
		for (int j = 0; j < col_cnt; ++j){
			matrix_s[i][j] = matr[i][j];
		}
	}
}

template<typename T>
void unlim_matrix<T>::operator = (unlim_vector<T> &v){
	reset(1, v.get_dimention());
	for (int i = 0; i < col_cnt; ++i){
		matrix_s[0][i] = v[i];
	}
}

template<typename T>
void unlim_matrix<T>::operator = (vector<T> &v){
	reset(1, v.size());
	for (int i = 0; i < col_cnt; ++i){
		matrix_s[0][i] = v[i];
	}
}

template<typename T>
vector<T>& unlim_matrix<T>::operator [](int ind) {
	if (ind < 0 || row_cnt <= ind) throw except_index_out_of_range(ind);
	else return matrix_s[ind];
}

template<typename T>
vector<T> unlim_matrix<T>::operator ()(int ind){
	if (ind < 0 || row_cnt <= ind) throw except_index_out_of_range(ind);
	vector<T> v(row_cnt);
	for (int i = 0; i < row_cnt; ++i) v[i] = matrix_s[i][ind];
	return v;
}

template<typename T, typename U>
unlim_matrix<T> operator + (unlim_matrix<T> &matr1, unlim_matrix<U> &matr2) {
	if (!int_convertable<U>()) throw except_vrong_type<U>();
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	if (matr1.is_empty() || matr2.is_empty() || !matr1.is_correct() || !matr2.is_correct()) return empty_unlim_matrix.convert_to<T>();
	if (!matr1.is_compatible_with(matr2))return empty_unlim_matrix.convert_to<T>();
	unlim_matrix<T> matr(matr1);
	int i, j, row, col;
	row = matr1.get_row_cnt();
	col = matr1.get_col_cnt();
	for (i = 0; i < row; ++i) {
		for (j = 0; j < col; ++j){ matr.matrix_p[i][j] += matr2.matrix_p[i][j]; }
	}
	return matr;
}

template<typename T, typename U>
unlim_matrix<T> operator - (unlim_matrix<T> &matr1, unlim_matrix<U> &matr2) {
	if (!int_convertable<U>()) throw except_vrong_type<U>();
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	if (matr1.is_empty() || matr2.is_empty() || !matr1.is_correct() || !matr2.is_correct()) return empty_unlim_matrix.convert_to<T>();
	if (!matr1.is_compatible_with(matr2))return empty_unlim_matrix.convert_to<T>();
	unlim_matrix<T> matr(matr1);
	int i, j, row, col;
	row = matr1.get_row_cnt();
	col = matr1.get_col_cnt();
	for (i = 0; i < row; ++i) {
		for (j = 0; j < col; ++j){ matr.matrix_p[i][j] -= matr2.matrix_p[i][j]; }
	}
	return matr;
}

template<typename T, typename U>
unlim_matrix<T> operator * (unlim_matrix<T> &matr1, U n) {
	if (!int_convertable<U>()) throw except_vrong_type<U>();
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	if (matr1.is_empty() || !matr1.is_correct()) return empty_unlim_matrix.convert_to<T>();
	unlim_matrix<T> matr(matr1);
	int i, j, row, col;
	row = matr1.get_row_cnt();
	col = matr1.get_col_cnt();
	for (i = 0; i < row; ++i) {
		for (j = 0; j < col; ++j){ matr.matrix_p[i][j] *= (T)n; }
	}
	return matr;
}

template<typename T, typename U>
unlim_matrix<T> operator * (U n, unlim_matrix<T> &matr1) {
	if (!int_convertable<U>()) throw except_vrong_type<U>();
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	if (matr1.is_empty() || !matr1.is_correct()) return empty_unlim_matrix.convert_to<T>();
	unlim_matrix<T> matr(matr1);
	int i, j, row, col;
	row = matr1.get_row_cnt();
	col = matr1.get_col_cnt();
	for (i = 0; i < row; ++i) {
		for (j = 0; j < col; ++j){ matr.matrix_p[i][j] *= (T)n; }
	}
	return matr;
}

template<typename T, typename U>
unlim_matrix<T> operator * (unlim_matrix<T> &matr1, unlim_matrix<U> &matr2) {
	if (!int_convertable<U>()) throw except_vrong_type<U>();
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	if (matr1.is_empty() || matr2.is_empty() || !matr1.is_correct() || !matr2.is_correct()) return empty_unlim_matrix.convert_to<T>();
	if (!matr1.is_compatible_with(matr2) || (matr1.get_col_cnt() != matr2.get_row_cnt())) return empty_unlim_matrix.convert_to<T>();
	int i, j, k;
	T sum;
	int row1 = matr1.get_row_cnt();
	int col1 = matr1.get_col_cnt();
	int row2 = matr2.get_row_cnt();
	int col2 = matr2.get_col_cnt();
	unlim_matrix<T> matr(row1, col2);
	for (i = 0; i < row1; ++i) {
		for (j = 0; j < col2; ++j){
			sum = 0;
			for (k = 0; k < col1; ++k){
				sum += matr1[i][k] * matr2[k][j];
			}
			matr[i][j] = sum;
		}
	}
	return matr;
}

template<typename T, typename U>
unlim_matrix<T> matr_product(unlim_matrix<T> &matr1, unlim_matrix<U> &matr2) {
	if (!int_convertable<U>()) throw except_vrong_type<U>();
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	if (matr1.is_empty() || matr2.is_empty() || !matr1.is_correct() || !matr2.is_correct()) return empty_unlim_matrix.convert_to<T>();
	if (!matr1.is_compatible_with(matr2) || (matr1.get_col_cnt() != matr2.get_row_cnt())) return empty_unlim_matrix.convert_to<T>();
	int i, j, k;
	T sum;
	int row1 = matr1.get_row_cnt();
	int col1 = matr1.get_col_cnt();
	int row2 = matr2.get_row_cnt();
	int col2 = matr2.get_col_cnt();
	unlim_matrix<T> matr(row1, col2);
	for (i = 0; i < row1; ++i) {
		for (j = 0; j < col2; ++j){
			sum = 0;
			for (k = 0; k < col1; ++k){
				sum += matr1[i][k] * matr2[k][j];
			}
			matr[i][j] = sum;
		}
	}
	return matr;
}

template<typename T, typename U>
unlim_vector<T> operator * (unlim_matrix<T> &matr, unlim_vector<U> &vect) {
	if (!int_convertable<U>()) throw except_vrong_type<U>();
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	if (!matr.is_correct() || vect.is_empty() || matr.get_col_cnt() != vect.get_dimention()) return empty_unlim_vector.convert_to<T>();
	int row = matr.get_row_cnt();
	int col = matr.get_col_cnt();
	T sum;
	unlim_vector<T> new_vect(row);
	for (int i = 0; i < row; ++i) {
		sum = 0;
		for (int j = 0; j < col; ++j) {
			sum += (T)matr.matrix_p[i][j] * vect.vector_p[j];
		}
		new_vect.vector_p[i] = sum;
	}
	return new_vect;
}

template<typename T>
void unlim_matrix<T>::operator / (T d){
	if (d == 0) return;
	for (int i = 0; i < row_cnt; ++i){
		for (int j = 0; j < col_cnt; ++j){
			matrix_s[i][j] /= d;
		}
	}
}

// NON_MEMBER FUNCTIONS =======================================================================

template<typename T>
T determinant(unlim_matrix<T> &matr) {
	T sum = 0;
	int i, col, neg = 1;
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	if (!matr.is_square())		throw except_non_compatible("Matrix is not square");

	if (matr.get_row_cnt() == 2) {
		return (matr.matrix_p[0][0] * matr.matrix_p[1][1] - matr.matrix_p[0][1] * matr.matrix_p[1][0]);
	}
	else {
		col = matr.get_col_cnt();
		for (i = 0; i < col; ++i, neg *= -1){
			sum += neg * matr.matrix_p[0][i] * determinant<T>(matr.algebr_compl(0, i));
		}
	}
	return sum;
}

template<typename T>
unlim_matrix<double> inverse(unlim_matrix<T> &matr) {
	if (matr.is_empty() || !matr.is_correct() || !matr.is_square()) return empty_unlim_matrix.convert_to<double>();
	int i, j;
	int row = matr.get_row_cnt();
	int col = matr.get_col_cnt();
	unlim_matrix<double> inv_matr(row, col);
	double deter = determinant<T>(matr);
	for (i = 0; i < row; ++i){
		for (j = 0; j < col; ++j){
			inv_matr.matrix_p[i][j] = (((i + j) % 2 == 0) ? 1 : -1) * determinant<T>(matr.algebr_compl(j, i)) / deter;
		}
	}
	return inv_matr;
}

template<typename T>
void unlim_matrix<T>::make_identical(int n){
	reset(n, n);
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			matrix_p[i][j] = 0;
		}
	}
	for (int i = 0; i < n; ++i){
		matrix_p[i][i] = 1;
	}
}

template<typename T>
int matr_rank(unlim_matrix<T> &matr) {
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	if (matr.is_empty() || !matr.is_correct()) throw except_empty_container();
	int row = matr.get_row_cnt();
	int col = matr.get_col_cnt();
	int rank = (row < col) ? row : col;
	vector<char> used_lines(row);
	unlim_matrix<double> nmatr(matr.convert_to<double>());
	int i;
	for (int j = 0; j < col; ++j) {
		for (i = 0; i < row; ++i){
			if (!used_lines[i] && abs(nmatr.matrix_p[i][j]) > _eps) break;
		}
		if (i == row) rank--;
		else {
			used_lines[i] = 1;
			for (int k = j + 1; k < col; ++k) { nmatr.matrix_p[i][k] /= nmatr.matrix_p[i][j]; }
			for (int r = 0; r < row; ++r) {
				if (r != i && abs(nmatr.matrix_p[r][j]) > _eps) {
					for (int k = j + 1; k < col; ++k) { nmatr.matrix_p[r][k] -= nmatr.matrix_p[r][j] * nmatr.matrix_p[i][k]; }
				}
			}
		}
		nmatr.print();
	}
	return rank;
}

template<typename T>
void unlim_matrix<T>::print_to_file(const char* name, const char* type) {
	if (string(type) == string("bin")){
		//int row_cnt = get_row_cnt();
		//int col_cnt = get_col_cnt();
		string str = string("matrices\\").append(name);
		ofstream f(name, ios::binary);
		if (!f) throw except_empty_container("empty file");

		f.write((char*)&row_cnt, sizeof(int));
		f.write((char*)&col_cnt, sizeof(int));

		for (int i = 0; i < row_cnt; ++i) {
			for (int j = 0; j < col_cnt; ++j) {
				f.write((char*)&(matrix_p[i][j]), sizeof(matrix_p[i][j]));
			}
		}
		f.close();
	}
	if (string(type) == string("txt")){
		string str = string("matrices\\").append(name).append(".txt");

		ofstream f(str, ios::out);
		if (!f) throw except_empty_container("empty file");
		f << row_cnt << ' ';
		f << col_cnt << ' ';

		for (int i = 0; i < row_cnt; ++i){
			for (int j = 0; j < col_cnt; ++j){
				f << matrix_p[i][j] << ' ';
			}
		}
		f.close();
	}
}

template<typename T>
void unlim_matrix<T>::read_from_file(const char* name, const char* type) {
	if (string(type) == string("bin")){
		int row = 0;
		int col = 0;
		string str = string("matrices\\").append(name);

		ifstream f(name, ios::binary);
		if (!f) throw except_empty_container("empty file");
		f.read((char*)&row, sizeof(int));
		f.read((char*)&col, sizeof(int));

		reset(row, col);
		for (int i = 0; i < row; ++i){
			for (int j = 0; j < col; ++j){
				f.read((char*)&matrix_p[i][j], sizeof(matrix_p[i][j]));
			}
		}
		f.close();
	}
	if (string(type) == string("txt")){
		int row = 0;
		int col = 0;
		string str = string("matrices\\").append(name).append(".txt");

		ifstream f(str, ios::in);
		if (!f) throw except_empty_container("empty file");
		f >> row;
		f >> col;

		reset(row, col);
		for (int i = 0; i < row; ++i){
			for (int j = 0; j < col; ++j){
				f >> matrix_p[i][j];
			}
		}
		f.close();
	}
}

template<typename T>
void operator << (unlim_matrix<T> &matr, const char* name) {
	int row_cnt = matr.get_row_cnt();
	int col_cnt = matr.get_col_cnt();
	string str = string("matrices\\").append(name);
	ofstream f(name, ios::binary);
	if (!f) throw except_empty_container("empty file");

	f.write((char*)&row_cnt, sizeof(int));
	f.write((char*)&col_cnt, sizeof(int));

	for (int i = 0; i < row_cnt; ++i) {
		for (int j = 0; j < col_cnt; ++j) {
			f.write((char*)&(matr.matrix_p[i][j]), sizeof(matr.matrix_p[i][j]));
		}
	}
	f.close();
}

template<typename T>
void operator >> (unlim_matrix<T> &matr, const char* name) {
	int row = 0;
	int col = 0;
	string str = string("matrices\\").append(name);

	ifstream f(name, ios::binary);
	if (!f) throw except_empty_container("empty file");
	f.read((char*)&row, sizeof(int));
	f.read((char*)&col, sizeof(int));

	matr.reset(row, col);
	for (int i = 0; i < row; ++i){
		for (int j = 0; j < col; ++j){
			f.read((char*)&matr.matrix_p[i][j], sizeof(matr.matrix_p[i][j]));
		}
	}
	f.close();
}

template<typename T>
void operator << (unlim_matrix<T> &matr, ofstream &f) {
	int row_cnt = matr.get_row_cnt();
	int col_cnt = matr.get_col_cnt();
	if (!f) throw except_empty_container("empty file");

	f.write((char*)&row_cnt, sizeof(int));
	f.write((char*)&col_cnt, sizeof(int));

		for (int i = 0; i < row_cnt; ++i) {
		for (int j = 0; j < col_cnt; ++j) {
			f.write((char*)&matr.matrix_p[i][j], sizeof(matr.matrix_p[i][j]));
		}
		}
	f.close();
}

template<typename T>
void operator >> (unlim_matrix<T> &matr, ifstream &f) {
	int row = 0;
	int col = 0;
	if (!f) throw except_empty_container("empty file");

	f.read((char*)&row, sizeof(int));
	f.read((char*)&col, sizeof(int));

	matr.reset(row, col);
	for (int i = 0; i < row; ++i){
		for (int j = 0; j < col; ++j){
			f.read((char*)&matr.matrix_p[i][j], sizeof(matr.matrix_p[i][j]));
		}
	}
	f.close();
}

unlim_matrix<double> centrirovat(unlim_matrix<double> &matr){
	unlim_matrix<double> M;
	M.reset(matr.matrix_p);
	double m;
	int col = matr.get_col_cnt();
	int row = matr.get_row_cnt();
	for (int j = 0; j < col; ++j){
		m = matr.col_sum(j) / col;
		for (int k = 0; k < row; ++k){
			M[k][j] = m;
		}
	}
	matr = matr - M;
	return matr;
}

unlim_matrix<double> normirovat(unlim_matrix<double> &matr){
	unlim_matrix<double> W;
	int col = matr.get_col_cnt();
	int row = matr.get_row_cnt();
	double d, m;
	W.reset(col, col);
	for (int j = 0; j < col; ++j){
		for (int i = 0; i < col; ++i){
			W[i][j] = 0;
		}
	}
	for (int j = 0; j < col; ++j){
		d = 0;
		m = matr.col_sum(j) / col;
		for (int i = 0; i < row; ++i){
			d += (matr[i][j] - m)*(matr[i][j] - m);
		}
		d = sqrt(d / col);
		W[j][j] = d;
	}
	matr = matr * W;
	return matr;
}

//DETERMINANT
/*
double LU_determinant(vector<vector<double>> A, int n)
{
	double det = 1;
	vector<vector<double>> L;
	vector<vector<double>> U;

	U = A;
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			L[j][i] = U[j][i] / U[i][i];

	for (int k = 1; k < n; k++)
	{
		for (int i = k - 1; i < n; i++)
			for (int j = i; j < n; j++)
				L[j][i] = U[j][i] / U[i][i];

		for (int i = k; i < n; i++)
			for (int j = k - 1; j < n; j++)
				U[i][j] = U[i][j] - L[i][k - 1] * U[k - 1][j];
	}
	for (int i = 0; i < n; i++)
		det *= U[i][i];
	return det;
}

template<typename T>
unlim_matrix<double> LU_inverse(unlim_matrix<T> &matr) {
	if (matr.is_empty() || !matr.is_correct() || !matr.is_square()) return empty_unlim_matrix.convert_to<double>();
	int i, j;
	int row = matr.get_row_cnt();
	int col = matr.get_col_cnt();
	unlim_matrix<double> inv_matr(row, col);
	double deter = LU_determinant(matr.matrix_p, row);
	for (i = 0; i < row; ++i){
		for (j = 0; j < col; ++j){
			inv_matr.matrix_p[i][j] = (((i + j) % 2 == 0) ? 1 : -1) * LU_determinant(matr.algebr_compl(j, i).matrix_p, 0) / deter;
		}
	}
	return inv_matr;
}
*/

//DETERMINANT

double gauss_det(unlim_matrix<double> &a)
{
	int i, j, k;
	int countSwaps = 1;
	unlim_matrix<double> c(a);
	int n = a.get_row_cnt();
	int m = a.get_col_cnt();
	for (i = 0; i < n; ++i)
	{
		// находим строку с максимальным первым элементом
		int iMax = i;
		for (j = i + 1; j < n; ++j)
			if (abs(c[j][i]) > abs(c[iMax][i]))
				iMax = j;
		if (abs(c[iMax][i]) < _eps)
			continue;
		for (k = 0; k < m; ++k)
			swap(c[i][k], c[iMax][k]);
		countSwaps = -countSwaps * (i != iMax ? 1 : -1);

		//  вычитаем текущую строку из всех остальных
		for (j = i + 1; j < n; ++j)
		{
			double q = -c[j][i] / c[i][i];
			for (k = m - 1; k >= i; --k)
				c[j][k] += q * c[i][k];
		}
	}

	double det = 1;

	// умножаем матрицу на -1, если мы сделали  нечётное количество перестановок строк
	// в итоге определитель результирующей матрицы  будет равен определителю начальной матрицы
	c = c * countSwaps;

	for (int i = 0; i < n; ++i){
		det *= c[i][i];
	}

	return det;
}

unlim_matrix<double> gauss_inverse(unlim_matrix<double> &matr) {
	if (matr.is_empty() || !matr.is_correct() || !matr.is_square()) return empty_unlim_matrix.convert_to<double>();
	int i, j;
	int row = matr.get_row_cnt();
	int col = matr.get_col_cnt();
	unlim_matrix<double> inv_matr(row, col);
	double deter = gauss_det(matr);
	for (i = 0; i < row; ++i){
		for (j = 0; j < col; ++j){
			inv_matr.matrix_p[i][j] = (((i + j) % 2 == 0) ? 1 : -1) * gauss_det(matr.algebr_compl(j, i)) / deter;
		}
	}
	return inv_matr;
}

#endif
