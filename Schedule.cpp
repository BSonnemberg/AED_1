#include "Schedule.h"
#include "Read.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <set>
#include <algorithm>


std::pair<std::pair<int, int>, std::pair<int, int>> Schedule:: calcularHoras(Classes aula) {
    int horasInicio = static_cast<int>(aula.getStartHour());
    double decimalMinutosInicio = (aula.getStartHour() - horasInicio) * 60;
    int minutosInicio = static_cast<int>(decimalMinutosInicio);
    int horasFim = horasInicio + static_cast<int>(aula.getDuration());
    int minutosFim = minutosInicio + static_cast<int>((aula.getDuration() - static_cast<int>(aula.getDuration())) * 60);

    while (minutosInicio >= 60) {
        minutosInicio -= 60;
        horasInicio++;
    }
    while (minutosFim >= 60) {
        minutosFim -= 60;
        horasFim++;
    }
    return {{horasInicio, minutosInicio}, {horasFim, minutosFim}};
}


void Schedule::printStudentSchedule(int studentCode) {
    bool ft =true;
    bool found=false;
    Read reader;
    reader.Read_Student();
    vector<Student> students = reader.getStudentvector();
    reader.Read_Classes();
    vector<Classes> aula = reader.getClassvector();
    vector<Classes> aux;

    for (Student student : students){
        if(student.getStudentCode()== studentCode){
            if(ft){
                found =true;
                cout << "Schedule for Student " << student.getStudentName() << " (Student Code: " << student.getStudentCode() << "):\n";
                ft=false;
            }
            for (Classes Class : aula) {
                if (Class.getUcCode() == student.getUcCode() && Class.getClassCode()==student.getClassCode()) {
                    aux.push_back(Class);
                }
            }
        }
    }
    if(!found){
        cout <<"Student not found!";
    }
    string currentDay = "";
    reader.sortClassesByWeekdayAndStartHour(aux);
    for (Classes Class : aux){
        std::pair<std::pair<int, int>, std::pair<int, int>> horas = calcularHoras(Class);

        if (Class.getWeekday() != currentDay) {
            currentDay = Class.getWeekday();
            cout << "-----" << currentDay << "-----" << endl;
        }
        cout << horas.first.first << ":" << setfill('0') << setw(2) << horas.first.second
             << " to " << horas.second.first << ":" << setfill('0') << setw(2) << horas.second.second;
        cout << "     " << Class.getType() << "    " << Class.getClassCode() << "    " << Class.getUcCode() << "\n";
    }
}

void Schedule::printClassSchedule(std::string ClassCode) {

    Read reader;
    reader.Read_Classes();
    vector<Classes> aula = reader.getClassvector();
    vector<Classes> aux;

    bool found = false;
    string currentDay = "";

    for (Classes Class : aula) {
        if (Class.getClassCode() == ClassCode) {
            aux.push_back(Class);
        }
    }
    reader.sortClassesByWeekdayAndStartHour(aux);
    for (Classes Class : aux) {
        if (Class.getClassCode() == ClassCode) {
            found = true;
            std::pair<std::pair<int, int>, std::pair<int, int>> horas = calcularHoras(Class);
            if (Class.getWeekday() != currentDay) {

                currentDay = Class.getWeekday();
                cout << "-----" << currentDay << "-----" << endl;
            }

            std::cout << horas.first.first << ":" << setfill('0') << setw(2) << horas.first.second
                      << " to " << horas.second.first << ":" << setfill('0') << setw(2) << horas.second.second;
            std::cout << "     " << Class.getType() << "    " << Class.getUcCode() << "\n";
        }
    }

    if (!found) {
        std::cout << "Class not found." << std::endl;
    }
}


