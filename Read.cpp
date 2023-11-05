/**
 * @file Read.cpp
 * @brief This file contains the implementation of the Read class, which is responsible for reading class and student data from CSV files.
 */
#include "Read.h"
#include "Classes.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "Student.h"
#include <algorithm>
using namespace std;
/**
 * @brief Reads class information from a CSV file and stores it in the 'lesson' vector.
 */
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
/**
 * @brief Returns the 'lesson' vector containing class information.
 * @return Vector of Classes objects.
 */
vector<Classes> Read::getClassvector(){
    return lesson;

    
}
/**
 * @brief Reads student information from a CSV file and stores it in the 'students' vector.
 */
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
/**
 * @brief Returns the 'students' vector containing student information.
 * @return Vector of Student objects.
 */
vector<Student> Read::getStudentvector() {
    return students;
}
/**
 * @brief Converts a weekday string to a corresponding numeric representation.
 * @param day The weekday string (e.g., "Monday", "Tuesday").
 * @return Numeric representation of the weekday (1 for Monday, 2 for Tuesday, and so on).
 *         Returns 0 in case of an error or an invalid day.
 */
int Read::weekdayToNumber(const std::string& day) {
    // Mapeamento dos dias da semana para números
    if (day == "Monday") return 1;
    if (day == "Tuesday") return 2;
    if (day == "Wednesday") return 3;
    if (day == "Thursday") return 4;
    if (day == "Friday") return 5;
    return 0; // Em caso de erro ou dia inválido
}
/**
 * @brief Sorts the 'aula' vector of Classes objects by weekday and start hour.
 *
 * This function sorts the input vector 'aula' based on the weekday and start hour of each class.
 *
 * @param aula A vector of Classes objects to be sorted.
 */
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
/**
 * @brief Reads class information per UC (University Course) from a CSV file and stores it in the 'classesPerUc' vector.
 */
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
/**
 * @brief Returns the 'classesPerUc' vector containing class information per UC.
 * @return Vector of Classes_Uc objects.
 */
vector<Classes_Uc> Read::getClassesPerUcvector() {
    return classesPerUc;
}
/**
 * @brief Updates the class associated with a student's UC (University Course).
 *
 * This function updates the class information for a specific student's UC in the 'students_classes.csv' file.
 *
 * @param studentCode The code of the student to update.
 * @param ucCode The code of the UC (University Course) to update.
 * @param newClassCode The new class code to associate with the student's UC.
 */
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
                for (Student& student : students) {
                    if (student.getStudentCode() == studentCode && student.getUcCode()==ucCode) {
                        student.setUcCode(ucCode);
                        student.setClassCode(newClassCode);
                        break;
                    }
                }
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

/**
 * @brief Adds a new student class entry to the 'students_classes.csv' file.
 *
 * This function adds a new entry for a student's class to the 'students_classes.csv' file. It checks if the entry already exists and appends the new entry if it doesn't.
 *
 * @param studentCode The code of the student to add.
 * @param studentName The name of the student to add.
 * @param ucCode The UC (University Course) code to associate with the student.
 * @param classCode The class code to associate with the UC.
 */
void Read::addStudentClass(int studentCode, const std::string& studentName, const std::string& ucCode, const std::string& classCode) {
    // Abra o arquivo original para leitura
    std::string filename = "../schedule/students_classes.csv";
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }

    // Verifique se a entrada já existe no arquivo
    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream lineStream(line);
        std::string currentStudentCode;
        std::string currentStudentName;
        std::string currentUcCode;
        std::string currentClassCode;

        if (std::getline(lineStream, currentStudentCode, ',') &&
            std::getline(lineStream, currentStudentName, ',') &&
            std::getline(lineStream, currentUcCode, ',') &&
            std::getline(lineStream, currentClassCode)) {


        }
    }

    // Agora abra o arquivo para adicionar a nova entrada
    std::ofstream outFile(filename, std::ios::app);  // Abra o arquivo no modo de anexar

    if (!outFile.is_open()) {
        std::cerr << "Error opening the file for writing." << std::endl;
        inFile.close();
        return;
    }

    // Escreva a nova entrada no arquivo
    outFile << studentCode << "," << studentName << "," << ucCode << "," << classCode << std::endl;
    students.push_back(Student(studentCode, studentName, ucCode, classCode));

    // Feche os arquivos
    inFile.close();
    outFile.close();
}

/**
 * @brief Removes a student class entry from the 'students_classes.csv' file.
 *
 * This function removes an existing entry for a student's class from the 'students_classes.csv' file. It checks for a match and removes the entry accordingly.
 *
 * @param studentCode The code of the student to remove.
 * @param studentName The name of the student to remove.
 * @param ucCode The UC (University Course) code to disassociate from the student.
 * @param classCode The class code to disassociate from the UC.
 */
void Read::removeStudentClass(int studentCode, string ucCode, string classCode) {
    std::string filename = "../schedule/students_classes.csv";
    std::string tempFilename = "../schedule/students_classes_temp.csv"; // Nome do arquivo temporário
    std::ifstream inFile(filename);
    std::ofstream outFile(tempFilename);
    std::string line;
    bool removed = false;
    int studentIndex = -1;

    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].getStudentCode() == studentCode && students[i].getUcCode() == ucCode) {
            studentIndex = static_cast<int>(i);
            break;
        }
    }

    while (std::getline(inFile, line)) {
        std::istringstream lineStream(line);
        std::string currentStudentCode;
        std::string currentstudentName, currentUcCode, currentclassCode;

        if (std::getline(lineStream, currentStudentCode, ',') &&
            std::getline(lineStream, currentstudentName, ',') &&
            std::getline(lineStream, currentUcCode, ',') &&
            std::getline(lineStream, currentclassCode)) {

            if (currentStudentCode == std::to_string(studentCode) && currentUcCode == ucCode) {
                // A entrada corresponde ao aluno e UC, então não a copiamos para o arquivo de saída (removemos).
                removed = true;
            } else {
                // A entrada não corresponde, então a copiamos para o arquivo de saída.
                outFile << currentStudentCode << "," << currentstudentName << "," << currentUcCode << "," << currentclassCode << '\n';
            }
        }
    }

    inFile.close();
    outFile.close();

    if (removed) {
        if (studentIndex != -1) {
            students.erase(students.begin() + studentIndex);
        }
        if (std::remove(filename.c_str()) == 0 && std::rename(tempFilename.c_str(), filename.c_str()) == 0) {
            // Sucesso ao substituir o arquivo original após a remoção da entrada.
        } else {
            std::cerr << "Error replacing the original file." << std::endl;
        }
    }
}






