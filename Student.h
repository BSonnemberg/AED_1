//
// Created by Marta on 27/10/2023.
//

#ifndef PROJETO_AED_STUDENT_H
#define PROJETO_AED_STUDENT_H
#include <string>
using namespace std;


class Student {
    private:
        int StudentCode;
        string StudentName, UcCode,ClassCode;
    public:
        Student(int StudentCode, string StudentName, string UcCode, string ClassCode);

        int getStudentCode();
        string getStudentName();
        string getUcCode();
        string getClassCode();






};


#endif //PROJETO_AED_STUDENT_H
