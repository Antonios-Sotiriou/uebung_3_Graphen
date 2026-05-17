#ifndef GRAPH_H
#define GRAPH_H

#include "headers/structs.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Edge {
	std::string to;
	int weight;
	std::string line;

};

class Graph {

public:
	// Adjazenzliste
	std::unordered_map<std::string, std::vector<Edge>> adj;

	//adding bidirectional
	void addEdge(const std::string& from, const std::string& to, int weight, const std::string& line);

	//check if station exists
	bool hasNode(const std::string& station) const;
};
#endif // !GRAPH_H
