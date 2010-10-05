#DEBUG=-DDEBUG
CXXFLAGS=-I/opt/local/include -O3 -g $(DEBUG)
LDFLAGS=-L/opt/local/lib -lgmp -lgmpxx

OBJ=simple-factorization.o SimpleFactorization.o

all: simple-factorization

simple-factorization: $(OBJ)
	g++ $(LDFLAGS) -o $@ $(OBJ)


clean:
	rm -f *.o simple-factorization
