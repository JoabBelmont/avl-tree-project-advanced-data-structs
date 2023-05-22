/**
 * @file name.hpp
 * @author Joabe Alves
 * @brief File containing the Name class
 * @version 0.1
 * @date 2023-05-19
 * 
 */

#ifndef NAME_HPP
#define NAME_HPP

#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <sstream>

class Name {
    private:
        std::string fullName;

    public:
        /* Construtores & Destrutores */
        Name() = default;
        Name(std::string fullName)
            : fullName(fullName) {}

        Name(std::vector<std::string> names) { this->fullName = names[0] + " " + names[1]; }

        ~Name() = default;

        /* Getters & Setters */
        std::string getFullName() const { return this->fullName; }
        void setFullName(std::string fullName) { this->fullName = fullName; }

        std::vector<std::string> splitFullName() const {
            std::vector<std::string> names;
            std::stringstream ss(this->fullName);
            std::string name;

            while (ss >> name) {
                names.push_back(name);
            }

            return names;
        }

        std::string getGivenName() const {
            std::vector<std::string> names = this->splitFullName();
            return names[0];
        }

        std::string getSurname() const {
            std::vector<std::string> names = this->splitFullName();
            return names[1];
        }

        /* Métodos */
        bool operator==(const Name& name) const { 
            // Checks if "this" is a prefix of "name"
            return std::string_view(name.getFullName().c_str(), this->getFullName().size()) == this->getFullName();
        }

        bool operator!=(const Name& name) const { return !operator==(name); }

        bool operator<(const Name &name) const { 
            return std::string_view(name.getFullName().c_str(), this->getFullName().size()) < this->getFullName();
        }

        bool operator>=(const Name &name) const { return !operator<(name); }

        bool operator>(const Name &name) const {
            return std::string_view(name.getFullName().c_str(), this->getFullName().size()) > this->getFullName();
        }

        bool operator<=(const Name &name) const { return !operator>(name); }

        friend std::ostream &operator<<(std::ostream &os, const Name &name) {
            os << name.getFullName();
            return os;
        }
};

#endif
