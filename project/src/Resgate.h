#ifndef SRC_RESGATE_H_
#define SRC_RESGATE_H_

#include <iostream>
#include <string>
#include "Graph.h"
#include "No.h"

class Resgate {
private:
	No local;
	unsigned int nPessoas;
public:
	/**
	 * Construtor default de um objeto do tipo resgate
	 */
	Resgate(){};

	Resgate(No local, unsigned int nPessoas);

	No getlocalNode() const;

	void setlocalNode(No novoLocal);

	unsigned int getNPessoas();

	bool decNPessoas(unsigned int nPessoas);

};

#endif /* SRC_RESGATE_H_ */
