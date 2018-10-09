#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef vector <int> IntVec;

class Player{
protected:
	typedef struct{
		int X;
		int Y;
	} Coordinates;
	Coordinates Coord;
	int ID;
	int HP;
	string Name;
public:
	Player(int id, int hp, string name){
		Coord = { 0, 0 };
		ID = id;
		HP = hp;
		Name = name;
	}
	void MoveNor(){ ++Coord.Y; }
	void MoveSou(){ --Coord.Y; }
	void MoveWes(){ --Coord.X; }
	void MoveEas(){ ++Coord.X; }

	virtual void PrintInfo() = 0{
		cout << "Player name: " << Name;
	}
};

class Developer : protected Player{
protected:
	string Language;

public:
	Developer(int id, int hp, string name, string lang) : Player(id, hp, name){
		Language = lang;
	}
	void PrintInfo() override{
		cout << "Developer name: " << Name << endl;
	}
};
