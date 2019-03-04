#pragma once

#include "queue.h"

#include <iostream>

template<class T>
struct _type{
	_type() = default;
	T operator ()() { return storage; }
	typedef T type;
	T storage;
};

template <class Key, class Val>
struct pair{
	Key key;
	Val val;
	bool operator != (pair <Key, Val> p) { return (p.key != key || p.val != val); }
};

template <class Key, class Val>
struct node{
	node() { l = nullptr; r = nullptr; }
	pair<Key, Val> data;
	node<Key, Val> *l; // left
	node<Key, Val> *r; // right;
	bool operator == (node<Key, Val>& nd) { return (nd.l == l && nd.r == r && nd.data == data); }
	bool operator != (node<Key, Val>& nd) { return (nd.l != l || nd.r != r || nd.data != data); }
	void operator = (pair<Key, Val>& p){ data.key = p.key; data.val = p.val; }
	void operator = (node<Key, Val>& nd){ data.key = nd.data.key; data.val = nd.data.val; }
};

template<class Key, class Val>
Key keyof(node<Key, Val> &nd){ return nd.data.key; }
template<class Key, class Val>
Key keyof(node<Key, Val> *nd){ return nd->data.key; }

template<class Key, class Val>
Val valof(node<Key, Val> &nd){ return nd.data.val; }
template<class Key, class Val>
Val valof(node<Key, Val> *nd){ return nd->data.val; }

template <class Key, class Val>
class binary_tree{
public:
	class iterator {
	public:
		iterator(qnode<node<Key, Val>*>* ptr_) : curr_node(ptr_) {}
		typedef iterator self_type;
		//typedef node<Key, Val>& reference;
		//typedef node<Key, Val> value_type;
		//typedef node<Key, Val>* pointer;
		typedef qnode<node<Key, Val>*>& reference;
		typedef qnode<node<Key, Val>*> value_type;
		typedef qnode<node<Key, Val>*>* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;
		~iterator() = default;
		qnode<node<Key, Val>*> operator * () { if (!curr_node) std::cout << "S.O.S!"; return *curr_node; }
		self_type operator ++ () { curr_node = curr_node->next; return *this; }
		bool operator ! () { return curr_node; }
		bool operator () (iterator it) { curr_node = it.curr_node; }
		bool operator != (iterator it) { return it.curr_node != curr_node; }
		bool operator == (iterator it) { return it.curr_node == curr_node; }
		void operator = (iterator it) { curr_node = it.curr_node; }
		_type<self_type> get_type(){ return _type<self_type>(); }
	private:
		qnode<node<Key, Val>*>* curr_node;
		typedef iterator self_type;
	};
	_type<iterator> get_iter_type(){ return _type<iterator>(); }
	binary_tree() { empty = true; }
	binary_tree(Key key_, Val val_);
	binary_tree(node<Key, Val>& nd);
	void add(node<Key, Val>& nd);
	void add(Key key_, Val val_);
	node<Key, Val>* get_base(){ return base_node; }
	void delete_tree(node<Key, Val> *base);

	iterator begin() { return iterator(node_queue.get_fout()); }
	iterator end() { return iterator(nullptr); }

	template<class UnaryFunction>
	void for_each(UnaryFunction f, node<Key, Val> *base)
	{
		if (base->l) for_each(f, base->l);
		f(*base);
		if (base->r) for_each(f, base->r);
	}

	template<class UnaryFunction>
	void range_for(UnaryFunction f, node<Key, Val> *base, Key min, Key max)
	{
		if (base->l && keyof(base->l) >= min) range_for(f, base->l, min, max);
		if (min <= keyof(base) && keyof(base) <= max) f(*base);
		if (base->r && keyof(base->r) <= max) range_for(f, base->r, min, max);
	}
	void print_tree(){ for (qnode<node<Key, Val>*>* bufnq = node_queue.get_fout(); bufnq; bufnq = bufnq->next) { print(*bufnq->obj); } }
private:
	bool empty;
	queue<node<Key, Val>*> node_queue;
	node<Key, Val> *base_node;
};

//SOME_FUNCTIONS=========================

template<class Key, class Val>
void print(node<Key, Val>& nd){
	if (&nd == nullptr) {
		std::cout << "NULL" << std::endl;
		return;
	}
	std::cout << "( " << nd.data.key << " , " << nd.data.val << " )" << std::endl; //<< nd.l << std::endl << nd.r << std::endl;
}

template<class Key, class Val>
void print_tree(node<Key, Val> *base){
	if (base->l) print_tree(base->l);
	print(*base);
	if (base->r) print_tree(base->r);
}

