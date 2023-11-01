#include "Read.h"
#include <iostream>
#include "Classes.h"

#include "Schedule.h"
#include "Menu.h"

#include "classes_per_uc.h"

using namespace std;

int main() {

    Menu menu;
    menu.firstMenu();







    reader.Read_classes_per_uc();
    vector<classes_per_uc> aux2 =reader.getClassesPerUCvector();

    cout << '\n' << aux2[0].getUcCode()<< '\n';
    cout << aux2[0].getClassCode()<< '\n';

    return 0;
}
