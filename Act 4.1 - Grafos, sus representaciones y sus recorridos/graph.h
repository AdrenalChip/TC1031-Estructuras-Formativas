
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
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;


class Graph {
private:
		int edgesList;
		int edgesMat;
		int nodes;
    vector<int> *adjList;
		int *adjMatrix;
		//vector<Type> *vect = new vector<Type>

public:
		void loadGraphMat(string, int, int);
		Graph(int);
		Graph();
		void addEdgeAdjMatrix(int, int);
		void addEdgeAdjList(int,int);
		string printAdjMat();
		string printAdjMat_clean();
		string printAdjList();
		void DFS(int,int);
		void DFH(int current,int goal,stack<int> &st,list<int> &visited,vector<vector<int>> &paths);
		void BFS (int,int);
		void BFH(int current,int goal,queue<int> &qu,list<int> &visited,vector<vector<int>> &paths);
		void print_visited(list<int> q); //NECESITO QUE IMPRIMA
		void print_path(vector<vector <int>> &path, int start, int goal);//guardar en auxstream;
		bool contains(list<int>, int);
		void sortAdjList();
		void loadGraphList(string name,int,int);

};

void Graph::loadGraphList(string name,int a,int b){ ///EL ciclo se aplica mas veces
	adjList=new vector<int>[a];
	nodes=a;
	for (int i=0;i< a-1;i++){
		string line;
		ifstream lee(name);   
		int u,v;
		if (lee.is_open()){
			while(getline(lee,line)){
				u=stoi(line.substr(1,1));
				v=stoi(line.substr(4,1));
				addEdgeAdjList(u,v);
			}
			lee.close();
		}else{
			cout<<"Unable to open file";
		}
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
	edgesList = edgesMat = 0;
}

Graph::Graph(int n) {
	nodes = n;
	adjList = new vector<int>[nodes];
	adjMatrix = new int [nodes*nodes];
	for (int i = 0; i < nodes*nodes; i++)
		adjMatrix[i] = 0;
	edgesList = edgesMat = 0;
}

void Graph::addEdgeAdjList(int u,int v){
	adjList[u].push_back(v);
    adjList[v].push_back(u);
	edgesList++;
}

void Graph::addEdgeAdjMatrix(int u, int v){
	adjMatrix[u*nodes+v] = 1;
	adjMatrix[v*nodes+u] = 1;
	edgesMat++;
}

string Graph::printAdjList(){
	  stringstream aux;
	  for (int i = 0; i < nodes; i++){
		sort(adjList[i].begin(),adjList[i].end());
	}
		for (int i = 0; i < nodes; i++){
	        aux << "vertex "
	             << i << " :";
	        for (int j = 0; j < adjList[i].size(); j ++){
				aux << adjList[i][j] << " ";
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

void Graph::DFS(int start,int goal){
		stack <int> st;
		list <int> visited;
		vector <vector<int>> paths(nodes, vector<int>(1, -1));
		st.push(start);
		DFH(start, goal, st, visited, paths);
		print_path(paths, start, goal);
}
void Graph::DFH(int current,int goal,stack<int> &st,list<int> &visited,vector<vector<int>> &paths){
		if(current == goal){
			print_visited(visited);
		} else if(st.empty()){
			cout << " node not found";
		}	else {
			current = st.top();
			st.pop();
			visited.push_back(current);
			for(int  i = 0; i < adjList[current].size(); i++)
				if(!contains(visited, adjList[current][i])){
					st.push(adjList[current][i]);
					paths[adjList[current][i]][0] = current;
				}
			DFH(current, goal, st, visited, paths);
		}
}

void Graph::BFS(int start,int goal){
	queue <int> qu;
		list <int> visited;
    vector <vector<int>> paths(nodes, vector<int>(0));
		qu.push(start);
 		BFH(start, goal, qu, visited, paths);
		print_path(paths, start, goal);
}

void Graph::BFH(int current,int goal,queue<int> &qu,list<int> &visited,vector<vector<int>> &paths){

		if(current == goal){
			print_visited(visited);
		} else if(qu.empty()){
			cout << " node not found";
		}	else {
			current = qu.front();
			qu.pop();
			visited.push_back(current);
			for(int  i = 0; i < adjList[current].size(); i++)
				if(!contains(visited, adjList[current][i])){
					qu.push(adjList[current][i]);
					paths[adjList[current][i]].push_back(current);
				}
			BFH(current, goal, qu, visited, paths);
		}
}

void Graph::print_visited(list<int> q){
	cout << "visited: ";
	while (!q.empty()){
    cout << q.front() << " ";
    q.pop_front();
  }
  cout << endl;
}

bool Graph::contains(list<int> ls, int node){
		list<int>::iterator it;
		it = find(ls.begin(), ls.end(), node);
		if(it != ls.end())
			return true;
		else
			return false;
}

void Graph::print_path(vector<vector <int>> &path, int start, int goal){
	int node =  path[goal][0];
	stack<int> reverse;
	reverse.push(goal);
	cout << "path: ";
	while (node != start) {
		reverse.push(node);
    node = path[node][0];
  }
	reverse.push(start);
	while (!reverse.empty()) {
		cout << reverse.top() << " ";
		reverse.pop();
  }
  cout << endl;
}
#endif /* Graph_H_ */
