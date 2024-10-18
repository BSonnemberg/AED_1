/**
 * @file Requests.h
 *
 * @brief This file defines the Requests class and related data structures for managing student enrollment actions.
 *
 * The Requests class provides functions for adding, switching, or removing a student's enrollment in classes and subjects (UCs).
 */
#ifndef PROJETO_AED_REQUESTS_H
#define PROJETO_AED_REQUESTS_H
#ifndef REQUESTS_H
#define REQUESTS_H

#include "Classes.h"
#include "Student.h"
#include "Read.h"
#include "Slot.h"
#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <stack>
/**
 * @enum ActionType
 * @brief Enumeration of possible student enrollment action types.
 */
enum class ActionType {
    AddUC,
    RemoveUC,
    SwitchUC,
    switchClass,
};

/**
 * @struct Action
 * @brief Data structure to represent a student enrollment action.
 */
struct Action {
    ActionType type;           /**< Type of action */
    int studentCode;           /**< Unique identifier of the student */
    std::string ucCode;        /**< Code of the University Course (UC) */
    std::string classCode;     /**< Code of the class */
    std::string description;   /**< Description of the action (optional) */
    std::string newClassCode;  /**< Code of the new class (for certain actions) */
    std::string newUcCode;     /**< Code of the new University Course (for certain actions) */
    std::string name;          /**< Name of the student */
};


/**
 * @class Requests
 * @brief Class for managing student enrollment actions.
 */
class Requests {
public:
    void undo();
    int cap =30;
    /**
     * @brief Default constructor for the Requests class.
     *
     * @param reader An instance of the Read class for reading student and class data.
     */
    Requests(Read reader);
    /**
     * @brief Default constructor for the Requests class.
     */
    Requests();
    /**
     * @brief Check for class schedule overlaps when enrolling in a new class.
     *
     * This function checks if there are any schedule overlaps between the student's existing classes and a new class.
     *
     * @param StudentCode The unique code of the student.
     * @param ucCode The code of the UC (subject) the student wants to enroll in.
     * @param newClassCode The code of the new class the student wants to enroll in.
     * @return True if there are no schedule overlaps; false otherwise.
     */
    bool cheekClassOverlap(int StudentCode, std::string ucCode, std::string newClassCode);
    /**
     * @brief Switch a student's class within the same UC (subject).
     *
     * This function switches a student's class within the same UC (subject) if conditions are met, updating enrollment records.
     *
     * @param StudentCode The unique code of the student.
     * @param ucCode The code of the UC (subject).
     * @param newClassCode The code of the new class.
     */
    void switchClass( int StudentCode, std::string ucCode, std::string newClassCode);
    /**
     * @brief Check if there is a vacancy for a student in a new class.
     *
     * This function checks if there is a vacancy in the new class for a student to enroll, considering occupancy limits.
     *
     * @param ucCode The code of the UC (subject).
     * @param oldClassCode The code of the old class.
     * @param newClassCode The code of the new class.
     * @return True if there is a vacancy; false if the occupancy limit is reached.
     */
    bool vacancy(std::string& ucCode, string oldClassCode, std::string& newClassCode);
    /**
     * @brief Check if the new class has the capacity to accommodate a student.
     *
     * This function checks if the new class has available capacity to accommodate a student, considering occupancy limits.
     *
     * @param ucCode The code of the UC (subject).
     * @param newClassCode The code of the new class.
     * @return True if there is capacity; false if the class is full.
     */
    bool capacity (string ucCode, string newClassCode);
    /**
     * @brief Add a new UC (subject) to a student's enrollment.
     *
     * This function adds a new UC to a student's enrollment if conditions are met and updates the enrollment records.
     *
     * @param StudentCode The unique code of the student.
     * @param ucCode The code of the UC (subject) to add.
     * @param newClassCode The code of the new class associated with the UC.
     * @return True if the UC is successfully added; false otherwise.
     */
    bool addUC(int StudentCode,  std::string ucCode,  std::string newClassCode);
    /**
     * @brief Remove a UC (subject) from a student's enrollment.
     *
     * This function removes a UC from a student's enrollment and updates the enrollment records.
     *
     * @param StudentCode The unique code of the student.
     * @param ucCode The code of the UC (subject) to remove.
     * @return True if the UC is successfully removed; false otherwise.
     */
    bool removeUC(int StudentCode,  string ucCode);
    /**
     * @brief Switch a student's UC (subject) and class.
     *
     * This function switches a student's UC and class, updating enrollment records and checking for schedule conflicts.
     *
     * @param StudentCode The unique code of the student.
     * @param ucCode The code of the UC (subject) to switch from.
     * @param newClassCode The code of the new class to switch to.
     * @param newUCCode The code of the new UC (subject) to switch to.
     */
    void switchUC(int StudentCode, string ucCode, string newClassCode, const std::string& newUCCode);
    /**
     * @brief Retrieve the list of classes in which a student is enrolled.
     *
     * This function returns a vector of class objects representing the classes in which a student is currently enrolled.
     *
     * @param StudentCode The unique code of the student.
     * @return A vector of Classes objects representing the student's enrolled classes.
     */
    vector<Classes> getStudentClasses(int StudentCode);
    /**
    * @brief Retrieve the schedule slots of a class in a given UC.
    *
    * This function returns a vector of Slot objects representing the schedule slots of a class in a specific UC (subject).
    *
    * @param ClassCode The code of the class.
    * @param UcCode The code of the UC (subject) containing the class.
    * @return A vector of Slot objects representing the class's schedule slots.
    */
    vector<Slot> getClassSlots(std::string ClassCode, std::string UcCode);
    std::stack<Action> acceptedRequests; /**< Stack for accepted requests */
    std::stack<Action> rejectedRequests;  /**< Stack for rejected requests */
    stack<Action> getAcceptRequests();/**< Get the stack of accepted requests */
    /**
     * @brief Function to convert ActionType enum to a string.
     * @param type The ActionType enum value.
     * @return A string representing the ActionType.
     */
    string actionTypeToString(ActionType type);
    /**
     * @brief Function to save the stack of accepted requests to a file.
     */
    void saveStack();
    /**
     * @brief Function to convert a string to ActionType enum.
     * @param type The string representing the ActionType.
     * @return An ActionType enum value.
     */
    ActionType actionTypeToEnum(string type);
    /**
     * @brief Function to load the stack of accepted requests from a file.
     */
    void loadStack();

};

#endif




#endif //PROJETO_AED_REQUESTS_H
