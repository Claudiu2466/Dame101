#include <iostream>
#include <memory>
#include <string>
#include "state.h"
#include "turn.h"

// Functie care afiseaza meniul principal
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
            // incepe jocul
            auto state = std::make_unique<State>(); // Folosim std::unique_ptr pentru State
            auto turn = std::make_unique<Turn>();   // Folosim std::unique_ptr pentru Turn

            while (true) {
                // Creaza lista de miscari posibile
                state->BuildListValidTurns();

                // Printeaza tabla de joc
                state->Print();

                // Alege jucatorul curent
                char player = state->GetPlayer();

                // Verifica daca jocul s-a terminat
                int winner_code = state->GetWinnerCode();
                if (winner_code > 0) {
                    std::cout << "\n-- Jucatorul " << player << " castiga\n" << std::endl;
                    return winner_code;
                }

                // asteapta inputul jucatorului
                std::cout << "\nJucatorul '" << player << "'> ";
                std::string move_input;
                std::getline(std::cin, move_input);

                // Verifica daca miscarea este valida
                turn->SetData(move_input); // Folosim functia SetData pentru a seta inputul
                if (state->CheckMatchingVaildTurn(turn)) {
                    // Decodeaza inputul jucatorului intr-o lista de coordonate
                    turn->Decode();

                    // Opereaza miscarea
                    state->Move(turn);

                    // Urmatorul jucator preia miscarea
                    state->SetNextPlayer();
                }
                else {
                    // Input nevalid
                    std::cout << "-- Miscare incorecta\n" << std::endl;
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
