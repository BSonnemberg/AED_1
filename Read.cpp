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

void Read::Read_Classes_Per_Uc() {
    string UcCode, ClassCode;
    string dir= "../schedule/classes_per_uc.csv";
    string line;

    ifstream input(dir);
    char sep = ',';

    getline(input, line);

    while(getline(input, line)){
        stringstream iss(line);

        getline(iss, UcCode, sep);
        getline(iss, ClassCode);

        Classes_Uc classesPerUcEntry = Classes_Uc(UcCode, ClassCode);
        classesPerUc.push_back(classesPerUcEntry);
    }
}

vector<Classes_Uc> Read::getClassesPerUcvector() {
    return classesPerUc;
}
void Read::updateStudentClass(int studentCode, string ucCode, string newClassCode) {
    std::string filename = "../schedule/students_classes.csv";
    std::string tempFilename = "../schedule/students_classes_temp.csv"; // Nome de arquivo temporário
    std::ifstream inFile(filename);
    std::ofstream outFile(tempFilename);
    std::string line;
    bool updated = false;

    while (std::getline(inFile, line)) {
        std::istringstream lineStream(line);
        std::string currentStudentCode;
        std::string studentName, currentUcCode, classCode;

        if (std::getline(lineStream, currentStudentCode, ',') &&
            std::getline(lineStream, studentName, ',') &&
            std::getline(lineStream, currentUcCode, ',') &&
            std::getline(lineStream, classCode)) {

            if (currentStudentCode == std::to_string(studentCode) && currentUcCode == ucCode) {
                outFile << studentCode << "," << studentName << "," << ucCode << "," << newClassCode << '\n';
                updated = true;
            } else {
                outFile << currentStudentCode << "," << studentName << "," << currentUcCode << "," << classCode << '\n';
            }
        }
    }

    inFile.close();
    outFile.close();

    if (updated) {
        if (std::remove(filename.c_str()) == 0 && std::rename(tempFilename.c_str(), filename.c_str()) == 0) {
            // Sucesso ao substituir o arquivo original
        } else {
            std::cerr << "Error replacing the original file." << std::endl;
        }
    }
}





