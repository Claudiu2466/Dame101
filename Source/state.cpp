#include "state.h"
#include <iostream>
#include <memory>
#include <algorithm>
#include <string>

// Constructor implicit
State::State() : o_count_(0), x_count_(0) {
    int index = 0;

    // Initializare tabla joc
    for (int y = 0; y < kBoardSize; ++y) {
        for (int x = 0; x < kBoardSize; ++x) {
            if ((x & 1) == (y & 1)) { // Spatiu permis
                if (y <= 3) { // Jucatorul O
                    data_[index] = kValidPlayerO;
                    ++o_count_;
                }
                else if (y >= 5) { // Jucatorul X
                    data_[index] = kValidPlayerX;
                    ++x_count_;
                }
                else { // Spatiu gol
                    data_[index] = kLegalSpace;
                }
            }
            else { // Spatiu interzis
                data_[index] = kIllegaleSpace;
            }
            ++index;
        }
    }

    // Jucatorul O merge primul
    data_[index++] = kValidPlayerO;
}

// Constructor de copiere
State::State(const State& other) {
    data_ = other.data_;
    valid_turns_ = other.valid_turns_;
    forced_capture_ = other.forced_capture_;
    o_count_ = other.o_count_;
    x_count_ = other.x_count_;
}

// Constructor cu parametrii
State::State(const std::string& data) {
    data_ = data;
    o_count_ = std::count(data_.begin(), data_.begin() + kIdIndex, kValidPlayerO);
    x_count_ = std::count(data_.begin(), data_.begin() + kIdIndex, kValidPlayerX);
}

// Operator de copiere
State& State::operator=(const State& other) {
    if (this != &other) {
        data_ = other.data_;
        valid_turns_ = other.valid_turns_;
        forced_capture_ = other.forced_capture_;
        o_count_ = other.o_count_;
        x_count_ = other.x_count_;
    }
    return *this;
}

// Operator de comparatie
bool State::operator==(const State& other) const {
    return data_ == other.data_;
}

// Operator de intrare
std::istream& operator>>(std::istream& is, State& state) {
    is >> state.data_;
    state.o_count_ = std::count(state.data_.begin(), state.data_.begin() + State::kIdIndex, State::kValidPlayerO);
    state.x_count_ = std::count(state.data_.begin(), state.data_.begin() + State::kIdIndex, State::kValidPlayerX);
    return is;
}

// Operator de afisare
std::ostream& operator<<(std::ostream& os, const State& state) {
    os << state.data_;
    return os;
}

