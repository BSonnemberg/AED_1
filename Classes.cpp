/**
 * @file Classes.cpp
 * @brief Implementation of the Classes class.
 */

#include "Classes.h"

/**
 * @brief Default constructor for the Classes class.
 */
Classes::Classes() {}

/**
 * @brief Parameterized constructor for the Classes class.
 * @param ClassCode The code of the class.
 * @param UcCode The code of the associated course.
 * @param Weekday The day of the week when the class occurs.
 * @param StartHour The starting time of the class.
 * @param Duration The duration of the class.
 * @param Type The type of the class (e.g., lecture, lab).
 */
Classes::Classes(string ClassCode, string UcCode, string Weekday, double StartHour, double Duration, string Type) {
    this->ClassCode = ClassCode;
    this->UcCode = UcCode;
    this->Weekday = Weekday;
    this->StartHour = StartHour;
    this->Duration = Duration;
    this->Type = Type;
}

/**
 * @brief Get the code of the class.
 * @return The code of the class.
 */
string Classes::getClassCode() {
    return ClassCode;
}

/**
 * @brief Get the code of the associated course.
 * @return The code of the associated course.
 */
string Classes::getUcCode() {
    return UcCode;
}

/**
 * @brief Get the day of the week when the class occurs.
 * @return The day of the week.
 */
string Classes::getWeekday() {
    return Weekday;
}

/**
 * @brief Get the starting time of the class.
 * @return The starting time.
 */
double Classes::getStartHour() {
    return StartHour;
}

/**
 * @brief Get the duration of the class.
 * @return The duration of the class.
 */
double Classes::getDuration() {
    return Duration;
}

/**
 * @brief Get the type of the class (e.g., lecture, lab).
 * @return The type of the class.
 */
string Classes::getType() {
    return Type;
}