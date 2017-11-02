#ifndef CYCLE_H_
#define CYCLE_H_

#include <vector>
#include <boost/dynamic_bitset.hpp>

#include "Graph.h"

using namespace std;
using namespace boost;

class Cycle {
private:
	Graph *g;
	vector<int> cycle;
	dynamic_bitset<> colors;

public:
	typedef typename vector<int>::size_type size_type;

	Cycle(Graph &g);
	void operator=(const Cycle& x);

	void closeCycle();
	bool isTrivial();
	bool hasColor(int color);

	vector<int>::size_type size() const;

	void insert(size_type pos, int v);

	int operator[](size_type n) const;
	int at(size_type n) const;

	void push_back(const int& v);
	void pop_back();
	void clear();

	bool operator==(Cycle& other);

};

#endif /* CYCLE_H_ */
