#include <gmpxx.h>
#include <iostream>
using namespace std;

#if 0
int factorize(const mpz_class &range1_min, const mpz_class &range1_max,
	      const mpz_class &range2_min, const mpz_class &range2_max) {

  range1_min = 10;
  range1_max = 40;

  range2_min = 100;
  range2_max = 110;


  ii = range1_min;
  while (ii < range1_max) {
    // find probable prime
    while (mpz_probab_prime_p(ii.get_mpz_t(), 5) == 0)
      ii++;
    
    cout << ii << " * ";

    jj = range2_min;
    // find probable prime
    while (jj < range2_max) {
      while (mpz_probab_prime_p(jj.get_mpz_t(), 5) == 0)
	jj++;

      // cout << jj << ",";

      if (ii * jj == candidate) {
	cout << endl << "Found tuple: (" << ii << ", " << jj << ")" << endl;
	return 1;
      }
      jj += 2;
    }
    cout << endl;

    ii += 2;
  }
}
#endif



int main(int argc, char **argv) {
  mpz_class candidate = 3103;
  mpz_class range1_min, range1_max;
  mpz_class range2_min, range2_max;
  mpz_class ii, jj;

  
  range1_min = 10;
  range1_max = 40;

  range2_min = 100;
  range2_max = 110;


  ii = range1_min;
  while (ii < range1_max) {
    // find probable prime
    while (mpz_probab_prime_p(ii.get_mpz_t(), 5) == 0)
      ii++;
    
    cout << ii << " * ";

    jj = range2_min;
    // find probable prime
    while (jj < range2_max) {
      while (mpz_probab_prime_p(jj.get_mpz_t(), 5) == 0)
	jj++;

      // cout << jj << ",";

      if (ii * jj == candidate) {
	cout << endl << "Found tuple: (" << ii << ", " << jj << ")" << endl;
	return 1;
      }
      jj += 2;
    }
    cout << endl;

    ii += 2;
  }
  return 0;

}

