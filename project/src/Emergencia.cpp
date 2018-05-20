
#include "Emergencia.h"
#include "Rua.h"
#include "Graph.h"
#include <map>


using namespace std;

Emergencia::Emergencia(bool FloydWarshall) {
	ID_ARESTA_GERAL = 1;
	gv = new GraphViewer(600, 600, false);
	maingv =new GraphViewer(600, 600, false);


}

Emergencia::~Emergencia() {

}

Vertex<No>* Emergencia::findNo(int id) {

	vector<Vertex<No>*> vertices = myGraph.getVertexSet();
	for (unsigned int i = 0; i < vertices.size(); i++) {
		if (vertices.at(i)->getInfo().getID() == id)
			return vertices.at(i);

	}

	return NULL;

}

float Emergencia::firstGraph(No vehicle){
	main_graph = Graph<No>();
	unsigned int aresta = 1;
	main_graph.addVertex(vehicle);
	main_graph.addVertex(hospital);
	float max_dist=0.0, temp_dist;
	for(unsigned int i = 0; i < resgates.size();i++){
		temp_dist = resgates[i]-hospital;
		if(max_dist < temp_dist) {
			max_dist = temp_dist;
		}
		if(resgates[i].get_num_people() > 0){
			main_graph.addVertex(resgates[i]);
			main_graph.addEdge(aresta, vehicle, resgates[i],1);aresta++;
			main_graph.addEdge(aresta,resgates[i], hospital,1);aresta++;
		}

	}
	return max_dist;
}

void Emergencia::readStreets() {


	std::string line;

	char token;

	string nomeRua, twoWays;
	int NoID, idRua;

	//Ler o ficheiro ruas.txt
	ifstream inFile("../files/streets.txt");

	if (!inFile) {
		cerr << "Unable to open file ruas.txt";
		exit(1);   // call system to stop
	}

	while (getline(inFile, line)) {

		std::stringstream linestream(line);

		linestream >> idRua >> token;
		getline(linestream, nomeRua, ';');
		getline(linestream, twoWays, ';');

		Rua r(idRua, nomeRua, ((twoWays == "True") ? true : false));
		do {
			linestream >> NoID >> token;
			r.setNoID(NoID);
		} while (token == ',');
		ruas.push_back(r);


		for (unsigned int i = 0; i < r.getNosID().size() - 1; i++) {
			Vertex<No>* v1 = findNo(r.getNosID().at(i));
			Vertex<No>* v2 = findNo(r.getNosID().at(i + 1));
			No no1 = v1->getInfo();
			No no2 = v2->getInfo();


			double weight = sqrt(
					pow((no2.getX() - no1.getX()), 2)
					+ pow((no2.getY() - no1.getY()), 2));

			myGraph.addEdge(ID_ARESTA_GERAL, no1, no2, weight);

			ID_ARESTA_GERAL++;
		}

		if (twoWays == "True") {

			for (int i = r.getNosID().size() - 1; i > 0; i--) {

				Vertex<No>* v1 = findNo(r.getNosID().at(i));
				Vertex<No>* v2 = findNo(r.getNosID().at(i - 1));
				No no1 = v1->getInfo();
				No no2 = v2->getInfo();

				double weight = sqrt(
						pow((no2.getX() - no1.getX()), 2)
						+ pow((no2.getY() - no1.getY()), 2));

				myGraph.addEdge(ID_ARESTA_GERAL, no1, no2, weight);

				ID_ARESTA_GERAL++;
			}
		}

	}

	inFile.close();


}

void Emergencia::readHospitals(string filename){
	std::string line;

	long long int idNo = 0;
	float X = 0;
	float Y = 0;
	char token;


	//Ler o ficheiro hospitalNos.txt
	ifstream inFile(filename);

	if (!inFile) {
		cerr << "Unable to open hospitals file";
		cin.get();
		exit(1);   // call system to stop
	}

	while (getline(inFile, line)) {

		std::stringstream linestream(line);

		linestream >> idNo >> token >> X >> token >> Y;

		Hospital hospital(idNo, X, Y);
		myGraph.addVertex(hospital);
		this->hospital = hospital;

	}

	inFile.close();
}

