
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

void Path::update_vehicle_path(Veiculo * vehicle){
	for(unsigned int i = 0; i < path.size();i++){
		unsigned int people_rescued = vehicle->decDisponibilidade(path[i]->get_num_people());
		if(people_rescued > 0){
			path[i]->dec_num_people(people_rescued);
		}
	}

}

