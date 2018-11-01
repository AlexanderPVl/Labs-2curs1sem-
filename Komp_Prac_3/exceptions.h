#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <fstream>

using namespace std;

class except_empty_container : public exception {
public:
	except_empty_container() : exception("Container is empty") {}
	except_empty_container(const char* msg) : exception(msg) {}
private:
};

#endif