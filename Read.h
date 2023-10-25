//
// Created by Beatriz Sonnemberg on 25/10/2023.
//

#ifndef PROJETO_AED_READ_H
#define PROJETO_AED_READ_H
#include "Classes.h"


class Read {
    private:
        vector<Classes> aula;
    public:
        void Read_Classes();
        vector<Classes> getClass();

};


#endif //PROJETO_AED_READ_H
