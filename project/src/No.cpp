/*
 * No.cpp
 *
 *  Created on: 28/03/2017
 *      Author: Carlos Freitas
 */

#include "No.h"


using namespace std;

No::No(int id, int x, int y, unsigned int nPessoas) {
	this->id = id;
	this->x = x;
	this->y =y;
	this->num_people = 0;
}

bool No::dec_num_people(unsigned int n_people){
	if(this->num_people-n_people < 0)
		return false;

	this->num_people = n_people;
	return true;
}

No::No(int id)
{
	this->id = id;
}

No::~No() {
	// TODO Auto-generated destructor stub
}

int No::getID() const{
	return id;
}

bool No::operator==(const No &no1) const
{
	return this->id == no1.getID();
}
int No::getX() const{
	return x;

}
int No::getY() const{
	return y;

}

bool No::operator<(const No &no1) const
{
	return this->getID() < no1.getID();
}

unsigned int No::getNPessoas(){
	return this->num_people;
}
