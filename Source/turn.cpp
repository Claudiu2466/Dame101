#include "turn.h"

#include <sstream>
#include <string>

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
    data_[--index] = '\0';    // sfarsit de sir
}

// destructor - adaugat pentru a preveni scurgerile de memorie
Turn::~Turn() {
    for (Coord* coord : coords_) {
        delete coord; // elimina coordonatele alocate dinamic
    }
}
