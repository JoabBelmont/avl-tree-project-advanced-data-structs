#ifndef NAME_HPP
#define NAME_HPP

#include <string>

class Name {
    private:
        std::string givenName;
        std::string surname;

    public:
        /* Construtores & Destrutores */
        Name() = default;
        Name(std::string givenName, std::string surname)
            : givenName(givenName), surname(surname) {}
        ~Name() = default;

        /* Getters & Setters */
        std::string getGivenName() const { return givenName; }
        void setGivenName(std::string givenName) { this->givenName = givenName; }

        std::string getSurname() const { return surname; }
        void setSurname(std::string surname) { this->surname = surname; }

        /* Métodos */
        friend std::ostream& operator<<(std::ostream& os, const Name& name) {
            os << name.getGivenName() << " " << name.getSurname();
            return os;
        }
};

#endif