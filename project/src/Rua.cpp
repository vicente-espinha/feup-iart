/*
 * Rua.cpp
 *
 *  Created on: 29/03/2017
 *      Author: up201503344
 */

#include "Rua.h"

Rua::Rua(int ID, string nome, bool twoWays) {
	this->ID=ID;
	this->nome=nome;
	this->twoways=twoWays;

}

void Rua::setNoID(int IDno){
	IDnos.push_back(IDno);
}

Rua::~Rua() {
	// TODO Auto-generated destructor stub
}

vector<int> Rua::getNosID(){
	return IDnos;
}

string Rua::getNome()
{
	return this->nome;
}

int Rua::getRandNoID(){
	srand(time(NULL));

	return IDnos[rand()%IDnos.size()];
}

int Rua::getID(){
	return ID;
}
