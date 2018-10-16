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
	int GetPrice() const { return price; }
	int GetID() const { return id; }

	virtual void PrintInfo() = 0;
};

class Table : virtual public Furniture{
private:
	std::string shape;
public:
	Table();
	Table(int id_, Table &T = Table());
	Table(int id_, int high_ = 0, int leng_ = 0, int dept_ = 0, int price_ = 0, std::string &material_ = std::string(NULL_STR), std::string &shape_ = std::string(NULL_STR));
	const std::string& GetShape() const { return shape; }

	void PrintInfo() override;
};

class Wardrobe : virtual public Furniture{
private:
	int shelfcnt;
public:
	Wardrobe();
	Wardrobe(int id_, int high_ = 0, int leng_ = 0, int dept_ = 0, int price_ = 0, std::string &material_ = std::string(NULL_STR), int shelfcnt_ = 0);

	void PrintInfo() override;
};

class CombinedWardrobe : public Table, public Wardrobe{
private:
	std::string name;
public:
	CombinedWardrobe();
	CombinedWardrobe(int id_, CombinedWardrobe &T = CombinedWardrobe());
	CombinedWardrobe(int id_, int high_ = 0, int leng_ = 0, int dept_ = 0, int price_ = 0, std::string &material_ = std::string(NULL_STR), std::string &shape_ = std::string(NULL_STR));
	const std::string& GetName() const;

	void PrintInfo() override final;
};

class SpetialFurniture : protected virtual Furniture{
private:
	bool CorrectHash(std::string& str) const;
	void PrintInfo() override{ Furniture::PrintInfo(); }
public:
	SpetialFurniture();
	int GetHigh(std::string& auth) const;
	int GetLeng(std::string& auth) const;
	int GetDept(std::string& auth) const;
	int GetPrice(std::string& auth) const;
	int GetID(std::string& auth) const;
};

class SecretFurniture : private SpetialFurniture{
private:
	bool CorrectHash(std::string& str) const;
	void PrintInfo() override{ Furniture::PrintInfo(); }
public:
	SecretFurniture();
	int GetHigh(std::string& auth) const;
	int GetLeng(std::string& auth) const;
	int GetDept(std::string& auth) const;
	int GetPrice(std::string& auth) const;
	int GetID(std::string& auth) const;
};
