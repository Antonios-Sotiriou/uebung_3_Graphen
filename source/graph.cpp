#include "headers/graph.h"
//#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

//#error "graph.cpp wird kompiliert"


//adding bidirectional
void Graph::addEdge(const std::string& from, const std::string& to, int weight, const std::string& line) {
	adj[from].push_back({ to,weight,line });
	adj[to].push_back({ from,weight,line });
}

//check if station exists
bool Graph::hasNode(const std::string& station) const {
	return adj.find(station) != adj.end();
}



