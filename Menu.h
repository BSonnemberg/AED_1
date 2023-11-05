#ifndef PROJETO_AED_MENU_H
#define PROJETO_AED_MENU_H
#include <iostream>
#include "Schedule.h"
#include "Requests.h"
using namespace std;
/**
 * @class Menu
 * @brief Class for managing a menu-driven program with various options.
 */
class Menu {
    public:
    /**
     * @brief Default constructor for the Menu class.
     */
        Menu();

        /**
         * @brief Display and manage the first menu with various options.
         */
        void firstMenu();

        /**
         * @brief Display the menu for printing a student's schedule.
         */
        void menuStudentSchedule();

        /**
         * @brief Display the menu for printing a class's schedule.
         */
        void menuClassSchedule();

        /**
         * @brief Display the menu for printing a UC's schedule.
         */
        void menuUcSchedule();

        /**
         * @brief Display the menu for printing students of a given UC.
         */
        void menuStudentUC();

        /**
         * @brief Display the menu for printing students of a given class.
         */
        void menuStudentClass();

        /**
         * @brief Display the menu for printing students of a given Class and UC.
         */
        void menuStudentClassUC();

        /**
         * @brief Display the menu for changing a student's Class for a given UC.
         */
        void menuChangeClass();

        /**
         * @brief Display the menu for adding a new UC for a student.
         */
        void menuAddUc();

        /**
         * @brief Display the menu for removing a UC from a student.
         */
        void menuRemoveUc();

        /**
         * @brief Display the menu for switching a student's UC and Class.
         */
        void menuSwitchUC();
        /**
         * @brief Perform an undo operation in the menu.
         */
        void menuUndo();
        Requests getRequests();

    private:
        Read reader;
        Requests requests;
};


#endif //PROJETO_AED_MENU_H
