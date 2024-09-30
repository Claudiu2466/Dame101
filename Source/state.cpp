#include "state.h"

#include <iostream>


State::State() : o_count_(0), x_count_(0) {
    int index = 0;

    // initializare tabla joc
    for (int y = 1; y <= kBoardSize; ++y) {
        for (int x = 1; x <= kBoardSize; ++x) {
            if ((x & 1) == (y & 1)) {             // spatiu permis
                if (y <= 3) {                       // jucatorul o
                    data_[index] = kValidPlayerO;
                    ++o_count_;
                }
                else if (y >= 6) {                  // jucatorul x
                    data_[index] = kValidPlayerX;
                    ++x_count_;
                }
                else {                              // spatiu gol
                    data_[index] = kLegalSpace;
                }
            }
            else {                                // spatiu interzis
                data_[index] = kIllegaleSpace;
            }
            ++index;
        }
    }

    // jucatorul o merge primul
    data_[index++] = kValidPlayerO;

    // sfarsit de sir
    data_[index] = '\0';
}

void State::BuildListValidTurns() {
    // resetare
    valid_turns_.clear();
    forced_capture_ = false;

    // verifica miscari posibile pentru fiecare piesa
    for (int y = 0; y < kBoardSize; ++y) {
        for (int x = 0; x < kBoardSize; ++x) {
            Coord* coord = new Coord(x, y);
            if (IsOwnPiece(coord)) {
                CheckValidTurns(coord);
            }
        }
    }

    // joc sfarsit
    if (valid_turns_.size() == 0) {
        char opponent = GetOpponent();
        SetPlayer(opponent - kManKingDiff);
    }

    // capturare fortata
    if (forced_capture_) {
        auto iterator = valid_turns_.begin();
        while (iterator != valid_turns_.end()) {
            if ((*iterator)->Capture()) {
                ++iterator;
            }
            else {
                iterator = valid_turns_.erase(iterator);
            }
        }
    }


}

void State::Print() const {
    const char kHRuler[] = "  a b c d e f g h";
    std::cout << kHRuler << "\n";
    int index = kBoardSize * kBoardSize - kBoardSize;
    for (int y = kBoardSize; y > 0; --y) {
        std::cout << y << " ";
        for (int x = 0; x < kBoardSize; ++x) {
            std::cout << data_[index++] << " ";
        }
        std::cout << y << "\n";
        index -= (kBoardSize << 1);
    }
    std::cout << kHRuler << std::endl;
}

bool State::CheckMatchingVaildTurn(Turn* turn) const {
    for (auto valid_turn : valid_turns_) {
        if (valid_turn->CheckMatching(turn)) {
            return true;
        }
    }
    return false;
}

void State::Move(Turn* turn) {
    std::vector<Coord*> coords = turn->Coords();
    char player = GetPlayer();
    char piece = GetPiece(coords[0]);
    bool king = IsKing(coords[0]);
    int last_coord_index = coords.size() - 1;

    SetPiece(coords[0], kLegalSpace);

    // daca sare
    if (turn->Capture()) {
        for (int i = 0; i < last_coord_index; ++i) {
            Coord* mid_coord = coords[i]->Average(coords[i + 1]);
            SetPiece(coords[i], kLegalSpace);
            SetPiece(mid_coord, kLegalSpace);
        }
    }

    // incoronare
    if (player == kValidPlayerO && coords[last_coord_index]->y == kBoardSize - 1
        || player == kValidPlayerX && coords[last_coord_index]->y == 0) {
        if (!king) {
            piece -= kManKingDiff;
        }
    }

    // ultima coord
    SetPiece(coords[last_coord_index], piece);
}

void State::SetNextPlayer() {
    if (GetPlayer() == kValidPlayerO) {
        data_[kIdIndex] = kValidPlayerX;
    }
    else {
        data_[kIdIndex] = kValidPlayerO;
    }
}

void State::SetInvalidTurn() {
    if (GetPlayer() == kValidPlayerO) {
        data_[kIdIndex] = kInvalidPlayerO;
    }
    else {
        data_[kIdIndex] = kInvalidPlayerX;
    }
}

char State::GetPlayer() const {
    if (data_[kIdIndex] == kValidPlayerO
        || data_[kIdIndex] == kInvalidPlayerO
        || data_[kIdIndex] == kWinningPlayerO) {
        return kValidPlayerO;
    }
    else {
        return kValidPlayerX;
    }
}

int State::GetWinnerCode() const {
    if (data_[kIdIndex] == kWinningPlayerO) {
        return 1;
    }
    if (data_[kIdIndex] == kWinningPlayerX) {
        return 2;
    }
    return 0;
}

void State::CheckValidTurns(Coord* coord) {
    std::vector<Coord*> coords;
    coords.push_back(coord);
    bool king = IsKing(coord);
    Coord* new_coord;

    // sare
    new_coord = new Coord(coord->x - 2, coord->y - 2);    // stanga jos
    CheckValidJumpTurns(coord, new_coord, coords, king);
    new_coord = new Coord(coord->x + 2, coord->y - 2);    // dreapta jos
    CheckValidJumpTurns(coord, new_coord, coords, king);
    new_coord = new Coord(coord->x - 2, coord->y + 2);    // stanga sus
    CheckValidJumpTurns(coord, new_coord, coords, king);
    new_coord = new Coord(coord->x + 2, coord->y + 2);    // dreapta sus
    CheckValidJumpTurns(coord, new_coord, coords, king);

    // merge
    if (!forced_capture_) {
        CheckValidMoveTurns(coord);
    }
}

