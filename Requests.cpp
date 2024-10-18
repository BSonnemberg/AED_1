#include "Requests.h"
#include <algorithm>
#include <fstream>
#include <sstream>

/**
 * @brief Constructor for the Requests class.
 * @param reader An instance of the Read class for reading and managing class and student data.
 */
Requests::Requests(Read reader) {}
/**
 * @brief Default constructor for the Requests class.
 */
Requests::Requests() {}
/**
 * @brief Check for class schedule overlaps for a student's enrollment in a new class.
 *
 * This function checks if enrolling a student in a new class with a specified UC (subject)
 * causes a schedule overlap with their current enrolled classes.
 *
 * @param StudentCode The unique identifier of the student.
 * @param ucCode The UC (subject) code for the new class.
 * @param newClassCode The code of the new class the student wants to enroll in.
 * @return True if no schedule overlap occurs, False if there is an overlap.
 */
 //Complexity: O(n * m)
bool Requests::cheekClassOverlap(int StudentCode, std::string ucCode, std::string newClassCode){

    std::vector<Classes> students_classes= this->getStudentClasses(StudentCode);

    std::vector<Slot> DestClasses_Slot= this->getClassSlots(newClassCode,ucCode);
    for( Classes class_slots:students_classes){
        if(class_slots.getUcCode()!=ucCode){
            Slot ActualSlot = Slot(class_slots.getWeekday(),class_slots.getStartHour(), class_slots.getDuration(), class_slots.getType());
            for(Slot DestSlot : DestClasses_Slot){
                if(DestSlot.overlaps(ActualSlot)){
                    return false;
                }
            }
        }
    }
    return true;
}
/**
 * @brief Get a list of classes associated with a specific student.
 *
 * This function retrieves a list of classes in which a specific student is currently enrolled.
 *
 * @param StudentCode The unique identifier of the student.
 * @return A vector containing the classes associated with the student.
 */
//Complexity: O(m * n)
vector<Classes> Requests::getStudentClasses(int StudentCode){
    Read reader;
    reader.Read_Student();
    reader.Read_Classes();
    vector<Classes> aux;
    std::vector<Student> students = reader.getStudentvector();
    std::vector<Classes> classes = reader.getClassvector();

    for (Student student: students) {
        if(StudentCode==student.getStudentCode()){
            for(Classes class_: classes) {
                if(class_.getClassCode()==student.getClassCode() && class_.getUcCode()==student.getUcCode()){
                    aux.push_back(class_);
                }

            }
        }
    }
    return aux;
}
/**
 * @brief Get the time slots for a specific class with a given ClassCode and UcCode (subject code).
 *
 * This function retrieves the time slots (schedule) for a specific class identified by its ClassCode
 * and UcCode (subject code).
 *
 * @param ClassCode The unique identifier for the class.
 * @param UcCode The code of the UC (subject) to which the class belongs.
 * @return A vector containing the time slots (schedule) for the specified class.
 */

vector<Slot> Requests::getClassSlots(std::string ClassCode, std::string UcCode){
    Read reader;
    reader.Read_Classes();
    vector<Slot> aux;
    std::vector<Classes> classes = reader.getClassvector();

    for (Classes class_: classes){
        if(class_.getUcCode()==UcCode && class_.getClassCode()==ClassCode){
            Slot slot=Slot(class_.getWeekday(), class_.getStartHour(), class_.getDuration(), class_.getType());
            aux.push_back(slot);
        }

    }
    return aux;
}
/**
 * @brief Check if there is a vacancy for a student to switch from an old class to a new class.
 *
 * This function checks if there is a vacancy in the new class compared to the old class for a specific UC (University Course).
 *
 * @param ucCode The UC code for which the switch is requested.
 * @param oldClassCode The code of the old class.
 * @param newClassCode The code of the new class.
 * @return True if there is a vacancy to switch to the new class; otherwise, false.
 */

