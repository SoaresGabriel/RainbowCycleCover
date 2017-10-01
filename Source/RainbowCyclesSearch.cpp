#include "RainbowCyclesSearch.h"
#include "Util.h"

#include <iostream>
#include <cmath>

RainbowCyclesSearch::RainbowCyclesSearch(Graph &graph) : graph(graph), adjList(graph.N) {
	inCycle.resize(graph.N);
	hasColor.resize(graph.C);
}

CycleCover& RainbowCyclesSearch::getRainbowCycles() {

	adjList = graph.adjList;
	cycles.clear();

	for (int i = 0; i < graph.N; i++) {
		inCycle[i] = false;
	}
	for(int i = 0; i < graph.C; i++){
		hasColor[i] = false;
	}
	
	vector<int> visitOrder(graph.N);
	for(int i = 0; i < graph.N; i++){
		visitOrder[i] = i;
	}

	/*ALEATORIZACAO*/
	shakeArray(visitOrder);
	for(int i = 0; i < graph.N; i++){
		if(adjList[i].size() > 1)
			shakeList(adjList[i]);
	}

	int v;
	for (int i = 0; i < graph.N; i++) {

		v = visitOrder[i];

		if (!inCycle[v]) {
			cycle.clear();
			vector<bool> visited(graph.N, false);
			
			if (findCycles(v, v, visited)) { // se encontrou um ciclo, deleta os vertices da lista de adjacencia
				deleteCycleVertexFromAdjList(cycles.back());
			}
		}
	}

	/*
	 * Cria ciclo degenerados com restante dos vertices
	 * */
	cycle.resize(1);
	for(int i = 0; i < graph.N; i++){
		if(!inCycle[i]){ // se vertice nao faz parte de um ciclo, vira um degenerado
			cycle[0] = i;
			cycles.push_back(cycle);
		}
	}

	return cycles;
}

/*
 * v -> vertice atual
 * o -> vertice de origem
 * */
bool RainbowCyclesSearch::findCycles(int v, int o, vector<bool> &visited) {
	visited[v] = true;
	cycle.push_back(v);

	int color;
	bool encontrou = false, adjO = false;
	
	for (int &dest : adjList[v]) {
		color = graph.adjMatrix[v][dest];

		if (!hasColor[color]) {
			if (dest == o) { // encontrou o ciclo
				adjO = true;

				//this->cycles.push_back(cycle);

			}else if(visited[dest]){
				continue;
			} else {
				hasColor[color] = true;
				encontrou = findCycles(dest, o, visited);
				hasColor[color] = false;
			}
		}
		
		if(encontrou)
			break;
	}

	if(!encontrou && adjO){ // origem é um vertice adjacente
		encontrou = true;
		this->cycles.push_back(cycle);
	}

	cycle.pop_back();

	return encontrou;
}

void RainbowCyclesSearch::deleteCycleVertexFromAdjList(Cycle &cyclee) {


	for (unsigned int i = 0; i < cyclee.size(); i++) {
		inCycle[cyclee[i]] = true;
	}

	for (int i = 0; i < graph.N; i++) {

		if (inCycle[i]) {
			adjList[i].clear();
		} else if(adjList[i].size() > 0) {


			for (list<int>::iterator it = adjList[i].begin(); it != adjList[i].end();) {

				if (inCycle[*it]) {
					it = adjList[i].erase(it);
				}else{
					it++;
				}

			}

		}

	}


}
