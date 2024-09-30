all: Dame101

Dame101: state.o turn.o main.o 
    g++ -o Dame101.exe state.o turn.o main.o

state.o:
    g++ state.cpp -o state.o -c

turn.o:
    g++ turn.cpp -o turn.o -c

main.o:
    g++ main.cpp -o main.o -c


clean:
    rm -f *.o *.exe