#include "headers/main.h"

Graph graph; //global erzeugt, damit die Funktion parseLineData sie verwenden kann
char *createRelativePath(const char filename[]);
void readFileData(const char filename[]);
void parseLineData(char line_data[]);
float execTime(const clock_t start);

int main(int argc, char *argv[]) {

	


    clock_t start = clock();

	argc = 4;
	argv[0] = (char*)PROJECT_DATA_DIR;
	argv[1] = (char*)"wiener_linien.txt";
	argv[2] = (char*)"Westbahnhof";
	argv[3] = (char*)"Stephansplatz";

    if (argc == 4) {
		for (int i = 0; i < argc; i++) {
			std::cout << "args: " << argv[i] << std::endl;
		}
		readFileData(argv[1]);
	} else {
		std::cout << "Not enought arguments have been provided!" << std::endl;
	}

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
void readFileData(const char filename[]) {

	char *path = createRelativePath(filename);

	FILE *fp = fopen(path, "r");
	if (!fp) {
		printf("Failed to open file: %s\n", path);
		return;
	}
	
	char line_data[1024] = "\0";
	while (!feof(fp)) {
		fgets(line_data, 1024, fp);
		parseLineData(line_data);
	}

	delete path;
}

//
///* Parses the data of a line, seperating Line name, station and weight from each other. */
//void parseLineData(char line_data[]) {
//	char line_name[4] = "";
//	char station_name[64] = "";
//	char weight[4] = "";
//
//	char* token = strtok(line_data, ":");
//	if (token != NULL) {
//		strcpy(line_name, token);
//	}
//	// consume the (:) char and spaces after the line name, until we hit a (") char
//	token = strtok(NULL, "\"");
//
//	printf("%s\n", line_name);
//	while (token != NULL) {
//
//		token = strtok(NULL, "\"");
//		if (token != NULL) {
//			strcpy(station_name, token);
//			printf("%-35s", station_name);
//		}
//
//		token = strtok(NULL, "\"");
//		if (token != NULL) {
//				strcpy(weight, token);
//				printf("%s\n", weight);
//		}
//	}
//}

void parseLineData(char line_data[]) {
	std::string lineName;
	std::vector<std::string> stations;
	std::vector<int> weights;

	// 1. Linienname extrahieren
	char* token = strtok(line_data, ":");
	if (token != NULL) {
		lineName = token;
	}

	// 2. Jetzt Stationen und Gewichte abwechselnd lesen
	token = strtok(NULL, "\""); // springt bis zum ersten "
	while (token != NULL) {

		// Station
		token = strtok(NULL, "\"");
		if (token == NULL) break;
		stations.push_back(token);

		// Gewicht (steht zwischen den nächsten ")
		token = strtok(NULL, "\"");
		if (token == NULL) break;
		weights.push_back(std::stoi(token));

		// nächster Durchlauf
	}

	// 3. Kanten erzeugen
	for (size_t i = 0; i + 1 < stations.size(); i++) {
		graph.addEdge(stations[i], stations[i + 1], weights[i], lineName);
	}
}



// Counts time passed since start.
float execTime(const clock_t start) {
	clock_t diff = clock() - start;
	return (float)diff / CLOCKS_PER_SEC;
}