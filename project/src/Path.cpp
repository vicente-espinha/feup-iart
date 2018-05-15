
#include "Path.h"

Path::Path(float dist) {
	this->dist = dist;
}

Path::Path(vector<No*> path, float dist) {
	this->path = path;
	this->dist = dist;
}

vector<No*> Path::get_path() {
	return this->path;
}

float Path::get_dist() {
	return this->dist;
}

void Path::print() {

	for(int i=0; i<path.size(); i++) {
		cout<< path[i]->getID()<<", ";
	}
}

