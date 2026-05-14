#include "headers/main.h"

char *createRelativePath(const char filename[]);
void readFileData(const char filename[]);
void parseLineData(const char line_data[]);
float execTime(const clock_t start);

int main(int argc, char *argv[]) {

    clock_t start = clock();

	argc = 4;
	argv[0] = PROJECT_DATA_DIR;
	argv[1] = "wiener_linien.txt";
	argv[2] = "Westbahnhof";
	argv[3] = "Stefansplatz";

    if (argc == 4) {
		for (int i = 0; i < argc; i++) {
			printf("args: %s\n", argv[i]);
		}
		readFileData(argv[1]);
	} else {
		printf("No arguments have been provided!");
	}

	printf("\nExecution time: %f secs\n", execTime(start));

	return 0;
}
/* Dynamically create a path to where the data are located. Return value must be freed after use. */
char *createRelativePath(const char filename[]) {
	int path_len = strlen(PROJECT_DATA_DIR) + strlen(filename) + 1;

	char *path = malloc(path_len);
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
		fgets(&line_data, 1024, fp);
		parseLineData(line_data);
	}

	free(path);
}
/* Parses the data of a line, seperating Line name, station and weight from each other. */
void parseLineData(const char line_data[]) {
	char line_name[4] = "";
	char station_name[64] = "";
	char weight[4] = "";

	char* token = strtok(line_data, ":");
	if (token != NULL) {
		strcpy(&line_name, token);
	}
	// consume the (:) char and spaces after the line name, until we hit a (") char
	token = strtok(NULL, "\"");

	printf("%s\n", line_name);
	while (token != NULL) {

		token = strtok(NULL, "\"");
		if (token != NULL) {
			strcpy(&station_name, token);
			printf("%-35s", station_name);
		}

		token = strtok(NULL, "\"");
		if (token != NULL) {
				strcpy(&weight, token);
				printf("%s\n", weight);
		}
	}
}

float execTime(const clock_t start) {
	clock_t diff = clock() - start;
	return (float)diff / CLOCKS_PER_SEC;
}