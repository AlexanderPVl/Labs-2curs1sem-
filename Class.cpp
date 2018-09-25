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
Vector2::Vector2(double x1, double y1, double x2, double y2){
	Coord = new double[4];
	Coord[0] = x1; Coord[1] = y1;
	Coord[2] = x2; Coord[3] = y2;
}
Vector2::~Vector2(){
	delete[] Coord;
}

double& Vector2::GetCoordRef(int i){
	return Coord[i];
}
double Vector2::GetCoord(int i) const{
	return Coord[i];
}
void Vector2::SetCoord(int i, double val){
	GetCoordRef(i) = val;
}
double Vector2::d(const char var) const{
	if (var == 'x')return GetCoord(2) - GetCoord(0);
	if (var == 'y')return GetCoord(3) - GetCoord(1);
	else return 0;
}
double Vector2::VectorLen() const{
	return sqrt(pow(d('x'), 2) + pow(d('y'), 2));
}
