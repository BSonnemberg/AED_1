#include "Read.h"
#include <iostream>
#include "Classes.h"

#include "Schedule.h"
#include "Menu.h"

#include "Classes_Uc.h"
#include "Requests.h"

using namespace std;

int main() {

    /*Menu menu;
    menu.firstMenu();*/

    Read reader;
    Requests requests(reader);
    requests.switchClass(202025232, "L.EIC002",  "1LEIC05");










}
