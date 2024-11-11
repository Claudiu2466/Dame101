#include <iostream>
#include "state.h"
#include "turn.h"

// Functie care afiseaza meniul principals
void DisplayMainMenu() {
    std::cout << "Bun Venit la jocul de dame!\n";
    std::cout << "=============================\n";
    std::cout << "Instructii:\n";
    std::cout << "1. Jocul are loc pe o tabla 8x8.\n";
    std::cout << "2. Jucatorii merg unul dupa altul.\n";
    std::cout << "3. Figurile se misca pe diagonala.\n";
    std::cout << "4. Controlul asupra pieselor are loc in modul urmator: Se scrie in consola spre exemplu (a3 b4) unde a3 este coordonata in care piesa se afla inainte de miscare iar b4 este coordonata unde dorim sa mutam piesa. Analog au loc restul miscarilor.\n";
    std::cout << "5. O piesa poate inlatura o alta piesa adversara sarind peste aceasta.\n";
    std::cout << "6. Jocul se termina cand unul din jucatori nu mai are miscari posibile.\n";
    std::cout << "7. Jucatorul cu mai multe piese sau care forteaza adversarul in a nu mai avea miscari posibile, castiga.\n";
    std::cout << "\nMeniu:\n";
    std::cout << "1. Incepe Jocul\n";
    std::cout << "2. Iesi\n";
    std::cout << "Alege o optiune (1 sau 2): ";
}

int main(int argc, char* argv[]) {
    int choice;
    while (true) {
        DisplayMainMenu();
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            // Incepe jocul
            State* state = new State();
            Turn* turn = new Turn();

            while (true) {
                // Creaza lista de miscari posibile
                state->BuildListValidTurns();

                // Printeaza tabla de joc
                state->Print();

                // Alege jucatorul curent
                char player = state->GetPlayer();

                // Verifica daca jocul e finisat
                int winner_code = state->GetWinnerCode();
                if (winner_code > 0) {
                    std::cout << "\n-- jucatorul " << player << " castiga\n" << std::endl;
                    delete state;
                    delete turn;
                    return winner_code;
                }

                // Asteapta pentru player-input
                std::cout << "\njucatorul '" << player << "'> ";
                std::cin.clear();
                std::cin.getline(turn->Data(), Turn::kDataLength);
                std::cout << std::endl;

                // Verifica daca miscrea e valida
                if (state->CheckMatchingVaildTurn(turn)) {
                    // decodeaza inputul jucatorului intr-o lista de coordonate
                    turn->Decode();

                    // opereaza miscarea
                    state->Move(turn);

                    // urmatorul jucator preia miscarea
                    state->SetNextPlayer();
                }
                else {
                    // Input nevalid
                    std::cout << "-- miscare incorecta\n" << std::endl;
                    state->SetInvalidTurn();
                }
            }
        }
        else if (choice == 2) {
            // Iesire din joc
            std::cout << "Multumim pentru joc!\n";
            return 0;
        }
        else {
            std::cout << "Alegere incorecta. Va rugam sa alegeti intre 1 si 2.\n";
        }
    }
}
