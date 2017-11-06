#include "Cycle.h"

Cycle::Cycle(Graph &g) : g(&g){
	colors.resize(g.C);
	colors.reset();
}

void Cycle::operator=(const Cycle& x){
	this->g = x.g;
	this->cycle = x.cycle;
	this->colors = x.colors;
}

void Cycle::closeCycle(){

	colors.reset();

	colors[g->getColor(cycle.back(), cycle[0])] = true;

	for(unsigned int i = 1; i < size(); i++){
		colors[g->getColor(cycle[i-1], cycle[i])] = true;
	}

}

bool Cycle::isTrivial(){
	return (this->size() == 1);
}

bool Cycle::hasColor(int color){
	return colors[color];
}

vector<int>::size_type Cycle::size() const{
	return cycle.size();
}

void Cycle::insert(size_type pos, int v){
	colors[g->getColor(cycle[pos-1], cycle[pos])] = false;;
	colors[g->getColor(cycle[pos-1], v)] = true;
	colors[g->getColor(v, cycle[pos])] = true;

	//readiciona o ultimo elemento ao ciclo
	cycle.push_back(cycle.back());

	// desloca todos os elementos para uma casa apos
	for(unsigned int i = cycle.size() - 2; i > pos; i--){
		cycle[i] = cycle[i-1];
	}

	cycle[pos] = v;

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
	colors.reset();
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
