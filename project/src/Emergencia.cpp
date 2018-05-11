
#include "Emergencia.h"
#include "Rua.h"
#include "Graph.h"
#include <map>


using namespace std;

Emergencia::Emergencia(bool FloydWarshall) {
	ID_ARESTA_GERAL = 1;
	gv = new GraphViewer(600, 600, false);


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

void Emergencia::readStreets() {

	ifstream inFile;
	std::string line;

	long long int idNo = 0;
	float X = 0;
	float Y = 0;
	char token;

	string nomeRua, twoWays;
	int NoID, idRua;

	//Ler o ficheiro ruas.txt
	inFile.open("ruas.txt");

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

		//TODO print
		cout<<"RUAS";
		for(int i=0; i<ruas.size(); i++) {
			cout<< ruas[i].getNome()<<endl;
		}
		cin.get();

	}

	inFile.close();

}

void Emergencia::readHospitals(string filename){
	ifstream inFile;
	std::string line;

	long long int idNo = 0;
	float X = 0;
	float Y = 0;
	char token;


	//Ler o ficheiro hospitalNos.txt
	inFile.open(filename);

	if (!inFile) {
		cerr << "Unable to open hospitals file";
		exit(1);   // call system to stop
	}

	while (getline(inFile, line)) {

		std::stringstream linestream(line);

		linestream >> idNo >> token >> X >> token >> Y;

		No n(idNo, X, Y);
		myGraph.addVertex(n);
		hospitais.push_back(n);

	}

	inFile.close();

	//TODO print
	 cout << "hospitais";
	for(int j = 0; j < hospitais.size();j++){
		cout << hospitais[j].getID() <<"\n";
	}
	cin.get();
}

void Emergencia::readInem(string filename){
	ifstream inFile;
	std::string line;

	long long int idNo = 0;
	float X = 0;
	float Y = 0;
	char token;

	//Ler o ficheiro inemNos.txt
		inFile.open(filename);

		if (!inFile) {
			cerr << "Unable to open Inem file";
			exit(1);   // call system to stop
		}
		unsigned int capacidade;

		while (getline(inFile, line)) {

			std::stringstream linestream(line);

			linestream >> idNo >> token >> X >> token >> Y >> token >> capacidade;

			No n(idNo, X, Y);

			myGraph.addVertex(n);
			Veiculo v(n,capacidade);
			INEM.push_back(v);

		}

		inFile.close();


		//TODO print
		 cout << "INEM";
		for(int j = 0; j < INEM.size();j++){
			cout << INEM[j].getlocalNode().getID() <<"    "<<INEM[j].getCapacidade()<<"\n";
		}
		cin.get();
}

void Emergencia::readResgate(string filename){
	ifstream inFile;
	std::string line;

	long long int idNo = 0;
	float X = 0;
	float Y = 0;
	char token;

	//Ler o ficheiro inemNos.txt
	inFile.open(filename);

	if (!inFile) {
		cerr << "Unable to open Resgate file";
		exit(1);   // call system to stop
	}
	unsigned int npessoas_resgate;

	while (getline(inFile, line)) {

		std::stringstream linestream(line);

		linestream >> idNo >> token >> X >> token >> Y >> token >> npessoas_resgate;

		No n(idNo, X, Y);

		myGraph.addVertex(n);
		Resgate resgate(n,npessoas_resgate);
		resgates.push_back(resgate);

	}

	inFile.close();


	//TODO print
	 cout << "RESGATE";
	for(int j = 0; j < resgates.size();j++){
		cout << resgates[j].getlocalNode().getID() <<"    "<<resgates[j].getNPessoas()<<"\n";
	}
	cin.get();
}

