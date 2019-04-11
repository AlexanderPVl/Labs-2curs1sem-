#include "LinkedList.h"
#include "BinaryTree.h"
#include "Graph.h"

void bin_tree(){
	binary_tree<int, char> tree1;
	int sz;
	tree1.add(30, 'c');
	tree1.add(10, 'a');
	tree1.add(20, 'b');
	tree1.add(50, 'e');
	tree1.add(40, 'd');
	tree1.add(70, 'e');
	tree1.add(60, 'e');

	subtree_size(tree1.get_base()->r->r, &sz);
	std::cout << "size: " << sz << std::endl;

	problem_pred(tree1.get_base(), case_10<int, char>);
	print(tree1.get_base()->r->r->r->r);
}

void link_list1(){
	linked_list<int, char> list1;
	linked_list<int, char> list2;

	list1.end_add(node<int, char>(3, 'c'));
	list1.end_add(node<int, char>(1, 'a'));
	list1.end_add(node<int, char>(2, 'b'));
	list1.end_add(node<int, char>(3, 'c'));
	//list1.end_add(node<int, char>(4, 'd'));
	//list1.end_add(node<int, char>(5, 'e'));
	//list1.end_add(node<int, char>(6, 'f'));
	cyclic_left(list1, 2);
	list1.print();

	list2.end_add(node<int, char>(1, 'a'));
	list2.end_add(node<int, char>(2, 'b'));
	list2.end_add(node<int, char>(3, 'c'));
	//list2.end_add(node<int, char>(4, 'd'));
	//list2.end_add(node<int, char>(5, 'e'));
	//list2.end_add(node<int, char>(6, 'f'));
	prt_truth(list1 == list2);
}

void link_list2(){
	linked_list<int, char> list1;

	list1.auto_fill(9);
	cyclic_left(list1, 2);
	//list1.delete_all();
	list1.print();

	std::cout << list1.elem_cnt() << std::endl;
}

void var3(){
	Task1();
	Task16(3);
}

int main(){
	//link_list1();
	//link_list2();
	//bin_tree();

	var3();
}
