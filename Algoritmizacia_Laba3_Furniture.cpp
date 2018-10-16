#include "Furniture.h"
#include "Includes.h"

//FURNITURE==========================
Furniture::Furniture(){
	measures = { 0, 0, 0 };
	price = 0;
	material = std::string(NULL_STR);
}

Furniture::Furniture(int id_, int high_, int leng_, int dept_, int price_, std::string &material_){
	measures.high = high_;
	measures.leng = leng_;
	measures.dept = dept_;
	price = price_;
	material = material_;
	id = id_;
}

void Furniture::PrintInfo(){
	std::cout << std::right << "Measures (" << "H x L x D): " << GetHigh() << " x " << GetLeng() << " x " << GetDept() << std::endl;
	std::cout << std::right << "Price: " << price << std::endl << "Material: " << material << std::endl;
}

//TABLE==============================
Table::Table() : Furniture(){
	measures.high = 0;
	measures.leng = 0;
	measures.dept = 0;
	price = 0;
	material = NULL_STR;
	shape = NULL_STR;
}

Table::Table(int id_, Table &T) : Furniture(id, T.GetHigh(), T.GetLeng(), T.GetDept(), T.price, T.material){
	id = id_;
	measures = T.measures;
	price = T.price;
	material = T.material;
	shape = T.shape;
}

Table::Table(int id_, int high_, int leng_, int dept_, int price_, std::string &material_, std::string &shape_) : Furniture(id_, high_, leng_, dept_, price_, material_){
	shape = shape_;
}

void Table::PrintInfo(){
	std::cout << "Table (ID = " << id << ") information:" << std::endl;
	Furniture::PrintInfo();
	std::cout << "Shape: " << shape << std::endl;
	std::cout << std::endl;
}

//WARDROBE============================
Wardrobe::Wardrobe() : Furniture(){
	shelfcnt = 0;
}

Wardrobe::Wardrobe(int id_, int high_, int leng_, int dept_, int price_, std::string &material_, int shelfcnt_) : Furniture(id_, high_, leng_, dept_, price_, material_){
	shelfcnt = shelfcnt_;
}

void Wardrobe::PrintInfo(){
	std::cout << "Wardrobe info:" << std::endl;
	Furniture::PrintInfo();
	std::cout << "Shelf count: " << shelfcnt << std::endl << std::endl;;
}

//COMBINED_WARDROBE===================
CombinedWardrobe::CombinedWardrobe() : Wardrobe(), Table(){
	name = std::string(NULL_STR);
}
CombinedWardrobe::CombinedWardrobe(int id_, CombinedWardrobe &T){
	name = std::string(NULL_STR);
}
CombinedWardrobe::CombinedWardrobe(int id_, int high_, int leng_, int dept_, int price_ , std::string &material_, std::string &shape_) : Wardrobe(id_, high_, leng_, dept_, price_, material_, 0), Table(id_, high_, leng_, dept_, price_, material_, shape_){
	name = std::string(NULL_STR);
}
const std::string& CombinedWardrobe::GetName() const { return name; }

void CombinedWardrobe::PrintInfo() {
	std::cout << "Combined wardrobe info:" << std::endl;
	Table::Furniture::PrintInfo();
	std::cout << "Name: " << name << std::endl << std::endl;
}

//SPETIAL_FURNITURE===================
bool SpetialFurniture::CorrectHash(std::string& str) const{
	//let's suppose that it is an ideal hash-function
	return false;
}

SpetialFurniture::SpetialFurniture() : Furniture(){
}

int SpetialFurniture::GetHigh(std::string& auth) const{
	if (CorrectHash(auth) == true)
		return measures.high;
	else{
		std::cout << "access is denied" << std::endl << std::endl;
		return -1;
	}
}

int SpetialFurniture::GetLeng(std::string& auth) const{
	if (CorrectHash(auth) == true)
		return measures.leng;
	else{
		std::cout << "access is denied" << std::endl << std::endl;
		return -1;
	}
}

int SpetialFurniture::GetDept(std::string& auth) const{
	if (CorrectHash(auth) == true)
		return measures.dept;
	else{
		std::cout << "access is denied" << std::endl << std::endl;
		return -1;
	}
}

int SpetialFurniture::GetPrice(std::string& auth) const{
	if (CorrectHash(auth) == true)
		return price;
	else{
		std::cout << "access is denied" << std::endl << std::endl;
		return -1;
	}
}

int SpetialFurniture::GetID(std::string& auth) const{
	if (CorrectHash(auth) == true)
		return price;
	else{
		std::cout << "access is denied" << std::endl << std::endl;
		return -1;
	}
}

//SECRET_FURNITURE===================
bool SecretFurniture::CorrectHash(std::string& str) const{
	//let's suppose that it is an ideal hash-function
	return false;
}

SecretFurniture::SecretFurniture() : SpetialFurniture(){
}

int SecretFurniture::GetHigh(std::string& auth) const{
	if (CorrectHash(auth) == true)
		return measures.high;
	else{
		std::cout << "access is denied" << std::endl << std::endl;
		return -1;
	}
}

int SecretFurniture::GetLeng(std::string& auth) const{
	if (CorrectHash(auth) == true)
		return measures.leng;
	else{
		std::cout << "access is denied" << std::endl << std::endl;
		return -1;
	}
}

int SecretFurniture::GetDept(std::string& auth) const{
	if (CorrectHash(auth) == true)
		return measures.dept;
	else{
		std::cout << "access is denied" << std::endl << std::endl;
		return -1;
	}
}

int SecretFurniture::GetPrice(std::string& auth) const{
	if (CorrectHash(auth) == true)
		return price;
	else{
		std::cout << "access is denied" << std::endl << std::endl;
		return -1;
	}
}

int SecretFurniture::GetID(std::string& auth) const{
	if (CorrectHash(auth) == true)
		return price;
	else{
		std::cout << "access is denied" << std::endl << std::endl;
		return -1;
	}
}
