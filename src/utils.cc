
#include "utils.h"

using namespace std ;

// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- -

double deltaPhi (double phi1, double phi2){
  double deltaphi=fabs(phi1-phi2);
  if (deltaphi > 6.283185308) deltaphi -= 6.283185308;
  if (deltaphi > 3.141592654) deltaphi = 6.283185308-deltaphi;
  return deltaphi;
}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- -

bool closeToLeptons (float eta, float phi, vector<leptonContainer> & TL_leptons, float R){
  for (unsigned int iLep = 0 ; iLep < TL_leptons.size () ; ++iLep){
    if ((eta - TL_leptons.at(iLep).lepton4V_.Eta ()) * (eta - TL_leptons.at(iLep).lepton4V_.Eta ()) +
	deltaPhi (phi, TL_leptons.at(iLep).lepton4V_.Phi ()) * deltaPhi (phi, TL_leptons.at(iLep).lepton4V_.Phi ()) < R * R) 
      return true ;
  }
  return false ;
}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- -


bool closeToLeptons (float eta, float phi, readTree & reader, float R){

  if ((eta - reader.eta1) * (eta - reader.eta1) +
      deltaPhi (phi, reader.phi1) * deltaPhi (phi, reader.phi1) < R * R) return true ;
  if ((eta - reader.eta2) * (eta - reader.eta2) +
      deltaPhi (phi, reader.phi2) * deltaPhi (phi, reader.phi2) < R * R) return true ;
  return false ;
}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- -


void fillRecoJetArray (vector<jetContainer> & jetVector, readTree & reader) {

  jetContainer dummy;
  if(reader.jetpt1 > 0){
    dummy.jet4V_.SetPtEtaPhiM(reader.jetpt1,reader.jeteta1,reader.jetphi1,reader.jetmass1);
    dummy.jetPUID_  = reader.jetpileupIDFlagCutBased1 ;
    dummy.btag_     = reader.jetBTagAlgo1 ;
    jetVector.push_back(dummy);
  }

  if(reader.jetpt2 > 0){
    dummy.jet4V_.SetPtEtaPhiM(reader.jetpt2,reader.jeteta2,reader.jetphi2,reader.jetmass2);
    dummy.jetPUID_  = reader.jetpileupIDFlagCutBased2 ;
    dummy.btag_     = reader.jetBTagAlgo2 ;
    jetVector.push_back(dummy);
  }
      
  if(reader.jetpt3 > 0){
    dummy.jet4V_.SetPtEtaPhiM(reader.jetpt3,reader.jeteta3,reader.jetphi3,reader.jetmass3);
    dummy.jetPUID_  = reader.jetpileupIDFlagCutBased3 ;
    dummy.btag_     = reader.jetBTagAlgo3 ;
    jetVector.push_back(dummy);
  }


  if(reader.jetpt4 > 0){
    dummy.jet4V_.SetPtEtaPhiM(reader.jetpt4,reader.jeteta4,reader.jetphi4,reader.jetmass4);
    dummy.jetPUID_  = reader.jetpileupIDFlagCutBased4 ;
    dummy.btag_     = reader.jetBTagAlgo4 ;
    jetVector.push_back(dummy);
  }
  
  if(reader.jetpt5 > 0){
    dummy.jet4V_.SetPtEtaPhiM(reader.jetpt5,reader.jeteta5,reader.jetphi5,reader.jetmass5);
    dummy.jetPUID_  = reader.jetpileupIDFlagCutBased5 ;
    dummy.btag_     = reader.jetBTagAlgo5 ;
    jetVector.push_back(dummy);
  }

  if(reader.jetpt6 > 0){
    dummy.jet4V_.SetPtEtaPhiM(reader.jetpt6,reader.jeteta6,reader.jetphi6,reader.jetmass6);
    dummy.jetPUID_  = reader.jetpileupIDFlagCutBased6 ;
    dummy.btag_     = reader.jetBTagAlgo6 ;
    jetVector.push_back(dummy);
  }

  if(reader.jetpt7 > 0){
    dummy.jet4V_.SetPtEtaPhiM(reader.jetpt7,reader.jeteta7,reader.jetphi7,reader.jetmass7);
    dummy.jetPUID_  = reader.jetpileupIDFlagCutBased7 ;
    dummy.btag_     = reader.jetBTagAlgo7 ;
    jetVector.push_back(dummy);
  }

  if(reader.jetpt8 > 0){
    dummy.jet4V_.SetPtEtaPhiM(reader.jetpt8,reader.jeteta8,reader.jetphi8,reader.jetmass8);
    dummy.jetPUID_  = reader.jetpileupIDFlagCutBased8 ;
    dummy.btag_     = reader.jetBTagAlgo8 ;
    jetVector.push_back(dummy);
  }
    
  return ;
}

// 
void fillPuppiJetArray (vector<jetContainer> & jetVector, readTree & reader) {

  jetContainer dummy;
  if(reader.jetpt_puppi1 > 0){
    dummy.jet4V_.SetPtEtaPhiM(reader.jetpt_puppi1,reader.jeteta_puppi1,reader.jetphi_puppi1,reader.jetmass_puppi1);
    dummy.jetPUID_  = reader.jetpileupIDFlagCutBased_puppi1 ;
    dummy.btag_     = reader.jetBTagAlgo_puppi1 ;
    jetVector.push_back(dummy);
  }

  if(reader.jetpt_puppi2 > 0){
    dummy.jet4V_.SetPtEtaPhiM(reader.jetpt_puppi2,reader.jeteta_puppi2,reader.jetphi_puppi2,reader.jetmass_puppi2);
    dummy.jetPUID_  = reader.jetpileupIDFlagCutBased_puppi2 ;
    dummy.btag_     = reader.jetBTagAlgo_puppi2 ;
    jetVector.push_back(dummy);
  }

  if(reader.jetpt_puppi3 > 0){
    dummy.jet4V_.SetPtEtaPhiM(reader.jetpt_puppi3,reader.jeteta_puppi3,reader.jetphi_puppi3,reader.jetmass_puppi3);
    dummy.jetPUID_  = reader.jetpileupIDFlagCutBased_puppi3 ;
    dummy.btag_     = reader.jetBTagAlgo_puppi3 ;
    jetVector.push_back(dummy);
  }

  if(reader.jetpt_puppi4 > 0){
    dummy.jet4V_.SetPtEtaPhiM(reader.jetpt_puppi4,reader.jeteta_puppi4,reader.jetphi_puppi4,reader.jetmass_puppi4);
    dummy.jetPUID_  = reader.jetpileupIDFlagCutBased_puppi4 ;
    dummy.btag_     = reader.jetBTagAlgo_puppi4 ;
    jetVector.push_back(dummy);
  }

  if(reader.jetpt_puppi5 > 0){
    dummy.jet4V_.SetPtEtaPhiM(reader.jetpt_puppi5,reader.jeteta_puppi5,reader.jetphi_puppi5,reader.jetmass_puppi5);
    dummy.jetPUID_  = reader.jetpileupIDFlagCutBased_puppi5 ;
    dummy.btag_     = reader.jetBTagAlgo_puppi5 ;
    jetVector.push_back(dummy);
  }

  if(reader.jetpt_puppi6 > 0){
    dummy.jet4V_.SetPtEtaPhiM(reader.jetpt_puppi6,reader.jeteta_puppi6,reader.jetphi_puppi6,reader.jetmass_puppi6);
    dummy.jetPUID_  = reader.jetpileupIDFlagCutBased_puppi6 ;
    dummy.btag_     = reader.jetBTagAlgo_puppi6 ;
    jetVector.push_back(dummy);
  }

  if(reader.jetpt_puppi7 > 0){
    dummy.jet4V_.SetPtEtaPhiM(reader.jetpt_puppi7,reader.jeteta_puppi7,reader.jetphi_puppi7,reader.jetmass_puppi7);
    dummy.jetPUID_  = reader.jetpileupIDFlagCutBased_puppi7 ;
    dummy.btag_     = reader.jetBTagAlgo_puppi7 ;
    jetVector.push_back(dummy);
  }

  if(reader.jetpt_puppi8 > 0){
    dummy.jet4V_.SetPtEtaPhiM(reader.jetpt_puppi8,reader.jeteta_puppi8,reader.jetphi_puppi8,reader.jetmass_puppi8);
    dummy.jetPUID_  = reader.jetpileupIDFlagCutBased_puppi8 ;
    dummy.btag_     = reader.jetBTagAlgo_puppi8 ;
    jetVector.push_back(dummy);
  }
    
  return ;
}

void fillGenJetArray (vector<jetContainer> & jetVector, readTree & reader) {

  jetContainer dummy;
  if(reader.jetGenpt1 > 0){
    dummy.jet4V_.SetPtEtaPhiM(reader.jetGenpt1,reader.jetGeneta1,reader.jetGenphi1,reader.jetGenm1);
    dummy.jetPUID_  = -999 ;
    dummy.btag_     = -999 ;
    jetVector.push_back(dummy);
  }

  if(reader.jetGenpt2 > 0){
    dummy.jet4V_.SetPtEtaPhiM(reader.jetGenpt2,reader.jetGeneta2,reader.jetGenphi2,reader.jetGenm2);
    dummy.jetPUID_  = -999 ;
    dummy.btag_     = -999 ;
    jetVector.push_back(dummy);
  }

  if(reader.jetGenpt3 > 0){
    dummy.jet4V_.SetPtEtaPhiM(reader.jetGenpt3,reader.jetGeneta3,reader.jetGenphi3,reader.jetGenm3);
    dummy.jetPUID_  = -999 ;
    dummy.btag_     = -999 ;
    jetVector.push_back(dummy);
  }

  if(reader.jetGenpt4 > 0){
    dummy.jet4V_.SetPtEtaPhiM(reader.jetGenpt4,reader.jetGeneta4,reader.jetGenphi4,reader.jetGenm4);
    dummy.jetPUID_  = -999 ;
    dummy.btag_     = -999 ;
    jetVector.push_back(dummy);
  }

  return ;
}

// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- -


void fillTrackJetArray (vector<jetContainer> & jetVector, readTree & reader){
  for( int iJet = 0; iJet < reader.TrackJet_V4_ ; iJet++){    
    jetContainer dummy;
    dummy.jet4V_.SetPxPyPzE(reader.TrackJet_V4_fP_fX[iJet],reader.TrackJet_V4_fP_fY[iJet],reader.TrackJet_V4_fP_fZ[iJet],reader.TrackJet_V4_fE[iJet]);
    dummy.btag_    = -999 ;
    dummy.jetPUID_ = -999;     
    jetVector.push_back(dummy);
    
  }
  return ;
}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- -


// isolation applied here
void fillRecoLeptonsArray (vector<leptonContainer> & lepVector, readTree & reader){

  leptonContainer dummy;

  if(reader.pt1 > 0 ){
    dummy.lepton4V_.SetPtEtaPhiM(reader.pt1,reader.eta1,reader.phi1,0);    
    dummy.charge_   = reader.ch1 ;
    dummy.iso_      = reader.isoRhoCorr1 ;
    dummy.flavour_ = reader.pid1;
    lepVector.push_back(dummy);
  }

  if(reader.pt2 > 0){
    dummy.lepton4V_.SetPtEtaPhiM(reader.pt2,reader.eta2,reader.phi2,0);
    dummy.charge_   = reader.ch2 ;
    dummy.iso_      = reader.isoRhoCorr2 ;
    dummy.flavour_ = reader.pid2;
    lepVector.push_back(dummy);
  }
   
  if(reader.pt3 > 0){
    dummy.lepton4V_.SetPtEtaPhiM(reader.pt3,reader.eta3,reader.phi3,0);
    dummy.charge_   = reader.ch3 ;
    dummy.iso_      = reader.isoRhoCorr3 ;
    dummy.flavour_ = reader.pid3;
    lepVector.push_back(dummy);
  }

  if(reader.pt4 > 0){
    dummy.lepton4V_.SetPtEtaPhiM(reader.pt4,reader.eta4,reader.phi4,0);
    dummy.charge_   = reader.ch4 ;
    dummy.iso_      = reader.isoRhoCorr4 ;
    dummy.flavour_ = reader.pid4;
    lepVector.push_back(dummy);
  }

  return ;
}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- -


