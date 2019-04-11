#pragma once

#include <iostream>
#include <set>
#include <ostream>
#include <algorithm>

template<class T>
struct general_set{
	general_set() { arr = nullptr; size = 0; }
	void insert(T& obj){
		if (!size) {
			arr = new T[1];
			arr[0] = obj;
			++size;
			return;
		}
		for (int i = 0; i < size; ++i){
			if (arr[i] == obj)return;
		}
		T* arr1 = new T[size];
		for (int i = 0; i < size; ++i){
			arr1[i] = arr[i];
		}
		delete[] arr;
		arr = new T[size + 1];
		for (int i = 0; i < size; ++i){
			arr[i] = arr1[i];
		}
		delete[] arr1;
		arr[size] = obj;
		++size;
	}
	bool has(T& obj){
		for (int i = 0; i < size; ++i){
			if (arr[i] == obj)return 1;
		}
		return 0;
	}
	T* arr;
	int size;
};

template<class Key, class Val>
struct node{
	node() = default;
	node(Key key_, Val val_){ key = key_; val = val_; }
	node<Key, Val> *next;
	node<Key, Val> *prev;
	Key key;
	Val val;
	void operator = (node &nd){ key = nd.key; val = nd.val; }
	bool operator == (node &nd){ return key == nd.key && val == nd.val; }
	bool operator < (node &nd){ return key < nd.key || val < nd.val; }
	bool operator != (node &nd){ return key != nd.key || val != nd.val; }
};

template<class Key, class Val>
class linked_list{ 
public:
	linked_list() { base_node = nullptr; }
	linked_list(const node<Key, Val>*, int);
	void cpy_from(const node<Key, Val>*, int);
	void beg_add(node<Key, Val>);
	void end_add(node<Key, Val>);
	void delete_node(node<Key, Val>*);
	void del_firstmax();
	void del_lastmax();
	void del_firstval(Val);
	void del_lastval(Val);
	void beg_add();
	void end_add();
	void print();
	void rprint();
	void delete_all();
	void auto_fill(int);
	bool is_empty() { return base_node == nullptr; }
	int elem_cnt();
	node<Key, Val>* get_base() { return base_node; }

	bool operator == (linked_list<Key, Val> ll);
private:
	node<Key, Val>* base_node;
};

template<class Key, class Val>
linked_list<Key, Val>::linked_list(const node<Key, Val>* node_arr, int cnt){
	for (int i = 0; i < cnt; ++i){
		end_add(node_arr[i]);
	}
}

template<class Key, class Val>
void linked_list<Key, Val>::cpy_from(const node<Key, Val>* node_arr, int cnt){
	for (int i = 0; i < cnt; ++i){
		end_add(node_arr[i]);
	}
}

template<class Key, class Val>
int linked_list<Key, Val>::elem_cnt(){
	if (!base_node) return 0;
	int cnt = 0;
	node<Key, Val>* curr = base_node;
	do{
		curr = curr->next;
		++cnt;
	} while (curr != base_node);
	return cnt;
}

template<class Key, class Val>
void linked_list<Key, Val>::print(){
	if (!base_node) return;
	node<Key, Val>* curr = base_node;
	do{
		std::cout << curr->val << ", " << curr->key << std::endl;
		curr = curr->next;
	} while (curr != base_node);
}

template<class Key, class Val>
void linked_list<Key, Val>::rprint(){
	if (!base_node) return;
	node<Key, Val>* curr = base_node->prev;
	do{
		std::cout << curr->val << std::endl;
		curr = curr->prev;
	} while (curr != base_node->prev);
}

template<class Key, class Val>
void linked_list<Key, Val>::delete_node(node<Key, Val>* ptr){
	ptr->prev->next = ptr->next;
	ptr->next->prev = ptr->prev;
	if (ptr == base_node) {
		*base_node = *(base_node->next);
		ptr = base_node->next;
		base_node->next = base_node->next->next;
		base_node->prev->next = base_node;
		if (base_node->next == base_node) { delete base_node; base_node = nullptr; }
		else {
			delete ptr;
		}
	}
	else delete ptr;
}

template<class Key, class Val>
void linked_list<Key, Val>::del_firstmax(){
	node<Key, Val>* ptr = base_node;
	node<Key, Val>* curr = base_node->next;
	while (curr != base_node){
		if (curr->key > ptr->key) ptr = curr;
		curr = curr->next;
	}
	delete_node(ptr);
}

template<class Key, class Val>
void linked_list<Key, Val>::del_firstval(Val val){
	node<Key, Val>* ptr = nullptr;
	node<Key, Val>* curr = base_node->next;
	if (base_node->val == val) { delete_node(base_node); return; }
	while (curr != base_node){
		if (curr->val == val) { ptr = curr; break; }
		curr = curr->next;
	}
	if (ptr) delete_node(ptr);
}

template<class Key, class Val>
void linked_list<Key, Val>::del_lastmax(){
	node<Key, Val>* ptr = base_node;
	node<Key, Val>* curr = base_node->next;
	while (curr != base_node){
		if (curr->key >= ptr->key) ptr = curr;
		curr = curr->next;
	}
	delete_node(ptr);
}

