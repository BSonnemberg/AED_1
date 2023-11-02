#include "Requests.h"
#include <iostream>
#include <algorithm>


Requests::Requests(Read& reader) : reader(reader) {}

bool Requests::vacancy(std::string& ucCode, string oldClassCode, std::string& newClassCode) {
    std::vector<Student> students = reader.getStudentvector();
    int maxOccupancyDifference = 4; // Máxima diferença de ocupação permitida

    int oldClassOccupancy = -1;
    int newClassOccupancy = +1;



    // Contar o número de alunos na turma antiga
    for (Student& student : students) {
        if (student.getUcCode() == ucCode && student.getClassCode() == oldClassCode) {
            oldClassOccupancy++;
        }
    }

    // Contar o número de alunos na turma nova
    for (Student& student : students) {
        if (student.getUcCode() == ucCode && student.getClassCode() == newClassCode) {
            newClassOccupancy++;
        }
    }

    int differenceWithOldClass = newClassOccupancy - oldClassOccupancy;

    if(differenceWithOldClass < 0){
        return true;
    }

    if (abs(differenceWithOldClass)> maxOccupancyDifference) {
        return false; // A diferença de ocupação excede o limite em relação à turma antiga da mesma UC.
    }

    return true;
}

    void Requests::switchClass(int StudentCode, std::string ucCode, std::string newClassCode) {
        reader.Read_Student();
        std::vector<Student> students = reader.getStudentvector();

        bool studentFound = false;


        for (Student student: students) {

            if (student.getStudentCode() == StudentCode && student.getUcCode() == ucCode) {
                studentFound = true;

                if (student.getClassCode() == newClassCode) {
                    std::cout << "The student " << student.getStudentName() << " is already in the class "
                              << newClassCode << "." << std::endl;
                } else {
                    // Verificar se a turma existe
                    if (vacancy(ucCode, student.getClassCode(), newClassCode) && capacity(ucCode, newClassCode)) {

                        student.setClassCode(newClassCode);
                        std::cout << "The student " << student.getStudentName() << " was transferred to the class "
                                  << newClassCode << "." << std::endl;
                        reader.updateStudentClass(StudentCode, ucCode, newClassCode);
                    } else if (!vacancy(ucCode, student.getClassCode(), newClassCode)) {
                        std::cout << "The change causes imbalance in classes" << std::endl;
                    } else {
                        cout << "Não há vagas na nova turma!";
                    }

                }

                break;
            }

        }
        if (!studentFound) {
            std::cout << "Student not found." << std::endl;
        }






    }

bool Requests::capacity(std::string ucCode, std::string newClassCode) {
    std::vector<Student> students = reader.getStudentvector();
    int newClassOccupancy = 1;
    int cap = 30;

    for (Student& student : students) {
        if (student.getUcCode() == ucCode && student.getClassCode() == newClassCode) {
            newClassOccupancy++;
        }
    }

    if (newClassOccupancy > cap){
        return false;
    }
    return true;

}

