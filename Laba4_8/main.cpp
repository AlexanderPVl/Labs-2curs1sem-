#include <iostream>

#include "linked_list.h"

int main(){
	int i = 0;
	linked_list<int> ll;
	ll.add(1); ll.add(2); ll.add(3);
	//ll.delete_all();
	ll.print();
	//std::for_each(ll.begin(), ll.end(), [](int i){ std::cout << i*i << " "; });
	std::for_each(ll.rbegin(), ll.rend(), [](int i){ std::cout << i*i << " "; });
	return 0;
}