void Schedule::printUcSchedule(std::string UcCode) {
    Read reader;
    reader.Read_Classes();
    vector<Classes> aula = reader.getClassvector();
    vector<Classes> aux;

    pair <int,int>currenthour ; // Inicialização das variáveis
    string currentType = "";

    for (Classes Class : aula) {
        if (Class.getUcCode() == UcCode) {
            aux.push_back(Class);
        }
    }

    if (!aux.empty()) {
        reader.sortClassesByWeekdayAndStartHour(aux);
        string currentDay = "";

        for (Classes Class : aux) {
            std::pair<std::pair<int, int>, std::pair<int, int>> horas = calcularHoras(Class);

            if (Class.getWeekday() != currentDay) {
                cout << '\n';
                currentDay = Class.getWeekday();
                cout << "-----" << currentDay << "-----" << endl;
                currenthour = {-1,-1}; // Reiniciar a hora ao mudar de dia
                currentType = ""; // Reiniciar o tipo de aula ao mudar de dia
            }

            if (horas.first != currenthour || currentType != Class.getType()) {
                cout << '\n';
                cout << horas.first.first << ":" << setfill('0') << setw(2) << horas.first.second
                     << " to " << horas.second.first << ":" << setfill('0') << setw(2) << horas.second.second;
                cout << "     " << Class.getType() << "    ";
                currenthour = horas.first;
                currentType = Class.getType();
            }

            cout << Class.getClassCode() << " ";
        }
    } else {
        cout << "UC not found." << endl;
    }

}




bool compareStudentsbyCode(Student a , Student b){
    return a.getStudentCode()<b.getStudentCode();
}

bool compareStudentbyName(Student a, Student b){
    return a.getStudentName()<b.getStudentName();
}






void Schedule::printStudentUc(std::string UcCode, string sortType) {
    std::set<std::string> printedIDs; // Conjunto para rastrear IDs de alunos já impressos
    Read reader;
    reader.Read_Student();
    vector<Student> students = reader.getStudentvector();

    bool found = false;
    if (sortType == "Alphabetical") {
        sort(students.begin(), students.end(), compareStudentbyName);
    }
    else{
        sort(students.begin(),students.end(), compareStudentsbyCode);
    }

    for ( auto& student : students) {
        if (student.getUcCode() == UcCode) {
            found = true;

            // Verifica se o ID do aluno já foi impresso
            std::string studentIDString = std::to_string(student.getStudentCode());
            if (printedIDs.count(studentIDString) == 0) {
                printedIDs.insert(studentIDString); // Adiciona o ID ao conjunto

                std::cout << "Student Name: " << student.getStudentName() << std::endl;
                std::cout << "Student ID: " << student.getStudentCode() << std::endl;
                // Outras informações relevantes do aluno
                std::cout << "------------------" << std::endl;
            }
        }
    }

    if (!found) {
        std::cout << "No students found in Uc " << UcCode << std::endl;
    }

}



void Schedule::printStudentClassUc(std::string UcCode, std::string ClassCode, string sortType) {

    Read reader;
    reader.Read_Student();
    vector<Student> students = reader.getStudentvector();
    bool found = false;
    if (sortType == "Alphabetical") {
        sort(students.begin(), students.end(), compareStudentbyName);
    }
    else{
        sort(students.begin(),students.end(), compareStudentsbyCode);
    }



    for ( Student student : students) {


        if (student.getUcCode() == UcCode && student.getClassCode()==ClassCode) {
            found = true;



                std::cout << "Student Name: " << student.getStudentName() << std::endl;
                std::cout << "Student ID: " << student.getStudentCode() << std::endl;
                // Outras informações relevantes do aluno
                std::cout << "------------------" << std::endl;

        }
    }

    if (!found) {

        std::cout << "No students found in Uc " << UcCode << std::endl;
    }


}


void Schedule::printStudentClass(std::string classCode, string sortType) {
    std::set<std::string> printedIDs; // Conjunto para rastrear IDs de alunos já impressos
    Read reader;
    reader.Read_Student();
    vector<Student> students = reader.getStudentvector();

    bool found = false;
    if (sortType == "Alphabetical") {
        sort(students.begin(), students.end(), compareStudentbyName);
    }
    else{
        sort(students.begin(),students.end(), compareStudentsbyCode);
    }


    for ( auto& student : students) {
        if (student.getClassCode() == classCode) {
            found = true;

            // Verifica se o ID do aluno já foi impresso
            std::string studentIDString = std::to_string(student.getStudentCode());
            if (printedIDs.count(studentIDString) == 0) {
                printedIDs.insert(studentIDString); // Adiciona o ID ao conjunto

                std::cout << "Student Name: " << student.getStudentName() << std::endl;
                std::cout << "Student ID: " << student.getStudentCode() << std::endl;
                // Outras informações relevantes do aluno
                std::cout << "------------------" << std::endl;
            }
        }
    }

    if (!found) {
        std::cout << "No students found in class " << classCode << std::endl;
    }

}
