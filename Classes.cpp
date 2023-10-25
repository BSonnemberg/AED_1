
#include "Classes.h"

string Classes::getClassCode() {
    return ClassCode;
}

Classes::Classes(string ClassCode,string UcCode,string Weekday, double StartHour, double Duration,string Type) {
    this->ClassCode = ClassCode;
    this->UcCode = UcCode;
    this->Weekday = Weekday;
    this->StartHour = StartHour;
    this->Duration = Duration;
    this->Type = Type;

}
