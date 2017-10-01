#include "Graph.h"

#include <iostream>

Graph* Graph::instance = 0;

Graph& Graph::getInstance(){
	if(!instance)
		instance = new Graph();
	
	return *instance;
}

void Graph::setNC(int N, int C){
	this->N = N;
	this->C = C;
	
	adjMatrix.resize(N);
	adjList.resize(N);
	
	for(int i = 0; i < N; i++){
		adjMatrix[i].resize(N);
	}
	
}

int Graph::deleteSingleColor(){

	list<int>::iterator it;

	bool oneColor;
	int color;
	int delOneColor = 0;

	for(int i = 0; i < N; i++){
		if(adjList[i].size() == 0)
			continue;

		/*
		 * Verifica as cores das arestas atuais, se todas forem da mesma cor, deleta o vertice
		 * */
		oneColor = true;
		color = adjMatrix[i][adjList[i].front()]; // cor do vertice atual ate o primeiro na sua lista de adjacencia
		for(it = adjList[i].begin(); it != adjList[i].end(); it++){
			if(adjMatrix[i][*it] != color){
				oneColor = false;
				break;
			}
		}

		// se tiver apenas uma cor, deleta o vertice da lista de adjacencia.
		if(oneColor){
			delOneColor += adjList[i].size();

			for(it = adjList[i].begin(); it != adjList[i].end(); it++){
				adjList[*it].remove(i);
			}

			adjList[i].clear();
		}

	}

	return delOneColor;

}

int Graph::deleteBridges(){

	vector<int> discoveryTime(N, -1);
	vector<int> low(N, -1);
	int time = 1;
	int bridges = 0;

	for(int i = 0; i < N; i++){
		if(discoveryTime[i] == -1){
			deleteBridgesAux(i, i, time, discoveryTime, low, bridges);
		}
	}

	return bridges;
}

int Graph::deleteBridgesAux(int parent, int vertex, int &time, vector<int> &discoveryTime, vector<int> &low, int &bridges){
	discoveryTime[vertex] = time;
	low[vertex] = discoveryTime[vertex];

	time++;

	bool itErased;
	int neighbor;
	for(list<int>::iterator it = adjList[vertex].begin(); it != adjList[vertex].end();){
		neighbor = *it;
		itErased = false;
		if(discoveryTime[neighbor] == -1){

			deleteBridgesAux(vertex, neighbor, time, discoveryTime, low, bridges);
			low[vertex] = low[neighbor];

			if(low[neighbor] == discoveryTime[neighbor]){
				it = adjList[vertex].erase(it);
				itErased = true;
				adjList[neighbor].remove(vertex);
				bridges++;
			}

		}else if(neighbor != parent && discoveryTime[neighbor] < discoveryTime[vertex]){
			discoveryTime[vertex] = discoveryTime[neighbor];
		}

		if(!itErased)
			it++;
	}

	return bridges;
}

void Graph::reduce(){

	int singleColorDeleted = 0, bridgesDeleted = 0, scd, bd;

	do{
		bd = deleteBridges();
		scd = deleteSingleColor();

		bridgesDeleted += bd;
		singleColorDeleted += scd;

	}while(bd > 0 || scd > 0);

	cout << "Pre-processamento: " << (singleColorDeleted + bridgesDeleted) << " arestas deletadas" << endl << endl;

}
