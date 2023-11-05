#ifndef PROJETO_AED_SCHEDULE_H
#define PROJETO_AED_SCHEDULE_H

#include "Student.h"
#include "Classes.h"

/**
 * @class Schedule
 * @brief Manages and prints schedules for students, classes, and courses (UC).
 */
class Schedule {
public:
    /**
     * @brief Print the schedule for a specific student based on the provided student code.
     *
     * This function reads student and class information, filters classes by the given student code, and prints the student's schedule.
     *
     * @param StudentCode The code of the student for which the schedule needs to be printed.
     */
    void printStudentSchedule(int StudentCode);

    /**
     * @brief Calculate the start and end times of a class.
     *
     * This function calculates the start and end times of a class based on its start hour and duration.
     *
     * @param _class The class object for which to calculate the hours.
     * @return A pair containing the start time and end time in hours and minutes.
     */
    pair<std::pair<int, int>, std::pair<int, int>> calcularHoras(Classes _class);

    /**
     * @brief Print the schedule for a specific class based on the provided class code.
     *
     * This function reads class information, filters classes by the given class code, and prints the class schedule.
     *
     * @param ClassCode The code of the class for which the schedule needs to be printed.
     */
    void printClassSchedule(string ClassCode);

    /**
     * @brief Print the schedule for a specific course (UC) based on the provided UC code.
     *
     * This function reads class information, filters classes by the given UC code, and prints the UC schedule.
     *
     * @param UcCode The code of the UC (Course) for which the schedule needs to be printed.
     */
    void printUcSchedule(string UcCode);

    /**
     * @brief Print the student information for a specific class based on the provided class code and sorting type.
     *
     * This function reads student information, filters students by the given class code, and prints their details.
     *
     * @param ClassCode The code of the class for which student information needs to be printed.
     * @param sortType The sorting type for the student list. It can be "Alphabetical" for sorting by name or any other value for sorting by student code.
     */
    void printStudentClass(string ClassCode, string sortType);

    /**
     * @brief Print the student information for a specific course (UC) based on the provided UC code and sorting type.
     *
     * This function reads student information, filters students by the given UC code, and prints their details.
     *
     * @param UcCode The code of the UC (Course) for which student information needs to be printed.
     * @param sortType The sorting type for the student list. It can be "Alphabetical" for sorting by name or any other value for sorting by student code.
     */
    void printStudentUc(string UcCode, string sortType);

    /**
     * @brief Print the student information for a specific course (UC) and class based on the provided UC code, class code, and sorting type.
     *
     * This function reads student information, filters students by the given UC code and class code, and prints their details.
     *
     * @param UcCode The code of the UC (Course) for which student information needs to be printed.
     * @param ClassCode The code of the class for which student information needs to be printed.
     * @param sortType The sorting type for the student list. It can be "Alphabetical" for sorting by name or any other value for sorting by student code.
     */
    void printStudentClassUc(string UcCode, string ClassCode, string sortType);
};

#endif //PROJETO_AED_SCHEDULE_H