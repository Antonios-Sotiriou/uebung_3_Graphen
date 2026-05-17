#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

/* The connection between two stops. Value is the weight for this connection. */
typedef struct Edge {
	int weight;
	std::string line;
	std::string next;
} Edge;

/* A station of the line which can have many connections to other lines. */
typedef struct Node {
	std::string name;
	int visited;
	std::vector<Edge> conns;
} Node;

class Graph {
	public:
		Graph();
		~Graph();

		std::unordered_map<std::string, Node> adj;

		void addNode(const std::string& from, const std::string& to, int weight, std::string line_name);
		void createNode(const std::string& from, const std::string& to, int weight, std::string line_name);
		void addEdge(const std::string& from, const std::string& to, int weight, std::string line_name);

		bool hasNode(const std::string& station) const;

		void findRoute(const std::string& from, const std::string& to);
		void findPath(Node& start, Node& end);

		void printNode(const std::string node_name);
		void printEdge(const Edge &edge);
};
#endif // !GRAPH_H
