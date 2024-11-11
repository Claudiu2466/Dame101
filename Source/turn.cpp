// turn.cpp
#include "turn.h"
#include <sstream>
#include <cstring>

// constructor implicit
Turn::Turn() : capture_(false) {}

// constructor cu parametrii
Turn::Turn(const std::vector<Coord*>& coords, bool capture)
    : coords_(coords), capture_(capture) {
    Encode();
}

// constructor de copiere
Turn::Turn(const Turn& other)
    : coords_(other.coords_), capture_(other.capture_) {
    std::copy(std::begin(other.data_), std::end(other.data_), std::begin(data_));
}

// destructor
Turn::~Turn() {
    for (Coord* coord : coords_) {
        delete coord; // elimina coordonatele alocate dinamic
    }
}

// operator de atribuire
Turn& Turn::operator=(const Turn& other) {
    if (this != &other) {
        for (Coord* coord : coords_) {
            delete coord; // eliberăm memoria pentru coordonatele vechi
        }
        coords_ = other.coords_;
        capture_ = other.capture_;
        std::copy(std::begin(other.data_), std::end(other.data_), std::begin(data_));
    }
    return *this;
}

// operator de comparare
bool Turn::operator==(const Turn& other) const {
    return capture_ == other.capture_ && std::string(data_) == std::string(other.data_);
}

// operator de citire
std::istream& operator>>(std::istream& is, Turn& turn) {
    std::string input;
    is >> input;

    return is;
}

// operator de afisare
std::ostream& operator<<(std::ostream& os, const Turn& turn) {
    os << "Capture: " << (turn.capture_ ? "Yes" : "No") << ", Coords: ";
    for (const auto& coord : turn.coords_) {
        os << *coord << " ";
    }
    return os;
}

void Turn::Decode() {
    // sterge vectorul coordonatelor
    coords_.clear();

    std::istringstream iss(data_);
    std::string token;
    while (iss >> token) {
        Coord* coord = new Coord(token[0] - kXMin, token[1] - kYMin);
        coords_.push_back(coord);
    }
}

bool Turn::CheckMatching(Turn* turn) const {
    turn->capture_ = capture_;
    std::string str1(data_);
    std::string str2(turn->Data());
    return str1.compare(str2) == 0;
}

void Turn::Encode() {
    int coords_size = coords_.size();

    int index = 0;
    for (int i = 0; i < coords_size; ++i) {
        data_[index++] = coords_[i]->x + kXMin;
        data_[index++] = coords_[i]->y + kYMin;
        data_[index++] = ' ';
    }
    data_[--index] = '\0'; // sfarsit de sir
}

char* Turn::Data() {
    return data_;
}

std::vector<Coord*> Turn::Coords() const {
    return coords_;
}

bool Turn::Capture() const {
    return capture_;
}
