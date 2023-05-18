#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <fstream>
#include "date.hpp"
#include "nationalId.hpp"
#include "name.hpp"

class Person {
    private:
        NationalID nationalID;
        Name fullName;
        Date birthDate;
        std::string city;

    public:
        /* Construtores & Destrutores */
        Person() = default;
        Person(NationalID nationalID, Name fullName, Date birthDate, std::string city)
            : nationalID(nationalID), fullName(fullName), birthDate(birthDate), city(city) {}
        ~Person() = default;

        /* Getters & Setters */
        NationalID getNationalID() const { return nationalID; }
        void setNationalID(NationalID nationalID) { this->nationalID = nationalID; }
        void setNationalID(std::string nationalID) { this->nationalID = NationalID(nationalID); }

        Name getFullName() const { return fullName; }
        void setFullName(std::vector<std::string> fullName) { this->fullName = Name(fullName); }

        Date getBirthDate() const { return birthDate; }
        void setBirthDate(Date birthDate) { this->birthDate = birthDate; }
        void setBirthDate(std::string birthDate) { this->birthDate = Date(birthDate); }

        std::string getCity() const { return city; }
        void setCity(std::string city) { this->city = city; }

        /* Métodos */
        friend std::ostream& operator<<(std::ostream& os, const Person& person) {
            os << 
            "CPF: " << person.getNationalID() << '\n' <<
            "Nome: " << person.getFullName() << '\n' <<
            "Data de Nascimento: " << person.getBirthDate() << '\n' <<
            "Cidade: " << person.getCity() << std::endl;

            return os;
        }
};

#endif
