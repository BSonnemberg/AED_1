//
// Created by Marta on 02/11/2023.
//

#include "Slot.h"

#include "Slot.h"
#include <map>

Slot::Slot(){
    weekDay = "";
    startTime = 0;
    endTime = 0;
    type = "";
}

Slot::Slot(std::string &weekDay, float &startTime, float &duration, std::string &type) {
    this->weekDay = weekDay;
    this->startTime = startTime;
    this->endTime = startTime + duration;
    this->type = type;
}
std::string Slot::getWeekDay(){
    return weekDay;
}

std::string Slot::getType(){
    return type;
}

float Slot::getStartTime(){
    return startTime;
}

float Slot::getEndTime(){
    return endTime;
}

bool Slot::overlaps(Slot& other) {
    if (this->weekDay != other.getWeekDay()) {
        return false;
    }
    if (this->startTime >= other.getEndTime() ||  this->endTime <= other.getStartTime()) {
        return false;
    }
    if(this->type == "T" || other.getType() == "T") {
        return false;
    }
    return true;
}


bool Slot::operator==(Slot &other) {
    if (weekDay != other.weekDay) {
        return false;
    }
    return startTime == other.startTime && endTime == other.endTime && type == other.type;
}

bool Slot::operator<(Slot &other) {
    if (weekDay != other.weekDay) {
        std::map<std::string, int> dayOrder = {
                {"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3},
                {"Thursday", 4}, {"Friday", 5}, {"Saturday", 6}, {"Sunday", 7}
        };
        return dayOrder[weekDay] < dayOrder[other.weekDay];
    }

    if (startTime != other.startTime) {
        return startTime < other.startTime;
    }

    if (endTime != other.endTime) {
        return endTime < other.endTime;
    }

    return type < other.type;
}

