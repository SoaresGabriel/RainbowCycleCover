#include <iostream>
#include <vector>
#include <list>

#include "RainbowCyclesSearch.h"
#include "ReadData.h"
#include "Util.h"
#include "CycleList.h"
#include "LocalSearch.h"
#include "RccpMIP.h"
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char **argv) {
	srand(time(0));

	string instance = argv[1];
	
	Graph &graph = ReadData(instance).read();

	unsigned int MAX_ITERATIONS = 500;
	unsigned int MAX_CYCLES = graph.N*graph.N;

	CycleList cycleList(graph, MAX_CYCLES);

	RainbowCyclesSearch rbs(graph, cycleList);

	LocalSearch localSearch(graph, cycleList);

	CycleCover bestSolution(graph.getTrivialWeight());
	unsigned int minCoverWeight = graph.N*graph.N, coverWeight;

	clock_t initialTime = clock(), finalTime;

	for(unsigned int iteration = 0; iteration < MAX_ITERATIONS; iteration++){

		CycleCover& solution = rbs.getRainbowCycles();
		coverWeight = solution.weight();

		//cycleList.push_back(solution);

		while(localSearch.trivialInsertion(solution));

		if(coverWeight < minCoverWeight){
			bestSolution = solution;
			minCoverWeight = coverWeight;
		}

	}

	cout << "Before Cplex: " << minCoverWeight << endl << endl;

	CycleCover& solution = OptimizeRCCP(cycleList);
	if(solution.weight() < minCoverWeight){
		bestSolution = solution;
	}

	finalTime = clock();
	long executionTime = ((finalTime - initialTime) / (CLOCKS_PER_SEC / 1000));


	printResult(bestSolution, executionTime, instance);


	cout << endl << endl;

	return 0;
}
