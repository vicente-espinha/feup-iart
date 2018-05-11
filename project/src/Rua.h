/*
 * Rua.h
 *
 *  Created on: 29/03/2017
 *      Author: up201503344
 */

#ifndef SRC_RUA_H_
#define SRC_RUA_H_

#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
using namespace std;


class Rua {
private:
	string nome;
	int ID;

	vector<int> IDnos;
	bool twoways;

public:

	/**
	 * Construtor de um objeto do tipo rua. Uma rua e caraterizada por um nome especifico e um ID, para cada rua,
	 * é guardados identificadores de todos os nos que representam o percurso dessa mesma rua.Uma rua pode ser de um ou dois sentidos
	 * @param ID identificador de uma rua
	 * @param nome nome que representa a rua
	 * @param twoWays flag que diz se a rua e de dois sentidos(true) ou de apenas um (false)
	 */
	Rua(int ID, string nome, bool twoWays);
	/**
	 * Destrutor default de uma Rua
	 */
	virtual ~Rua();
	/**
	 * Adiciona ao vetor de identificadores de nos com o valor dado como parametro
	 * @param IDnos inteiro a ser adicionado ao vetor IDnos
	 */
	void setNoID(int IDnos);
	/**
	 * Funcao que retorna o vetor que representao os Nos que pertencem a rua
	 * @return a variavel IDnos do objeto
	 */
	vector<int> getNosID();
	/**
	 * Devolve o nome da rua
	 * @return a variavel nome do objeto
	 */
	string getNome();
	/**
	 *Retorna,aleatoriamente um identificador de um no que pertence a rua
	 *@return o valor aleatorio do vetor nosID
	 */
	int getRandNoID();
	/**
	 * Retorna o id da rua
	 * @return Id da rua
	 */
	int getID();
};

#endif /* SRC_RUA_H_ */
