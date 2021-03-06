#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>    // std::sort

using namespace std;


class Graph {
private:
		int edgesList;
		int edgesMat;
		int nodes;
    	vector<int> *adjList;
		int *adjMatrix;

public:
		void loadGraphList(string,int,int);
		void loadGraphMat(string, int, int);
		Graph(int);
		Graph();
		void addEdgeAdjMatrix(int, int);
		void addEdgeAdjList(int, int);
		string printAdjMat();
		string printAdjMat_clean();
		string printAdjList();
		string DFS(int,int);
		void DFH(int,int,stack<int>&,list<int>&,vector<vector<int>>&);
		bool contains(list<int>, int);
		string print_path(vector<vector <int>>&,int,int);
		string print_visited(list<int>);
		string BFS(int,int);
		void BFH(int,int,queue<int>&,list<int>&,vector<vector<int>>&);
};

	string Graph::DFS(int init,int final){
		string s;
		stack<int> st;				
		list<int> visited;
		vector<vector<int>> caminos(nodes,vector<int>(1, -1));
		st.push(init);
		DFH(init, final, st, visited, caminos);
		s=print_visited(visited)+print_path(caminos,init,final);
		return s;
	}

void Graph::DFH(int current,int goal,stack<int> &st,list<int> &visited,vector<vector<int>> &paths){//
	if(current == goal){
	} else if(st.empty()){
		cout << "Nodo no encontrado";
	}	
	else {
		current = st.top();
		st.pop();
		visited.push_back(current);
		for(int  i = 0; i < adjList[current].size(); i++){
			if(!contains(visited, adjList[current][i])){
				st.push(adjList[current][i]);
				paths[adjList[current][i]][0] = current;
			}
		}
		DFH(current, goal, st, visited, paths);
	}
}

bool Graph::contains(list<int> ls, int node){
		list<int>::iterator it;
		it = find(ls.begin(), ls.end(), node);
		if(it != ls.end()){
			return true;
		}
		else{
			return false;
		}
}

string Graph::print_visited(list<int> q){
	string s;
	s=s+"visited: ";
	while (!q.empty()){
    s=s+to_string(q.front())+ " ";
    q.pop_front();
	}
	return s;
}


string Graph::print_path(vector<vector <int>> &path, int start, int goal){
	stringstream s;
	int node =  path[goal][0];
	stack<int> reverse;
	reverse.push(goal);
	while (node != start) {
		reverse.push(node);
    node = path[node][0];
  }
	reverse.push(start);
	while (!reverse.empty()) {
		if(s.tellp() != 0){
			s<<" ";
		}
		s<<to_string(reverse.top());
		reverse.pop();
  }
  return "path: "+s.str();
}


string Graph::BFS(int a,int b){
	string s;
	queue<int> q;
	list<int> visited;
	vector <vector<int>> paths(nodes, vector<int>(0));
	q.push(a);
	BFH(a, b, q, visited, paths);
	s=print_visited(visited)+print_path(paths,a,b);
	return s;
}

void Graph::BFH(int current,int goal,queue<int> &q,list<int> &visited,vector<vector<int>> &paths){//
	if(current == goal){
	} else if(q.empty()){
		cout << "Nodo no encontrado";
	}	
	else {
		current = q.front();
		q.pop();
		visited.push_back(current);
		for(int  i = 0; i < adjList[current].size(); i++){
			if(!contains(visited, adjList[current][i])){
				q.push(adjList[current][i]);
				paths[adjList[current][i]].push_back(current);
			}
		}
		BFH(current, goal, q, visited, paths);
	}
}

void Graph::loadGraphList(string fileName, int numNodes, int maxArcos){
	nodes=numNodes;
	adjList=new vector<int>[numNodes];

	string line;
		ifstream lee (fileName);
		int u, v;
		if (lee.is_open()){
			while (getline(lee, line)){
				u = stoi(line.substr(1,1));
				v = stoi(line.substr(4,1));
				addEdgeAdjList(u,v);
			}
			lee.close();
		} else {
			cout << "Unable to open file";
		}
	for(int i=0;i<nodes;i++){//Falta ordenar uno
		sort(adjList[i].begin(),adjList[i].end());
	}

}

void Graph::loadGraphMat(string name, int a, int b){
	adjMatrix = new int [a*b];
	nodes = a;
	for (int i = 0; i < a*b; i++)
		adjMatrix[i] = 0;
		string line;
		ifstream lee (name);
		int u, v;
		if (lee.is_open()){
			while (getline(lee, line)){
				u = stoi(line.substr(1,1));
				v = stoi(line.substr(4,1));
				addEdgeAdjMatrix(u,v);
			}
			lee.close(); // Closes the file
		} else {
			cout << "Unable to open file";
		}
}

Graph::Graph() {
	nodes = edgesList = edgesMat = 0;
}

Graph::Graph(int n) {
	nodes = n;
	adjList = new vector<int>[nodes];
	adjMatrix = new int [nodes*nodes];
	for (int i = 0; i < nodes*nodes; i++)
		adjMatrix[i] = 0;
	edgesList = edgesMat = 0;
}

void Graph::addEdgeAdjMatrix(int u, int v){ 
	adjMatrix[u*nodes+v] = 1;
	adjMatrix[v*nodes+u] = 1;
	edgesMat++;
}

//Auxiliar para agregar arcos 
void Graph::addEdgeAdjList(int u, int v){
	adjList[u].push_back(v);
	adjList[v].push_back(u);
	edgesList++;
}

string Graph::printAdjList(){
	  stringstream aux;
		for (int i = 0; i < nodes; i++){
	        aux << "vertex "
	             << i << " :";
	        for (int j = 0; j < adjList[i].size(); j ++){
							 aux << " " << adjList[i][j];
					}
	        aux << " ";
    }
		return aux.str();

}

string Graph::printAdjMat(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
	   for (int j = 0; j < nodes; j++){
			 aux << adjMatrix[i*nodes+j] << " ";
		 }
  }
	return aux.str();
}

string Graph::printAdjMat_clean(){
	stringstream aux;
	aux << "\n nodes \t|";
	for (int i = 0; i < nodes; i++){
			aux << "\t" << i ;
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
			aux << "__________";
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
		 aux << i << "\t|";
	   for (int j = 0; j < nodes; j++){
			 aux << "\t" << adjMatrix[i*nodes+j];
		 }
	   aux << "\n";
  }
	return aux.str();
}

#endif /* Graph_H_ */