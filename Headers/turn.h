// turn.h
#ifndef TURN_H_
#define TURN_H_

#include "coord.h"
#include <vector>
#include <string>

class Turn {
public:
    // constructor implicit
    Turn();

    // constructor cu parametrii
    Turn(const std::vector<Coord*>& coords, bool capture);

    // constructor de copiere
    Turn(const Turn& other);

    // destructor
    ~Turn();

    // operator de atribuire
    Turn& operator=(const Turn& other);

    // operator de comparare
    bool operator==(const Turn& other) const;

    // operator de citire
    friend std::istream& operator>>(std::istream& is, Turn& turn);

    // operator de afisare
    friend std::ostream& operator<<(std::ostream& os, const Turn& turn);

    void Decode();
    bool CheckMatching(Turn* turn) const;
    void Encode();
    char* Data();
    std::vector<Coord*> Coords() const;
    bool Capture() const;

private:
    std::vector<Coord*> coords_;
    bool capture_;
    char data_[256]; // Adjust size as needed
};

#endif // TURN_H_
