#include "Graph.h"

void isolated(bool** matr, int n){
	std::cout << "isolated: " << std::endl;
	bool fl = 0;
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			if (matr[i][j] && i != j) fl = 1;
		}
		if (!fl) std::cout << i + 1 << std::endl;
		fl = 0;
	}
}

void loops(bool** matr, int n){
	std::cout << "loops: " << std::endl;
	for (int j = 0; j < n; ++j){
		if (matr[j][j]) std::cout << j << std::endl;
 	}
}

void cycles(bool** matr, int n){
	bool fl = 0;
	std::cout << "cycles: " << std::endl;

	bool** w = new bool*[n];
	for (int i = 0; i < n; ++i){
		w[i] = new bool[n];
		for (int j = 0; j < n; ++j){
			w[i][j] = 0;
		}
	}

	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			w[i][j] = matr[i][j];
		}
	}

	for (int k = 1; k < n; ++k) {
		for (int i = 1; i < n; ++i){
			for (int j = 1; j < n; ++j){
				w[i][j] = w[i][j] || (w[i][k] && w[k][j]);
			}
		}
	}

	for (int i = 0; i < n; ++i){
		if (w[i][i]) {
			fl = 1;
			
			break;
		}
	}
	if (fl) std::cout << "There are cycles" << std::endl;
	else std::cout << "There is no cycles" << std::endl;
	for (int j = 0; j < n; ++j){
		delete w[j];
	}
	delete[] w;
}

void degree(bool** matr, int n){
	int deg = 0;
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i){
			if (matr[k][i]) deg += 1;
		}
	}
	std::cout << "degree: " << deg << std::endl;
}

void edges(bool** matr, int n){
	int deg = 0;
	std::cout << "edges: " << std::endl;
	for (int k = 0; k < n; ++k) {
		for (int i = k; i < n; ++i){
			if (matr[k][i]) std::cout << "(" << k + 1 << ", " << i + 1 << ")" << std::endl;
		}
	}
}

void Task1(){
	int n = 3;
	bool** matr = new bool*[n];
	for (int i = 0; i < n; ++i){
		matr[i] = new bool[n];
		for (int j = 0; j < n; ++j){
			matr[i][j] = 0;
		}
	}
	matr[0][2] = 1;
	matr[2][0] = 1;
	matr[1][1] = 1;

	isolated(matr, n);
	loops(matr, n);
	cycles(matr, n);
	degree(matr, n);
	edges(matr, n);

	for (int j = 0; j < n; ++j){
		delete matr[j];
	}
	delete[] matr;
}

void Task16(int n){
	bool** matr = new bool*[n];
	for (int i = 0; i < n; ++i){
		matr[i] = new bool[n];
		for (int j = 0; j <= i; ++j){
			matr[i][j] = 0;
		}
		for (int j = i + 1; j < n; ++j){
			matr[i][j] = 1;
		}
	}
	std::cout << std::endl;
	std::cout << "Task 16:" << std::endl;
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			std::cout << matr[i][j] << " ";
		}
		std::cout << std::endl;
	}
}