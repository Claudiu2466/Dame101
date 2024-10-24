//
// EXPRIMAREA COORDONATELOR CAII DE MISCARE SAU A SARITURII
// 

#ifndef TURN_H_
#define TURN_H_

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "state.h"
#include "coord.h"

class State;

class Turn {
public:
    const static int kDataLength = 30;

    // constructor implicit
    Turn() : capture_(false) {}

    // constructor cu parametrii
    Turn(const std::vector<Coord*>& coords, bool capture)
        : coords_(coords), capture_(capture) {
        Encode();
    }

    // constructor de copiere
    Turn(const Turn& other)
        : coords_(other.coords_), capture_(other.capture_) {
        std::copy(std::begin(other.data_), std::end(other.data_), std::begin(data_));
    }

    // distructor
    ~Turn() {
        for (Coord* coord : coords_) {
            delete coord;
        }
    }

    // operator de atribuire
    Turn& operator=(const Turn& other) {
        if (this != &other) {

            for (Coord* coord : coords_) {
                delete coord;
            }
            coords_ = other.coords_;
            capture_ = other.capture_;
            std::copy(std::begin(other.data_), std::end(other.data_), std::begin(data_));
        }
        return *this;
    }

    // operator de comparare
    bool operator==(const Turn& other) const {
        return capture_ == other.capture_ && std::string(data_) == std::string(other.data_);
    }

    // operator de citire
    friend std::istream& operator>>(std::istream& is, Turn& turn) {
        std::string input;
        is >> input;

        return is;
    }

    // operator de afisare
    friend std::ostream& operator<<(std::ostream& os, const Turn& turn) {
        os << "Capture: " << (turn.capture_ ? "Yes" : "No") << ", Coords: ";
        for (const auto& coord : turn.coords_) {
            os << *coord << " ";
        }
        return os;
    }

    void Decode();

    bool CheckMatching(Turn* turn) const;

    char* Data() { return data_; }
    std::vector<Coord*> Coords() const { return coords_; }
    bool Capture() const { return capture_; }

private:
    const char kXMin = 'a';     // COORDONATA X MINIMA
    const char kYMin = '1';     // COORDONATA Y MINIMA

    void Encode();

    char data_[kDataLength];
    std::vector<Coord*> coords_;
    bool capture_;
};

#endif // TURN_H_
