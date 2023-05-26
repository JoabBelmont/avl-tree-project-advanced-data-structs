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

using NationalIDGetter = NationalID (Person::*)() const;
using NameGetter = Name (Person::*)() const;
using DateGetter = Date (Person::*)() const;
using CityGetter = std::string (Person::*)() const;

/* Define function pointers for getter functions */
NationalIDGetter getNationalID = &Person::getNationalID;
NameGetter getFullName = &Person::getFullName;
DateGetter getBirthDate = &Person::getBirthDate;
CityGetter getCity = &Person::getCity;

/* Reads CSV data into the people vector */
void readCSV(const std::string filename, std::vector<Person> &people) {
    std::vector<std::string> fields;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file.\n";
    }

    std::string line;
    std::getline(file, line); // Skip the header line

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;
        Person person;

        // Read each field separated by the delimiter (comma in this case)

        // National ID
        std::getline(ss, field, ',');
        person.setNationalID(field);

        // Given Name
        std::getline(ss, field, ',');
        fields.push_back(field);

        // Surname
        std::getline(ss, field, ',');
        fields.push_back(field);

        // Full Name
        person.setFullName(fields);
        fields.clear();

        // Birth Date
        std::getline(ss, field, ',');
        person.setBirthDate(field);

        // City
        std::getline(ss, field, '\n');
        person.setCity(field);

        people.push_back(person);
    }

    file.close();
}

/* Checks if a std::string only contains digits */
bool isNumber(std::string input) {
    for (char c : input)
        if (!isdigit(c)) return false;
    return true;
}

/* Replaces all non-digit characters in a std::string with a delimiter */
void setInput(std::string &input, char delimiter) {
    for (char &c : input) {
        if (!isdigit(c))
            c = delimiter;
    }
}

/* Checks if a NationalID input's format is valid */
bool nationalIDValidity(std::string input) {
    if (input.size() < 11) return false;

    setInput(input, ' ');
    std::stringstream ss(input);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(ss, token, ' '))
        tokens.push_back(token);

    if (tokens.size() != 4) return false;

    if (tokens[0].size() != 3) return false;
    if (tokens[1].size() != 3) return false;
    if (tokens[2].size() != 3) return false;
    if (tokens[3].size() != 2) return false;
    return true;
}

/* Checks if a Date input's format is valid */
bool dateValidity(std::string input) {
    if (input.size() < 10) return false;

    setInput(input, ' ');
    std::stringstream ss(input);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(ss, token, ' '))
        tokens.push_back(token);

    if (tokens.size() != 3) return false;

    if (tokens[0].size() != 2) return false;
    if (tokens[1].size() != 2) return false;
    if (tokens[2].size() != 4) return false;
    return true;
}

/* Implementation of the Name Menu */
void nameMenu(avl_tree<Name> &tree) {
    std::string input;
    bool capitalize { true };

    system("clear || cls");
    std::cout << "\n ╭ Type the desired search term for name \n";
    std::cout << " ╰|> ";
    std::getline(std::cin, input);

    // Forces the input to be capitalized
    for (char c : input) {
        if (capitalize && isalpha(c)) {
            c = toupper(c);
            capitalize = false;
        } else
            c = tolower(c);

        if (isspace(c))
            capitalize = true;
    }

    // If the input is a single word, it will be treated as a given name
    Name name(input);
    system("clear || cls");
    std::cout << '\n';
    std::cout << " Searching for \"" << name << "\":\n\n";
    tree.searchPeople(name);

    std::cout << " Press \"Enter\" to go back to the Main Menu.";
    getchar();
}

/* Implementation of the National ID Menu */
void nationalIDMenu(avl_tree<NationalID>& tree) {
    std::string input;

    system("clear || cls");
    while (true) {
        std::cout << "\n ╭ Type the desired National ID \n";
        std::cout << " ╰|> ";
        std::getline(std::cin, input);

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
            std::cout << '\n';
            std::cout << " Searching for \"" << nationalID << "\":\n\n";
            tree.searchPeople(nationalID);

            std::cout << " Press \"Enter\" to go back to the Main Menu.";
            getchar();
            break;
        } catch (const std::exception& e) {
            // Catches the exception and displays an error message
            std::cout << " " << e.what() << " Try again.\n";
            continue;
        }
    }
}


