#pragma once

#include <iostream>
#include <string>
using namespace std;

class Fract{
private:
	int Nume; // числитель
	int Deno; // знаменатель

public:
	Fract();
	Fract(Fract& f);
	Fract(int nume, int deno);
	int GetNume() const;
	int GetDeno() const;
	void SetNume(int nume);
	void SetDeno(int deno);
	void Simplify();
	bool IsNatural();
	int ToInt();
	double ToDouble();
	Fract& operator + (const Fract f);
	Fract& operator - (const Fract f);
	Fract& operator * (const Fract f);
	Fract& operator / (const Fract f);
	Fract& operator = (const Fract f);
	Fract& operator () (int nume, int deno);
};

template < class Type >
class Container{
private:
	int Count;
	Type *Array;

public:
	Container();
	Container(Container<Type>&Cont);
	Container(int N);
	~Container();
	//void Initialise();
	int GetCount();
	Type& ArrAccess();
	Type& operator [] (int n);
};

ostream &operator << (ostream &ost, Fract f);
//template<class Type>
//ostream &operator << (ostream &ost, Container<Type>Cont);
Fract& operator ^ (const Fract f1, const int N);
