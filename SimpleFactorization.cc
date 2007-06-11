#include "SimpleFactorization.h"
#include <gmpxx.h>

SimpleFactorization::SimpleFactorization() {
  range1_min = 0;
  range1_max = 0;
  range2_min = 0;
  range2_max = 0;

  factor1    = 0;
  factor2    = 0;
}

bool SimpleFactorization::factorize(const mpz_class &candidate) {
  if (range1_min * range2_min > candidate)
    return false;
  if (range1_max * range2_max < candidate)
    return false;

  factor1 = range1_min;
  while (factor1 <= range1_max) {
    // find probable prime
    while (mpz_probab_prime_p(factor1.get_mpz_t(), 5) == 0)
      factor1++;
    
    factor2 = range2_min;
    // find probable prime
    while (factor2 <= range2_max) {
      while (mpz_probab_prime_p(factor2.get_mpz_t(), 5) == 0)
	factor2++;

      if (factor1 * factor2 == candidate) {
	return true;
      }
      factor2 += 2;
    }

    factor1 += 2;
  }

  return false;
}

void SimpleFactorization::setRange1(const mpz_class &min, const mpz_class &max) {
  range1_min = min;
  range1_max = max;
  range1_int = range1_max - range1_min;
}

void SimpleFactorization::setRange2(const mpz_class &min, const mpz_class &max) {
  range2_min = min;
  range2_max = max;
}

const mpz_class& SimpleFactorization::getFactor1() {
  return factor1;
}

const mpz_class& SimpleFactorization::getFactor2() {
  return factor2;
}

double SimpleFactorization::getProgress() {
  if (range1_int > 0) {
    mpz_class total_progress;
    total_progress = (100 * (factor1 - range1_min)) / range1_int;
    return total_progress.get_ui() / 100.0;
  }
  return 0.0;
}
