#ifndef CYCLELIST_H_
#define CYCLELIST_H_

#include <vector>
#include "Graph.h"
#include "Cycle.h"
#include "CycleCover.h"
#include <boost/dynamic_bitset.hpp>

using namespace boost;

class CycleList {
public:
	const unsigned int N; // graph.N
	const int M; // peso dos ciclos triviais

private:
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
