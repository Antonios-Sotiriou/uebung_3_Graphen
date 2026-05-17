#ifndef PRINTSTRUCTS_H
#define PRINTSTRUCTS_H

#include "headers/structs.h"

#include <iostream>

void printConnection(Connection& conn);
void printStation(Station& station);
void printLine(Line& line);
void printLinesTable(LinesTable& lines_table);

#endif // !PRINTSTRUCTS_H