void State::BuildListValidTurns() {
    valid_turns_.clear();
    forced_capture_ = false;

    // Verifica miscari posibile pentru fiecare piesa
    for (int y = 0; y < kBoardSize; ++y) {
        for (int x = 0; x < kBoardSize; ++x) {
            auto coord = std::make_shared<Coord>(x, y);
            if (IsOwnPiece(coord)) {
                CheckValidTurns(coord);
            }
        }
    }

    // Joc sfarsit
    if (valid_turns_.empty()) {
        char opponent = GetOpponent();
        SetPlayer(opponent - kManKingDiff);
    }

    // Capturare fortata
    if (forced_capture_) {
        valid_turns_.erase(
            std::remove_if(valid_turns_.begin(), valid_turns_.end(), [](const std::shared_ptr<Turn>& turn) {
                return !turn->Capture();
                }),
            valid_turns_.end()
        );
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

bool State::CheckMatchingVaildTurn(const std::shared_ptr<Turn>& turn) const {
    return std::any_of(valid_turns_.begin(), valid_turns_.end(),
        [&turn](const std::shared_ptr<Turn>& valid_turn) {
            return valid_turn->CheckMatching(turn);
        });
}

void State::Move(std::shared_ptr<Turn> turn) {
    auto coords = turn->Coords();
    char player = GetPlayer();
    char piece = GetPiece(coords[0]);
    bool king = IsKing(coords[0]);
    int last_coord_index = coords.size() - 1;

    SetPiece(coords[0], kLegalSpace);

    // Daca sare
    if (turn->Capture()) {
        for (int i = 0; i < last_coord_index; ++i) {
            auto mid_coord = coords[i]->Average(coords[i + 1]);
            SetPiece(coords[i], kLegalSpace);
            SetPiece(mid_coord, kLegalSpace);
        }
    }

    // Incronare
    if ((player == kValidPlayerO && coords[last_coord_index]->y == kBoardSize - 1) ||
        (player == kValidPlayerX && coords[last_coord_index]->y == 0)) {
        if (!king) {
            piece -= kManKingDiff;
        }
    }

    // Ultima coordonata
    SetPiece(coords[last_coord_index], piece);
}

void State::SetNextPlayer() {
    data_[kIdIndex] = (GetPlayer() == kValidPlayerO) ? kValidPlayerX : kValidPlayerO;
}

void State::SetInvalidTurn() {
    data_[kIdIndex] = (GetPlayer() == kValidPlayerO) ? kInvalidPlayerO : kInvalidPlayerX;
}

char State::GetPlayer() const {
    return (data_[kIdIndex] == kValidPlayerO || data_[kIdIndex] == kInvalidPlayerO || data_[kIdIndex] == kWinningPlayerO)
        ? kValidPlayerO : kValidPlayerX;
}

int State::GetWinnerCode() const {
    if (data_[kIdIndex] == kWinningPlayerO) return 1;
    if (data_[kIdIndex] == kWinningPlayerX) return 2;
    return 0;
}

// Restul metodelor care interactioneaza cu coordonatele
// De exemplu, metodele care adaugau valid_turns vor utiliza std::shared_ptr<Turn>

void State::AddValidJumpTurn(const std::vector<std::shared_ptr<Coord>>& coords) {
    valid_turns_.push_back(std::make_shared<Turn>(coords, true));
}

void State::AddValidMoveTurn(std::shared_ptr<Coord> pre_coord, std::shared_ptr<Coord> new_coord) {
    valid_turns_.push_back(std::make_shared<Turn>(std::vector<std::shared_ptr<Coord>>{pre_coord, new_coord}, false));
}

bool State::IsValidCoord(const std::shared_ptr<Coord>& coord) const {
    return (coord->x >= 0 && coord->x < kBoardSize
        && coord->y >= 0 && coord->y < kBoardSize);
}

bool State::IsOwnPiece(const std::shared_ptr<Coord>& coord) const {
    char player = GetPlayer();
    char piece = GetPiece(coord);

    return (piece == player || piece == player - kManKingDiff);
}

bool State::IsOpponentPiece(const std::shared_ptr<Coord>& coord) const {
    char opponent = GetOpponent();
    char piece = GetPiece(coord);

    return (piece == opponent || piece == opponent - kManKingDiff);
}

bool State::IsLegal(const std::shared_ptr<Coord>& coord) const {
    return GetPiece(coord) == kLegalSpace;
}

bool State::IsKing(const std::shared_ptr<Coord>& coord) const {
    char piece = GetPiece(coord);
    return piece >= 'A' && piece <= 'Z';
}

bool State::IsValidDirection(std::shared_ptr<Coord> pre_coord, std::shared_ptr<Coord> new_coord) const {
    char player = GetPlayer();
    int stepY = new_coord->y - pre_coord->y;
    return (player == kValidPlayerO && stepY > 0) || (player == kValidPlayerX && stepY < 0);
}

bool State::IsMovable(std::shared_ptr<Coord> pre_coord, std::shared_ptr<Coord> new_coord) const {
    return IsValidCoord(new_coord) && IsLegal(new_coord)
        && (IsValidDirection(pre_coord, new_coord) || IsKing(pre_coord));
}

bool State::IsJumpable(std::shared_ptr<Coord> pre_coord, std::shared_ptr<Coord> new_coord, bool king) const {
    if (IsValidCoord(new_coord) && IsLegal(new_coord)
        && (IsValidDirection(pre_coord, new_coord) || king)) {
        auto mid_coord = pre_coord->Average(new_coord);
        return IsOpponentPiece(mid_coord);
    }
    return false;
}

char State::GetOpponent() const {
    return (GetPlayer() == kValidPlayerO) ? kValidPlayerX : kValidPlayerO;
}

void State::SetPlayer(char player) {
    data_[kIdIndex] = player;
}

void State::SetPiece(std::shared_ptr<Coord> coord, char piece) {
    data_[coord->y * kBoardSize + coord->x] = piece;
}

char State::GetPiece(std::shared_ptr<Coord> coord) const {
    return data_[coord->y * kBoardSize + coord->x];
}
