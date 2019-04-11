#pragma once
#include <iostream>
#include <string>

template <class Key, class Val>
struct pair{
	pair() {}
	pair(Key key_, Val val_) { key = key_, val = val_; }
	bool operator != (pair <Key, Val> p) { return (p.key != key || p.val != val); }
	void operator = (pair <Key, Val> p) { p.key = key, p.val = val; }

	Key key;
	Val val;
};

template <class Key, class Val>
struct tnode{
	tnode() { l = r = nullptr; }
	tnode(Key key_, Val val_) { data.key = key_, data.val = val_; l = r = nullptr; }
	pair<Key, Val> data;
	tnode<Key, Val> *l; // left
	tnode<Key, Val> *r; // right;
	bool operator == (tnode<Key, Val>& nd) { return (nd.l == l && nd.r == r && nd.data == data); }
	bool operator != (tnode<Key, Val>& nd) { return (nd.l != l || nd.r != r || nd.data != data); }
	void operator = (pair<Key, Val>& p){ data.key = p.key; data.val = p.val; }
	void operator = (tnode<Key, Val>& nd){ data.key = nd.data.key; data.val = nd.data.val; }
};

template<class Key, class Val>
Key keyof(tnode<Key, Val> &nd){ return nd.data.key; }
template<class Key, class Val>
Key keyof(tnode<Key, Val> *nd){ return nd->data.key; }

template<class Key, class Val>
Val valof(tnode<Key, Val> &nd){ return nd.data.val; }
template<class Key, class Val>
Val valof(tnode<Key, Val> *nd){ return nd->data.val; }

template <class Key, class Val>
class binary_tree{
public:
	binary_tree() { empty = true; }
	binary_tree(Key key_, Val val_);
	binary_tree(tnode<Key, Val>& nd);
	void add(tnode<Key, Val>& nd);
	void add(Key key_, Val val_);
	tnode<Key, Val>* get_base(){ return base_tnode; }
	void delete_tree(tnode<Key, Val> *base);

	template<class UnaryFunction>
	void for_each(UnaryFunction f, tnode<Key, Val> *base)
	{
		if (base->l) for_each(f, base->l);
		f(*base);
		if (base->r) for_each(f, base->r);
	}

	template<class UnaryFunction>
	void range_for(UnaryFunction f, tnode<Key, Val> *base, Key min, Key max)
	{
		if (base->l && keyof(base->l) >= min) range_for(f, base->l, min, max);
		if (min <= keyof(base) && keyof(base) <= max) f(*base);
		if (base->r && keyof(base->r) <= max) range_for(f, base->r, min, max);
	}
private:
	bool empty;
	tnode<Key, Val> *base_tnode;
};

//SOME_FUNCTIONS=========================

template<class Key, class Val>
void print(tnode<Key, Val>* nd){
	if (!nd) return;
	std::cout << "( " << nd->data.key << " , " << nd->data.val << " )" << std::endl;
}


template<class Key, class Val>
void print_tree(tnode<Key, Val> *base){
	if (base->l) print_tree(base->l);
	print(base);
	if (base->r) print_tree(base->r);
}

template<class Key, class Val>
void  binary_tree<Key, Val>::delete_tree(tnode<Key, Val> *base){
	if (base->l) delete_tree(base->l);
	if (base->r) delete_tree(base->r);
	delete base;
}

template<class Key, class Val>
void linsert(tnode<Key, Val> &n1, tnode<Key, Val> &n2){
	n2.l = n1.l;
	if (!n1.l){
		n1.l = &n2;
		n2.l = n2.r = nullptr;
	}
	n2.r = nullptr;
	n1.l = &n2;
}

template<class Key, class Val>
void rinsert(tnode<Key, Val> &n1, tnode<Key, Val>& n2){
	n2.l = nullptr;
	n2.r = n1.r;
	if (!n1.r){
		n1.r = &n2;
		n2.r = nullptr;
	}
	n1.r = &n2;
}

