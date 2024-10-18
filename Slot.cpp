/**
 * @file Slot.cpp
 * @brief Implementation of the Slot class for managing time slots.
 *
 * This file contains the implementation of the Slot class, which represents time slots with
 * information about the day of the week, start and end times, and type.
 */
#include "Slot.h"

#include "Slot.h"
#include <map>
/**
 * @brief Default constructor for the Slot class.
 *
 * Initializes the time slot with default values.
 */
Slot::Slot(){
    weekDay = "";
    startTime = 0;
    endTime = 0;
    type = "";
}
/**
 * @brief Parameterized constructor for the Slot class.
 *
 * Initializes the time slot with the provided values for the day of the week, start time, duration, and type.
 *
 * @param weekDay The day of the week for the time slot.
 * @param startTime The start time of the time slot.
 * @param duration The duration of the time slot.
 * @param type The type of the time slot.
 */
Slot::Slot(std::string weekDay, double startTime, double duration, std::string type) {
    this->weekDay = weekDay;
    this->startTime = startTime;
    this->endTime = startTime + duration;
    this->type = type;
}
/**
 * @brief Get the day of the week for the time slot.
 *
 * @return The day of the week as a string.
 */
std::string Slot::getWeekDay(){
    return weekDay;
}
/**
 * @brief Get the type of the time slot.
 *
 * @return The type of the time slot as a string.
 */
std::string Slot::getType(){
    return type;
}
/**
 * @brief Get the start time of the time slot.
 *
 * @return The start time of the time slot as a floating-point number.
 */
double Slot::getStartTime(){
    return startTime;
}
/**
 * @brief Get the end time of the time slot.
 *
 * @return The end time of the time slot as a floating-point number.
 */
double Slot::getEndTime(){
    return endTime;
}
/**
 * @brief Check if the current time slot overlaps with another time slot.
 *
 * This function checks if the current time slot overlaps with the provided time slot.
 *
 * @param other The time slot to check for overlap.
 * @return True if there is an overlap, false otherwise.
 */
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

/**
 * @brief Compare two time slots for equality.
 *
 * This function compares the current time slot with another time slot for equality.
 *
 * @param other The time slot to compare with.
 * @return True if the time slots are equal, false otherwise.
 */
bool Slot::operator==(Slot &other) {
    if (weekDay != other.weekDay) {
        return false;
    }
    return startTime == other.startTime && endTime == other.endTime && type == other.type;
}
/**
 * @brief Compare two time slots for ordering.
 *
 * This function compares the current time slot with another time slot for ordering purposes.
 *
 * @param other The time slot to compare with.
 * @return True if the current time slot is less than the other, false otherwise.
 */
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

