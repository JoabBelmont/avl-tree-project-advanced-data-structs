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
#include "show-menus.hpp"

using namespace std;
using NationalIDGetter = NationalID (Person::*)() const;
using NameGetter = Name (Person::*)() const;
using DateGetter = Date (Person::*)() const;
using CityGetter = string (Person::*)() const;

/* Define function pointers for getter functions */
NationalIDGetter getNationalID = &Person::getNationalID;
NameGetter getFullName = &Person::getFullName;
DateGetter getBirthDate = &Person::getBirthDate;
CityGetter getCity = &Person::getCity;

/* Reads CSV data into the people vector */
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

/* Checks if a string only contains digits */
bool isNumber(string input) {
    for (char c : input)
        if (!isdigit(c)) return false;
    return true;
}

/* Replaces all non-digit characters in a string with a delimiter */
void setInput(string &input, char delimiter) {
    for (char &c : input) {
        if (!isdigit(c))
            c = delimiter;
    }
}

/* Checks if a NationalID input's format is valid */
bool nationalIDValidity(string input) {
    if (input.size() < 11) return false;

    setInput(input, ' ');
    stringstream ss(input);
    string token;
    vector<string> tokens;

    while (getline(ss, token, ' '))
        tokens.push_back(token);

    if (tokens.size() != 4) return false;

    if (tokens[0].size() != 3) return false;
    if (tokens[1].size() != 3) return false;
    if (tokens[2].size() != 3) return false;
    if (tokens[3].size() != 2) return false;
    return true;
}

/* Implementation of the Name Menu */
void nameMenu(avl_tree<Name> &tree) {
    string input;

    system("clear || cls");
    cout << "\n ╭ Type the desired search term for name \n";
    cout << " ╰|> ";
    getline(cin, input);

    // Forces the input to be capitalized
    input[0] = toupper(input[0]);
    for (int i = 1; input[i]; i++)
        input[i] = tolower(input[i]);

    // If the input is a single word, it will be treated as a given name
    Name name(input);
    system("clear || cls");
    cout << '\n';
    cout << " Searching for \"" << name << "\":\n\n";
    tree.searchPeople(name);

    cout << " Press \"Enter\" to go back to the Main Menu.";
    getchar();
}

/* Implementation of the National ID Menu */
void nationalIDMenu(avl_tree<NationalID>& tree) {
    string input;

    system("clear || cls");
    while (true) {
        cout << "\n ╭ Type the desired National ID \n";
        cout << " ╰|> ";
        getline(cin, input);

        // If the input is a number with 11 digits, it will be formatted
        if (input.size() == 11 && isNumber(input)) {
            input.insert(3, ".");
            input.insert(7, ".");
            input.insert(11, "-");
        }

        try {
            // Validates the input and throws an exception if it's invalid
            if (!nationalIDValidity(input)) {
                throw std::runtime_error("Invalid National ID.");
            }

            NationalID nationalID(input);

            system("clear || cls");
            cout << '\n';
            cout << " Searching for \"" << nationalID << "\":\n\n";
            tree.searchPeople(nationalID);

            cout << " Press \"Enter\" to go back to the Main Menu.";
            getchar();
            break;
        } catch (const std::exception& e) {
            // Catches the exception and displays an error message
            cout << " " << e.what() << " Try again.\n";
            continue;
        }
    }
}


