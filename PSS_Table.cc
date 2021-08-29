/****************************************
 * PSS_Table class - Body v1.80         *
 * (C) Shin-ichi MINATO (Aug 29, 2021)  *
 ****************************************/

#include "PSS_Table.h"
using namespace std;

PSS_Table::PSS_Table()
{
  _m = 0;
  _n = 0;
  _c = 0;
  _label = 0;
  _rate = 0;
  _ord = 0;
  _Z = 0;
  _heat = 0;
  _maxZ = 0;
#ifdef PMAP
  _pmap = 0;
#else //PMAP
  _nC = 0;
  _cC = 0;
#endif //PMAP
  this->_statFunc = &PSS_Table::LikeP;
}

PSS_Table::~PSS_Table()
{
  if(_n) delete[] _n;
  if(_c) delete[] _c;
  if(_label)
  {
    for(int i=0; i<_m; i++) if(_label[i]) delete[] _label[i];
    delete[] _label;
  }
  if(_rate) delete[] _rate;
  if(_ord) delete[] _ord;
  if(_Z) delete[] _Z;
  if(_heat) delete[] _heat;
  if(_maxZ) delete[] _maxZ;
#ifdef PMAP
  if(_pmap) delete[] _pmap;
#else //PMAP
  if(_nC)
  {
    for(int i=1; i<_m; i++) if(_nC[i]) delete[] _nC[i];
    delete[] _nC;
  }
  if(_cC)
  {
    for(int i=1; i<_m; i++) if(_cC[i]) delete[] _cC[i];
    delete[] _cC;
  }
#endif //PMAP
}

int PSS_Table::Alloc(const int m)
{
  if(_n) { delete[] _n; _n = 0; }
  if(_c) { delete[] _c; _c = 0; }
  if(_label)
  {
    for(int i=0; i<_m; i++) if(_label[i]) delete[] _label[i];
    delete[] _label; _label = 0;
  }
  if(_rate) { delete[] _rate; _rate = 0; }
  if(_ord) { delete[] _ord; _ord = 0; }
  if(_Z) { delete[] _Z; _Z = 0; }
  if(_heat) { delete[] _heat; _heat = 0; }
  if(_maxZ) { delete[] _maxZ; _maxZ = 0; }
#ifdef PMAP
  if(_pmap) { delete[] _pmap; _pmap = 0; }
#else //PMAP
  if(_nC)
  {
    for(int i=1; i<_m; i++) if(_nC[i]) delete[] _nC[i];
    delete[] _nC;
  }
  if(_cC)
  {
    for(int i=1; i<_m; i++) if(_cC[i]) delete[] _cC[i];
    delete[] _cC;
  }
#endif //PMAP

  _m = (m < 0)? 0: m;
#ifndef PMAP
  _sizeC = _m * 64;
#endif //PMAP

  if(_m > 0)
  {
    if(!(_n = new ULLint[_m])) { Alloc(0); return 1; }
    if(!(_c = new ULLint[_m])) { Alloc(0); return 1; }
    if(!(_label = new char*[_m])) { Alloc(0); return 1; }
    if(!(_rate = new double [_m])) { Alloc(0); return 1; }
    if(!(_ord = new int[_m])) { Alloc(0); return 1; }
    if(!(_Z = new int[_m])) { Alloc(0); return 1; }
    if(!(_heat = new ULLint[_m])) { Alloc(0); return 1; }
    if(!(_maxZ = new int[_m])) { Alloc(0); return 1; }
#ifdef PMAP
    if(!(_pmap = new Pmap[_m])) { Alloc(0); return 1; }
#else //PMAP
    if(!(_nC = new ULLint*[_m])) { Alloc(0); return 1; }
    if(!(_cC = new ULLint*[_m])) { Alloc(0); return 1; }
#endif //PMAP

    for(int i=0; i<_m; i++)
    {
      _n[i] = 0;
      _c[i] = 0;
      _label[i] = 0;
      _rate[i] = 0;
      _ord[i] = i;
      _Z[i] = 0;
      _heat[i] = 0;
      _maxZ[i] = 0;
#ifndef PMAP
      _nC[i] = 0;
      _cC[i] = 0;
#endif //PMAP
    }
    for(int i=0; i<_m; i++)
      if((_label[i] = new char[16])) _label[i][0] = 0;
      else { Alloc(0); return 1; }
#ifndef PMAP
    for(int i=0; i<_m; i++)
      if((_nC[i] = new ULLint[_sizeC]))
        for(int j=0; j<_sizeC; j++) _nC[i][j] = 0;
      else { Alloc(0); return 1; }
    for(int i=0; i<_m; i++)
      if((_cC[i] = new ULLint[_sizeC]))
        for(int j=0; j<_sizeC; j++) _cC[i][j] = 0;
      else { Alloc(0); return 1; }
#endif //PMAP
  }
  return 0;
}

