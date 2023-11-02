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


    requests.switchUC(202031607,"L.EIC004","1LEIC05","L.EIC002");










}
