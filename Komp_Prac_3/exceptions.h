#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <fstream>

using namespace std;

class except_empty_container : public exception {
public:
	except_empty_container() : exception("Container is empty") {}
	except_empty_container(const char* msg) : exception(msg) { cout << "\n" << msg << endl; }
	except_empty_container(const char* msg, bool if_empty_, int size_) : exception(msg) {
		cout << "\n" << msg << endl;
		if_empty = if_empty_;
		size = size_;
	}
private:
	bool if_empty;
	int size;
};

class except_non_compatible : public exception {
public:
	except_non_compatible() : exception("Types are not compatible") {}
	except_non_compatible(const char* msg) : exception(msg) { cout << "\n" << msg << endl; }
};

template<class T>
class except_vrong_type : public exception {
public:
	except_vrong_type() : exception("Unavailable data type") { cout << "\n" << "Unavailable data type \"" << typeid(T).name() << "\"" << endl; }
	except_vrong_type(const char* msg) : exception(msg) { cout << "\n" << msg << endl; }
	typedef T type;
};

class except_index_out_of_range : public exception {
public:
	except_index_out_of_range(int ind) : exception("Index has ran out of range") {
		cout << "\n" << "Index has ran out of range (" << ind << ")" << endl;
		index = ind;
	}
	except_index_out_of_range(int ind, const char* msg) : exception(msg) {
		cout << "\n" << msg << endl;
		index = ind;
	}
	int index;
};

#endif
