#include <iostream>
#include "Class.h"

using namespace std;

int main()
{
	Cube cube1(3, 2);
	Vector2 vect(0, 0, 2, 1);
	cout << cube1.MaxCube() << endl;
	cout << vect.VectorLen() << endl;
	vect.FindNormal();
	cout << vect.GetCoordArray(0) << " " << vect.GetCoordArray(1) << " " << vect.GetCoordArray(2) << " " << vect.GetCoordArray(3) << endl;
	return 0;
}
