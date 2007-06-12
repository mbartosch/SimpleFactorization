CXXFLAGS=-I/opt/local/include
LDFLAGS=-L/opt/local/lib -lgmp -lgmpxx

OBJ=SimpleFactorization.o SimpleFactorizationBinary.o

all: simple-factorization

simple-factorization: main.o $(OBJ)
	g++ $(LDFLAGS) -o $@ $< $(OBJ)


clean:
	rm -f *.o simple-factorization
