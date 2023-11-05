#include "Classes_Uc.h"

/**
 * @brief Constructor for the Classes_Uc class.
 * @param UcCode The code of the associated course.
 * @param ClassCode The code of the class.
 */
Classes_Uc::Classes_Uc(std::string UcCode, std::string ClassCode) {
    this->UcCode = UcCode;
    this->ClassCode = ClassCode;
}

/**
 * @brief Get the code of the associated course.
 * @return The code of the associated course.
 */
string Classes_Uc::getUcCode() {
    return UcCode;
}

/**
 * @brief Get the code of the class.
 * @return The code of the class.
 */
string Classes_Uc::getClassCode() {
    return ClassCode;
}