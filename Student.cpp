#include "Student.h"
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
Student::Student(int StudentCode, std::string StudentName, std::string UcCode, std::string ClassCode) {
    this->StudentCode= StudentCode;
    this->StudentName = StudentName;
    this->UcCode = UcCode;
    this->ClassCode = ClassCode;
}
/**
 * @brief Get the unique code of the student.
 *
 * @return The unique code of the student as an integer.
 */
int Student::getStudentCode() {
    return StudentCode;
}
/**
 * @brief Get the name of the student.
 *
 * @return The name of the student as a string.
 */
string Student::getStudentName() {
    return StudentName;
}
/**
 * @brief Get the code of the course associated with the student.
 *
 * @return The code of the course as a string.
 */
string Student::getUcCode() {
    return UcCode;
}
/**
 * @brief Get the code of the class the student is enrolled in.
 *
 * @return The code of the class as a string.
 */
string Student::getClassCode() {
    return ClassCode;
}
/**
 * @brief Set the code of the class the student is enrolled in.
 *
 * @param newClassCode The new class code to set for the student.
 */
void Student::setClassCode(string& newClassCode){
    ClassCode = newClassCode;
}
/**
 * @brief Set the UC (subject) code for the student.
 *
 * This function sets the UC code for the student.
 *
 * @param ucCode The UC code to set for the student.
 */

void Student::setUcCode(string& ucCode){
    UcCode = ucCode;
}