/* Implementation of the Date Menu */
void dateMenu(avl_tree<Date>& tree) {
    string option;
    string input1, input2;
    Date date;

    while (true) {
        system("clear || cls");
        showDateMenu();
        getline(cin, option);

        if (option == "0") { // Go back to the Main Menu
            return;
        } else if (option == "1") { // Search by single date
            system("clear || cls");
            while (true) {
                cout << "\n ╭ Type the desired date (MM/DD/YYYY) \n";
                cout << " ╰|> ";
                getline(cin, input1);
                setInput(input1, '/'); // Allows the user to type the date with any delimiter

                try {
                    date = Date(input1);
                    
                    // Checks if the date is in the right format
                    if (!date.isValid()) {
                        throw std::runtime_error("Invalid date. Try again.");
                    }

                    system("clear || cls");
                    cout << '\n';
                    cout << " Searching for \"" << date << "\":\n\n";
                    tree.searchPeople(date);
                    break;
                } catch (const std::exception& e) {
                    cout << "An error occurred: " << e.what() << '\n';
                    cout << "Press \"Enter\" to continue.";
                    getchar();
                }
            }
            cout << " Press \"Enter\" to go back to the Main Menu.";
            getchar();
        } else if (option == "2") { // Search by interval
            system("clear || cls");
            cout << "\n ╭ Type the desired interval (MM/DD/YYYY)\n";
            cout << " ├|> Start: ";
            getline(cin, input1);
            setInput(input1, '/');
            cout << " ╰|> Finish: ";
            getline(cin, input2);
            setInput(input2, '/');
            cout << '\n';

            try {
                Date startDate(input1);
                Date endDate(input2);

                // If the dates are in the wrong order, the user is asked if they want to swap them
                if (startDate > endDate) {
                    string op;

                    while (true) {
                        cout << " Starting date is bigger than the ending date.\n";
                        cout << " Did you mean \"" << endDate << " - " << startDate << "\"? (Y/n) ";
                        getline(cin, op);

                        if (op == "y" || op == "Y" || op == "") {
                            system("clear || cls");
                            cout << '\n';
                            cout << " Searching for \"" << endDate << " - " << startDate << "\":\n\n";
                            // Swaps the dates
                            tree.searchPeople(endDate, startDate);
                            break;
                        } else if (op == "n" || op == "N") {
                            break;
                        } else {
                            cout << '\n';
                            continue;
                        }
                    }
                } else {
                    system("clear || cls");
                    cout << " Searching for \"" << startDate << " - " << endDate << "\":\n\n";
                    cout << '\n';
                    tree.searchPeople(startDate, endDate);
                }

                cout << " Press \"Enter\" to go back to the Main Menu.";
                getchar();
            } catch (const std::exception& e) {
                cout << "An error occurred: " << e.what() << '\n';
                cout << "Press \"Enter\" to continue.";
                getchar();
            }
        } else {
            cout << " Invalid option, press \"Enter\" and try again.";
            getchar();
        }
    }
}

/* Implementation of the Debug Menu */
void debugMenu(avl_tree<Name> &fullNameTree, avl_tree<Date> &birthDateTree, avl_tree<NationalID> &nationalIDTree, vector<Person> &people) {
    string option;

    while (true) {
        system("clear || cls");
        showDebugMenu();
        getline(cin, option);

        if (option == "0") { // Returns to the Main Menu
            return;
        } else if (option == "1") { // Show Tree submenu
            string op;

            while (true) {
                system("clear || cls");
                showTreeMenu();
                getline(cin, op);

                if (op == "0") { // Returns to the Debug Menu
                    break;
                } else if (op == "1") { // Shows the National ID Tree
                    nationalIDTree.bshow();
                    cout << "\n \"National ID\" Tree shown, press \"Enter\" to go back to the Debug Menu.";
                    getchar();
                } else if (op == "2") { // Shows the Full Name Tree
                    fullNameTree.bshow();
                    cout << "\n \"Name\" Tree shown, press \"Enter\" to go back to the Debug Menu.";
                    getchar();
                } else if (op == "3") { // Shows the Birth Date Tree
                    birthDateTree.bshow();
                    cout << "\n \"Date\" Tree shown, press \"Enter\" to go back to the Debug Menu.";
                    getchar();
                } else if (op == "4") { // Shows all trees
                    nationalIDTree.bshow();
                    fullNameTree.bshow();
                    birthDateTree.bshow();
                    cout << "\n All trees shown, press \"Enter\" to go back.";
                    getchar();
                } else {
                    cout << " Invalid option, press \"Enter\" and try again.";
                    getchar();
                    continue;
                }
            }
        } else if (option == "2") { // Shows all people
            for (auto &person : people) {
                cout << person << '\n';
            }
            cout << "All people shown, press \"Enter\" to go back to the Debug Menu.";
            getchar();
        } else {
            cout << " Invalid option, press \"Enter\" and try again.";
            getchar();
            continue;
        }
    }
}

#endif
