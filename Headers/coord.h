// coord.h
// COORDONATELE TABLEI DE JOC

#ifndef COORD_H_
#define COORD_H_

#include <iostream>

struct Coord {
    // constructor implicit
    Coord(int new_x = 0, int new_y = 0);

    // constructor de copiere
    Coord(const Coord& other);

    // destructor
    ~Coord();

    // operator de atribuire
    Coord& operator=(const Coord& other);

    // operator de comparare
    bool operator==(const Coord& other) const;

    // operator de citire
    friend std::istream& operator>>(std::istream& is, Coord& coord);

    // operator de afisare
    friend std::ostream& operator<<(std::ostream& os, const Coord& coord);

    // Metoda pentru media coordonatelor
    Coord Average(const Coord& coord) const;

    // Metoda pentru compararea coordonatelor
    bool Equal(const Coord& coord) const;

    int x;
    int y;
};

#endif // COORD_H_
