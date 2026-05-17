#include "headers/printStructs.h"

void printConnection(Connection& conn) {
    std::cout << "    " << conn.weight << " -> " << conn.next << std::endl;
}
void printStation(Station& station) {
    std::cout << station.name << " {" << std::endl;
    for (auto conn : station.conns) {
        printConnection(conn);
    }
    std::cout << "}" << std::endl;
}
void printLine(Line& line) {
    int stations_length = line.stations.size();
    int weights_length = stations_length - 1;

    std::cout << line.name << " {\n    " << std::endl;
    for (int i = 0; i < stations_length; i++) {
        std::cout << line.stations[i];
        if (i == weights_length) {
            break;
        }
        std::cout << " <- " << line.weights[i] << " -> ";
    }
    std::cout << "\n}" << std::endl;
}
void printLinesTable(LinesTable& lines_table) {
    for (auto line : lines_table.lines) {
        std::cout << "{" << std::endl;
        std::cout << "    name   : " << line.name << std::endl;
        std::cout << "    stations: " << line.stations.size() << std::endl;
        std::cout << "    weights : " << line.weights.size() << std::endl;
        std::cout << "}" << std::endl;
    }
}