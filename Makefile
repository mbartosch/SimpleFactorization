CXXFLAGS=-I/opt/local/include
LDFLAGS=-L/opt/local/lib -lgmp -lgmpxx


all: simple-factorization

simple-factorization: main.o
	g++ $(LDFLAGS) -o $@ $<


clean:
	rm -f *.o simple-factorization
