// 
// COORDONATELE TABLEI DE JOC
//

#ifndef COORD_H_
#define COORD_H_

#include <iostream>

struct Coord {
    // constructor implicit
    Coord(int new_x = 0, int new_y = 0) : x(new_x), y(new_y) {}

    // constructor de copiere
    Coord(const Coord& other) : x(other.x), y(other.y) {}

    // destructor
    ~Coord() {}

    // constructor cu parametrii
    Coord& operator=(const Coord& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    // operator de comparare
    bool operator==(const Coord& other) const {
        return x == other.x && y == other.y;
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
        return Coord((x + coord.x) >> 1, (y + coord.y) >> 1);
    }

    // Metoda pentru compararea coordonatelor
    bool Equal(const Coord& coord) const {
        return x == coord.x && y == coord.y;
    }

    int x;
    int y;
};

#endif // COORD_H_
