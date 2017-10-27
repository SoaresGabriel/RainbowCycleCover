#ifndef CYCLECOVER_H_
#define CYCLECOVER_H_

#include "Graph.h"
#include "Cycle.h"

class CycleCover {

private:
	unsigned int TRIVIAL_WEIGHT;

	vector<Cycle> trivialCycles;
	vector<Cycle> nonTrivialCycles;
	bool lastAddTrivial = false;

public:
	CycleCover(unsigned int trivialWeight);

	void push_back(Cycle& cycle);
	Cycle& back();
	unsigned int size();
	void clear();

	vector<Cycle>& getNonTrivialCycles();
	vector<Cycle>& getTrivialCycles();

	unsigned int trivialCount();
	unsigned int nonTrivialCount();
	unsigned int weight();

	void operator=(CycleCover& toCopy);
	Cycle& operator[](unsigned int& i);
};

#endif /* CYCLECOVER_H_ */
