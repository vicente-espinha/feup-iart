/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <climits>
#include <cstddef>
#include <iostream>
#include <math.h>
#include <stack>
#include "Path.h"
#include "Veiculo.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;

const int NOT_VISITED = 0;
const int BEING_VISITED = 1;
const int DONE_VISITED = 2;
const int INT_INFINITY = INT_MAX;

/*
 * Class Vertex
 */
template <class T>
class Vertex {
	T info;
	vector<Edge<T>  > adj;
	int vectorPos;
	bool visited;
	bool processing;
	float heuristic;
	float accCost;
	void addEdge(int idAresta, Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);

	//folha pratica 5
	int indegree;
	int dist;
public:
	Vertex(T in);
	friend class Graph<T>;
	T getInfo() const;
	int getIndegree() const;
	vector< Edge<T> > getAdj();
	int getDist() const;
	int getVectorPos() const;
	Vertex* path;

};

template <class T>
struct vertex_greater_than {
    bool operator()(Vertex<T> * a, Vertex<T> * b) const {
        return a->getDist() > b->getDist();
    }
};

template <class T>
vector< Edge<T> >Vertex<T>::getAdj()
{
	return adj;
}

template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	d->indegree--; //adicionado do exercicio 5
	typename vector<Edge<T> >::iterator it= adj.begin();
	typename vector<Edge<T> >::iterator ite= adj.end();
	while (it!=ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}

//atualizado pelo exercicio 5
template <class T>
Vertex<T>::Vertex(T in): info(in), visited(false), processing(false), indegree(0), dist(0) {
	path = NULL;
}


template <class T>
void Vertex<T>::addEdge(int idAresta, Vertex<T> *dest, double w) {
	Edge<T> edgeD(idAresta, dest,w);
	adj.push_back(edgeD);

}


template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
int Vertex<T>::getIndegree() const {
	return this->indegree;
}

template <class T>
int Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
int Vertex<T>::getVectorPos() const{

	return vectorPos;
}

/*
 * Class Edge
 */
template <class T>
class Edge {
	Vertex<T> * dest;
	double weight;
	int ID;
public:
	Edge(Vertex<T> *d, double w);
	Edge(int ID, Vertex<T> *d, double w);
	int getID();
	Vertex<T>* getDest();
	friend class Graph<T>;
	friend class Vertex<T>;
	double getWeight();
};

template <class T>
Edge<T>::Edge(int ID,Vertex<T> *d, double w): ID(ID), dest(d), weight(w){}

/*template <class T>
Edge<T>::Edge(Vertex<T> *d, double w):dest(d), weight(w){}*/


template<class T>
int Edge<T>::getID()
{
	return ID;
}

template <class T>
double Edge<T>::getWeight()
{
	return weight;
}
template<class T>
Vertex<T> * Edge<T>::getDest()
{
	return dest;
}


/*
 * Class Graph
 */
template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;


	//Exercicio 5
	int numCycles;
	void dfsVisit(Vertex<T> *v);
	void dfsVisit();
	void getPathTo(Vertex<T> *origin, list<T> &res);

	//exercicio 6
		int ** W;   //weight
		int ** P;   //path
public:
	void dfs(Vertex<T> *v, vector<T> &res) const;
	bool addVertex(const T &in);
	bool addEdge(int idAresta, const T &sourc, const T &dest, double w);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> posdfs(bool resetVisited);
	Graph<T> getTranspose();
	void fillOrder(int v, bool visited[], stack<int> &Stack);
	bool stronglyConnectedComponents();
	vector<T> bfs(Vertex<T> *v) const;
	int maxNewChildren(Vertex<T> *v, T &inf) const;
	vector<Vertex<T> * > getVertexSet() const;
	int getNumVertex() const;

	Vertex<T>* getVertex(const T &v) const;
	void resetIndegrees();
	vector<Vertex<T>*> getSources() const;
	int getNumCycles();
	bool isDAG();
	vector<T> topologicalOrder();
	Path getPath(const T &origin, const T &dest);
	vector <T> getResourcesToPath(const T &origin, const T &dest,vector<Edge<T> > &EdgestoPaint);

	void unweightedShortestPath(const T &v);
	void bellmanFordShortestPath(const T &s);
	void dijkstraShortestPath(const T &s);
	void floydWarshallShortestPath();
	int getfloydWarshallweight(int vOrigIndex, int vDestIndex);
	int edgeCost(int vOrigIndex, int vDestIndex);
	vector<T> getfloydWarshallPath(const T &origin, const T &dest);
	void getfloydWarshallPathAux(int index1, int index2, vector<T> & res);
	vector< Edge<T> > getEdges(vector<T> nodes);
	void aStarPath(const T &init, const T &final);
	void aStarPathComplex(const T &init, const T &final, const Veiculo &vehicle);


};


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}
template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
	return vertexSet;
}

