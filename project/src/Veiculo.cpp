
#include "Veiculo.h"

Veiculo::Veiculo(unsigned int ID,No local, unsigned int capacidade){
	this->local = local;
	this->capacidade = capacidade;
	this->dist = 0;
	this->disponivel = capacidade;
	this->ID = ID;
}



Veiculo::~Veiculo() {
	// TODO Auto-generated destructor stub
}

No Veiculo::getlocalNode() const
{
	return this->local;
}

void Veiculo::setlocalNode(No novoLocal){
	this->local = novoLocal;
}


unsigned int Veiculo::getDisponibilidade() const
{
	return disponivel;
}

void Veiculo::setDisponibilidade(unsigned int value)
{
	this->disponivel = value;
}

unsigned int Veiculo::decDisponibilidade(unsigned int lugares_ocupados){

	if(this->disponivel == 0){
		return 0;
	}else if(this->disponivel-lugares_ocupados < 0){
		unsigned int new_lugares_ocupados = lugares_ocupados - this->disponivel;
		this->disponivel = 0;
		return new_lugares_ocupados;
	}else{
		this->disponivel = this->disponivel-lugares_ocupados;
		return lugares_ocupados;
	}
}

unsigned int Veiculo::getCapacidade(){
	return this->capacidade;
}

float Veiculo::getDist(){
	return this->dist;
}

void Veiculo::incDist(float dist){
	this->dist +=dist;
	this->num_travels++;
}
unsigned int Veiculo::getId(){
	return this->ID;
}

unsigned int Veiculo::get_num_travels(){
	return this->num_travels;
}
