#pragma once

#include <iostream>

template<class T>
struct qnode{
	qnode(T obj_) { obj = obj_; next = nullptr; }
	void setchild(qnode<T> &nd) { next = &nd; }
	T obj;
	qnode<T>* next;
	void operator = (qnode<T> &nd) { obj = nd.obj; }
	void operator = (T &obj_) { obj = obj_; }
};

template<class T>
class queue{
public:
	class iterator{
	public:
		typedef iterator self_type;
		typedef T& reference;
		typedef T value_type;
		typedef qnode<T>* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;
		iterator() { curr = nullptr; }
		iterator(pointer qn) { curr = qn; }
		reference operator *() { return curr->obj; }
		self_type operator ++() { if (curr) curr = curr->next; return *this; }
		void operator = (pointer qn) { curr = qn; }
		bool operator != (self_type it) { return curr != it.curr; }
		bool operator == (self_type it) { return curr == it.curr; }
	private:
		pointer curr;
	};
	queue();
	void push(T &obj);
	T pop();
	void pop(T &obj);
	void print();
	void qdelete();
	iterator begin() { return iterator(fout); }
	iterator end() {
		return nullptr; /*return iterator(fin);*/ }
	bool operator()() { return fin; }
private:
	qnode<T>* fin;
	qnode<T>* fout;
	qnode<T>* last_added;
};

template<class T>
queue<T>::queue(){
	fin = fout = last_added = nullptr;
}

template<class T>
void queue<T>::qdelete(){
	qnode<T>* curr = new qnode<T>(-1);
	while (last_added){
		curr = last_added;
		last_added = last_added->next;
		delete curr;
	}
}

template<class T>
void queue<T>::push(T &obj){
	if (!fin){
		fin = new qnode<T>(obj);
		fout = fin;
		fin->next = nullptr;
		last_added = fin;
		return;
	}
	if (fin == fout){
		qnode<T> *new_qnode = new qnode<T>(obj);
		fout = new_qnode;
		fout->next = fin;
		last_added = fout;
		return;
	}
	qnode<T> *new_qnode = new qnode<T>(obj);
	new_qnode->next = fout->next;
	new_qnode->obj = fout->obj;
	fout->obj = obj;
	fout->next = new_qnode;
	last_added = new_qnode;
}

template<class T>
T queue<T>::pop(){
	if (!fin){
		return 0;
	}
	if (fin == fout){
		delete fin;
		fin = fout = nullptr;
		//return fout->obj;
		return -1;
	}
	qnode<T> *del_qnode = new qnode<T>(-1);
	del_qnode = fout;
	T ret = fout->obj;
	fout = fout->next;
	if (!del_qnode)
		delete del_qnode;
	return ret;
}

template<class T>
void queue<T>::pop(T &obj){
	if (!fin){
		obj = -1;
		return;
	}
	if (fin == fout){
		obj = fin->obj;
		fin = fout = nullptr;
		return;
	}
	obj = fout->obj;
	fout = fout->next;
	return;
}

template<class T>
void queue<T>::print(){
	qnode<T> *buf = new qnode<T>(fout->obj);
	buf = fout;
	while (buf != nullptr){
		std::cout << buf->obj;
		buf = buf->next;
	}
	delete buf;
}
