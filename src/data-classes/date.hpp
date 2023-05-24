/**
 * @file date.hpp
 * @author Joabe Alves
 * @brief File containing the Date class
 * @version 0.1
 * @date 2023-05-19
 * 
 */

#ifndef DATE_HPP
#define DATE_HPP

#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

class Date {
    private:
        /* Attributes */
        int day;
        int month;
        int year;

    public:
        /* Constructors & Destructors */
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

            this->month = std::stoi(tokens[0]);
            this->day = std::stoi(tokens[1]);
            this->year = std::stoi(tokens[2]);
        }

        ~Date() = default;

        /* Getters & Setters */
        int getDay() const { return day; }
        void setDay(int day) { this->day = day; }

        int getMonth() const { return month; }
        void setMonth(int month) { this->month = month; }

        int getYear() const { return year; }
        void setYear(int year) { this->year = year; }

        /* Methods */
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
            os << std::setfill('0') << std::setw(2) << date.getDay() << '/'
               << std::setfill('0') << std::setw(2) << date.getMonth() << '/'
               << std::setfill('0') << std::setw(4) << date.getYear();
            return os;
        }

        friend std::istream& operator>>(std::istream& is, Date& date) {
            std::string line;
            getline(is, line);

            date = Date(line);
            return is;
        }

        bool isLeapYear() {
            if (year % 4 == 0 && year % 100 != 0)
                return true;
            else if (year % 400 == 0)
                return true;
            else
                return false;
        }

        bool isValid() {
            if (month < 1 || month > 12)
                return false;
            else if (day < 1 || day > 31)
                return false;
            else if (month == 2 && day > 29)
                return false;
            else if (month == 2 && day == 29 && !isLeapYear())
                return false;
            else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
                return false;
            else if (*this == Date())
                return false;
            else
                return true;
        }
};

#endif
