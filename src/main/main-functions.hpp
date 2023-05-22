/**
 * @file main-functions.hpp
 * @author Joabe Alves
 * @brief File containing the main functions of the program
 * @version 0.1
 * @date 2023-05-19
 * 
 */

#ifndef MAIN_FUNCTIONS_HPP
#define MAIN_FUNCTIONS_HPP

#include <iostream>
#include <fstream>
#include <string>

#include "../avl/avl.hpp"

using namespace std;
using NationalIDGetter = NationalID (Person::*)() const;
using NameGetter = Name (Person::*)() const;
using DateGetter = Date (Person::*)() const;
using CityGetter = string (Person::*)() const;

NationalIDGetter getNationalID = &Person::getNationalID;
NameGetter getFullName = &Person::getFullName;
DateGetter getBirthDate = &Person::getBirthDate;
CityGetter getCity = &Person::getCity;

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

bool isNumber(string str) {
    for (char c : str)
        if (!isdigit(c)) return false;
    return true;
}

#endif
