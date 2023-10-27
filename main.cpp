#include "Read.h"
#include <iostream>
#include "Classes.h"
using namespace std;

int main() {
    Read reader;
    reader.Read_Classes();
    vector<Classes> aux = reader.getClassvector();

    cout << aux[0].getClassCode() << '\n';
    cout << aux[0].getUcCode() << '\n';
    cout << aux[0].getWeekday()<< '\n';
    cout << aux[0].getStartHour()<< '\n';
    cout << aux[0].getDuration()<< '\n';
    cout << aux[0].getType()<< '\n';


    reader.Read_Student();
    vector<Student> aux1=reader.getStudentvector();

    cout << '\n' << aux1[0].getStudentCode() << '\n';
    cout << aux1[0].getStudentName() << '\n';
    cout << aux1[0].getUcCode()<< '\n';
    cout << aux1[0].getClassCode()<< '\n';





    return 0;
}