template <class T>
bool Graph<T>::addVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++)
		if ((*it)->info == in) return false;
	Vertex<T> *v1 = new Vertex<T>(in);
	if(vertexSet.size() > 0)
		(*v1).vectorPos = vertexSet.size();
	else
		(*v1).vectorPos = 0;
	vertexSet.push_back(v1);
	return true;
}

template <class T>
bool Graph<T>::removeVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++) {
		if ((*it)->info == in) { //se encontrar
			Vertex<T> * v= *it;  //guarda temporario
			vertexSet.erase(it); //apaga
			typename vector<Vertex<T>*>::iterator it1= vertexSet.begin();
			typename vector<Vertex<T>*>::iterator it1e= vertexSet.end();
			for (; it1!=it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}
			// decrementa indegree para arestas que se iniciam em "v"
			typename vector<Edge<T> >::iterator itAdj= v->adj.begin();
			typename vector<Edge<T> >::iterator itAdje= v->adj.end();
			for (; itAdj!=itAdje; itAdj++) {
				itAdj->dest->indegree--;
			}
			delete v;
			return true;
		}
	}
	return false;
}

template <class T>
bool Graph<T>::addEdge(int idAresta, const T &sourc, const T &dest, double w) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
			{ vS=*it; found++;}
		if ( (*it)->info == dest )
			{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	vD->indegree++; //adicionado pelo exercicio 5
	vS->addEdge(idAresta, vD,w);
	return true;
}

template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
			{ vS=*it; found++;}
		if ( (*it)->info == dest )
			{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;

	//adicionado pelo exercicio 5
	return vS->removeEdgeTo(vD);
}




template <class T>
vector<T> Graph<T>::dfs() const {
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	vector<T> res;
	it=vertexSet.begin();
	for (; it !=ite; it++)
	    if ( (*it)->visited==false )
	    	dfs(*it,res);
	return res;
}

template <class T>
void Graph<T>::dfs(Vertex<T> *v,vector<T> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge<T> >::iterator it= (v->adj).begin();
	typename vector<Edge<T> >::iterator ite= (v->adj).end();
	for (; it !=ite; it++)
	    if ( it->dest->visited == false){
	    	dfs(it->dest, res);
	    }
}

template<class T>
vector<T> Graph<T>::posdfs(bool resetVisited)
{
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();

	if(resetVisited)
	{
		for(;it != ite ; it++)
		{
			(*it)->visited = false;
		}
	}

	vector<T> res;
	it = vertexSet.begin();
	ite = --vertexSet.end();
	for(; ite >= it; ite--)
	{
		if((*ite)->visited == false)
		{
			dfs(*ite,res);
		}
	}
	return res;

}
template<class T>
Graph<T> Graph<T>::getTranspose()
{
	Graph res;
	vector<Vertex<T> *>  aux = vertexSet;
	int aresta_nr=0;
	for(unsigned int i = 0; i < aux.size();i++)
	{
		for(unsigned int j = 0; j < aux.at(i)->adj.size(); j++)
		{

				Vertex<T> * vO = aux.at(i);
				Edge<T> ed = vO->adj.at(j);
				Vertex<T>* vd = ed.getDest();
				res.addVertex(vO->getInfo());
				res.addVertex(vd->getInfo());
				res.addEdge(aresta_nr,vd->getInfo(), vO->getInfo(), ed.weight);
				aresta_nr++;
		}
	}
	return res;
}



template <class T>
bool Graph<T>::stronglyConnectedComponents(){

		vector<T> graphPosDFS= this->posdfs(true);
		Graph<T> Gr = getTranspose();
		vector<T> GrPosDFS;
		typename vector<Vertex<T>*>::const_iterator it= Gr.vertexSet.begin();
			typename vector<Vertex<T>*>::const_iterator ite= Gr.vertexSet.end();

				for(;it != ite ; it++)
				{
					(*it)->visited = false;
				}
		Gr.dfs(Gr.getVertex(graphPosDFS.at(graphPosDFS.size()-1)), GrPosDFS);
		if(graphPosDFS.size() == GrPosDFS.size())
			return true;
		else
			return false;

}

