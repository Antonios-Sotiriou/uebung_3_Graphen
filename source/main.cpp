#include "headers/main.h"

char *createRelativePath(const char filename[]);
void readFileData(LinesTable *lines_table, const char filename[]);
void parseLineData(LinesTable *lines_table, char line_data[]);
float execTime(const clock_t start);

int main(int argc, char *argv[]) {

    clock_t start = clock();

	LinesTable lines_table;

	argc = 4;
	argv[0] = (char*)PROJECT_DATA_DIR;
	argv[1] = (char*)"wiener_linien.txt";
	argv[2] = (char*)"Westbahnhof";
	argv[3] = (char*)"Stefansplatz";

    if (argc == 4) {
		for (int i = 0; i < argc; i++) {
			std::cout << "args: " << argv[i] << std::endl;
		}
		readFileData(&lines_table, argv[1]);
	} else {
		std::cout << "Not enought arguments have been provided!" << std::endl;
	}
	printLinesTable(lines_table);
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
void readFileData(LinesTable *lines_table, const char filename[]) {

	char *path = createRelativePath(filename);

	FILE *fp = fopen(path, "r");
	if (!fp) {
		printf("Failed to open file: %s\n", path);
		return;
	}
	
	char line_data[1024] = { 0 };
	while (!feof(fp)) {
		fgets(line_data, 1024, fp);
		parseLineData(lines_table, line_data);
	}

	delete path;
}
/* Parses the data of a line, seperating Line name, station and weight from each other. */
void parseLineData(LinesTable *lines_table, char line_data[]) {
	Line line;

	char* token = strtok(line_data, ":");
	if (token != nullptr) {
		line.name.assign(token);
	}
	// consume the (:) char and spaces after the line name, until we hit a (") char
	token = strtok(nullptr, "\"");

	while (token != nullptr) {

		token = strtok(nullptr, "\"");
		if (token != nullptr) {
			line.stations.push_back(token);
		}

		token = strtok(nullptr, "\"");
		if (token != nullptr) {
			int weight = atoi(token);
			if (weight != 0) {
				line.weights.push_back(weight);
			}
		}
	}

	lines_table->lines.push_back(line);
}
// Counts time passed since start.
float execTime(const clock_t start) {
	clock_t diff = clock() - start;
	return (float)diff / CLOCKS_PER_SEC;
}