#DEBUG=-DDEBUG
CXXFLAGS=-I/opt/local/include -O3 -g $(DEBUG)
LDFLAGS=-L/opt/local/lib -lgmp -lgmpxx

OBJ=SimpleFactorization.o

all: simple-factorization

simple-factorization: main.o $(OBJ)
	g++ $(LDFLAGS) -o $@ $< $(OBJ)


clean:
	rm -f *.o simple-factorization