void Emergencia::readNodes(){
	ifstream inFile;
	std::string line;

	long long int idNo = 0;
	float X = 0;
	float Y = 0;
	char token;

	//Ler o ficheiro nosNormals.txt
	inFile.open("nos.txt");

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

void Emergencia::getCall(int noID, int polFlag, int bombFlag, int inemFlag,
		bool gotoHospital) {

	/*if (!myGraph.stronglyConnectedComponents()) {
		cout << "Nao e possivel calcular a sua chamada por invalidade do mapa"
				<< endl;
		getchar();
		return;
	}*/

	tempoinicial = std::chrono::system_clock::now();

	No localizacao;
	gv->setVertexIcon(noID, "ajuda1.png");
	for (unsigned int i = 0; i < myGraph.getVertexSet().size(); i++) {
		if (myGraph.getVertexSet()[i]->getInfo().getID() == noID)
			localizacao = myGraph.getVertexSet()[i]->getInfo();
	}

	vector<Edge<No> > pathedgesPolicia;
	vector<Edge<No> > pathedgesBombeiros;
	vector<Edge<No> > pathedgesINEM;
	vector<Edge<No> > pathHospital;
	vector<No> pathnodes;
	vector<vector<Edge<No> > > pathsPolicia;
	vector<vector<Edge<No> > > pathsBombeiros;
	vector<vector<Edge<No> > > pathsINEM;
	while (inemFlag > 0) {

		No INEMAssistencia = findElement(myGraph.getVertex(localizacao),
				pathnodes, 'I');
		if (pathnodes.size() > 0) {

			cout << "A ambulancia do INEM seguira o seguinte caminho: ";
			for (unsigned int i = 0; i < pathnodes.size(); i++)
				cout << pathnodes[i].getID() << " ";
			cout << endl;
			pathedgesINEM = myGraph.getEdges(pathnodes);
			pathsINEM.push_back(pathedgesINEM);

		} else
			cout << "Na sua localizaçao ja existe ambulancias\n";
		inemFlag--;

	}
	pathnodes.clear();
	while (bombFlag > 0) {
		No BombAssistencia = findElement(myGraph.getVertex(localizacao),
				pathnodes, 'B');
		if (pathnodes.size() > 0) {
			cout << "O camiao dos bombeiros seguira o seguinte caminho: ";
			for (unsigned int i = 0; i < pathnodes.size(); i++)
				cout << pathnodes[i].getID() << " ";
			cout << endl;
			pathedgesBombeiros = myGraph.getEdges(pathnodes);
			pathsBombeiros.push_back(pathedgesBombeiros);
		} else
			cout << "Na sua localizacao ja existe uns bombeiros\n" << endl;
		bombFlag--;
	}

	pathnodes.clear();
	while (polFlag > 0) {
		No PoliciaAssistencia = findElement(myGraph.getVertex(localizacao),
				pathnodes, 'P');
		if (pathnodes.size() > 0) {
			cout << "O carro da policia seguira o seguinte caminho: ";
			for (unsigned int i = 0; i < pathnodes.size(); i++)
				cout << pathnodes[i].getID() << " ";
			cout << endl;
			pathedgesPolicia = myGraph.getEdges(pathnodes);
			pathsPolicia.push_back(pathedgesPolicia);
		} else
			cout << "Na sua localizacao ja existe policias\n" << endl;
		polFlag--;
	}
	if (gotoHospital) {
		pathHospital = moveToHospital(myGraph.getVertex(localizacao));
		if (pathHospital.size() == 0)
			cout << "Na sua localizacao ja existe um hospital\n" << endl;
	}

	tempofinal = std::chrono::system_clock::now();
	cout << endl << "Tempo Final: " << system_clock::to_time_t(tempofinal) << endl;
	for (unsigned int i = 0; i < pathsINEM.size(); i++)
		this->drawPath(pathsINEM[i], "green", "INEM.png");
	for (unsigned int i = 0; i < pathsBombeiros.size(); i++)
		this->drawPath(pathsBombeiros[i], "red", "bombeiro.png");
	for (unsigned int i = 0; i < pathsPolicia.size(); i++)
		this->drawPath(pathsPolicia[i], "blue", "policia.png");
	if (pathHospital.size() > 0) {
		drawPath(pathHospital, "green", "INEM.png");
	}

}

void Emergencia::displayGraph() {

	gv->createWindow(600, 600);

	gv->defineEdgeColor("black");
	gv->defineVertexIcon("normal.png");
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
	cin.get();

}

void Emergencia::colorNodes() {

	vector<Veiculo>::iterator it = this->INEM.begin();
	for (; it != INEM.end(); it++) {
		(*it).decDisponibilidade();
		if ((*it).getDisponibilidade() == 0)
			gv->setVertexIcon((*it).getlocalNode().getID(), "INEM.png");

	}
	for (unsigned int i = 0; i < this->hospitais.size(); i++) {
		gv->setVertexIcon(hospitais.at(i).getID(), "hospital.png");
	}

	vector<Resgate>::iterator itresgate = this->resgates.begin();
	for (; itresgate != resgates.end(); itresgate++) {
		//TODO WHAT??
		//(*it).decDisponibilidade();
		gv->setVertexIcon((*itresgate).getlocalNode().getID(), "dead.png");

	}

	gv->rearrange();
}

No Emergencia::findElement(Vertex<No>* localizacao, vector<No> &pathnodes,
		char elementType) {

	vector<Veiculo>* auxvector;
	switch (elementType) {
	case 'I':
		auxvector = &INEM;
		break;
	};

	Veiculo* veicFinal;
	int distAtual;
	int distMinima = INT_MAX;

	/*if (!(isFloydWarshall)) {
		for (unsigned int i = 0; i < (*auxvector).size(); i++) {
			if ((*auxvector)[i].getDisponibilidade() == 0) {
				myGraph.dijkstraShortestPath((*auxvector)[i].getlocalNode());
				distAtual = localizacao->getDist();
				if (distAtual < distMinima) {
					distMinima = distAtual;
					veicFinal = &(*auxvector)[i];
					if (!((*auxvector)[i].getlocalNode()
							== localizacao->getInfo()))
						pathnodes = myGraph.getPath(
								(*auxvector)[i].getlocalNode(),
								localizacao->getInfo());
				}
			}

		}

	} else {

		for (unsigned int i = 0; i < (*auxvector).size(); i++) {
			if ((*auxvector)[i].getDisponibilidade() == 0) {
				distAtual =
						myGraph.getfloydWarshallweight(
								myGraph.getVertex(
										(*auxvector)[i].getlocalNode())->getVectorPos(),
										localizacao->getVectorPos());
				if (distAtual < distMinima) {
					distMinima = distAtual;
					veicFinal = &(*auxvector)[i];
				}
			}
		}
		if (!((*veicFinal).getlocalNode() == localizacao->getInfo()))
			pathnodes = myGraph.getfloydWarshallPath(
					(*veicFinal).getlocalNode(), localizacao->getInfo());
	}*/

	(*veicFinal).setDisponibilidade(3);
	if (pathnodes.size() > 0)
		(*veicFinal).setlocalNode(pathnodes[pathnodes.size() - 1]);
	return (*veicFinal).getlocalNode();

}

void Emergencia::drawPath(vector<Edge<No> > &edgepath, string color,
		string icon) {

	for (unsigned int i = 0; i < edgepath.size(); i++) {
		gv->setVertexIcon(edgepath.at(i).getDest()->getInfo().getID(), icon);

		gv->setEdgeColor(edgepath.at(i).getID(), color);
		gv->setEdgeThickness(edgepath.at(i).getID(), 5);
		gv->rearrange();
		Sleep(1000);
		gv->setVertexIcon(edgepath.at(i).getDest()->getInfo().getID(),
				"normal.png");
		gv->rearrange();
	}

}

vector<Edge<No> > Emergencia::moveToHospital(Vertex<No>* localizacao) {
	int distmin = INT_MAX;
	No nofinal;
	Vertex<No>* aux;
	vector<No> nodestopaint;
	vector<Edge<No> > edgestopaint;
	/*if (!isFloydWarshall) {
		myGraph.dijkstraShortestPath(localizacao->getInfo());
		for (unsigned int i = 0; i < this->hospitais.size(); i++) {
			aux = myGraph.getVertex(hospitais.at(i));
			if (aux->getDist() < distmin) {
				distmin = aux->getDist();
				nofinal = hospitais.at(i);
			}
		}
		if (distmin != 0) {
			cout
			<< "Posteriormente a ambulancia seguira o seguinte caminho em direcao ao hospital: ";
			nodestopaint = myGraph.getPath(localizacao->getInfo(), nofinal);
			for (unsigned int i = 0; i < nodestopaint.size(); i++)
				cout << nodestopaint[i].getID() << " ";
			cout << endl;

		} else {
			cout << "Na sua localizacao ja existe um hospital\n";
		}
	} else {

		int weight;
		for (unsigned int i = 0; i < this->hospitais.size(); i++) {
			weight = myGraph.getfloydWarshallweight(localizacao->getVectorPos(),
					myGraph.getVertex(hospitais[i])->getVectorPos());
			if (weight < distmin) {
				distmin = weight;
				nofinal = hospitais.at(i);
			}
		}
		if (distmin != 0) {
			cout
			<< "Posteriormente a ambulancia seguira o seguinte caminho em direcao ao hospital: ";
			nodestopaint = myGraph.getfloydWarshallPath(localizacao->getInfo(),
					nofinal);
			for (unsigned int i = 0; i < nodestopaint.size(); i++)
				cout << nodestopaint[i].getID() << " ";
			cout << endl;

		} else {
			cout << "Na sua localizacao ja existe um hospital\n";
		}

	}*/
	if (distmin != 0)
		edgestopaint = myGraph.getEdges(nodestopaint);
	return edgestopaint;
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
		gv->setVertexIcon(aux.at(i)->getInfo().getID(), "normal.png");
	}
	this->colorNodes();

	gv->rearrange();
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
			gv->setEdgeLabel(aux.at(a).getID(), ruas.at(i).getNome());
		}
		aux.clear();
	}

}

