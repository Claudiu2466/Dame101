/**
 * @file turn.h
 * @brief Header-ul pentru clasa Turn.
 *
 * @mainpage
 * # Proiect: Dame101
 * - **Autor:** [B. Claudiu]
 * - **An:** 2024
 * - **Descriere:** Această clasă reprezintă mutările în jocul de Checkers. Fiecare mutare include pozițiile pieselor, verificările validității și salvarea/încărcarea datelor în format string.
 *
 * Clasa `Turn` gestionează:
 * - Mutările pieselor în joc.
 * - Verificarea și compararea mutărilor.
 * - Codificarea și decodificarea mutărilor în date.
 */

#ifndef TURN_H_
#define TURN_H_

#include "coord.h"
#include <vector>
#include <string>
#include <memory>  // pentru smart pointers

 /**
  * @class Turn
  * @brief Clasa care reprezintă o mutare în jocul de Checkers.
  *
  * Clasa `Turn` este responsabilă pentru gestionarea:
  * - Pozițiilor pieselor implicate în mutare.
  * - Determinarea mutărilor valide și nevalide.
  * - Codificarea și decodificarea datelor mutării pentru salvare și comparare.
  */
class Turn {
public:
    /**
     * @brief Constructor implicit al clasei Turn.
     */
    Turn();

    /**
     * @brief Constructor cu parametrii pentru inițializarea mutării.
     * @param coords Vector de coordonate care definesc piesele implicate în mutare.
     * @param capture Flag care indică dacă mutarea implică captura unei piese.
     */
    Turn(const std::vector<std::shared_ptr<Coord>>& coords, bool capture);

    /**
     * @brief Constructor de copiere.
     * @param other Referință către alt obiect `Turn`.
     */
    Turn(const Turn& other);

    /**
     * @brief Destructor implicit.
     */
    ~Turn() = default;

    /**
     * @brief Operatorul de atribuire.
     * @param other Referință către alt obiect `Turn`.
     * @return Referință către obiectul curent.
     */
    Turn& operator=(const Turn& other);

    /**
     * @brief Operatorul de comparare.
     * @param other Referință către alt obiect `Turn`.
     * @return `true` dacă mutările sunt identice, `false` în caz contrar.
     */
    bool operator==(const Turn& other) const;

    /**
     * @brief Operatorul de citire din stream.
     * @param is Stream-ul de intrare.
     * @param turn Referință la obiectul `Turn`.
     * @return Stream-ul de intrare.
     */
    friend std::istream& operator>>(std::istream& is, Turn& turn);

    /**
     * @brief Operatorul de afișare în stream.
     * @param os Stream-ul de ieșire.
     * @param turn Referință la obiectul `Turn`.
     * @return Stream-ul de ieșire.
     */
    friend std::ostream& operator<<(std::ostream& os, const Turn& turn);

    /**
     * @brief Decodifică datele mutării într-o formă interpretabilă în joc.
     */
    void Decode();

    /**
     * @brief Verifică dacă o altă mutare este similară cu mutarea curentă.
     * @param turn Mutarea propusă pentru comparare.
     * @return `true` dacă mutările sunt identice.
     */
    bool CheckMatching(const std::shared_ptr<Turn>& turn) const;

    /**
     * @brief Encodează mutarea în datele necesare pentru salvare.
     */
    void Encode();

    /**
     * @brief Returnează datele mutării în format string.
     * @return Referință către string-ul `data_`.
     */
    const std::string& Data() const;

    /**
     * @brief Returnează referința la coordonatele implicate în mutare.
     * @return Vector-ul `coords_` cu coordonatele implicate în mutare.
     */
    const std::vector<std::shared_ptr<Coord>>& Coords() const;

    /**
     * @brief Verifică dacă mutarea implică o captura.
     * @return `true` dacă mutarea include captura unei piese, `false` în caz contrar.
     */
    bool Capture() const;

private:
    std::vector<std::shared_ptr<Coord>> coords_;  ///< Vector-ul de coordonate implicate în mutare.
    bool capture_;  ///< Flag-ul care indică dacă mutarea include captura.
    std::string data_;  ///< Datele mutării stocate în format string pentru salvare și comparare.
};

#endif  // TURN_H_
