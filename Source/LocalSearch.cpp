#include "LocalSearch.h"

LocalSearch::LocalSearch(Graph& graph, CycleList& cycleList) : graph(graph), cycleList(cycleList){

}

bool LocalSearch::trivialInsertion(CycleCover& cover){

	vector<Cycle>& trivials = cover.getTrivialCycles();
	vector<Cycle>& nonTrivials = cover.getNonTrivialCycles();

	int trivial, remove, colorA, colorB;
	for(unsigned int i = 0; i < trivials.size(); i++){
		trivial = trivials[i][0];

		for(unsigned int j = 0; j < nonTrivials.size(); j++){

			Cycle &c = nonTrivials[j];


			for(unsigned int k = 1; k < c.size(); k++){

				remove = graph.getColor(c[k-1], c[k]); // cor da aresta que sera removida
				// cores das arestas que seriam adicionadas
				colorA = graph.getColor(trivial, c[k-1]);
				colorB = graph.getColor(trivial, c[k]);

				if( 	(colorA != graph.C && colorB != graph.C) &&
						(colorA != colorB) &&
						(!c.hasColor(colorA) || colorA == remove) &&
						(!c.hasColor(colorB) || colorB == remove) ) {


					c.insert(k, trivial);
					trivials.erase(trivials.begin() + i);

					cycleList.push_back(c);

					return true;

				}


			}


		}

	}

	return false;

}

