// coord.h
// COORDONATELE TABLEI DE JOC

#ifndef COORD_H_
#define COORD_H_

#include <iostream>
#include <memory>

class Coord {
public:
    // constructor implicit
    Coord(int new_x = 0, int new_y = 0)
        : x(new_x), y(new_y) {}

    // constructor de copiere
    Coord(const Coord& other)
        : x(other.x), y(other.y) {}

    // destructor
    ~Coord() = default; // utilizam destructorul implicit

    // operator de atribuire
    Coord& operator=(const Coord& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    // operator de comparare
    bool operator==(const Coord& other) const {
        return (x == other.x && y == other.y);
    }

    // operator de citire
    friend std::istream& operator>>(std::istream& is, Coord& coord) {
        is >> coord.x >> coord.y;
        return is;
    }

    // operator de afisare
    friend std::ostream& operator<<(std::ostream& os, const Coord& coord) {
        os << "(" << coord.x << ", " << coord.y << ")";
        return os;
    }

    // Metoda pentru media coordonatelor
    Coord Average(const Coord& coord) const {
        return Coord((x + coord.x) / 2, (y + coord.y) / 2);
    }

    // Metoda pentru compararea coordonatelor
    bool Equal(const Coord& coord) const {
        return *this == coord;
    }

    int x;
    int y;
};

#endif // COORD_H_
