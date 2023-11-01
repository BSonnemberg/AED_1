//
// Created by Marta on 31/10/2023.
//

#ifndef PROJETO_AED_MENU_H
#define PROJETO_AED_MENU_H
#include <iostream>
#include "Schedule.h"
using namespace std;

class Menu {
    public:
        Menu();
        void firstMenu();
        void menuStudentSchedule();
        void menuClassSchedule();
        void menuUcSchedule();
        void menuStudentUC();
        void menuStudentClass();
        void menuStudentClassUC();
};


#endif //PROJETO_AED_MENU_H
