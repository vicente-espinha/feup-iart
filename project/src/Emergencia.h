
/*
 * Emergencia.h
 *
 *  Created on: 28/03/2017
 *      Author: Carlos Freitas
 */


#ifndef SRC_EMERGENCIA_H_
#define SRC_EMERGENCIA_H_

#include <vector>
#include "Veiculo.h"
#include "No.h"
#include <sstream>
#include <stdio.h>
#include <iostream>
#include "graphviewer.h"
#include "Graph.h"
#include "Rua.h"
#include "Resgate.h"
#include <math.h>
#include <fstream>
#include <map>
#include <algorithm>
#include "utils.h"
#include "StringSearch.h"
#include <ratio>
#include <chrono>
#include <ctime>
#include <iostream>

using namespace std::chrono;

class Emergencia {

private:
	vector<Veiculo> INEM;
	vector<Rua> ruas;
	vector<No> hospitais;
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
	 * Existe o ficheiro de nos que representa todos os nos do graph que nao representa nenhum local de grande importancia
	 * Existe o ficheiro de arestas que representa todas as arestas do grafo, e os nos que de entrada e saida de cada aresta
	 * Existe o ficheiro de hospitais que representam os nos onde se encontram hospitais. Cada hospital e guardado no vetor hospitais
	 * Existe o ficheiros de INEMS que representa os nos onde se encontram as ambulancias. Cada ambulancia e guardada no vetor INEM
	 * Existe o ficheiros de policias que representa os nos onde encontram policias. Cada policia e guardado no vetor de policias
	 * Existe o ficheiro de bombeiros que representa os nos onde se encontram os bombeiros. Cada bombeiro e guardado no vetor bombeiros do objeto emergencia
	 * Existe o ficheiro de ruas onde e representado o nome da rua e os ids dos nos que a constitui, cada rua e adicionada no vetor ruas do objeto emergencia
	 * Existe o ficheiro de freguesias que representa os nos pertencentes a essa freguesia.
	 */
	void readStreets();

	void readHospitals(string filename);

	void readInem(string filename);

	void readResgate(string filename);

	void readNodes();
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
	 * Pinta as arestas contidas no vetor edgepath com a cor "color" e preenche os respetivos vértices de destino com o icone "icon", dando reset ao vértice de origem.
	 * @param edgepath Vetor que contém as arestas a serem modificadas
	 * @param color com com a qual devem ser pintadas as arestas
	 * @param icon icon que ficará no vértice de destino das arestas pintadas
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

	//vector<string> verificacaoExata(string user_string, string tipo, Freguesia fr);

	bool pesquisaExata(string rua_utilizador,string rua_grafo);

	multimap<int, string> pesquisaAproximada(string rua_utilizador, vector<string> &graph_vector);

	//vector<string> verificacaoAproximada(string string_utilizador, string tipo, Freguesia fr);

	void encontraVeiculos(vector<int> ids);

	//vector<Freguesia> getFreguesias();





};

#endif /* SRC_EMERGENCIA_H_ */