void Emergencia::readInem(string filename){
	std::string line;

	long long int idNo = 0;
	float X = 0;
	float Y = 0;
	char token;

	//Ler o ficheiro inemNos.txt
	ifstream inFile(filename);

		if (!inFile) {
			cerr << "Unable to open Inem file";
			exit(1);   // call system to stop
		}
		unsigned int capacidade;
		unsigned int id = 1;

		while (getline(inFile, line)) {

			std::stringstream linestream(line);

			linestream >> idNo >> token >> X >> token >> Y >> token >> capacidade;

			No n(idNo, X, Y);

			myGraph.addVertex(n);
			Veiculo v(id,n,capacidade);
			id++;
			INEM.push_back(v);

		}

		inFile.close();
}

void Emergencia::readResgate(string filename){
	std::string line;

	long long int idNo = 0;
	float X = 0;
	float Y = 0;
	char token;

	//Ler o ficheiro inemNos.txt
	ifstream inFile(filename);

	if (!inFile) {
		cerr << "Unable to open Resgate file";
		exit(1);   // call system to stop
	}
	unsigned int npessoas_resgate;

	while (getline(inFile, line)) {

		std::stringstream linestream(line);

		linestream >> idNo >> token >> X >> token >> Y >> token >> npessoas_resgate;

		this->left_num_people += npessoas_resgate;

		Resgate resgate(idNo, X, Y ,npessoas_resgate);
		myGraph.addVertex(resgate);
		resgates.push_back(resgate);

	}

	inFile.close();
}

void Emergencia::readNodes(){
	ifstream inFile { };
	std::string line { };

	long long int idNo { 0 };
	float X = 0;
	float Y = 0;
	char token { };

	//Ler o ficheiro nosNormals.txt
	inFile.open("../files/nodes.txt");

	if (!inFile) {
		cerr << "Unable to open file nos.txt";
		exit(1);   // call system to stop
	}

	while (getline(inFile, line)) {

		std::stringstream linestream(line);

		linestream >> idNo >> token >> X >> token >> Y;
		No n(idNo, X, Y);
		myGraph.addVertex(n);

	}

	inFile.close();
}




void Emergencia::path(bool aStar) {


	tempoinicial = std::chrono::system_clock::now();
  while(this->left_num_people > 0){

	Veiculo* ambulance = this->ambulance_selection();
	float max_dist = this->firstGraph(ambulance->getlocalNode());
	if(aStar == true)
		main_graph.aStarPathComplex(ambulance->getlocalNode(), hospital, ambulance->getCapacidade(), &myGraph, max_dist);
	else
		main_graph.dijkstraPathComplex(ambulance->getlocalNode(), hospital, ambulance->getCapacidade(), &myGraph, max_dist);


	Path final_path = main_graph.getPath(ambulance->getlocalNode(), hospital);
	vector< Edge<No> > edges = myGraph.getEdges(final_path.get_nodes());
	gv->setVertexIcon(final_path.get_nodes().at(0).getID(),"../icons/normal.png");
	this->drawPath(edges, "red", "../icons/INEM.png");

	this->update_rescue(ambulance, final_path, edges);


  }
  tempofinal = std::chrono::system_clock::now();

  cout<<"TOTAL DISTANCE:  "<<this->total_distance;
  cout<<endl<<endl<<" TempoFinal: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(tempofinal-tempoinicial).count()<<endl;
}

void Emergencia::update_rescue(Veiculo * vehicle, Path path, vector<Edge<No>> edges){

	float final_dist = 0;

	for(unsigned int i = 0; i < edges.size(); i++){
		final_dist += edges[i].getWeight();
	}




	vehicle->incDist(final_dist); //update vehicle distance already done

	Vertex<No>* vertex = myGraph.getVertex(path.get_rescue());
	unsigned int left_people = min(vehicle->getCapacidade(), vertex->getInfo().get_num_people());
	vertex->updateInfo(left_people);


	for(unsigned int i = 0; i < resgates.size();i++){
		if(resgates[i] == vertex->getInfo()){
			resgates[i].dec_num_people(left_people);
		}
	}

	vehicle->setlocalNode(hospital);

	this->left_num_people -= left_people;
	this->total_distance += final_dist;

}

