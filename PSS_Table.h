/****************************************
 *  PSS_Table class - Header v1.80      *
 *  (C) Shin-ichi MINATO (Aug 29, 2021) *
 ****************************************/

class PSS_Table;

#ifndef _PSS_Table_
#define _PSS_Table_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

typedef unsigned long long ULLint;

#ifdef PMAP
#include <map>
typedef std::map<ULLint, ULLint> Pmap;
#endif //PMAP

class PSS_Table
{
public:
  int _m;
  ULLint *_n;
  ULLint *_c;
  char **_label;
  double *_rate;
  int *_ord;

  ULLint _nG;
  ULLint _cG;
  ULLint _cG2;
  double _rateG;
  double _rateG2;
  double _likeG;
  double _likeG2;

  int *_Z;
  ULLint *_heat;
  int *_maxZ;
  int _maxTail;
  double _statTh;
  double _statMax;
  ULLint _nmax;
  ULLint _cmin;
  int _prn;
  ULLint _call;
  double (PSS_Table::*_statFunc)(const ULLint, const ULLint) const;

#ifdef PMAP
  Pmap *_pmap;
#else //PMAP
  int _sizeC;
  ULLint **_nC;
  ULLint **_cC;
#endif //PMAP

  PSS_Table();
  ~PSS_Table();
  int Alloc(const int);
  int Import(FILE *);
  int RandomCopy(PSS_Table &);
  void Export(void) const;
  void PreProc(void);
  void PrintStats(void) const;
  double LikeP(const ULLint, const ULLint) const;
  double LikeB(const ULLint, const ULLint) const;
  double ChiP(const ULLint, const ULLint) const;
  double ChiB(const ULLint, const ULLint) const;
  void SortRate(void);
  void SortN(void);
  void SortC(void);
  void SortRateR(void);
  void SortNR(void);
  void SortCR(void);
  void PrintZ(const int, const ULLint, const ULLint);
  ULLint EnumHotSpotsBT(const int, const ULLint, const ULLint);
  int EnumHotSpots(const double, const ULLint, const ULLint, const int);
};

#endif // _PSS_Table_

