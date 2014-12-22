//////////////////////////////////////////////////////////////////////////////////////////////////////
// compare for a single variable the expected stats uncertainty to the difference between H and noH //
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <map>

#include "TChain.h"
#include "TLorentzVector.h"

#include "readTree.h"
#include "plotter.h"
#include "ConfigParser.h"
#include "readTree.h"
#include "utils.h"

using namespace std ;

double matchingCone ;
double minLeptonCleaningPt;
double minLeptonCutPt;
double minJetCutPt;
double leptonIsoCut;
double leptonIsoCutLoose;
bool   usePuppiAsDefault;

// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
int main (int argc, char ** argv) {

  // check number of inpt parameters
  if(argc < 2){
    cerr<<"Forgot to parse the cfg file --> exit "<<std::endl;
    return -1;
  }
 
  // parse config file parameter
  if (gConfigParser) return 1 ;
  gConfigParser = new ConfigParser();

  TString config ; 
  config.Form("%s",argv[1]);

  if(!(gConfigParser->init(config))){
      std::cout << ">>> parseConfigFile::Could not open configuration file " << config << std::endl;
      return -1;
  }

  // import base directory where samples are located and txt file with the directory name + other info
  std::string InputBaseDirectory           = gConfigParser -> readStringOption("Input::InputBaseDirectory");
  std::string InputSampleList              = gConfigParser -> readStringOption("Input::InputSampleList");

  std::map<std::string,std::vector<sampleContainer> > sampleMap ;
  if(ReadInputSampleFile(InputSampleList,sampleMap) <= 0){
    std::cerr<<" Empty Input Sample File or not Exisisting --> Exit "<<std::endl; return -1;}
  
  // treeName
  std::string treeName           = gConfigParser -> readStringOption("Input::TreeName");

  // take the cut list
  std::string InputCutList       = gConfigParser -> readStringOption("Input::InputCutList");

  std::vector <cutContainer> CutList;
  if(ReadInputCutFile(InputCutList,CutList) <= 0){
    std::cerr<<" Empty Cut List File or not Exisisting --> Exit "<<std::endl; return -1;}

  // take the variable list to be plotted
  std::string InputVariableList  = gConfigParser -> readStringOption("Input::InputVariableList");
  std::vector<variableContainer> variableList;

  if(ReadInputVariableFile(InputVariableList,variableList) <= 0 ){
    std::cerr<<" Empty Variable List File or not Exisisting --> Exit "<<std::endl; return -1;}

  double lumi  =  gConfigParser -> readDoubleOption("Option::Lumi"); // fb^(-1)
  lumi *= 1000. ;   // transform into pb^(-1)

  matchingCone        = gConfigParser -> readDoubleOption("Option::matchingCone"); 
  minLeptonCleaningPt = gConfigParser -> readDoubleOption("Option::minLeptonCleaningPt"); 
  minLeptonCutPt      = gConfigParser -> readDoubleOption("Option::minLeptonCutPt");
  minJetCutPt         = gConfigParser -> readDoubleOption("Option::minJetCutPt");
  usePuppiAsDefault   = gConfigParser -> readBoolOption("Option::usePuppiAsDefault");
  leptonIsoCut        = gConfigParser -> readDoubleOption("Option::leptonIsoCut");
  leptonIsoCutLoose   = gConfigParser -> readDoubleOption("Option::leptonIsoCutLoose");

  // output directory
  std::string outputPlotDirectory = gConfigParser -> readStringOption("Output::outputPlotDirectory");
  system(("mkdir -p output/"+outputPlotDirectory).c_str());
  system(("rm -r output/"+outputPlotDirectory+"/*").c_str());

  ///// Start the analysis
  
  plotter analysisPlots (lumi,"output") ;

  std::map<string,TH1F*> histoCutEff ;

  for( std::map<std::string,std::vector<sampleContainer> >::iterator itSample = sampleMap.begin() ; itSample != sampleMap.end(); itSample++){

   TChain* chain = new TChain (treeName.c_str()) ;  
   int numBefore = 0;
   // take input files
   for(size_t iContainer = 0; iContainer < itSample->second.size(); iContainer++){     
    numBefore += itSample->second.at(iContainer).numBefore; 
    chain->Add ((InputBaseDirectory+"/"+itSample->second.at(iContainer).sampleName+"/*1.root").c_str()) ;
    //chain->Add ((InputBaseDirectory+"/"+itSample->second.at(iContainer).sampleName+"/*2.root").c_str()) ;
    //chain->Add ((InputBaseDirectory+"/"+itSample->second.at(iContainer).sampleName+"/*3.root").c_str()) ;
    //chain->Add ((InputBaseDirectory+"/"+itSample->second.at(iContainer).sampleName+"/*4.root").c_str()) ;
   }

   int totEvent = chain->GetEntries();

   readTree* ReadTree  = new readTree((TTree*)(chain));

   // add  sample to the analysis plot container
   if(numBefore > totEvent)
     analysisPlots.addSample(itSample->first,itSample->second.at(0).xsec,numBefore, itSample->second.at(0).isSignal, itSample->second.at(0).color) ;   // create the sample to analyze
   else
     analysisPlots.addSample(itSample->first,itSample->second.at(0).xsec,totEvent, itSample->second.at(0).isSignal, itSample->second.at(0).color) ;   // create the sample to analyze
 

   // Add cuts to the analysis plot container
   for(size_t iCut = 0; iCut < CutList.size(); iCut++){
     analysisPlots.addLayerToSample  (itSample->first,CutList.at(iCut).cutLayerName) ;      
     histoCutEff[itSample->first+"_"+CutList.at(iCut).cutLayerName] = new TH1F((itSample->first+"_"+CutList.at(iCut).cutLayerName).c_str(),"",10,0,10);

     // Add variables to the plot
     for(size_t iVar = 0; iVar < variableList.size(); iVar++){   
       analysisPlots.addPlotToLayer (itSample->first,CutList.at(iCut).cutLayerName,variableList.at(iVar).variableName,
                                     variableList.at(iVar).Nbin,variableList.at(iVar).min,variableList.at(iVar).max,variableList.at(iVar).label) ;
     }
   }

   fillHistos (analysisPlots,ReadTree,CutList,variableList,itSample->first,usePuppiAsDefault,
               minLeptonCutPt,minLeptonCleaningPt,leptonIsoCut,leptonIsoCutLoose,matchingCone,minJetCutPt,histoCutEff) ; // fill the histogram
  }

    
  // plotting
  // ---- ---- ---- ---- ---- ---- ----
  analysisPlots.setPoissonErrors () ;
  for(size_t iCut = 0; iCut < CutList.size(); iCut++){
    analysisPlots.plotRelativeExcessFullLayer (CutList.at(iCut).cutLayerName, outputPlotDirectory) ;
    analysisPlots.printEventNumber(CutList.at(iCut).cutLayerName,"DeltaPhi_LL");
  }

  TFile* outputEfficiency = new TFile("output/outputEfficiency.root","RECREATE");

  for(map<string,TH1F*>::const_iterator itMap = histoCutEff.begin(); itMap !=  histoCutEff.end(); itMap++){
    itMap->second->Scale(1./itMap->second->GetBinContent(1));
    itMap->second->Write();
  }
  outputEfficiency->Close();    

  return 0 ;
}  

