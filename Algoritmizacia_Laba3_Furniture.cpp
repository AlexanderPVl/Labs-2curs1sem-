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
void Wardrobe::PrintInfo(){
	std::cout << "Wardrobe info:" << std::endl;
	Furniture::PrintInfo();
	std::cout << "Shelf count: " << shelfcnt << std::endl << std::endl;;
}
