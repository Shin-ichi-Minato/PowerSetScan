/****************************************
 * Power Set Scan ver 1.80 Main         *
 * (C) Shin-ichi MINATO (Aug 29, 2021)  *
 ****************************************/

#include "PSS_Table.h"
using namespace std;

int main(int argc, char *argv[])
{
  PSS_Table A;
  FILE *fp = 0;
  double likeTh = 0;
  int nmax = 0;
  int cmin = 0;
  int prn = 0;
  int rt = 0;
  int e = 0;
  if(argc <= 2) e = 1;
  else
  {
    if((fp = fopen(argv[1], "r")) == 0)
    {
      cerr << "filename??\n";
      return 1;
    }
    likeTh = strtod(argv[2], NULL);
    int px = 2;
    while(++px < argc)
    {
      if(!strcmp(argv[px], "-p")) prn = 1;
      else if(!strcmp(argv[px], "-hm")) prn = 2;
      else if(!strcmp(argv[px], "-ber")) 
        A._statFunc = &PSS_Table::LikeB;
      else if(!strcmp(argv[px], "-chi")) 
        A._statFunc = &PSS_Table::ChiB;
      else if(!strcmp(argv[px], "-nmax"))
      {
        if(++px >= argc) e = 1;
        else nmax = strtoll(argv[px], NULL, 10);
      }
      else if(!strcmp(argv[px], "-cmin"))
      {
        if(++px >= argc) e = 1;
        else cmin = strtoll(argv[px], NULL, 10);
      }
      else if(!strcmp(argv[px], "-r"))
      {
        if(++px >= argc) e = 1;
        else rt = strtol(argv[px], NULL, 10);
      }
      else e = 1;
    }
  }
  if(e)
  {
    cerr << "pss <filename> <min_scanstat> [<flag> [<number>]]*\n";
    cerr << "<flag>\n";
    cerr << "-p             print all hotspots\n";
    cerr << "-hm            print hotspot-heatmap\n";
    cerr << "-ber           using Bernoulli-model statistic\n";
    cerr << "-chi           using Chi-squared statistic\n";
    cerr << "-nmax <number> bounded search with n(Z) <= nmax\n";
    cerr << "-cmin <number> bounded search with c(Z) >= cmin\n";
    cerr << "-r <number>    repeat execution by uniformly randomized data\n";
    return 1;
  }

  cerr << "**** PowerSetScan (v.1.80) ****\n";
  if(!prn) cerr <<"[HotSpotHits,  MaxStats]\n";
  cerr.flush();
  cout << fixed;

  if(A.Import(fp))
  {
    cerr << "File read error.\n";
    return 1;
  }

  if(rt > 0)
  {
    PSS_Table B;
    B._statFunc = A._statFunc;
    for(int i=0; i<rt; i++)
    {
      B.RandomCopy(A);
      B.PreProc();
      if(prn) cerr << "========\n";
      B.EnumHotSpots(likeTh, nmax, cmin, prn);
    }
  }
  else
  {
    A.PreProc();
    A.EnumHotSpots(likeTh, nmax, cmin, prn);
  }
  return 0;
}

