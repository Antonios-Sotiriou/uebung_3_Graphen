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

/* Struct to save data for each line before we create the graph of them. */
typedef struct {
	std::string name;
	std::vector<std::string> stations;
	std::vector<int> weights;
} Line;

/* Holds all the data readed from file. From this struct we can process the data further without reading the file again. */
typedef struct {
	std::vector<Line> lines;
} LinesTable;

#endif // !STRUCTS_H