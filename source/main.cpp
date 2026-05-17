#include "headers/main.h"

char *createRelativePath(const char filename[]);
void readFileData(Graph &graph, const char filename[]);
void parseLineData(Graph &graph, char line_data[]);
float execTime(const clock_t start);

int main(int argc, char *argv[]) {

    clock_t start = clock();
	Graph graph;

	argc = 4;
	argv[0] = (char*)PROJECT_DATA_DIR;
	argv[1] = (char*)"wiener_linien.txt";
	argv[2] = (char*)"Westbahnhof";
	argv[3] = (char*)"Jaegerstrasse";

    if (argc == 4) {
		for (int i = 0; i < argc; i++) {
			std::cout << "args: " << argv[i] << std::endl;
		}
		readFileData(graph, argv[1]);
	} else {
		std::cout << "Not enought arguments have been provided!" << std::endl;
	}

	graph.findRoute(argv[2], argv[3]);
	//graph.printNode("Westbahnhof");
	printf("\nExecution time: %f secs\n", execTime(start));

	return 0;
}
/* Dynamically create a path to where the data are located. Return value must be freed after use. */
char *createRelativePath(const char filename[]) {
	int path_len = strlen(PROJECT_DATA_DIR) + strlen(filename) + 1;

	char *path = new char[path_len];
	if (!path) {
		return NULL;
	}
	snprintf(path, path_len, "%s%s", PROJECT_DATA_DIR, filename);

	return path;
}
/* Reads the data from the file line by line. */
void readFileData(Graph& graph, const char filename[]) {

	char *path = createRelativePath(filename);

	FILE *fp = fopen(path, "r");
	if (!fp) {
		printf("Failed to open file: %s\n", path);
		return;
	}
	
	char line_data[1024] = { 0 };
	while (!feof(fp)) {
		fgets(line_data, 1024, fp);
		parseLineData(graph, line_data);
	}

	delete path;
}
void parseLineData(Graph& graph, char line_data[]) {
	std::string lineName;
	std::vector<std::string> stations;
	std::vector<int> weights;

	char* token = strtok(line_data, ":");
	if (token != NULL) {
		lineName = token;
	}

	// consume the (:) char and spaces after the line name, until we hit a (") char
	token = strtok(NULL, "\"");
	while (token != NULL) {

		token = strtok(NULL, "\"");
		if (token == NULL) {
			break;
		}
		stations.push_back(token);

		token = strtok(NULL, "\"");
		if (token == NULL) {
			break;
		}
		int weight = atoi(token);
		if (weight) {
			weights.push_back(weight);
		}
	}

	for (size_t i = 0; i + 1 < stations.size(); i++) {
		graph.addNode(stations[i], stations[i + 1], weights[i], lineName);
	}
}
// Counts time passed since start.
float execTime(const clock_t start) {
	clock_t diff = clock() - start;
	return (float)diff / CLOCKS_PER_SEC;
}