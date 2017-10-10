/*
 * ResultCover.h
 *
 *  Created on: 30 de set de 2017
 *      Author: gabri
 */

#ifndef CYCLECOVER_H_
#define CYCLECOVER_H_

#include "Graph.h"
#include "Cycle.h"

class CycleCover {

private:
	unsigned int TRIVIAL_WEIGHT;

	vector<Cycle> cycles;

	unsigned int trivial;
	unsigned int nonTrivial;

public:
	CycleCover();

	void push_back(Cycle& cycle);
	Cycle& back();
	unsigned int size();
	void clear();

	vector<Cycle>& getCycles();

	unsigned int trivialCount();
	unsigned int nonTrivialCount();
	unsigned int weight();

	void operator=(CycleCover& toCopy);
	Cycle& operator[](unsigned int& i);
};

#endif /* CYCLECOVER_H_ */
