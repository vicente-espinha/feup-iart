#ifndef SRC_PATH_H_
#define SRC_PATH_H_

#include <iostream>
#include <utility>
#include <string>
#include "No.h"
#include <limits>
#include <cstddef>
#include <vector>

using namespace std;

class Path {
private:
	vector<No*> path;
	float dist;

public:
	Path(){};
	Path(float dist);
	Path(vector<No*> path, float dist);
	vector<No*> get_path();
	float get_dist();
	void print();

};

#endif /* SRC_PATH_H_ */
