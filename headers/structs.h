#ifndef STRUCTS_H
#define STRUCTS_H

enum NodeType {
	station,
	connection
};

/* A station of the line which can have many connections to other lines. */
typedef struct Station {
	char name[64];
	int num_of_cons;
	struct Connection *conns;
} Station;

/* The connection between two stops. Value is the weight for this connection. */
typedef struct {
	int value;
	Station *prev;
	Station *next;
} Connection;

/* Struct to save data for each line before we create the graph of them. */
typedef struct {
	char name[64];
	int num_of_weigth, num_of_stations;
	char *stations;
	int *weights;
} Line;

/* Holds all the data readed from file. From this struct we can process the data further without reading the file again. */
typedef struct {
	Line *lines;
} LinesTable;

#endif // !STRUCTS_H