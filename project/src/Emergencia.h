
/*
 * Emergencia.h
 *
 *  Created on: 28/03/2017
 *      Author: Carlos Freitas
 */


#ifndef SRC_EMERGENCIA_H_
#define SRC_EMERGENCIA_H_

#include <vector>
#include "No.h"
#include <sstream>
#include <stdio.h>
#include <iostream>
#include "graphviewer.h"
#include "Graph.h"
#include "Rua.h"
#include "Resgate.h"
#include "Hospital.h"
#include <math.h>
#include <fstream>
#include <map>
#include <algorithm>
#include <ratio>
#include <chrono>
#include <ctime>
#include <iostream>

using namespace std::chrono;

class Emergencia {

private:
	vector<Veiculo> INEM;
	vector<Rua> ruas;
	Hospital hospital;
	vector<Resgate> resgates;
	Graph<No> myGraph;
	GraphViewer *gv;
	int ID_ARESTA_GERAL;
	system_clock::time_point tempoinicial=system_clock::now();
	system_clock::time_point  tempofinal=system_clock::now();

public:
	/**
	 *Construtor de um objeto Emergencia, em que inicializa o GraphViewer por defeito, e todos as variaveis de contagem de tempo a zero
	 *@param FloydWarshall booleano que diz se o objeto do tipo Emergencia usa o algoritmo de Floyd-Warshall(se for dado true) ou  de Dijkstra (se o parametro dado for false)
	 */
	Emergencia(bool FloydWarshall);
	/**
	 * Funcao que le os ficheiros txts que representam as arestas,os nos e as ruas do grafo myGraph que e preenchido a medida que os ficheiros sao lidos
	 * Existe o ficheiro de arestas que representa todas as arestas do grafo, e os nos que de entrada e saida de cada aresta
	 * Existe o ficheiro de ruas onde e representado o nome da rua e os ids dos nos que a constitui, cada rua e adicionada no vetor ruas do objeto emergencia
	 */
	void readStreets();

	/*
	 * Funcao que le o ficheiro de hospitais que representam os nos onde se encontram hospitais. Cada hospital e guardado no vetor hospitais
	 * @param filename ->nome do ficheiro que contem a informa��o sobre os hospitais
	 */
	void readHospitals(string filename);

	/*
	 * Funcao que le o ficheiro de INEMS que representa os nos onde se encontram as ambulancias. Cada ambulancia e guardada no vetor INEM
	 *  @param filename ->nome do ficheiro que contem a informa��o sobre os INEM
	 */
	void readInem(string filename);

	/*
	 * Funcao que le o ficheiro de Resgates que representa os nos onde se encontram os porntos a evacuar. Cada Resgate guardado no vetor
	 *  @param filename ->nome do ficheiro que contem a informa��o sobre os pontos de Resgates
	 */
	void readResgate(string filename);

	/**
	 *  Funcao que le o ficheiro de nos que representa todos os nos do graph que nao representa nenhum local de grande importancia
	 */
	void readNodes();

	void pre_process();

	Path path_vehicle(Veiculo * vehicle);

	vector<Path> calc_dist_rescues(Veiculo veiculo);

	Veiculo* ambulance_selection();
	/**
	 * Com o id, e com o numero de cada tipo de veiculo a ser chamada, esta funcao calcula quais os melhores veiculos a acionar
	 * e qual o caminho que estes irao percorrer
	 * @param noID identicador do no de onde e feita  a chamada(ou seja para onde os veiculos se irao dirigir
	 * @param polFlag numero de carros de policias a serem chamados
	 * @param bombFlag numero de carros de bombeiros a serem chamados
	 * @param inemFlag numero de carros do INEM a serem chamados
	 * @param gotoHospital flag que indica se e necessario uma ambulancia apos chegar ao local ter de ir para o hospital mais perto.
	 *
	 */
	void getCall(int noID,int polFlag,int bombFlag,int inemFlag, bool gotoHospital);
	/**
	 * Cria a partir do Grafo myGraph uma representacao visual do mesmo atraves do GraphViewer
	 */
	void displayGraph();
	/**
	 * Destrutor de Emergencia
	 */
	virtual ~Emergencia();
	/**
	 * Retorna o Vertex do myGraph que contem o No com o id dado como parametro
	 * @param id ID do No a procurar
	 * @return apontador para o vertex do respetivo No no myGraph
	 */
	Vertex<No>* findNo(int id);
	/**
	 * Funcao que retorna o No onde se encontra o tipo de veiculo especificado como parametro mais perto da localizacao dada
	 * @param localizacao local a comparar onde se encontra o veiculo mais perto
	 * @param pathnodes vetor onde e guardado os Nos que representam o percurso desse veiculo ao local dado como parametro
	 * @param elementType carater que representa o tipo de veiculo a encontrar('B'-bombeiros,'I'-INEM,'P'-policia)
	 * @return o no do local onde se encontra o veiculo mais perto
	 */
	No findElement(Vertex<No>* localizacao, vector<No> &pathnodes, char elementType);
	/**
	 *Funcao que representa o movimento da ambulancia do local de socorro dado como argumento ao hospital mais perto
	 *@param localizacao local de onde a ambulancia parte
	 *@return retorna um vetor de arestas que representam o percurso da ambulancia ate ao hospital mais perto
	 */
	vector<Edge<No> > moveToHospital(Vertex<No>* localizacao);
	/**
	 * Apos ser demonstrado  percurso no GraphViewer feito por um veiculo e preciso atualizar o estado dos Nos do mesmo e voltar a meter as arestas
	 * como se encontravam originalmente
	 */
	void resetGV();
	/**
	 * Pinta as arestas contidas no vetor edgepath com a cor "color" e preenche os respetivos v�rtices de destino com o icone "icon", dando reset ao v�rtice de origem.
	 * @param edgepath Vetor que cont�m as arestas a serem modificadas
	 * @param color com com a qual devem ser pintadas as arestas
	 * @param icon icon que ficar� no v�rtice de destino das arestas pintadas
	 */
	void drawPath(vector<Edge<No> > &edgepath,string color,string icon);
	/**
	 * Pinta cada No do grafo do graphViewer com o respetivo icone que representa cada local de forma
	 * percetivel
	 */
	void colorNodes();
	/**
	 * Atribui o valor a variavel FloydWarshall para que durante o processo de verificacao de caminhos seja possivel saber qual o algoritmo que o utilizador selecionou
	 * @param value Verdadeiro se foi escolhido utilizar este algoritmo e false caso nao tenha sido.
	 */
	void setFloydWarshall(bool value);
	/**
	 * Retorna um vetor das ruas existentes no mapa
	 * @return Vetor que contem as ruas
	 */
	vector<Rua> getRuas();
	/**
	 * Desenha em cada aresta do grafo representado no graphviewer o nome da rua a que pertence
	 */
	void writeRuas();


	/**
	 * A funcao que verifica a conetividade do grafo
	 */
	bool verificarConetividade();

	void encontraVeiculos(vector<int> ids);

	vector<float> calc_percentage(vector<float> raw_values);





};

#endif /* SRC_EMERGENCIA_H_ */
