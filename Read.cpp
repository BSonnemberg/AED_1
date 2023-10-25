#include "Read.h"
#include "Classes.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

void Read::Read_Classes() {

    std::string classCode, ucCode, weekDay, type;
    std::string dir = "classes.txt", line;
    std::ifstream input(dir);
    double startHour, duration;
    char sep = ',';

    // ignore first line
    getline(input, line);

    while (getline(input, line)) {

        std::stringstream stream(line);
        // get schedule details
        getline(stream, classCode, sep);
        getline(stream, ucCode, sep);
        getline(stream, weekDay, sep);

        startHour = std::stod(stream.str());
        duration = std::stod(stream.str());
        getline(stream, type, sep);

        Classes classes = Classes(classCode, ucCode, weekDay, startHour, duration, type);
        aula.push_back(classes);
    }
}

std::vector<Classes> Read::getClass(){
    return aula;

    
}

