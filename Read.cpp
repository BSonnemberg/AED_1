//
// Created by Beatriz Sonnemberg on 25/10/2023.
//

#include "Read.h"
#include "Classes.h"
#include <fstream>
#include <sstream>
using namespace  std;

void Read::Read_Classes() {
    string ClassCode,UcCode,Weekday,Type;
    double StartHour,Duration;
    char c;
    vector<Classes> aula;
    string file = "classes.txt";
    string line;
    ifstream in(file);
    while (!in.eof()) {
        getline(in, line);
        istringstream iss(line);
        getline(iss, ClassCode,c);
        getline(iss, UcCode,c);
        getline(iss, Weekday,c);
        iss >> StartHour >> c;
        iss >> Duration >> c;
        getline(iss, Type,c);

        Classes classes = Classes(ClassCode, UcCode, Weekday,StartHour,Duration,Type);
        aula.push_back(classes);

    }
}

std::vector<Classes> Read::getCLass(){
    return aula;
    
}

