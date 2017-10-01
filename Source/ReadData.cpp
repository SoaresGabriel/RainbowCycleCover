#include "ReadData.h"
#include <fstream>
#include <iostream>
#include "Graph.h"

void ReadData::read(string fileName){
	
	ifstream in(fileName, ios::in);
	
	if(!in){
		std::cout << "Falha ao abrir o arquivo!" << endl;
		exit(1);
	}
	
	Graph &g = Graph::getInstance();
	int N, C;
	
	in >> N;
	in >> C;


	g.setNC(N, C);

	// Leitura da matriz de adjacencia
	for (int i = 0; i < N; i++) {
		for (int j = i+1; j < N; j++) {
			in >> g.adjMatrix[i][j];
			g.adjMatrix[j][i] = g.adjMatrix[i][j];
		}
	}

	in.close();

	//monta lista de adjacencia
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			if (g.adjMatrix[i][j] < C) { // se existe aquele vertice
				g.adjList[i].push_back(j);
				g.adjList[j].push_back(i);
			}
		}
	}
	
	g.reduce();

}
