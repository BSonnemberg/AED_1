#ifndef PROJETO_AED_CLASSES_H
#define PROJETO_AED_CLASSES_H

#include <string>
#include <vector>

using namespace std;

/**
 * @brief The Classes class represents class schedule entries.
 */
class Classes {
private:
    string ClassCode; /**< The code of the class. */
    string UcCode; /**< The code of the associated course. */
    string Weekday; /**< The day of the week when the class occurs. */
    double StartHour; /**< The starting time of the class. */
    double Duration; /**< The duration of the class. */
    string Type; /**< The type of the class (e.g., lecture, lab). */

public:
    /**
     * @brief Default constructor for the Classes class.
     */
    Classes();

    /**
     * @brief Parameterized constructor for the Classes class.
     * @param ClassCode The code of the class.
     * @param UcCode The code of the associated course.
     * @param Weekday The day of the week when the class occurs.
     * @param StartHour The starting time of the class.
     * @param Duration The duration of the class.
     * @param Type The type of the class.
     */
    Classes(string ClassCode, string UcCode, string Weekday, double StartHour, double Duration, string Type);

    /**
     * @brief Get the code of the class.
     * @return The code of the class.
     */
    string getClassCode();

    /**
     * @brief Get the code of the associated course.
     * @return The code of the associated course.
     */
    string getUcCode();

    /**
     * @brief Get the day of the week when the class occurs.
     * @return The day of the week.
     */
    string getWeekday();

    /**
     * @brief Get the type of the class.
     * @return The type of the class (e.g., lecture, lab).
     */
    string getType();

    /**
     * @brief Get the starting time of the class.
     * @return The starting time.
     */
    double getStartHour();

    /**
     * @brief Get the duration of the class.
     * @return The duration of the class.
     */
    double getDuration();
};

#endif // PROJETO_AED_CLASSES_H