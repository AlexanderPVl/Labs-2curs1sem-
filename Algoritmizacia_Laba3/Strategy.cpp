#include "Strategy.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef vector <int> IntVec;

#include "Strategy.h"

//VECTOR2=================================
Vector2::Vector2(){ Set(0, 0); }

Vector2::Vector2(double x_, double y_){ Set(x_, y_); }

void Vector2::Set(double x_, double y_){
	x = x_;
	y = y_;
}

double Vector2::Length(){
	return sqrt(x*x + y*y);
}

Vector2& Vector2::Normalize(){
	double len = this->Length();
	x /= len;
	y /= len;
	return *this;
}

Vector2& Vector2::Rotate(double deg){
	deg = deg * PI / 180;
	double x_ = x;
	double y_ = y;
	x = x_ * cos(deg) - y_ * sin(deg);
	y = x_ * sin(deg) + y_ * cos(deg);
	return *this;
}

Vector2& Vector2::operator += (const Vector2& v){
	this->x = this->x + v.x;
	this->y = this->y + v.y;
	return *this;
}

Vector2& Vector2::operator = (const Vector2& v){
	this->x = v.x;
	this->y = v.y;
	return *this;
}

std::ostream& Vector2::operator << (std::ostream& ost){
	std::cout << "(" << x << ", " << y << ")" << std::endl;
	return ost;
}

std::ostream& operator << (std::ostream& ost, const Vector2& v){
	std::cout << "(" << v.x << ", " << v.y << ")" << std::endl;
	return ost;
}

Vector2 operator + (const Vector2& v1, const Vector2& v2){
	return Vector2(v1.x + v2.x, v1.y + v2.y);
}

Vector2 operator - (const Vector2& v1, const Vector2& v2){
	return Vector2(v1.x - v2.x, v1.y - v2.y);
}

Vector2 operator * (const Vector2& v, const double k){
	return Vector2(v.x * k, v.y * k);
}

bool operator == (const Vector2& v1, const Vector2& v2){
	return (v1.x == v2.x && v1.y == v2.y);
}

//PLAYER==================================
Player::Player(int id_, string& name_){
	id = id_;
	name = name_;
}

Player::~Player(){
	for (auto unit : unit_array)delete unit;
}

void Player::AddUnit(int id){
	switch (id){
	case 0:
		unit_array.push_back(new Connor);
		break;
	case 1:
		unit_array.push_back(new Habib);
		break;
	case 2:
		unit_array.push_back(new Ferguson);
		break;
	default:
		return;
	}
}

void Player::PrintUnitArray(){
	for (auto unit : unit_array)unit->PrintInfo();
}

void Player::ForEachUnitID_Attac(int id, Unit* u){
	int i = 0;
	for_each(unit_array.begin(), unit_array.end(), [u, id](Unit* unit){if (unit->GetId() == id)unit->Attac(*u); });
}

void Player::PrintInfo(){
	std::cout << "ID: " << id << std::endl;
	std::cout << "Name: " << name << std::endl;
}

//UFC_UNIT===============================
void UFC_Unit::Hit(int n){
	if (hp < 0){
		alive = false;
		hp = 0;
	}
	else if (!alive)return;
	else hp -= n;
}
void UFC_Unit::Attac(Unit& u) const{
	if (time(NULL) - last_attac_time <= attac_delay){
		std::cout << ">Not time yet!" << std::endl << std::endl;
		return;
	}
	if ((position - u.GetPosition()).Length() > range){
		std::cout << ">Enemy is too far" << std::endl << std::endl;
		return;
	}
	last_attac_time = time(NULL);
	std::cout << ">" "ID " << id << " hits ID " << u.GetId() << " with " << attac << " damage" << std::endl << std::endl;
	u.Hit(attac);
}

Vector2& UFC_Unit::Move(double time){
	position += direction * time * speed;
	return position;
}

Vector2& UFC_Unit::Rotate(int deg){
	direction.Rotate(deg);
	return direction;
}

const Vector2& UFC_Unit::GetPosition() const { return position; }

const Vector2& UFC_Unit::GetDirection() const { return direction; }

void UFC_Unit::GoToPoint(Vector2& point) {
	direction = (point - position).Normalize();
	double t = (point - position).Length() / speed;
	Move(t);
}

int UFC_Unit::GetId() const { return id; }

time_t UFC_Unit::Cooldown() const{
	return time(NULL) - last_attac_time;
}

void UFC_Unit::PrintInfo() const {
	std::cout << "ID: " << id << std::endl;
	std::cout << "Hp: " << hp << std::endl << "Attac: " << attac << std::endl << "Position: " << position << "Direction: " << direction;
	std::cout << "Speed: " << speed << std::endl << std::endl;
}

//CONNOR=================================

Connor::Connor(){
	id = 0;
	hp = 100;
	attac = 20;
	speed = 200;
	range = 128; //
	alive = true;
	position.Set(0, 0);
	direction.Set(1, 0);
	attac_delay = 1;
	last_attac_time = 0;
}

//HABIB==================================

Habib::Habib(){
	id = 1;
	hp = 150;
	attac = 30;
	speed = 220;
	range = 128; //
	alive = true;
	position.Set(0, 0);
	direction.Set(1, 0);
	attac_delay = 1;
	last_attac_time = 0;
}

//FERGUSON================================

Ferguson::Ferguson(){
	id = 2;
	hp = 130;
	krit = 2;
	attac = 50;
	speed = 230;
	range = 128; //
	alive = true;
	position.Set(0, 0);
	direction.Set(1, 0);
	attac_delay = 1;
	last_attac_time = 0;
}
void Ferguson::Attac(Unit& u) const{
	if (time(NULL) - last_attac_time <= attac_delay){
		std::cout << ">Not time yet!" << std::endl << std::endl;
		return;
	}
	if ((position - u.GetPosition()).Length() > range){
		std::cout << ">Enemy is too far" << std::endl << std::endl;
		return;
	}
	last_attac_time = time(NULL);
	u.Hit(attac * krit);
}
