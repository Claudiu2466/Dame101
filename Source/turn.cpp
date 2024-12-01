// turn.cpp
#include "turn.h"
#include <sstream>
#include <algorithm>
#include <iterator>
#include <memory>

// Constructor implicit
Turn::Turn() : capture_(false) {}

// Constructor cu parametrii
Turn::Turn(const std::vector<std::shared_ptr<Coord>>& coords, bool capture)
    : coords_(coords), capture_(capture) {
    Encode();
}

// Constructor de copiere
Turn::Turn(const Turn& other)
    : coords_(other.coords_), capture_(other.capture_) {
    std::copy(other.data_.begin(), other.data_.end(), std::back_inserter(data_));
}

// Destructor
Turn::~Turn() = default;  // Nu mai e nevoie sa eliberam manual memoria, deoarece folosim smart pointers

// Operator de atribuire
Turn& Turn::operator=(const Turn& other) {
    if (this != &other) {
        coords_ = other.coords_;
        capture_ = other.capture_;
        data_ = other.data_;
    }
    return *this;
}

// Operator de comparare
bool Turn::operator==(const Turn& other) const {
    return capture_ == other.capture_ && data_ == other.data_;
}

// Operator de citire
std::istream& operator>>(std::istream& is, Turn& turn) {
    std::string input;
    is >> input;
    std::istringstream iss(input);

    std::vector<std::shared_ptr<Coord>> coords;
    std::string token;
    while (iss >> token) {
        coords.push_back(std::make_shared<Coord>(token[0] - kXMin, token[1] - kYMin));
    }
    turn.coords_ = coords;
    return is;
}

// Operator de afisare
std::ostream& operator<<(std::ostream& os, const Turn& turn) {
    os << "Capture: " << (turn.capture_ ? "Yes" : "No") << ", Coords: ";
    for (const auto& coord : turn.coords_) {
        os << *coord << " ";
    }
    return os;
}

void Turn::Decode() {
    coords_.clear();
    std::istringstream iss(data_);
    std::string token;
    while (iss >> token) {
        coords_.push_back(std::make_shared<Coord>(token[0] - kXMin, token[1] - kYMin));
    }
}

bool Turn::CheckMatching(const Turn& turn) const {
    return capture_ == turn.capture_ && data_ == turn.data_;
}

void Turn::Encode() {
    std::ostringstream oss;
    for (const auto& coord : coords_) {
        oss << char(coord->x + kXMin) << char(coord->y + kYMin) << ' ';
    }
    data_ = oss.str();
}

const std::string& Turn::Data() const {
    return data_;
}

const std::vector<std::shared_ptr<Coord>>& Turn::Coords() const {
    return coords_;
}

bool Turn::Capture() const {
    return capture_;
}
