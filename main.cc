#include <iostream>
#include <gmpxx.h>
#include "SimpleFactorization.h"
#include "SimpleFactorizationBinary.h"

using namespace std;


int main(int argc, char **argv) {
  // 4801 * 10093 = 48456493
  mpz_class candidate = 48456493;
  // SimpleFactorization factorizer;
  SimpleFactorizationBinary factorizer;
  double progress;

  factorizer.setRange1(0, 15000);
  factorizer.setRange2(0, 15000);

  if (factorizer.factorize(candidate)) {
    mpz_class f1, f2;
    f1 = factorizer.getFactor1();
    f2 = factorizer.getFactor2();

    cout << endl 
	 << "Found factorization: " 
	 << f1 << " * " << f2
	 << " = " << candidate << endl;

    progress = factorizer.getProgress();
    cout << "Pct: " << progress << endl;
    
  }
}

