#ifndef DERIVATIVE_MATRIX_H
#define DERIVATIVE_MATRIX_H

#include "unlim_matrix.h"

template<typename T>
class unlim_ident_matrix : public unlim_matrix<T> {
public:
	unlim_ident_matrix();
	unlim_ident_matrix(int dim);
	~unlim_ident_matrix() = default;
	int get_dimention() const;
private:
	int dimention;
	bool correct; // if empty => not correct
	bool empty;
};

template<typename T>
class unlim_symmetric_matrix : public unlim_matrix<T> {
public:
	unlim_symmetric_matrix();
	unlim_symmetric_matrix(int dim);
	unlim_symmetric_matrix(unlim_symmetric_matrix<T> &matr);
	unlim_symmetric_matrix(unlim_matrix<T> &matr);
	~unlim_symmetric_matrix() = default;
private:
	int dimention;
};

template<typename T>
class unlim_upptriang_matrix : public unlim_matrix<T> {
public:
	unlim_upptriang_matrix();
	unlim_upptriang_matrix(int dim);
	unlim_upptriang_matrix(unlim_upptriang_matrix<T> &matr);
	unlim_upptriang_matrix(unlim_matrix<T> &matr);
	~unlim_upptriang_matrix() = default;
private:
	int dimention;
};

template<typename T>
class unlim_lowtriang_matrix : public unlim_matrix<T> {
public:
	unlim_lowtriang_matrix();
	unlim_lowtriang_matrix(int dim);
	unlim_lowtriang_matrix(unlim_lowtriang_matrix<T> &matr);
	unlim_lowtriang_matrix(unlim_matrix<T> &matr);
	~unlim_lowtriang_matrix() = default;
private:
	int dimention;
};

// IDENTICAL MATRIX ======================================================================

template<typename T>
unlim_ident_matrix<T>::unlim_ident_matrix() : unlim_matrix<T>() {
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	empty = true;
	correct = false;
	dimention = 0;
	row_cnt = col_cnt = dimention;
};

template<typename T>
unlim_ident_matrix<T>::unlim_ident_matrix(int dim) : unlim_matrix<T>(dim, dim) {
	int i;
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	if (dim <= 0) {
		empty = true;
		correct = false;
		dimention = 0;
	} else {
		empty = false;
		correct = true;
		dimention = dim;
		for (i = 0; i < dim; ++i) { matrix_s[i][i] = 1; }
	}
	row_cnt = col_cnt = dimention;
}

template<typename T>
int unlim_ident_matrix<T>::get_dimention() const { return dimention; }

// OPERATORS =============================================================================