vector<leptonContainer>  dumpLeptons (vector<leptonContainer> & TL_leptons, 
                                      float isocut, float minptcut){
  vector<leptonContainer>  goodLeptons ;
  for (size_t i = 0 ; i < TL_leptons.size() ; ++i){
    if (TL_leptons.at(i).iso_  > isocut) continue ;
    if (TL_leptons.at(i).lepton4V_.Pt() < minptcut) continue ;
    goodLeptons.push_back (TL_leptons.at(i)) ;
  }
  return goodLeptons;
}

vector<leptonContainer>  dumpLeptons (vector<leptonContainer> & TL_leptons, 
                                      float isocut_mu, float isocut_el, float minptcut){
  vector<leptonContainer>  goodLeptons ;
  for (size_t i = 0 ; i < TL_leptons.size() ; ++i){
    if (TL_leptons.at(i).lepton4V_.Pt() < minptcut) continue ;
    if (TL_leptons.at(i).iso_  > isocut_mu and fabs(TL_leptons.at(i).flavour_) == 13) continue ;
    if (TL_leptons.at(i).iso_  > isocut_el and fabs(TL_leptons.at(i).flavour_) == 11) continue ;
    goodLeptons.push_back (TL_leptons.at(i)) ;
  }
  return goodLeptons;
}



// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- -


vector<jetContainer> dumpJets (vector<jetContainer> & TL_jets, vector<leptonContainer> & TL_leptons, 
                               float minptcut, float btagcut, float jetPUIDCut, float lepminptcut, float deltaR){

  vector<jetContainer> goodJets ;
  for (size_t iJet = 0 ; iJet < TL_jets.size() ; ++iJet){
    if (TL_jets.at(iJet).jet4V_.Pt() < minptcut)   continue ;
    if (TL_jets.at(iJet).btag_       > btagcut)    continue ;
    if (TL_jets.at(iJet).jetPUID_    < jetPUIDCut) continue ;
    
    bool discard = false ;
    for (unsigned int iLep = 0 ; iLep < TL_leptons.size () ; ++iLep){
      if (TL_leptons.at(iLep).lepton4V_.Pt () < lepminptcut) continue ;
      if (TL_leptons.at(iLep).lepton4V_.DeltaR(TL_jets.at(iJet).jet4V_) < deltaR){
	discard = true ;
	break ;
      }
    }
    if (discard) continue ;
    goodJets.push_back(TL_jets.at(iJet));;        
  }
  return goodJets ;
}
               

               
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- -


vector<jetContainer> dumpTrackJets (vector<jetContainer> & TL_jets, vector<leptonContainer> & TL_leptons, 
                    float minptcut, float lepminptcut, float deltaR){

  vector<jetContainer> goodJets ; 
  for (size_t iJet = 0 ; iJet < TL_jets.size() ; ++iJet){
    if (TL_jets.at(iJet).jet4V_.Pt() < minptcut) continue ;
    bool discard = false ;
    for (unsigned int iLep = 0 ; iLep < TL_leptons.size () ; ++iLep){
      if (TL_leptons.at(iLep).lepton4V_.Pt() < lepminptcut) continue ;
       if (TL_leptons.at(iLep).lepton4V_.DeltaR(TL_jets.at(iJet).jet4V_) < deltaR) {
	 discard = true ;
       	 break ;
       }    
    }
    if (discard) continue ;    
    goodJets.push_back (TL_jets.at(iJet)) ;        
  }
  return goodJets;
}


