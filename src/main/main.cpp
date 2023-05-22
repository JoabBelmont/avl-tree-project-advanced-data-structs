/**
 * @file main.cpp
 * @author Joabe Alves
 * @brief File containing the main function
 * @version 0.1
 * @date 2023-05-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "main-functions.hpp"
#include "show-menus.hpp"
#include <exception>

void fullNameSubMenu(avl_tree<Name> &tree);
void nationalIDSubMenu(avl_tree<NationalID> &tree);
void dateSubMenu(avl_tree<Date> &tree);
void debugSubMenu(avl_tree<Name> &fullNameTree, avl_tree<Date> &birthDateTree, avl_tree<NationalID> &nationalIDTree, vector<Person> &people);
/* 
    - Implement the debug submenu
        View tree
            Which tree?
        Choose archive
        Show all registered people
        Cat archive, grep
*/

int main() {
    string op;
    avl_tree<Name> fullNameTree;
    avl_tree<Date> birthDateTree;
    avl_tree<NationalID> nationalIDTree;
    vector<Person> people;

    readCSV("src/main/data.csv", people);

    fullNameTree.populateTree(people, getFullName);
    birthDateTree.populateTree(people, getBirthDate);
    nationalIDTree.populateTree(people, getNationalID);

    while (true) {
        showMainMenu();
        getline(cin, op);
        if (op == "0") {
            system("clear || cls");
            break;
        }
        else if (op == "1") {
            // system("clear || cls");
            fullNameSubMenu(fullNameTree);
        }
        else if (op == "2") {
            // system("clear || cls");
            nationalIDSubMenu(nationalIDTree);
        }
        else if (op == "3") {
            system("clear || cls");
            dateSubMenu(birthDateTree);
        }
        else if (op == "4") {
            system("clear || cls");
            debugSubMenu(fullNameTree, birthDateTree, nationalIDTree, people);
        }
    }

    return 0;
}

void fullNameSubMenu(avl_tree<Name> &tree) {
    string input;

    cout << "Digite o nome desejado: ";
    getline(cin, input);
    input[0] = toupper(input[0]);

    Name name(input);
    system("clear || cls");
    tree.searchPeople(name);

    cout << "Aperte \"Enter\" para voltar ao menu principal.";
    getchar();
}

void nationalIDSubMenu(avl_tree<NationalID> &tree) {
    string input;
    int fstCmp, sndCmp, trdCmp, lastCmp;

    cout << "Digite o CPF desejado: ";
    getline(cin, input);

    if (input.size() == 11 && isNumber(input)) {
        input.insert(3, ".");
        input.insert(7, ".");
        input.insert(11, "-");
    } else if (input.size() == 11 && !isNumber(input)) {
        cout << "CPF inválido. Tente novamente.\n";
    }

    NationalID nationalID(input);

    system("clear || cls");
    tree.searchPeople(nationalID);

    cout << "Aperte \"Enter\" para voltar ao menu principal.";
    getchar();
}

void dateSubMenu(avl_tree<Date>& tree) {
    string op;
    string input1, input2;

    while (true) {
        system("clear || cls");
        showDateSubMenu();
        cout << "Digite a opcao desejada: ";
        getline(cin, op);

        if (op == "0") {
            return;
        } else if (op == "1") {
            cout << "Digite a data desejada: ";
            getline(cin, input1);

            try {
                Date date(input1);
                tree.searchPeople(date);
                getchar();
            } catch (const std::exception& e) {
                cout << "Erro ao converter a data. Tente novamente.\n";
                getchar();
            }
        } else if (op == "2") {
            cout << "Digite o intervalo desejado:\n";
            cout << "Início: ";
            getline(cin, input1);
            cout << "Fim: ";
            getline(cin, input2);

            try {
                Date startDate(input1);
                Date endDate(input2);
                tree.searchPeople(startDate, endDate);
            } catch (const std::exception& e) {
                cout << "Erro ao converter as datas. Tente novamente.\n";
                getchar();
            }
        } else {
            cout << "Opção inválida, aperte \"Enter\" e tente novamente.";
            getchar();
        }
    }
}

void debugSubMenu(avl_tree<Name> &fullNameTree, avl_tree<Date> &birthDateTree, avl_tree<NationalID> &nationalIDTree, vector<Person> &people) {
    showDebugSubMenu();
    getchar();
}