template <class T>
vector<T> Graph<T>::bfs(Vertex<T> *v) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
			}
		}
	}
	return res;
}

template <class T>
int Graph<T>::maxNewChildren(Vertex<T> *v, T &inf) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	queue<int> level;
	int maxChildren=0;
	inf =v->info;
	q.push(v);
	level.push(0);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		int l=level.front();
		level.pop(); l++;
		int nChildren=0;
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
				level.push(l);
				nChildren++;
			}
		}
		if (nChildren>maxChildren) {
			maxChildren=nChildren;
			inf = v1->info;
		}
	}
	return maxChildren;
}

//****
template <class T>
Vertex<T>* Graph<T>::getVertex(const T &v) const {
	for(unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == v) return vertexSet[i];
	return NULL;
}

template<class T>
void Graph<T>::resetIndegrees() {
	//colocar todos os indegree em 0;
	for(unsigned int i = 0; i < vertexSet.size(); i++) vertexSet[i]->indegree = 0;

	//actualizar os indegree
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		//percorrer o vetor de Edges, e atualizar indegree
		for(unsigned int j = 0; j < vertexSet[i]->adj.size(); j++) {
			vertexSet[i]->adj[j].dest->indegree++;
		}
	}
}


template<class T>
vector<Vertex<T>*> Graph<T>::getSources() const {
	vector< Vertex<T>* > buffer;
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		if( vertexSet[i]->indegree == 0 ) buffer.push_back( vertexSet[i] );
	}
	return buffer;
}


template <class T>
int Graph<T>::getNumCycles() {
	numCycles = 0;
	dfsVisit();
	return this->numCycles;
}

template <class T>
bool Graph<T>::isDAG() {
	if (getNumCycles() == 0) return true;
	return false;
}

template <class T>
void Graph<T>::dfsVisit() {
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	it=vertexSet.begin();
	for (; it !=ite; it++)
	    if ( (*it)->visited==false ){
	    	cout << "Being visited" << endl;
	    	dfsVisit(*it);
	    }
}

template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v) {
	v->processing=true;
	v->visited = true;
	typename vector<Edge<T> >::iterator it= (v->adj).begin();
	typename vector<Edge<T> >::iterator ite= (v->adj).end();
	for (; it !=ite; it++) {
		if ( it->dest->processing == true) numCycles++;
	    if ( it->dest->visited == false ){
	    	dfsVisit(it->dest);
	    }
	}
	v->processing=false;
}

template<class T>
vector<T> Graph<T>::topologicalOrder() {
	//vetor com o resultado da ordenacao
	vector<T> res;

	//verificar se ee um DAG
	if( getNumCycles() > 0 ) {
		cout << "Ordenacao Impossivel!" << endl;
		return res;
	}

	//garantir que os "indegree" estao inicializados corretamente
	this->resetIndegrees();

	queue<Vertex<T>*> q;

	vector<Vertex<T>*> sources = getSources();
	while( !sources.empty() ) {
		q.push( sources.back() );
		sources.pop_back();
	}

	//processar fontes
	while( !q.empty() ) {
		Vertex<T>* v = q.front();
		q.pop();

		res.push_back(v->info);

		for(unsigned int i = 0; i < v->adj.size(); i++) {
			v->adj[i].dest->indegree--;
			if( v->adj[i].dest->indegree == 0) q.push( v->adj[i].dest );
		}
	}

	//testar se o procedimento foi bem sucedido
	if ( res.size() != vertexSet.size() ) {
		while( !res.empty() ) res.pop_back();
	}

	//garantir que os "indegree" ficam atualizados no final
	this->resetIndegrees();

	return res;
}

template<class T>
void Graph<T>::unweightedShortestPath(const T &s) {

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;
	queue< Vertex<T>* > q;
	q.push(v);

	while( !q.empty() ) {
		v = q.front(); q.pop();
		for(unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;
			if( w->dist == INT_INFINITY ) {
				w->dist = v->dist + 1;
				w->path = v;
				q.push(w);
			}
		}
	}

}

template<class T>
void Graph<T>::getPathTo(Vertex<T> *dest, list<T> &res) {
	res.push_back(dest->info);
	if( dest->path != NULL )
		getPathTo(dest->path, res);

}

