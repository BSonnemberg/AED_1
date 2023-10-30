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

vector<Classes> Read::getClassvector(){
    return aula;

    
}

void Read::Read_Student() {
    int StudentCode;
    string StudentName, UcCode,ClassCode;

    string  dir = "../schedule/students_classes.csv", line;

    ifstream input(dir);
    char sep =',';

    getline(input,line);

    while(getline(input,line)){
        stringstream iss (line);

        iss >> StudentCode >> sep;
        getline(iss, StudentName, sep);
        getline(iss, UcCode, sep);
        getline(iss, ClassCode);

        Student student = Student(StudentCode,StudentName,UcCode,ClassCode);
        students.push_back(student);
    }


}

vector<Student> Read::getStudentvector() {
    return students;
}

void Read::Read_classes_per_uc() {
    string UcCode, ClassCode;

    string dir = "../schedule/classes_per_uc.csv";
    string line;

    ifstream input(dir);
    char sep = ',';

    getline(input, line);

    while (getline(input, line)) {
        stringstream iss(line);

        getline(iss, UcCode, sep);
        getline(iss, ClassCode);

        classes_per_uc classesPerUcEntry = classes_per_uc(UcCode, ClassCode);
        classesPerUC.push_back(classesPerUcEntry);
    }
}

vector<classes_per_uc> Read::getClassesPerUCvector() {
    return classesPerUC;
}