bool Requests::vacancy(std::string& ucCode, string oldClassCode, std::string& newClassCode) {
    Read reader;
    reader.Read_Student();
    std::vector<Student> students = reader.getStudentvector();
    int maxOccupancyDifference = 4; // Máxima diferença de ocupação permitida

    int oldClassOccupancy = -1;
    int newClassOccupancy = +1;



    // Contar o número de alunos na turma antiga
    for (Student& student : students) {
        if (student.getUcCode() == ucCode && student.getClassCode() == oldClassCode) {
            oldClassOccupancy++;
        }
    }

    // Contar o número de alunos na turma nova
    for (Student& student : students) {
        if (student.getUcCode() == ucCode && student.getClassCode() == newClassCode) {
            newClassOccupancy++;
        }
    }

    int differenceWithOldClass = newClassOccupancy - oldClassOccupancy;

    if(differenceWithOldClass < 0){
        return true;
    }

    if (abs(differenceWithOldClass)> maxOccupancyDifference) {
        return false;
    }

    return true;
}
/**
 * @brief Switch a student's class for a specific UC.
 *
 * This function allows a student to switch from their current class to a new class within the same UC, provided there is a vacancy and the new class is within capacity.
 *
 * @param StudentCode The code of the student requesting the switch.
 * @param ucCode The UC code for which the switch is requested.
 * @param newClassCode The code of the new class.
 */
    void Requests::switchClass(int StudentCode, std::string ucCode, std::string newClassCode) {
        Action action;
        action.type = ActionType::switchClass ;
        action.studentCode=StudentCode;
        action.ucCode = ucCode;
        action.newClassCode=newClassCode;
        action.description= "Switch";
        Read reader;
        reader.Read_Student();
        std::vector<Student> students = reader.getStudentvector();

        bool studentFound = false;
        bool checkOverlap=false;


        for (Student student: students) {

            if (student.getStudentCode() == StudentCode && student.getUcCode() == ucCode) {
                studentFound = true;

                if (student.getClassCode() == newClassCode) {

                    rejectedRequests.push(action);
                    std::cout << "The student " << student.getStudentName() << " is already in the class "
                              << newClassCode << "." << std::endl;
                } else {
                    checkOverlap=this->cheekClassOverlap(StudentCode, ucCode, newClassCode);
                    if (vacancy(ucCode, student.getClassCode(), newClassCode) && capacity(ucCode, newClassCode) && checkOverlap){
                        action.classCode=student.getClassCode();
                        student.setClassCode(newClassCode);
                        acceptedRequests.push(action);
                        std::cout << "The student " << student.getStudentName() << " was transferred to the class "
                                  << newClassCode << "." << std::endl;
                        reader.updateStudentClass(StudentCode, ucCode, newClassCode);
                    } else if (!vacancy(ucCode, student.getClassCode(), newClassCode)) {
                        rejectedRequests.push(action);
                        std::cout << "The change causes imbalance in classes" << std::endl;
                    }  else {
                        if (checkOverlap==false){
                            rejectedRequests.push(action);
                            cout<<"There is a schedule conflit";
                        }
                        else{
                            rejectedRequests.push(action);
                            cout << "There are no vacancies in the class!";
                        }
                    }

                }

                break;
            }

        }
        if (!studentFound) {
            std::cout << "Student not found." << std::endl;
        }

    }
/**
 * @brief Check if there is capacity in the new class for a specific UC.
 *
 * This function checks if there is capacity in the new class for a specific UC, considering the maximum occupancy limit.
 *
 * @param ucCode The UC code for which the capacity check is performed.
 * @param newClassCode The code of the new class.
 * @return True if there is capacity in the new class; otherwise, false.
 */
bool Requests::capacity(std::string ucCode, std::string newClassCode) {
    Read reader;
    reader.Read_Student();
    std::vector<Student> students = reader.getStudentvector();
    int newClassOccupancy = 1;
    int cap = 30;

    for (Student& student : students) {
        if (student.getUcCode() == ucCode && student.getClassCode() == newClassCode) {
            newClassOccupancy++;
        }
    }

    if (newClassOccupancy > cap){
        return false;
    }
    return true;

}

/**
 * @brief Add a new UC (University Course) for a student.
 *
 * This function allows a student to add a new UC to their schedule, considering the maximum number of UCs and vacancy in the new UC.
 *
 * @param StudentCode The code of the student to add the UC.
 * @param ucCode The code of the UC to be added.
 * @param newClassCode The code of the class associated with the new UC.
 * @return True if the UC was added successfully; otherwise, false.
 */
