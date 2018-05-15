#include "Hospital.h"

	Hospital::Hospital(int id, int x, int y): No(id, x, y,0){}

	void Hospital::add_new_rescue(Path new_rescue) {
		this->rescues.push_back(new_rescue);
	}

	vector<Path> Hospital::get_rescues(){
		return this->rescues;
	}
