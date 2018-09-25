#pragma once
#include <iostream>

class Cube{
	int X;
	int Y;
	int Deg3(int n) const;

public:
	Cube(int x = 0, int y = 0);

	int MaxCube();
	int GetX() const;
	int GetY() const;
	void SetX(int x = 0);
	void SetY(int y = 0);
};

class Vector2{
	double* Coord = NULL;
	double d(const char var) const;

public:
	Vector2(double x1 = 0, double y1 = 0, double x2 = 0, double y2 = 0);
	~Vector2();

	double& GetCoordRef(int i);
	double GetCoord(int i) const;
	void SetCoord(int i, double val);
	double VectorLen() const;
};
