#ifndef PROJETO_AED_CLASSES_H
#define PROJETO_AED_CLASSES_H
#include <string>
#include <vector>


using namespace std;

class Classes {
    private:
        string ClassCode,UcCode,Weekday,Type;
        double StartHour,Duration;
    public:
        Classes();
        Classes(string ClassCode, string UcCode,string Weekday,double StartHour,double Duration,string Type);

        string getClassCode();
        string getUcCode();
        string getWeekday();
        string getType();
        double getStartHour();
        double getDuration();




};


#endif //PROJETO_AED_CLASSES_H
