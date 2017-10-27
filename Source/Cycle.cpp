#include "Cycle.h"

Cycle::Cycle(Graph &g) : g(&g){

}

void Cycle::operator=(const Cycle& x){
	this->g = x.g;
	this->cycle = x.cycle;
}

bool Cycle::isTrivial(){
	return (this->size() == 1);
}

vector<int>::size_type Cycle::size() const{
	return cycle.size();
}

int Cycle::operator[](size_type n) const{
	return cycle[n];
}

int Cycle::at(size_type n) const{
	return cycle.at(n);
}

void Cycle::push_back(const int& v){
	cycle.push_back(v);

}

void Cycle::pop_back(){
	cycle.pop_back();
}

void Cycle::clear(){
	cycle.clear();
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
