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
	queue();
	void push(T &obj);
	T pop();
	void pop(T &obj);
	void print();
private:
	qnode<T>* fin;
	qnode<T>* fout;
};

template<class T>
queue<T>::queue(){
	fin = fout = nullptr;
}

template<class T>
void queue<T>::push(T &obj){
	if (!fin){
		fin = new qnode<T>(obj);
		fout = fin;
		fin->next = nullptr;
		return;
	}
	if (fin == fout){
		qnode<T> *new_qnode = new qnode<T>(obj);
		fout = new_qnode;
		fout->next = fin;
	}
	qnode<T> *new_qnode = new qnode<T>(obj);
	new_qnode->next = fout->next;
	new_qnode->obj = fout->obj;
	fout->obj = obj;
	fout->next = new_qnode;
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
		return;
	}
	if (fin == fout){
		obj = fin->obj;
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
