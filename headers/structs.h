#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
#include <vector>

enum NodeType {
	station,
	connection
};

/* The connection between two stops. Value is the weight for this connection. */
typedef struct Connection {
	int weight;
	std::string next;
} Connection;

/* A station of the line which can have many connections to other lines. */
typedef struct Station {
	std::string name;
	std::vector<Connection> conns;
} Station;

#endif // !STRUCTS_H