#include "bin_tree.h"
#include <algorithm>

#define filter_tree_it(f) filter_iterator<binary_tree<int, char>::iterator, decltype(f)>

//using namespace std;

auto general_lambda = [](){};
typedef decltype(general_lambda) lambda_type;

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

	auto _f = [](qnode<node<int, char>*> qn){ if (qn.obj->data.key > 8) std::cout << qn.obj->data.key << " is bigger than 8" << std::endl; };
	auto _g = [](binary_tree<int, char>::iterator bt_i){ std::cout << (*bt_i).obj->data.key << " is bigger than 8" << std::endl; };


	typedef filter_iterator<binary_tree<int, char>::iterator, lambda_type> filter_tree_iter;

	auto _u = [](binary_tree<int, char>::iterator bt_i, bool &b){ b = (*bt_i).obj->data.key == 9; };

	bt.print_tree();

	std::for_each(filter_tree_it(_u)(bt.begin()), filter_tree_it(_u)(bt.end()), _g);

	bt.delete_tree(&base(bt));
}

void stack_func(){
	stack<int> st;
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
