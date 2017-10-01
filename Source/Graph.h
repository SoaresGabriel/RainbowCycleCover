#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <list>

using namespace std;

class Graph {
private:
	static Graph* instance;
	Graph(): N(0), C(0){
	}
	
	int deleteSingleColor();
	int deleteBridges();
	int deleteBridgesAux(int parent, int vertex, int &time, vector<int> &discoveryTime, vector<int> &low, int &bridges);

public:
	int N;
	int C;
	vector<vector<int> > adjMatrix;
	vector<list<int> > adjList;
	
	void setNC(int N, int C);
	void reduce();
	
	// SINGLETON
	static Graph& getInstance();
};

#endif /* READDATA_H_ */
