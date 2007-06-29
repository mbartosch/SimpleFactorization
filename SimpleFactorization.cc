#include "SimpleFactorization.h"
#include <gmpxx.h>
#include <iostream>

using namespace std;

SimpleFactorization::SimpleFactorization(mpz_class &arg) {
  candidate = arg;
  this->setRange(2, sqrt(arg));
  factor = 0;
}

SimpleFactorization::SimpleFactorization(const char* arg) {
  candidate.set_str(arg, 10);
  this->setRange(2, sqrt(candidate));
  factor = 0;
}

bool SimpleFactorization::factorize() {
  if (range_max < range_min)
    return false;

  factor = range_min;
  if (factor < 2)
    factor = 2;

  while (factor <= range_max) {
    if (mpz_divisible_p(candidate.get_mpz_t(), 
			factor.get_mpz_t())) {
      return 1;
    }
    factor++;
    if (mpz_even_p(factor.get_mpz_t()))
      factor++;
  }
  return false;
}


void SimpleFactorization::setMin(const mpz_class &min) {
  range_min = 2;

  if (min > 2)
    range_min = min;

  range_int = range_max - range_min;
}

void SimpleFactorization::setMin(const char* min) {
  mpz_class tmp(min);
  this->setMin(tmp);
}

const mpz_class& SimpleFactorization::getMin() {
  return range_min;
}

const mpz_class& SimpleFactorization::getMax() {
  return range_max;
}

void SimpleFactorization::setMax(const mpz_class &max) {
  range_max = sqrt(candidate);
  
  if (max < range_max)
    range_max = max;

  range_int = range_max - range_min;
}

void SimpleFactorization::setMax(const char* max) {
  mpz_class tmp(max);
  this->setMax(tmp);
}


void SimpleFactorization::setRange(const mpz_class &min, const mpz_class &max) {
  this->setMin(min);
  this->setMax(max);
}
void SimpleFactorization::setRange(const char* min, const char* max) {
  this->setMin(min);
  this->setMax(max);
}

const mpz_class& SimpleFactorization::getFactor() {
  return factor;
}

const mpz_class& SimpleFactorization::getCandidate() {
  return candidate;
}

double SimpleFactorization::getProgress() {
  mpf_class total = factor - range_min;
  mpf_class progress = 0;

  if (range_int > 0) {
    progress = total / range_int;
  }
  return progress.get_d();
}
