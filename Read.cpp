#include "Read.h"
#include "Classes.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "Student.h"
#include <algorithm>
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
        lesson.push_back(classes);

    }


}

vector<Classes> Read::getClassvector(){
    return lesson;

    
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









int Read::weekdayToNumber(const std::string& day) {
    // Mapeamento dos dias da semana para números
    if (day == "Monday") return 1;
    if (day == "Tuesday") return 2;
    if (day == "Wednesday") return 3;
    if (day == "Thursday") return 4;
    if (day == "Friday") return 5;
    return 0; // Em caso de erro ou dia inválido
}

void Read::sortClassesByWeekdayAndStartHour(std::vector<Classes>& aula) {
    std::sort(aula.begin(), aula.end(), [this](Classes a, Classes b) {
        // Primeiro, compara os dias da semana
        if (weekdayToNumber(a.getWeekday()) != weekdayToNumber(b.getWeekday())) {
            return weekdayToNumber(a.getWeekday()) < weekdayToNumber(b.getWeekday());
        } else {
            // Se os dias forem iguais, compara as horas de início
            return a.getStartHour() < b.getStartHour();
        }
    });
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


