#include "Resgate.h"

using namespace std;

Resgate::Resgate(No local, unsigned int nPessoas){
	this->local = local;
	this->nPessoas = nPessoas;
}

No Resgate::getlocalNode() const{
	return this->local;
}

void Resgate::setlocalNode(No novoLocal){
	this->local = novoLocal;
}

unsigned int Resgate::getNPessoas(){
	return this->nPessoas;
}

bool Resgate::decNPessoas(unsigned int nPessoas){
	if(this->nPessoas-nPessoas < 0)
		return false;

	this->nPessoas = nPessoas;
	return true;

}
