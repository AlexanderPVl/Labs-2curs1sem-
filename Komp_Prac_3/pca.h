#pragma once

#include "derivative_matrix.h"

class pca{
public:
	pca();
	pca(vector<vector<double> > matr);
	void centrir();
	void normir();
	void autoscale();
	three_tuple<unlim_matrix<double>> nipals();
	void print();
	unlim_matrix<double> get_X() { return X; }
	double leverage(int i); // ������
	vector<double> leverage_vector(); // ������ ��������
	double leverage(unlim_matrix<double> scores, int i);
	double variance(int i); // ����������
	double TRVC(); // ������ ��������� �������� � ��������
	double ERVC(); // ���������� ��������� �������� � ��������
	three_tuple<unlim_matrix<double>> nipals_PTE; // = {P, T, E}

private:
	unlim_matrix<double> X;
};

pca::pca()
{
	X.reset(empty_unlim_matrix.convert_to<double>().matrix_p);
}

pca::pca(vector<vector<double> > matr){
	X.reset(matr);
	nipals_PTE = nipals();
}

void pca::print(){
	cout << "X:" << endl;
	X.print();
	cout << endl;
}

void pca::centrir(){
	centrirovat(X);
}

void pca::normir(){
	normirovat(X);
}

void pca::autoscale(){
	centrir();
	normir();
}

three_tuple<unlim_matrix<double>> pca::nipals(){
	unlim_matrix<double> E;
	autoscale();
	E = X;
	//E.print();
	unlim_matrix<double> t, t_old, p, d, P, T;
	int pc = min(E.get_col_cnt(), E.get_row_cnt()), i = 0;
	for (int h = 0; h < pc; ++h){
		t = E(h);
		do{
			if (t.get_col_cnt() != E.get_row_cnt()) t = t.transpose();
			p = t * E; p / pow(t.frobenius_norme(), 2);
			p / p.frobenius_norme();
			t_old = t;
			p = p.transpose();
			t = E * p; t / pow(p.frobenius_norme(), 2);
			d = t_old.transpose() - t;
			p = p.transpose();
		} while (d.frobenius_norme() > _eps);
		E = E - t * p;
		P.append_row(p[0]);
		T.append_col(t(0));
	}
	P = P.transpose();

	three_tuple<unlim_matrix<double>> tt(P, T, E);
	cout << "test: " << endl;
	nipals_PTE = tt;
	return tt;
}

double pca::leverage(int i){
	if (nipals_PTE.is_empty) nipals_PTE = nipals();
	if (i < 0 || i >= nipals_PTE[1].get_col_cnt()) throw except_index_out_of_range(i);
	unlim_matrix<double> T = nipals_PTE[1];
	unlim_matrix<double> ti;

	ti = T[i];
	T = matr_product(T.transpose(), T);
	T = gauss_inverse(T);

	return matr_product(matr_product(ti, T), ti.transpose())[0][0];
}

vector<double> pca::leverage_vector(){
	if (nipals_PTE.is_empty) nipals_PTE = nipals();
	unlim_matrix<double> T = nipals_PTE[1];
	unlim_matrix<double> mulT = nipals_PTE[1];
	unlim_matrix<double> ti;

	mulT = gauss_inverse(matr_product(T.transpose(), T));

	vector<double> leverages;

	for (int i = 0; i < T.get_row_cnt(); ++i){
		ti = T[i];
		leverages.push_back(matr_product(matr_product(ti, mulT), ti.transpose())[0][0]);
	}
	return leverages;
}

double pca::leverage(unlim_matrix<double> scores, int i){
	if (i < 0 || i >= scores.get_col_cnt()) throw except_index_out_of_range(i);
	unlim_matrix<double> T = scores;
	unlim_matrix<double> ti;
	vector<vector<double>> Ti; Ti.push_back(scores(i));
	ti.reset(Ti);
	unlim_matrix<double> ti_t = ti.transpose();
	T = matr_product(T, T.transpose());
	//T = inverse<double>(T);
	T = gauss_inverse(T);
	return matr_product(ti.transpose(), matr_product(matr_product(ti, T), ti.transpose()))[0][0];
}

double pca::variance(int i){
	if (nipals_PTE.is_empty) nipals_PTE = nipals();
	if (i < 0 || i >= nipals_PTE[2].get_row_cnt()) throw except_index_out_of_range(i);
	double sum = 0;
	for (int k = 0; k < nipals_PTE[2].get_col_cnt(); ++k){
		sum += (nipals_PTE[2])[i][k] * (nipals_PTE[2])[i][k];
	}
	return sqrt(sum);
}

double pca::TRVC(){
	if (nipals_PTE.is_empty) nipals_PTE = nipals();
	unlim_matrix<double> E = nipals_PTE[2];
	double res = 0;
	int row = E.get_row_cnt();
	int col = E.get_col_cnt();
	for (int i = 0; i < row; ++i){
		for (int j = 0; j < col; ++j){
			res += E[i][j] * E[i][j];
		}
	}
	return res / (row * col);
}

double pca::ERVC(){
	if (X.is_empty()) throw except_empty_container();
	if (nipals_PTE.is_empty) nipals_PTE = nipals();
	unlim_matrix<double> E = nipals_PTE[2];
	double e_sum = 0, x_sum = 0;
	int e_row = E.get_row_cnt();
	int e_col = E.get_col_cnt();
	int x_row = X.get_row_cnt();
	int x_col = X.get_col_cnt();
	for (int i = 0; i < e_row; ++i){
		for (int j = 0; j < e_col; ++j){
			e_sum += E[i][j] * E[i][j];
		}
	}
	for (int i = 0; i < x_row; ++i){
		for (int j = 0; j < x_col; ++j){
			x_sum += X[i][j] * X[i][j];
		}
	}
	return 1 - e_sum / x_sum;
}
