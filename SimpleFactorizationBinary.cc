#include <iostream>
#include "SimpleFactorizationBinary.h"
#include <gmpxx.h>

using namespace std;

SimpleFactorizationBinary::SimpleFactorizationBinary() {
  range1_min = 0;
  range1_max = 0;
  range2_min = 0;
  range2_max = 0;

  factor1    = 0;
  factor2    = 0;
}

bool SimpleFactorizationBinary::factorize(const mpz_class &candidate) {
  mpz_class r2min, r2max;
  mpz_class prod;

  r2min = range2_min;
  r2max = range2_max;

  factor1 = range1_min;

  while (1) {
    while (mpz_probab_prime_p(factor1.get_mpz_t(), 5) == 0 && (factor1 <= range1_max))
      factor1++;
    if (factor1 >= range1_max)
      break;

    factor2 = r2min + (r2max - r2min) / 2;
    
    prod = factor1 * factor2;

    if (prod == candidate) {
      return true;
    }

    if (prod > candidate) {
      if (r2min < factor2 && factor2 < r2max) {
	r2max = factor2;
      } else {
	factor1 += 2;
	r2min = range2_min;
	r2max = range2_max;
      }
    } else {
      if (r2min < factor2 && factor2 < r2max) {
	r2min = factor2;
      } else {
	factor1 += 2;
	r2min = range2_min;
	r2max = range2_max;
      }
    }
    
    cout << endl;
  }
  

  return false;
}

