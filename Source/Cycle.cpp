/*
 * Cycle.cpp
 *
 *  Created on: 27 de set de 2017
 *      Author: gabri
 */

#include "Cycle.h"
#include "Graph.h"

Cycle::Cycle() : bitset(Graph::getInstance().N), modified(true) {
}

bool Cycle::isTrivial(){
	return (this->size() == 1);
}

bool Cycle::operator==(Cycle& other){
	if(this->cycle.size() != other.cycle.size() || this->getBitset() != other.getBitset())
		return false;

	// se fores ciclos degenerados e tiver o mesmo bitset, sao iguais.
	if(this->isTrivial()){
		return true;
	}

	int N = this->cycle.size();
	int j = 0;

	//encontrar as posicoes de um mesmo vertice nos dois ciclos
	while(other.cycle[j] != this->cycle[0])
		j++;

	int before = (j > 0 ? j-1 : N-1); // indice anterior ao j

	// se o proximo vertice for igual
	if(this->cycle[1] == other.cycle[(j+1)%N]){

		for(int a = 0; a < N; a++){
			if(this->cycle[a] != other.cycle[(j+a)%N] )
				return false;
		}

		return true;

	}else if(this->cycle[1] == other.cycle[before]){

		for(int a = 0; a < N; a++, j--){
			if(j < 0)
				j = N-1;

			if(this->cycle[a] != other.cycle[j])
				return false;
		}

		return true;

	}

	return false;
}

int& Cycle::operator[](int n){
	return this->cycle[n];
	modified = true;
}

int Cycle::operator[](int n) const{
	return this->cycle[n];
}

void Cycle::push_back(const unsigned int& v){
	this->cycle.push_back(v);
	modified = true;
}

void Cycle::pop_back(){
	this->cycle.pop_back();
	modified = true;
}

size_t Cycle::size(){
	return this->cycle.size();
}

void Cycle::resize(const unsigned int &n){
	cycle.resize(n);
	modified = true;
}

void Cycle::clear(){
	this->cycle.clear();
	modified = true;
}

dynamic_bitset<>& Cycle::getBitset(){
	if(modified){
		bitset.reset();

		for(unsigned int i = 0; i < cycle.size(); i++)
			bitset.set(cycle[i], true);

		modified = false;
	}
	return bitset;
}
