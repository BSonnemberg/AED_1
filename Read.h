/**
 * @file Read.h
 * @brief This header file defines the Read class, which is responsible for reading and managing class and student data.
 *
 * The Read class provides methods for reading and manipulating class, student, and UC (University Course) data.
 */

#ifndef PROJETO_AED_READ_H
#define PROJETO_AED_READ_H
#include "Classes.h"
#include "Student.h"
#include "Classes_Uc.h"
/**
 * @class Read
 * @brief This class handles reading and managing class, student, and UC data.
 */

class Read {
    private:
        vector<Classes> lesson;
        vector<Student> students;
        vector<Classes_Uc> classesPerUc;

    public:
        /**
         * @brief Read class information from a CSV file and store it in the 'lesson' vector.
         */
        void Read_Classes();
        /**
         * @brief Get the 'lesson' vector containing class information.
         * @return Vector of Classes objects.
         */
        vector<Classes> getClassvector();
        /**
         * @brief Read student information from a CSV file and store it in the 'students' vector.
         */
        void Read_Student();
        /**
         * @brief Get the 'students' vector containing student information.
         * @return Vector of Student objects.
         */
        vector<Student> getStudentvector();
        /**
         * @brief Update the class associated with a student's UC (University Course).
         * @param studentCode The code of the student to update.
         * @param ucCode The UC code to update.
         * @param newClassCode The new class code to associate with the student's UC.
         */
        void updateStudentClass(int studentCode, string  ucCode, string newClassCode);
        /**
         * @brief Read class information per UC from a CSV file and store it in the 'classesPerUc' vector.
         */
        void Read_Classes_Per_Uc();
        /**
         * @brief Get the 'classesPerUc' vector containing class information per UC.
         * @return Vector of Classes_Uc objects.
         */
        vector<Classes_Uc> getClassesPerUcvector();
        /**
         * @brief Add a new student class entry to the 'students_classes.csv' file.
         * @param studentCode The code of the student to add.
         * @param studentName The name of the student to add.
         * @param ucCode The UC code to associate with the student.
         * @param classCode The class code to associate with the UC.
         */
        void addStudentClass(int studentCode, const std::string& studentName, const std::string& ucCode, const std::string& classCode);
        /**
         * @brief Remove a student class entry from the 'students_classes.csv' file.
         * @param studentCode The code of the student to remove.
         * @param studentName The name of the student to remove.
         * @param ucCode The UC code to disassociate from the student.
         * @param classCode The class code to disassociate from the UC.
         */
        void removeStudentClass(int studentCode, string ucCode, string classCode);
        /**
         * @brief Compare student codes for sorting purposes.
         * @param a First Student object to compare.
         * @param b Second Student object to compare.
         * @return True if the code of Student 'a' is less than the code of Student 'b', false otherwise.
         */
        bool compareStudentCodes(Student a, Student b);
        /**
         * @brief Sort students by their codes.
         * @param students Vector of Student objects to be sorted.
         */
        void sortStudentsByCode(std::vector<Student>& students);
        /**
         * @brief Convert a weekday string to a corresponding numeric representation.
         * @param day The weekday string (e.g., "Monday", "Tuesday").
         * @return Numeric representation of the weekday (1 for Monday, 2 for Tuesday, and so on).
         *         Returns 0 in case of an error or an invalid day.
         */

        int weekdayToNumber(const std::string& day);
        /**
         * @brief Sort the 'aula' vector of Classes objects by weekday and start hour.
         *
         * This function sorts the input vector 'aula' based on the weekday and start hour of each class.
         *
         * @param aula A vector of Classes objects to be sorted.
         */
        void sortClassesByWeekdayAndStartHour(std::vector<Classes>& aula);





};


#endif //PROJETO_AED_READ_H
