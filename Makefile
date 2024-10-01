# Definim compilatorul și opțiunile
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Fișierul executabil
EXEC = Dame101.exe

# Fișiere obiect
OBJS = state.o turn.o main.o

# Ținta principală: creare executabil
all: $(EXEC)

# Regulă pentru a lega fișierele obiect într-un executabil
$(EXEC): $(OBJS)
	$(CXX) -o $(EXEC) $(OBJS)

# Regulă pentru fiecare fișier obiect
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Curățare fișiere obiect și executabil
clean:
	rm -f *.o *.exe
