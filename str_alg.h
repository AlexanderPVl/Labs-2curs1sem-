#pragma once

#include <algorithm>
#include <set>

#include "nums.h"

using namespace std;

ostream &operator << (ostream &ost, vector<string> str);

ostream &operator << (ostream &ost, set<char> st);

void enter_vs(vector<string> &vs);

void func4(vector<string> &vs_, set<char> &s_, const char* srch_str);

void intersection();