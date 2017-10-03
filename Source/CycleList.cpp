/*
 * CycleList.cpp
 *
 *  Created on: 2 de out de 2017
 *      Author: gabri
 */

#include "CycleList.h"

CycleList::CycleList(unsigned int maxQtCycles) : N(Graph::getInstance().N), MAX_CYCLES(maxQtCycles), vertexCycles(N) ,vertexCyclesBitset(N) {

	cycles.reserve(MAX_CYCLES);

	for(unsigned int i = 0; i < N; i++){
		vertexCyclesBitset[i].resize(maxQtCycles);
		vertexCyclesBitset[i].reset();
	}

}

void CycleList::push_back(Cycle &cycle){

	if(cycles.size() == MAX_CYCLES)
		return;

	dynamic_bitset<> intersection;
	intersection.resize(MAX_CYCLES);
	intersection.set();

	for(unsigned int i = 0; i < cycle.size(); i++)
		intersection &= vertexCyclesBitset[cycle[i]]; // faz a intercessao com os cyclos que contem o vertice cycle[i]

	bool contains = false; // se a lista de ciclos atual ja tem esse ciclo

	// percorre os elementos da intercessao
	for(unsigned int i = intersection.find_first(); i != dynamic_bitset<>::npos; i = intersection.find_next(i)){
		if(cycle == cycles[i]){
			contains = true;
			break;
		}
	}

	if(!contains){
		cycles.push_back(cycle);
		int cycleIndex = cycles.size() - 1;
		for(unsigned int i = 0; i < cycle.size(); i++){
			vertexCyclesBitset[cycle[i]].set(cycleIndex);
			vertexCycles[cycle[i]].push_back(cycleIndex);
		}
	}


}

void CycleList::push_back(CycleCover &cycleCover){
	vector<Cycle>& cycles = cycleCover.getCycles();
	for(int i = 0; i < cycles.size(); i++){
		this->push_back(cycles[i]);
	}
}