template<class Key, class Val>
void insert(tnode<Key, Val> &n1, tnode<Key, Val>& n2){
	if (keyof(n2) < keyof(n1)) linsert(n1, n2);
	else rinsert(n1, n2);
}

template<class Key, class Val>
tnode<Key, Val>& llimit(tnode<Key, Val> &n1, Key key_){
	if (!n1.l) return n1;
	if (keyof(n1.l) > key_) return llimit(*n1.l, key_);
	return n1;
}

template<class Key, class Val>
tnode<Key, Val>& rlimit(tnode<Key, Val> &n1, Key key_){
	if (!n1.r) return n1;
	if (keyof(n1.r) <= key_) return llimit(*n1.r, key_);
	return n1;
}

template<class Key, class Val>
tnode<Key, Val>& base(binary_tree<Key, Val> &bt){ return *bt.get_base(); }

template<class Key, class Val>
void insert(tnode<Key, Val> *n1, tnode<Key, Val> *n2){ insert(*n1, *n2); }

//BINARY_TREE============================
template <class Key, class Val>
binary_tree<Key, Val>::binary_tree(Key key_, Val val_){
	base_tnode->data.key = key_;
	base_tnode->data.val = val_;
	base_tnode->l = nullptr;
	base_tnode->r = nullptr;
	empty = false;
}

template <class Key, class Val>
binary_tree<Key, Val>::binary_tree(tnode<Key, Val>& nd){
	base_tnode = new tnode<Key, Val>;
	base_tnode->l = nullptr;
	base_tnode->r = nullptr;
	empty = false;
}

template <class Key, class Val>
void binary_tree<Key, Val>::add(tnode<Key, Val>& nd){
	if (empty){
		base_tnode = new tnode<Key, Val>;
		base_tnode->data = nd.data;
		base_tnode->l = nullptr;
		base_tnode->r = nullptr;
		empty = false;

		return;
	}
}

template <class Key, class Val>
void binary_tree<Key, Val>::add(Key key_, Val val_){
	if (empty){
		base_tnode = new tnode<Key, Val>;
		base_tnode->data.key = key_;
		base_tnode->data.val = val_;
		base_tnode->l = nullptr;
		base_tnode->r = nullptr;
		empty = false;

		return;
	}

	tnode<Key, Val> *curr = base_tnode;
	tnode<Key, Val> *buf;
	tnode<Key, Val> *new_tnode = new tnode<Key, Val>;
	new_tnode->data.key = key_;
	new_tnode->data.val = val_;
	new_tnode->l = new_tnode->r = nullptr;

	do{
		buf = curr;
		curr = &llimit(rlimit(*curr, key_), key_);
	} while (curr != buf);

	insert(curr, new_tnode);
}

template <class Key, class Val>
void subtree_size(tnode<Key, Val>* root, int* size, int f = 1){
	if (f) {
		if (!root) {
			*size = 0;
			return;
		}
		*size = 0;
	}
	if (!root) return;
	*size += 1;
	subtree_size(root->l, size, 0);
	subtree_size(root->r, size, 0);
}

template <class Key, class Val>
bool case_8(tnode<Key, Val>* root){
	int l, r;
	subtree_size(root->l, &l);
	subtree_size(root->r, &r);
	return l != r;
}

template <class Key, class Val>
bool case_10(tnode<Key, Val>* root){
	int l, r;
	subtree_size(root->l, &l);
	subtree_size(root->r, &r);
	return (l == r - 1) || (l == r + 1);
}

template<class Key, class Val, class Pred>
void problem_pred(tnode<Key, Val>* root, Pred* pred){
	if (!root) return;
	int num = 1;
	if (pred(root)) std::cout << num << std::endl;
	_problem_pred(root->l, &num, pred);
	_problem_pred(root->r, &num, pred);
}

template <class Key, class Val, class Pred>
void _problem_pred(tnode<Key, Val>* root, int *num, Pred* pred){
	if (!root) return;
	*num += 1;
	if (pred(root)) std::cout << *num << std::endl;
	_problem_pred(root->l, num, pred);
	_problem_pred(root->r, num, pred);
}
