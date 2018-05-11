/*
 * No.cpp
 *
 *  Created on: 28/03/2017
 *      Author: Carlos Freitas
 */

#include "No.h"


using namespace std;

No::No(int id, int x, int y) {
	this->id = id;
	this->x = x;
	this->y =y;

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
	if( this->id == no1.getID())
	{

		return true;
	}
	return false;
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
