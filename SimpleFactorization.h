#ifndef _SIMPLEFACTORIZATION_H_
#define _SIMPLEFACTORIZATION_H_

#include <gmpxx.h>


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
  virtual double getProgress();
  
 protected:
  mpz_class range_min;
  mpz_class range_max;
  mpz_class range_int;
  mpz_class factor;
  mpz_class candidate;
};


#endif
