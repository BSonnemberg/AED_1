#include "Requests.h"
#include <algorithm>


Requests::Requests(Read reader) {}

bool Requests::vacancy(std::string& ucCode, string oldClassCode, std::string& newClassCode) {
    Read reader;
    reader.Read_Student();
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
    Read reader;
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
                    }  else {

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
    Read reader;
    reader.Read_Student();
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









bool Requests::addUC(int StudentCode, std::string ucCode,  std::string newClassCode) {
    Read reader;
    reader.Read_Student();
    std::vector<Student> students = reader.getStudentvector();
    int ucCount = 0;
    string studentName;

    for (Student student : students) {
        if (reader.hasTimeConflict(ucCode, newClassCode)) {
            std::cout << "Time conflict with another class in the same UC. Cannot add." << std::endl;
            return false;
        }

        if (student.getStudentCode() == StudentCode) {
            studentName = student.getStudentName();



            if(student.getUcCode()==ucCode) {


                cout << "Student is already registered for the specified UC.";
                return false;
            }

        ucCount++;

        }
    }


    if (ucCount >= 7) {
        std::cout << "The student is already registered in 7 UCs. Cannot add more." << std::endl;
        return false;
    }

    // Verificar se há vaga na nova UC.
    else if (!capacity( ucCode, newClassCode)) {
        std::cout << "No vacancy in the new UC. Cannot add." << std::endl;
        return false;
    }



    else {
        // Adicionar a UC para o aluno e atualizar o arquivo "students_classes.csv".
        cout << studentName;
        reader.addStudentClass(StudentCode, studentName, ucCode, newClassCode);
        std::cout << "UC " << ucCode << " added to student " << StudentCode << "." << std::endl;
        return true;
    }
}

// Função para remover uma UC de um aluno
bool Requests::removeUC(int StudentCode, string ucCode) {
    Read reader;
    reader.Read_Student();
    std::vector<Student> students = reader.getStudentvector();
    bool found = false;
    string studentName;
    string classCode;

    for (Student& student : students) {

        if (student.getStudentCode() == StudentCode && student.getUcCode() == ucCode ) {
            studentName = student.getStudentName();
            classCode = student.getClassCode();

            found = true;
            return true;
        }
        std::cout << "UC not found for the student." << std::endl;
        return false;
    }

    // Remover a UC do aluno e atualizar o arquivo "students_classes.csv".
    reader.removeStudentClass(StudentCode, studentName,ucCode, classCode);
    std::cout << "UC " << ucCode << " removed from student " << StudentCode << "." << std::endl;

    return true;
}

// Função para trocar de UC para um aluno
void Requests::switchUC(int StudentCode, string ucCode,  string newClassCode, const std::string& newUCCode) {
    string studentname;
    Read reader;
    reader.Read_Student();
    if (!capacity(newClassCode,newClassCode)) {
        std::cout << "Transfer not allowed. The class has reached its maximum occupancy difference." << std::endl;
        return;
    }
    // Verificar conflito de horários.


    std::vector<Student> students = reader.getStudentvector();
    bool found = false;

    for (Student& student : students) {
        if (student.getStudentCode() == StudentCode) {
            if (student.getUcCode() == ucCode) {

                if (student.getClassCode() == newClassCode && student.getUcCode() == newUCCode) {
                    std::cout << "The student " << student.getStudentName() << " is already in the class " << newClassCode << "in uc" << newUCCode <<  "." << std::endl;
                } else {
                    std::cout << "Student found." << std::endl;
                }
                found = true;
                studentname = student.getStudentName();
                break;
            }
        }
    }

    // Remover a UC atual e adicionar a nova UC para o aluno

    removeUC(StudentCode, ucCode);
    addUC(StudentCode,  newUCCode, newClassCode);
}

