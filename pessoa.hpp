#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <string>
#include "date.hpp"

class Person {
    private:
        int cpf;
        std::string name;
        std::string surname;
        Date birthDate;
        std::string city;

    public:
        /* Construtores & Destrutores */
        Person();
        Person(int cpf, std::string name, std::string surname, Date birthDate, std::string city)
            : cpf(cpf), name(name), surname(surname), birthDate(birthDate), city(city) {}
        ~Person();

        /* Getters & Setters */
        int getCpf() { return cpf; }
        void setCpf(int cpf) { this->cpf = cpf; }

        std::string getName() { return name; }
        void setName(std::string name) { this->name = name; }

        std::string getSurname() { return surname; }
        void setSurname(std::string surname) { this->surname = surname; }

        Date getBirthDate() { return birthDate; }
        void setBirthDate(Date birthDate) { this->birthDate = birthDate; }

        std::string getCity() { return city; }
        void setCity(std::string city) { this->city = city; }
};

#endif
