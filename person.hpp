#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <fstream>
#include "date.hpp"

class Person {
    private:
        int nationalID;
        std::string givenName;
        std::string surname;
        Date birthDate;
        std::string city;

    public:
        /* Construtores & Destrutores */
        Person() = default;
        Person(int nationalID, std::string givenName, std::string surname, Date birthDate, std::string city)
            : nationalID(nationalID), givenName(givenName), surname(surname), birthDate(birthDate), city(city) {}
        ~Person() = default;

        /* Getters & Setters */
        int getNationalID() const { return nationalID; }
        void setNationalID(int nationalID) { this->nationalID = nationalID; }

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