//----------------------
void fillHistos (plotter & analysisPlots, 
                 readTree* reader, 
                 vector<cutContainer> & CutList,
                 vector<variableContainer> & VariableList,
                 const string & sampleName,     const bool & usePuppiAsDefault, 
                 const double & minPtLeptonCut, const double & minPtLeptonCutCleaning,
                 const double & leptonIsoCut_mu,const double & leptonIsoCut_el, const double & leptonIsoLooseCut,
                 const double & matchingCone,   const double & minJetCutPt,   
                 map <string,TH1F*> & vect,
                 const string & finalStateString) {

  cout << "reading sample " << sampleName << "\n" ;
  int maxevents = reader->fChain->GetEntries() ;

  // loop over events                                                                                                                                                       
  for (int iEvent = 0 ; iEvent < maxevents ; ++iEvent){                                                                                                                      

    reader->fChain->GetEntry(iEvent) ;                                                                                                                                      
           
    if (iEvent % 100000 == 0) cout << "reading event " << iEvent << "\n" ;                                                                                                  

    // filter LHE level leptons for madgraph polarized events
    if(TString(sampleName).Contains("Madgraph")){
      if(finalStateString == "UU"){
	if(fabs(reader->leptonLHEpid1) != 13 or fabs(reader->leptonLHEpid2) != 13)
	  continue;
      }
      else if(finalStateString == "EE"){
	if(fabs(reader->leptonLHEpid1) != 11 or fabs(reader->leptonLHEpid2) != 11) continue;
      }
      else if(finalStateString == "DF"){
	if(fabs(reader->leptonLHEpid1) == fabs(reader->leptonLHEpid2)) continue ;
      }

      // if an event pass the cut, fill the associated map                                                                                                                 
      TLorentzVector L_lepton1, L_lepton2, L_parton1, L_parton2 ;

      L_lepton1.SetPtEtaPhiM(reader->leptonLHEpt1,reader->leptonLHEeta1,reader->leptonLHEphi1,reader->leptonLHEm1);
      L_lepton2.SetPtEtaPhiM(reader->leptonLHEpt2,reader->leptonLHEeta2,reader->leptonLHEphi2,reader->leptonLHEm2);
      
      L_parton1.SetPtEtaPhiM(reader->jetLHEPartonpt1,reader->jetLHEPartoneta1,reader->jetLHEPartonphi1,0.);
      L_parton2.SetPtEtaPhiM(reader->jetLHEPartonpt2,reader->jetLHEPartoneta2,reader->jetLHEPartonphi2,0.);

      if(L_lepton1.Pt() < minPtLeptonCut or L_lepton2.Pt() < minPtLeptonCut) continue;
    }


    for(size_t iCut = 0; iCut < CutList.size() ; iCut++){ 
      
      if(!passCutContainerSelection(reader,
				    CutList.at(iCut),
				    sampleName,
				    usePuppiAsDefault,
				    minPtLeptonCut,
				    minPtLeptonCutCleaning,
				    leptonIsoCut_mu,
				    leptonIsoCut_el,
				    leptonIsoLooseCut,
				    matchingCone,
				    minJetCutPt,
				    vect)) continue;

      // some basic lorentz vectors
      TLorentzVector L_dilepton, L_met, L_gen_met, L_LLmet;
      TLorentzVector L_dijet, L_dijet_gen;

 
      // dump all the lepton in the event                                                                                                                                       
      vector<leptonContainer> LeptonsAll;
      fillRecoLeptonsArray (LeptonsAll, *reader);

      // dump tight leptons                                                                                                                                                     
      vector<leptonContainer> leptonsIsoTight ;
      leptonsIsoTight = dumpLeptons (LeptonsAll, leptonIsoCut_mu, leptonIsoCut_el, minPtLeptonCut);

      L_dilepton = leptonsIsoTight.at(0).lepton4V_ + leptonsIsoTight.at(1).lepton4V_ ;               

      if(not usePuppiAsDefault){
	L_met.SetPtEtaPhiM       (reader->pfmet,0.,reader->pfmetphi, 0.) ;                                                                                                      
      }
      else{
	L_met.SetPtEtaPhiM (reader->pfmet_puppi,0.,reader->pfmetphi_puppi, 0.) ;                                                                                        
      }

      L_LLmet = L_dilepton + L_met ;

      L_gen_met.SetPtEtaPhiM   (reader->metGenpt,0.,reader->metGenphi, 0.) ;                                                                                                   
                                                                                                                                                                           
      float asimJ = 0, asimL = 0, Rvar = 0, asimGenJ = 0, RvarGen = 0;
      float aveEta = 0, aveEtaGen = 0;


      // take reco jets                                                                                                                                                         
      vector<jetContainer> RecoJetsAll ;
      if(not usePuppiAsDefault){
	fillRecoJetArray (RecoJetsAll, *reader) ;
      }
      else{
	fillPuppiJetArray (RecoJetsAll, *reader) ;
      }

      // take gen jets                                                                                                                                                          
      vector<jetContainer> GenJetsAll ;
      fillGenJetArray (GenJetsAll, *reader) ;

      // take jets                                                                                                                                                          
      vector<jetContainer> RecoJets;
      RecoJets  = dumpJets (RecoJetsAll, leptonsIsoTight, minJetCutPt, CutList.at(iCut).bTagVeto, CutList.at(iCut).jetPUID, minPtLeptonCutCleaning, matchingCone);

      // take gen jets                                                                                                                                                         
      vector<jetContainer> GenJets;
      GenJets  = dumpJets (GenJetsAll, leptonsIsoTight, minJetCutPt, -999, -999, minPtLeptonCutCleaning, matchingCone);


      asimL = (leptonsIsoTight.at(0).lepton4V_.Pt()-leptonsIsoTight.at(1).lepton4V_.Pt())/(leptonsIsoTight.at(0).lepton4V_.Pt()+leptonsIsoTight.at(1).lepton4V_.Pt()) ;      

      if(RecoJets.size() >= 2){
	L_dijet  = RecoJets.at(0).jet4V_ + RecoJets.at(1).jet4V_;                                                                                                    
	asimJ    = (RecoJets.at(0).jet4V_.Pt()-RecoJets.at(1).jet4V_.Pt())/(RecoJets.at(0).jet4V_.Pt()+RecoJets.at(1).jet4V_.Pt()) ;                                        
	Rvar     = (leptonsIsoTight.at(0).lepton4V_.Pt()*leptonsIsoTight.at(1).lepton4V_.Pt())/(RecoJets.at(0).jet4V_.Pt()*RecoJets.at(1).jet4V_.Pt()) ;                  
        aveEta   = 0.5*(RecoJets.at(0).jet4V_.Eta()+RecoJets.at(1).jet4V_.Eta());
      }
    
      if(GenJets.size() >= 2){
	L_dijet_gen   = GenJets.at(0).jet4V_ + GenJets.at(1).jet4V_;                                                                                              
	asimGenJ      = (GenJets.at(0).jet4V_.Pt()-GenJets.at(1).jet4V_.Pt())/(GenJets.at(0).jet4V_.Pt()+GenJets.at(1).jet4V_.Pt()) ;                             
	RvarGen       = (leptonsIsoTight.at(0).lepton4V_.Pt()*leptonsIsoTight.at(1).lepton4V_.Pt())/(GenJets.at(0).jet4V_.Pt()*GenJets.at(1).jet4V_.Pt()) ;                     
        aveEtaGen     = 0.5*(GenJets.at(0).jet4V_.Eta()+GenJets.at(1).jet4V_.Eta());
      }
      
      // track jet info
      float TKJ_SumHT = 0.,TKJ_SumHT_IN = 0., TKJ_SumHT_OUT = 0. ;
      int   TKJ_num   = 0, TKJ_num_IN   = 0,  TKJ_num_OUT  = 0 ;

      if(RecoJets.size() >=2){

	float dRThreshold = 0.5 ;

	vector<jetContainer> trackJetsAll;
	fillTrackJetArray (trackJetsAll,*reader) ;
	vector<jetContainer> trackJets ;
	trackJets = dumpTrackJets (trackJetsAll, leptonsIsoTight, 1., minPtLeptonCutCleaning, dRThreshold);

	float TJ_etaMin = RecoJets.at (0).jet4V_.Eta () ;
	float TJ_etaMax = RecoJets.at (1).jet4V_.Eta () ;
	float TJ_phiMin = RecoJets.at (0).jet4V_.Phi () ;
	float TJ_phiMax = RecoJets.at (1).jet4V_.Phi () ;
	if (TJ_etaMin > TJ_etaMax){
          swap (TJ_etaMin, TJ_etaMax) ;
          swap (TJ_phiMin, TJ_phiMax) ;
        }

	// loop over track jets                                                                                                                                                
	for (size_t iJet = 0 ; iJet < trackJets.size () ; ++iJet){

          float iJetPhi = trackJets.at (iJet).jet4V_.Phi () ;
          float iJetEta = trackJets.at (iJet).jet4V_.Eta () ;
          float iJetPt  = trackJets.at (iJet).jet4V_.Pt () ;

          float dR2_Min = deltaPhi(TJ_phiMin, iJetPhi);
          dR2_Min *= dR2_Min ;
          dR2_Min += (iJetEta - TJ_etaMin) * (iJetEta - TJ_etaMin) ;
          float dR2_Max = deltaPhi (TJ_phiMax, iJetPhi) ;
          dR2_Max *= dR2_Max ;
          dR2_Max += (iJetEta - TJ_etaMax) * (iJetEta - TJ_etaMax) ;

          // veto the tag jets                                                                                                                                                  
          if (sqrt(dR2_Max) < dRThreshold || sqrt(dR2_Min) < dRThreshold) continue ;

          float iJetModPhi = iJetPhi ;
          float iJetZep    = (trackJets.at (iJet).jet4V_.Eta () - aveEta) /(TJ_etaMax - TJ_etaMin);
          if (iJetZep < -0.5)     iJetModPhi -= TJ_phiMin ;
          else if (iJetZep > 0.5) iJetModPhi -= TJ_phiMax ;

	  ++TKJ_num ;
          TKJ_SumHT += iJetPt ;

          if (iJetEta > TJ_etaMin && iJetEta < TJ_etaMax){
	      ++TKJ_num_IN ;
	      TKJ_SumHT_IN += iJetPt ;
	  }

	  else if (iJetEta < TJ_etaMin || iJetEta > TJ_etaMax){
	      ++TKJ_num_OUT ;
	      TKJ_SumHT_OUT += iJetPt ;
	  }
	}
	
      }

      TString Name ;
      string  NameSample ; 
      if(TString(sampleName).Contains("Madgraph_")){
        Name = sampleName;
        Name.ReplaceAll("Madgraph_","");
	NameSample = string(Name) ;
      }
      else 
	NameSample = sampleName ;

      
      for(size_t iVar = 0; iVar < VariableList.size(); iVar++){

        // track jets
        if(VariableList.at(iVar).variableName == "numTkjets" and RecoJets.size() >=2){ 
	  analysisPlots.fillHisto (NameSample, CutList.at(iCut).cutLayerName, VariableList.at(iVar).variableName,  TKJ_num,                1.) ;
	}
        else if(VariableList.at(iVar).variableName == "numTkjets_In"  and RecoJets.size() >=2){ 
	  analysisPlots.fillHisto (NameSample, CutList.at(iCut).cutLayerName, VariableList.at(iVar).variableName,  TKJ_num_IN,             1.) ;
	}
        else if(VariableList.at(iVar).variableName == "numTkjets_Out" and RecoJets.size() >=2){ 
	  analysisPlots.fillHisto (NameSample, CutList.at(iCut).cutLayerName, VariableList.at(iVar).variableName,  TKJ_num_OUT,            1.) ;
	}
        else if(VariableList.at(iVar).variableName == "HTtkjets"      and RecoJets.size() >=2){ 
	  analysisPlots.fillHisto (NameSample, CutList.at(iCut).cutLayerName, VariableList.at(iVar).variableName,  TKJ_SumHT,              1.) ;
	}
        else if(VariableList.at(iVar).variableName == "HTtkjets_In"   and RecoJets.size() >=2){ 
	  analysisPlots.fillHisto (NameSample, CutList.at(iCut).cutLayerName, VariableList.at(iVar).variableName,  TKJ_SumHT_IN,           1.) ;
	}
        else if(VariableList.at(iVar).variableName == "HTtkjets_Out"  and RecoJets.size() >=2){ 
	  analysisPlots.fillHisto (NameSample, CutList.at(iCut).cutLayerName, VariableList.at(iVar).variableName,  TKJ_SumHT_OUT,          1.) ;
	}

        // jet based variables
	if(VariableList.at(iVar).variableName == "ptj1" and RecoJets.size() >= 1){
 	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,RecoJets.at(0).jet4V_.Pt(),1);   
	}
	else if(VariableList.at(iVar).variableName == "ptj1_gen" and GenJets.size() >= 1){
 	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,GenJets.at(0).jet4V_.Pt(),1);   
	}

	else if(VariableList.at(iVar).variableName == "ptj2" and RecoJets.size() >= 2){
 	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,RecoJets.at(1).jet4V_.Pt(),1);   
	}
	else if(VariableList.at(iVar).variableName == "ptj2_gen" and GenJets.size() >= 2){
 	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,GenJets.at(1).jet4V_.Pt(),1);   
	}


	else if(VariableList.at(iVar).variableName == "etaj1" and RecoJets.size() >= 1){
 	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,RecoJets.at(0).jet4V_.Eta(),1);   
	}
	else if(VariableList.at(iVar).variableName == "etaj1_gen" and GenJets.size() >= 1){
 	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,GenJets.at(0).jet4V_.Eta(),1);   
	}
	else if(VariableList.at(iVar).variableName == "etaj2" and RecoJets.size() >= 2){
 	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,RecoJets.at(1).jet4V_.Eta(),1);   
	}
	else if(VariableList.at(iVar).variableName == "etaj2_gen" and GenJets.size() >= 2){
 	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,GenJets.at(1).jet4V_.Eta(),1);   
	}


	else if(VariableList.at(iVar).variableName == "detajj" and RecoJets.size() >= 2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(RecoJets.at(0).jet4V_.Eta()-RecoJets.at(1).jet4V_.Eta()),1);   
	}
	else if(VariableList.at(iVar).variableName == "detajj_gen" and GenJets.size() >= 2){
	 analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(GenJets.at(0).jet4V_.Eta()-GenJets.at(1).jet4V_.Eta()),1);   
	}       

	else if(VariableList.at(iVar).variableName == "dRjj" and RecoJets.size() >= 2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,RecoJets.at(0).jet4V_.DeltaR(RecoJets.at(1).jet4V_),1);   
	}
	else if(VariableList.at(iVar).variableName == "dRjj_gen" and GenJets.size() >= 2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,GenJets.at(0).jet4V_.DeltaR(GenJets.at(1).jet4V_),1);   
	}       

	else if(VariableList.at(iVar).variableName == "mjj" and RecoJets.size() >= 2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,L_dijet.M(),1);   
	}
	else if(VariableList.at(iVar).variableName == "mjj_gen" and GenJets.size() >= 2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,L_dijet_gen.M(),1);   
	}

	else if(VariableList.at(iVar).variableName == "ptjj" and RecoJets.size() >= 2){
 	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,L_dijet.Pt(),1);   
	}
	else if(VariableList.at(iVar).variableName == "ptjj_gen" and GenJets.size() >= 2){
 	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,L_dijet_gen.Pt(),1);   
	}

	else if(VariableList.at(iVar).variableName == "Asim_j" and RecoJets.size() >=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,asimJ,1);   
	}
	else if(VariableList.at(iVar).variableName == "Asim_j_gen" and GenJets.size() >=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,asimGenJ,1);   
	}

	else if(VariableList.at(iVar).variableName == "DeltaPhi_JJ"       and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(RecoJets.at(0).jet4V_.DeltaPhi(RecoJets.at(1).jet4V_)),1);   
	} 
	else if(VariableList.at(iVar).variableName == "DeltaPhi_JJ_gen"   and GenJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(GenJets.at(0).jet4V_.DeltaPhi(GenJets.at(1).jet4V_)),1);   
	}        

	else if(VariableList.at(iVar).variableName == "etaj1etaj2"       and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,RecoJets.at(0).jet4V_.Eta()*RecoJets.at(1).jet4V_.Eta(),1);   
	} 
	else if(VariableList.at(iVar).variableName == "etaj1etaj2_gen"       and GenJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,GenJets.at(0).jet4V_.Eta()*GenJets.at(1).jet4V_.Eta(),1);   
	} 

        // lepton based quantities

	else if(VariableList.at(iVar).variableName == "ptl1"){
 	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,leptonsIsoTight.at(0).lepton4V_.Pt(),1);   
	}
	else if(VariableList.at(iVar).variableName == "ptl2"){
 	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,leptonsIsoTight.at(1).lepton4V_.Pt(),1);   
	}

	else if(VariableList.at(iVar).variableName == "etal1"){
 	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,leptonsIsoTight.at(0).lepton4V_.Eta(),1);   
	}
	else if(VariableList.at(iVar).variableName == "etal2"){
 	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,leptonsIsoTight.at(1).lepton4V_.Eta(),1);   
	}

	else if(VariableList.at(iVar).variableName == "ptll"){
 	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,L_dilepton.Pt(),1);   
	}
	else if(VariableList.at(iVar).variableName == "phill"){
 	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,L_dilepton.Phi(),1);   
	}
	else if(VariableList.at(iVar).variableName == "dRll"){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,leptonsIsoTight.at(0).lepton4V_.DeltaR(leptonsIsoTight.at(1).lepton4V_),1);   
	}
	else if(VariableList.at(iVar).variableName == "etall"){
 	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,L_dilepton.Eta(),1);   
	}
	else if(VariableList.at(iVar).variableName == "mll"){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,L_dilepton.M(),1);   
	}

	else if(VariableList.at(iVar).variableName == "etal1etal2"){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,leptonsIsoTight.at(0).lepton4V_.Eta()*leptonsIsoTight.at(1).lepton4V_.Eta(),1);   
	} 


	else if(VariableList.at(iVar).variableName == "DeltaPhi_LL"){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(leptonsIsoTight.at(0).lepton4V_.DeltaPhi(leptonsIsoTight.at(1).lepton4V_)),1);   
	}
	else if(VariableList.at(iVar).variableName == "DeltaEta_LL"){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(leptonsIsoTight.at(0).lepton4V_.Eta()-leptonsIsoTight.at(1).lepton4V_.Eta()),1);   
	} 

	else if(VariableList.at(iVar).variableName == "Asim_l"){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,asimL,1);   
	}

        // met
	else if(VariableList.at(iVar).variableName == "met"){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,L_met.Pt(),1);   
	}
	else if(VariableList.at(iVar).variableName == "met_gen"){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,L_gen_met.Pt(),1);   
	}


        /// mixed variables using all event objects

	else if(VariableList.at(iVar).variableName == "leadLepZep" and RecoJets.size() >= 2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,(leptonsIsoTight.at(0).lepton4V_.Eta()-aveEta)/(fabs(RecoJets.at(0).jet4V_.Eta()-RecoJets.at(1).jet4V_.Eta())),1);   
	}
	else if(VariableList.at(iVar).variableName == "leadLepZep_gen" and RecoJets.size() >= 2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,(leptonsIsoTight.at(0).lepton4V_.Eta()-aveEtaGen)/(fabs(GenJets.at(0).jet4V_.Eta()-GenJets.at(1).jet4V_.Eta())),1);   
	}
	else if(VariableList.at(iVar).variableName == "trailLepZep" and RecoJets.size() >= 2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,(leptonsIsoTight.at(1).lepton4V_.Eta()-aveEta)/(fabs(RecoJets.at(0).jet4V_.Eta()-RecoJets.at(1).jet4V_.Eta())),1);   
	}
	else if(VariableList.at(iVar).variableName == "trailLepZep_gen" and RecoJets.size() >= 2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,(leptonsIsoTight.at(1).lepton4V_.Eta()-aveEtaGen)/(fabs(GenJets.at(0).jet4V_.Eta()-GenJets.at(1).jet4V_.Eta())),1);   
	}

       
	else if(VariableList.at(iVar).variableName == "R"){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,Rvar,1);   
	}
	else if(VariableList.at(iVar).variableName == "R_gen"){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,RvarGen,1);   
	}
      
        // lepton and met
	else if(VariableList.at(iVar).variableName == "DeltaPhi_LMet"){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(leptonsIsoTight.at(0).lepton4V_.DeltaPhi(L_met)),1);   
	} 
	else if(VariableList.at(iVar).variableName == "DeltaPhi_LMet_gen"){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(leptonsIsoTight.at(0).lepton4V_.DeltaPhi(L_gen_met)),1);   
	} 	

	else if(VariableList.at(iVar).variableName == "ptLMet"){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,(leptonsIsoTight.at(0).lepton4V_+L_met).Pt(),1);   
	}         

	else if(VariableList.at(iVar).variableName == "DeltaPhi_TLMet"){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(leptonsIsoTight.at(1).lepton4V_.DeltaPhi(L_met)),1);   
	} 
	else if(VariableList.at(iVar).variableName == "DeltaPhi_TLMet_gen"){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(leptonsIsoTight.at(1).lepton4V_.DeltaPhi(L_gen_met)),1);   
	} 

	else if(VariableList.at(iVar).variableName == "ptTLMet"){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,(leptonsIsoTight.at(1).lepton4V_+L_met).Pt(),1);   
	} 

	else if(VariableList.at(iVar).variableName == "DeltaPhi_LLMet"){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(L_dilepton.DeltaPhi(L_met)),1);   
	} 
	else if(VariableList.at(iVar).variableName == "DeltaPhi_LLMet_gen"){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(L_dilepton.DeltaPhi(L_gen_met)),1);   
	} 

	else if(VariableList.at(iVar).variableName == "ptLLMet"){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,(L_dilepton+L_met).Pt(),1);   
	} 

	
        // lepton and jets
	else if(VariableList.at(iVar).variableName == "DeltaPhi_LJL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(RecoJets.at(0).jet4V_.DeltaPhi(leptonsIsoTight.at(0).lepton4V_)),1);   
	} 
	else if(VariableList.at(iVar).variableName == "DeltaPhi_LJTL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(RecoJets.at(0).jet4V_.DeltaPhi(leptonsIsoTight.at(1).lepton4V_)),1);   
	} 
	else if(VariableList.at(iVar).variableName == "DeltaPhi_LJLL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(RecoJets.at(0).jet4V_.DeltaPhi(L_dilepton)),1);   
	} 


	else if(VariableList.at(iVar).variableName == "dR_LJL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,RecoJets.at(0).jet4V_.DeltaR(leptonsIsoTight.at(0).lepton4V_),1);   
	} 
	else if(VariableList.at(iVar).variableName == "dR_LJTL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,RecoJets.at(0).jet4V_.DeltaR(leptonsIsoTight.at(1).lepton4V_),1);   
	} 
	else if(VariableList.at(iVar).variableName == "dR_LJLL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,RecoJets.at(0).jet4V_.DeltaR(L_dilepton),1);   
	} 
      
	else if(VariableList.at(iVar).variableName == "ptLJL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,(RecoJets.at(0).jet4V_+leptonsIsoTight.at(0).lepton4V_).Pt(),1); 
	} 
	else if(VariableList.at(iVar).variableName == "ptLJTL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,(RecoJets.at(0).jet4V_+leptonsIsoTight.at(1).lepton4V_).Pt(),1);
	} 
	else if(VariableList.at(iVar).variableName == "ptLJLL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,(RecoJets.at(0).jet4V_+L_dilepton).Pt(),1);   
	} 

      
	else if(VariableList.at(iVar).variableName == "DeltaPhi_TJL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(RecoJets.at(1).jet4V_.DeltaPhi(leptonsIsoTight.at(0).lepton4V_)),1);   
	} 
	else if(VariableList.at(iVar).variableName == "DeltaPhi_TJTL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(RecoJets.at(1).jet4V_.DeltaPhi(leptonsIsoTight.at(1).lepton4V_)),1);   
	} 
	else if(VariableList.at(iVar).variableName == "DeltaPhi_TJLL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(RecoJets.at(1).jet4V_.DeltaPhi(L_dilepton)),1);   
	} 


	else if(VariableList.at(iVar).variableName == "dR_TJL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,RecoJets.at(1).jet4V_.DeltaR(leptonsIsoTight.at(0).lepton4V_),1);   
	} 
	else if(VariableList.at(iVar).variableName == "dR_TJTL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,RecoJets.at(1).jet4V_.DeltaR(leptonsIsoTight.at(1).lepton4V_),1);   
	} 
	else if(VariableList.at(iVar).variableName == "dR_TJLL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,RecoJets.at(1).jet4V_.DeltaR(L_dilepton),1);   
	} 


	else if(VariableList.at(iVar).variableName == "ptTJL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,(RecoJets.at(1).jet4V_+leptonsIsoTight.at(0).lepton4V_).Pt(),1); 
	} 
	else if(VariableList.at(iVar).variableName == "ptTJTL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,(RecoJets.at(1).jet4V_+leptonsIsoTight.at(1).lepton4V_).Pt(),1);
	} 
	else if(VariableList.at(iVar).variableName == "ptTJLL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,(RecoJets.at(1).jet4V_+L_dilepton).Pt(),1);   
	} 

	else if(VariableList.at(iVar).variableName == "DeltaPhi_JJL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(L_dijet.DeltaPhi(leptonsIsoTight.at(0).lepton4V_)),1);   
	} 
	else if(VariableList.at(iVar).variableName == "DeltaPhi_JJTL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(L_dijet.DeltaPhi(leptonsIsoTight.at(1).lepton4V_)),1);   
	} 
	else if(VariableList.at(iVar).variableName == "DeltaPhi_JJLL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(L_dijet.DeltaPhi(L_dilepton)),1);   
	} 

	else if(VariableList.at(iVar).variableName == "dR_JJL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,L_dijet.DeltaR(leptonsIsoTight.at(0).lepton4V_),1);   
	} 
	else if(VariableList.at(iVar).variableName == "dR_JJTL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,L_dijet.DeltaR(leptonsIsoTight.at(1).lepton4V_),1);   
	} 
	else if(VariableList.at(iVar).variableName == "dR_JJLL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,L_dijet.DeltaR(L_dilepton),1);   
	} 


	else if(VariableList.at(iVar).variableName == "ptJJL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,(L_dijet+leptonsIsoTight.at(0).lepton4V_).Pt(),1); 
	} 
	else if(VariableList.at(iVar).variableName == "ptJJTL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,(L_dijet+leptonsIsoTight.at(1).lepton4V_).Pt(),1);
	} 
	else if(VariableList.at(iVar).variableName == "ptJJLL" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,(L_dijet+L_dilepton).Pt(),1);   
	} 


        // jet and met
	else if(VariableList.at(iVar).variableName == "DeltaPhi_JJMet" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(L_dijet.DeltaPhi(L_met)),1);   
	} 
	else if(VariableList.at(iVar).variableName == "DeltaPhi_JJMet_gen" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(L_dijet.DeltaPhi(L_gen_met)),1);   
	} 

	else if(VariableList.at(iVar).variableName == "ptJJMet" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,(L_dijet+L_met).Pt(),1);   
	} 

	else if(VariableList.at(iVar).variableName == "DeltaPhi_JJ_gen_Met" and GenJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(L_dijet_gen.DeltaPhi(L_met)),1);   
	} 
	else if(VariableList.at(iVar).variableName == "DeltaPhi_JJ_gen_Met_gen" and GenJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(L_dijet_gen.DeltaPhi(L_gen_met)),1);   
	} 

	else if(VariableList.at(iVar).variableName == "DeltaPhi_LJMet" and RecoJets.size()>=1){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(RecoJets.at(0).jet4V_.DeltaPhi(L_met)),1);   
	} 
	else if(VariableList.at(iVar).variableName == "DeltaPhi_LJMet_gen" and RecoJets.size()>=1){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(RecoJets.at(0).jet4V_.DeltaPhi(L_gen_met)),1);   
	} 

	else if(VariableList.at(iVar).variableName == "ptLJMet" and RecoJets.size()>=1){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,(RecoJets.at(0).jet4V_+L_met).Pt(),1);   
	} 

	else if(VariableList.at(iVar).variableName == "DeltaPhi_LJ_gen_Met" and GenJets.size()>=1){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(GenJets.at(0).jet4V_.DeltaPhi(L_met)),1);   
	} 
	else if(VariableList.at(iVar).variableName == "DeltaPhi_LJ_gen_Met_gen" and GenJets.size()>=1){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(GenJets.at(0).jet4V_.DeltaPhi(L_gen_met)),1);   
	} 

	else if(VariableList.at(iVar).variableName == "DeltaPhi_TJMet" and RecoJets.size() >=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(RecoJets.at(1).jet4V_.DeltaPhi(L_met)),1);   
	} 
	else if(VariableList.at(iVar).variableName == "DeltaPhi_TJMet_gen" and RecoJets.size() >=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(RecoJets.at(1).jet4V_.DeltaPhi(L_gen_met)),1);   
	} 

	else if(VariableList.at(iVar).variableName == "ptTJMet" and RecoJets.size()>=1){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,(RecoJets.at(1).jet4V_+L_met).Pt(),1);   
	} 


        // Lepton JJ_LLMET
	else if(VariableList.at(iVar).variableName == "ptJJ_LLMet" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,(L_dijet+L_LLmet).Pt(),1);   
	}
	else if(VariableList.at(iVar).variableName == "DeltaPhi_JJ_LLMet" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,fabs(L_dijet.DeltaPhi(L_LLmet)),1);   
	}
	else if(VariableList.at(iVar).variableName == "dR_JJ_LLMet" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,L_dijet.DeltaR(L_LLmet),1);   
	}

        // some invariant mass
        else if(VariableList.at(iVar).variableName == "mlljj" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,(L_dilepton+L_dijet).M(),1);
	}

        else if(VariableList.at(iVar).variableName == "mlljjmet" and RecoJets.size()>=2){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,(L_dilepton+L_dijet+L_met).M(),1);
	}

        // tranvserse mass
	else if(VariableList.at(iVar).variableName == "mTH"){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,sqrt(2*L_dilepton.Pt()*L_met.Pt()*(1-TMath::Cos(L_dilepton.DeltaPhi(L_met)))),1);   
	}
	else if(VariableList.at(iVar).variableName == "mTH_gen"){
	  analysisPlots.fillHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList.at(iVar).variableName,sqrt(2*L_dilepton.Pt()*L_gen_met.Pt()*(1-TMath::Cos(L_dilepton.DeltaPhi(L_gen_met)))),1);   
	}

      }       
    }
  }
}

