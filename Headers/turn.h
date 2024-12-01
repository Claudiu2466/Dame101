// turn.h
#ifndef TURN_H_
#define TURN_H_

#include "coord.h"
#include <vector>
#include <string>
#include <memory>  // pentru smart pointers

class Turn {
public:
    // constructor implicit
    Turn();

    // constructor cu parametrii
    Turn(const std::vector<std::shared_ptr<Coord>>& coords, bool capture);

    // constructor de copiere
    Turn(const Turn& other);

    // destructor
    ~Turn() = default;

    // operator de atribuire
    Turn& operator=(const Turn& other);

    // operator de comparare
    bool operator==(const Turn& other) const;

    // operator de citire
    friend std::istream& operator>>(std::istream& is, Turn& turn);

    // operator de afisare
    friend std::ostream& operator<<(std::ostream& os, const Turn& turn);

    void Decode();
    bool CheckMatching(const std::shared_ptr<Turn>& turn) const;
    void Encode();
    const std::string& Data() const;
    const std::vector<std::shared_ptr<Coord>>& Coords() const;
    bool Capture() const;

private:
    std::vector<std::shared_ptr<Coord>> coords_;  // Folosim smart pointers pentru coordonate
    bool capture_;
    std::string data_;  // Folosim std::string pentru date
};

#endif // TURN_H_
