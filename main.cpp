#include "Read.h"
#include <iostream>
#include "Classes.h"
using namespace std;

int main() {
    Read reader;
    reader.Read_Classes();
    std::vector<Classes> aux = reader.getClass();

    cout << aux[0].getClassCode() << '\n';
    cout << aux[0].getUcCode() << '\n';
    cout << aux[0].getWeekday()<< '\n';
    cout << aux[0].getStartHour()<< '\n';
    cout << aux[0].getDuration()<< '\n';
    cout << aux[0].getType()<< '\n';




    return 0;
}
