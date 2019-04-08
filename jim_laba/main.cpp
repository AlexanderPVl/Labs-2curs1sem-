#include "LinkedList.h"
#include "BinaryTree.h"

void bin_tree(){
	binary_tree<int, char> tree1;
	int sz;
	tree1.add(3, 'c');
	tree1.add(1, 'a');
	tree1.add(2, 'b');
	tree1.add(5, 'e');
	tree1.add(4, 'd');
	tree1.add(7, 'e');
	tree1.add(6, 'e');

	//print_tree(tree1.get_base());
	subtree_size(tree1.get_base()->r->r, &sz);
	std::cout << "size: " << sz << std::endl;
	//problem_10(tree1.get_base());
	problem_pred(tree1.get_base(), case_8<int, char>);
	print(tree1.get_base()->l->r);
}

void link_list(){
	linked_list<int, char> list1;
	linked_list<int, char> list2;
	node<int, char> nd1;

	list1.end_add(node<int, char>(1, 'a'));
	list1.end_add(node<int, char>(2, 'b'));
	list1.end_add(node<int, char>(3, 'c'));
	//list1.end_add(node<int, char>(4, 'd'));
	list1.end_add(node<int, char>(4, 'd'));
	list1.end_add(node<int, char>(5, 'e'));
	list1.end_add(node<int, char>(6, 'f'));
	//list1.end_add(node<int, char>(7, 'g'));
	//list1.beg_add(node<int, char>(3, 'd'));
	//list1.delete_node(list1.get_base());

	//list1.del_lastmax();
	//list1.del_lastval('b');
	cyclic_left(list1, 2);


	list1.print();

	std::cout << list1.elem_cnt() << std::endl;
}

int main(){
	//link_list();
	bin_tree();

}