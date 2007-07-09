#include "SimpleFactorization.h"
#include <gmpxx.h>
#include <iostream>
#include <stdio.h>

using namespace std;

SimpleFactorization::SimpleFactorization(mpz_class &arg) {
  candidate = arg;
  this->setRange(2, sqrt(arg));
  factor = 0;
  options = SIMPLE_FACTORIZATION_OPTIMIZE_2;
  nr_of_divisions = 0;
}

SimpleFactorization::SimpleFactorization(const char* arg) {
  candidate.set_str(arg, 10);
  this->setRange(2, sqrt(candidate));
  factor = 0;
  options = SIMPLE_FACTORIZATION_OPTIMIZE_2;
  nr_of_divisions = 0;
}

bool SimpleFactorization::factorize() {
  if (range_max < range_min)
    return false;

  factor = range_min;
  if (factor < 2)
    factor = 2;

  while (factor <= range_max) {
    if ((options & SIMPLE_FACTORIZATION_OPTIMIZE_2)
	&& mpz_even_p(factor.get_mpz_t())) {
      factor++;
      continue;
    }

    if ((options & SIMPLE_FACTORIZATION_OPTIMIZE_3) ||
	(options & SIMPLE_FACTORIZATION_OPTIMIZE_5)) {
      char* factor_as_string = NULL;
      factor_as_string = mpz_get_str(NULL, 10, factor.get_mpz_t());
      char lastdigit = factor_as_string[strlen(factor_as_string) - 1];
      bool skip = false;

      if (options & SIMPLE_FACTORIZATION_OPTIMIZE_5) {
	if (lastdigit == '5') {
	  skip = true;
	}
      }

      if (! skip && (options & SIMPLE_FACTORIZATION_OPTIMIZE_3)) {
	int sum_of_digits = 0;
	int len, ii;
	len = strlen(factor_as_string);
	
	for (ii = 0; ii < len; ii++) {
	  sum_of_digits += factor_as_string[ii] - '0';
	}
	
	if (sum_of_digits % 3 == 0) {
	  skip = true;
	}
      }

      if (factor_as_string) {
	free(factor_as_string);
	factor_as_string = NULL;
      }

      if (skip) {
	factor++;
	continue;
      }
    }      

    if (options & SIMPLE_FACTORIZATION_STATISTICS)
      nr_of_divisions++;

    if (mpz_divisible_p(candidate.get_mpz_t(), 
			factor.get_mpz_t())) {
      return 1;
    }
    factor++;
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

const mpz_class& SimpleFactorization::getNumberOfDivisions() {
  return nr_of_divisions;
}

double SimpleFactorization::getProgress() {
  mpf_class total = factor - range_min;
  mpf_class progress = 0;

  if (range_int > 0) {
    progress = total / range_int;
  }
  return progress.get_d();
}