template<class T>
Path Graph<T>::getPath(const T &origin, const T &dest){


	list<T*> buffer;
	Vertex<T>* v = getVertex(dest);
	float final_dist = v->getDist();

	vector< Edge<T> > edges;

	buffer.push_front(&v->info);
	while (! (v->path->info == origin )) {

		v = v->path;
		buffer.push_front(&v->info);
	}

	buffer.push_front(&v->path->info);
	vector<T*> res;
	while( !buffer.empty() ) {
		res.push_back( buffer.front() );
		buffer.pop_front();
	}
	Path path = Path(res, final_dist);
	return path;
}

template<class T>
vector<T> Graph<T>::getResourcesToPath(const T &origin, const T &dest,vector<Edge<T> > &EdgestoPaint)
{
	dijkstraShortestPath(origin);
	 //return getPath(origin,dest,EdgestoPaint);
}

template <class T>
int Graph<T>::getfloydWarshallweight(int vOrigIndex, int vDestIndex){
	return W[vOrigIndex][vDestIndex];

}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &origin, const T &dest){

	int originIndex = -1, destinationIndex = -1;

	for(unsigned int i = 0; i < vertexSet.size(); i++)
	{
		if(vertexSet[i]->info == origin)
			originIndex = i;
		if(vertexSet[i]->info == dest)
			destinationIndex = i;

		if(originIndex != -1 && destinationIndex != -1)
			break;
	}


	vector<T> res;

	//se nao foi encontrada solucao possivel, retorna lista vazia
	if(W[originIndex][destinationIndex] == INT_INFINITY)
		return res;

	res.push_back(vertexSet[originIndex]->info);

	//se houver pontos intermedios...
	if(P[originIndex][destinationIndex] != -1)
	{
		int intermedIndex = P[originIndex][destinationIndex];

		getfloydWarshallPathAux(originIndex, intermedIndex, res);

		res.push_back(vertexSet[intermedIndex]->info);

		getfloydWarshallPathAux(intermedIndex,destinationIndex, res);
	}

	res.push_back(vertexSet[destinationIndex]->info);


	return res;
}



template<class T>
void Graph<T>::getfloydWarshallPathAux(int index1, int index2, vector<T> & res)
{
	if(P[index1][index2] != -1)
	{
		getfloydWarshallPathAux(index1, P[index1][index2], res);

		res.push_back(vertexSet[P[index1][index2]]->info);

		getfloydWarshallPathAux(P[index1][index2],index2, res);
	}
}




template<class T>
void Graph<T>::bellmanFordShortestPath(const T &s) {

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;
	queue< Vertex<T>* > q;
	q.push(v);

	while( !q.empty() ) {
		v = q.front(); q.pop();
		for(unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;
			if(v->dist + v->adj[i].weight < w->dist) {
				w->dist = v->dist + v->adj[i].weight;
				w->path = v;
				q.push(w);
			}
		}
	}
}





template<class T>
void Graph<T>::dijkstraShortestPath(const T &s) {

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
		vertexSet[i]->processing = false;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;

	vector< Vertex<T>* > pq;
	pq.push_back(v);

	make_heap(pq.begin(), pq.end());


	while( !pq.empty() ) {

		v = pq.front();
		pop_heap(pq.begin(), pq.end());
		pq.pop_back();

		for(unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;

			if(v->dist + v->adj[i].weight < w->dist ) {

				w->dist = v->dist + v->adj[i].weight;
				w->path = v;

				//se já estiver na lista, apenas a actualiza
				if(!w->processing)
				{
					w->processing = true;
					pq.push_back(w);
				}

				make_heap (pq.begin(),pq.end(),vertex_greater_than<T>());
			}
		}
	}
}

template<class T>
int Graph<T>::edgeCost(int vOrigIndex, int vDestIndex)
{
	if(vertexSet[vOrigIndex] == vertexSet[vDestIndex])
		return 0;

	for(unsigned int i = 0; i < vertexSet[vOrigIndex]->adj.size(); i++)
	{
		if(vertexSet[vOrigIndex]->adj[i].dest == vertexSet[vDestIndex])
			return vertexSet[vOrigIndex]->adj[i].weight;
	}

	return INT_INFINITY;
}