int PSS_Table::Import(FILE *strm)
{
  char s[256];
  do if(fscanf(strm, "%s", s) == EOF) return 1;
  while(s[0] == '#'); // go next word
  int m = strtol(s, NULL, 10);
  do if(fscanf(strm, "%s", s) == EOF) return 1;
  while(s[0] == '#'); // go next word

  if(Alloc(m)) return 1;
  int e = 0;
  for(int i=0; i<_m; i++)
  {
    _n[i] = strtoll(s, NULL, 10);
    do if(fscanf(strm, "%s", s) == EOF) { e = 1; break; }
    while(s[0] == '#'); // go next word
    _c[i] = strtoll(s, NULL, 10);
    if(fscanf(strm, "%s", s) == EOF) { if(i<_m-1) e = 1; break; }
    if(s[0] == '#') 
    {
      strcpy(_label[i], s+1);
      do if(fscanf(strm, "%s", s) == EOF) { if(i<_m-1) e = 1; break; }
      while(s[0] == '#'); // go next word
    }
    else _label[i][0] = 0;
  }
  if(e) { Alloc(0); return 1; }
  return 0;
}

int PSS_Table::RandomCopy(PSS_Table& st)
{
  if(_m != st._m)
    if(Alloc(st._m)) return 1;
  if(_m <= 0) return 0;
  _nG = 0;
  _cG = 0;
  for(int i=0; i<_m; i++)
  {
    _heat[i] = _nG;
    _n[i] = st._n[i];
    _c[i] = 0;
    _nG += st._n[i];
    _cG += st._c[i];
    _ord[i] = st._ord[i];
  }
  int msb = 1;
  while(msb <= _m) msb <<= 1;
  msb >>= 1;
  for(ULLint nn=_nG; nn>_nG-_cG; nn--)
  {
    ULLint r = ((double)random() / ((ULLint)RAND_MAX + 1)) * nn;
    int a = 0;
    for(int d=msb; d>0; d>>=1)
      if(a + d < _m && r >= _heat[a + d]) a += d;
    _c[a]++;
    for(int i=a+1; i<_m; i++) _heat[i]--;
  }
  for(int i=0; i<_m; i++) _heat[i] = 0;
  return 0;
}

void PSS_Table::Export() const
{
  cout << _m << " #n\n";
  for(int i=0; i<_m; i++)
    cout << "#" << i << ": " << _n[i]
	 << " " << _c[i] << " #" << _label[i] << "\n";
  cout.flush();
}

void PSS_Table::PreProc()
{
  _nG = 0;
  _cG = 0;
  for(int i=0; i<_m; i++)
  {
    _nG += _n[i];
    _cG += _c[i];
    _rate[i] = (double)_c[i]/_n[i];
  }
  _cG2 = _nG - _cG;
  _rateG = (double)_cG / _nG;
  _rateG2 = (double)_cG2 / _nG;
  _likeG = - log(_rateG) * _cG;
  _likeG2 = - log(_rateG2) * _cG2;
  for(int i=0; i<_m; i++)
  {
#ifdef PMAP
    _pmap[i].clear();
    _pmap[i].insert(make_pair(_cG, _nG));
#else //PMAP
    for(int j=0; j<_sizeC; j++)
    { _nC[i][j] = _nG; _cC[i][j] = 0; }
#endif //PMAP
  }
}

