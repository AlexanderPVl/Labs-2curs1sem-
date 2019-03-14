#include "Classes.h"

using namespace std;

void FractFunc(){
	Fract f1(1, 2), f2(f1), f;
	cout << "f1 = " << f1;
	cout << "f2 = " << f2;
	f = f1;
	cout << "f = " << f;
	f + f2;
	cout << "f + f2 = " << f;
	f * f1;
	cout << "f * f1 = " << f;
	f / f2;
	cout << "f / f2 = " << f;
	f(8, 9);
	cout << "f = " << f;
	f(10, 3);
	f = Fract(1, 2);
	f = f ^ 3;
	//cout << f;
}

void ContainerFunc(){
	Container<Fract>Cont1(4);
	Container<Fract>Cont2(Cont1);
	Cont1 << cout << endl;
	Cont2 << cout << endl;
}

int main(){
	//FractFunc();
	ContainerFunc();

	return 0;
}
