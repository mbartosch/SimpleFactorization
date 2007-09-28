#include "SimpleFactorization.h"
#include <gmpxx.h>
#include <iostream>
#include <stdio.h>

using namespace std;

SimpleFactorization::SimpleFactorization(mpz_class &arg) {
  candidate = arg;
  this->setRange(2, sqrt(arg));
  factor = 2;

  nr_of_divisions = 0;
}

SimpleFactorization::SimpleFactorization(const char* arg) {
  candidate.set_str(arg, 10);
  this->setRange(2, sqrt(candidate));
  factor = 2;

  nr_of_divisions = 0;
}


bool SimpleFactorization::factorize() {
  int mod30;
  mpz_class mpz_mod30;

  if (range_max < range_min)
    return false;

  if (factor < 2)
    factor = 2;
  
  mpz_mod30 = factor % 30;
  mod30 = mpz_mod30.get_si();
  
  while (factor <= range_max) {
    if (! (mod30 == 1 ||
	   mod30 == 7 ||
	   mod30 == 11 ||
	   mod30 == 13 ||
	   mod30 == 17 ||
	   mod30 == 19 ||
	   mod30 == 23 ||
	   mod30 == 29 ||
	   factor == 2 ||
	   factor == 3 ||
	   factor == 5)) {
      factor++;
      ++mod30 %= 30;
      continue;
    }
    
#ifdef DEBUG
    cout << "Test: " << factor << endl;
#endif
    
    nr_of_divisions++;
    if (mpz_divisible_p(candidate.get_mpz_t(), 
			factor.get_mpz_t())) {
      // determine new candidate for subsequent factorizations
      candidate = candidate / factor;
      this->setMax(sqrt(candidate));
      return true;
    }
    factor++;
    ++mod30 %= 30;
    
  }
  return false;
}

void SimpleFactorization::setOptions(const unsigned int arg) {
  options = arg;
}

unsigned int SimpleFactorization::getOptions() {
  return options;
}

void SimpleFactorization::setMin(const mpz_class &min) {
  range_min = 2;

  if (min > 2)
    range_min = min;

  search_int = range_max - range_min;
  factor = range_min;
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

  if (range_max - range_min > search_int)
    search_int = range_max - range_min;
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

const long long SimpleFactorization::getNumberOfDivisions() {
  return nr_of_divisions;
}

double SimpleFactorization::getProgress() {
  mpf_class total = factor - range_min;
  mpf_class progress = 0;

  if (search_int > 0) {
    progress = total / search_int;
  }
  return progress.get_d();
}
