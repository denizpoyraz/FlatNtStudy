#ifndef fakeBackgroundUtils_h
#define fakeBackgroundUtils_h

#include <vector>

#include "TChain.h"
#include "TLorentzVector.h"
#include "TRandom3.h"

#include "plotter.h"
#include "readTree.h"
#include "ReadInputFile.h"
#include "utils.h"

#define muonChargeMisID           1E-6
#define electronChargeMisIDBarrel 5E-4
#define electronChargeMisIDEndcap 3E-3

using namespace std ;

/// method to get the fake weight and the new lepton kinematic                                                                                                                  
float getFakeWeight( jetContainer inputJet,
                     fakeRateContainer & fakeRate,
                     string leptonFlavour,
                     vector<jetContainer> & jetCollection);


leptonContainer createFakeLepton( jetContainer inputJet,
                                  leptonContainer inputLepton,
                                  fakeMigrationContainer & fakeMigration,
                                  string finalStateString);

void makeFakeLeptonBackground(const string & sampleName,
			      const int    & samplePosition,
                              const string & finalStateString,
                              plotter & analysisPlots,
                              readTree *reader,
                              cutContainer & cutElement,
                              vector<variableContainer> & VariableList,
                              vector<leptonContainer> & leptonsIsoTight,
                              vector<leptonContainer> & LeptonsAll,
                              vector<leptonContainer> & softMuons,
                              vector<jetContainer> & RecoJets,
                              vector<jetContainer> & GenJets,
                              vector<jetContainer> & trackJetsAll,
                              TLorentzVector & L_met,
                              const float & minJetCutPt,
                              const float & leptonIsoLooseCut,
                              const float & minPtLeptonCutCleaning,
                              const float & matchingCone,
                              fakeRateContainer & fakeRate,
                              fakeMigrationContainer & fakeMigration,
                              map <string,TH1F*> & vect
                              );

void makeFakeLeptonBackground(const string & sampleName,
			      const int    & samplePosition,
                              const string & finalStateString,
                              plotter & analysisPlots,
                              readTree *reader,
                              cutContainer & cutElement,
                              vector<variableContainer> & VariableList,
                              vector<variableContainer2D> & VariableList2D,
                              vector<leptonContainer> & leptonsIsoTight,
                              vector<leptonContainer> & LeptonsAll,
                              vector<leptonContainer> & softMuons,
                              vector<jetContainer> & RecoJets,
                              vector<jetContainer> & GenJets,
                              vector<jetContainer> & trackJetsAll,
                              TLorentzVector & L_met,
                              const float & minJetCutPt,
                              const float & leptonIsoLooseCut,
                              const float & minPtLeptonCutCleaning,
                              const float & matchingCone,
                              fakeRateContainer & fakeRate,
                              fakeMigrationContainer & fakeMigration,
                              map <string,TH1F*> & vect
                              );


// -------------------

void makeFakeChargeBackground(const string & sampleName,
			      const int    & samplePosition,
                              const string & finalStateString,
                              plotter & analysisPlots,
                              readTree *reader,
                              cutContainer & cutElement,
                              vector<variableContainer> & VariableList,
                              vector<leptonContainer> & leptonsIsoTight,
                              vector<leptonContainer> & LeptonsAll,
                              vector<leptonContainer> & softMuons,
                              vector<jetContainer> & RecoJets,
                              vector<jetContainer> & GenJets,
                              vector<jetContainer> & trackJetsAll,
                              TLorentzVector & L_met,
                              const float & minJetCutPt,
                              const float & leptonIsoLooseCut,
                              const float & minPtLeptonCutCleaning,
                              const float & matchingCone,
                              map <string,TH1F*> & vect);

void makeFakeChargeBackground(const string & sampleName,
			      const int    & samplePosition,
                              const string & finalStateString,
                              plotter & analysisPlots,
                              readTree *reader,
                              cutContainer & cutElement,
                              vector<variableContainer> & VariableList,
                              vector<variableContainer2D> & VariableList2D,
                              vector<leptonContainer> & leptonsIsoTight,
                              vector<leptonContainer> & LeptonsAll,
                              vector<leptonContainer> & softMuons,
                              vector<jetContainer> & RecoJets,
                              vector<jetContainer> & GenJets,
                              vector<jetContainer> & trackJetsAll,
                              TLorentzVector & L_met,
                              const float & minJetCutPt,
                              const float & leptonIsoLooseCut,
                              const float & minPtLeptonCutCleaning,
                              const float & matchingCone,
                              map <string,TH1F*> & vect);




#endif