void PSS_Table::SortRate()
{
  for(int i=0; i<_m; i++)
  {
    int t;
    int k = i;
    double max = 0;
    for(int j=i; j<_m; j++)
    {
      double rate = _rate[_ord[j]];
      if(rate > max) { k = j; max = rate; }
    }
    if(i != k) { t = _ord[i]; _ord[i] = _ord[k]; _ord[k] = t; }
  }
}

void PSS_Table::SortN()
{
  for(int i=0; i<_m; i++)
  {
    int t;
    int k = i;
    ULLint  max = 0;
    for(int j=i; j<_m; j++)
    {
      ULLint n = _n[_ord[j]];
      if(n > max) { k = j; max = n; }
    }
    if(i != k) { t = _ord[i]; _ord[i] = _ord[k]; _ord[k] = t; }
  }
}

void PSS_Table::SortC()
{
  for(int i=0; i<_m; i++)
  {
    int t;
    int k = i;
    ULLint  max = 0;
    for(int j=i; j<_m; j++)
    {
      ULLint c = _c[_ord[j]];
      if(c > max) { k = j; max = c; }
    }
    if(i != k) { t = _ord[i]; _ord[i] = _ord[k]; _ord[k] = t; }
  }
}

void PSS_Table::SortRateR()
{
  for(int i=_m-1; i>=0; i--)
  {
    int t;
    int k = i;
    double max = 0;
    for(int j=0; j<=i; j++)
    {
      double rate = _rate[_ord[j]];
      if(rate > max) { k = j; max = rate; }
    }
    if(i != k) { t = _ord[i]; _ord[i] = _ord[k]; _ord[k] = t; }
  }
}

void PSS_Table::SortNR()
{
  for(int i=_m-1; i>=0; i--)
  {
    int t;
    int k = i;
    ULLint  max = 0;
    for(int j=0; j<=i; j++)
    {
      ULLint n = _n[_ord[j]];
      if(n > max) { k = j; max = n; }
    }
    if(i != k) { t = _ord[i]; _ord[i] = _ord[k]; _ord[k] = t; }
  }
}

void PSS_Table::SortCR()
{
  for(int i=_m-1; i>=0; i--)
  {
    int t;
    int k = i;
    ULLint  max = 0;
    for(int j=0; j<=i; j++)
    {
      ULLint c = _c[_ord[j]];
      if(c > max) { k = j; max = c; }
    }
    if(i != k) { t = _ord[i]; _ord[i] = _ord[k]; _ord[k] = t; }
  }
}

void PSS_Table::PrintStats() const
{
  for(int i=0; i<_m; i++)
  {
    int k = _ord[i];
    cout << i << ": " << _n[k] << " " << _c[k] << " "
	 << _rate[k] << " "
	 << fixed << LikeP(_n[k], _c[k]) << " "
	 << fixed << LikeB(_n[k], _c[k]) << " "
	 << _label[k] << "\n";
  }
  cout << "G: " << _nG << " " << _cG << " "
       << _rateG << "\n";
  cout.flush();
}

double PSS_Table::LikeP(const ULLint nZ, const ULLint cZ) const
{
  if(nZ == 0 || nZ >= _nG) return 0;
  ULLint nZc = _nG - nZ;
  ULLint cZc = _cG - cZ;
  double rateZ = (double)cZ / nZ;
  double rateZc = (double)cZc / nZc;

  return (rateZ <= _rateG)? 0: 
          _likeG + log(rateZ)*cZ + log(rateZc)*cZc;
}

