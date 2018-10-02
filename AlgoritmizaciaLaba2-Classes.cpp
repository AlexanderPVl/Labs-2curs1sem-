#include "Classes.h"

//FRACT==========================================
Fract::Fract(){
	Nume = 1;
	Deno = 1;
}
Fract::Fract(Fract& f){
	if (!f.Deno){
		this->Deno = 1;
		cout << "ERROR: denominator equals to 0" << endl;
	}
	this->Deno = f.Deno;
	this->Nume = f.Nume;
	Simplify();
}
Fract::Fract(int nume, int deno){
	if (!deno){
		deno = 1;
		cout << "ERROR: denominator equals to 0" << endl;
	}
	Nume = nume;
	Deno = deno;
	Simplify();
}
int Fract::GetNume() const{
	return Nume;
}
int Fract::GetDeno() const{
	return Deno;
}
void Fract::SetNume(int nume){
	Nume = nume;
	Simplify();
}
void Fract::SetDeno(int deno){
	if (!deno){
		this->Deno = 1;
		cout << "ERROR: denominator equals to 0" << endl;
	}
	Deno = deno;
	Simplify();
}
void Fract::Simplify(){
	if (Deno < 0){
		Nume = -Nume;
		Deno = -Deno;
	}
	if (!(Nume % Deno)){
		Nume /= Deno;
		Deno = 1;
	}
	if (Nume){
		if (!(Deno%Nume)){
			Deno /= Nume;
			Nume = 1;
		}
	}
	if (!Deno){
		Deno = 1;
		cout << "ERROR: denominator equals to 0" << endl;
	}
}
bool Fract::IsNatural(){
	return (this->Deno == 1);
}
int Fract::ToInt(){
	if (!Deno){
		cout << "ERROR: denominator equals to 0" << endl;
		return 0;
	}
	return this->Nume / this->Deno;
}
double Fract::ToDouble(){
	if (!Deno){
		cout << "ERROR: denominator equals to 0" << endl;
		return 0;
	}
	return (double)Nume / (double)Deno;
}
Fract& Fract::operator + (const Fract f){
	this->SetNume(this->GetDeno()*f.GetNume() + this->GetNume()*f.GetDeno());
	this->SetDeno(this->GetDeno()*f.GetDeno());
	Simplify();
	return *this;
}
Fract& Fract::operator - (const Fract f){
	this->SetNume(this->GetNume()*f.GetDeno() - this->GetDeno()*f.GetNume());
	this->SetDeno(this->GetDeno()*f.GetDeno());
	Simplify();
	return *this;
}
Fract& Fract::operator * (const Fract f){
	this->SetNume(this->GetNume()*f.GetNume());
	this->SetDeno(this->GetDeno()*f.GetDeno());
	Simplify();
	return *this;
}
Fract& Fract::operator / (const Fract f){
	this->SetNume(this->GetNume()*f.GetDeno());
	this->SetDeno(this->GetDeno()*f.GetNume());
	Simplify();
	return *this;
}
Fract& Fract::operator = (const Fract f){
	this->Deno = f.Deno;
	this->Nume = f.Nume;
	if (!Deno){
		Deno = 1;
		cout << "ERROR: denominator equals to 0" << endl;
	}
	return *this;
}
Fract& Fract::operator () (int nume, int deno){
	this->Nume = nume;
	this->Deno = deno;
	if (!this->Deno){
		Deno = 1;
		cout << "ERROR: denominator equals to 0" << endl;
	}
	return *this;
}
Fract& operator ^ (const Fract f1, const int N){
	Fract f;
	int GN = f1.GetNume();
	int GD = f1.GetDeno();
	int nume = 1, deno = 1, i = 0;
	for (; i < N; i++){
		nume *= GN;
		deno *= GD;
	}
	f.SetDeno(deno);
	f.SetNume(nume);
	return f;
}
ostream &operator << (ostream &ost, Fract f){
	if (!f.GetNume()){
		cout << "0" << endl;
	}
	else if (f.GetDeno()==1){
		cout << f.GetNume() << endl; 
	}
	else
		cout << f.GetNume() << "/" << f.GetDeno() << endl;
	return ost;
}



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
		*this[i] = Cont[i];
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
/*template <class Type>
ostream& Container<Type>::operator << (ostream &ost, Container<Type>Cont){
	int i = 0;
	for (; i < Cont.GetCount(); i++)
		cout << Cont[i];
}*/
