#ifndef DATE_HPP
#define DATE_HPP

#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

class Date {
    private:
        int day;
        int month;
        int year;

    public:
        /* Construtores & Destrutores */
        Date() = default;
        Date(int month, int day, int year)
            : month(month), day(day), year(year) {}

        Date(std::string date) {
            std::stringstream ss(date);
            std::string token;
            std::vector<std::string> tokens;
            
            while (getline(ss, token, '/')) {
                tokens.push_back(token);
            }

            this->month = stoi(tokens[0]);
            this->day = stoi(tokens[1]);
            this->year = stoi(tokens[2]);
        }

        ~Date() = default;

        /* Getters & Setters */
        int getDay() const { return day; }
        void setDay(int day) { this->day = day; }

        int getMonth() const { return month; }
        void setMonth(int month) { this->month = month; }

        int getYear() const { return year; }
        void setYear(int year) { this->year = year; }

        /* Métodos */
        bool operator==(Date date) const { 
            return (day == date.getDay() &&
                    month == date.getMonth() &&
                    year == date.getYear());
        }

        bool operator!=(Date date) const { return !operator==(date); }

        bool operator<(Date date) const { 
            if (year < date.getYear()) 
                return true;
            else if (year == date.getYear() && month < date.getMonth())
                return true;
            else if (year == date.getYear() && month == date.getMonth() && day < date.getDay())
                return true;
            else 
                return false;
        }

        bool operator>(Date date) const { 
            if (year > date.getYear())
                return true;
            else if (year == date.getYear() && month > date.getMonth())
                return true;
            else if (year == date.getYear() && month == date.getMonth() && day > date.getDay())
                return true;
            else
                return false;
        }

        bool operator<=(Date date) const { return !operator>(date); }

        bool operator>=(Date date) const { return !operator<(date); }

        friend std::ostream& operator<<(std::ostream& os, const Date& date) {
            os << std::setfill('0') << std::setw(2) << date.getDay() << "/"
               << std::setfill('0') << std::setw(2) << date.getMonth() << "/"
               << std::setfill('0') << std::setw(4) << date.getYear();
            return os;
        }
};

#endif
