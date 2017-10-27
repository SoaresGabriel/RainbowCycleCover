#include "CycleList.h"

CycleList::CycleList(unsigned int maxQtCycles) : N(Graph::getInstance().N), M((N/3)+1), MAX_CYCLES(maxQtCycles), vertexCyclesBitset(N), vertexCycles(N) {

	cycles.reserve(MAX_CYCLES);

	Cycle trivial(Graph::getInstance());

	for(unsigned int i = 0; i < N; i++){
		vertexCyclesBitset[i].resize(maxQtCycles);
		vertexCyclesBitset[i].reset();

		// inclusao dos ciclos triviais
		trivial.push_back(i);
		cycles.push_back(trivial);
		trivial.pop_back();
		vertexCyclesBitset[i].set(i);
		vertexCycles[i].push_back(i);
	}

}

void CycleList::push_back(Cycle &cycle){

	if(cycles.size() == MAX_CYCLES || cycle.isTrivial())
		return;

	dynamic_bitset<> intersection;
	intersection.resize(MAX_CYCLES);
	intersection.set();

	for(unsigned int i = 0; i < cycle.size(); i++)
		intersection &= vertexCyclesBitset[cycle[i]]; // faz a intercessao com os cyclos que contem o vertice cycle[i]

	bool contains = false; // se a lista de ciclos atual ja tem esse ciclo

	// percorre os elementos da intercessao
	for(unsigned int i = intersection.find_first(); i < MAX_CYCLES; i = intersection.find_next(i)){
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
	for(unsigned int i = 0; i < cycleCover.size(); i++){
		this->push_back(cycleCover[i]);
	}
}
