#include "CycleCover.h"

CycleCover::CycleCover(unsigned int trivialWeight) : TRIVIAL_WEIGHT(trivialWeight) {

}

void CycleCover::push_back(Cycle& cycle){
	if(cycle.size() > 1){
		lastAddTrivial = false;
		nonTrivialCycles.push_back(cycle);
	}else{
		lastAddTrivial = true;
		trivialCycles.push_back(cycle);
	}
}

Cycle& CycleCover::back(){
	return (lastAddTrivial? trivialCycles.back() : nonTrivialCycles.back() );
}

unsigned int CycleCover::size(){
	return nonTrivialCycles.size() + trivialCycles.size();
}

void CycleCover::clear(){
	nonTrivialCycles.clear();
	trivialCycles.clear();
}

vector<Cycle>& CycleCover::getNonTrivialCycles(){
	return nonTrivialCycles;
}

vector<Cycle>& CycleCover::getTrivialCycles(){
	return nonTrivialCycles;
}

unsigned int CycleCover::trivialCount(){
	return trivialCycles.size();
}

unsigned int CycleCover::nonTrivialCount(){
	return nonTrivialCycles.size();
}

unsigned int CycleCover::weight(){
	return nonTrivialCount() + TRIVIAL_WEIGHT * trivialCount();
}

void CycleCover::operator=(CycleCover& toCopy){
	this->nonTrivialCycles = toCopy.nonTrivialCycles;
	this->trivialCycles = toCopy.trivialCycles;
	this->TRIVIAL_WEIGHT = toCopy.TRIVIAL_WEIGHT;
	this->lastAddTrivial = toCopy.lastAddTrivial;
}

Cycle& CycleCover::operator[](unsigned int& i){
	if(i < nonTrivialCycles.size())
		return nonTrivialCycles[i];
	else
		return trivialCycles[i - nonTrivialCycles.size()];
}
