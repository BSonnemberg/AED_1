#ifndef PROJETO_AED_SLOT_H
#define PROJETO_AED_SLOT_H
#include <string>

/**
 * @class Slot
 * @brief Represents a time slot with information about the day, start time, end time, and type.
 */
class Slot {
public:
    /**
     * @brief Default constructor for the Slot class.
     *
     * Initializes the time slot with default values.
     */
    Slot();
    /**
     * @brief Parameterized constructor for the Slot class.
     *
     * Initializes the time slot with the provided values for the day of the week, start time, duration, and type.
     *
     * @param weekDay The day of the week for the time slot.
     * @param beginTime The start time of the time slot.
     * @param duration The duration of the time slot.
     * @param type The type of the time slot.
     */
    Slot(std::string weekDay, double beginTime, double duration, std::string type);

    /**
     * @brief Get the day of the week for the time slot.
     *
     * @return The day of the week as a string.
     */
    std::string getWeekDay();
    /**
     * @brief Get the type of the time slot.
     *
     * @return The type of the time slot as a string.
     */
    std::string getType();
    /**
     * @brief Get the start time of the time slot.
     *
     * @return The start time of the time slot as a floating-point number.
     */
    double getStartTime();
    /**
     * @brief Get the end time of the time slot.
     *
     * @return The end time of the time slot as a floating-point number.
     */
    double getEndTime();
    /**
     * @brief Check if the current time slot overlaps with another time slot.
     *
     * This function checks if the current time slot overlaps with the provided time slot.
     *
     * @param other The time slot to check for overlap.
     * @return True if there is an overlap, false otherwise.
     */
    bool overlaps(Slot &other);
    /**
     * @brief Compare two time slots for equality.
     *
     * This function compares the current time slot with another time slot for equality.
     *
     * @param other The time slot to compare with.
     * @return True if the time slots are equal, false otherwise.
     */
    bool operator==(Slot &other);
    /**
     * @brief Compare two time slots for ordering.
     *
     * This function compares the current time slot with another time slot for ordering purposes.
     *
     * @param other The time slot to compare with.
     * @return True if the current time slot is less than the other, false otherwise.
     */
    bool operator<(Slot &other);

private:
    std::string weekDay; /**< The day of the week for the time slot. */
    double startTime; /**< The start time of the time slot. */
    double endTime; /**< The end time of the time slot. */
    std::string type; /**< The type of the time slot. */
};


#endif //PROJETO_AED_SLOT_H
