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
#include "Slot.h"
#include <vector>
#include <string>
#include <iostream>


class Requests {
public:

    int cap =30;

    Requests(Read reader);
    Requests();
    bool cheekClassOverlap(int StudentCode, std::string ucCode, std::string newClassCode);

    void switchClass( int StudentCode, std::string ucCode, std::string newClassCode);
    bool vacancy(std::string& ucCode, string oldClassCode, std::string& newClassCode);
    bool capacity (string ucCode, string newClassCode);
    bool addUC(int StudentCode,  std::string ucCode,  std::string newClassCode);
    bool removeUC(int StudentCode,  string ucCode);
    void switchUC(int StudentCode, string ucCode, string newClassCode, const std::string& newUCCode);
    vector<Classes> getStudentClasses(int StudentCode);
    vector<Slot> getClassSlots(std::string ClassCode, std::string UcCode);

private:



};

#endif




#endif //PROJETO_AED_REQUESTS_H
