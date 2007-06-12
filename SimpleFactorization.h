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
  SimpleFactorization();
  
  virtual void setRange1(const mpz_class &min, const mpz_class &max);
  virtual void setRange2(const mpz_class &min, const mpz_class &max);

  virtual bool factorize(const mpz_class &candidate);

  virtual const mpz_class& getFactor1();
  virtual const mpz_class& getFactor2();
  virtual double getProgress();
  
 protected:
  mpz_class range1_min;
  mpz_class range1_max;
  mpz_class range1_int;
  mpz_class range2_min;
  mpz_class range2_max;
  mpz_class factor1;
  mpz_class factor2;
};


#endif
