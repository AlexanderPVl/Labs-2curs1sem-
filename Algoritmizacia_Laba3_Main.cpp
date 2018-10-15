#include "Strategy.h"
#include "Furniture.h"

#include <vector>
#include <conio.h>

//#define ESC 27

void StrategyFunc();
void FurnitureFunc();
int GetComand(std::string& command);
void Iterate();

void StrategyFunc(){
	std::cout << "STRATEGY FUNCTION:=======================================================" << std::endl;

	std::vector<Unit*> unitarray;

	//Connor* con = new Connor;
	//Habib* hab = new Habib;
	unitarray.push_back(new Habib);
	unitarray.push_back(new Connor);

	for (auto unit : unitarray){
		unit->PrintInfo();
	}

	//hab->Attac(*con);
	//hab->Attac(*con);
	unitarray[0]->Attac(*unitarray[1]);
	unitarray[0]->Attac(*unitarray[1]);
	unitarray[1]->PrintInfo();
	//con->PrintInfo();

	_sleep(4000);

	//hab->Attac(*con);
	unitarray[0]->Attac(*unitarray[1]);
	unitarray[1]->PrintInfo();
	unitarray[1]->Move(3);
	_sleep(4000);
	unitarray[0]->Attac(*unitarray[1]);
	unitarray[1]->PrintInfo();

	//con->PrintInfo();

}

void FurnitureFunc(){
	std::cout << std::endl << std::endl << std::endl << "FURNITURE FUNCTION:======================================================" << std::endl << std::endl;
	std::vector <Furniture*> furn_vec;
	Table table1(1, 3, 4, 5, 1, std::string("Wood"), std::string("Square"));
	Table table2(2, table1);
	Table* t1 = new Table;
	Wardrobe* w1 = new Wardrobe;
	for (int i = 0; i < 4; ++i) furn_vec.push_back(&table1);
	for (int i = 0; i < 4; ++i) furn_vec.push_back(&table2);
	for (int i = 0; i < 4; ++i) furn_vec.push_back(w1);

	for (auto a : furn_vec) a->PrintInfo();
}

int GetComand(std::string& command){
	if (command == "end")return 0;
	else if (command == "printinfo")return 1;
	else if (command == "clear")return 2;

	return -1;
}

void Iterate(){
	std::string command;
	int command_id;

	std::cout << "Enter commands here" << std::endl;
	while (1){
		std::cout << std::endl << ">";
		std::cin >> command;
		command_id = GetComand(command);
		switch (command_id){
		case 0:return;
		case 1:
			std::cout << "Print info" << std::endl;
			break;
		default:
			std::cout << "Error has occured!" << std::endl;
			break;
		case -1:
			std::cout << "Unknown command!" << std::endl;
			break;
		case 2:
			system("cls");
			std::cout << "Enter commands here" << std::endl;
			break;
		}
	}
}

int main(){
	//Iterate();
	StrategyFunc();
	//std::cout << std::endl;
	//FurnitureFunc();
	//std::cout << Hash(std::string("123"));

	return 0;
}
