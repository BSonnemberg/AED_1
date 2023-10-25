#include "Read.h"
#include <iostream>
#include "Classes.h"
using namespace std;

int main() {
    Read reader;
    reader.Read_Classes();
    std::vector<Classes> aux = reader.getClass();
    for(size_t i = 0; i < aux.size(); i++)
        cout << aux[i].getClassCode();
    return 0;
}
