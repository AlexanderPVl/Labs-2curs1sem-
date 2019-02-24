#pragma once

#include <random>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

ostream &operator << (ostream &ost, vector<char> str);

void rand_gen();

bool is_polyndrome(int t);

void odometer();