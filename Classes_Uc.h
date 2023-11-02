#ifndef PROJETO_AED_CLASSES_UC_H
#define PROJETO_AED_CLASSES_UC_H
#include <string>
using namespace std;


class Classes_Uc {
private:
    string UcCode, ClassCode;
public:
    Classes_Uc(string UcCode, string ClassCode);
    string getUcCode();
    string getClassCode();

};


#endif //PROJETO_AED_CLASSES_UC_H