bool Emergencia::verificarConetividade() {
	return true;
	//return myGraph.stronglyConnectedComponents();
}

/*
vector<string> Emergencia::verificacaoExata(string user_string, string tipo, Freguesia fr) {
	tempoinicial = std::chrono::system_clock::now();
	string ret = "";
	vector<string> vRet;
	bool encontrou = false;
	if(tipo == "ruas")
		for (unsigned int i = 0; i < getKeys(fr.getIDRuaNo()).size(); i++) {
			if (pesquisaExata(user_string, ruas.at(getKeys(fr.getIDRuaNo()).at(i) - 1).getNome())) {
				encontrou = true;
				 vRet.push_back(ruas.at(getKeys(fr.getIDRuaNo()).at(i) - 1).getNome());


			}
		}
	else
		for (unsigned int i = 0; i < freguesias.size(); i++) {
			if (pesquisaExata(user_string, freguesias.at(i).getNome())) {
				encontrou = true;
				vRet.push_back(freguesias.at(i).getNome());


			}
		}
	if(!encontrou)
		vRet.push_back("lugar desconhecido");
	tempofinal = std::chrono::system_clock::now();
	cout<<endl<<endl<<" TempoFinal: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(tempofinal-tempoinicial).count();
	return vRet;
}
*/

bool Emergencia::pesquisaExata(string rua_utilizador, string rua_grafo) {

	vector<string> splited_rua_grafo = splitString(rua_grafo);
	vector<string> splited_rua_utilizador = splitString(rua_utilizador);
	for(int i = 0 ; (i + splited_rua_utilizador.size()) <= splited_rua_grafo.size() ; i++ ){
		string text = concatenateStrings(splited_rua_grafo, splited_rua_utilizador.size(), i);
		string pattern = concatenateStrings(splited_rua_utilizador, splited_rua_utilizador.size(), 0);
		if(KMP(pattern, text))
			return true;

	}
	return false;
}

