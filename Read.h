//
// Created by Beatriz Sonnemberg on 25/10/2023.
//

#ifndef PROJETO_AED_READ_H
#define PROJETO_AED_READ_H
#include "Classes.h"


class Read {
    private:
        static vector<Classes> aula;
    public:
        void Read_Classes();
        static vector<Classes> getCLass();

};


#endif //PROJETO_AED_READ_H