template<typename T, typename U>
unlim_matrix<T> operator * (unlim_matrix<T> &matr1, unlim_ident_matrix<U> &matr2) {
	if (!int_convertable<U>()) throw except_vrong_type<U>();
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	if (matr1.is_empty() || matr2.is_empty() || !matr1.is_correct() || !matr2.is_correct()) return empty_unlim_matrix.convert_to<T>();
	if (!matr1.is_compatible_with(matr2) || matr1.get_col_cnt() != matr2.get_row_cnt())return empty_unlim_matrix.convert_to<T>();
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
unlim_matrix<T> operator * (unlim_ident_matrix<U> &matr2, unlim_matrix<T> &matr1) {
	if (!int_convertable<U>()) throw except_vrong_type<U>();
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	//if (matr1.is_empty() || matr2.is_empty() || !matr1.is_correct() || !matr2.is_correct()) return empty_unlim_matrix.convert_to<T>();
	if (!matr1.is_compatible_with(matr2) || matr1.get_col_cnt() != matr2.get_row_cnt())return empty_unlim_matrix.convert_to<T>();
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

//SYMMETRIC MATRIX

template<typename T>
unlim_symmetric_matrix<T>::unlim_symmetric_matrix() {
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	empty = true;
	correct = false;
	dimention = 0;
	row_cnt = col_cnt = dimention;
}

template<typename T>
unlim_symmetric_matrix<T>::unlim_symmetric_matrix(int dim) {
	int i;
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	if (dim <= 0) {
		empty = true;
		correct = false;
		dimention = 0;
	}
	else {
		empty = false;
		correct = true;
		dimention = dim;
	}
	row_cnt = col_cnt = dimention;
}

template<typename T>
unlim_symmetric_matrix<T>::unlim_symmetric_matrix(unlim_symmetric_matrix<T> &matr) {
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	if (matr.is_symmetric() && !matr.is_empty()) {
		empty = false;
		correct = true;
		dimention = matr.dimention;
	} else {
		correct = false;
		empty = true;
		dimention = 0;
	}
	row_cnt = col_cnt = dimention;
	matrix_s = matr.matrix_s;
}

template<typename T>
unlim_symmetric_matrix<T>::unlim_symmetric_matrix(unlim_matrix<T> &matr) {
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	if (!matr.is_symmetric()) {
		empty = true;
		correct = false;
		dimention = 0;
	} else {
		empty = matr.is_empty();
		correct = matr.is_correct();
		dimention = matr.get_row_cnt();
	}
	row_cnt = col_cnt = dimention;
	matrix_s = matr.matrix_p;
}

// UPPER TRIANGULAR MATRIX

template<typename T>
unlim_upptriang_matrix<T>::unlim_upptriang_matrix() {
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	empty = true;
	correct = false;
	dimention = 0;
	row_cnt = col_cnt = dimention;
}

template<typename T>
unlim_upptriang_matrix<T>::unlim_upptriang_matrix(int dim) {
	int i;
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	if (dim <= 0) {
		empty = true;
		correct = false;
		dimention = 0;
	}
	else {
		empty = false;
		correct = true;
		dimention = dim;
	}
	row_cnt = col_cnt = dimention;
}

template<typename T>
unlim_upptriang_matrix<T>::unlim_upptriang_matrix(unlim_upptriang_matrix<T> &matr) {
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	empty = matr.empty;
	if (matr.is_upptriangle()) {
		correct = (empty) ? false : true;
		dimention = matr.dimention;
	}
	else {
		correct = false;
		dimention = 0;
	}
	row_cnt = col_cnt = dimention;
	matrix_s = matr.matrix_s;
}

template<typename T>
unlim_upptriang_matrix<T>::unlim_upptriang_matrix(unlim_matrix<T> &matr) {
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	if (!matr.is_upptriangle()) {
		empty = true;
		correct = false;
		dimention = 0;
	}
	else {
		empty = matr.is_empty();
		correct = matr.is_correct();
		dimention = matr.get_row_cnt();
	}
	row_cnt = col_cnt = dimention;
	matrix_s = matr.matrix_p;
}

// LOWER TRIANG|ULAR MATRIX

template<typename T>
unlim_lowtriang_matrix<T>::unlim_lowtriang_matrix() {
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	empty = true;
	correct = false;
	dimention = 0;
	row_cnt = col_cnt = dimention;
}

template<typename T>
unlim_lowtriang_matrix<T>::unlim_lowtriang_matrix(int dim) {
	int i;
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	if (dim <= 0) {
		empty = true;
		correct = false;
		dimention = 0;
	}
	else {
		empty = false;
		correct = true;
		dimention = dim;
	}
	row_cnt = col_cnt = dimention;
}

template<typename T>
unlim_lowtriang_matrix<T>::unlim_lowtriang_matrix(unlim_lowtriang_matrix<T> &matr) {
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	empty = matr.empty;
	if (matr.is_lowtriangle()) {
		correct = (empty) ? false : true;
		dimention = matr.dimention;
	}
	else {
		correct = false;
		dimention = 0;
	}
	row_cnt = col_cnt = dimention;
	matrix_s = matr.matrix_s;
}

template<typename T>
unlim_lowtriang_matrix<T>::unlim_lowtriang_matrix(unlim_matrix<T> &matr) {
	if (!int_convertable<T>()) throw except_vrong_type<T>();
	if (!matr.is_lowtriangle()) {
		empty = true;
		correct = false;
		dimention = 0;
	}
	else {
		empty = matr.is_empty();
		correct = matr.is_correct();
		dimention = matr.get_row_cnt();
	}
	row_cnt = col_cnt = dimention;
	matrix_s = matr.matrix_p;
}

#endif
