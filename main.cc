#include <iostream>
#include <gmpxx.h>
#include "SimpleFactorization.h"

#define VERSION "0.4.0"


using namespace std;

void usage() {
  cout << "simple-factorization v" << VERSION << endl << endl;
  cout << "Usage:" << endl;
  cout << "simple-factorization [OPTIONS] candidate" << endl << endl;
  cout << "Factorize the specified candidate number using the naive try-to-divide-approach" << endl << endl;
  cout << "Options:" << endl;
  cout << "  --help         this help text" << endl;
  cout << "  --full         don't stop after finding a factor, instead fully factorize" << endl;
  cout << "  --min <VALUE>  lower bound for search (default: 2)" << endl;
  cout << "  --max <VALUE>  upper bound for search (default: square root of candidate)" << endl;
  cout << endl;
  exit(0);
}


void factorize() {


}


int main(int argc, char **argv) {
  mpz_class candidate = 0;
  char *min = NULL;
  char *max = NULL;
  int ii;
  bool opt_full = false;
  unsigned int options = 0;

  if (argc == 1) usage();

  ii = 1;
  /* parse options */
  while (ii < argc) {
    if (strcmp(argv[ii], "--help") == 0) 
      usage();

    if (strcmp(argv[ii], "--min") == 0) {
      ii++;
      if (ii >= argc) usage();
      min = (char*) malloc(strlen(argv[ii]));
      strcpy(min, argv[ii]);
      ii++;
      continue;
    }

    if (strcmp(argv[ii], "--max") == 0) {
      ii++;
      if (ii >= argc) usage();
      max = (char*) malloc(strlen(argv[ii]));
      strcpy(max, argv[ii]);
      ii++;
      continue;
    }

    if (strcmp(argv[ii], "--verbose") == 0) {
      ii++;
      options |= SIMPLE_FACTORIZATION_VERBOSE;
      continue;
    }

    if (strcmp(argv[ii], "--full") == 0) {
      ii++;
      opt_full = true;
      continue;
    }


    if (*argv[ii] == '-') {
      fprintf(stderr, "Unrecognized option %s\n", argv[ii]);
      exit(1);
    }

    if (candidate != 0)
      usage();
 
    candidate.set_str(argv[ii], 10);
    ii++;
  }

  // 4801 * 10093 = 48456493

  SimpleFactorization factorizer(candidate);
  factorizer.setOptions(options);

  if (min)
    factorizer.setMin(min);
  if (max)
    factorizer.setMax(max);

 
  cout << endl << "Trying to factorize " << factorizer.getCandidate() << endl;
  cout << "in range: " 
       << factorizer.getMin() << " - " << factorizer.getMax()
       << endl;

  double progress;
  // factorizer.setRange(0, 15000);

  if (factorizer.factorize()) {
    mpz_class f;
    f = factorizer.getFactor();

    cout << endl 
	 << "Found factor(s): ";

    cout << f;
    if (opt_full) {
      while (factorizer.factorize()) {
	f = factorizer.getFactor();
	cout << " * " << f;
      }
      cout << " * " << factorizer.getCandidate();
    } else {
      cout << " (lowest factor of factorization)";
    }

    cout << endl;

    progress = factorizer.getProgress();
    cout << "(Finished at " << progress * 100 << "% of search range.)" << endl;
    cout << "Performed " << factorizer.getNumberOfDivisions() << " test divisions." << endl;
    
  } else {
    cout << "No factorization found." << endl;
  }
}

