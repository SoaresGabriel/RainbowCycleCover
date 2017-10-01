/*
 * Cycle.h
 *
 *  Created on: 27 de set de 2017
 *      Author: gabri
 */

#ifndef CYCLE_H_
#define CYCLE_H_

#include <vector>
#include <boost/dynamic_bitset.hpp>

using namespace std;
using namespace boost;

class Cycle {
private:

	vector<int> cycle;
	dynamic_bitset<> bitset;
	bool modified;

public:
	Cycle();

	bool operator==(Cycle& other);
	int& operator[](int n);
	int operator[](int n) const;

	void push_back(const unsigned int& v);
	void pop_back();

	size_t size();
	void resize(const unsigned int &n);
	void clear();

	dynamic_bitset<>& getBitset();

};

#endif /* CYCLE_H_ */