template<class T>
void Graph<T>::floydWarshallShortestPath() {

	W = new int * [vertexSet.size()];
	P = new int * [vertexSet.size()];
	for(unsigned int i = 0; i < vertexSet.size(); i++)
	{
		W[i] = new int[vertexSet.size()];
		P[i] = new int[vertexSet.size()];
		for(unsigned int j = 0; j < vertexSet.size(); j++)
		{
			W[i][j] = edgeCost(i,j);
			P[i][j] = -1;
		}
	}


	for(unsigned int k = 0; k < vertexSet.size(); k++)
		for(unsigned int i = 0; i < vertexSet.size(); i++)
			for(unsigned int j = 0; j < vertexSet.size(); j++)
			{
				//se somarmos qualquer coisa ao valor INT_INFINITY, ocorre overflow, o que resulta num valor negativo, logo nem convém considerar essa soma
				if(W[i][k] == INT_INFINITY || W[k][j] == INT_INFINITY)
					continue;

				int val = min ( W[i][j], W[i][k]+W[k][j] );
				if(val != W[i][j])
				{
					W[i][j] = val;
					P[i][j] = k;
				}
			}

}


template <class T>
vector< Edge<T> > Graph<T>::getEdges(vector<T> nodes){

	vector< Edge<T> > edges;
	for(unsigned int i=0; i<nodes.size()-1; i++)
	{
		vector< Edge<T> > adjs = getVertex(nodes[i])->adj;

		for(unsigned int j=0; j<adjs.size(); j++){
			if(adjs[j].dest->info == nodes[i+1]){

				edges.push_back(adjs[j]);
				break;
			}
				
		}
	}
	return edges;
}


template<class T>
void Graph<T>::aStarPath(const T &init, const T &final) {

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
		vertexSet[i]->processing = false;
	}

	Vertex<T>* vinit = getVertex(init);
	Vertex<T>* vfinal = getVertex(final);

	int distX = pow((vinit->info.getX() - vfinal->info.getX()), 2);
	int distY = pow((vinit->info.getY() - vfinal->info.getY()), 2);
	vinit->heuristic = sqrt(distX + distY);

	vinit->dist = 0;

	vector< Vertex<T>* > pq;
	pq.push_back(vinit);

	make_heap(pq.begin(), pq.end());

	Vertex<T>* v;
	while( !pq.empty() ) {

		v = pq.front();
		pop_heap(pq.begin(), pq.end());
		pq.pop_back();

		for(unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;
			//v->adj[i].setVisited(true);

			distX = pow((vfinal->info.getX() - w->info.getX()), 2);
			distY = pow((vfinal->info.getY() - w->info.getY()), 2);
			w->heuristic = sqrt(distX + distY);

			if((v->dist + v->adj[i].weight + v->heuristic) < w->dist ) {

				w->dist = v->dist + v->adj[i].weight;
				w->path = v;

				//se já estiver na lista, apenas a actualiza
				if(!w->processing)
				{
					w->processing = true;
					pq.push_back(w);
				}

				make_heap (pq.begin(),pq.end(),vertex_greater_than<T>());
			}
		}
	}
}

template<class T>
void Graph<T>::aStarPathComplex(const T &init, const T &final,const Veiculo &vehicle){
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
			vertexSet[i]->path = NULL;
			vertexSet[i]->dist = INT_INFINITY;
			vertexSet[i]->processing = false;
		}

		Vertex<T>* vinit = getVertex(init);
		Vertex<T>* vfinal = getVertex(final);

		int distX = pow((vinit->info.getX() - vfinal->info.getX()), 2);
		int distY = pow((vinit->info.getY() - vfinal->info.getY()), 2);
		vinit->heuristic = sqrt(distX + distY);

		vinit->dist = 0;

		vector< Vertex<T>* > pq;
		pq.push_back(vinit);

		make_heap(pq.begin(), pq.end());

		Vertex<T>* v;
		while( !pq.empty() ) {

			v = pq.front();
			pop_heap(pq.begin(), pq.end());
			pq.pop_back();

			for(unsigned int i = 0; i < v->adj.size(); i++) {
				Vertex<T>* w = v->adj[i].dest;
				//v->adj[i].setVisited(true);



				distX = pow((vfinal->info.getX() - w->info.getX()), 2);
				distY = pow((vfinal->info.getY() - w->info.getY()), 2);
				float distance = sqrt(distX + distY);
				float capacity = vehicle->getCapacity();

				if(

				w->heuristic = ;

				if((v->dist + v->adj[i].weight + v->heuristic) < w->dist ) {

					w->dist = v->dist + v->adj[i].weight;
					w->path = v;

					//se já estiver na lista, apenas a actualiza
					if(!w->processing)
					{
						w->processing = true;
						pq.push_back(w);
					}

					make_heap (pq.begin(),pq.end(),vertex_greater_than<T>());
				}
			}
		}

}


#endif /* GRAPH_H_ */