// 2D histograms
void fill2DHistos (plotter & analysisPlots,
                   readTree* reader,
                   vector<cutContainer> & CutList,
                   vector<variableContainer2D> & VariableList2D,
                   const string & sampleName,
                   const bool & usePuppiAsDefault,
                   const double & minPtLeptonCut,
                   const double & minPtLeptonCutCleaning,
                   const double & leptonIsoCut_mu,
                   const double & leptonIsoCut_el,
                   const double & leptonIsoLooseCut,
                   const double & matchingCone,
                   const double & minJetCutPt,
		   const string & finalStateString){


  cout << "reading sample " << sampleName << "\n" ;
  int maxevents = reader->fChain->GetEntries() ;

  map<string,TH1F*>  vect ;

  // loop over events                                                                                                                                                       
  for (int iEvent = 0 ; iEvent < maxevents ; ++iEvent){                                                                                                                      

    reader->fChain->GetEntry(iEvent) ;                                                                                                                                      
           
    if (iEvent % 100000 == 0) cout << "reading event " << iEvent << "\n" ;                                                                                                  

    // filter LHE level leptons for madgraph polarized events
    if(TString(sampleName).Contains("Madgraph")){

      if(finalStateString == "UU"){
	if(fabs(reader->leptonLHEpid1) != 13 or fabs(reader->leptonLHEpid2) != 13)
	  continue;
      }
      else if(finalStateString == "EE"){
	if(fabs(reader->leptonLHEpid1) != 11 or fabs(reader->leptonLHEpid2) != 11) continue;
      }
      else if(finalStateString == "DF"){
	if(fabs(reader->leptonLHEpid1) == fabs(reader->leptonLHEpid2)) continue ;
      }

      // if an event pass the cut, fill the associated map                                                                                                                 
      TLorentzVector L_lepton1, L_lepton2, L_parton1, L_parton2 ;

      L_lepton1.SetPtEtaPhiM(reader->leptonLHEpt1,reader->leptonLHEeta1,reader->leptonLHEphi1,reader->leptonLHEm1);
      L_lepton2.SetPtEtaPhiM(reader->leptonLHEpt2,reader->leptonLHEeta2,reader->leptonLHEphi2,reader->leptonLHEm2);
      
      L_parton1.SetPtEtaPhiM(reader->jetLHEPartonpt1,reader->jetLHEPartoneta1,reader->jetLHEPartonphi1,0.);
      L_parton2.SetPtEtaPhiM(reader->jetLHEPartonpt2,reader->jetLHEPartoneta2,reader->jetLHEPartonphi2,0.);

      if(L_lepton1.Pt() < minPtLeptonCut or L_lepton2.Pt() < minPtLeptonCut) continue;
    }
    
    for(size_t iCut = 0; iCut < CutList.size() ; iCut++){ 

      if(!passCutContainerSelection(reader,
				    CutList.at(iCut),
				    sampleName,
				    usePuppiAsDefault,
				    minPtLeptonCut,
				    minPtLeptonCutCleaning,
				    leptonIsoCut_mu,
				    leptonIsoCut_el,
				    leptonIsoLooseCut,
				    matchingCone,
				    minJetCutPt,
				    vect)) continue;

      // some basic lorentz vectors
      TLorentzVector L_dilepton, L_met, L_gen_met, L_LLmet;
      TLorentzVector L_dijet, L_dijet_gen;

 
      // dump all the lepton in the event                                                                                                                                       
      vector<leptonContainer> LeptonsAll;
      fillRecoLeptonsArray (LeptonsAll, *reader);

      // dump tight leptons                                                                                                                                                     
      vector<leptonContainer> leptonsIsoTight ;
      leptonsIsoTight = dumpLeptons (LeptonsAll, leptonIsoCut_mu, leptonIsoCut_el, minPtLeptonCut);

      L_dilepton = leptonsIsoTight.at(0).lepton4V_ + leptonsIsoTight.at(1).lepton4V_ ;               

      if(not usePuppiAsDefault){
	L_met.SetPtEtaPhiM       (reader->pfmet,0.,reader->pfmetphi, 0.) ;                                                                                                      
      }
      else{
	L_met.SetPtEtaPhiM (reader->pfmet_puppi,0.,reader->pfmetphi_puppi, 0.) ;                                                                                        
      }

      L_LLmet = L_dilepton + L_met ;

      L_gen_met.SetPtEtaPhiM   (reader->metGenpt,0.,reader->metGenphi, 0.) ;                                                                                                   
                                                                                                                                                                           
      float asimJ = 0, asimL = 0, Rvar = 0, aveEta = 0;
      //      float asimGenJ = 0, RvarGen = 0, aveEtaGen = 0;


      // take reco jets                                                                                                                                                         
      vector<jetContainer> RecoJetsAll ;
      if(not usePuppiAsDefault){
	fillRecoJetArray (RecoJetsAll, *reader) ;
      }
      else{
	fillPuppiJetArray (RecoJetsAll, *reader) ;
      }

      // take gen jets                                                                                                                                                          
      //      vector<jetContainer> GenJetsAll ;
      //      fillGenJetArray (GenJetsAll, *reader) ;

      // take jets                                                                                                                                                          
      vector<jetContainer> RecoJets;
      RecoJets  = dumpJets (RecoJetsAll, leptonsIsoTight, minJetCutPt, CutList.at(iCut).bTagVeto, CutList.at(iCut).jetPUID, minPtLeptonCutCleaning, matchingCone);

      // take gen jets                                                                                                                                                         
      //      vector<jetContainer> GenJets;
      //      GenJets  = dumpJets (GenJetsAll, leptonsIsoTight, minJetCutPt, -999, -999, minPtLeptonCutCleaning, matchingCone);


      asimL = (leptonsIsoTight.at(0).lepton4V_.Pt()-leptonsIsoTight.at(1).lepton4V_.Pt())/(leptonsIsoTight.at(0).lepton4V_.Pt()+leptonsIsoTight.at(1).lepton4V_.Pt()) ;      

      if(RecoJets.size() >= 2){
	L_dijet  = RecoJets.at(0).jet4V_ + RecoJets.at(1).jet4V_;                                                                                                    
	asimJ    = (RecoJets.at(0).jet4V_.Pt()-RecoJets.at(1).jet4V_.Pt())/(RecoJets.at(0).jet4V_.Pt()+RecoJets.at(1).jet4V_.Pt()) ;                                        
	Rvar     = (leptonsIsoTight.at(0).lepton4V_.Pt()*leptonsIsoTight.at(1).lepton4V_.Pt())/(RecoJets.at(0).jet4V_.Pt()*RecoJets.at(1).jet4V_.Pt()) ;                  
        aveEta   = 0.5*(RecoJets.at(0).jet4V_.Eta()+RecoJets.at(1).jet4V_.Eta());
      }
    
      //      if(GenJets.size() >= 2){
      //	L_dijet_gen   = GenJets.at(0).jet4V_ + GenJets.at(1).jet4V_;                                                                                              
      //	asimGenJ      = (GenJets.at(0).jet4V_.Pt()-GenJets.at(1).jet4V_.Pt())/(GenJets.at(0).jet4V_.Pt()+GenJets.at(1).jet4V_.Pt()) ;                             
      //	RvarGen       = (leptonsIsoTight.at(0).lepton4V_.Pt()*leptonsIsoTight.at(1).lepton4V_.Pt())/(GenJets.at(0).jet4V_.Pt()*GenJets.at(1).jet4V_.Pt()) ;            
      //        aveEtaGen     = 0.5*(GenJets.at(0).jet4V_.Eta()+GenJets.at(1).jet4V_.Eta());
      //      }
      
      // track jet info
      float TKJ_SumHT = 0.,TKJ_SumHT_IN = 0., TKJ_SumHT_OUT = 0. ;
      int   TKJ_num   = 0, TKJ_num_IN   = 0,  TKJ_num_OUT  = 0 ;

      if(RecoJets.size() >=2){

	float dRThreshold = 0.5 ;

	vector<jetContainer> trackJetsAll;
	fillTrackJetArray (trackJetsAll,*reader) ;
	vector<jetContainer> trackJets ;
	trackJets = dumpTrackJets (trackJetsAll, leptonsIsoTight, 1., minPtLeptonCutCleaning, dRThreshold);

	float TJ_etaMin = RecoJets.at (0).jet4V_.Eta () ;
	float TJ_etaMax = RecoJets.at (1).jet4V_.Eta () ;
	float TJ_phiMin = RecoJets.at (0).jet4V_.Phi () ;
	float TJ_phiMax = RecoJets.at (1).jet4V_.Phi () ;
	if (TJ_etaMin > TJ_etaMax){
          swap (TJ_etaMin, TJ_etaMax) ;
          swap (TJ_phiMin, TJ_phiMax) ;
        }

	// loop over track jets                                                                                                                                                
	for (size_t iJet = 0 ; iJet < trackJets.size () ; ++iJet){

          float iJetPhi = trackJets.at (iJet).jet4V_.Phi () ;
          float iJetEta = trackJets.at (iJet).jet4V_.Eta () ;
          float iJetPt  = trackJets.at (iJet).jet4V_.Pt () ;

          float dR2_Min = deltaPhi(TJ_phiMin, iJetPhi);
          dR2_Min *= dR2_Min ;
          dR2_Min += (iJetEta - TJ_etaMin) * (iJetEta - TJ_etaMin) ;
          float dR2_Max = deltaPhi (TJ_phiMax, iJetPhi) ;
          dR2_Max *= dR2_Max ;
          dR2_Max += (iJetEta - TJ_etaMax) * (iJetEta - TJ_etaMax) ;

          // veto the tag jets                                                                                                                                                  
          if (sqrt(dR2_Max) < dRThreshold || sqrt(dR2_Min) < dRThreshold) continue ;

          float iJetModPhi = iJetPhi ;
          float iJetZep    = (trackJets.at (iJet).jet4V_.Eta () - aveEta) /(TJ_etaMax - TJ_etaMin);
          if (iJetZep < -0.5)     iJetModPhi -= TJ_phiMin ;
          else if (iJetZep > 0.5) iJetModPhi -= TJ_phiMax ;

	  ++TKJ_num ;
          TKJ_SumHT += iJetPt ;

          if (iJetEta > TJ_etaMin && iJetEta < TJ_etaMax){
	      ++TKJ_num_IN ;
	      TKJ_SumHT_IN += iJetPt ;
	  }

	  else if (iJetEta < TJ_etaMin || iJetEta > TJ_etaMax){
	      ++TKJ_num_OUT ;
	      TKJ_SumHT_OUT += iJetPt ;
	  }
	}
	
      }

      TString Name ; 
      string NameSample ;
      if(TString(sampleName).Contains("Madgraph_")){
        Name = sampleName;
        Name.ReplaceAll("Madgraph_","");
	NameSample = string(Name) ;
      }
      else 
	NameSample = sampleName ;

      for(size_t iVar = 0; iVar < VariableList2D.size(); iVar++){

        // tranvserse mass
	if(VariableList2D.at(iVar).variableNameX == "Asim_j" and VariableList2D.at(iVar).variableNameY == "Asim_l" ){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimJ,asimL,1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_j" and VariableList2D.at(iVar).variableNameY == "R"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimJ,Rvar,1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_j" and VariableList2D.at(iVar).variableNameY == "DeltaPhi_JJ"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimJ,fabs(RecoJets.at(0).jet4V_.DeltaPhi(RecoJets.at(1).jet4V_)),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_j" and VariableList2D.at(iVar).variableNameY == "DeltaPhi_JJLL"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimJ,fabs(L_dijet.DeltaPhi(L_dilepton)),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_j" and VariableList2D.at(iVar).variableNameY == "DeltaPhi_LL"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimJ,fabs(leptonsIsoTight.at(0).lepton4V_.DeltaPhi(leptonsIsoTight.at(1).lepton4V_)),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_j" and VariableList2D.at(iVar).variableNameY == "detajj"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimJ,fabs(RecoJets.at(0).jet4V_.Eta()-RecoJets.at(1).jet4V_.Eta()),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_j" and VariableList2D.at(iVar).variableNameY == "mjj"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimJ,L_dijet.M(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_j" and VariableList2D.at(iVar).variableNameY == "mTH"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimJ,sqrt(2*L_dilepton.Pt()*L_met.Pt()*(1-TMath::Cos(L_dilepton.DeltaPhi(L_met)))),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_j" and VariableList2D.at(iVar).variableNameY == "DeltaPhi_LLMet"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimJ,fabs(L_dilepton.DeltaPhi(L_met)),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_j" and VariableList2D.at(iVar).variableNameY == "mll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimJ,L_dilepton.M(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_j" and VariableList2D.at(iVar).variableNameY == "ptJJLL"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimJ,(L_dilepton+L_dijet).Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_j" and VariableList2D.at(iVar).variableNameY == "ptJJ"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimJ,L_dijet.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_j" and VariableList2D.at(iVar).variableNameY == "ptll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimJ,L_dilepton.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_j" and VariableList2D.at(iVar).variableNameY == "ptl2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimJ,leptonsIsoTight.at(1).lepton4V_.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_j" and VariableList2D.at(iVar).variableNameY == "ptj2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimJ,RecoJets.at(1).jet4V_.Pt(),1);   
	}

        ///
	else if(VariableList2D.at(iVar).variableNameX == "Asim_l" and VariableList2D.at(iVar).variableNameY == "R"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimL,Rvar,1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_l" and VariableList2D.at(iVar).variableNameY == "DeltaPhi_JJ"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimL,fabs(RecoJets.at(0).jet4V_.DeltaPhi(RecoJets.at(1).jet4V_)),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_l" and VariableList2D.at(iVar).variableNameY == "DeltaPhi_JJLL"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimL,fabs(L_dijet.DeltaPhi(L_dilepton)),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_l" and VariableList2D.at(iVar).variableNameY == "DeltaPhi_LL"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimL,fabs(leptonsIsoTight.at(0).lepton4V_.DeltaPhi(leptonsIsoTight.at(1).lepton4V_)),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_l" and VariableList2D.at(iVar).variableNameY == "detajj"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimL,fabs(RecoJets.at(0).jet4V_.Eta()-RecoJets.at(1).jet4V_.Eta()),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_l" and VariableList2D.at(iVar).variableNameY == "mjj"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimL,L_dijet.M(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_l" and VariableList2D.at(iVar).variableNameY == "mTH"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimL,sqrt(2*L_dilepton.Pt()*L_met.Pt()*(1-TMath::Cos(L_dilepton.DeltaPhi(L_met)))),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_l" and VariableList2D.at(iVar).variableNameY == "DeltaPhi_LLMet"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimL,fabs(L_dilepton.DeltaPhi(L_met)),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_l" and VariableList2D.at(iVar).variableNameY == "mll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimL,L_dilepton.M(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_l" and VariableList2D.at(iVar).variableNameY == "ptJJLL"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimL,(L_dilepton+L_dijet).Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_l" and VariableList2D.at(iVar).variableNameY == "ptJJ"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimL,L_dijet.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_l" and VariableList2D.at(iVar).variableNameY == "ptll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimL,L_dilepton.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_l" and VariableList2D.at(iVar).variableNameY == "ptl2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimL,leptonsIsoTight.at(1).lepton4V_.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "Asim_l" and VariableList2D.at(iVar).variableNameY == "ptj2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     asimL,RecoJets.at(1).jet4V_.Pt(),1);   
	}

        ////
	else if(VariableList2D.at(iVar).variableNameX == "R" and VariableList2D.at(iVar).variableNameY == "DeltaPhi_JJ"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     Rvar,fabs(RecoJets.at(0).jet4V_.DeltaPhi(RecoJets.at(1).jet4V_)),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "R" and VariableList2D.at(iVar).variableNameY == "DeltaPhi_JJLL"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     Rvar,fabs(L_dijet.DeltaPhi(L_dilepton)),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "R" and VariableList2D.at(iVar).variableNameY == "DeltaPhi_LL"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     Rvar,fabs(leptonsIsoTight.at(0).lepton4V_.DeltaPhi(leptonsIsoTight.at(1).lepton4V_)),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "R" and VariableList2D.at(iVar).variableNameY == "detajj"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     Rvar,fabs(RecoJets.at(0).jet4V_.Eta()-RecoJets.at(1).jet4V_.Eta()),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "R" and VariableList2D.at(iVar).variableNameY == "mjj"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     Rvar,L_dijet.M(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "R" and VariableList2D.at(iVar).variableNameY == "mTH"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     Rvar,sqrt(2*L_dilepton.Pt()*L_met.Pt()*(1-TMath::Cos(L_dilepton.DeltaPhi(L_met)))),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "R" and VariableList2D.at(iVar).variableNameY == "DeltaPhi_LLMet"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     Rvar,fabs(L_dilepton.DeltaPhi(L_met)),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "R" and VariableList2D.at(iVar).variableNameY == "mll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     Rvar,L_dilepton.M(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "R" and VariableList2D.at(iVar).variableNameY == "ptJJLL"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     Rvar,(L_dilepton+L_dijet).Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "R" and VariableList2D.at(iVar).variableNameY == "ptJJ"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     Rvar,L_dijet.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "R" and VariableList2D.at(iVar).variableNameY == "ptll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     Rvar,L_dilepton.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "R" and VariableList2D.at(iVar).variableNameY == "ptl2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     Rvar,leptonsIsoTight.at(1).lepton4V_.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "R" and VariableList2D.at(iVar).variableNameY == "ptj2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     Rvar,RecoJets.at(1).jet4V_.Pt(),1);   
	}

        ////
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJ" and VariableList2D.at(iVar).variableNameY == "DeltaPhi_JJLL"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(RecoJets.at(0).jet4V_.DeltaPhi(RecoJets.at(1).jet4V_)),fabs(L_dijet.DeltaPhi(L_dilepton)),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJ" and VariableList2D.at(iVar).variableNameY == "DeltaPhi_LL"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(RecoJets.at(0).jet4V_.DeltaPhi(RecoJets.at(1).jet4V_)),fabs(leptonsIsoTight.at(0).lepton4V_.DeltaPhi(leptonsIsoTight.at(1).lepton4V_)),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJ" and VariableList2D.at(iVar).variableNameY == "detajj"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(RecoJets.at(0).jet4V_.DeltaPhi(RecoJets.at(1).jet4V_)),fabs(RecoJets.at(0).jet4V_.Eta()-RecoJets.at(1).jet4V_.Eta()),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJ" and VariableList2D.at(iVar).variableNameY == "mjj"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(RecoJets.at(0).jet4V_.DeltaPhi(RecoJets.at(1).jet4V_)),L_dijet.M(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJ" and VariableList2D.at(iVar).variableNameY == "mTH"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(RecoJets.at(0).jet4V_.DeltaPhi(RecoJets.at(1).jet4V_)),sqrt(2*L_dilepton.Pt()*L_met.Pt()*(1-TMath::Cos(L_dilepton.DeltaPhi(L_met)))),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJ" and VariableList2D.at(iVar).variableNameY == "DeltaPhi_LLMet"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(RecoJets.at(0).jet4V_.DeltaPhi(RecoJets.at(1).jet4V_)),fabs(L_dilepton.DeltaPhi(L_met)),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJ" and VariableList2D.at(iVar).variableNameY == "mll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(RecoJets.at(0).jet4V_.DeltaPhi(RecoJets.at(1).jet4V_)),L_dilepton.M(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJ" and VariableList2D.at(iVar).variableNameY == "ptJJLL"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(RecoJets.at(0).jet4V_.DeltaPhi(RecoJets.at(1).jet4V_)),(L_dilepton+L_dijet).Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJ" and VariableList2D.at(iVar).variableNameY == "ptJJ"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(RecoJets.at(0).jet4V_.DeltaPhi(RecoJets.at(1).jet4V_)),L_dijet.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJ" and VariableList2D.at(iVar).variableNameY == "ptll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(RecoJets.at(0).jet4V_.DeltaPhi(RecoJets.at(1).jet4V_)),L_dilepton.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJ" and VariableList2D.at(iVar).variableNameY == "ptl2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(RecoJets.at(0).jet4V_.DeltaPhi(RecoJets.at(1).jet4V_)),leptonsIsoTight.at(1).lepton4V_.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJ" and VariableList2D.at(iVar).variableNameY == "ptj2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(RecoJets.at(0).jet4V_.DeltaPhi(RecoJets.at(1).jet4V_)),RecoJets.at(1).jet4V_.Pt(),1);   
	}

        ////
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJLL" and VariableList2D.at(iVar).variableNameY == "DeltaPhi_LL"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(L_dijet.DeltaPhi(L_dilepton)),fabs(leptonsIsoTight.at(0).lepton4V_.DeltaPhi(leptonsIsoTight.at(1).lepton4V_)),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJLL" and VariableList2D.at(iVar).variableNameY == "detajj"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(L_dijet.DeltaPhi(L_dilepton)),fabs(RecoJets.at(0).jet4V_.Eta()-RecoJets.at(1).jet4V_.Eta()),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJLL" and VariableList2D.at(iVar).variableNameY == "mjj"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(L_dijet.DeltaPhi(L_dilepton)),L_dijet.M(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJLL" and VariableList2D.at(iVar).variableNameY == "mTH"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(L_dijet.DeltaPhi(L_dilepton)),sqrt(2*L_dilepton.Pt()*L_met.Pt()*(1-TMath::Cos(L_dilepton.DeltaPhi(L_met)))),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJLL" and VariableList2D.at(iVar).variableNameY == "DeltaPhi_LLMet"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(L_dijet.DeltaPhi(L_dilepton)),fabs(L_dilepton.DeltaPhi(L_met)),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJLL" and VariableList2D.at(iVar).variableNameY == "mll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(L_dijet.DeltaPhi(L_dilepton)),L_dilepton.M(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJLL" and VariableList2D.at(iVar).variableNameY == "ptJJLL"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(L_dijet.DeltaPhi(L_dilepton)),(L_dilepton+L_dijet).Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJLL" and VariableList2D.at(iVar).variableNameY == "ptJJ"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(L_dijet.DeltaPhi(L_dilepton)),L_dijet.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJLL" and VariableList2D.at(iVar).variableNameY == "ptll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(L_dijet.DeltaPhi(L_dilepton)),L_dilepton.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJLL" and VariableList2D.at(iVar).variableNameY == "ptl2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(L_dijet.DeltaPhi(L_dilepton)),leptonsIsoTight.at(1).lepton4V_.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_JJLL" and VariableList2D.at(iVar).variableNameY == "ptj2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(L_dijet.DeltaPhi(L_dilepton)),RecoJets.at(1).jet4V_.Pt(),1);   
	}


        ////
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_LL" and VariableList2D.at(iVar).variableNameY == "detajj"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(leptonsIsoTight.at(0).lepton4V_.DeltaPhi(leptonsIsoTight.at(1).lepton4V_)),fabs(RecoJets.at(0).jet4V_.Eta()-RecoJets.at(1).jet4V_.Eta()),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_LL" and VariableList2D.at(iVar).variableNameY == "mjj"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(leptonsIsoTight.at(0).lepton4V_.DeltaPhi(leptonsIsoTight.at(1).lepton4V_)),L_dijet.M(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_LL" and VariableList2D.at(iVar).variableNameY == "mTH"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(leptonsIsoTight.at(0).lepton4V_.DeltaPhi(leptonsIsoTight.at(1).lepton4V_)),sqrt(2*L_dilepton.Pt()*L_met.Pt()*(1-TMath::Cos(L_dilepton.DeltaPhi(L_met)))),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_LL" and VariableList2D.at(iVar).variableNameY == "DeltaPhi_LLMet"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(leptonsIsoTight.at(0).lepton4V_.DeltaPhi(leptonsIsoTight.at(1).lepton4V_)),fabs(L_dilepton.DeltaPhi(L_met)),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_LL" and VariableList2D.at(iVar).variableNameY == "mll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(leptonsIsoTight.at(0).lepton4V_.DeltaPhi(leptonsIsoTight.at(1).lepton4V_)),L_dilepton.M(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_LL" and VariableList2D.at(iVar).variableNameY == "ptJJLL"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(leptonsIsoTight.at(0).lepton4V_.DeltaPhi(leptonsIsoTight.at(1).lepton4V_)),(L_dilepton+L_dijet).Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_LL" and VariableList2D.at(iVar).variableNameY == "ptJJ"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(leptonsIsoTight.at(0).lepton4V_.DeltaPhi(leptonsIsoTight.at(1).lepton4V_)),L_dijet.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_LL" and VariableList2D.at(iVar).variableNameY == "ptll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(leptonsIsoTight.at(0).lepton4V_.DeltaPhi(leptonsIsoTight.at(1).lepton4V_)),L_dilepton.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_LL" and VariableList2D.at(iVar).variableNameY == "ptl2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(leptonsIsoTight.at(0).lepton4V_.DeltaPhi(leptonsIsoTight.at(1).lepton4V_)),leptonsIsoTight.at(1).lepton4V_.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_LL" and VariableList2D.at(iVar).variableNameY == "ptj2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(leptonsIsoTight.at(0).lepton4V_.DeltaPhi(leptonsIsoTight.at(1).lepton4V_)),RecoJets.at(1).jet4V_.Pt(),1);   
	}

 
        ///

	else if(VariableList2D.at(iVar).variableNameX == "detajj" and VariableList2D.at(iVar).variableNameY == "mjj"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(RecoJets.at(0).jet4V_.Eta()-RecoJets.at(1).jet4V_.Eta()),L_dijet.M(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "detajj" and VariableList2D.at(iVar).variableNameY == "mTH"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(RecoJets.at(0).jet4V_.Eta()-RecoJets.at(1).jet4V_.Eta()),sqrt(2*L_dilepton.Pt()*L_met.Pt()*(1-TMath::Cos(L_dilepton.DeltaPhi(L_met)))),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "detajj" and VariableList2D.at(iVar).variableNameY == "DeltaPhi_LLMet"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(RecoJets.at(0).jet4V_.Eta()-RecoJets.at(1).jet4V_.Eta()),fabs(L_dilepton.DeltaPhi(L_met)),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "detajj" and VariableList2D.at(iVar).variableNameY == "mll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(RecoJets.at(0).jet4V_.Eta()-RecoJets.at(1).jet4V_.Eta()),L_dilepton.M(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "detajj" and VariableList2D.at(iVar).variableNameY == "ptJJLL"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(RecoJets.at(0).jet4V_.Eta()-RecoJets.at(1).jet4V_.Eta()),(L_dilepton+L_dijet).Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "detajj" and VariableList2D.at(iVar).variableNameY == "ptJJ"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(RecoJets.at(0).jet4V_.Eta()-RecoJets.at(1).jet4V_.Eta()),L_dijet.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "detajj" and VariableList2D.at(iVar).variableNameY == "ptll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(RecoJets.at(0).jet4V_.Eta()-RecoJets.at(1).jet4V_.Eta()),L_dilepton.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "detajj" and VariableList2D.at(iVar).variableNameY == "ptl2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(RecoJets.at(0).jet4V_.Eta()-RecoJets.at(1).jet4V_.Eta()),leptonsIsoTight.at(1).lepton4V_.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "detajj" and VariableList2D.at(iVar).variableNameY == "ptj2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(RecoJets.at(0).jet4V_.Eta()-RecoJets.at(1).jet4V_.Eta()),RecoJets.at(1).jet4V_.Pt(),1);   
	}

        ///
	else if(VariableList2D.at(iVar).variableNameX == "mjj" and VariableList2D.at(iVar).variableNameY == "mTH"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     L_dijet.M(),sqrt(2*L_dilepton.Pt()*L_met.Pt()*(1-TMath::Cos(L_dilepton.DeltaPhi(L_met)))),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "mjj" and VariableList2D.at(iVar).variableNameY == "DeltaPhi_LLMet"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     L_dijet.M(),fabs(L_dilepton.DeltaPhi(L_met)),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "mjj" and VariableList2D.at(iVar).variableNameY == "mll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     L_dijet.M(),L_dilepton.M(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "mjj" and VariableList2D.at(iVar).variableNameY == "ptJJLL"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     L_dijet.M(),(L_dilepton+L_dijet).Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "mjj" and VariableList2D.at(iVar).variableNameY == "ptJJ"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     L_dijet.M(),L_dijet.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "mjj" and VariableList2D.at(iVar).variableNameY == "ptll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     L_dijet.M(),L_dilepton.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "mjj" and VariableList2D.at(iVar).variableNameY == "ptl2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     L_dijet.M(),leptonsIsoTight.at(1).lepton4V_.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "mjj" and VariableList2D.at(iVar).variableNameY == "ptj2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     L_dijet.M(),RecoJets.at(1).jet4V_.Pt(),1);   
	}

        ///
	else if(VariableList2D.at(iVar).variableNameX == "mTH" and VariableList2D.at(iVar).variableNameY == "DeltaPhi_LLMet"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				    sqrt(2*L_dilepton.Pt()*L_met.Pt()*(1-TMath::Cos(L_dilepton.DeltaPhi(L_met)))),fabs(L_dilepton.DeltaPhi(L_met)),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "mTH" and VariableList2D.at(iVar).variableNameY == "mll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				    sqrt(2*L_dilepton.Pt()*L_met.Pt()*(1-TMath::Cos(L_dilepton.DeltaPhi(L_met)))),L_dilepton.M(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "mTH" and VariableList2D.at(iVar).variableNameY == "ptJJLL"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				    sqrt(2*L_dilepton.Pt()*L_met.Pt()*(1-TMath::Cos(L_dilepton.DeltaPhi(L_met)))),(L_dilepton+L_dijet).Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "mTH" and VariableList2D.at(iVar).variableNameY == "ptJJ"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				    sqrt(2*L_dilepton.Pt()*L_met.Pt()*(1-TMath::Cos(L_dilepton.DeltaPhi(L_met)))),L_dijet.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "mTH" and VariableList2D.at(iVar).variableNameY == "ptll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				    sqrt(2*L_dilepton.Pt()*L_met.Pt()*(1-TMath::Cos(L_dilepton.DeltaPhi(L_met)))),L_dilepton.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "mTH" and VariableList2D.at(iVar).variableNameY == "ptl2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				    sqrt(2*L_dilepton.Pt()*L_met.Pt()*(1-TMath::Cos(L_dilepton.DeltaPhi(L_met)))),leptonsIsoTight.at(1).lepton4V_.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "mTH" and VariableList2D.at(iVar).variableNameY == "ptj2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				    sqrt(2*L_dilepton.Pt()*L_met.Pt()*(1-TMath::Cos(L_dilepton.DeltaPhi(L_met)))),RecoJets.at(1).jet4V_.Pt(),1);   
	}


        ///
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_LLMet" and VariableList2D.at(iVar).variableNameY == "mll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(L_dilepton.DeltaPhi(L_met)),L_dilepton.M(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_LLMet" and VariableList2D.at(iVar).variableNameY == "ptJJLL"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(L_dilepton.DeltaPhi(L_met)),(L_dilepton+L_dijet).Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_LLMet" and VariableList2D.at(iVar).variableNameY == "ptJJ"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(L_dilepton.DeltaPhi(L_met)),L_dijet.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_LLMet" and VariableList2D.at(iVar).variableNameY == "ptll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(L_dilepton.DeltaPhi(L_met)),L_dilepton.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_LLMet" and VariableList2D.at(iVar).variableNameY == "ptl2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(L_dilepton.DeltaPhi(L_met)),leptonsIsoTight.at(1).lepton4V_.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "DeltaPhi_LLMet" and VariableList2D.at(iVar).variableNameY == "ptj2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     fabs(L_dilepton.DeltaPhi(L_met)),RecoJets.at(1).jet4V_.Pt(),1);   
	}

        ///
	else if(VariableList2D.at(iVar).variableNameX == "mll" and VariableList2D.at(iVar).variableNameY == "ptJJLL"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     L_dilepton.M(),(L_dilepton+L_dijet).Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "mll" and VariableList2D.at(iVar).variableNameY == "ptJJ"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     L_dilepton.M(),L_dijet.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "mll" and VariableList2D.at(iVar).variableNameY == "ptll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     L_dilepton.M(),L_dilepton.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "mll" and VariableList2D.at(iVar).variableNameY == "ptl2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     L_dilepton.M(),leptonsIsoTight.at(1).lepton4V_.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "mll" and VariableList2D.at(iVar).variableNameY == "ptj2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     L_dilepton.M(),RecoJets.at(1).jet4V_.Pt(),1);   
	}

        ///
	else if(VariableList2D.at(iVar).variableNameX == "ptJJLL" and VariableList2D.at(iVar).variableNameY == "ptJJ"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     (L_dilepton+L_dijet).Pt(),L_dijet.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "ptJJLL" and VariableList2D.at(iVar).variableNameY == "ptll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     (L_dilepton+L_dijet).Pt(),L_dilepton.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "ptJJLL" and VariableList2D.at(iVar).variableNameY == "ptl2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     (L_dilepton+L_dijet).Pt(),leptonsIsoTight.at(1).lepton4V_.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "ptJJLL" and VariableList2D.at(iVar).variableNameY == "ptj2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     (L_dilepton+L_dijet).Pt(),RecoJets.at(1).jet4V_.Pt(),1);   
	}

        ///
	else if(VariableList2D.at(iVar).variableNameX == "ptJJ" and VariableList2D.at(iVar).variableNameY == "ptll"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     L_dijet.Pt(),L_dilepton.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "ptJJ" and VariableList2D.at(iVar).variableNameY == "ptl2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     L_dijet.Pt(),leptonsIsoTight.at(1).lepton4V_.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "ptJJ" and VariableList2D.at(iVar).variableNameY == "ptj2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     L_dijet.Pt(),RecoJets.at(1).jet4V_.Pt(),1);   
	}

        ///
	else if(VariableList2D.at(iVar).variableNameX == "ptll" and VariableList2D.at(iVar).variableNameY == "ptl2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     L_dilepton.Pt(),leptonsIsoTight.at(1).lepton4V_.Pt(),1);   
	}
	else if(VariableList2D.at(iVar).variableNameX == "ptll" and VariableList2D.at(iVar).variableNameY == "ptj2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     L_dilepton.Pt(),RecoJets.at(1).jet4V_.Pt(),1);   
	}

        ///
	else if(VariableList2D.at(iVar).variableNameX == "ptl2" and VariableList2D.at(iVar).variableNameY == "ptj2"){
	  analysisPlots.fill2DHisto (NameSample,CutList.at(iCut).cutLayerName,VariableList2D.at(iVar).variableNameX+"_"+VariableList2D.at(iVar).variableNameY,
				     leptonsIsoTight.at(1).lepton4V_.Pt(),RecoJets.at(1).jet4V_.Pt(),1);   
	}
      }                
    }
  }
}


