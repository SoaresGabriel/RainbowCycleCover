#include "ReadData.h"

ReadData::ReadData(string fileName) : g(Graph::getInstance()), fileName(fileName), N(0), C(0) {

}

Graph& ReadData::read(){
	
	ifstream in(fileName, ios::in);
	
	if(!in){
		std::cout << "Falha ao abrir o arquivo!" << endl;
		exit(1);
	}
	
	string::size_type point = fileName.find_last_of(".");
	string fileExtension = fileName.substr(point + 1, fileName.size() - point - 1);

	Graph &g = Graph::getInstance();

	if(fileExtension == "rnd"){
		readRCCPEdgesList(in);
	}else{
		readUpperTriangularMatrix(in);
	}
	
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

	in.close();

	return g;
}

void ReadData::readUpperTriangularMatrix(ifstream& in){

	in >> N;
	in >> C;
	g.setN(N);
	g.setC(C);

	// Leitura da matriz de adjacencia
	for (int i = 0; i < N; i++) {
		for (int j = i+1; j < N; j++) {
			in >> g.adjMatrix[i][j];
			g.adjMatrix[j][i] = g.adjMatrix[i][j];
		}
	}

}

void ReadData::readRCCPEdgesList(ifstream& in){
	string s = "";

	while(s != "NUMBER_VERTICES:"){
		in >> s;
	}
	in >> N;

	int edges;
	while(s != "NUMBER_EDGES:"){
		in >> s;
	}
	in >> edges;

	while(s != "NUMBER_COLORS:"){
		in >> s;
	}
	in >> C;

	g.setN(N);
	g.setC(C);

	// inicializa matriz sem vertices
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			g.adjMatrix[i][j] = C;
		}
	}

	while(s != "LIST_EDGE_(source_destination_color)"){
		in >> s;
	}

	int v, w, c;
	for(int i = 0; i < edges; i++){
		in >> v >> w >> c;

		g.adjMatrix[v-1][w-1] = c-1;
		g.adjMatrix[w-1][v-1] = c-1;

	}

}