double PSS_Table::LikeB(const ULLint nZ, const ULLint cZ) const
{
  if(nZ == 0 || nZ >= _nG) return 0;
  ULLint cZ2 = nZ - cZ;
  ULLint nZc = _nG - nZ;
  ULLint cZc = _cG - cZ;
  ULLint cZc2 = nZc - cZc;
  double rateZ = (double)cZ / nZ;
  double rateZc = (double)cZc / nZc;
  double rateZ2 = (double)cZ2 / nZ;
  double rateZc2 = (double)cZc2 / nZc;

  return (rateZ <= _rateG)? 0: 
          _likeG + log(rateZ)*cZ + log(rateZc)*cZc
        + _likeG2 + log(rateZ2)*cZ2 + log(rateZc2)*cZc2;
}

double PSS_Table::ChiP(const ULLint nZ, const ULLint cZ) const
{
  if(nZ == 0 || nZ >= _nG) return 0;
  ULLint nZc = _nG - nZ;
  ULLint cZc = _cG - cZ;
  double rateZ = (double)cZ / nZ;
  // double rateZc = (double)cZc / nZc;

  double e_cZ = (double)nZ * _rateG;
  double e_cZc = (double)nZc * _rateG;

  return (rateZ <= _rateG)? 0: 
         (e_cZ - cZ) * (e_cZ - cZ) / e_cZ +
         (e_cZc - cZc) * (e_cZc - cZc) / e_cZc;
}

double PSS_Table::ChiB(const ULLint nZ, const ULLint cZ) const
{
  if(nZ == 0 || nZ >= _nG) return 0;
  ULLint nZc = _nG - nZ;
  ULLint cZc = _cG - cZ;
  double rateZ = (double)cZ / nZ;
  //double rateZc = (double)cZc / nZc;

  double e_cZ = (double)nZ * _rateG;
  double e_cZc = (double)nZc * _rateG;

  return (rateZ <= _rateG)? 0: 
         (e_cZ - cZ) * (e_cZ - cZ) / e_cZ +
         (e_cZ - cZ) * (e_cZ - cZ) / (nZ - e_cZ) +
         (e_cZc - cZc) * (e_cZc - cZc) / e_cZc +
         (e_cZc - cZc) * (e_cZc - cZc) / (nZc - e_cZc);
}

void PSS_Table::PrintZ(const int tail, const ULLint nZ, const ULLint cZ)
{
  if(_prn == 1)
  {
    double rateZ = (double) cZ / nZ;
    cout << (this->*_statFunc)(nZ, cZ) << " ";
    cout << "(n:" << nZ << " c:" << cZ << " c/n:" << rateZ << ")\n";
    for(int i=0; i<=tail; i++)
      if(_Z[i])
      {
        int j = _ord[i];
        char *s = _label[j];
        if(!s[0]) cout << " " << j;
        else cout << " " << s;
      }
    cout << "\n----\n";
    cout.flush();
  }
  else
    for(int i=0; i<=tail; i++)
      if(_Z[i]) _heat[_ord[i]]++;
}

