#include "headers/graph.h"

Graph::Graph() {
	adj = {};
}

Graph::~Graph() {}

void Graph::addNode(const std::string& from, const std::string& to, int weight, std::string line_name) {
	if (hasNode(from)) {
		addEdge(from, to, weight, line_name);
	} else {
		createNode(from, to, weight, line_name);
	}
	if (hasNode(to)) {
		addEdge(to, from, weight, line_name);
	} else {
	    createNode(to, from, weight, line_name);
	}
}

void Graph::createNode(const std::string& from, const std::string& to, int weight, std::string line_name) {
	Edge new_edge = { weight, line_name, to };
	Node new_node;
	new_node.name = from;
	new_node.visited = 0;
	new_node.conns.push_back(new_edge);

	adj.insert(std::pair<std::string, Node>(from, new_node));
}

void Graph::addEdge(const std::string& from, const std::string& to, int weight, std::string line_name) {
	Edge new_edge = { weight, line_name, to };
	adj[from].conns.push_back(new_edge);
}

bool Graph::hasNode(const std::string& station) const {
	return adj.find(station) != adj.end();
}

void Graph::findRoute(const std::string& from, const std::string& to) {
	if (adj.find(from) == adj.end()) {
		std::cout << "Start Station not found" << std::endl;
		return;
	}
	Node start_point = adj.at(from);

	if (adj.find(to) == adj.end()) {
		std::cout << "End Station not found" << std::endl;
		return;
	}
	Node end_point = adj.at(to);

	findPath(start_point, end_point);
}

void Graph::findPath(Node& start, Node& end) {
	std::cout << start.name << " ";
	if (start.visited) {
		//std::cout << "Already visited: " << start.name << std::endl;
		return;
	}
	start.visited = 1;

	if (start.name == end.name) {
		std::cout << "  " << end.name << ": Connection found!##########################################" << std::endl;
		return;
	}

	for (auto conn : start.conns) {
		if (conn.next != "") {
			std::cout << start.name << " <-> ";
			findPath(adj.at(conn.next), end);
		}
	}
}

void Graph::printNode(const std::string node_name) {
	if (!hasNode(node_name)) {
		std::cout << "Node not found" << std::endl;
		return;
	}
	Node node = adj.at(node_name);
	std::cout << node.name << " {" << std::endl;
	for (auto conn : node.conns) {
		printEdge(conn);
	}
	std::cout << "}" << std::endl;
}

void Graph::printEdge(const Edge& edge) {
	std::cout << "    " << edge.weight << " -> " << edge.next << "    Line: " << edge.line << std::endl;
}
