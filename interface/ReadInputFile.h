#ifndef ReadInputFile_h
#define ReadInputFile_h

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;

// sample container class                                                                                                                                             
class sampleContainer {
 public :
  sampleContainer(){};
  ~sampleContainer(){};

 sampleContainer(string sampleName, int color, double xsec, int numBefore, int isSignal):
  sampleName(sampleName),
    color(color),
    xsec(xsec),
    numBefore(numBefore),
    isSignal(isSignal){};

  string sampleName ;
  int    color;
  double xsec;
  int numBefore;
  int isSignal;

};

class cutContainer {

 public :
  cutContainer(){};
  ~cutContainer(){};

 cutContainer(string cutLayerName, 
              pair<double,double> ptL, 
              double  chargeSign, 
              double  flavour,
              int     nLep, 
              int     nextra,             
              double  MET, 
              pair<double,double> ptJet, 
              double DetaJJ, 
              double Mjj, 
              pair<double,double> Mll, 
              pair<double,double> MllZVeto, 
              double bTagVeto, double jetPUID ):
    cutLayerName(cutLayerName),
      ptL( ptL),
      chargeSign(chargeSign),
      flavour(flavour),
      nLep(nLep),
      nextra(nextra),
      MET(MET),
      ptJet(ptJet),
      DetaJJ(DetaJJ),
      Mjj(Mjj),
      Mll(Mll),
      MllZVeto(MllZVeto),
      bTagVeto(bTagVeto),
      jetPUID(jetPUID){};

  string cutLayerName ;
  pair<double,double> ptL;
  double  chargeSign;
  double  flavour;
  int     nLep;
  int     nextra;
  double  MET;
  pair<double,double> ptJet;  
  double  DetaJJ;
  double  Mjj;
  pair<double,double>  Mll;
  pair<double,double>  MllZVeto;
  double  bTagVeto;
  double  jetPUID;
};

class variableContainer {

 public :

  variableContainer(){};
  ~variableContainer(){};

  variableContainer(string variableName, int Nbin, double min, double max, string label):
   variableName(variableName),
    Nbin(Nbin),
    min(min),
    max(max),
    label(label){}; 

   string variableName ;
   int Nbin ;
   double min;
   double max;
   string label;

};


int ReadInputSampleFile   (const string & , map<string, vector<sampleContainer> > & );

int ReadInputVariableFile (const string & , vector<variableContainer> & );

int ReadInputVariableFile (const string & , vector<string> & );

int ReadInputCutFile      (const string & , vector<cutContainer> &);

#endif
