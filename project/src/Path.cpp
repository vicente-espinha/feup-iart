
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

bool Path::operator<(Path &rhs){
	return this->dist < rhs.get_dist();
}

void Path::append(Path rhs){
	vector<No*> rhs_path = rhs.get_path();
	this->path.insert(this->path.begin(), rhs_path.begin(), rhs_path.end());
	this->dist += rhs.get_dist();
}

vector<No> Path::get_nodes() {
	vector<No> nodes;
	for(unsigned int i=0; i<this->path.size(); i++) {
		nodes.push_back(*(this->path[i]));
	}
	return nodes;
}

No* Path::get_rescue(){
	return this->rescue;
}

void Path::set_rescue(No* rescue){
	this->rescue = rescue;
}

