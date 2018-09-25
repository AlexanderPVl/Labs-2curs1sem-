#include <iostream>
#include "Class.h"

using namespace std;

int main()
{
	Cube cube1(3, 2);
	Vector2 vect(0, 0, 4, 3);
	cout << cube1.MaxCube() << endl;
	cout << vect.VectorLen() << endl;
	return 0;
}