ULLint PSS_Table::EnumHotSpotsBT(const int tail, const ULLint nZ, const ULLint cZ)
{
  // ChkPrune
#ifdef PMAP
  Pmap::iterator itr = _pmap[tail].lower_bound(cZ);
  if(nZ >= itr->second) return 0;
#else //PMAP
  int nx = nZ * _sizeC / _nG;
  if(nx > 0 && cZ <= _cC[tail][nx-1]) return 0;
  if(nZ >= _nC[tail][nx] && cZ <= _cC[tail][nx]) return 0;
#endif //PMAP

  _call++;
  ULLint hit = 0;
  double statZ = (this->*_statFunc)(nZ, cZ);
  if(statZ > _statMax)
    if(nZ <= _nmax && cZ >= _cmin)
    {
      _statMax = statZ;
      if(_prn)
      {
        _maxTail = tail;
        for(int i=0; i<=tail; i++) _maxZ[i] = _Z[i];
      }
    }
  if(statZ >= _statTh)
    if(nZ <= _nmax && cZ >= _cmin)
    {
      hit = 1; 
      if(_prn) PrintZ(tail, nZ, cZ);
    }

  if(nZ <= _nmax)
  {
    for(int i=tail+1; i<_m; i++)
    {
      _Z[i] = 1;
      hit += EnumHotSpotsBT(i, nZ+_n[_ord[i]], cZ+_c[_ord[i]]);
      _Z[i] = 0;
    }
  }

#ifndef NAIVE
  if(hit == 0) // EntPrune
  {
    for(int i=tail; i<_m; i++)
    {
#ifdef PMAP
      itr = _pmap[i].lower_bound(cZ);
      if(nZ >= itr->second) break;
      if(cZ == itr->first) itr->second = nZ;
      else itr = _pmap[i].insert(itr, make_pair(cZ, nZ));
      Pmap::iterator itr_x = itr;
      while(itr_x != _pmap[i].begin() && nZ <= (--itr_x)->second)
      {
        _pmap[i].erase(itr_x);
        itr_x = itr;
      }
#else //PMAP
      if(cZ <= _cC[i][nx]) break;
      _nC[i][nx] = nZ;
      _cC[i][nx] = cZ;
      for(int j=nx+1; j<_sizeC && cZ>_cC[i][j]; j++)
      {
        _nC[i][j] = nZ;
        _cC[i][j] = cZ;
      }
#endif //PMAP
    }
  }
#endif //NAIVE

  return hit;
}

int PSS_Table::EnumHotSpots(const double statTh, const ULLint nmax, const ULLint cmin, const int prn = 0)
{
  ULLint hit = 0;
  _statTh = statTh;
  _statMax = 0;
  _maxTail = 0;
  _nmax = (nmax)? nmax: _nG;
  _cmin = cmin;
  _prn = prn;
  _call = 0;

  SortRate();

  if(_m < 2) return 1;
  for(int i=0; i<_m; i++)
  {
    _Z[i] = 0;
    _heat[i] = 0;
  }

  for(int i=0; i<_m; i++)
  {
    _Z[i] = 1;
    hit += EnumHotSpotsBT(i, _n[_ord[i]], _c[_ord[i]]);
    _Z[i] = 0;
  }

  if(_prn == 1 && hit == 0)
  {
    ULLint nZ = 0;
    ULLint cZ = 0;
    for(int i=0; i<=_maxTail; i++)
    {
      nZ += _maxZ[i]? _n[_ord[i]]: 0;
      cZ += _maxZ[i]? _c[_ord[i]]: 0;
    }
    double rateZ = (double) cZ / nZ;
    cout << (this->*_statFunc)(nZ, cZ) << " ";
    cout << "(n:" << nZ << " c:" << cZ << " c/n:" << rateZ << ")\n";
    for(int i=0; i<=_maxTail; i++)
      if(_maxZ[i])
      {
        int j = _ord[i];
        char *s = _label[j];
        if(!s[0]) cout << " " << j;
        else cout << " " << s;
      }
    cout << "\n";
  }
  else
  {
    if(_prn == 2)
    {
      for(int i=0; i<_m; i++)
      {
          char *s = _label[i];
          if(!s[0]) cout << " " << i;
          else cout << " " << s;
	  cout << " " << _heat[i] << "\n";
      }
      cout << "----\n";
    }
  }

  if(_prn) cerr << "[HotSpotHits,  MaxStats]\n";
  cout << hit << ",\t";
  cout << _statMax << "\n";
  //cout << "total_calls:  " << _call << "\n";
#ifdef PMAP
  //int ps = 0;
  //for(int i=0; i<_m; i++) ps += _pmap[i].size();
  //cout << "pareto_points: " << ps << "\n";
#endif //PMAP
 
  return 0;
}