Veiculo* Emergencia::ambulance_selection(){

	float x = 0, y = 0;
	vector<float> people;
	int total_people = 0;
	float temp_people;
	bool exist = false;

	for(unsigned int i = 0; i < resgates.size(); i++){

		x += resgates[i].getX();
		y += resgates[i].getY();

		temp_people = resgates[i].get_num_people();
		total_people += temp_people;
		people.push_back(temp_people);

		if(resgates[i].get_num_people() > 0){
			exist = true;
		}
	}

	if(!exist)
		return NULL;

	//centroide
	x = x / resgates.size();
	y = y / resgates.size();

	float num_people_avg = total_people / resgates.size(),p = 0; //media de pessoas nos veiculos

	for(unsigned int i = 0; i < people.size(); i++){
		p = p + pow(people[i] - num_people_avg,2);
	}
	float total_people_aux = num_people_avg + sqrt(p/(resgates.size())); //media + desvio padrao 10%

	float distX,distY,dist_final_aux,capacidade_aux;
	vector<float> distances,times,capacidades;

	for(unsigned int i = 0; i < INEM.size(); i++){
		distX = pow((INEM[i].getlocalNode().getX()-x), 2);
		distY = pow((INEM[i].getlocalNode().getY()-y), 2);

		dist_final_aux = sqrt(distX + distY);

		capacidade_aux = abs(INEM[i].getCapacidade() - total_people_aux);

		distances.push_back(dist_final_aux);
		times.push_back(INEM[i].getDist());
		capacidades.push_back(capacidade_aux);
	}

	distances = this->calc_percentage(distances);  //50%
	times = this->calc_percentage(times); //40%
	capacidades = this->calc_percentage(capacidades);//10%

	vector<float>aux;
	float final_result;

	for(unsigned int i = 0; i < INEM.size(); i++){
		final_result = distances[i]*0.5 + times[i]*0.4 + capacidades[i]*0.1;

		aux.push_back(final_result);
	}

	int min_pos = distance(aux.begin(),min_element(aux.begin(),aux.end()));

	return &INEM[min_pos];
}

vector<float> Emergencia::calc_percentage(vector<float> raw_values) {
	float max = *max_element(raw_values.begin(), raw_values.end());
	if(max == 0)
		max = 1;
	vector< float> perc_values;
	for(unsigned int i=0; i<raw_values.size(); i++) {
		perc_values.push_back(raw_values[i]/max);
	}
	return perc_values;

}


vector<Path> Emergencia::calc_dist_rescues(Veiculo veiculo){
	No node = veiculo.getlocalNode();
	vector<Path> paths;
	if(hospital == node){
		paths = hospital.get_rescues();
		if(!paths.empty())
			return paths;
	}
	for(unsigned int i=0; i<resgates.size(); i++) {
		if(resgates[i].get_num_people() > 0){
			myGraph.aStarPath(node,resgates[i]);
			Path rescue = myGraph.getPath(node,resgates[i]);
			paths.push_back(rescue);
			if(hospital == node) {
				hospital.add_new_rescue(rescue);
			}
		}
	}
	return paths;
}




void Emergencia::displayGraph() {

	gv->createWindow(600, 600);

	gv->defineEdgeColor("black");
	gv->defineVertexIcon("../icons/normal.png");
	gv->defineEdgeCurved(false);

	vector<Vertex<No>*> vertexSet = myGraph.getVertexSet();

	typename vector<Vertex<No>*>::const_iterator it = vertexSet.begin();
	typename vector<Vertex<No>*>::const_iterator ite = vertexSet.end();

	for (; it != ite; it++) {

		No addno = (*it)->getInfo();

		gv->addNode(addno.getID(), (addno.getX() * 2) + 20,
				-(addno.getY() * 2) + 420);
		stringstream ss;
		ss << addno.getID();
		gv->setVertexLabel(addno.getID(), ss.str());
	}

	it = vertexSet.begin();
	ite = vertexSet.end();
	typename vector<Edge<No> >::iterator itEdges;
	typename vector<Edge<No> >::iterator iteEdges;

	for (; it != ite; it++) {

		vector<Edge<No> > edgesvec = (*it)->getAdj();
		itEdges = edgesvec.begin();
		iteEdges = edgesvec.end();
		for (; itEdges != iteEdges; itEdges++) {
			gv->addEdge((itEdges)->getID(), (*it)->getInfo().getID(),
					(itEdges)->getDest()->getInfo().getID(),
					EdgeType::DIRECTED);
		}

	}
	colorNodes();

	this->resetGV();
	this->writeRuas();
	gv->rearrange();

}

