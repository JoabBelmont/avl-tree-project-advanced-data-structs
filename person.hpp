#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <fstream>
#include "date.hpp"
#include "nationalId.hpp"

class Person {
    private:
        NationalID nationalID;
        std::string givenName;
        std::string surname;
        Date birthDate;
        std::string city;

    public:
        /* Construtores & Destrutores */
        Person() = default;
        Person(NationalID nationalID, std::string givenName, std::string surname, Date birthDate, std::string city)
            : nationalID(nationalID), givenName(givenName), surname(surname), birthDate(birthDate), city(city) {}
        ~Person() = default;

        /* Getters & Setters */
        NationalID getNationalID() const { return nationalID; }
        void setNationalID(NationalID nationalID) { this->nationalID = nationalID; }
        void setNationalID(std::string nationalID) { this->nationalID = NationalID(nationalID); }

        std::string getGivenName() const { return givenName; }
        void setGivenName(std::string givenName) { this->givenName = givenName; }

        std::string getSurname() const { return surname; }
        void setSurname(std::string surname) { this->surname = surname; }

        Date getBirthDate() const { return birthDate; }
        void setBirthDate(Date birthDate) { this->birthDate = birthDate; }
        void setBirthDate(std::string birthDate) { this->birthDate = Date(birthDate); }

        std::string getCity() const { return city; }
        void setCity(std::string city) { this->city = city; }

        /* Métodos */
        friend std::ostream& operator<<(std::ostream& os, const Person& person) {
            os << 
            "CPF: " << person.getNationalID() << "\n" <<
            "Nome: " << person.getGivenName() << " " <<
            person.getSurname() << "\n" <<
            "Data de Nascimento: " << person.getBirthDate() << "\n" <<
            "Cidade: " << person.getCity() << std::endl;

            return os;
        }
};

#endif
