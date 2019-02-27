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

	bt.range_for([](node<int, char> &nd){ print(nd); }, &base(bt), 8, 11);
	bt.for_each([](node<int, char> &nd){ print(nd); }, &base(bt));

	//std::for_each(bt.begin(), bt.end(), [](qnode<node<int, char>*> nd){ print(*nd.obj); });

	auto f = [](qnode<node<int, char>*> qn){ if (qn.obj->data.key > 8) std::cout << qn.obj->data.key << " is bigger than 8" << std::endl; };

	bt.print_tree();

	filter_iterator < binary_tree<int, char>::iterator, decltype(f)> f_it();
	std::for_each(bt.begin(), bt.end(), f);

	bt.delete_tree(&base(bt));
}

void stack_func(){
	stack<int> st;
	int a;
	for (int i = 1; i <= 17; ++i){
		st.push(i);
	}

	std::for_each(st.begin(), st.end(), [](int t){std::cout << t << " "; });

	for (int i = 1; i <= 4; ++i){
		st.pop();
	}
	st.delete_excess();
	std::cout << std::endl;
	std::for_each(st.last(), st.end(), [](int t){std::cout << t << " "; });

	st.delete_all();
}

void queue_func(){
	queue<int> q;

	for (int i = 1; i <= 4; ++i){
		q.push(i);
	}
	for (int i = 0; i < 4; ++i){
		std::cout << q.pop();
	}
	q.print();
}

int main(){
	bin_tree_fucn();
	stack_func();
	queue_func();


	return 0;
}