multimap<int, string> Emergencia::pesquisaAproximada(string rua_utilizador, vector<string> &graph_vector){



	vector<string> split_rua_utilizador = splitString(rua_utilizador); // vetor com todas as palavras escritas pelo utilizador, divididas em strings
	vector<string> split_rua_grafo; // vetor com todas as palavras da rua do grafo que se encontra em análise, divididas em strings
	map<string, int> map_ruas; // map <nome da rua, menor diferenca entre a palavra do utilizador, a ser analisada e as varias palavras da rua em questao>
	vector<map<string,int> > diferenca_ruas; //vetor contendo os map_ruas de cada uma das palavras escritas pelo utilizador
	multimap<int, string> final; //multimap<diferenca minima total da rua em consideracao, nome da rua em consideracao>
	int diferenca_minima;
	int diferenca_temp;

	//itera todas as palavras escritas pelo utilizador
	for (unsigned int i=0; i<split_rua_utilizador.size(); i++){

		//para cada palavra do utilizador itera todas as ruas do grafo
		for(unsigned int j=0; j<graph_vector.size(); j++){

			split_rua_grafo= splitString(graph_vector[j]); // divide a ruado grafo em analise nas suas varias palavras
			diferenca_minima = -1; // reset ao valor da diferenca minima da rua sinalizando que houve mudanca de rua

			//itera cada uma das palavras da rua do grafo em analise
			for(unsigned int k=0; k<split_rua_grafo.size(); k++){

				//condicao para garantir que as palavras com tamanho menor que o da palavra do utilizador,
				//e que ao mesmo tempo nao tem 3 caracteres(para evitar analise excessiva de palavras com "de" "da",
				//que poderiam provocar semelhancas indesejadas), nao serão analisadas.
				if((split_rua_grafo[k].size() < split_rua_utilizador[i].size()) && ( split_rua_grafo[k].size() <= 3))
					continue;

				//obtem a distancia entre a palvara do utilizador que esta a ser analisada
				//e a palavra da rua que esta a ser analisada
				diferenca_temp = editDistance(split_rua_utilizador[i], split_rua_grafo[k]);

				//verifica se essa é a primeira palavra da rua que esta a ser analisada
				//ou se a sua diferenca dessa rua é menor que a minima diferenca atual da rua,
				//atualizando a diferenca minima se for esse o caso
				if(diferenca_minima ==-1 || diferenca_temp<diferenca_minima){
					diferenca_minima = diferenca_temp;
				}

			}
			//insere a rua analisada no map de ruas da palavra de utilizador que esta atualmente a ser analisada
			map_ruas.insert(pair<string, int>(graph_vector[j], diferenca_minima));
		}
		//terminado a analise da palavra do utilizador para todas as ruas,
		//guarda-se o map resultante para cada palavra, limpando o map ruas para que possa ser utilizado pela palavra seguinte
		diferenca_ruas.push_back(map_ruas);
		map_ruas.clear();

	}

	int totaldistance;

	//calcula a menor diatncia total entre a cada rua do grafo e a string total escrita pelo utilizador
	for(unsigned int i=0;i< graph_vector.size(); i++){

		totaldistance=0;
		//para cada rua itera-se o vetor que contem os maps de cada uma das palavras da string do utilizaodr
		for(unsigned int j=0; j<diferenca_ruas.size(); j++){

			//soma as varias distancias minimas da rua em analise
			totaldistance += diferenca_ruas[j][graph_vector[i]];
		}
		//insere no vetor final um par contendo a minima distancia total da rua e o seu nome
		//para que sejam ordenados por minima distancia
		final.insert(pair<int, string>(totaldistance, graph_vector[i]));
	}

	//retorna o nome das ruas pela sua ordem de semelhanca,da mais semelhante para a menos semelhante
	return final;

}
/*
vector<string> Emergencia::verificacaoAproximada(string string_utilizador, string tipo, Freguesia fr){
	tempoinicial = std::chrono::system_clock::now();
	vector<string> graph_strings;
	vector<string> ret;
	vector<int> IDruas;
	if(tipo == "ruas"){
		IDruas = getKeys(fr.getIDRuaNo());
		for(int i=0; i<IDruas.size(); i++){

			graph_strings.push_back(ruas.at(IDruas[i]-1).getNome());
		}
	}else
	{
		for(int i=0; i<freguesias.size(); i++){

			graph_strings.push_back(freguesias[i].getNome());
		}
	}
	multimap<int,string> final_strings = pesquisaAproximada(string_utilizador, graph_strings);

	unsigned int to_print = 0;
	for (std::multimap<int,string>::iterator it=final_strings.begin(); it!=final_strings.end(); ++it){
		if(to_print < 6 ){


			cout<< to_print+1 << " - " << (*it).second<<endl;
			ret.push_back((*it).second);
			to_print++;

		}
		else
			break;
	}
	tempofinal = std::chrono::system_clock::now();
	cout<<endl<<endl<<" TempoFinal: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(tempofinal-tempoinicial).count();
	getchar();
	return ret;

}
*/


void Emergencia::encontraVeiculos(vector<int> ids) {
	string ret = "";
	bool in = false;
	bool bomb = false;
	bool pol = false;
	vector<int> numInem;
	vector<int> numPolicias;
	vector<int> numBombeiros;


	for (unsigned int i = 0; i < INEM.size(); i++) {
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

/*
vector<Freguesia> Emergencia::getFreguesias(){
	return freguesias;
}

*/
