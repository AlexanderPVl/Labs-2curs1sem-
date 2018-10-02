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
	ostream& Container<Type>::operator << (ostream &ost){
		int i = 0;
		for (; i < Count; i++)
			cout << Array[i];
		return ost;
	}
};

//CONTAINER======================================
template <class Type>
Type& Container<Type>::operator [] (int n){
	if (n >= Count)
		return Array[Count];
	return Array[n];
}
template <class Type>
Container<Type>::~Container(){
	delete[] Array;
}
template <class Type>
Container<Type>::Container(Container<Type>&Cont){
	int i;
	Array = new Type[Cont.GetCount()];
	for (i = 0; i < Cont.GetCount(); i++){
		Array[i] = Cont[i];
	}
	this->Count = Cont.GetCount();
}
template <class Type>
Container<Type>::Container(int N){
	Array = new Type[N];
	this->Count = N;
}
template <class Type>
Container<Type>::Container(){
	Array = new Type[1];
	this->Count = 1;
}
/*template <class Type>
void Container<Type>::Initialise(){
Type T;
int i = 0;
for (; i < Count; i++)
Array[i] = T;
}*/
template <class Type>
int Container<Type>::GetCount(){
	return Count;
}
template <class Type>
Type& Container<Type>::ArrAccess(){
	return Array;
}
//template <class Type>



ostream &operator << (ostream &ost, Fract f);
//template<class Type>
//ostream &operator << (ostream &ost, Container<Type>Cont);
Fract& operator ^ (const Fract f1, const int N);
