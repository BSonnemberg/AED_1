#include "Schedule.h"
#include "Read.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <set>
#include <algorithm>

/**
 * @brief Calculate the start and end times of a class.
 *
 * This function calculates the start and end times of a class based on its start hour and duration.
 *
 * @param _class The class object for which to calculate the hours.
 * @return A pair containing the start time and end time in hours and minutes.
 */
std::pair<std::pair<int, int>, std::pair<int, int>> Schedule:: calcularHoras(Classes _class) {
    int horasInicio = static_cast<int>(_class.getStartHour());
    double decimalMinutosInicio = (_class.getStartHour() - horasInicio) * 60;
    int minutosInicio = static_cast<int>(decimalMinutosInicio);
    int horasFim = horasInicio + static_cast<int>(_class.getDuration());
    int minutosFim = minutosInicio + static_cast<int>((_class.getDuration() - static_cast<int>(_class.getDuration())) * 60);

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

/**
 * @brief Print the schedule for a specific student.
 *
 * This function reads student and class information, filters classes for the given student, and prints the student's schedule.
 *
 * @param studentCode The code of the student for whom the schedule needs to be printed.
 */
void Schedule::printStudentSchedule(int studentCode) {
    bool ft =true;
    bool found=false;
    Read reader;
    reader.Read_Student();
    vector<Student> students = reader.getStudentvector();
    reader.Read_Classes();
    vector<Classes> _class = reader.getClassvector();
    vector<Classes> aux;

    for (Student student : students){
        if(student.getStudentCode()== studentCode){
            if(ft){
                found =true;
                cout << "Schedule for Student " << student.getStudentName() << " (Student Code: " << student.getStudentCode() << "):\n";
                ft=false;
            }
            for (Classes Class : _class) {
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
/**
 * @brief Print the schedule for a specific class based on the provided class code.
 *
 * This function reads class information, filters classes by the given class code, and prints the class schedule.
 *
 * @param ClassCode The code of the class for which the schedule needs to be printed.
 */
void Schedule::printClassSchedule(std::string ClassCode) {

    Read reader;
    reader.Read_Classes();
    vector<Classes> _class = reader.getClassvector();
    vector<Classes> aux;

    bool found = false;
    string currentDay = "";

    for (Classes Class : _class) {
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

/**
 * @brief Print the schedule for a specific course (UC) based on the provided UC code.
 *
 * This function reads class information, filters classes by the given UC code, and prints the UC schedule.
 *
 * @param UcCode The code of the UC (Course) for which the schedule needs to be printed.
 */
void Schedule::printUcSchedule(std::string UcCode) {
    Read reader;
    reader.Read_Classes();
    vector<Classes> _class = reader.getClassvector();
    vector<Classes> aux;

    pair <int,int>currenthour ; // Inicialização das variáveis
    string currentType = "";

    for (Classes Class : _class) {
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
                currentType = ""; // Reiniciar o tipo de _class ao mudar de dia
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



/**
 * @brief Compares two student objects based on their student codes.
 *
 * This function is used to compare two student objects by their student codes.
 *
 * @param a The first student object for comparison.
 * @param b The second student object for comparison.
 * @return True if the student code of 'a' is less than the student code of 'b', otherwise false.
 */
bool compareStudentsbyCode(Student a , Student b){
    return a.getStudentCode()<b.getStudentCode();
}
/**
 * @brief Compares two student objects based on their student names.
 *
 * This function is used to compare two student objects by their student names.
 *
 * @param a The first student object for comparison.
 * @param b The second student object for comparison.
 * @return True if the student name of 'a' is lexicographically less than the student name of 'b', otherwise false.
 */
bool compareStudentbyName(Student a, Student b){
    return a.getStudentName()<b.getStudentName();
}





/**
 * @brief Print the student information for a specific course (UC) based on the provided UC code and sorting type.
 *
 * This function reads student information, filters students by the given UC code, and prints their details.
 *
 * @param UcCode The code of the UC (Course) for which student information needs to be printed.
 * @param sortType The sorting type for the student list. It can be "Alphabetical" for sorting by name or any other value for sorting by student code.
 */
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


/**
 * @brief Print the student information for a specific course (UC) and class based on the provided UC code, class code, and sorting type.
 *
 * This function reads student information, filters students by the given UC code and class code, and prints their details.
 *
 * @param UcCode The code of the UC (Course) for which student information needs to be printed.
 * @param ClassCode The code of the class for which student information needs to be printed.
 * @param sortType The sorting type for the student list. It can be "Alphabetical" for sorting by name or any other value for sorting by student code.
 */
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

/**
 * @brief Print the student information for a specific class based on the provided class code and sorting type.
 *
 * This function reads student information, filters students by the given class code, and prints their details.
 *
 * @param classCode The code of the class for which student information needs to be printed.
 * @param sortType The sorting type for the student list. It can be "Alphabetical" for sorting by name or any other value for sorting by student code.
 */
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
