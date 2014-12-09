/*
cjv plots
-------------------
*/

#include <iostream>
#include <map>

#include "TChain.h"
#include "TLorentzVector.h"

#include "readTree.h"
#include "plotter.h"

using namespace std ;


double 
deltaPhi (double phi1, double phi2)
{
  double deltaphi=fabs(phi1-phi2);
  if (deltaphi > 6.283185308) deltaphi -= 6.283185308;
  if (deltaphi > 3.141592654) deltaphi = 6.283185308-deltaphi;
  return deltaphi;
}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- -


void fillHistos (plotter & analysisPlots, readTree & reader, const string sampleName)
{
  int maxevents = reader.fChain->GetEntries () ;
  cout << "reading sample " << sampleName 
       << " with " << maxevents << " entries\n" ;
  // loop over events
  for (int iEvent = 0 ; iEvent < maxevents ; ++iEvent)
    {
      reader.GetEntry (iEvent) ;
      if (iEvent % 10000 == 0) cout << "reading event " << iEvent << "\n" ; 

      if (reader.pt1 < 0    ||
          reader.pt2 < 0    ||
          reader.jetpt1 < 0 ||
          reader.jetpt2 < 0) continue ;

      TLorentzVector L_leadi_lepton ;
      L_leadi_lepton.SetPtEtaPhiM (reader.pt1, reader.eta1, reader.phi1, 0.) ;

      TLorentzVector L_trail_lepton ;
      L_trail_lepton.SetPtEtaPhiM (reader.pt2, reader.eta2, reader.phi2, 0.) ;

      TLorentzVector L_leadi_jet ;
      L_leadi_jet.SetPtEtaPhiM (reader.jetpt1, reader.jeteta1, reader.jetphi1, 0.) ;

      TLorentzVector L_trail_jet ;
      L_trail_jet.SetPtEtaPhiM (reader.jetpt2, reader.jeteta2, reader.jetphi2, 0.) ;

      float TJ_etaMin = reader.jeteta1 ;
      float TJ_etaMax = reader.jeteta2 ;
      if (TJ_etaMin > TJ_etaMax) swap (TJ_etaMin, TJ_etaMax) ;
      
      int TKJ_num = 0 ;
      int TKJ_num_OneGeV = 0 ;
      int TKJ_num_ThreeGeV = 0 ;
      float TKJ_SumHT = 0 ;
      float TKJ_SumHT_OneGeV = 0 ;
      float TKJ_SumHT_ThreeGeV = 0 ;

      int TKJ_num_IN = 0 ;
      int TKJ_num_OneGeV_IN = 0 ;
      int TKJ_num_ThreeGeV_IN = 0 ;
      float TKJ_SumHT_IN = 0 ;
      float TKJ_SumHT_OneGeV_IN = 0 ;
      float TKJ_SumHT_ThreeGeV_IN = 0 ;

      // tk jet 1 
      if (reader.jetTrackpt1 > 0)
        {
          analysisPlots.fillHisto (sampleName, "total", "tkJetPt", reader.jetTrackpt1, 1.) ;
          ++TKJ_num ;
          TKJ_SumHT += reader.jetTrackpt1 ;
          if (reader.jetTrackpt1 > 1.) 
            {
              ++TKJ_num_OneGeV ;
              TKJ_SumHT_OneGeV += reader.jetTrackpt1 ;
            }
          if (reader.jetTrackpt1 > 3.) 
            {
              ++TKJ_num_ThreeGeV ;
              TKJ_SumHT_ThreeGeV += reader.jetTrackpt1 ;
            }
          // only the central region  
          if (reader.jetTracketa1 < TJ_etaMin ||
              reader.jetTracketa1 > TJ_etaMax) continue ;  
          analysisPlots.fillHisto (sampleName, "total", "tkJetPt_IN", reader.jetTrackpt1, 1.) ;
          ++TKJ_num_IN ;
          TKJ_SumHT_IN += reader.jetTrackpt1 ;
          if (reader.jetTrackpt1 > 1.) 
            {
              ++TKJ_num_OneGeV_IN ;
              TKJ_SumHT_OneGeV_IN += reader.jetTrackpt1 ;
            }
          if (reader.jetTrackpt1 > 3.) 
            {
              ++TKJ_num_ThreeGeV_IN ;
              TKJ_SumHT_ThreeGeV_IN += reader.jetTrackpt1 ;
            }
        }
      
      // tk jet 2 
      if (reader.jetTrackpt2 > 0)
        {
          analysisPlots.fillHisto (sampleName, "total", "tkJetPt", reader.jetTrackpt2, 1.) ;
          ++TKJ_num ;
          TKJ_SumHT += reader.jetTrackpt2 ;
          if (reader.jetTrackpt2 > 1.) 
            {
              ++TKJ_num_OneGeV ;
              TKJ_SumHT_OneGeV += reader.jetTrackpt2 ;
            }
          if (reader.jetTrackpt2 > 3.) 
            {
              ++TKJ_num_ThreeGeV ;
              TKJ_SumHT_ThreeGeV += reader.jetTrackpt2 ;
            }
          // only the central region  
          if (reader.jetTracketa2 < TJ_etaMin ||
              reader.jetTracketa2 > TJ_etaMax) continue ;  
          analysisPlots.fillHisto (sampleName, "total", "tkJetPt_IN", reader.jetTrackpt2, 1.) ;
          ++TKJ_num_IN ;
          TKJ_SumHT_IN += reader.jetTrackpt2 ;
          if (reader.jetTrackpt2 > 1.) 
            {
              ++TKJ_num_OneGeV_IN ;
              TKJ_SumHT_OneGeV_IN += reader.jetTrackpt2 ;
            }
          if (reader.jetTrackpt2 > 3.) 
            {
              ++TKJ_num_ThreeGeV_IN ;
              TKJ_SumHT_ThreeGeV_IN += reader.jetTrackpt2 ;
            }
        }
      
      // tk jet 3 
      if (reader.jetTrackpt3 > 0)
        {
          analysisPlots.fillHisto (sampleName, "total", "tkJetPt", reader.jetTrackpt3, 1.) ;
          ++TKJ_num ;
          TKJ_SumHT += reader.jetTrackpt3 ;
          if (reader.jetTrackpt3 > 1.) 
            {
              ++TKJ_num_OneGeV ;
              TKJ_SumHT_OneGeV += reader.jetTrackpt3 ;
            }
          if (reader.jetTrackpt3 > 3.) 
            {
              ++TKJ_num_ThreeGeV ;
              TKJ_SumHT_ThreeGeV += reader.jetTrackpt3 ;
            }
          // only the central region  
          if (reader.jetTracketa3 < TJ_etaMin ||
              reader.jetTracketa3 > TJ_etaMax) continue ;  
          analysisPlots.fillHisto (sampleName, "total", "tkJetPt_IN", reader.jetTrackpt3, 1.) ;
          ++TKJ_num_IN ;
          TKJ_SumHT_IN += reader.jetTrackpt3 ;
          if (reader.jetTrackpt3 > 1.) 
            {
              ++TKJ_num_OneGeV_IN ;
              TKJ_SumHT_OneGeV_IN += reader.jetTrackpt3 ;
            }
          if (reader.jetTrackpt3 > 3.) 
            {
              ++TKJ_num_ThreeGeV_IN ;
              TKJ_SumHT_ThreeGeV_IN += reader.jetTrackpt3 ;
            }
        }
      
      // tk jet 4 
      if (reader.jetTrackpt4 > 0)
        {
          analysisPlots.fillHisto (sampleName, "total", "tkJetPt", reader.jetTrackpt4, 1.) ;
          ++TKJ_num ;
          TKJ_SumHT += reader.jetTrackpt4 ;
          if (reader.jetTrackpt4 > 1.) 
            {
              ++TKJ_num_OneGeV ;
              TKJ_SumHT_OneGeV += reader.jetTrackpt4 ;
            }
          if (reader.jetTrackpt4 > 3.) 
            {
              ++TKJ_num_ThreeGeV ;
              TKJ_SumHT_ThreeGeV += reader.jetTrackpt4 ;
            }
          // only the central region  
          if (reader.jetTracketa4 < TJ_etaMin ||
              reader.jetTracketa4 > TJ_etaMax) continue ;  
          analysisPlots.fillHisto (sampleName, "total", "tkJetPt_IN", reader.jetTrackpt4, 1.) ;
          ++TKJ_num_IN ;
          TKJ_SumHT_IN += reader.jetTrackpt4 ;
          if (reader.jetTrackpt4 > 1.) 
            {
              ++TKJ_num_OneGeV_IN ;
              TKJ_SumHT_OneGeV_IN += reader.jetTrackpt4 ;
            }
          if (reader.jetTrackpt4 > 3.) 
            {
              ++TKJ_num_ThreeGeV_IN ;
              TKJ_SumHT_ThreeGeV_IN += reader.jetTrackpt4 ;
            }
        }
      
      // tk jet 5 
      if (reader.jetTrackpt5 > 0)
        {
          analysisPlots.fillHisto (sampleName, "total", "tkJetPt", reader.jetTrackpt5, 1.) ;
          ++TKJ_num ;
          TKJ_SumHT += reader.jetTrackpt5 ;
          if (reader.jetTrackpt5 > 1.) 
            {
              ++TKJ_num_OneGeV ;
              TKJ_SumHT_OneGeV += reader.jetTrackpt5 ;
            }
          if (reader.jetTrackpt5 > 3.) 
            {
              ++TKJ_num_ThreeGeV ;
              TKJ_SumHT_ThreeGeV += reader.jetTrackpt5 ;
            }
          // only the central region  
          if (reader.jetTracketa5 < TJ_etaMin ||
              reader.jetTracketa5 > TJ_etaMax) continue ;  
          analysisPlots.fillHisto (sampleName, "total", "tkJetPt_IN", reader.jetTrackpt5, 1.) ;
          ++TKJ_num_IN ;
          TKJ_SumHT_IN += reader.jetTrackpt5 ;
          if (reader.jetTrackpt5 > 1.) 
            {
              ++TKJ_num_OneGeV_IN ;
              TKJ_SumHT_OneGeV_IN += reader.jetTrackpt5 ;
            }
          if (reader.jetTrackpt5 > 3.) 
            {
              ++TKJ_num_ThreeGeV_IN ;
              TKJ_SumHT_ThreeGeV_IN += reader.jetTrackpt5 ;
            }
        }
      
      // tk jet 6 
      if (reader.jetTrackpt6 > 0)
        {
          analysisPlots.fillHisto (sampleName, "total", "tkJetPt", reader.jetTrackpt6, 1.) ;
          ++TKJ_num ;
          TKJ_SumHT += reader.jetTrackpt6 ;
          if (reader.jetTrackpt6 > 1.) 
            {
              ++TKJ_num_OneGeV ;
              TKJ_SumHT_OneGeV += reader.jetTrackpt6 ;
            }
          if (reader.jetTrackpt6 > 3.) 
            {
              ++TKJ_num_ThreeGeV ;
              TKJ_SumHT_ThreeGeV += reader.jetTrackpt6 ;
            }
          // only the central region  
          if (reader.jetTracketa6 < TJ_etaMin ||
              reader.jetTracketa6 > TJ_etaMax) continue ;  
          analysisPlots.fillHisto (sampleName, "total", "tkJetPt_IN", reader.jetTrackpt6, 1.) ;
          ++TKJ_num_IN ;
          TKJ_SumHT_IN += reader.jetTrackpt6 ;
          if (reader.jetTrackpt6 > 1.) 
            {
              ++TKJ_num_OneGeV_IN ;
              TKJ_SumHT_OneGeV_IN += reader.jetTrackpt6 ;
            }
          if (reader.jetTrackpt6 > 3.) 
            {
              ++TKJ_num_ThreeGeV_IN ;
              TKJ_SumHT_ThreeGeV_IN += reader.jetTrackpt6 ;
            }
        }
      
      // tk jet 7 
      if (reader.jetTrackpt7 > 0)
        {
          analysisPlots.fillHisto (sampleName, "total", "tkJetPt", reader.jetTrackpt7, 1.) ;
          ++TKJ_num ;
          TKJ_SumHT += reader.jetTrackpt7 ;
          if (reader.jetTrackpt7 > 1.) 
            {
              ++TKJ_num_OneGeV ;
              TKJ_SumHT_OneGeV += reader.jetTrackpt7 ;
            }
          if (reader.jetTrackpt7 > 3.) 
            {
              ++TKJ_num_ThreeGeV ;
              TKJ_SumHT_ThreeGeV += reader.jetTrackpt7 ;
            }
          // only the central region  
          if (reader.jetTracketa7 < TJ_etaMin ||
              reader.jetTracketa7 > TJ_etaMax) continue ;  
          analysisPlots.fillHisto (sampleName, "total", "tkJetPt_IN", reader.jetTrackpt7, 1.) ;
          ++TKJ_num_IN ;
          TKJ_SumHT_IN += reader.jetTrackpt7 ;
          if (reader.jetTrackpt7 > 1.) 
            {
              ++TKJ_num_OneGeV_IN ;
              TKJ_SumHT_OneGeV_IN += reader.jetTrackpt7 ;
            }
          if (reader.jetTrackpt7 > 3.) 
            {
              ++TKJ_num_ThreeGeV_IN ;
              TKJ_SumHT_ThreeGeV_IN += reader.jetTrackpt7 ;
            }
        }
      
      // tk jet 8 
      if (reader.jetTrackpt8 > 0)
        {
          analysisPlots.fillHisto (sampleName, "total", "tkJetPt", reader.jetTrackpt8, 1.) ;
          ++TKJ_num ;
          TKJ_SumHT += reader.jetTrackpt8 ;
          if (reader.jetTrackpt8 > 1.) 
            {
              ++TKJ_num_OneGeV ;
              TKJ_SumHT_OneGeV += reader.jetTrackpt8 ;
            }
          if (reader.jetTrackpt8 > 3.) 
            {
              ++TKJ_num_ThreeGeV ;
              TKJ_SumHT_ThreeGeV += reader.jetTrackpt8 ;
            }
          // only the central region  
          if (reader.jetTracketa8 < TJ_etaMin ||
              reader.jetTracketa8 > TJ_etaMax) continue ;  
          analysisPlots.fillHisto (sampleName, "total", "tkJetPt_IN", reader.jetTrackpt8, 1.) ;
          ++TKJ_num_IN ;
          TKJ_SumHT_IN += reader.jetTrackpt8 ;
          if (reader.jetTrackpt8 > 1.) 
            {
              ++TKJ_num_OneGeV_IN ;
              TKJ_SumHT_OneGeV_IN += reader.jetTrackpt8 ;
            }
          if (reader.jetTrackpt8 > 3.) 
            {
              ++TKJ_num_ThreeGeV_IN ;
              TKJ_SumHT_ThreeGeV_IN += reader.jetTrackpt8 ;
            }
        }
      analysisPlots.fillHisto (sampleName, "total", "tkJetNum",               TKJ_num, 1.) ;
      analysisPlots.fillHisto (sampleName, "total", "tkJetNum_OneGeV",        TKJ_num_OneGeV, 1.) ;
      analysisPlots.fillHisto (sampleName, "total", "tkJetNum_ThreeGeV",      TKJ_num_ThreeGeV, 1.) ;
      analysisPlots.fillHisto (sampleName, "total", "tkJetNum_IN",            TKJ_num_IN, 1.) ;
      analysisPlots.fillHisto (sampleName, "total", "tkJetNum_OneGeV_IN",     TKJ_num_OneGeV_IN, 1.) ;
      analysisPlots.fillHisto (sampleName, "total", "tkJetNum_ThreeGeV_IN",   TKJ_num_ThreeGeV_IN, 1.) ;
      analysisPlots.fillHisto (sampleName, "total", "tkJetSumHT",             TKJ_SumHT, 1.) ;
      analysisPlots.fillHisto (sampleName, "total", "tkJetSumHT_OneGeV",      TKJ_SumHT_OneGeV, 1.) ;
      analysisPlots.fillHisto (sampleName, "total", "tkJetSumHT_ThreeGeV",    TKJ_SumHT_ThreeGeV, 1.) ;
      analysisPlots.fillHisto (sampleName, "total", "tkJetSumHT_IN",          TKJ_SumHT_IN, 1.) ;
      analysisPlots.fillHisto (sampleName, "total", "tkJetSumHT_OneGeV_IN",   TKJ_SumHT_OneGeV_IN, 1.) ;
      analysisPlots.fillHisto (sampleName, "total", "tkJetSumHT_ThreeGeV_IN", TKJ_SumHT_ThreeGeV_IN, 1.) ;
      
    } // loop over events
  analysisPlots.setPoissonErrors () ;
  return ;
}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


