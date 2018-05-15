#include "Resgate.h"

using namespace std;

Resgate::Resgate(int id, int x, int y, unsigned int nPessoas): No(id, x, y,nPessoas){
	this->hospital = Path(FLOAT_INFINITY);
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
