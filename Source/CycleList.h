/*
 * CycleList.h
 *
 *  Created on: 2 de out de 2017
 *      Author: gabri
 */

#ifndef CYCLELIST_H_
#define CYCLELIST_H_

#include <vector>
#include "Graph.h"
#include "Cycle.h"
#include "CycleCover.h"

class CycleList {
private:
	const unsigned int N; // graph.N
	const unsigned int MAX_CYCLES;
	vector<dynamic_bitset<> > vertexCyclesBitset;

public:
	vector<Cycle> cycles;
	vector<vector<int> > vertexCycles;

	CycleList(unsigned int maxQtCycles);

	void push_back(Cycle &cycle);
	void push_back(CycleCover &cycleCover);

};


#endif /* CYCLELIST_H_ */
