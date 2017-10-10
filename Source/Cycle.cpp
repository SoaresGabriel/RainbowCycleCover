/*
 * Cycle.cpp
 *
 *  Created on: 27 de set de 2017
 *      Author: gabri
 */

#include "Cycle.h"

bool Cycle::isTrivial(){
	return (this->size() == 1);
}

bool Cycle::operator==(Cycle& other){
	if(this->size() != other.size())
		return false;

	if(this->isTrivial() && this->at(0) == other[0]){
		return true;
	}

	int N = this->size();
	int j = 0;

	//encontrar as posicoes de um mesmo vertice nos dois ciclos
	while(other[j] != this->at(0))
		j++;

	int before = (j > 0 ? j-1 : N-1); // indice anterior ao j

	// se o proximo vertice for igual
	if(this->at(1) == other[(j+1)%N]){

		for(int a = 0; a < N; a++){
			if(this->at(a) != other[(j+a)%N] )
				return false;
		}

		return true;

	}else if(this->at(1) == other[before]){

		for(int a = 0; a < N; a++, j--){
			if(j < 0)
				j = N-1;

			if(this->at(a) != other[j])
				return false;
		}

		return true;

	}

	return false;
}