void Emergencia::displaySmallGraph(){
	maingv->createWindow(600, 600);

		maingv->defineEdgeColor("black");
		maingv->defineVertexIcon("../icons/normal.png");
		maingv->defineEdgeCurved(false);

		vector<Vertex<No>*> vertexSet = main_graph.getVertexSet();

		typename vector<Vertex<No>*>::const_iterator it = vertexSet.begin();
		typename vector<Vertex<No>*>::const_iterator ite = vertexSet.end();

		for (; it != ite; it++) {

			No addno = (*it)->getInfo();

			maingv->addNode(addno.getID(), (addno.getX() * 2) + 20,
					-(addno.getY() * 2) + 420);
			stringstream ss;
			ss << addno.getID();
			maingv->setVertexLabel(addno.getID(), ss.str());
		}

		it = vertexSet.begin();
		ite = vertexSet.end();
		typename vector<Edge<No> >::iterator itEdges;
		typename vector<Edge<No> >::iterator iteEdges;

		for (; it != ite; it++) {

			vector<Edge<No> > edgesvec = (*it)->getAdj();
			itEdges = edgesvec.begin();
			iteEdges = edgesvec.end();
			for (; itEdges != iteEdges; itEdges++) {
				maingv->addEdge((itEdges)->getID(), (*it)->getInfo().getID(),
						(itEdges)->getDest()->getInfo().getID(),
						EdgeType::DIRECTED);
			}

		}
		colorMainNodes();

		this->resetMainGV();
		maingv->rearrange();
}

void Emergencia::colorMainNodes() {

	vector<Veiculo>::iterator it = this->INEM.begin();
	for (; it != INEM.end(); it++) {
		if ((*it).getlocalNode().getID() != hospital.getID() )
			maingv->setVertexIcon((*it).getlocalNode().getID(), "../icons/INEM.png");
	}

	maingv->setVertexIcon(hospital.getID(), "../icons/hospital.png");


	vector<Resgate>::iterator itresgate = this->resgates.begin();
	for (; itresgate != resgates.end(); itresgate++) {
		maingv->setVertexIcon((*itresgate).getID(), "../icons/dead.png");

	}

	maingv->rearrange();
}

void Emergencia::resetMainGV() {

	vector<Vertex<No>*> vertexSet = main_graph.getVertexSet();
	typename vector<Vertex<No>*>::const_iterator it = vertexSet.begin();
	typename vector<Vertex<No>*>::const_iterator ite = vertexSet.end();
	typename vector<Edge<No> >::iterator itEdges;
	typename vector<Edge<No> >::iterator iteEdges;

	for (; it != ite; it++) {

		vector<Edge<No> > edgesvec = (*it)->getAdj();
		itEdges = edgesvec.begin();
		iteEdges = edgesvec.end();
		for (; itEdges != iteEdges; itEdges++) {
			maingv->setEdgeColor(itEdges->getID(), "black");
			maingv->setEdgeThickness(itEdges->getID(), 1);
		}

	}

	vector<Vertex<No>*> aux = main_graph.getVertexSet();
	for (unsigned int i = 0; i < aux.size(); i++) {
		maingv->setVertexIcon(aux.at(i)->getInfo().getID(), "../icons/normal.png");
	}
	this->colorMainNodes();

	maingv->rearrange();
}

void Emergencia::colorNodes() {

	vector<Veiculo>::iterator it = this->INEM.begin();
	for (; it != INEM.end(); it++) {
		if ((*it).getlocalNode().getID() != hospital.getID() )
			gv->setVertexIcon((*it).getlocalNode().getID(), "../icons/INEM.png");
	}

	gv->setVertexIcon(hospital.getID(), "../icons/hospital.png");


	vector<Resgate>::iterator itresgate = this->resgates.begin();
	for (; itresgate != resgates.end(); itresgate++) {
		gv->setVertexIcon((*itresgate).getID(), "../icons/dead.png");

	}

	gv->rearrange();
}


