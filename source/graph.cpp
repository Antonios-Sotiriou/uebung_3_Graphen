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
	start_node = adj.at(from);

	if (adj.find(to) == adj.end()) {
		std::cout << "End Station not found" << std::endl;
		return;
	}
	end_node = adj.at(to);

	findPath(start_node, end_node);
	printPath();
}

int Graph::findPath(Node& start, Node& end) {
	path.push_back(start);
	if (start.name == end.name) {
		//std::cout << "  " << end.name << ": Connection found!" << std::endl;
		return 1;
	}

	if (start.visited == start.conns.size()) {
		//std::cout << "Already visited: " << start.name << std::endl;
		return 0;
	}
	start.visited++;

	for (auto conn : start.conns) {
		if (conn.next != "") {
			//std::cout << start.name << " <-> ";
			Node next_node = adj.at(conn.next);
			if (!next_node.visited) {
				if (findPath(adj.at(conn.next), end)) {
					cost.push_back(conn);
					return 1;
				}
			}
		}
	}
	if (path.size())
	    path.pop_back();
	if (cost.size())
		cost.pop_back();
	return 0;
}

void Graph::printNode(const std::string node_name) const {
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

void Graph::printEdge(const Edge& edge) const {
	std::cout << "    " << edge.weight << " -> " << edge.next << "    Line: " << edge.line << std::endl;
}

void Graph::printPath() const {

	if (path.size()) {
		int len = path.size();
		int cost_index = len - 2;

		std::cout << "Connection found!" << std::endl;
		for (int i = 0; i < len; i++) {
			printf("%35s ", path[i].name.c_str());
			if (cost_index < 0) {
				break;
			}
			printf("  %2s %2d   %s\n", cost[cost_index].line.c_str(), cost[cost_index].weight, cost[cost_index].next.c_str());
			cost_index--;
		}
	}
}
