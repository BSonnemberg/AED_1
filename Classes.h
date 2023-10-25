#ifndef PROJETO_AED_CLASSES_H
#define PROJETO_AED_CLASSES_H
#include <string>
#include <vector>

using namespace std;

class Classes {
    string ClassCode,UcCode,Weekday,Type;
    double StartHour,Duration;
    public:
        string getClassCode();
        Classes(string ClassCode, string UcCode,string Weekday,double StartHour,double Duration,string Type);



};


#endif //PROJETO_AED_CLASSES_H
