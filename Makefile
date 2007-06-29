CXXFLAGS=-I/opt/local/include -g
LDFLAGS=-L/opt/local/lib -lgmp -lgmpxx

OBJ=SimpleFactorization.o

all: simple-factorization

simple-factorization: main.o $(OBJ)
	g++ $(LDFLAGS) -o $@ $< $(OBJ)


clean:
	rm -f *.o simple-factorization
