/**
 * @file nationalId.hpp
 * @author Joabe Alves
 * @brief File containing the NationalID class
 * @version 0.1
 * @date 2023-05-19
 * 
 */

#ifndef NATIONALID_HPP
#define NATIONALID_HPP

#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

class NationalID {
private:
    /* Attributes */
    int fstCamp;
    int sndCamp;
    int trdCamp;
    int lastCamp;

public:
    /* Constructors & Destructors */
    NationalID() = default;
    NationalID(int fstCamp, int sndCamp, int trdCamp, int lastCamp)
        : fstCamp(fstCamp), sndCamp(sndCamp), trdCamp(trdCamp), lastCamp(lastCamp) {}
    
    NationalID(std::string id) {
        std::vector<std::string> tokens;
        std::stringstream ss(id);
        std::string token;

        while (getline(ss, token, '.')) {
            std::stringstream sub_ss(token);
            std::string sub_token;
            while (getline(sub_ss, sub_token, '-')) {
                tokens.push_back(sub_token);
            }
        }

        if (tokens.size() != 4) {
            throw std::invalid_argument("Invalid National ID");
        }

        this->fstCamp = std::stoi(tokens[0]);
        this->sndCamp = std::stoi(tokens[1]);
        this->trdCamp = std::stoi(tokens[2]);
        this->lastCamp = std::stoi(tokens[3]);
    }

    ~NationalID() = default;

    /* Getters & Setters */
    int getFstCamp() const { return fstCamp; }
    void setFstCamp(int fstCamp) { this->fstCamp = fstCamp; }

    int getSndCamp() const { return sndCamp; }
    void setSndCamp(int sndCamp) { this->sndCamp = sndCamp; }

    int getTrdCamp() const { return trdCamp; }
    void setTrdCamp(int trdCamp) { this->trdCamp = trdCamp; }

    int getLastCamp() const { return lastCamp; }
    void setLastCamp(int lastCamp) { this->lastCamp = lastCamp; }

    /* Methods */
    bool operator==(NationalID id) const { 
        return (fstCamp == id.getFstCamp() &&
                sndCamp == id.getSndCamp() &&
                trdCamp == id.getTrdCamp() &&
                lastCamp == id.getLastCamp());
    }

    bool operator!=(NationalID id) const { return !operator==(id); }

    bool operator<(NationalID id) const { 
        if (fstCamp < id.getFstCamp()) 
            return true;
        else if (fstCamp == id.getFstCamp() && sndCamp < id.getSndCamp())
            return true;
        else if (fstCamp == id.getFstCamp() && sndCamp == id.getSndCamp() && trdCamp < id.getTrdCamp())
            return true;
        else if (fstCamp == id.getFstCamp() && sndCamp == id.getSndCamp() && trdCamp == id.getTrdCamp() && lastCamp < id.getLastCamp())
            return true;
        else
            return false;
    }

    bool operator>(NationalID id) const {
        if (fstCamp > id.getFstCamp())
            return true;
        else if (fstCamp == id.getFstCamp() && sndCamp > id.getSndCamp())
            return true;
        else if (fstCamp == id.getFstCamp() && sndCamp == id.getSndCamp() && trdCamp > id.getTrdCamp())
            return true;
        else if (fstCamp == id.getFstCamp() && sndCamp == id.getSndCamp() && trdCamp == id.getTrdCamp() && lastCamp > id.getLastCamp())
            return true;
        else
            return false;
    }

    bool operator<=(NationalID id) const { return !operator>(id); }

    bool operator>=(NationalID id) const { return !operator<(id); }

    friend std::ostream& operator<<(std::ostream& os, const NationalID& id) {
        os << std::setfill('0') << std::setw(3) << id.getFstCamp() << "."
        << std::setfill('0') << std::setw(3) << id.getSndCamp() << "."
        << std::setfill('0') << std::setw(3) << id.getTrdCamp() << "-"
        << std::setfill('0') << std::setw(2) << id.getLastCamp();
        return os;
    }

    friend std::istream& operator>>(std::istream& is, NationalID& id) {
        std::string line;
        getline(is, line);
        id = NationalID(line);
        return is;
    }
};

#endif
