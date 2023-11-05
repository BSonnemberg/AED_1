#ifndef PROJETO_AED_CLASSES_UC_H
#define PROJETO_AED_CLASSES_UC_H

#include <string>
using namespace std;

/**
 * @brief The Classes_Uc class represents the association between a course and a class.
 */
class Classes_Uc {
private:
    string UcCode; /**< The code of the associated course. */
    string ClassCode; /**< The code of the class. */
public:
    /**
     * @brief Constructor for the Classes_Uc class.
     * @param UcCode The code of the associated course.
     * @param ClassCode The code of the class.
     */
    Classes_Uc(string UcCode, string ClassCode);

    /**
     * @brief Get the code of the associated course.
     * @return The code of the associated course.
     */
    string getUcCode();

    /**
     * @brief Get the code of the class.
     * @return The code of the class.
     */
    string getClassCode();
};

#endif // PROJETO_AED_CLASSES_UC_H