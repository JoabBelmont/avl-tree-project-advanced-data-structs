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
#include <exception>

using namespace std;

int main() {
    string option;
    avl_tree<Name> fullNameTree;
    avl_tree<Date> birthDateTree;
    avl_tree<NationalID> nationalIDTree;
    vector<Person> people;

    readCSV("src/main/data.csv", people);

    // Populate the AVL trees with the data from the people vector
    fullNameTree.populateTree(people, getFullName);
    birthDateTree.populateTree(people, getBirthDate);
    nationalIDTree.populateTree(people, getNationalID);

    while (true) {
        showMainMenu();
        getline(cin, option);
        if (option == "0") { // Exit
            system("clear || cls");
            break;
        }
        else if (option == "1") { // Search by name
            nameMenu(fullNameTree);
        }
        else if (option == "2") { // Search by National ID
            nationalIDMenu(nationalIDTree);
        }
        else if (option == "3") { // Search by birth date
            dateMenu(birthDateTree);
        }
        else if (option == "4") { // Debug menu
            debugMenu(fullNameTree, birthDateTree, nationalIDTree, people);
        } else {
            cout << "Invalid option." << endl;
            cout << "Press \"Enter\" to try again.";
            getchar();
            continue;
        }
    }

    // fullNameTree.searchPeople(Name("Kai Gomes"));

    return 0;
}