void Emergencia::drawPath(vector<Edge<No> > &edgepath, string color,
		string icon) {

	for (unsigned int i = 0; i < edgepath.size(); i++) {
		gv->setVertexIcon(edgepath.at(i).getDest()->getInfo().getID(), icon);

		gv->setEdgeColor(edgepath.at(i).getID(), color);
		gv->setEdgeThickness(edgepath.at(i).getID(), 5);
		gv->rearrange();
		Sleep(1000);



		if(i == (edgepath.size()-1)){
			gv->setVertexIcon(edgepath.at(i).getDest()->getInfo().getID(),
							"../icons/hospital.png");
		}else
		gv->setVertexIcon(edgepath.at(i).getDest()->getInfo().getID(),
				"../icons/normal.png");
		gv->rearrange();
	}

}


void Emergencia::resetGV() {

	vector<Vertex<No>*> vertexSet = myGraph.getVertexSet();
	typename vector<Vertex<No>*>::const_iterator it = vertexSet.begin();
	typename vector<Vertex<No>*>::const_iterator ite = vertexSet.end();
	typename vector<Edge<No> >::iterator itEdges;
	typename vector<Edge<No> >::iterator iteEdges;

	for (; it != ite; it++) {

		vector<Edge<No> > edgesvec = (*it)->getAdj();
		itEdges = edgesvec.begin();
		iteEdges = edgesvec.end();
		for (; itEdges != iteEdges; itEdges++) {
			gv->setEdgeColor(itEdges->getID(), "black");
			gv->setEdgeThickness(itEdges->getID(), 1);
		}

	}

	vector<Vertex<No>*> aux = myGraph.getVertexSet();
	for (unsigned int i = 0; i < aux.size(); i++) {
		gv->setVertexIcon(aux.at(i)->getInfo().getID(), "../icons/normal.png");
	}
	this->colorNodes();

	gv->rearrange();
}

void Emergencia::closeGV() {
	gv->closeWindow();
	//maingv->closeWindow();
}

vector<Rua> Emergencia::getRuas() {
	return this->ruas;
}

void Emergencia::writeRuas() {
	vector<No> path;
	for (unsigned int i = 0; i < ruas.size(); i++) {
		for (unsigned int a = 0; a < ruas.at(i).getNosID().size(); a++) {
			No n = No(ruas.at(i).getNosID().at(a));
			path.push_back(n);
		}
		vector<Edge<No> > aux = myGraph.getEdges(path);
		path.clear();
		for (unsigned int a = 0; a < aux.size(); a++) {
			//gv->setEdgeLabel(aux.at(a).getID(), ruas.at(i).getNome());
			gv->setEdgeLabel(aux.at(a).getID(), to_string(aux.at(a).getWeight()));
		}
		aux.clear();
	}

}

bool Emergencia::verificarConetividade() {
	return myGraph.stronglyConnectedComponents();
}



void Emergencia::encontraVeiculos(vector<int> ids) {
	string ret = "";
	bool in = false;
	vector<int> numInem;
	vector<int> numPolicias = vector<int>();
	vector<int> numBombeiros;


	for(unsigned int i = 0; i < INEM.size(); i++) {
		for (unsigned int a = 0; a < ids.size(); a++) {
			if (INEM.at(i).getlocalNode().getID() == ids.at(a)) {
				in = true;
				numInem.push_back(ids.at(a));
				break;
			}
		}
	}
	if(in){
		cout<<"    INEM: ";
		for(unsigned int i=0; i<numInem.size(); i++)
			 cout<<numInem[i]<<" ";
		cout<<endl;
	}
	else
		cout<<"Nao existe INEM nesta rua\n";

}


void Emergencia::resetEmergencia(){
	this->INEM.clear();
	this->ruas.clear();
	gv = new GraphViewer(600, 600, false);
	system_clock::time_point tempoinicial=system_clock::now();
	system_clock::time_point  tempofinal=system_clock::now();
	ID_ARESTA_GERAL = 1;
	total_distance = 0;
	left_num_people = 0;
	resgates.clear();

}