template<class Key, class Val>
void  binary_tree<Key, Val>::delete_tree(node<Key, Val> *base){
	if (base->l) delete_tree(base->l);
	if (base->r) delete_tree(base->r);
	delete base;
	node_queue.delete_queue();
}

template<class Key, class Val>
void linsert(node<Key, Val> &n1, node<Key, Val> &n2){
	n2.l = n1.l;
	if (!n1.l){
		n1.l = &n2;
		n2.l = n2.r = nullptr;
	}
	n2.r = nullptr;
	n1.l = &n2;
}

template<class Key, class Val>
void rinsert(node<Key, Val> &n1, node<Key, Val>& n2){
	n2.l = nullptr;
	n2.r = n1.r;
	if (!n1.r){
		n1.r = &n2;
		n2.r = nullptr;
	}
	n1.r = &n2;
}

template<class Key, class Val>
void insert(node<Key, Val> &n1, node<Key, Val>& n2){
	if (keyof(n2) < keyof(n1)) linsert(n1, n2);
	else rinsert(n1, n2);
}

template<class Key, class Val>
node<Key, Val>& llimit(node<Key, Val> &n1, Key key_){
	if (!n1.l) return n1;
	if (keyof(n1.l) > key_) return llimit(*n1.l, key_);
	return n1;
}

template<class Key, class Val>
node<Key, Val>& rlimit(node<Key, Val> &n1, Key key_){
	if (!n1.r) return n1;
	if (keyof(n1.r) <= key_) return llimit(*n1.r, key_);
	return n1;
}

template<class Key, class Val>
node<Key, Val>& base(binary_tree<Key, Val> &bt){ return *bt.get_base(); }

template<class Key, class Val>
void insert(node<Key, Val> *n1, node<Key, Val> *n2){ insert(*n1, *n2); }

//BINARY_TREE============================
template <class Key, class Val>
binary_tree<Key, Val>::binary_tree(Key key_, Val val_){
	base_node->data.key = key_;
	base_node->data.val = val_;
	base_node->l = nullptr;
	base_node->r = nullptr;
	empty = false;
}

template <class Key, class Val>
binary_tree<Key, Val>::binary_tree(node<Key, Val>& nd){
	base_node = new node<Key, Val>;
	base_node->l = nullptr;
	base_node->r = nullptr;
	empty = false;
}

template <class Key, class Val>
void binary_tree<Key, Val>::add(node<Key, Val>& nd){
	if (empty){
		base_node = new node<Key, Val>;
		base_node->data = nd.data;
		base_node->l = nullptr;
		base_node->r = nullptr;
		empty = false;

		return;
	}
}

template <class Key, class Val>
void binary_tree<Key, Val>::add(Key key_, Val val_){
	if (empty){
		base_node = new node<Key, Val>;
		base_node->data.key = key_;
		base_node->data.val = val_;
		base_node->l = nullptr;
		base_node->r = nullptr;
		node_queue.push(base_node);
		empty = false;

		return;
	}

	node<Key, Val> *curr = base_node;
	node<Key, Val> *buf;
	node<Key, Val> *new_node = new node<Key, Val>;
	new_node->data.key = key_;
	new_node->data.val = val_;
	new_node->l = new_node->r = nullptr;
	node_queue.push(new_node);

	do{
		buf = curr;
		curr = &llimit(rlimit(*curr, key_), key_);
	} while (curr != buf);

	insert(curr, new_node);
}

template<class Iter, class Pred>
class filter_iterator{
public:
	filter_iterator(Iter it_) : it(it_) {
		while (it_ != Iter(nullptr)) {
			if (pr(it_)){
				it = it_;
				return;
			}
			++it_;
		}
		it = it_;
	}
	filter_iterator(Pred pr_) : pr(pr_) {}
	filter_iterator(Iter it_, Pred pr_) : it(it_), pr(pr_) {}
	void pred_init(Pred pr_) { pr = pr_; }
	typedef filter_iterator self_type;
	typedef Iter& reference;
	typedef Iter value_type;
	typedef Iter* pointer;
	typedef std::forward_iterator_tag iterator_category;
	typedef int difference_type;
	bool operator == (filter_iterator f_it) { return it == f_it.it; }
	bool operator != (filter_iterator f_it) { return it != f_it.it; }
	bool operator != (Iter it_) { return it != it_; }
	bool operator == (Iter it_) { return it == it_; }
	void operator () (Iter it_) { it = it_; }
	Iter operator * () { return it; }
	filter_iterator operator ++ () {
		++it;
		Iter it_ = it;
		while (it_ != Iter(nullptr)) {
			if (pr(it_)){
				it = it_;
				return *this;
			}
			++it_;
		}
		it = it_;
		return *this;
	}
	~filter_iterator() = default;
private:
	Iter it;
	Pred pr;
};
