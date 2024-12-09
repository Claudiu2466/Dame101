/**
 * @file coord.h
 * @brief Header-ul pentru clasa Coord.
 *
 * @mainpage
 * # Proiect: Dame101
 * - **Autor:** [B. Claudiu]
 * - **An:** 2024
 * - **Descriere:** Clasa `Coord` gestionează coordonatele pieselor pe tabla de joc, incluzând operații de comparare, atribuire și input/output.
 *
 * Clasa `Coord` include:
 * - Constructori și destructori pentru inițializarea și copierea obiectelor.
 * - Metode pentru compararea și manipularea coordonatelor.
 * - Operatorii pentru input și output din stream-uri.
 */

#ifndef COORD_H_
#define COORD_H_

#include <iostream>
#include <memory>  // pentru smart pointers

 /**
  * @class Coord
  * @brief Clasa care reprezintă coordonatele pieselor pe tabla de joc.
  *
  * Clasa `Coord` stochează informațiile despre poziția pieselor în joc,
  * compară și atribuie coordonatele și oferă metode utile pentru manipularea acestora.
  */
class Coord {
public:
    /**
     * @brief Constructor implicit.
     * @param new_x Coordonata X (implicit 0).
     * @param new_y Coordonata Y (implicit 0).
     */
    Coord(int new_x = 0, int new_y = 0)
        : x(new_x), y(new_y) {}

    /**
     * @brief Constructor de copiere.
     * @param other Referință la alt obiect `Coord`.
     */
    Coord(const Coord& other)
        : x(other.x), y(other.y) {}

    /**
     * @brief Destructor implicit.
     * Destructorul este implicit, deoarece nu sunt resurse dinamice.
     */
    ~Coord() = default;

    /**
     * @brief Operatorul de atribuire.
     * @param other Referință la alt obiect `Coord`.
     * @return Referință către obiectul curent.
     */
    Coord& operator=(const Coord& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    /**
     * @brief Operatorul de comparare.
     * Compară două coordonate pentru a vedea dacă sunt identice.
     * @param other Referință la alt obiect `Coord`.
     * @return `true` dacă coordonatele sunt identice.
     */
    bool operator==(const Coord& other) const {
        return (x == other.x && y == other.y);
    }

    /**
     * @brief Operatorul de citire din stream.
     * @param is Stream-ul de intrare.
     * @param coord Referință la obiectul `Coord`.
     * @return Stream-ul de intrare.
     */
    friend std::istream& operator>>(std::istream& is, Coord& coord) {
        is >> coord.x >> coord.y;
        return is;
    }

    /**
     * @brief Operatorul de afișare în stream.
     * @param os Stream-ul de ieșire.
     * @param coord Referință la obiectul `Coord`.
     * @return Stream-ul de ieșire.
     */
    friend std::ostream& operator<<(std::ostream& os, const Coord& coord) {
        os << "(" << coord.x << ", " << coord.y << ")";
        return os;
    }

    /**
     * @brief Metodă pentru a calcula media între două coordonate.
     * @param coord Referință la alt obiect `Coord`.
     * @return Obiect `Coord` cu media coordonatelor X și Y.
     */
    Coord Average(const Coord& coord) const {
        return Coord((x + coord.x) / 2, (y + coord.y) / 2);
    }

    /**
     * @brief Metodă pentru compararea coordonatelor.
     * @param coord Referință la alt obiect `Coord`.
     * @return `true` dacă obiectele `Coord` sunt identice.
     */
    bool Equal(const Coord& coord) const {
        return *this == coord;
    }

    int x;  ///< Coordonata X pe tabla de joc.
    int y;  ///< Coordonata Y pe tabla de joc.
};

#endif // COORD_H_
