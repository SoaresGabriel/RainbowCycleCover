#ifndef UTIL_H_
#define UTIL_H_

#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "CycleCover.h"

using namespace std;

void shakeArray(vector<int> &array);
void shakeList(list<int> &list);

string getInstanceName(string instance);

void printResult(CycleCover &cover, long int executionTime, string instance);

#endif /* UTIL_H_ */
