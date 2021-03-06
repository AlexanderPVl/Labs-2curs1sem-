#include "Strategy.h"
#include "Furniture.h"

#include <vector>
#include <conio.h>

//#define ESC 27

template<class T>
extern void AddToVector(T* class_, std::vector<T*> &v);

void StrategyFunc();
void FurnitureFunc();
int GetComand(std::string& command);
void Iterate();

void StrategyFunc(){
	std::cout << "STRATEGY FUNCTION:=======================================================" << std::endl;

	/*std::vector<Unit*> unitarray;

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

	_sleep(2000);

	//hab->Attac(*con);
	unitarray[0]->Attac(*unitarray[1]);
	unitarray[1]->PrintInfo();
	unitarray[1]->Move(3);
	_sleep(2000);
	unitarray[0]->Attac(*unitarray[1]);
	unitarray[1]->PrintInfo();

	//con->PrintInfo();*/
	Player player(1, std::string("Username"));
	for (int i = 0; i < 3; ++i)
		player.AddUnit(0);
	for (int i = 0; i < 3; ++i)
		player.AddUnit(1);
	for (int i = 0; i < 3; ++i)
		player.AddUnit(2);
	player.PrintUnitArray();

	Ferguson ferg;

	player.ForEachUnitID_Attac(1, &ferg);
	player.ForEachUnitID_Attac(1, &ferg);
	player.ForEachUnitID_Attac(2, &ferg);

	ferg.PrintInfo();

}

void FurnitureFunc(){
	std::cout << std::endl << std::endl << std::endl << "FURNITURE FUNCTION:======================================================" << std::endl << std::endl;
	std::vector <Furniture*> furn_vec;
	Table table1(1, 3, 4, 5, 1, std::string("Wood"), std::string("Square"));
	Table table2(2, table1);
	Table* t1 = new Table;
	Wardrobe* w1 = new Wardrobe;
	CombinedWardrobe* cw1 = new CombinedWardrobe;
	SpetialFurniture* spf1 = new SpetialFurniture(118, std::string("ExampleKey"));
	SpetialFurniture* spf2 = new SpetialFurniture(*spf1, std::string("ExampleKey"), 1024, std::string("ExampleKey"));
	SecretFurniture* sef1 = new SecretFurniture;
	for (int i = 0; i < 4; ++i) table1.AddTo(furn_vec);
	for (int i = 0; i < 4; ++i) table2.AddTo(furn_vec); //furn_vec.push_back(&table2);
	for (int i = 0; i < 4; ++i) w1->AddTo(furn_vec); //furn_vec.push_back(w1);
	for (int i = 0; i < 2; ++i) cw1->AddTo(furn_vec); //furn_vec.push_back(cw1);
	//spf1->AddTo(furn_vec);
	//sef1->AddTo(furn_vec);
	//AddToVector<Furniture>(sef1, furn_vec);
	spf1->AddTo(furn_vec);
	spf2->AddTo(furn_vec);
	sef1->AddTo(furn_vec);

	for (auto a : furn_vec) a->PrintInfo();

	spf1->GetID(std::string("ExampleKey"));
	sef1->GetDept(std::string("ExampleKey"));
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
	FurnitureFunc();
	//std::cout << Hash(std::string("123"));



	return 0;
}
