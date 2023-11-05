#include "Requests.h"
#include <algorithm>


Requests::Requests(Read reader) {}

Requests::Requests() {}

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
        return false; // A diferença de ocupação excede o limite em relação à turma antiga da mesma UC.
    }

    return true;
}

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
                            cout << "Não há vagas na nova turma!";
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


bool Requests::addUC(int StudentCode, std::string ucCode,  std::string newClassCode) {
    Action action;
    action.type = ActionType::AddUC;
    action.studentCode=StudentCode;
    action.ucCode = ucCode;
    action.classCode=newClassCode;
    action.description= "Adicionada UC " + ucCode + " para o aluno " + std::to_string(StudentCode);
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
    // Verificar se há vaga na nova UC.
    else if (!capacity( ucCode, newClassCode)) {
        rejectedRequests.push(action);
        std::cout << "No vacancy in the new UC. Cannot add." << std::endl;
        return false;
    }

    else {
        // Adicionar a UC para o aluno e atualizar o arquivo "students_classes.csv".
        acceptedRequests.push(action);
        cout << studentName;
        reader.addStudentClass(StudentCode, studentName, ucCode, newClassCode);
        std::cout << "UC " << ucCode << " added to student " << StudentCode << "." << std::endl;

        return true;
    }
}

// Função para remover uma UC de um aluno

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

// Função para trocar de UC para um aluno
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

// Verificar conflito de horários.


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

    // Remover a UC atual e adicionar a nova UC para o aluno
    acceptedRequests.push(action);
    cout<<"Switch UC";
    reader.addStudentClass(StudentCode,studentname,newUCCode,newClassCode);
    reader.removeStudentClass(StudentCode,ucCode,classCode);

}

void Requests::undo() {
    Read reader;
    reader.Read_Student();
    std::vector<Student> students = reader.getStudentvector();

    if (!acceptedRequests.empty()) {
        Action lastAction = acceptedRequests.top();
        switch (lastAction.type){
            case ActionType::AddUC:
                cout << "UNDO";
                reader.removeStudentClass(lastAction.studentCode, lastAction.ucCode,lastAction.classCode);
                break;
            case ActionType::SwitchUC:
                cout << "Undo swutvhUc";
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



