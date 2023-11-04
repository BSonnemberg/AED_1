#ifndef PROJETO_AED_SCHEDULE_H
#define PROJETO_AED_SCHEDULE_H
using namespace std;
#include "Student.h"
#include "Classes.h"

class Schedule {
    public:

        void printStudentSchedule(int StudentCode);
        pair<std::pair<int, int>, std::pair<int, int>>  calcularHoras(Classes aula);
        void printClassSchedule (string ClassCode);

        void printUcSchedule (string UcCode);

        void printStudentClass(string ClassCode, string sortType);
        void printStudentUc (string UcCode, string sortType);
        void printStudentClassUc (string UcCode, string ClassCode, string sortType);







};


#endif //PROJETO_AED_SCHEDULE_H
