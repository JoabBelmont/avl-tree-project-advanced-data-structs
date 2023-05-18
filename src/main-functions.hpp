#ifndef MAIN_FUNCTIONS_HPP
#define MAIN_FUNCTIONS_HPP

#include <iostream>
#include <fstream>

#include "./avl/avl.hpp"

using namespace std;
using NationalIDGetter = NationalID (Person::*)() const;
using NameGetter = Name (Person::*)() const;
using DateGetter = Date (Person::*)() const;

NationalIDGetter getNationalID = &Person::getNationalID;
NameGetter getFullName = &Person::getFullName;
DateGetter getBirthDate = &Person::getBirthDate;

/* Declaração */
void readCSV(const string filename, vector<Person> &people);

/* Implementação */
// template <typename T>
// void searchPeople(avl_tree<T> &tree, T key) {
//     Node<T> *node = tree.searchNode(key);
//     if (node) {
//         while (node) {
//             cout << *node->toPerson << '\n';
//             node = node->next;
//         }
//     } else cout << "Not found" << '\n';
// }

// template <typename T>
// void searchPrefix(avl_tree<T> &tree, T key) {
//     Node<T> *node = tree.searchNode(key);
//     Node<T> *predecessor = tree.predecessor(node);
//     Node<T> *successor = tree.successor(node);

//     if (node->left) {
//         if (key == predecessor->key) {
//             cout << *predecessor->toPerson << '\n';
//             searchPrefix(tree, predecessor->key);
//         }
//     } else return;

//     if (node->right) {
//         if (key == successor->key) {
//             cout << *successor->toPerson << '\n';
//             searchPrefix(tree, successor->key);
//         }
//     } else return;
// }

void readCSV(const string filename, vector<Person> &people) {
    vector<string> fields;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
    }

    string line;
    getline(file, line); // Skip the header line

    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        Person person;

        // Read each field separated by the delimiter (comma in this case)

        // National ID
        getline(ss, field, ',');
        person.setNationalID(field);

        // Given Name
        getline(ss, field, ',');
        fields.push_back(field);

        // Surname
        getline(ss, field, ',');
        fields.push_back(field);

        // Full Name
        person.setFullName(fields);
        fields.clear();

        // Birth Date
        getline(ss, field, ',');
        person.setBirthDate(field);

        // City
        getline(ss, field, '\n');
        person.setCity(field);

        people.push_back(person);
    }

    file.close();
}

#endif
