//
// Created by Marta on 01/11/2023.
//

#ifndef PROJETO_AED_REQUESTS_H
#define PROJETO_AED_REQUESTS_H



#ifndef REQUESTS_H
#define REQUESTS_H

#include "Classes.h"
#include "Student.h"
#include "Read.h"
#include <vector>
#include <string>

class Requests {
public:


    Requests(Read& reader);
    void switchClass( int StudentCode, std::string ucCode, std::string& newClassCode);
    bool vacancy(std::string& ucCode, basic_string<char> oldClassCode, std::string& newClassCode);
    bool capacity (string ucCode, string newClassCode);

private:

    Read& reader;


};

#endif




#endif //PROJETO_AED_REQUESTS_H
