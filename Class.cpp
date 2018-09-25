#include "Class.h"
#include <math.h>

//CUBE================================
int Cube::Deg3(int n) const{
	return n*n*n;
}
Cube::Cube(int x, int y){
	X = x;
	Y = y;
}
int Cube::GetX() const{
	return X;
}
int Cube::GetY() const{
	return Y;
}
void Cube::SetX(int x){
	X = x;
}
void Cube::SetY(int y){
	Y = y;
}
int Cube::MaxCube(){
	int max = (X > Y) ? X : Y;
	return Deg3(max);
}

//VECTOR==============================
void Vector2::FindNormal(){
	if (!d('x') && !d('y')){
		Coord[0] = Coord[1] = Coord[2] = Coord[3] = 0;
		return;
	}
	if (!d('x')){
		Coord[0] = Coord[1] = Coord[3] = 0;
		Coord[2] = 1;
		return;
	}
	else if (!d('y')){
		Coord[0] = Coord[1] = Coord[2] = 0;
		Coord[3] = 1;
		return;
	}
	else{
		Coord[0] = Coord[1] = 0;
		Coord[2] = 1 / d('x');
		Coord[3] = -1 / d('y');
		return;
	}

	Coord[0] = 1;
	Coord[1] = 1;
	Coord[2] = 1;
	Coord[3] = 1;
}
Vector2::Vector2(double x1, double y1, double x2, double y2){
	X1 = x1;
	Y1 = y1;
	X2 = x2;
	Y2 = y2;
	Coord = new double[4];
}
Vector2::~Vector2(){
	delete[] Coord;
}

double& Vector2::GetCoordRef(int i){
	switch (i){
	case 0: return X1;
	case 1: return Y1;
	case 2: return X2;
	case 3: return Y2;
	default: return X1;
	}
}
double Vector2::GetCoord(int i) const{
	switch (i){
	case 0: return X1;
	case 1: return Y1;
	case 2: return X2;
	case 3: return Y2;
	default: return 0;
	}
}
void Vector2::SetCoord(int i, double val){
	GetCoordRef(i) = val;
}
double Vector2::d(const char var) const{
	if (var == 'x')return (GetCoord(2) - GetCoord(0));
	if (var == 'y')return (GetCoord(3) - GetCoord(1));
	else return 0;
}
double Vector2::VectorLen() const{
	return sqrt(pow(d('x'), 2) + pow(d('y'), 2));
}
double Vector2::GetCoordArray(int i){
	return Coord[i];
}