bool passCutContainerSelection (readTree* reader,
				cutContainer & Cut,
				const string & sampleName,
				const bool   & usePuppiAsDefault,
				const double & minPtLeptonCut,
                                const double & minPtLeptonCutCleaning,
                                const double & leptonIsoCut_mu,
                                const double & leptonIsoCut_el,
                                const double & leptonIsoLooseCut,
                                const double & matchingCone,
                                const double & minJetCutPt,
                                map<string,TH1F*> & vect){


  // dump all the lepton in the event
  vector<leptonContainer> LeptonsAll;
  fillRecoLeptonsArray (LeptonsAll, *reader); 

  // dump tight leptons
  vector<leptonContainer> leptonsIsoTight ;                                                                                                                             
  leptonsIsoTight = dumpLeptons (LeptonsAll, leptonIsoCut_mu, leptonIsoCut_el, minPtLeptonCut);                                                                               

  // identify loose leptons                                                                                                                                             
  vector<leptonContainer> leptonsIsoLoose ;                                                                                                                              
  leptonsIsoLoose = dumpLeptons (LeptonsAll, leptonIsoLooseCut,minPtLeptonCut);                                          

  // take reco jets 
  vector<jetContainer> RecoJetsAll ;                                                                                                                                     
  if(!usePuppiAsDefault)
    fillRecoJetArray (RecoJetsAll, *reader) ;                                                                                              
  else 
    fillPuppiJetArray (RecoJetsAll, *reader) ;                                                                                              

  // skip event with less than two leptons by default                                                                                                                    
  TString nameTemp;
  string Name;
  if(TString(sampleName).Contains("Madgraph_")){
    nameTemp =sampleName ;
    nameTemp.ReplaceAll("Madgraph_","");
    Name = string(nameTemp);
  }
  else
    Name = sampleName ;

  int iBin = 1;
  if(vect.size()!=0){
    vect[Name+"_"+Cut.cutLayerName]->SetBinContent(iBin,vect[Name+"_"+Cut.cutLayerName]->GetBinContent(iBin)+1);   
    vect[Name+"_"+Cut.cutLayerName]->GetXaxis()->SetBinLabel(iBin,"all events");
    iBin++;   
  }

  if(LeptonsAll.size() < 2 )  return false ; // skip the event --> only two reco leptons are good            
  if(RecoJetsAll.size() < 2)  return false ; // skip the event with less than two reco jet                                                     


  if(vect.size()!=0){
    vect[Name+"_"+Cut.cutLayerName]->SetBinContent(iBin,vect[Name+"_"+Cut.cutLayerName]->GetBinContent(iBin)+1);   
    vect[Name+"_"+Cut.cutLayerName]->GetXaxis()->SetBinLabel(iBin,"Reco L-J");
    iBin++;   
  }

   
  // identify tight leptons and require exactly nLep                                                                                                                       
  if (int(leptonsIsoTight.size()) != Cut.nLep ) return false;                                                                                                    

  if(vect.size()!=0){
    vect[Name+"_"+Cut.cutLayerName]->SetBinContent(iBin,vect[Name+"_"+Cut.cutLayerName]->GetBinContent(iBin)+1);   
    vect[Name+"_"+Cut.cutLayerName]->GetXaxis()->SetBinLabel(iBin,"NLep tight");
    iBin++;   
  }

  if (leptonsIsoTight.at(0).lepton4V_.Pt() < Cut.ptL.first) return false;
  
  bool badTrailingLepton = false;
  for( size_t iLep = 1 ; iLep < leptonsIsoTight.size(); iLep++){
    if( leptonsIsoTight.at(iLep).lepton4V_.Pt() < Cut.ptL.second) 
      badTrailingLepton = true;
  }                         
  if(badTrailingLepton) return false;

  if(vect.size()!=0){
    vect[Name+"_"+Cut.cutLayerName]->SetBinContent(iBin,vect[Name+"_"+Cut.cutLayerName]->GetBinContent(iBin)+1);   
    vect[Name+"_"+Cut.cutLayerName]->GetXaxis()->SetBinLabel(iBin,"Lepton PT");
    iBin++;   
  }

  int extraLepton = 0; // count the extra lepton number                                                                                                            
            
  for(size_t iLepton = 0; iLepton < leptonsIsoLoose.size() ; iLepton++){                                                                                             
           
    if(leptonsIsoLoose.at(iLepton).lepton4V_ == leptonsIsoLoose.at(0).lepton4V_ or leptonsIsoLoose.at(iLepton).lepton4V_ == leptonsIsoLoose.at(1).lepton4V_) continue; // skip tight ones
    extraLepton++;                                                                                                                                                          
  }                                                                                                                                                              
                                                                                                                                                                               
  if(extraLepton > Cut.nextra ) return false; // extra lepton cut                                                                                             
  if(vect.size()!=0){
    vect[Name+"_"+Cut.cutLayerName]->SetBinContent(iBin,vect[Name+"_"+Cut.cutLayerName]->GetBinContent(iBin)+1);   
    vect[Name+"_"+Cut.cutLayerName]->GetXaxis()->SetBinLabel(iBin,"extra lepton");
    iBin++;   
  }

  // apply Zmass veto: if nLep == 2 is a veto (WW analysis) if nLep == 3 is a tag (WZ analysis)
  bool isZMassVeto = false;                                                                                                                                            
  for(size_t iLept = 0; iLept < LeptonsAll.size() ; iLept++){                                                                                                             
    if(LeptonsAll.at(iLept).lepton4V_.Pt() < minPtLeptonCut) continue;
    for(size_t jLept = iLept+1; jLept < LeptonsAll.size() ; jLept++){                                                                                                   
      if(LeptonsAll.at(jLept).lepton4V_.Pt() < minPtLeptonCut) continue; 
      if(fabs(LeptonsAll.at(jLept).flavour_) != fabs(LeptonsAll.at(iLept).flavour_)) continue; 
      if((LeptonsAll.at(iLept).lepton4V_ + LeptonsAll.at(jLept).lepton4V_).M() > Cut.MllZVeto.first and                                                         
	 (LeptonsAll.at(iLept).lepton4V_ + LeptonsAll.at(jLept).lepton4V_).M() < Cut.MllZVeto.second and                                                       
	 LeptonsAll.at(iLept).charge_*LeptonsAll.at(jLept).charge_ == -1)                                                                                   
	isZMassVeto = true;                                                                                                                                            
    }
  }                                                                                                                                                                       

  if(isZMassVeto and Cut.nLep == 2) return false;                                                                                                                   
  if(not isZMassVeto and Cut.nLep == 3) return false;

  if(vect.size()!=0){
    vect[Name+"_"+Cut.cutLayerName]->SetBinContent(iBin,vect[Name+"_"+Cut.cutLayerName]->GetBinContent(iBin)+1);   
    vect[Name+"_"+Cut.cutLayerName]->GetXaxis()->SetBinLabel(iBin,"Z veto");
    iBin++;   
  }
                                                                                                                                                                          
  // charge cut for same sign final state : zero means no cut, one means same sign, -1 opposite sign                                                                        
  if(Cut.chargeSign != 0){
    int sign = 1;
    for(size_t leptSize = 0; leptSize < leptonsIsoTight.size(); leptSize++) // loop on tight leptns
      sign *= leptonsIsoTight.at(leptSize).charge_;
    if(sign != Cut.chargeSign) return false;
  }

  if(vect.size()!=0){
    vect[Name+"_"+Cut.cutLayerName]->SetBinContent(iBin,vect[Name+"_"+Cut.cutLayerName]->GetBinContent(iBin)+1);   
    vect[Name+"_"+Cut.cutLayerName]->GetXaxis()->SetBinLabel(iBin,"same sign");
    iBin++;   
  }

  // flavour selection
  if(Cut.flavour != 0){
    int flavour = 0;
    int sameflavour = 0;
    for(size_t leptSize = 0; leptSize < leptonsIsoTight.size(); leptSize++) // loop on tight leptns
      flavour += fabs(leptonsIsoTight.at(leptSize).flavour_) ;
    if(flavour/leptonsIsoTight.size() == 11 or flavour/leptonsIsoTight.size() == 13 ) sameflavour = 1;
    else sameflavour = -1;
    if(sameflavour != Cut.flavour) return false;
  }

  if(vect.size()!=0){
    vect[Name+"_"+Cut.cutLayerName]->SetBinContent(iBin,vect[Name+"_"+Cut.cutLayerName]->GetBinContent(iBin)+1);   
    vect[Name+"_"+Cut.cutLayerName]->GetXaxis()->SetBinLabel(iBin,"flavour selection");
    iBin++;   
  }

  // met cut
  if(reader->pfmet_puppi < Cut.MET) return false;  

  if(vect.size()!=0){
    vect[Name+"_"+Cut.cutLayerName]->SetBinContent(iBin,vect[Name+"_"+Cut.cutLayerName]->GetBinContent(iBin)+1);   
    vect[Name+"_"+Cut.cutLayerName]->GetXaxis()->SetBinLabel(iBin,"met selection");
    iBin++;   
  }


  // take jets
  vector<jetContainer> RecoJets;
  RecoJets  = dumpJets (RecoJetsAll, leptonsIsoTight, minJetCutPt, Cut.bTagVeto, Cut.jetPUID, minPtLeptonCutCleaning, matchingCone);   
  if(RecoJets.size() < 2 ) return false;

  if(vect.size()!=0){
    vect[Name+"_"+Cut.cutLayerName]->SetBinContent(iBin,vect[Name+"_"+Cut.cutLayerName]->GetBinContent(iBin)+1);   
    vect[Name+"_"+Cut.cutLayerName]->GetXaxis()->SetBinLabel(iBin,"jet counting");
    iBin++;   
  }

  ///////// Lorentz Vector
  TLorentzVector L_dilepton;
  L_dilepton = leptonsIsoTight.at(0).lepton4V_ + leptonsIsoTight.at(1).lepton4V_ ;               
  
  // apply Mll cut
  if(L_dilepton.M() < Cut.Mll.first or L_dilepton.M() > Cut.Mll.second) return false;
  
  if(vect.size()!=0){
    vect[Name+"_"+Cut.cutLayerName]->SetBinContent(iBin,vect[Name+"_"+Cut.cutLayerName]->GetBinContent(iBin)+1);   
    vect[Name+"_"+Cut.cutLayerName]->GetXaxis()->SetBinLabel(iBin,"Mll");
    iBin++;   
  }

  TLorentzVector L_dijet;
  if(RecoJets.size() >= 2){
    L_dijet  = RecoJets.at(0).jet4V_ + RecoJets.at(1).jet4V_;                                                                                                    
  }

  // apply VBF cuts
  if(L_dijet.M() < Cut.Mjj) return false;
     

  if(vect.size()!=0){
    vect[Name+"_"+Cut.cutLayerName]->SetBinContent(iBin,vect[Name+"_"+Cut.cutLayerName]->GetBinContent(iBin)+1);   
    vect[Name+"_"+Cut.cutLayerName]->GetXaxis()->SetBinLabel(iBin,"Mjj");
    iBin++;   
  }

  if(fabs(RecoJets.at(0).jet4V_.Eta()-RecoJets.at(1).jet4V_.Eta()) < Cut.DetaJJ) return false;
  
  if(vect.size()!=0){
    vect[Name+"_"+Cut.cutLayerName]->SetBinContent(iBin,vect[Name+"_"+Cut.cutLayerName]->GetBinContent(iBin)+1);   
    vect[Name+"_"+Cut.cutLayerName]->GetXaxis()->SetBinLabel(iBin,"DetaJJ");
    iBin++;   
  }

  if(fabs(leptonsIsoTight.at(0).lepton4V_.Eta()-leptonsIsoTight.at(1).lepton4V_.Eta()) > Cut.DetaLL) return false;

  if(vect.size()!=0){
    vect[Name+"_"+Cut.cutLayerName]->SetBinContent(iBin,vect[Name+"_"+Cut.cutLayerName]->GetBinContent(iBin)+1);   
    vect[Name+"_"+Cut.cutLayerName]->GetXaxis()->SetBinLabel(iBin,"DetaLL");
    iBin++;   
  }


  // polarized cut
  if(Cut.polarization != 99 or TString(sampleName).Contains("Madgraph")){

    int polarizationFlag = 0;

    if(Cut.polarization != 99){
      if(fabs(reader->vbosonLHEspin1) == 0 and fabs(reader->vbosonLHEspin2) == 0) 
	polarizationFlag = 0 ; //LL
      else if((fabs(reader->vbosonLHEspin1) == 1 and fabs(reader->vbosonLHEspin2) ==0) or (fabs(reader->vbosonLHEspin1) == 0 and fabs(reader->vbosonLHEspin2) ==1))
	polarizationFlag = 1 ; //TL
      else
	polarizationFlag = 2 ; //TT

      if(polarizationFlag != Cut.polarization) return false;

      if(vect.size()!=0){
	vect[Name+"_"+Cut.cutLayerName]->SetBinContent(iBin,vect[Name+"_"+Cut.cutLayerName]->GetBinContent(iBin)+1);   
	vect[Name+"_"+Cut.cutLayerName]->GetXaxis()->SetBinLabel(iBin,"Polarization");
	iBin++;   
      }
    }
    else if(TString(sampleName).Contains("Madgraph")){
      if(fabs(reader->vbosonLHEspin1) == 0 and fabs(reader->vbosonLHEspin2) == 0) 
	polarizationFlag = 0 ; //LL
      else if((fabs(reader->vbosonLHEspin1) == 1 and fabs(reader->vbosonLHEspin2) ==0) or (fabs(reader->vbosonLHEspin1) == 0 and fabs(reader->vbosonLHEspin2) ==1))
	polarizationFlag = 1 ; //TL
      else 
	polarizationFlag = 2 ; //TT

      if(TString(sampleName).Contains("_LL")  and polarizationFlag != 0) return false;
      if(TString(sampleName).Contains("_TL")  and polarizationFlag != 1) return false;
      if(TString(sampleName).Contains("_TT")  and polarizationFlag != 2) return false;

      if(vect.size()!=0){
	vect[Name+"_"+Cut.cutLayerName]->SetBinContent(iBin,vect[Name+"_"+Cut.cutLayerName]->GetBinContent(iBin)+1);   
	vect[Name+"_"+Cut.cutLayerName]->GetXaxis()->SetBinLabel(iBin,"Polarization");
	iBin++;   
      }
    }
  }
  else{    
    if(vect.size()!=0){
      vect[Name+"_"+Cut.cutLayerName]->SetBinContent(iBin,vect[Name+"_"+Cut.cutLayerName]->GetBinContent(iBin)+1);   
      vect[Name+"_"+Cut.cutLayerName]->GetXaxis()->SetBinLabel(iBin,"Polarization");
      iBin++;   
    }
  } 
  

  return true;

}
