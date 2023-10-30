//
// Created by Beatriz Sonnemberg on 25/10/2023.
//

#ifndef PROJETO_AED_READ_H
#define PROJETO_AED_READ_H
#include "Classes.h"
#include "Student.h"
#include "classes_per_uc.h"


class Read {
    private:
        vector<Classes> aula;
        vector<Student> students;
        vector<classes_per_uc> classesPerUC;
    public:
        void Read_Classes();
        vector<Classes> getClassvector();

        void Read_Student();
        vector<Student> getStudentvector();

        void Read_classes_per_uc();
        vector<classes_per_uc> getClassesPerUCvector();

};


#endif //PROJETO_AED_READ_H
