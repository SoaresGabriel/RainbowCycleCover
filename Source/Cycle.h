#ifndef CYCLE_H_
#define CYCLE_H_

#include <vector>

#include "Graph.h"

using namespace std;

class Cycle {
private:
	Graph &g;
	vector<int> cycle;

public:
	typedef typename vector<int>::size_type size_type;

	class reference;

	vector<bool> colors;

	Cycle(Graph &g);
	void operator=(const Cycle& x);

	bool isTrivial();

	vector<int>::size_type size() const;

	int operator[](size_type n) const;
	int at(size_type n) const;

	void push_back(const int& val);
	void pop_back();
	void clear();

	bool operator==(Cycle& other);

};

#endif /* CYCLE_H_ */
