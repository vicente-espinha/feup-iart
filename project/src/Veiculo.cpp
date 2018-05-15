
#include "Veiculo.h"

Veiculo::Veiculo(No local, unsigned int capacidade) : disponivel(0){
	this->local = local;
	this->capacidade = capacidade;
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

void Veiculo::decDisponibilidade(){
	if(disponivel > 0)
		disponivel--;
}

unsigned int Veiculo::getCapacidade(){
	return this->capacidade;
}

bool Veiculo::decCapacidade(unsigned int lugares_ocupados){
	if(this->capacidade-lugares_ocupados < 0)
		return false;
	else
		this->capacidade = this->capacidade-lugares_ocupados;
	return true;
}

float Veiculo::get_dist(){
	return this->dist;
}

void Veiculo::inc_dist(float dist){
	this->dist +=dist;
}
