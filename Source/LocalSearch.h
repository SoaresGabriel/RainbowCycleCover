#ifndef LOCALSEARCH_H_
#define LOCALSEARCH_H_

#include <vector>

#include "Cycle.h"
#include "CycleCover.h"
#include "CycleList.h"

using namespace std;

class LocalSearch {
private:
	Graph& graph;
	CycleList& cycleList;

public:

	LocalSearch(Graph& graph, CycleList& cycleList);

	bool trivialInsertion(CycleCover& cover);

};

#endif /* LOCALSEARCH_H_ */
