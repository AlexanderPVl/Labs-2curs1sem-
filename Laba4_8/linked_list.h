#include <algorithm>

template<class T>
struct node{
	T obj;
	node<T>* next;
	node<T>* prev;
};

template<class T>
class linked_list{
public:
	class iterator{
	public:
		iterator(node<T>* ptr_) : curr_node(ptr_) {}
		typedef iterator self_type;
		typedef T& reference;
		typedef T value_type;
		typedef T* pointer;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef int difference_type;
		~iterator() = default;
		reference operator * () { return curr_node->obj; }
		self_type operator ++ () { curr_node = curr_node->next; return *this; }
		self_type operator -- () { curr_node = curr_node->prev; return *this; }
		bool operator != (iterator it) { return it.curr_node != curr_node; }
		bool operator == (iterator it) { return it.curr_node == curr_node; }
		bool operator == (std::reverse_iterator<iterator> rit) { return rit.current == curr_node; }
		void operator = (iterator it) { curr_node = it.curr_node; }
	private:
		node<T>* curr_node;
	};

	linked_list() { base_node = nullptr; }
	void add(T obj_);
	void print();
	void rprint();
	void delete_all();
	iterator begin() { return iterator(base_node); }
	iterator cbegin() { return iterator(link_node->prev); }
	std::reverse_iterator<iterator> rbegin() { return std::reverse_iterator<iterator>(link_node->prev); }
	std::reverse_iterator<iterator> rend() { return std::reverse_iterator<iterator>(link_node->next); }
	iterator end() { return iterator(link_node); }
	iterator cend() { return iterator(link_node); }
private:
	node<T>* base_node;
	node<T>* link_node;
};

template<class T>
void linked_list<T>::print(){
	if (!base_node) return;
	node<T>* curr = base_node;
	do{
		std::cout << curr->obj << " ";
		curr = curr->next;
	} while (curr != link_node);
}

template<class T>
void linked_list<T>::rprint(){
	if (!base_node) return;
	node<T>* curr = link_node->prev;
	do{
		std::cout << curr->obj << " ";
		curr = curr->prev;
	} while (curr != link_node);
}

template<class T>
void linked_list<T>::add(T obj_){
	node<T>* new_node = new node<T>;
	new_node->obj = obj_;
	if (!base_node){
		base_node = new_node;
		link_node = new node<T>;
		base_node->prev = base_node->next = link_node;
		link_node->next = base_node;
		link_node->prev = base_node;
		return;
	}
	new_node->prev = link_node->prev;
	link_node->prev->next = new_node;
	link_node->prev = new_node;
	new_node->next = link_node;
}

template<class T>
void linked_list<T>::delete_all(){
	node<T>* curr = base_node;
	while (curr != link_node){
		base_node = base_node->next;
		delete curr;
		curr = base_node;
	}
	delete link_node;
	link_node = base_node = nullptr;
}