//
// Created by Beatriz Sonnemberg on 25/10/2023.
//

#ifndef PROJETO_AED_READ_H
#define PROJETO_AED_READ_H
#include "Classes.h"
#include "Student.h"


class Read {
    private:
        vector<Classes> aula;
        vector<Student> students;
    public:
        void Read_Classes();
        vector<Classes> getClassvector();

        void Read_Student();
        vector<Student> getStudentvector();

};


#endif //PROJETO_AED_READ_H
