/*
 * No.h
 *
 *  Created on: 28/03/2017
 *      Author: Carlos Freitas
 */

#ifndef SRC_NO_H_
#define SRC_NO_H_

#include <iostream>

class No {
private:
	int id;
	int x;
	int y;
	unsigned int num_people;
public:
	/**
	 * Construtor default de um objeto do tipo no
	 */
	No() {
	}
	;
	/**
	 * Construtor que cria um no com o id indicado como parametro
	 * @param id id do novo No a criar
	 */
	No(int id);
	/**
	 * Construtor de um No que o cria com o id dado como parametro,e com as coordenadas do mesmo;
	 * @param id Id do novo No
	 * @param x representacao da posicao nos eixos xx do novo No
	 * @param y representacao da posicao nos eixos yy do novo No
	 */
	No(int id, int x, int y);

	No(int id, int x, int y, unsigned int num_people);
	/**
	 * Destrutor default de um No
	 */
	virtual ~No();
	/*
	 * Devolve a variavel que representa o identificador do No
	 * @return a variavel id do No
	 */
	int getID() const;
	/**
	 * Overload do operador de igualdade de forma a comparar dois Nos,dois Nos sao considerados
	 * equivalentes se os seus ids forem iguais;
	 * @param no1 No a comparar com
	 * @return true se os nos forem iguais,caso contrario retorna false;
	 */
	bool operator==(const No &no1) const;
	/**
	 *Overload do operador de inferioridade, um No e considerado menor que outro caso o seu id seja com o id do No  a comparar
	 *@param no1 No a comparar com
	 *@return true se o No for menor que no1,caso contrario retorna false;
	 */
	bool operator<(const No &no1) const;
	/**
	 * Devolve a representacao do No nos eixos xx
	 * @return a variavel x do No
	 */
	int getX() const;
	/**
	 * Devolve a representacao do No nos eixos yy
	 * @return a variavel y do No
	 */
	int getY() const;

	unsigned int get_num_people();

	bool dec_num_people(unsigned int n_people);

	float operator-(const No &no1) const;
};

#endif /* SRC_NO_H_ */
