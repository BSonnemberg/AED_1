#include <limits>
#include "Menu.h"
/**
 * @brief Constructor for Menu class.
 */
Menu::Menu() {
    this->requests=Requests (this->reader);
}

/**
 * @brief Display and manage the first menu with various options.
 */
void Menu::firstMenu(){
    requests.loadStack();
    int option;
    do {
        std::cout << '\n' << "--------------------Menu--------------------" << std::endl;
        std::cout << "1 - Print the schedule of a student" << std::endl
                  << "2 - Print the schedule of a class" << std::endl
                  << "3 - Print the schedule of a UC" << std::endl
                  << "4 - Print the students of a given UC" << std::endl
                  << "5 - Print the students of a given Class" << std::endl
                  << "6 - Print the students of a given Class and UC" << std::endl
                  << "7 - Change the student Class of a given UC" << endl
                  << "8 - Add  UC" << endl
                  << "9 - Remove UC" << endl
                  << "10 - Switch UC" << endl
                  << "11 - Undo last move" << endl
                  << "12 - Exit" << std::endl;
        std::cout << "Please insert a number: ";

        std::cin >> option;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descarta a entrada inválida
            std::cout << "Invalid input. Please enter a valid number." << std::endl;
        } else {
            switch (option) {
                case 1:
                    menuStudentSchedule();
                    break;
                case 2:
                    menuClassSchedule();
                    break;
                case 3:
                    menuUcSchedule();
                    break;
                case 4:
                    menuStudentUC();
                    break;
                case 5:
                    menuStudentClass();
                    break;
                case 6:
                    menuStudentClassUC();
                    break;
                case 7:
                    menuChangeClass();
                    break;
                case 8:
                    menuAddUc();
                    break;
                case 9:
                    menuRemoveUc();
                    break;
                case 10:
                    menuSwitchUC();
                    break;
                case 11:
                    menuUndo();
                    break;
                case 12:
                    std::cout << "Exiting the program. Goodbye!" << std::endl;
                    requests.saveStack();
                    return;
                default:
                    std::cout << "Choose a valid number." << std::endl;
                    break;
            }
        }
    } while (option != 12);

}
/**
 * @brief Display the menu for printing a student's schedule.
 */
void Menu::menuStudentSchedule() {
    int StudentCode;
    Schedule schedule;
    cout << "Please insert the student's code: ";
    cin >> StudentCode;
    schedule.printStudentSchedule(StudentCode);


}
/**
 * @brief Display the menu for printing a class's schedule.
 */
void Menu::menuClassSchedule() {
    string ClassCode;
    Schedule schedule;
    cout << "Please insert the Class Code: ";
    cin >> ClassCode;
    schedule.printClassSchedule(ClassCode);
}
/**
 * @brief Display the menu for printing a UC's schedule.
 */
void Menu::menuUcSchedule() {
    string  UcCode;
    Schedule schedule;
    cout << "Please insert the UC code: ";
    cin >> UcCode;
    schedule.printUcSchedule(UcCode);
}
/**
 * @brief Display the menu for printing students of a given UC.
 */
void Menu::menuStudentUC() {
    string UcCode;
    string sorting;
    Schedule schedule;
    cout << "Please insert the UC code: ";
    cin >> UcCode;
    cout << "1 - Alphabetical"<< endl;
    cout << "2 - Numerical" << endl;
    cout << "In which order do you want to print the students?" << endl;
    int option;
    cin >> option;
    while(option < 1 || option > 4){
        cout << ">> Please choose a valid option: "; cin >> option; cout << endl;
    }
    if(option==1){
        sorting = "Alphabetical";
    }
    else{
        sorting = "Numerical";
    }
    schedule.printStudentUc(UcCode, sorting);
}
/**
 * @brief Display the menu for printing students of a given class.
 */
void Menu::menuStudentClass() {
    string ClassCode;
    string sorting;
    Schedule schedule;
    cout << "Please insert the Class code: ";
    cin >> ClassCode;
    cout << "1 - Alphabetical"<< endl;
    cout << "2 - Numerical" << endl;
    cout << "In which order do you want to print the students?" << endl;
    int option;
    cin >> option;
    while(option < 1 || option > 4){
        cout << ">> Please choose a valid option: "; cin >> option; cout << endl;
    }
    if(option==1){
        sorting = "Alphabetical";
    }
    else{
        sorting = "Numerical";
    }
    schedule.printStudentClass(ClassCode,sorting);
}
/**
 * @brief Display the menu for printing students of a given Class and UC.
 */
void  Menu::menuStudentClassUC() {
    string UcCode;
    string ClassCode;
    string sorting;
    Schedule schedule;
    cout << "Please insert the Class code: ";
    cin >> ClassCode;
    cout << "Please insert the UC code: ";
    cin >> UcCode;

    cout << "1 - Alphabetical"<< endl;
    cout << "2 - Numerical" << endl;
    cout << "In which order do you want to print the students?" << endl;
    int option;
    cin >> option;
    while(option < 1 || option > 4){
        cout << ">> Please choose a valid option: "; cin >> option; cout << endl;
    }
    if(option==1){
        sorting = "Alphabetical";
    }
    else{
        sorting = "Numerical";
    }
    schedule.printStudentClassUc(UcCode,ClassCode,sorting);
}
/**
 * @brief Display the menu for changing a student's Class for a given UC.
 */
void Menu::menuChangeClass() {
    int StudentCode;
    std::string ucCode;
    std::string newClassCode;

    cout << "Please insert the student code: ";
    cin >> StudentCode;

    cout << "Please insert the UC Code: ";
    cin >> ucCode;

    cout << "Please insert the New Class Code: ";
    cin >> newClassCode;

    this->requests.switchClass(StudentCode,ucCode,newClassCode);
}
/**
 * @brief Display the menu for adding a new UC for a student.
 */
void Menu::menuAddUc() {
    int StudentCode;
    std::string ucCode;
    std::string newClassCode;
    cout << "Please insert the student code: ";
    cin >> StudentCode;
    cout << "Please insert the new UC Code: ";
    cin >> ucCode;
    cout << "Please insert the new Class Code: ";
    cin >> newClassCode;

    this->requests.addUC(StudentCode,ucCode,newClassCode);

}
/**
 * @brief Display the menu for removing a UC from a student.
 */
void Menu::menuRemoveUc() {
    int StudentCode;
    string ucCode;
    cout << "Please insert the student code: ";
    cin >> StudentCode;
    cout << "Please insert the ucCode: ";
    cin >> ucCode;
    this->requests.removeUC(StudentCode,ucCode);
}
/**
 * @brief Display the menu for switching a student's UC and Class.
 */
void Menu::menuSwitchUC() {
    int StudentCode;
    string ucCode;
    string newClassCode;
    string newUCCode;
    cout << "Please insert the student code: ";
    cin >> StudentCode;
    cout << "Please insert the ucCode: ";
    cin >> ucCode;
    cout << "Please insert the new Class Code: ";
    cin >> newClassCode;
    cout << "Please insert the new UC Code: ";
    cin >> newUCCode;

    this->requests.switchUC(StudentCode,ucCode,newClassCode, newUCCode);


}
/**
 * @brief Perform an undo operation in the menu.
 *
 * This function is responsible for undoing the last action executed in the menu, if possible.
 * It uses the `Requests` class to manage undo operations.
 */
void Menu::menuUndo() {
    this->requests.undo();
}

/**
 * @brief Get the Requests object associated with the Menu.
 * @return Requests object.
 */

Requests Menu::getRequests(){
    return requests;
}