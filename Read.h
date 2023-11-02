//
// Created by Beatriz Sonnemberg on 25/10/2023.
//

#ifndef PROJETO_AED_READ_H
#define PROJETO_AED_READ_H
#include "Classes.h"
#include "Student.h"
#include "Classes_Uc.h"



class Read {
    private:
        vector<Classes> lesson;
        vector<Student> students;
        vector<Classes_Uc> classesPerUc;

    public:
        void Read_Classes();
        vector<Classes> getClassvector();

        void Read_Student();
        vector<Student> getStudentvector();
        void updateStudentClass(int studentCode, string  ucCode, string newClassCode);
        void Read_Classes_Per_Uc();
        vector<Classes_Uc> getClassesPerUcvector();
    void addStudentClass(int studentCode, const std::string& studentName, const std::string& ucCode, const std::string& classCode);

    void removeStudentClass(int studentCode, string studentName, string ucCode, string classCode);

    bool compareStudentCodes(Student a, Student b);
    void sortStudentsByCode(std::vector<Student>& students);



    int weekdayToNumber(const std::string& day);
    void sortClassesByWeekdayAndStartHour(std::vector<Classes>& aula);





};


#endif //PROJETO_AED_READ_H
