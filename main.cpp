#include "bin_tree.h"
#include <algorithm>

//using namespace std;

void bin_tree_fucn(){
	node<int, char> nd1;
	nd1.data.key = 10; nd1.data.val = 'a';
	binary_tree<int, char> bt;
	//bt.add(nd1);
	bt.add(10, 'a');
	bt.add(8, 'b');
	bt.add(7, 'c');
	bt.add(9, 'u');
	bt.add(12, 'v');
	bt.add(11, 'x');
	bt.add(13, 'w');

	//print_tree(&base(bt));

	bt.range_for([](node<int, char> &nd){ print(nd); }, &base(bt), 8, 11);

	binary_tree<int, char>::iterator t;
	//print(*t);
}

void queue_func(){
	queue<int> q;
	int a;
	for (int i = 1; i <= 17; ++i){
		q.push(i);
	}

	std::for_each(q.begin(), q.end(), [](int t){std::cout << t << " "; });
	//q.delete_all();
	for (int i = 1; i <= 4; ++i){
		q.pop();
	}
	q.delete_excess();
	std::cout << std::endl;
	std::for_each(q.last(), q.end(), [](int t){std::cout << t << " "; });
}

int main(){
	bin_tree_fucn();
	queue_func();

	return 0;
}
