/////////////////////////////////////////////////////////////////////////////////////////////////////
// compare for a single variable the expected stats uncertainty to the difference between H and noH //
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <map>

#include "TChain.h"
#include "TLorentzVector.h"
#include "TSystem.h"
#include "TLatex.h"
#include "TPad.h"

#include "plotter.h"
#include "ConfigParser.h"
#include "readTree.h"
#include "utils.h"

#include "RooFormulaVar.h"
#include "RooKeysPdf.h"
#include "RooExponential.h"
#include "RooArgusBG.h"
#include "RooFitResult.h"
#include "RooWorkspace.h"
#include "RooPlot.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooRealVar.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooGaussian.h"
#include "RooPolynomial.h"
#include "RooGenericPdf.h"
#include "RooFFTConvPdf.h"
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif 

using namespace RooFit ;
using namespace std ;

double matchingCone ;
double minLeptonCleaningPt ;
double minLeptonCutPt ;
double minJetCutPt ;
double leptonIsoCut_mu ;
double leptonIsoCut_el ;
double leptonIsoCutLoose ;
bool   usePuppiAsDefault ;
int    lheLevelFilter ;

// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
int main (int argc, char ** argv) 
{

  // check number of inpt parameters
  if (argc < 2){
    cerr<<"Forgot to parse the cfg file --> exit "<<endl ;
    return -1 ;
  }

  // Set Root style from global enviroment path                                                                                                                               
  string ROOTStyle ;
  if (getenv ("ROOTStyle")!=NULL){
    ROOTStyle = getenv ("ROOTStyle") ;
    gROOT->ProcessLine ( (".x "+ROOTStyle+"/setTDRStyle.C").c_str ()) ;
  }

  gStyle->SetOptStat (0) ;
  gStyle->SetPadTopMargin (0.09) ;
  gStyle->SetPadLeftMargin (0.13) ;
  gStyle->SetErrorX (0.5) ;


  // parse config file parameter
  if (gConfigParser) return 1 ;
  gConfigParser = new ConfigParser () ;

  TString config ; 
  config.Form ("%s",argv[1]) ;

  if (! (gConfigParser->init (config)))
    {
      cout << ">>> parseConfigFile::Could not open configuration file " << config << endl ;
      return -1 ;
    }

  // import base directory where samples are located and txt file with the directory name + other info
  string InputBaseDirectory  = gConfigParser->readStringOption ("Input::InputBaseDirectory") ;

  // import from cfg file the cross section value for this sample
  float CrossSection   = gConfigParser->readFloatOption ("Input::CrossSection") ;

  // total number of events
  int maxEventNumber   = gConfigParser->readFloatOption ("Input::EventsNumber") ;

  // treeName
  string treeName      = gConfigParser->readStringOption ("Input::TreeName") ;

  // take the cut list
  string InputCutList  = gConfigParser->readStringOption ("Input::InputCutList") ;

  // Read the cut file
  vector <cutContainer> CutList ;
  if (ReadInputCutFile (InputCutList,CutList) <= 0){
    cerr<<" Empty Cut List File or not Exisisting --> Exit "<<endl ; return -1 ;}

  // take the variable list to be plotted
  string InputVariableList  = gConfigParser->readStringOption ("Input::InputVariableList") ;
  vector<variableContainer> variableList ;

  if (ReadInputVariableFile (InputVariableList,variableList) <= 0 )
    {
      cerr << " Empty Variable List File or not Exisisting --> Exit "
           << endl ; 
      return -1 ;
    }

  // take lumi and other parameters
  double lumi  =  gConfigParser->readDoubleOption ("Option::Lumi") ; // fb^ (-1)
  lumi *= 1000. ;   // transform into pb^ (-1)

  lheLevelFilter      = gConfigParser->readDoubleOption ("Option::lheLevelFilter") ;
  matchingCone        = gConfigParser->readDoubleOption ("Option::matchingCone") ; 
  minLeptonCleaningPt = gConfigParser->readDoubleOption ("Option::minLeptonCleaningPt") ; 
  minLeptonCutPt      = gConfigParser->readDoubleOption ("Option::minLeptonCutPt") ;
  minJetCutPt         = gConfigParser->readDoubleOption ("Option::minJetCutPt") ;
  usePuppiAsDefault   = gConfigParser->readBoolOption   ("Option::usePuppiAsDefault") ;
  leptonIsoCut_mu     = gConfigParser->readDoubleOption ("Option::leptonIsoCutMu") ;
  leptonIsoCut_el     = gConfigParser->readDoubleOption ("Option::leptonIsoCutEl") ;
  leptonIsoCutLoose   = gConfigParser->readDoubleOption ("Option::leptonIsoCutLoose") ;

  // output directory
  string outputPlotDirectory = gConfigParser->readStringOption ("Output::outputPlotDirectory") ;
  system ( ("mkdir -p output/"+outputPlotDirectory).c_str ()) ;
  system ( ("rm -r output/"+outputPlotDirectory+"/*").c_str ()) ;

  ///// Start the analysis  
  map<string,TH1F*> histoCutEff ;

  TChain* chain = new TChain (treeName.c_str ()) ;  
  chain->Add ( (InputBaseDirectory+"/*.root").c_str ()) ;
  int totEvent = chain->GetEntries () ;

  readTree* reader  = new readTree ( (TTree*) (chain)) ;

  int maximumEvents = chain->GetEntries () ;
  if (maxEventNumber > 0 && maxEventNumber < maximumEvents) 
    maximumEvents = maxEventNumber ;
  
  float weight = 1.0 * lumi * CrossSection / float (maximumEvents) ;
  cout<< "Lumi (fb-1) "                   << lumi/1000.
      << ", entries before : "            << totEvent
      << ", cross section : "             << CrossSection
      << ", Nevents before selections : " << lumi * CrossSection
      << ", weight : "                    << weight 
      << endl ;

  // make the plot container 
  vector<histoContainer> plotVector ;

  for (size_t iCut = 0 ; iCut < CutList.size () ; iCut++)
    {
      histoCutEff["WW_EWK_"+CutList.at (iCut).cutLayerName] = 
         new TH1F ( ("WW_EWK_"+CutList.at (iCut).cutLayerName).c_str (), "", 15, 0, 15) ;
      for (size_t iVar = 0 ; iVar < variableList.size () ; iVar++)
        {
          plotVector.push_back (histoContainer (CutList.at (iCut).cutLayerName,variableList.at (iVar))) ;
        }
    }

  int passingLHEFilter = 0 ;
  
  // Loop on the events
  for (int iEvent = 0 ; iEvent < maximumEvents ; iEvent++)
    {
      reader->fChain->GetEntry (iEvent) ;
      if (iEvent % 100000 == 0) cout << "reading event " << iEvent << "\n" ;
  
      // filter LHE level leptons
      if (lheLevelFilter == 0)
        {
          if (fabs (reader->leptonLHEpid1) != 13 or 
              fabs (reader->leptonLHEpid2) != 13) continue ;
        }
      else if (lheLevelFilter == 1)
        {
          if (fabs (reader->leptonLHEpid1) != 11 or 
              fabs (reader->leptonLHEpid2) != 11) continue ;
        }
      else if (lheLevelFilter == 2)
        {
          if (fabs (reader->leptonLHEpid1) == fabs (reader->leptonLHEpid2)) continue ;
        }
  
      passingLHEFilter++ ;
  
      // if an event pass the cut, fill the associated map                                                                                                                         
      TLorentzVector L_lepton1, L_lepton2, L_parton1, L_parton2 ;
  
      L_lepton1.SetPtEtaPhiM (reader->leptonLHEpt1,reader->leptonLHEeta1,reader->leptonLHEphi1,reader->leptonLHEm1) ;
      L_lepton2.SetPtEtaPhiM (reader->leptonLHEpt2,reader->leptonLHEeta2,reader->leptonLHEphi2,reader->leptonLHEm2) ;
  
      L_parton1.SetPtEtaPhiM (reader->jetLHEPartonpt1,reader->jetLHEPartoneta1,reader->jetLHEPartonphi1,0.) ;
      L_parton2.SetPtEtaPhiM (reader->jetLHEPartonpt2,reader->jetLHEPartoneta2,reader->jetLHEPartonphi2,0.) ;
  
      if (L_lepton1.Pt () < minLeptonCutPt or 
          L_lepton2.Pt () < minLeptonCutPt) continue ;
  
      if (L_parton1.Eta () * L_parton2.Eta () > 0) continue ;
      
      // Loop  on the cut list --> one cut for each polarization
      for (size_t iCut = 0 ; iCut < CutList.size () ; iCut++)
        {
    
          // cut the events
          string name = "WW_EWK" ;
          if (!passCutContainerSelection (reader,
                                        CutList.at (iCut),
                                        name,
                                        usePuppiAsDefault,
                                        minLeptonCutPt,
                                        minLeptonCleaningPt,
                                        leptonIsoCut_mu,
                                        leptonIsoCut_el,
                                        leptonIsoCutLoose,
                                        matchingCone,
                                        minJetCutPt,
                                        histoCutEff)) continue ;
    
          
          // if an event passes the cut, fill the associated map
    
          // dump all the leptons in the event                                                                                                                                       
          vector<leptonContainer> LeptonsAll ;
          fillRecoLeptonsArray (LeptonsAll, *reader) ;
    
          // dump tight leptons                                                                                                                                                     
          vector<leptonContainer> leptonsIsoTight ;
          leptonsIsoTight = dumpLeptons (LeptonsAll, leptonIsoCut_mu, leptonIsoCut_el, minLeptonCutPt) ;
    
          TLorentzVector L_dilepton = leptonsIsoTight.at (0).lepton4V_ + leptonsIsoTight.at (1).lepton4V_ ;
          TLorentzVector L_met ; 
          L_met.SetPtEtaPhiM (reader->pfmet,0.,reader->pfmetphi, 0.) ;
          TLorentzVector L_LLmet = L_dilepton + L_met ;
          TLorentzVector L_puppi_met ;
          L_puppi_met.SetPtEtaPhiM (reader->pfmet_puppi,0.,reader->pfmetphi_puppi, 0.) ;
    
          float asimJ = 0, asimL = 0, Rvar = 0 ;
    
          // take reco jets                                                                                                                                                         
          vector<jetContainer> RecoJetsAll ;
          if (not usePuppiAsDefault)
            fillRecoJetArray (RecoJetsAll, *reader) ;
          else 
            fillPuppiJetArray (RecoJetsAll, *reader) ;
    
          // take jets                                                                                                                                                         
          vector<jetContainer> RecoJets ;
          RecoJets  = dumpJets (RecoJetsAll, leptonsIsoTight, minJetCutPt, CutList.at (iCut).bTagVeto, CutList.at (iCut).jetPUID, minLeptonCleaningPt, matchingCone) ;
    
          asimL = (leptonsIsoTight.at (0).lepton4V_.Pt ()-leptonsIsoTight.at (1).lepton4V_.Pt ())/ (leptonsIsoTight.at (0).lepton4V_.Pt ()+leptonsIsoTight.at (1).lepton4V_.Pt ()) ;
    
          TLorentzVector L_dijet ;
          if (RecoJets.size () >= 2)
            {
              L_dijet  = RecoJets.at (0).jet4V_ + RecoJets.at (1).jet4V_ ;
              asimJ    = (RecoJets.at (0).jet4V_.Pt ()-RecoJets.at (1).jet4V_.Pt ())/ (RecoJets.at (0).jet4V_.Pt ()+RecoJets.at (1).jet4V_.Pt ()) ;
              Rvar     = (leptonsIsoTight.at (0).lepton4V_.Pt ()*leptonsIsoTight.at (1).lepton4V_.Pt ())/ (RecoJets.at (0).jet4V_.Pt ()*RecoJets.at (1).jet4V_.Pt ()) ;
            }
    
          // loop on variables
          for (size_t iVar = 0 ; iVar < variableList.size () ; ++iVar)
            {
              histoContainer tmpPlot ;
              tmpPlot.cutName = CutList.at (iCut).cutLayerName ;
              tmpPlot.varName = variableList.at (iVar).variableName ;
              vector<histoContainer>::iterator itVec ;
              itVec = find (plotVector.begin (), plotVector.end (), tmpPlot) ;
              if (itVec == plotVector.end ())
                {
                  cerr << "Problem -->plot not found for "
                       << CutList.at (iCut).cutLayerName 
                       << "  " << variableList.at (iVar).variableName
                       << endl ;
                  continue ;
                }
              if (variableList.at (iVar).variableName == "ptj1" and RecoJets.size () >=2){
                    itVec->histogram->Fill (RecoJets.at (0).jet4V_.Pt (),1.*weight) ; 
                  }
              else if (variableList.at (iVar).variableName == "ptj2" and RecoJets.size () >=2){
                    itVec->histogram->Fill (RecoJets.at (1).jet4V_.Pt (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "etaj1" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (RecoJets.at (0).jet4V_.Eta ()),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "etaj2" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (RecoJets.at (1).jet4V_.Eta ()),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "detajj" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (RecoJets.at (0).jet4V_.Eta ()-RecoJets.at (1).jet4V_.Eta ()),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "ptjj" and RecoJets.size () >=2){
                    itVec->histogram->Fill (L_dijet.Pt (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "mjj" and RecoJets.size () >=2){
                    itVec->histogram->Fill (L_dijet.M (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "dRjj" and RecoJets.size () >=2){
                    itVec->histogram->Fill (RecoJets.at (0).jet4V_.DeltaR (RecoJets.at (1).jet4V_),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "Asim_j" and RecoJets.size () >=2){
                    itVec->histogram->Fill (asimJ,weight) ;
                  }
              else if (variableList.at (iVar).variableName == "DeltaPhi_JJ" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (RecoJets.at (0).jet4V_.DeltaPhi (RecoJets.at (1).jet4V_)),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "etaj1etaj2" and RecoJets.size () >=2){
                    itVec->histogram->Fill (RecoJets.at (0).jet4V_.Eta ()*RecoJets.at (1).jet4V_.Eta (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "ptl1" and RecoJets.size () >=2){
                    itVec->histogram->Fill (leptonsIsoTight.at (0).lepton4V_.Pt (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "ptl2" and RecoJets.size () >=2){
                    itVec->histogram->Fill (leptonsIsoTight.at (1).lepton4V_.Pt (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "etal1" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (leptonsIsoTight.at (0).lepton4V_.Eta ()),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "etal2" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (leptonsIsoTight.at (1).lepton4V_.Eta ()),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "mll" and RecoJets.size () >=2){
                    itVec->histogram->Fill (L_dilepton.M (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "ptll" and RecoJets.size () >=2){
                    itVec->histogram->Fill (L_dilepton.Pt (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "etall" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (L_dilepton.Eta ()),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "phill" and RecoJets.size () >=2){
                    itVec->histogram->Fill (L_dilepton.Phi (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "dRll" and RecoJets.size () >=2){
                    itVec->histogram->Fill (leptonsIsoTight.at (0).lepton4V_.DeltaR (leptonsIsoTight.at (1).lepton4V_),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "etal1etal2" and RecoJets.size () >=2){
                    itVec->histogram->Fill (leptonsIsoTight.at (0).lepton4V_.Eta ()*leptonsIsoTight.at (1).lepton4V_.Eta (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "DeltaPhi_LL" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (leptonsIsoTight.at (0).lepton4V_.DeltaPhi (leptonsIsoTight.at (1).lepton4V_)),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "DeltaEta_LL" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (leptonsIsoTight.at (0).lepton4V_.Eta ()-leptonsIsoTight.at (1).lepton4V_.Eta ()),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "Asim_l" and RecoJets.size () >=2){
                    itVec->histogram->Fill (asimL,weight) ;
                  }
              else if (variableList.at (iVar).variableName == "met" and RecoJets.size () >=2){
                    itVec->histogram->Fill (L_met.Pt (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "R" and RecoJets.size () >=2){
                    itVec->histogram->Fill (Rvar,weight) ;
                  }
              else if (variableList.at (iVar).variableName == "DeltaPhi_LMet" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (leptonsIsoTight.at (0).lepton4V_.DeltaPhi (L_met)),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "ptLMet" and RecoJets.size () >=2){
                    itVec->histogram->Fill ( (leptonsIsoTight.at (0).lepton4V_ + L_met).Pt (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "DeltaPhi_TLMet" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (leptonsIsoTight.at (0).lepton4V_.DeltaPhi (L_met)),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "ptTLMet" and RecoJets.size () >=2){
                    itVec->histogram->Fill ( (leptonsIsoTight.at (1).lepton4V_ + L_met).Pt (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "DeltaPhi_LLMet" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (L_dilepton.DeltaPhi (L_met)),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "ptLLMet" and RecoJets.size () >=2){
                    itVec->histogram->Fill ( (L_dilepton + L_met).Pt (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "DeltaPhi_LJL" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (leptonsIsoTight.at (0).lepton4V_.DeltaPhi (RecoJets.at (0).jet4V_)),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "ptLJL" and RecoJets.size () >=2){
                    itVec->histogram->Fill ( (leptonsIsoTight.at (0).lepton4V_+RecoJets.at (0).jet4V_).Pt (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "dR_LJL" and RecoJets.size () >=2){
                    itVec->histogram->Fill (leptonsIsoTight.at (0).lepton4V_.DeltaR (RecoJets.at (0).jet4V_),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "DeltaPhi_TJL" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (leptonsIsoTight.at (0).lepton4V_.DeltaPhi (RecoJets.at (1).jet4V_)),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "ptTJL" and RecoJets.size () >=2){
                    itVec->histogram->Fill ( (leptonsIsoTight.at (0).lepton4V_+RecoJets.at (1).jet4V_).Pt (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "dR_TJL" and RecoJets.size () >=2){
                    itVec->histogram->Fill (leptonsIsoTight.at (0).lepton4V_.DeltaR (RecoJets.at (1).jet4V_),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "DeltaPhi_JJL" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (leptonsIsoTight.at (0).lepton4V_.DeltaPhi (L_dijet)),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "ptJJL" and RecoJets.size () >=2){
                    itVec->histogram->Fill ( (leptonsIsoTight.at (0).lepton4V_+L_dijet).Pt (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "dR_JJL" and RecoJets.size () >=2){
                    itVec->histogram->Fill (leptonsIsoTight.at (0).lepton4V_.DeltaR (L_dijet),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "DeltaPhi_LJTL" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (leptonsIsoTight.at (1).lepton4V_.DeltaPhi (RecoJets.at (0).jet4V_)),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "DeltaPhi_TJTL" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (leptonsIsoTight.at (1).lepton4V_.DeltaPhi (RecoJets.at (1).jet4V_)),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "DeltaPhi_JJTL" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (leptonsIsoTight.at (1).lepton4V_.DeltaPhi (L_dijet)),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "dR_LJTL" and RecoJets.size () >=2){
                    itVec->histogram->Fill (leptonsIsoTight.at (1).lepton4V_.DeltaR (RecoJets.at (0).jet4V_),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "dR_TJTL" and RecoJets.size () >=2){
                    itVec->histogram->Fill (leptonsIsoTight.at (1).lepton4V_.DeltaR (RecoJets.at (1).jet4V_),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "dR_JJTL" and RecoJets.size () >=2){
                    itVec->histogram->Fill (leptonsIsoTight.at (1).lepton4V_.DeltaR (L_dijet),weight) ;
                  }          
              else if (variableList.at (iVar).variableName == "ptLJTL" and RecoJets.size () >=2){
                    itVec->histogram->Fill ( (leptonsIsoTight.at (1).lepton4V_+RecoJets.at (0).jet4V_).Pt (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "ptTJTL" and RecoJets.size () >=2){
                    itVec->histogram->Fill ( (leptonsIsoTight.at (1).lepton4V_+RecoJets.at (1).jet4V_).Pt (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "ptJJTL" and RecoJets.size () >=2){
                    itVec->histogram->Fill ( (leptonsIsoTight.at (1).lepton4V_+L_dijet).Pt (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "DeltaPhi_LJLL" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (L_dilepton.DeltaPhi (RecoJets.at (0).jet4V_)),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "DeltaPhi_TJLL" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (L_dilepton.DeltaPhi (RecoJets.at (1).jet4V_)),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "DeltaPhi_JJLL" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (L_dilepton.DeltaPhi (L_dijet)),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "dR_LJLL" and RecoJets.size () >=2){
                    itVec->histogram->Fill (L_dilepton.DeltaR (RecoJets.at (0).jet4V_),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "dR_TJLL" and RecoJets.size () >=2){
                    itVec->histogram->Fill (L_dilepton.DeltaR (RecoJets.at (1).jet4V_),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "dR_JJLL" and RecoJets.size () >=2){
                    itVec->histogram->Fill (L_dilepton.DeltaR (L_dijet),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "ptLJLL" and RecoJets.size () >=2){
                    itVec->histogram->Fill ( (L_dilepton+RecoJets.at (0).jet4V_).Pt (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "ptTJLL" and RecoJets.size () >=2){
                    itVec->histogram->Fill ( (L_dilepton+RecoJets.at (1).jet4V_).Pt (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "ptJJLL" and RecoJets.size () >=2){
                    itVec->histogram->Fill ( (L_dilepton+L_dijet).Pt (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "DeltaPhi_JJMet" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (L_dijet.DeltaPhi (L_met)),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "ptJJMet" and RecoJets.size () >=2){
                    itVec->histogram->Fill ( (L_dijet+L_met).Pt (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "DeltaPhi_LJMet" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (RecoJets.at (0).jet4V_.DeltaPhi (L_met)),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "ptLJMet" and RecoJets.size () >=2){
                    itVec->histogram->Fill ( (RecoJets.at (0).jet4V_+L_met).Pt (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "DeltaPhi_TJMet" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (RecoJets.at (1).jet4V_.DeltaPhi (L_met)),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "ptTJMet" and RecoJets.size () >=2){
                    itVec->histogram->Fill ( (RecoJets.at (1).jet4V_+L_met).Pt (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "ptJJ_LLMet" and RecoJets.size () >=2){
                    itVec->histogram->Fill ( (L_dijet+L_LLmet).Pt (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "DeltaPhi_JJ_LLMet" and RecoJets.size () >=2){
                    itVec->histogram->Fill (fabs (L_dijet.DeltaPhi (L_LLmet)),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "dR_JJ_LLMet" and RecoJets.size () >=2){
                    itVec->histogram->Fill (L_dijet.DeltaR (L_LLmet),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "mlljj" and RecoJets.size () >=2){
                    itVec->histogram->Fill ( (L_dilepton+L_dijet).M (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "mlljjmet" and RecoJets.size () >=2){
                    itVec->histogram->Fill ( (L_dilepton+L_dijet+L_met).M (),weight) ;
                  }
              else if (variableList.at (iVar).variableName == "mTH" and RecoJets.size () >=2){
                    itVec->histogram->Fill (sqrt (2*L_dilepton.Pt ()*L_met.Pt ()* (1-TMath::Cos (L_dilepton.DeltaPhi (L_met)))),weight) ;
                  } 
            } // loop on variables
        } // Loop  on the cut list
    } // Loop on the events

  TFile* outputEfficiency = new TFile ( ("output/"+outputPlotDirectory+"/outputEfficiency.root").c_str (),"RECREATE") ;

  for (map<string,TH1F*>::const_iterator itMap = histoCutEff.begin () ; itMap !=  histoCutEff.end () ; itMap++)
    {
      itMap->second->Scale (1./itMap->second->GetBinContent (1)) ;
      itMap->second->Write () ;
    }

  outputEfficiency->Close () ;    

  // do the simulation thing for each variable
  // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

  cout << " STARTING THE PERFORMANCE EVALUATION\n" ;
  cout << "  ---- ---- ---- ---- ---- ---- ----\n" ;

  // make the canvas and basic banners                                                                                                                                         
  TCanvas *cCanvas = new TCanvas ("cCanvas","",1,52,550,550) ;
  cCanvas->SetTicks () ;
  cCanvas->SetFillColor (0) ;
  cCanvas->SetBorderMode (0) ;
  cCanvas->SetBorderSize (2) ;
  cCanvas->SetTickx (1) ;
  cCanvas->SetTicky (1) ;
  cCanvas->SetRightMargin (0.05) ;
  cCanvas->SetBottomMargin (0.12) ;
  cCanvas->SetFrameBorderMode (0) ;

  int Ntoys = gConfigParser->readIntOption ("Option::Ntoys") ;
  int EventsPerToy = gConfigParser->readIntOption ("Option::EventsPerToy") ;
  int makeDeatailedPlots = gConfigParser->readFloatOption ("Output::makeDetailedPlots") ;

  cout << " + running " << Ntoys
       << " toys, with " << EventsPerToy << " events each\n" ;
  
  // loop on variables
  for (size_t iVar = 0 ; iVar < variableList.size () ; iVar++)
    {
      TH1F * h_sig = 0 ;
      TH1F * h_bkg = 0 ; 

      // loop on cuts = loop on polarisations
      for (size_t iCut = 0 ; iCut < CutList.size () ; iCut++)
        {
          histoContainer tmpPlot ;
          tmpPlot.cutName = CutList.at (iCut).cutLayerName ;
          tmpPlot.varName = variableList.at (iVar).variableName ;
          vector<histoContainer>::iterator itVec ;
          itVec = find (plotVector.begin (), plotVector.end (), tmpPlot) ;
          if (itVec == plotVector.end ())
            {
              cerr << "Problem -->plot not found for " << CutList.at (iCut).cutLayerName 
                   << "  " << variableList.at (iVar).variableName 
                   << endl ;
            }
          if (itVec->findCutByLabel ("LL"))
            {
              if (h_sig == 0) h_sig = itVec->histogram ;
              else
                {
                  cerr << "ERROR TOO MANY SIGNALS " << endl ;
                  exit (1) ;
                }
            }
          else
            {      
              if (h_bkg == 0) 
                {
                  TString name = "totalBkg_" ;
                  name += itVec->histogram->GetName () ;
                  h_bkg = (TH1F *) itVec->histogram->Clone (name) ;
                }
              else h_bkg->Add (itVec->histogram) ;
            }
        } // loop on cuts = loop on polarisations

      h_bkg->Draw () ;
      h_sig->Draw ("same") ;
      cCanvas->Print (string ("output/" + outputPlotDirectory + "/" + variableList.at (iVar).variableName + "_beforePlaying.png").c_str (), "png") ;

      TH1F * totalModel = (TH1F *) h_bkg->Clone ("totalModel") ;
      totalModel->Add (h_sig) ;
      
      float int_sig = h_sig->Integral () ;
      float int_bkg = h_bkg->Integral () ;
      
      cout << "DEBUG FIXME expected number of SIG events : " << int_sig << endl ;
      cout << "DEBUG FIXME expected number of BKG events : " << int_bkg << endl ;
      
      h_sig->Scale (1./int_sig) ;
      h_bkg->Scale (1./int_bkg) ;

      // prepare the RooDataHist
      RooRealVar x ("x", "x", 
                    h_sig->GetXaxis ()->GetXmin (), 
                    h_sig->GetXaxis ()->GetXmax ()) ;   
      x.setRange("allofit",
                 h_sig->GetXaxis ()->GetXmin (), 
                 h_sig->GetXaxis ()->GetXmax ()) ;   
      RooDataHist rdh_sig ("rdh", "rdh", RooArgList (x), h_sig) ;
      RooDataHist rdh_bkg ("rdh", "rdh", RooArgList (x), h_bkg) ;
      RooDataHist rdh_totalModel ("rdh", "rdh", RooArgList (x), h_sig) ;
      RooHistPdf pdf_totalModel ("pdf_totalModel", "pdf_totalModel", RooArgSet (x), rdh_totalModel) ;
      
      RooHistPdf pdf_sig ("pdf_sig", "pdf_sig", RooArgSet (x), rdh_sig) ;
      RooHistPdf pdf_bkg ("pdf_bkg", "pdf_bkg", RooArgSet (x), rdh_bkg) ;
      // fixme scegli i limiti ed il valore centrale!!!

//      float sample_fraction = int_sig / (int_sig + int_bkg) ;

      RooRealVar coef_sig ("coef_sig", "coef_sig", int_sig, 0.1 * int_sig, 10. * int_sig) ;   
      TH1F sig_fitResults ("sig_fitResults", "sig_fitResults", 100, 0.3 * int_sig, 1.7  * int_sig) ;
      RooRealVar coef_bkg ("coef_bkg", "coef_bkg", int_bkg, 0.1 * int_bkg, 10. * int_bkg) ;   
      TH1F bkg_fitResults ("bkg_fitResults", "bkg_fitResults", 100, 0.3 * int_bkg, 1.7 * int_bkg) ;
      RooAddPdf fittingFunction ("fittingFunction", "fittingFunction", 
          RooArgList (pdf_sig, pdf_bkg),
          RooArgList (coef_sig, coef_bkg)
        ) ;  

      if (EventsPerToy == -1) EventsPerToy = int (int_sig + int_bkg) ;

      // loop over toy exp
      for (int i = 0 ; i < Ntoys ; ++i)
        {
          RooDataSet * data = pdf_totalModel.generate (RooArgSet (x), EventsPerToy) ;
          fittingFunction.fitTo (*data, PrintLevel (-10)) ;
//          fittingFunction.fitTo (*data, Minos (kTRUE), PrintLevel (-10)) ;
          sig_fitResults.Fill (coef_sig.getVal ()) ;
          bkg_fitResults.Fill (coef_bkg.getVal ()) ;
//          sig_fitResults.Fill (coef_sig.getVal () / EventsPerToy) ;
//          bkg_fitResults.Fill (coef_bkg.getVal () / EventsPerToy) ;

//          RooAbsReal* fracInt = fittingFunction.createIntegral (x) ;
//          cout << " INTEGRAL INTEGRAL INTEGRAL " << fracInt->getVal () << endl ;

          if (makeDeatailedPlots)
            {
              RooPlot * localxplot = x.frame () ;
              data->plotOn (localxplot, MarkerColor (kRed)) ;
              fittingFunction.plotOn (localxplot, DrawOption ("F"), FillColor (kGray + 2), Components (RooArgSet(pdf_bkg))) ;
              fittingFunction.plotOn (localxplot, LineColor (kBlue + 2)) ;
              pdf_totalModel.plotOn (localxplot, LineWidth (1), LineColor (kGreen + 1)) ; //,LineStyle (kDashed)
              localxplot->Draw () ;
              TString fileName = "_fit_" ;
              fileName += i ;
              fileName += ".png" ;
              cCanvas->Print ("output/" + outputPlotDirectory + "/" + variableList.at (iVar).variableName + fileName, "png") ;
            }
        }

      sig_fitResults.Draw () ;
      cCanvas->SaveAs (string ("output/"+outputPlotDirectory+"/"+variableList.at (iVar).variableName+"_sig_perf.png").c_str (),"png") ;
      bkg_fitResults.Draw () ;
      cCanvas->SaveAs (string ("output/"+outputPlotDirectory+"/"+variableList.at (iVar).variableName+"_bkg_perf.png").c_str (),"png") ;

    } // loop on variables
    
  cout << "LHE filter efficiency : " << passingLHEFilter
       << " totEvent " << totEvent
       << " efficiency " << float (passingLHEFilter)/float (totEvent)*100
       << " % " << endl ;
  
  return 0 ;
}  
