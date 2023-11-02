//
// Created by Marta on 01/11/2023.
//

#include "Classes_Uc.h"




Classes_Uc::Classes_Uc(std::string UcCode, std::string ClassCode) {
    this->UcCode = UcCode;
    this->ClassCode = ClassCode;
}

string Classes_Uc::getUcCode() {
    return UcCode;
}

string Classes_Uc::getClassCode() {
    return ClassCode;
}
