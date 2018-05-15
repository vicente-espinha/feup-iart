#include "Resgate.h"

using namespace std;

Resgate::Resgate(int id, int x, int y, unsigned int nPessoas): No(id, x, y){
	this->nPessoas = nPessoas;
	this->hospital = Path(FLOAT_INFINITY);
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


void Resgate::add_outro_resgate(Path new_rescue) {
	this->outros_resgates.push_back(new_rescue);
}

void Resgate::set_hospital(Path new_hospital) {

	if(this->hospital.get_dist() > new_hospital.get_dist()){
		this->hospital = new_hospital;
	}
}

Path Resgate::get_hospital(){
	return this->hospital;
}

bool Resgate::operator!=(Resgate &rhs){
	return this->getX() != rhs.getX() && this->getY() != rhs.getY();
}
