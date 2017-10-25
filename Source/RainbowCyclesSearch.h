#ifndef RAINBOWCYCLESSEARCH_H_
#define RAINBOWCYCLESSEARCH_H_

#include <vector>
#include <list>
#include <set>
#include <algorithm>

#include <iostream>
#include <cmath>

#include "Graph.h"
#include "CycleCover.h"

using namespace std;

class RainbowCyclesSearch {
private:
	Graph &graph;
	vector<list<int> > adjList;

	Cycle cycle;
	CycleCover cycles;
	// diz se tem determinada cor no caminho do dfs
	vector<bool> hasColor;
	// diz quais vertices j� fazem parte de um ciclo
	vector<bool> inCycle;

	vector<int> visit;

	void calculateVisitOrder();
	int getNextVisitVertex();
	void deleteCycleVertexFromAdjList(Cycle &cyclee);
	bool findCycles(int v, int o, vector<bool> &visited, int recursionLevel);

public:
	RainbowCyclesSearch(Graph &graph);
	CycleCover& getRainbowCycles();
};

#endif /* RAINBOWCYCLESSEARCH_H_ */
