
#ifndef PROJETO_AED_STUDENT_H
#define PROJETO_AED_STUDENT_H
#include <string>
using namespace std;

/**
 * @class Student
 * @brief Represents a student with information such as student code, name, course code, and class code.
 */

class Student {
    private:
    int StudentCode; /**< The unique code of the student. */
    std::string StudentName; /**< The name of the student. */
    std::string UcCode; /**< The code of the course associated with the student. */
    std::string ClassCode; /**< The code of the class the student is enrolled in. */
    public:
        /**
         * @brief Constructor for the Student class.
         *
         * Initializes a Student object with the provided information.
         *
         * @param StudentCode The unique code of the student.
         * @param StudentName The name of the student.
         * @param UcCode The code of the course associated with the student.
         * @param ClassCode The code of the class the student is enrolled in.
         */
        Student(int StudentCode, string StudentName, string UcCode, string ClassCode);

        Student();
        /**
        * @brief Get the unique code of the student.
        *
        * @return The unique code of the student as an integer.
        */
        int getStudentCode();
        /**
         * @brief Get the name of the student.
         *
         * @return The name of the student as a string.
         */
        string getStudentName();
        /**
         * @brief Get the code of the course associated with the student.
         *
         * @return The code of the course as a string.
         */
        string getUcCode();
        /**
         * @brief Get the code of the class the student is enrolled in.
         *
         * @return The code of the class as a string.
         */
        string getClassCode();
        /**
         * @brief Set the code of the class the student is enrolled in.
         *
         * @param newClassCode The new class code to set for the student.
         */
        void setClassCode(string& newClassCode);
        /**
        * @brief Sets the UC (subject) code for the object.
        *
        * This method updates the UC code for the object.
        *
        * @param ucCode The UC code to set for the object.
        */
        void setUcCode(string& ucCode);


};


#endif //PROJETO_AED_STUDENT_H
