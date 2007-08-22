#include "SimpleFactorization.h"
#include <gmpxx.h>
#include <iostream>
#include <stdio.h>

using namespace std;

SimpleFactorization::SimpleFactorization(mpz_class &arg) {
  candidate = arg;
  this->setRange(2, sqrt(arg));
  factor = 2;
  options = SIMPLE_FACTORIZATION_OPTIMIZE_2;
  nr_of_divisions = 0;
}

SimpleFactorization::SimpleFactorization(const char* arg) {
  candidate.set_str(arg, 10);
  this->setRange(2, sqrt(candidate));
  factor = 2;
  options = SIMPLE_FACTORIZATION_OPTIMIZE_2;
  nr_of_divisions = 0;
}


bool SimpleFactorization::is_probable_prime(const mpz_class &arg) {
    if ((options & SIMPLE_FACTORIZATION_OPTIMIZE_2)
	&& mpz_even_p(arg.get_mpz_t())
	&& arg != 2) {
      return false;
    }

    if ((options & SIMPLE_FACTORIZATION_OPTIMIZE_3) ||
	(options & SIMPLE_FACTORIZATION_OPTIMIZE_5)) {
      char* arg_as_string = NULL;
      arg_as_string = mpz_get_str(NULL, 10, arg.get_mpz_t());
      char lastdigit = arg_as_string[strlen(arg_as_string) - 1];

      if (options & SIMPLE_FACTORIZATION_OPTIMIZE_5) {
	if (lastdigit == '5') {
	  if (arg_as_string) {
	    free(arg_as_string);
	    arg_as_string = NULL;
	  }
	  return false;
	}
      }

      if (options & SIMPLE_FACTORIZATION_OPTIMIZE_3) {
	int sum_of_digits = 0;
	int len, ii;
	len = strlen(arg_as_string);
	
	for (ii = 0; ii < len; ii++) {
	  sum_of_digits += arg_as_string[ii] - '0';
	}
	
	if (sum_of_digits % 3 == 0) {
	  if (arg_as_string) {
	    free(arg_as_string);
	    arg_as_string = NULL;
	  }
	  return false;
	}
      }

      if (arg_as_string) {
	free(arg_as_string);
	arg_as_string = NULL;
      }
    }  

    return true;
}


bool SimpleFactorization::factorize() {
  if (range_max < range_min)
    return false;

  if (factor < 2)
    factor = 2;

  while (factor <= range_max) {
    if (! this->is_probable_prime(factor)) {
      factor++;
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
