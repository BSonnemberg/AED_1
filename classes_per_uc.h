#ifndef PROJETO_AED_CLASSES_PER_UC_H
#define PROJETO_AED_CLASSES_PER_UC_H
#include <string>
using namespace std;


class classes_per_uc {
    private:
        string UcCode,ClassCode;
    public:
        classes_per_uc(string UcCode, string ClassCode);

        string getUcCode();
        string getClassCode();
};


#endif //PROJETO_AED_CLASSES_PER_UC_H
