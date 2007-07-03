#include <iostream>
#include <gmpxx.h>
#include "SimpleFactorization.h"
// #include "SimpleFactorizationBinary.h"

#define VERSION "0.1.0"


using namespace std;

void usage() {
  cout << "simple-factorization v" << VERSION << endl << endl;
  cout << "Usage:" << endl;
  cout << "simple-factorization [OPTIONS] candidate" << endl << endl;
  cout << "Factorize the specified candidate number using the naive try-to-divide-approach" << endl << endl;
  cout << "Options:" << endl;
  cout << "  --help         this help text" << endl;
  cout << "  --min <VALUE>  lower bound for search (default: 2)" << endl;
  cout << "  --max <VALUE>  upper bound for search (default: square root of candidate)" << endl << endl;
  exit(0);
}

int main(int argc, char **argv) {
  mpz_class candidate;
  char *min = NULL;
  char *max = NULL;
  int ii;

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

    if (*argv[ii] == '-' && (strlen(argv[ii]) > 1)) {
      fprintf(stderr, "Unrecognized option %s\n", argv[ii]);
      exit(1);
    }

    candidate.set_str(argv[ii], 10);
    ii++;
  }

  // 4801 * 10093 = 48456493

  SimpleFactorization factorizer(candidate);
  if (min)
    factorizer.setMin(min);
  if (max)
     factorizer.setMax(max);
 
  cout << "Trying to factorize " << factorizer.getCandidate() << endl;
  cout << "in range: " 
       << factorizer.getMin() << " - " << factorizer.getMax()
       << endl;

  double progress;
  // factorizer.setRange(0, 15000);

  if (factorizer.factorize()) {
    mpz_class f;
    f = factorizer.getFactor();

    cout << endl 
	 << "Found factor: " 
	 << f << " for " << factorizer.getCandidate() << endl;

    progress = factorizer.getProgress();
    cout << "(At " << progress * 100 << "% of search range.)" << endl;
    
  } else {
    cout << "No factorization found for " << factorizer.getCandidate() << endl;
  }
}

