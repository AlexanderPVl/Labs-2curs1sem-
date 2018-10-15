#pragma once

#include <vector>
#include <iomanip>
#include <time.h>

#include "Includes.h"

#define PI 3.141592653589793

class Vector2{
public:
	double x;
	double y;

	Vector2();
	Vector2(double x_, double y_);
	void Set(double x_ = 0, double y_ = 0);
	double Length();
	Vector2& Normalize();
	Vector2& Rotate(double deg);

	Vector2& operator += (const Vector2& v);
	Vector2& operator = (const Vector2& v);
	std::ostream& operator << (std::ostream& ost);
};
//VECTOR2 operators
//==============================<
Vector2 operator + (const Vector2& v1, const Vector2& v2);
Vector2 operator - (const Vector2& v1, const Vector2& v2);
Vector2 operator * (const Vector2& v1, const double k);
std::ostream& operator << (std::ostream& ost, const Vector2& v);
bool operator == (const Vector2& v1, const Vector2& v2);
//==============================/>

class Player{
protected:
	int id;
	std::string name;
public:
	Player(int id, std::string& name);

	virtual void PrintInfo() = 0;
};

class Unit{
public:
	Unit(){}
	virtual void Hit(int) {}
	virtual void Attac(Unit&) {}
	virtual Vector2& Move(double) = 0 {}
	virtual Vector2& Rotate(int) = 0 {}
	virtual Vector2& GetPosition() = 0 {}
	virtual Vector2& GetDirection() = 0 {}
	virtual void GoToPoint(Vector2&) = 0 {}

	virtual void PrintInfo() = 0 {}
	virtual ~Unit() {}
};

class UFC_Unit : public Unit{
protected:
	int id;
	int hp;
	int attac;
	int range; //
	bool alive;
	Vector2 position;
	Vector2 direction;

	time_t attac_delay;
	time_t last_attac_time;

	double speed;

public:

	void Hit(int n) final override;
	void Attac(Unit& u) override;
	Vector2& Move(double) final override;
	Vector2& Rotate(int) final override;
	Vector2& GetPosition() final override;
	Vector2& GetDirection() final override;
	void GoToPoint(Vector2& point) final override;

	void PrintInfo() override = 0;
};

class Connor : public UFC_Unit{
public:
	Connor();

	void PrintInfo() final override { UFC_Unit::PrintInfo(); }
};

class Habib : public UFC_Unit{
public:
	Habib();

	void PrintInfo() final override { UFC_Unit::PrintInfo(); }
};

class Ferguson : public UFC_Unit{
	int krit;
public:
	Ferguson();
	void Attac(Unit& u) final override;

	void PrintInfo() final override { UFC_Unit::PrintInfo(); }
};