bool State::CheckValidJumpTurns(
    Coord* pre_coord, Coord* new_coord, std::vector<Coord*> coords, bool king) {
    if (IsJumpable(pre_coord, new_coord, king)) {
        coords.push_back(new_coord);
        bool child = false;
        Coord* next_coord;

        // saritura avansata
        next_coord = new Coord(new_coord->x - 2, new_coord->y - 2);   // stanga jos
        if (!pre_coord->Equal(next_coord)) {
            child = CheckValidJumpTurns(new_coord, next_coord, coords, king) || child;
        }
        next_coord = new Coord(new_coord->x + 2, new_coord->y - 2);   // dreapta jos
        if (!pre_coord->Equal(next_coord)) {
            child = CheckValidJumpTurns(new_coord, next_coord, coords, king) || child;
        }
        next_coord = new Coord(new_coord->x - 2, new_coord->y + 2);   // stanga sus
        if (!pre_coord->Equal(next_coord)) {
            child = CheckValidJumpTurns(new_coord, next_coord, coords, king) || child;
        }
        next_coord = new Coord(new_coord->x + 2, new_coord->y + 2);   // dreapta sus
        if (!pre_coord->Equal(next_coord)) {
            child = CheckValidJumpTurns(new_coord, next_coord, coords, king) || child;
        }

        if (!child) {
            forced_capture_ = true;
            AddValidJumpTurn(coords);
        }
        return true;
    }
    else {
        return false;
    }
}

void State::CheckValidMoveTurns(Coord* coord) {
    Coord* new_coord;

    new_coord = new Coord(coord->x - 1, coord->y - 1);        // stanga jos
    if (IsMovable(coord, new_coord)) {
        AddValidMoveTurn(coord, new_coord);
    }
    new_coord = new Coord(coord->x + 1, coord->y - 1);        // dreapta jos
    if (IsMovable(coord, new_coord)) {
        AddValidMoveTurn(coord, new_coord);
    }
    new_coord = new Coord(coord->x - 1, coord->y + 1);        // stanga sus
    if (IsMovable(coord, new_coord)) {
        AddValidMoveTurn(coord, new_coord);
    }
    new_coord = new Coord(coord->x + 1, coord->y + 1);        // dreapta sus
    if (IsMovable(coord, new_coord)) {
        AddValidMoveTurn(coord, new_coord);
    }
}

void State::AddValidJumpTurn(const std::vector<Coord*> coords) {
    valid_turns_.push_back(new Turn(coords, true));
}

void State::AddValidMoveTurn(Coord* pre_coord, Coord* new_coord) {
    std::vector<Coord*> coords;
    coords.push_back(pre_coord);
    coords.push_back(new_coord);
    valid_turns_.push_back(new Turn(coords, false));
}

bool State::IsValidCoord(const Coord* coord) const {
    return (coord->x >= 0 && coord->x < kBoardSize
        && coord->y >= 0 && coord->y < kBoardSize);
}

bool State::IsOwnPiece(const Coord* coord) const {
    char player = GetPlayer();
    char piece = GetPiece(coord);

    if (piece == player || piece == player - kManKingDiff) {
        return true;
    }
    else {
        return false;
    }
}

bool State::IsOpponentPiece(const Coord* coord) const {
    char opponent = GetOpponent();
    char piece = GetPiece(coord);

    if (piece == opponent || piece == opponent - kManKingDiff) {
        return true;
    }
    else {
        return false;
    }
}

bool State::IsLegal(const Coord* coord) const {
    return GetPiece(coord) == kLegalSpace;
}

bool State::IsKing(const Coord* coord) const {
    char piece = GetPiece(coord);
    return piece >= 'A' && piece <= 'Z';
}

bool State::IsValidDirection(Coord* pre_coord, Coord* new_coord) const {
    char player = GetPlayer();
    int stepY = new_coord->y - pre_coord->y;
    if (player == kValidPlayerO && stepY > 0
        || player == kValidPlayerX && stepY < 0) {
        return true;
    }
    return false;
}

bool State::IsMovable(Coord* pre_coord, Coord* new_coord) const {
    if (IsValidCoord(new_coord) && IsLegal(new_coord)
        && (IsValidDirection(pre_coord, new_coord) || IsKing(pre_coord))) {
        return true;
    }
    return false;
}

bool State::IsJumpable(Coord* pre_coord, Coord* new_coord, bool king) const {
    if (IsValidCoord(new_coord) && IsLegal(new_coord)
        && (IsValidDirection(pre_coord, new_coord) || king)) {
        Coord* mid_coord = pre_coord->Average(new_coord);
        if (IsOpponentPiece(mid_coord)) {
            return true;
        }
    }
    return false;
}

char State::GetOpponent() const {
    char player = GetPlayer();
    if (player == kValidPlayerO) {
        return kValidPlayerX;
    }
    else {
        return kValidPlayerO;
    }
}

void State::SetPlayer(const char player) {
    data_[kIdIndex] = player;
}

void State::SetPiece(const Coord* coord, const char piece) {
    data_[coord->y * kBoardSize + coord->x] = piece;
}

char State::GetPiece(const Coord* coord) const {
    return data_[coord->y * kBoardSize + coord->x];
}
