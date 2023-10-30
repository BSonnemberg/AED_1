#include "classes_per_uc.h"

classes_per_uc::classes_per_uc(std::string UcCode, std::string ClassCode) {
    this->UcCode = UcCode;
    this->ClassCode = ClassCode;
}

string classes_per_uc::getUcCode() {
    return UcCode;
}

string classes_per_uc::getClassCode() {
    return ClassCode;
}
