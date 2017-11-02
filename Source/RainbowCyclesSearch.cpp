#include "RainbowCyclesSearch.h"
#include "Util.h"

RainbowCyclesSearch::RainbowCyclesSearch(Graph &graph) : graph(graph), adjList(graph.N), cycle(graph), cycles(graph.getTrivialWeight()) {
	inCycle.resize(graph.N);
	hasColor.resize(graph.C);
}

CycleCover& RainbowCyclesSearch::getRainbowCycles() {

	adjList = graph.getAdjList();
	cycles.clear();

	for (int i = 0; i < graph.N; i++) {
		inCycle[i] = false;
	}
	for(int i = 0; i < graph.C; i++){
		hasColor[i] = false;
	}

	visit.resize(graph.N);
	for(int i = 0; i < graph.N; i++){
		visit[i] = i;
	}

	// aleatoriza lista de adjacencia
	for(int i = 0; i < graph.N; i++){
		if(adjList[i].size() > 1)
			shakeList(adjList[i]);
	}

	int v;
	while(visit.size() > 0) {
		v = getNextVertex();

		cycle.clear();
		vector<bool> visited(graph.N, false);

		if (findCycles(v, v, visited, 1)) { // se encontrou um ciclo, deleta os vertices da lista de adjacencia
			deleteCycleVertexFromAdjList(cycles.back());
		}
	}

	// Cria ciclo degenerados com restante dos vertices
	cycle.clear();
	for(int i = 0; i < graph.N; i++){
		if(!inCycle[i]){ // se vertice nao faz parte de um ciclo, vira um degenerado
			cycle.push_back(i);
			cycles.push_back(cycle);
			cycle.pop_back();
		}
	}

	return cycles;
}

/*
 * v -> vertice atual
 * o -> vertice de origem
 * */
bool RainbowCyclesSearch::findCycles(int v, int o, vector<bool> &visited, int recursionLevel) {
	visited[v] = true;
	cycle.push_back(v);

	int color;
	bool encontrou = false, adjO = false;
	
	for (int &dest : adjList[v]) {
		color = graph.getColor(v, dest);

		if (!hasColor[color]) {
			if (dest == o) { // encontrou o ciclo
				adjO = true;
			}else if(visited[dest]){
				continue;
			} else if(recursionLevel < graph.C) { // tamanho do ciclo no menor ou igual ao numero de cores
				hasColor[color] = true;
				encontrou = findCycles(dest, o, visited, recursionLevel + 1);
				hasColor[color] = false;
			}
		}
		
		if(encontrou)
			break;
	}

	if(!encontrou && adjO){ // origem � um vertice adjacente
		encontrou = true;
		cycle.closeCycle();
		this->cycles.push_back(cycle);
	}

	cycle.pop_back();

	return encontrou;
}

void RainbowCyclesSearch::deleteCycleVertexFromAdjList(Cycle &cyclee) {

	// marca vertices que já fazem parte de um ciclo
	for (unsigned int i = 0; i < cyclee.size(); i++) {
		inCycle[cyclee[i]] = true;
	}

	// deleta vertices da lista de adjacencia
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

	// deleta vertices da lista a visitar
	for(unsigned int i = 0; i < visit.size(); i++){
		if(inCycle[visit[i]]){
			visit[i] = visit[visit.size() - 1];
			visit.pop_back();
			i--; // verificar novamente posicao atual
		}
	}


}

int RainbowCyclesSearch::getNextVertex(){

	int M = 1; // numero total de arestas no grafo + 1

	// calcula o grau colorido de cada vertice restante
	vector<int> cDegree(graph.N, 0);
	set<int> cdeg;
	for(int v : visit){
		cdeg.clear();

		M += adjList[v].size();

		for(int w : adjList[v]){
			cdeg.insert(graph.getColor(v, w));
		}

		cDegree[v] = cdeg.size();
	}

	//calcula prioridade
	vector<int> priority(graph.N);
	for(int v : visit){
		priority[v] = adjList[v].size()/M + cDegree[v]/graph.C;
	}

	// ordena de acordo com a prioridade
	sort(visit.begin(), visit.end(), [&priority](int v, int w){
		return priority[v] < priority[w];
	});


	// aleatoriza proximo vertice entre os 30% primeiros
	int pos = rand() % (int) ceil(visit.size() * 0.3);
	int v = visit[pos];

	//deleta vertice da lista a visitar
	visit[pos] = visit[visit.size() - 1];
	visit.pop_back();

	return v;
}
