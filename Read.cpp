#include "Read.h"
#include "Classes.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

void Read::Read_Classes() {

    string ClassCode, UcCode, Weekday, Type;
    string dir = "../schedule/classes.csv", line;
    ifstream input(dir);
    double StartHour, Duration;
    char sep = ',';


    getline(input, line);

    while (getline(input, line)) {

        stringstream iss(line);

        getline(iss, ClassCode, sep);
        getline(iss, UcCode, sep);
        getline(iss, Weekday, sep);
        iss>> StartHour >> sep;
        iss>> Duration >> sep;
        getline(iss, Type);



        Classes classes = Classes(ClassCode, UcCode, Weekday, StartHour, Duration, Type);
        aula.push_back(classes);
    }
}

std::vector<Classes> Read::getClass(){
    return aula;

    
}

