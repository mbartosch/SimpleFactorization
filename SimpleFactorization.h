#ifndef _SIMPLEFACTORIZATION_H_
#define _SIMPLEFACTORIZATION_H_

#include <gmpxx.h>

// stub class as defined by CrypTool
class CProgressModel 
{ 
 public: 
  CProgressModel() { } 
  virtual double getProgress() = 0; // 0.0 <= result <= 1.0 
}; 

class SimpleFactorization : public CProgressModel {
 public:
  SimpleFactorization(mpz_class &arg);
  SimpleFactorization(const char* arg);

  virtual void setMin(const mpz_class &min);
  virtual void setMin(const char* arg);
  virtual const mpz_class& getMin();

  virtual void setMax(const mpz_class &max);
  virtual void setMax(const char* max);
  virtual const mpz_class& getMax();

  virtual void setRange(const mpz_class &min, const mpz_class &max);
  virtual void setRange(const char* min, const char* max);

  virtual bool factorize();

  virtual const mpz_class& getFactor();
  virtual const mpz_class& getCandidate();
  virtual const long long getNumberOfDivisions();

  virtual double getProgress();
  
 protected:
  //  virtual bool is_probable_prime(const mpz_class &arg);

  mpz_class range_min;
  mpz_class range_max;
  mpz_class search_int;
  mpz_class factor;
  mpz_class candidate;
  unsigned long long nr_of_divisions;
};


#endif
