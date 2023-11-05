//
// Created by Marta on 01/11/2023.
//

#ifndef PROJETO_AED_REQUESTS_H
#define PROJETO_AED_REQUESTS_H



#ifndef REQUESTS_H
#define REQUESTS_H

#include "Classes.h"
#include "Student.h"
#include "Read.h"
#include "Slot.h"
#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <stack>

enum class ActionType {
    AddUC,
    RemoveUC,
    SwitchUC,
    switchClass,
    // Adicione outros tipos de ação conforme necessário
};

// Defina uma estrutura de dados para representar uma ação
struct Action {
    ActionType type;
    int studentCode;
    std::string ucCode;
    std::string classCode;
    std::string description; // Uma descrição da ação (opcional)
    string newClassCode;
    string  newUcCode;
    string name;
};



class Requests {
public:
    void undo();
    int cap =30;

    Requests(Read reader);
    Requests();
    bool cheekClassOverlap(int StudentCode, std::string ucCode, std::string newClassCode);

    void switchClass( int StudentCode, std::string ucCode, std::string newClassCode);
    bool vacancy(std::string& ucCode, string oldClassCode, std::string& newClassCode);
    bool capacity (string ucCode, string newClassCode);
    bool addUC(int StudentCode,  std::string ucCode,  std::string newClassCode);
    bool removeUC(int StudentCode,  string ucCode);
    void switchUC(int StudentCode, string ucCode, string newClassCode, const std::string& newUCCode);
    vector<Classes> getStudentClasses(int StudentCode);
    vector<Slot> getClassSlots(std::string ClassCode, std::string UcCode);

private:


    std::stack<Action> acceptedRequests; // Fila para pedidos aceites
    std::stack<Action> rejectedRequests; // Fila para pedidos recusados


};

#endif




#endif //PROJETO_AED_REQUESTS_H
