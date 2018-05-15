#ifndef SRC_RESGATE_H_
#define SRC_RESGATE_H_

#include <iostream>
#include <utility>
#include <string>
#include "No.h"
#include "Path.h"
#include <limits>
#include <cstddef>
#include <vector>

using namespace std;

const float FLOAT_INFINITY = numeric_limits<float>::max();

class Resgate: public No {
private:
	vector<Path> outros_resgates;
	Path hospital;

public:
	/**
	 * Construtor default de um objeto do tipo resgate
	 */
	Resgate(int id, int x, int y, unsigned int nPessoas);

	bool decNPessoas(unsigned int nPessoas);

	void add_outro_resgate(Path new_rescue);

	void set_hospital(Path new_hospital);

	Path get_hospital();

	bool operator!=(Resgate &rhs);

};

#endif /* SRC_RESGATE_H_ */
