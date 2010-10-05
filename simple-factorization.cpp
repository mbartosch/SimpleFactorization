#ifdef WIN32
#include "stdafx.h"
#include <windows.h>
#endif

#include <stdlib.h>
#include <signal.h>
#include <iostream>
#include <gmpxx.h>
#include "SimpleFactorization.h"

#define VERSION "0.5.1"

using namespace std;

SimpleFactorization *factorizer = NULL;

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


void statistics() {
  double progress;
  if (factorizer) {
    progress = factorizer->getProgress();
    cout << progress * 100 << " % of search space." << endl;
    cout << "Performed " << factorizer->getNumberOfDivisions() << " test divisions." << endl;
  }
}

void sigint_handler(int) {
  if (factorizer) {
    cout << endl << "User requested program termination at ";
    statistics();
    cout << "Current test factor: " << factorizer->getFactor() << endl;
    delete factorizer;
    exit(0);
  }
}

void sigusr1_handler(int) {
  if (factorizer) {
    cout << endl << "Currently at ";
    statistics();
  }
}

#ifdef WIN32
int sigusr_count = 0;
BOOL CtrlHandler(DWORD fdwCtrlType) {
  switch(fdwCtrlType) {
  case CTRL_C_EVENT:
    sigusr1_handler(0);
    if (! sigusr_count++)
      cout << "(Hint: use Ctrl-Break if you wish to terminate the program.)" << endl;
    return(TRUE);
    
  case CTRL_BREAK_EVENT:
    sigint_handler(0);
    return(TRUE);

  default:
    return(FALSE);
  }
}
#endif


#ifndef WIN32
int main(int argc, char **argv) {
#else
int _tmain(int argc, _TCHAR **argv) {
#endif
  mpz_class candidate = 0;
  char *min = NULL;
  char *max = NULL;
  int ii;
  bool opt_full = false;

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

  factorizer = new SimpleFactorization(candidate);

  if (min)
    factorizer->setMin(min);
  if (max)
    factorizer->setMax(max);

 
  cout << endl << "Trying to ";
  if (! opt_full)
    cout << "find the first prime factor of ";
  else
    cout << "factorize ";
  cout << factorizer->getCandidate() << endl;
  cout << "in range: " 
       << factorizer->getMin() << " - " << factorizer->getMax()
       << endl;

#ifndef WIN32
  if(signal(SIGINT, SIG_IGN) != SIG_IGN)
    signal(SIGINT, sigint_handler);

  signal(SIGUSR1, sigusr1_handler);
#else
  SetConsoleCtrlHandler((PHANDLER_ROUTINE) CtrlHandler, TRUE);
#endif


  if (factorizer->factorize()) {
    mpz_class f;
    f = factorizer->getFactor();

    cout << endl 
	 << "Found factors: ";

    cout << f;
    if (opt_full) {
      while (factorizer->factorize()) {
	f = factorizer->getFactor();
	cout << " * " << f;
	fflush(stdout);
      }
      cout << " * " << factorizer->getCandidate();
    } else {
      cout << " * " << factorizer->getCandidate() << endl;
      cout << "The factorization stopped after finding the first factor, the second factor" << endl;
      cout << "may be non-prime. (Hint: Use the --full option to get a full factorization)" << endl;
    }

    cout << endl;

    cout << "Finished at ";
    statistics();

  } else {
    cout << "No factorization found." << endl;
  }
  delete factorizer;
  exit(0);
}