bool Requests::addUC(int StudentCode, std::string ucCode,  std::string newClassCode) {
    Action action;
    action.type = ActionType::AddUC;
    action.studentCode=StudentCode;
    action.ucCode = ucCode;
    action.classCode=newClassCode;
    action.description= "Added UC " + ucCode + " to the student " + std::to_string(StudentCode);
    Read reader;
    reader.Read_Student();
    std::vector<Student> students = reader.getStudentvector();
    int ucCount = 0;
    string studentName;
    bool checkOverlap=false;

    for (Student student : students) {

        if (student.getStudentCode() == StudentCode) {
            studentName = student.getStudentName();

            if(student.getUcCode()==ucCode) {
                rejectedRequests.push(action);
                cout << "Student is already registered for the specified UC.";
                return false;
            }

        ucCount++;

        }
    }


    if (ucCount >= 7) {
        rejectedRequests.push(action);
        std::cout << "The student is already registered in 7 UCs. Cannot add more." << std::endl;
        return false;
    }
    checkOverlap=this->cheekClassOverlap(StudentCode, ucCode, newClassCode);

    if (checkOverlap==false){
        rejectedRequests.push(action);
        cout<<"There is a schedule conflit";
        return false;
    }
    else if (!capacity( ucCode, newClassCode)) {
        rejectedRequests.push(action);
        std::cout << "No vacancy in the new UC. Cannot add." << std::endl;
        return false;
    }

    else {
        acceptedRequests.push(action);
        reader.addStudentClass(StudentCode, studentName, ucCode, newClassCode);
        std::cout << "UC " << ucCode << " added to student " << StudentCode << "." << std::endl;

        return true;
    }
}
/**
 * @brief Remove a UC (University Course) from a student's schedule.
 *
 * This function allows the removal of a UC from a student's schedule, updating the student's class information.
 *
 * @param StudentCode The code of the student from whom the UC will be removed.
 * @param ucCode The code of the UC to be removed.
 * @return True if the UC was successfully removed; otherwise, false.
 */
bool Requests::removeUC(int StudentCode, string ucCode) {
    Action action;
    action.type = ActionType::RemoveUC;
    action.studentCode=StudentCode;
    action.ucCode = ucCode;
    action.description= "Remove";
    Read reader;
    reader.Read_Student();
    std::vector<Student> students = reader.getStudentvector();
    bool found = false;
    string studentName;
    string classCode;

    for (Student& student : students) {

        if (student.getStudentCode() == StudentCode && student.getUcCode() == ucCode ) {
            action.name= student.getStudentName();
            classCode =student.getClassCode();
            action.classCode = student.getClassCode();

            found = true;
            acceptedRequests.push(action);
            std::cout << "UC " << ucCode << " removed from student " << StudentCode << "." << std::endl;
            reader.removeStudentClass(StudentCode,ucCode, classCode);

            return true;
        }
        std::cout << "UC not found for the student." << std::endl;
        rejectedRequests.push(action);
        return false;
    }

    // Remover a UC do aluno e atualizar o arquivo "students_classes.csv".
    acceptedRequests.push(action);
    std::cout << "UC " << ucCode << " removed from student " << StudentCode << "." << std::endl;
    reader.removeStudentClass(StudentCode,ucCode, classCode);



    return true;
}
/**
 * @brief Switch a student from one UC to another UC within the same class.
 *
 * This function allows a student to switch from one UC to another UC within the same class, subject to various checks.
 *
 * @param StudentCode The code of the student requesting the switch.
 * @param ucCode The code of the current UC.
 * @param newClassCode The code of the new class.
 * @param newUCCode The code of the new UC.
 */
void Requests::switchUC(int StudentCode, string ucCode,  string newClassCode, const std::string& newUCCode) {
    Action action;
    action.type = ActionType::SwitchUC;
    action.studentCode=StudentCode;
    action.ucCode = ucCode;

    action.newClassCode=newClassCode;
    action.newUcCode = newUCCode;
    action.description= "SwitchUC";
    string studentname;
    string classCode;
    Read reader;
    reader.Read_Student();
    if (!capacity(newClassCode,newClassCode)) {
        rejectedRequests.push(action);
        std::cout << "Transfer not allowed. The class has reached its maximum occupancy difference." << std::endl;
        return;
    }




    std::vector<Student> students = reader.getStudentvector();
    bool found = false;

    for (Student& student : students) {
        if (student.getStudentCode() == StudentCode) {

            if (student.getUcCode() == ucCode) {


                if (student.getClassCode() == newClassCode && student.getUcCode() == newUCCode) {
                    rejectedRequests.push(action);
                    std::cout << "The student " << student.getStudentName() << " is already in the class " << newClassCode << "in uc" << newUCCode <<  "." << std::endl;
                } else {
                    rejectedRequests.push(action);
                    std::cout << "Student found." << std::endl;
                }
                found = true;
                action.classCode=student.getClassCode();
                action.name = student.getStudentName();
                studentname = student.getStudentName();
                classCode = student.getClassCode();
                break;
            }
        }
    }
    bool checkOverlap=this->cheekClassOverlap(StudentCode, ucCode, newClassCode);

    if (checkOverlap==false){
        rejectedRequests.push(action);
        cout<<"There is a schedule conflit";
    }


    acceptedRequests.push(action);
    cout<<"Switch UC";
    reader.addStudentClass(StudentCode,studentname,newUCCode,newClassCode);
    reader.removeStudentClass(StudentCode,ucCode,classCode);

}
/**
 * @brief Undo the last student enrollment action.
 *
 * This function undoes the last student enrollment action, such as adding, switching, or removing a UC (subject) or class. It reverts the student's enrollment status based on the last accepted request.
 */
