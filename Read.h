//
// Created by Beatriz Sonnemberg on 25/10/2023.
//

#ifndef PROJETO_AED_READ_H
#define PROJETO_AED_READ_H
#include "Classes.h"
#include "Student.h"


class Read {
    private:
        vector<Classes> lesson;
        vector<Student> students;
    public:
        void Read_Classes();
        vector<Classes> getClassvector();

        void Read_Student();
        vector<Student> getStudentvector();

    bool compareStudentCodes(Student a, Student b);
    void sortStudentsByCode(std::vector<Student>& students);



    int weekdayToNumber(const std::string& day);
    void sortClassesByWeekdayAndStartHour(std::vector<Classes>& aula);



};


#endif //PROJETO_AED_READ_H