/* Implementation of the Date Menu */
void dateMenu(avl_tree<Date>& tree) {
    std::string option;
    std::string input1, input2;
    Date date;

    while (true) {
        system("clear || cls");
        showDateMenu();
        std::getline(std::cin, option);

        if (option == "0") { // Go back to the Main Menu
            return;
        } else if (option == "1") { // Search by single date
            system("clear || cls");
            while (true) {
                std::cout << "\n ╭ Type the desired date (MM/DD/YYYY) \n";
                std::cout << " ╰|> ";
                std::getline(std::cin, input1);
                setInput(input1, '/'); // Allows the user to type the date with any delimiter

                try {
                    if (!dateValidity(input1)) {
                        throw std::runtime_error("Invalid date. Try again.");
                    }

                    date = Date(input1);
                    
                    // Checks if the date is in the right format
                    if (!date.isValid()) {
                        throw std::runtime_error("Invalid date. Try again.");
                    }

                    system("clear || cls");
                    std::cout << '\n';
                    std::cout << " Searching for \"" << date << "\":\n\n";
                    tree.searchPeople(date);
                    break;
                } catch (const std::exception& e) {
                    std::cout << " An error occurred: " << e.what() << '\n';
                    std::cout << " Press \"Enter\" to continue.";
                    getchar();
                }
            }
            std::cout << " Press \"Enter\" to go back to the Main Menu.";
            getchar();
        } else if (option == "2") { // Search by interval
            system("clear || cls");
            std::cout << "\n ╭ Type the desired interval (MM/DD/YYYY)\n";
            std::cout << " ├|> Start: ";
            std::getline(std::cin, input1);
            setInput(input1, '/');
            std::cout << " ╰|> Finish: ";
            std::getline(std::cin, input2);
            setInput(input2, '/');
            std::cout << '\n';

            try {
                if (!dateValidity(input1) || !dateValidity(input2)) {
                    throw std::runtime_error("Invalid date. Try again.");
                }

                Date startDate(input1);
                Date endDate(input2);

                if (!date.isValid()) {
                    throw std::runtime_error("Invalid date. Try again.");
                }

                // If the dates are in the wrong order, the user is asked if they want to swap them
                if (startDate > endDate) {
                    std::string op;

                    while (true) {
                        std::cout << " Starting date is bigger than the ending date.\n";
                        std::cout << " Did you mean \"" << endDate << " - " << startDate << "\"? (Y/n) ";
                        std::getline(std::cin, op);

                        if (op == "y" || op == "Y" || op == "") {
                            system("clear || cls");
                            std::cout << '\n';
                            std::cout << " Searching for \"" << endDate << " - " << startDate << "\":\n\n";
                            // Swaps the dates
                            tree.searchPeople(endDate, startDate);
                            break;
                        } else if (op == "n" || op == "N") {
                            break;
                        } else {
                            std::cout << '\n';
                            continue;
                        }
                    }
                } else {
                    system("clear || cls");
                    std::cout << " Searching for \"" << startDate << " - " << endDate << "\":\n";
                    std::cout << '\n';
                    tree.searchPeople(startDate, endDate);
                }

                std::cout << " Press \"Enter\" to go back to the Main Menu.";
                getchar();
            } catch (const std::exception& e) {
                std::cout << " An error occurred: " << e.what() << '\n';
                std::cout << " Press \"Enter\" to continue.";
                getchar();
            }
        } else {
            std::cout << " Invalid option, press \"Enter\" and try again.";
            getchar();
        }
    }
}

/* Implementation of the Debug Menu */
void debugMenu(avl_tree<Name> &fullNameTree, avl_tree<Date> &birthDateTree, avl_tree<NationalID> &nationalIDTree, std::vector<Person> &people) {
    std::string option;

    while (true) {
        system("clear || cls");
        showDebugMenu();
        std::getline(std::cin, option);

        if (option == "0") { // Returns to the Main Menu
            return;
        } else if (option == "1") { // Show Tree submenu
            std::string op;

            while (true) {
                system("clear || cls");
                showTreeMenu();
                std::getline(std::cin, op);

                if (op == "0") { // Returns to the Debug Menu
                    break;
                } else if (op == "1") { // Shows the National ID Tree
                    nationalIDTree.bshow();
                    std::cout << "\n \"National ID\" Tree shown, press \"Enter\" to go back to the Debug Menu.";
                    getchar();
                } else if (op == "2") { // Shows the Full Name Tree
                    fullNameTree.bshow();
                    std::cout << "\n \"Name\" Tree shown, press \"Enter\" to go back to the Debug Menu.";
                    getchar();
                } else if (op == "3") { // Shows the Birth Date Tree
                    birthDateTree.bshow();
                    std::cout << "\n \"Date\" Tree shown, press \"Enter\" to go back to the Debug Menu.";
                    getchar();
                } else if (op == "4") { // Shows all trees
                    nationalIDTree.bshow();
                    fullNameTree.bshow();
                    birthDateTree.bshow();
                    std::cout << "\n All trees shown, press \"Enter\" to go back.";
                    getchar();
                } else {
                    std::cout << " Invalid option, press \"Enter\" and try again.";
                    getchar();
                    continue;
                }
            }
        } else if (option == "2") { // Shows all people
            for (auto &person : people) {
                std::cout << person << '\n';
            }
            std::cout << "All people shown, press \"Enter\" to go back to the Debug Menu.";
            getchar();
        } else {
            std::cout << " Invalid option, press \"Enter\" and try again.";
            getchar();
            continue;
        }
    }
}

#endif