template<class Key, class Val>
void linked_list<Key, Val>::del_lastval(Val val){
	node<Key, Val>* ptr = nullptr;
	node<Key, Val>* curr = base_node->next;
	while (curr != base_node){
		if (curr->val == val) { ptr = curr; }
		curr = curr->next;
	}
	if (ptr) { delete_node(ptr); return; }
	if (base_node->val == val) delete_node(base_node);
}

template<class Key, class Val>
void linked_list<Key, Val>::beg_add(node<Key, Val> nd){
	node<Key, Val>* new_node = new node <Key, Val>;
	if (!base_node){
		base_node = new_node;
		*base_node = nd;
		base_node->next = base_node;
		base_node->prev = base_node;
		return;
	}
	*new_node = *base_node;
	*base_node = nd;
	new_node->prev = base_node;
	new_node->next = base_node->next;
	base_node->next->prev = new_node;
	base_node->next = new_node;
}

template<class Key, class Val>
void linked_list<Key, Val>::beg_add(){
	node<Key, Val> nd;
	std::cout << "Key: "; std::cin >> nd.key;
	std::cout << "Val: "; std::cin >> nd.val;
	beg_add(nd);
}

template<class Key, class Val>
void linked_list<Key, Val>::end_add(node<Key, Val> nd){
	node<Key, Val>* new_node = new node <Key, Val>;
	*new_node = nd;
	if (!base_node){
		base_node = new_node;
		base_node->next = base_node;
		base_node->prev = base_node;
		return;
	}
	new_node->next = base_node;
	new_node->prev = base_node->prev;
	base_node->prev->next = new_node;
	base_node->prev = new_node;
}

template<class Key, class Val>
void linked_list<Key, Val>::end_add(){
	node<Key, Val> nd;
	std::cout << "Key: "; std::cin >> nd.key;
	std::cout << "Val: "; std::cin >> nd.val;
	end_add(nd);
}

template<class Key, class Val>
void linked_list<Key, Val>::delete_all(){
	node<Key, Val>* curr = base_node;
	node<Key, Val>* buff = curr;
	while (curr != base_node){
		buff = curr;
		curr = curr->next;
		delete buff;
	}
	delete base_node;
	base_node = nullptr;
}

template<class Key, class Val>
bool linked_list<Key, Val>::operator == (linked_list<Key, Val> ll) {
	if (ll.is_empty() && is_empty()) return true;
	//if (ll.elem_cnt() != elem_cnt()) return false;
	node<Key, Val>* curr = base_node;
	node<Key, Val>* ll_curr = ll.base_node;
	node<Key, Val> buff;
	general_set<node<Key, Val>> v1;
	general_set<node<Key, Val>> v2;
	//general_set<node<Key, Val>> v3;
	do{
		buff = *curr;
		v1.insert(buff);
		buff = *ll_curr;
		v2.insert(buff);
		curr = curr->next;
		ll_curr = ll_curr->next;
	} while (curr != base_node);
	if (v1.size != v2.size) return false;
	for (int i = 0; i < v1.size; ++i)if (!v2.has(v1.arr[i]))return false;
	return true;
}

template<class Key, class Val>
void to_right(node<Key, Val>** nd, int cnt) {
	int i = cnt;
	while (i-- > 0){
		*nd = (*nd)->next;
	}
}

template<class Key, class Val>
void to_left(node<Key, Val>** nd, int cnt) {
	int i = cnt;
	while (i-- > 0){
		*nd = (*nd)->prev;
	}
}

template<class Key, class Val>
void cyclic_right(linked_list<Key, Val>& ll, int cnt) {
	if (ll.is_empty() || ll.elem_cnt() == 1 || cnt <= 0) return;
	int elcnt = ll.elem_cnt();
	cnt = cnt % elcnt;
	node<Key, Val>* node_arr = new node<Key, Val>[elcnt];
	node<Key, Val>* base = ll.get_base();
	node<Key, Val>* curr = base;

	for (int i = 0; i < elcnt; ++i){
		node_arr[(i + cnt) % elcnt] = *curr;
		curr = curr->next;
	}

	ll.delete_all();
	ll.cpy_from(node_arr, elcnt);
}

template<class Key, class Val>
void cyclic_left(linked_list<Key, Val>& ll, int cnt) {
	if (ll.is_empty() || ll.elem_cnt() == 1 || cnt <= 0) return;
	int elcnt = ll.elem_cnt();
	cnt = cnt % elcnt;
	node<Key, Val>* node_arr = new node<Key, Val>[elcnt];
	node<Key, Val>* base = ll.get_base();
	node<Key, Val>* curr = base;

	for (int i = 0; i < elcnt; ++i){
		node_arr[(elcnt - cnt + i) % elcnt] = *curr;
		curr = curr->next;
	}

	ll.delete_all();
	ll.cpy_from(node_arr, elcnt);
}

template<class Key, class Val>
void linked_list<Key, Val>::auto_fill(int) {}

template<>
void linked_list<int, char>::auto_fill(int el_cnt){
	char mod = 'z' - 'a' + 1;
	for (int i = 0; i < el_cnt; ++i){
		end_add(node<int, char>(i, 'a' + i % mod));
	}
}

void prt_truth(bool p){
	if (p)std::cout << "Yes";
	else std::cout << "no";
	std::cout << std::endl;
}