void Requests::undo() {
    Read reader;
    reader.Read_Student();
    std::vector<Student> students = reader.getStudentvector();

    if (!acceptedRequests.empty()) {
        Action lastAction = acceptedRequests.top();
        switch (lastAction.type){
            case ActionType::AddUC:
                cout << "UNDO ADDUC";
                reader.removeStudentClass(lastAction.studentCode, lastAction.ucCode,lastAction.classCode);
                break;
            case ActionType::SwitchUC:
                cout << "Undo SWITCHUC";
                reader.removeStudentClass(lastAction.studentCode,lastAction.newUcCode, lastAction.newClassCode);
                reader.addStudentClass(lastAction.studentCode,lastAction.name,lastAction.ucCode,lastAction.classCode);
                break;
            case ActionType::RemoveUC:
                cout << "UNDO REMOVE";
                reader.addStudentClass(lastAction.studentCode,lastAction.name,lastAction.ucCode,lastAction.classCode);
                break;
            case ActionType::switchClass:
                cout << "UNDO SWITCHCLASS";
                reader.updateStudentClass(lastAction.studentCode, lastAction.ucCode,lastAction.classCode);
                break;



        }
    } else {
        std::cout << "No actions to undo." << std::endl;
    }
           }

/**
 * @brief Retrieve the accepted requests stack.
 * @return The stack containing the accepted requests.
 */

stack<Action> Requests::getAcceptRequests(){
    return acceptedRequests;
}

/**
 * @brief Convert an action type to a string representation.
 * @param type The ActionType enum to be converted.
 * @return String representation of the ActionType.
 */
string Requests::actionTypeToString(ActionType type) {
    switch (type) {
        case ActionType::AddUC: return "AddUC";
        case ActionType::RemoveUC: return "RemoveUC";
        case ActionType::SwitchUC: return "SwitchUC";
        case ActionType::switchClass: return "switchClass";
        default: return " ";
    }
}

/**
 * @brief Save the accepted requests stack to a file.
 */
void Requests::saveStack(){
    string filename= "../schedule/saveStack.txt";
    ofstream file(filename);
    stack<Action>aux1;
    if(file.is_open()){

        while(acceptedRequests.size()>0){

            Action aux2 = acceptedRequests.top();
            aux1.push(aux2);
            acceptedRequests.pop();
        }
        while(aux1.size()>0){

            Action aux3 =aux1.top();
            aux1.pop();
            string line;

            file << actionTypeToString(aux3.type) << ";"<<aux3.studentCode<< ";"<<aux3.ucCode<<";"<<aux3.classCode<<";"<<aux3.description<<";"<<aux3.newClassCode<<";"<<aux3.newUcCode<<";"<<aux3.name;
        }
    }
    file.close();
}
/**
 * @brief Convert a string representation to an action type enum.
 * @param type String representation of the ActionType.
 * @return The corresponding ActionType enum.
 */
ActionType Requests::actionTypeToEnum(string type) {
    if(type=="AddUC") return ActionType::AddUC;
    if(type== "RemoveUC") return ActionType::RemoveUC;
    if(type=="SwitchUC") return ActionType::SwitchUC;
    if(type=="switchClass") return ActionType::switchClass ;
    return ActionType::AddUC;
}
/**
 * @brief Save the accepted requests stack to a file.
 */

void Requests::loadStack(){
    std::string filename = "../schedule/saveStack.txt";
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }
    std::string line;
    while (std::getline(inFile, line)) {

        std::istringstream lineStream(line);
        Action action;
        string type;
        string studentCode;
        if (std::getline(lineStream, type, ';') &&
            std::getline(lineStream, studentCode, ';') &&
            std::getline(lineStream, action.ucCode, ';') &&
            std::getline(lineStream, action.classCode, ';')&&
            std::getline(lineStream, action.description, ';') &&
            std::getline(lineStream, action.newClassCode, ';') &&
            std::getline(lineStream, action.newUcCode, ';')&&
            std::getline(lineStream, action.name, ';')){

        }
        action.studentCode = stoi(studentCode);
        action.type= actionTypeToEnum(type);
        acceptedRequests.push(action);
    }
}