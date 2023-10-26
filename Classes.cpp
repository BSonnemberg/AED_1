#include "Classes.h"


Classes::Classes(string ClassCode,string UcCode,string Weekday, double StartHour, double Duration,string Type) {
    this->ClassCode = ClassCode;
    this->UcCode = UcCode;
    this->Weekday = Weekday;
    this->StartHour = StartHour;
    this->Duration = Duration;
    this->Type = Type;

}

string Classes::getClassCode() {
    return ClassCode;
}

string Classes::getUcCode() {
    return UcCode;
}

string Classes::getWeekday() {
    return Weekday;
}

double Classes::getStartHour() {
    return StartHour;
}

double Classes::getDuration() {
    return Duration;
}

string Classes::getType() {
    return Type;
}