int main (int argc, char ** argv)
{
  float lumi = 300. ; // fb^(-1)
  lumi *= 1000. ;   // transform into pb^(-1)
  plotter analysisPlots (lumi) ;

  // on cmsmi4
  string baseFolder = "/data2/govoni/TP/ntuples/2012-12-09/" ;   
  string etaLimit = "2p5" ;

  float XS_EWK_WW2j_126 = 4.13649215685881443E-003/*pb*/ ;
  float XS_EWK_WW2j_noH = 4.49200073018412010E-003/*pb*/ ;
  float XS_QCD_WW2j_126 = 1.06691296353271774E-003/*pb*/ ;

  // EWK 126 sample 
  // ---- ---- ---- ---- ---- ---- ----

  TChain * sample_EWK_WW2j_126 = new TChain ("easyDelphes") ;
  sample_EWK_WW2j_126->Add ((baseFolder + "PHANTOM_SS_EWK_DF_126_" + etaLimit + "/*.root").c_str ()) ;
  int totEvents_EWK_WW2j_126 = sample_EWK_WW2j_126->GetEntries () ;
  cout << "reading TChain from " << (baseFolder + "PHANTOM_SS_EWK_DF_126_" + etaLimit + "/*.root") << endl ;

  readTree reader_EWK_WW2j_126 (sample_EWK_WW2j_126) ;

  analysisPlots.addSample ("EWK_WW2j_126", XS_EWK_WW2j_126, totEvents_EWK_WW2j_126, 1, 50) ; 
  analysisPlots.addLayerToSample ("EWK_WW2j_126", "total") ; 
  
  analysisPlots.addPlotToLayer ("EWK_WW2j_126", "total", "tkJetPt",                1000, 0., 1000.) ; 
  analysisPlots.addPlotToLayer ("EWK_WW2j_126", "total", "tkJetPt_IN",             1000, 0., 1000.) ; 

  analysisPlots.addPlotToLayer ("EWK_WW2j_126", "total", "tkJetNum",               30, 0., 30.) ; 
  analysisPlots.addPlotToLayer ("EWK_WW2j_126", "total", "tkJetNum_OneGeV",        30, 0., 30.) ; 
  analysisPlots.addPlotToLayer ("EWK_WW2j_126", "total", "tkJetNum_ThreeGeV",      30, 0., 30.) ; 
  analysisPlots.addPlotToLayer ("EWK_WW2j_126", "total", "tkJetNum_IN",            30, 0., 30.) ; 
  analysisPlots.addPlotToLayer ("EWK_WW2j_126", "total", "tkJetNum_OneGeV_IN",     30, 0., 30.) ; 
  analysisPlots.addPlotToLayer ("EWK_WW2j_126", "total", "tkJetNum_ThreeGeV_IN",   30, 0., 30.) ; 

  analysisPlots.addPlotToLayer ("EWK_WW2j_126", "total", "tkJetSumHT",             200, 0., 1000.) ; 
  analysisPlots.addPlotToLayer ("EWK_WW2j_126", "total", "tkJetSumHT_OneGeV",      200, 0., 1000.) ; 
  analysisPlots.addPlotToLayer ("EWK_WW2j_126", "total", "tkJetSumHT_ThreeGeV",    200, 0., 1000.) ; 
  analysisPlots.addPlotToLayer ("EWK_WW2j_126", "total", "tkJetSumHT_IN",          200, 0., 1000.) ; 
  analysisPlots.addPlotToLayer ("EWK_WW2j_126", "total", "tkJetSumHT_OneGeV_IN",   200, 0., 1000.) ; 
  analysisPlots.addPlotToLayer ("EWK_WW2j_126", "total", "tkJetSumHT_ThreeGeV_IN", 200, 0., 1000.) ; 

  fillHistos (analysisPlots, reader_EWK_WW2j_126, "EWK_WW2j_126") ;

/*
  // EWK noH sample 
  // ---- ---- ---- ---- ---- ---- ----

  TChain * sample_EWK_WW2j_noH = new TChain ("easyDelphes") ;
  sample_EWK_WW2j_noH->Add ((baseFolder + "PHANTOM_SS_EWK_DF_noH_" + etaLimit + "/*.root").c_str ()) ;
  int totEvents_EWK_WW2j_noH = sample_EWK_WW2j_noH->GetEntries () ;

  readTree reader_EWK_WW2j_noH (sample_EWK_WW2j_noH) ;
  analysisPlots.copySampleStructure ("EWK_WW2j_noH", "EWK_WW2j_126", XS_EWK_WW2j_noH, totEvents_EWK_WW2j_noH, 0, 38) ;
  fillHistos (analysisPlots, reader_EWK_WW2j_noH, "EWK_WW2j_noH") ;
*/

  // QCD 126 sample 
  // ---- ---- ---- ---- ---- ---- ----

  TChain * sample_QCD_WW2j_126 = new TChain ("easyDelphes") ;
  sample_QCD_WW2j_126->Add ((baseFolder + "PHANTOM_SS_QCD_DF_126_" + etaLimit + "/*.root").c_str ()) ;
  int totEvents_QCD_WW2j_126 = sample_QCD_WW2j_126->GetEntries () ;

  readTree reader_QCD_WW2j_126 (sample_QCD_WW2j_126) ;
  analysisPlots.copySampleStructure ("QCD_WW2j_126", "EWK_WW2j_126", XS_QCD_WW2j_126, totEvents_QCD_WW2j_126, 0, 8) ;
  fillHistos (analysisPlots, reader_QCD_WW2j_126, "QCD_WW2j_126") ;

  // plotting
  // ---- ---- ---- ---- ---- ---- ----

  analysisPlots.plotFullLayer ("total") ;
  analysisPlots.compareStoBFullLayer ("total") ;


  return 0 ;
}  
