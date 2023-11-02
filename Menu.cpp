//
// Created by Marta on 31/10/2023.
//

#include <limits>
#include "Menu.h"

Menu::Menu() {}



void Menu::firstMenu(){
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
                  << "8 - Exit" << std::endl;
        std::cout << "Please insert a number: ";

        std::cin >> option;

        if (std::cin.fail()) {
            std::cin.clear(); // Limpa o estado de erro
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
                    std::cout << "Exiting the program. Goodbye!" << std::endl;
                    return; // Encerra o programa
                default:
                    std::cout << "Choose a valid number." << std::endl;
                    break;
            }
        }
    } while (option != 7);

}

void Menu::menuStudentSchedule() {
    int StudentCode;
    Schedule schedule;
    cout << "Please insert the student's code: ";
    cin >> StudentCode;
    schedule.printStudentSchedule(StudentCode);


}

void Menu::menuClassSchedule() {
    string ClassCode;
    Schedule schedule;
    cout << "Please insert the Class Code: ";
    cin >> ClassCode;
    schedule.printClassSchedule(ClassCode);
}

void Menu::menuUcSchedule() {
    string  UcCode;
    Schedule schedule;
    cout << "Please insert the UC code: ";
    cin >> UcCode;
    schedule.printUcSchedule(UcCode);
}

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