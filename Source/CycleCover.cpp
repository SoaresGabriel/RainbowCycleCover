/*
 * ResultCover.cpp
 *
 *  Created on: 30 de set de 2017
 *      Author: gabri
 */

#include "CycleCover.h"

CycleCover::CycleCover() : TRIVIAL_WEIGHT((Graph::getInstance().N / 3)+1), trivial(0), nonTrivial(0) {

}

void CycleCover::push_back(Cycle& cycle){
	cycles.push_back(cycle);
	if(cycle.size() > 1)
		nonTrivial++;
	else
		trivial++;
}

Cycle& CycleCover::back(){
	return cycles.back();
}

unsigned int CycleCover::size(){
	return cycles.size();
}

void CycleCover::clear(){
	cycles.clear();
	trivial = 0;
	nonTrivial = 0;
}

vector<Cycle>& CycleCover::getCycles(){
	return this->cycles;
}

unsigned int CycleCover::trivialCount(){
	return trivial;
}

unsigned int CycleCover::nonTrivialCount(){
	return nonTrivial;
}

unsigned int CycleCover::weight(){
	return nonTrivial + TRIVIAL_WEIGHT * trivial;
}

void CycleCover::operator=(CycleCover& toCopy){
	this->cycles = toCopy.cycles;
	this->TRIVIAL_WEIGHT = toCopy.TRIVIAL_WEIGHT;
	this->trivial = toCopy.trivial;
	this->nonTrivial = toCopy.nonTrivial;
}

Cycle& CycleCover::operator[](unsigned int& i){
	return cycles[i];
}
