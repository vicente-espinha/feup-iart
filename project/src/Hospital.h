#ifndef SRC_HOPITAL_H_
#define SRC_HOPITAL_H_

#include <iostream>
#include <utility>
#include <string>
#include "No.h"
#include "Path.h"
#include <limits>
#include <cstddef>
#include <vector>

using namespace std;

class Hospital: public No {
private:
	vector<Path> rescues;
public:
	/**
	 * Construtor default de um objeto do tipo resgate
	 */
	Hospital(){};

	Hospital(int id, int x, int y);

	void add_new_rescue(Path new_rescue);

	vector<Path> get_rescues();

};

#endif /* SRC_HOPITAL_H_ */
