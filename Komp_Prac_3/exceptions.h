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

#endif
