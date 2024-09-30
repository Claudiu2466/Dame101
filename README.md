# Dame
## Ce reprezinta acest proiect?
- Acest proiect este o mini reprezentare a jocului de tabla "Dame".
## Care sunt regulile de joc?
- Jocul de "Dame" se joaca in 2. In varianta digitala exista posibilitatea de a juca atat contra un jucator real cat si impotriva unui calculator.
### Exista 3 reguli de baza in "Dame":
- Damele se pot deplasa numai in diagonala pe patratele intunecate.
- La începutul jocului, piesele se pot deplasa doar înainte, adică spre partea adversarului.
- Damele se pot deplasa in sus si in jos atunci cand devin „regi” ajungand la ultimul rand al partii opuse.
## Explicatie claselor si structurilor de baza:

## `coord.h`

### Scop
Definește o structură de bază pentru a reprezenta coordonatele (x, y) într-un spațiu bidimensional. Este utilizată pentru a gestiona locațiile pe tabla de joc și pentru a realiza calculul pozițiilor.

### Structura `Coord`

#### Variabile de membru
- `int x`: Coordonația pe axa X.
- `int y`: Coordonația pe axa Y.

#### Constructor implicit
- `Coord()`: Inițializează `x` și `y` la 0. Este folosit atunci când nu se specifică explicit coordonatele.

#### Constructor cu parametri
- `Coord(int new_x, int new_y)`: Permite inițializarea coordonatelor cu valori specifice pentru `x` și `y`. Este folosit pentru a seta coordonate personalizate la crearea unui obiect `Coord`.

#### Metode

- `Coord* Average(Coord* coord)`: 
  - **Scop**: Calculează media coordonatelor între două obiecte `Coord`.
  - **Detaliu**: Ia coordonatele curente (`x` și `y`) și cele ale altui obiect `Coord` și calculează coordonatele medii. Rezultatul este returnat ca un nou obiect `Coord` creat dinamic.
  - **Îmbunătățire**: Ar fi mai sigur să folosești referințe constante pentru a evita manipulările accidentale și pentru a evita posibilele scurgeri de memorie.

- `bool Equal(Coord* coord)`:
  - **Scop**: Verifică dacă coordonatele curente sunt egale cu cele ale altui obiect `Coord`.
  - **Detaliu**: Compara valorile `x` și `y` ale obiectului curent cu cele ale obiectului referit de pointerul `coord`.

## `state.h`

### Scop
Reprezintă starea actuală a jocului, inclusiv tabla de joc și jucătorul activ. Gestionează validitatea mișcărilor și starea pieselor pe tablă.

### Clasa `State`

#### Variabile de membru
- `const static int kBoardSize`: Dimensiunea tablei de joc (8x8 în acest caz). Utilizată pentru a defini dimensiunea tablei și pentru a verifica limitele jocului.
- `char data_[kDataLength]`: Un tablou de caractere care stochează datele curente ale tablei de joc, inclusiv pozițiile pieselor și starea jocului.
- `std::vector<Turn*> valid_turns_`: Un vector care conține mișcările valide posibile pentru jucătorul curent. Utilizat pentru a gestiona și valida mișcările posibile.
- `bool forced_capture_`: Indicator care arată dacă o captura este forțată în joc.
- `int o_count_, x_count_`: Numără piesele fiecărui jucător pe tablă.

#### Metode publice

- `BuildListValidTurns()`:
  - **Scop**: Construieste lista mișcărilor valide posibile pentru jucătorul curent.
  - **Detaliu**: Identifică toate mișcările legale care pot fi efectuate pe baza stării curente a tablei și le stochează în `valid_turns_`.

- `Print() const`:
  - **Scop**: Afișează starea curentă a tablei de joc.
  - **Detaliu**: Imprimă reprezentarea textuală a tablei de joc în consola sau alt mediu de ieșire.

- `bool CheckMatchingVaildTurn(Turn* turn) const`:
  - **Scop**: Verifică dacă o mișcare specificată este validă.
  - **Detaliu**: Compară mișcarea oferită cu lista de mișcări valide și returnează `true` dacă se potrivește.

- `void Move(Turn* turn)`:
  - **Scop**: Efectuează mișcarea specificată pe tablă.
  - **Detaliu**: Actualizează tabloul de joc conform mișcării specificate.

- `void SetNextPlayer()`:
  - **Scop**: Schimbă jucătorul activ.
  - **Detaliu**: Comută între jucători, modificând starea activă a jucătorului.

#### Metode private

- `void CheckValidTurns(Coord* coord)`:
  - **Scop**: Verifică mișcările valide pentru o poziție specifică.
  - **Detaliu**: Identifică și validează toate mișcările posibile pentru o piesă aflată la coordonatele specificate.

- `bool CheckValidJumpTurns(...)` și `void CheckValidMoveTurns(Coord* coord)`:
  - **Scop**: Verifică mișcările valide de tip săritură și mișcările de bază.
  - **Detaliu**: Verifică dacă săriturile și mișcările normale sunt legale pe baza stării curente a tablei.

- `bool is_valid_coord(const Coord* coord) const`:
  - **Scop**: Verifică dacă coordonatele sunt valide pe tablă.
  - **Detaliu**: Asigură că coordonatele se află în limitele tablei de joc.

- `bool is_own_piece(const Coord* coord) const` și `bool is_opponent_piece(const Coord* coord) const`:
  - **Scop**: Verifică dacă coordonatele conțin o piesă a jucătorului curent sau a adversarului.

- `bool is_king(const Coord* coord) const`:
  - **Scop**: Verifică dacă piesa de la coordonatele date este un rege (în contextul jocului).

- `bool is_valid_direction(Coord* pre_coord, Coord* new_coord) const`:
  - **Scop**: Verifică dacă direcția mișcării este validă.

- `bool is_moveable(Coord* pre_coord, Coord* new_coord) const` și `bool is_jumpable(Coord* pre_coord, Coord* new_coord, bool king) const`:
  - **Scop**: Verifică dacă piesa poate fi mutată sau dacă este posibilă o săritură.

- `char get_opponent() const` și `void set_player(const char player)`:
  - **Scop**: Gestionază identificarea și schimbarea jucătorului curent.

- `void set_piece(const Coord* coord, const char piece)` și `char get_piece(const Coord* coord) const`:
  - **Scop**: Setează sau obține piesa de pe o coordonată specifică.

## `turn.h`

### Scop
Reprezintă o mișcare (săritură sau mișcare) pe tablă, incluzând coordonatele implicate și dacă mișcarea include captura pieselor. Este folosit pentru a codifica și decodifica mișcările.

### Clasa `Turn`

#### Variabile de membru
- `const static int kDataLength`: Dimensiunea maximă a datelor pentru o mișcare codificată.
- `char data_[kDataLength]`: Tabloul de caractere care stochează mișcarea codificată.
- `std::vector<Coord*> coords_`: Un vector de coordonate care reprezintă secvența de mișcare.
- `bool capture_`: Indică dacă mișcarea include captura unei piese.

#### Constructori

- `Turn()`: Constructor implicit.
- `Turn(const std::vector<Coord*> coords, const bool capture)`: Constructor care inițializează mișcarea cu coordonate specifice și flagul de captură.

#### Metode

- `void Encode()`:
  - **Scop**: Codifică coordonatele și captura într-un format de date compact.
  - **Detaliu**: Transformă coordonatele și informația de captură în formatul stocat în `data_`.

- `void Decode()`:
  - **Scop**: Decodifică datele codificate înapoi în coordonate și informații despre captura pieselor.
  - **Detaliu**: Transformă datele codificate în obiecte `Coord` și flagul de captură.
