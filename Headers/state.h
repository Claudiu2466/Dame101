/**
 * @file state.h
 * @brief Header-ul pentru clasa State.
 *
 * @mainpage
 * # Proiect: Dame101
 * - **Autor:** [B. Claudiu]
 * - **An:** 2024
 * - **Descriere:** Această clasă reprezintă starea jocului, inclusiv tabla de joc și jucătorul activ. Conține metodele necesare pentru mutări, verificarea validității mutărilor, salvarea și încărcarea stării din fișiere JSON și manipularea pieselor pe tablă.
 *
 * Clasa `State` gestionează:
 * - Tabla de joc de dimensiune 8x8.
 * - Mutările valabile și nevalabile ale pieselor.
 * - Compararea și copierea stării jocului.
 * - Salvarea și încărcarea stării jocului în format JSON.
 * - Identificarea câștigătorului jocului.
 */

#ifndef STATE_H_
#define STATE_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>  // pentru salvarea și încărcarea fișierelor JSON
#include <memory>   // pentru smart pointers
#include "turn.h"
#include "coord.h"
#include "json.hpp"

class Turn;

/**
 * @class State
 * @brief Clasa care reprezintă starea jocului și jucătorul activ.
 *
 * Clasa `State` este responsabilă pentru:
 * - Gestionarea mutărilor pieselor.
 * - Determinarea validității mutărilor și verificarea câștigătorului.
 * - Salvarea și încărcarea stării jocului din fișiere JSON.
 */
class State {
public:
    const static int kBoardSize = 8;  ///< Dimensiunea tablei de joc (8x8).
    const static int kIdIndex = kBoardSize * kBoardSize;  ///< Index-ul pentru identificarea datelor tablei.
    const static int kDataLength = kIdIndex + 1 + 1;  ///< Lungimea datelor jocului.

    /**
     * @brief Constructor implicit al clasei State.
     */
    State();

    /**
     * @brief Constructor de copiere.
     * @param other Referință către alt obiect `State` pentru copiere.
     */
    State(const State& other);

    /**
     * @brief Constructor cu parametri, inițializează starea jocului.
     * @param data String-ul care conține datele inițiale ale jocului.
     */
    State(const std::string& data);

    /**
     * @brief Destructor implicit.
     */
    ~State() = default;

    /**
     * @brief Operatorul de atribuire.
     * @param other Referință către alt obiect `State`.
     * @return Referință către obiectul curent.
     */
    State& operator=(const State& other);

    /**
     * @brief Operatorul de comparare.
     * @param other Referință către alt obiect `State`.
     * @return `true` dacă obiectele sunt identice, `false` în caz contrar.
     */
    bool operator==(const State& other) const;

    /**
     * @brief Operatorul de citire din stream.
     * @param is Stream-ul de intrare.
     * @param state Referință la obiectul `State`.
     * @return Stream-ul de intrare.
     */
    friend std::istream& operator>>(std::istream& is, State& state);

    /**
     * @brief Operatorul de afișare în stream.
     * @param os Stream-ul de ieșire.
     * @param state Referință la obiectul `State`.
     * @return Stream-ul de ieșire.
     */
    friend std::ostream& operator<<(std::ostream& os, const State& state);

    /**
     * @brief Construiește lista mutărilor valide.
     */
    void BuildListValidTurns();

    /**
     * @brief Afișează starea jocului.
     */
    void Print() const;

    /**
     * @brief Verifică dacă o mutare este validă în contextul jocului.
     * @param turn Mutarea propusă.
     * @return `true` dacă mutarea este validă.
     */
    bool CheckMatchingValidTurn(std::shared_ptr<Turn> turn) const;

    /**
     * @brief Mută o piesă conform unei mutări valide.
     * @param turn Mutarea propusă.
     */
    void Move(std::shared_ptr<Turn> turn);

    /**
     * @brief Setează următorul jucător activ.
     */
    void SetNextPlayer();

    /**
     * @brief Marchează o mutare ca fiind invalidă.
     */
    void SetInvalidTurn();

    /**
     * @brief Returnează jucătorul curent.
     * @return Caracterul reprezentând jucătorul activ.
     */
    char GetPlayer() const;

    /**
     * @brief Returnează codul câștigătorului.
     * @return Codul câștigătorului (valorile sunt specificate în constante).
     */
    int GetWinnerCode() const;

    /**
     * @brief Salvează starea jocului într-un fișier JSON.
     * @param filename Numele fișierului.
     */
    void SaveToJson(const std::string& filename) const;

    /**
     * @brief Încarcă starea jocului dintr-un fișier JSON.
     * @param filename Numele fișierului.
     */
    void LoadFromJson(const std::string& filename);

private:
    const static int kManKingDiff = 'a' - 'A';  ///< Diferența ASCII pentru regele om.
    const static char kLegalSpace = '.';       ///< Spațiul valid al tablei.
    const static char kIllegaleSpace = ' ';     ///< Spațiul invalid.
    const static char kValidPlayerO = 'o';      ///< Reprezentantul jucătorului O.
    const static char kValidPlayerX = 'x';      ///< Reprezentantul jucătorului X.
    const static char kInvalidPlayerO = 'p';    ///< Reprezentantul jucătorului invalid O.
    const static char kInvalidPlayerX = 'y';    ///< Reprezentantul jucătorului invalid X.
    const static char kWinningPlayerO = 'O';    ///< Reprezentantul câștigătorului O.
    const static char kWinningPlayerX = 'X';    ///< Reprezentantul câștigătorului X.

    void CheckValidTurns(Coord* coord);
    void CheckValidJumpTurns(Coord* pre_coord, Coord* new_coord, std::vector<Coord*> coords, bool king);
    void CheckValidMoveTurns(Coord* coord);
    void AddValidJumpTurn(const std::vector<Coord*> coords);
    void AddValidMoveTurn(Coord* pre_coord, Coord* new_coord);

    bool IsValidCoord(const Coord* coord) const;
    bool IsOwnPiece(const Coord* coord) const;
    bool IsOpponentPiece(const Coord* coord) const;
    bool IsLegal(const Coord* coord) const;
    bool IsKing(const Coord* coord) const;
    bool IsValidDirection(Coord* pre_coord, Coord* new_coord) const;
    bool IsMovable(Coord* pre_coord, Coord* new_coord) const;
    bool IsJumpable(Coord* pre_coord, Coord* new_coord, bool king) const;

    char GetOpponent() const;
    void SetPlayer(const char player);
    void SetPiece(const Coord* coord, const char piece);
    char GetPiece(const Coord* coord) const;

    std::string data_;
    std::vector<std::shared_ptr<Turn>> valid_turns_;
    bool forced_capture_;
    int o_count_;
    int x_count_;
};

#endif  // STATE_H_
