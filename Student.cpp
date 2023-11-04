#include "Student.h"

Student::Student(int StudentCode, std::string StudentName, std::string UcCode, std::string ClassCode) {
    this->StudentCode= StudentCode;
    this->StudentName = StudentName;
    this->UcCode = UcCode;
    this->ClassCode = ClassCode;
}

int Student::getStudentCode() {
    return StudentCode;
}

string Student::getStudentName() {
    return StudentName;
}

string Student::getUcCode() {
    return UcCode;
}

string Student::getClassCode() {
    return ClassCode;
}
void Student::setClassCode(string& newClassCode){
    ClassCode = newClassCode;
}



