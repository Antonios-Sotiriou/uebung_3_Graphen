#include "headers/graph.h"

void Graph::addEdge(const std::string& from, const std::string& to, int weight, const std::string& line) {
	adj[from].push_back({ to,weight,line });
	adj[to].push_back({ from,weight,line });
}

bool Graph::hasNode(const std::string& station) const {
	return adj.find(station) != adj.end();
}
