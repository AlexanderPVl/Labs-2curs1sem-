#pragma once

#include "Includes.h"
#define FURNITURE_CONSTRUCT_ARGLIST id_, high_, leng_, dept_, price_, material_

class Furniture{
protected:
	typedef struct{
		int high;
		int leng;
		int dept;
	} Measures;

	Measures measures;
	std::string material;
	int price;
	int id;
public:
	Furniture();
	Furniture(int id_, int high_ = 0, int leng_ = 0, int dept_ = 0, int price_ = 0, std::string &material_ = std::string(NULL_STR));
	int GetHigh() const { return measures.high; }
	int GetLeng() const { return measures.leng; }
	int GetDept() const { return measures.dept; }

	virtual void PrintInfo() = 0;
};

class Table : public Furniture{
private:
	std::string shape;
public:
	Table();
	Table(int id_, Table &T = Table());
	Table(int id_, int high_ = 0, int leng_ = 0, int dept_ = 0, int price_ = 0, std::string &material_ = std::string(NULL_STR), std::string &shape_ = std::string(NULL_STR));
	const std::string& GetShape() const { return shape; }

	void PrintInfo() override final;
};

class Wardrobe : public Furniture{
private:
	int shelfcnt;
public:
	Wardrobe();

	void PrintInfo() override final;
};

/*class CombinedShelf : public Furniture{
private:
	std::string shape;
public:
	CombinedShelf();
	CombinedShelf(int id_, CombinedShelf &T = CombinedShelf());
	CombinedShelf(int id_, int high_ = 0, int leng_ = 0, int dept_ = 0, int price_ = 0, std::string &material_ = std::string(NULL_STR), std::string &shape_ = std::string(NULL_STR));
	const std::string& GetShape() const { return shape; }

	void PrintInfo() override final;
};*/
