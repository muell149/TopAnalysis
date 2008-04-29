/*
 FWlite analyzer running on TQAF Layer2 Output in ttbar dileptonic mu mu decay chanel
   
   specify the name of the input and output file below!
*/

double invMass(TLorentzVector, TLorentzVector);   // calculates the invariant mass of to particle 4-vectors

int ttDilepMuMuAnalyzer() {

  // specify sample and output file here 
  TFile sourceFile("/rdata2/desy-cms001/data/dammann/data/TQAF_L2_TtDilepMuMu/ttbar.root");    
  TString *outputName = new TString("ttbar");
  TString *outputPsName = new TString(*outputName);
  outputPsName->Append(".eps");
  TString *outputRootName = new TString(*outputName);
  outputRootName->Append(".root");  
           
  TTree *events = (TTree*)sourceFile.Get("Events");
  events->GetEntry();      
    
  vector<TtDilepEvtSolution> solutions; 
  TBranch *solsBranch = events->GetBranch("TtDilepEvtSolutions_solutions__TQAF.obj"); 
  assert( solsBranch != 0 );
  solsBranch->SetAddress(&solutions);

  // book histograms   
  // general        
  TH1F *AllTopMassHist  = new TH1F("AllTopMassHist" , "all reconstructed top masses"  ,  50,  100, 300);  
  TH1F *BestTopMassHist = new TH1F("BestTopMassHist", "best reconstructed top mass"   ,  50,  100, 300);
  TH1F *GenTopMassHist  = new TH1F("GenTopMassHist" , "generated top masses"          ,  50,  100, 300);
  TH1F *WeightMaxHist   = new TH1F("WeightMaxHist"  , "maximum solution weight"       ,  50,    0,   1);
  TH1F *NSolHist        = new TH1F("NSolHist"       , "number of solutions per event ",  10, -0.5, 9.5); 
  
  // top kinematics (not directly accessible)
  //TH1F *PtTopHist    = new TH1F("PtTopHist"   , "p_{t,t}" ,  50,    0, 400);    
  //TH1F *EtaTopHist   = new TH1F("EtaTopHist"  , "#eta_{t}",  50, -2.5, 2.5);       
  //TH1F *PhiTopHist   = new TH1F("PhiTopHist"  , "#phi_{t}",  72, -180, 180); 
      
  TH1F *PtGenTHist    = new TH1F("PtGenTHist"   , "p_{t}"   ,  50,    0, 400);  
  TH1F *EtaGenTHist   = new TH1F("EtaGenTHist"  , "#eta_{t}",  50, -2.5, 2.5);  
  TH1F *PhiGenTHist   = new TH1F("PhiGenTHist"  , "#phi_{t}",  72, -180, 180); 
    
  // muon quantities  
  TH1F *PtMuPHist    = new TH1F("PtMuPHist"   , "p_{t,#mu^{+}}" ,  50,   10, 110);    
  TH1F *PtMuMHist    = new TH1F("PtMuMHist"   , "p_{t,#mu^{-}}" ,  50,   10, 110);
  TH1F *EtaMuPHist   = new TH1F("EtaMuPHist"  , "#eta_{#mu^{+}}",  50, -2.5, 2.5);    
  TH1F *EtaMuMHist   = new TH1F("EtaMuMHist"  , "#eta_{#mu^{-}}",  50, -2.5, 2.5);   
  TH1F *PhiMuPHist   = new TH1F("PhiMuPHist"  , "#phi_{#mu^{+}}",  72, -180, 180);    
  TH1F *PhiMuMHist   = new TH1F("PhiMuMHist"  , "#phi_{#mu^{-}}",  72, -180, 180);  
  
  TH1F *PtGenMuPHist    = new TH1F("PtGenMuPHist"   , "p_{t,#mu^{+}}" ,  50,   10, 110);    
  TH1F *PtGenMuMHist    = new TH1F("PtGenMuMHist"   , "p_{t,#mu^{-}}" ,  50,   10, 110);
  TH1F *EtaGenMuPHist   = new TH1F("EtaGenMuPHist"  , "#eta_{#mu^{+}}",  50, -2.5, 2.5);    
  TH1F *EtaGenMuMHist   = new TH1F("EtaGenMuMHist"  , "#eta_{#mu^{-}}",  50, -2.5, 2.5);   
  TH1F *PhiGenMuPHist   = new TH1F("PhiGenMuPHist"  , "#phi_{#mu^{+}}",  72, -180, 180);    
  TH1F *PhiGenMuMHist   = new TH1F("PhiGenMuMHist"  , "#phi_{#mu^{-}}",  72, -180, 180);  
  
  TH1F* DilepMassHist    = new  TH1F("DilepMassHist"     , "M_{#mu^{+},#mu^{-}}", 100, 0, 200); 
  TH1F* DilepMassGenHist = new  TH1F("DilepMassGenHist"  , "M_{#mu^{+},#mu^{-}}", 100, 0, 200);    
    
  // jet quantities
  TH1F *PtBJetHist   = new TH1F("PtBJetHist"  , "p_{t,b}"  ,  50,  25, 225);
  TH1F *PtBbJetHist  = new TH1F("PtBbJetHist" , "p_{t,b_}" ,  50,  25, 225);
  TH1F *EtaBJetHist  = new TH1F("EtaBJetHist" , "#eta_{b} ",  50,-2.5, 2.5);
  TH1F *EtaBbJetHist = new TH1F("EtaBbJetHist", "#eta_{b_}",  50,-2.5, 2.5); 
  TH1F *PhiBJetHist  = new TH1F("PhiBJetHist" , "#phi_{b} ",  72,-180, 180);
  TH1F *PhiBbJetHist = new TH1F("PhiBbJetHist", "#phi_{b_}",  72,-180, 180);
  
  TH1F *PtGenBHist   = new TH1F("PtGenBHist"  , "p_{t,b}"  ,  50,  25, 225);
  TH1F *PtGenBbHist  = new TH1F("PtGenBbHist" , "p_{t,b_}" ,  50,  25, 225);
  TH1F *EtaGenBHist  = new TH1F("EtaGenBHist" , "#eta_{b} ",  50,-2.5, 2.5);
  TH1F *EtaGenBbHist = new TH1F("EtaGenBbHist", "#eta_{b_}",  50,-2.5, 2.5); 
  TH1F *PhiGenBHist  = new TH1F("PhiGenBHist" , "#phi_{b} ",  72,-180, 180);
  TH1F *PhiGenBbHist = new TH1F("PhiGenBbHist", "#phi_{b_}",  72,-180, 180);  
      
  // MET quantities 
  TH1F *PtMetHist  = new TH1F("PtMetHist" , "missing transverse momentum" , 50,   0, 200);    
  TH1F *PhiMetHist = new TH1F("PhiMetHist", "#phi MET"                    , 72,-180, 180);
  
  TH1F *PtGenMetHist  = new TH1F("PtGenMetHist" , "generated missing transverse momentum" , 50,   0, 200);    
  TH1F *PhiGenMetHist = new TH1F("PhiGenMetHist", "generated #phi MET"                    , 72,-180, 180);    
   
  TH1F *maxEtInEmTowersHist    = new TH1F("maxEtInEmTowersHist"   , "maximum energy deposited in ECAL towers",  50,  0, 100);  
  TH1F *maxEtInHadTowersHist   = new TH1F("maxEtInHadTowersHist"  , "maximum energy deposited in HCAL towers",  50,  0, 100);  
  TH1F *etFractionHadronicHist = new TH1F("etFractionHadronicHist", "event hadronic energy fraction"         ,  50,  0,   1);
  TH1F *etFractionEmHist       = new TH1F("etFractionEmHist"      , "event electromagnetic energy fraction"  ,  50,  0,   1);  
  TH1F *hadEtInHBHist          = new TH1F("hadEtInHBHist"         , "event hadronic energy in HB"            ,  50,  0, 100);  
  TH1F *hadEtInHOHist          = new TH1F("hadEtInHOHist"         , "event hadronic energy in HO"            ,  25,  0,   5);  
  TH1F *hadEtInHFHist          = new TH1F("hadEtInHFHist"         , "event hadronic energy in HF"            ,  50,  0, 100);  
  TH1F *hadEtInHEHist          = new TH1F("hadEtInHEHist"         , "event hadronic energy in HE"            ,  50,  0, 100);  
  TH1F *emEtInEBHist           = new TH1F("emEtInEBHist"          , "event electromagnetic energy in EB"     ,  50,  0, 200);    
  TH1F *emEtInEEHist           = new TH1F("emEtInEEHist"          , "event electromagnetic energy in EE"     ,  50,  0, 100);  
  TH1F *emEtInHFHist           = new TH1F("emEtInHFHist"          , "event electromagnetic energy in HF"     ,  50,  0, 100); 
   
  cout << events->GetEntries() << " events found in tree" << endl; 
    
  // event loop      
  for(unsigned int i = 0; i < events->GetEntries(); ++i) { 
  //for(unsigned int i = 0; i < 1000; ++i) {           
    // inform about job status
    if(i%1000==0) { 
      cout << " event number: " << i << endl;
    }
         
    solsBranch->SetAddress(&solutions);      
    solsBranch->GetEntry(i);
    events->GetEntry(i,0); 

    int nSols = solutions.size();    
    NSolHist   ->Fill(nSols - .5);
    
    //loop over solutions per event        
    for(unsigned int j = 0; j < nSols; j++) {
      double recTopMass = solutions.at(j).getRecTopMass();

      // check for dummy solutions and solution without appropiate top mass
      if(recTopMass==0) continue;       
      AllTopMassHist->Fill(recTopMass);

      // get solution which matches generated event best
      if(solutions.at(j).getBestSol()) {        
        BestTopMassHist->Fill(recTopMass);           
      }

      double recWeightMax = solutions[j].getRecWeightMax();
      WeightMaxHist->Fill(recWeightMax);

      // get top objects                            
      TopMuon MuonP = solutions[j].getMuonp();
      TopMuon MuonM = solutions[j].getMuonm();	 
      TopJet  BJet  = solutions.at(j).getCalJetB();         	             
      TopJet  BbJet = solutions.at(j).getJetBbar();        
      TopMET  Met   = solutions.at(j).getMET();

      // kinematical variables                     
      // muons
      double PtMuP  = MuonP.pt();      PtMuPHist ->Fill(PtMuP); 
      double PtMuM  = MuonM.pt();      PtMuMHist ->Fill(PtMuM);
      double EtaMuP = MuonP.eta();     EtaMuPHist->Fill(EtaMuP); 
      double EtaMuM = MuonM.eta();     EtaMuMHist->Fill(EtaMuM);       
      double PhiMuP = MuonP.phi();     PhiMuPHist->Fill(PhiMuP*180/TMath::Pi()); 
      double PhiMuM = MuonM.phi();     PhiMuMHist->Fill(PhiMuM*180/TMath::Pi());
      
      // invariant mass of the muon pair to surpress z induced background
      TLorentzVector P4MuP = TLorentzVector(MuonP.px(),MuonP.py(),MuonP.pz(),MuonP.energy());
      TLorentzVector P4MuM = TLorentzVector(MuonM.px(),MuonM.py(),MuonM.pz(),MuonM.energy());      
      double DilepMass =  invMass(P4MuP,P4MuM);  
      DilepMassHist->Fill(DilepMass);       

      // jets
      double PtBJet   = BJet.pt();     PtBJetHist  ->Fill(PtBJet); 
      double PtBbJet  = BbJet.pt();    PtBbJetHist ->Fill(PtBbJet);
      double EtaBJet  = BJet.eta();    EtaBJetHist ->Fill(EtaBJet); 
      double EtaBbJet = BbJet.eta();   EtaBbJetHist->Fill(EtaBbJet);       
      double PhiBJet  = BJet.phi();    PhiBJetHist ->Fill(PhiBJet*180/TMath::Pi()); 
      double PhiBbJet = BbJet.phi();   PhiBbJetHist->Fill(PhiBbJet*180/TMath::Pi());  

      // MET
      double PtMet  = Met.pt();        PtMetHist ->Fill(PtMet);        
      double PhiMet = Met.phi();       PhiMetHist->Fill(PhiMet*180/TMath::Pi()); 

      double maxEtInEmTowers    = Met.maxEtInEmTowers();    maxEtInEmTowersHist   ->Fill(maxEtInEmTowers);
      double maxEtInHadTowers   = Met.maxEtInHadTowers();   maxEtInHadTowersHist  ->Fill(maxEtInHadTowers);       
      double etFractionHadronic = Met.etFractionHadronic(); etFractionHadronicHist->Fill(etFractionHadronic);       
      double etFractionEm       = Met.emEtFraction();       etFractionEmHist      ->Fill(etFractionEm);       
      double hadEtInHB          = Met.hadEtInHB();          hadEtInHBHist         ->Fill(hadEtInHB);
      double hadEtInHO          = Met.hadEtInHO();          hadEtInHOHist         ->Fill(hadEtInHO);  
      double hadEtInHF          = Met.hadEtInHF();          hadEtInHFHist         ->Fill(hadEtInHF);       
      double hadEtInHE          = Met.hadEtInHE();          hadEtInHEHist         ->Fill(hadEtInHE);       
      double emEtInEB           = Met.emEtInEB();           emEtInEBHist          ->Fill(emEtInEB);       
      double emEtInEE           = Met.emEtInEE();           emEtInEEHist          ->Fill(emEtInEE);
      double emEtInHF           = Met.emEtInHF();           emEtInHFHist          ->Fill(emEtInHF);  
                 
      // get generator information
      reco::GenParticle  GenMet = Met.getGenMET();  
      double PtGenMet  = GenMet.pt();        PtGenMetHist ->Fill(PtGenMet);        
      double PhiGenMet = GenMet.phi();       PhiGenMetHist->Fill(PhiGenMet*180/TMath::Pi());  
                         
      edm::RefProd<TtGenEvent> GenEvent = solutions.at(j).getGenEvent(); 
      if(GenEvent.isNonnull() && GenEvent->isFullLeptonic()==true) {
        reco::GenParticle* GenTop  = GenEvent->top();
        reco::GenParticle* GenTopb = GenEvent->topBar();
        reco::GenParticle* GenMuP  = GenEvent->muPlus();
        reco::GenParticle* GenMuM  = GenEvent->muMinus();		
        reco::GenParticle* GenB    = GenEvent->b();        
	reco::GenParticle* GenBb   = GenEvent->bBar();	       		
       
        double GenTopMass  = GenTop ->mass();   GenTopMassHist->Fill(GenTopMass);
	double GenTopPt    = GenTop ->pt();     PtGenTHist    ->Fill(GenTopPt);
	double GenTopEta   = GenTop ->eta();    EtaGenTHist   ->Fill(GenTopEta);
	double GenTopPhi   = GenTop ->phi();    PhiGenTHist   ->Fill(GenTopPhi*180/TMath::Pi());
	
        double GenTopbMass = GenTopb->mass();   GenTopMassHist->Fill(GenTopMass);
	double GenTopbPt   = GenTopb->pt();     PtGenTHist    ->Fill(GenTopbPt);
	double GenTopbEta  = GenTopb->eta();    EtaGenTHist   ->Fill(GenTopbEta);
	double GenTopbPhi  = GenTopb->phi();    PhiGenTHist   ->Fill(GenTopbPhi*180/TMath::Pi());	
       
        if(GenMuP!=0 ) {
          double PtGenMuP  = GenMuP->pt();      PtGenMuPHist ->Fill(PtGenMuP); 
	  double EtaGenMuP = GenMuP->eta();     EtaGenMuPHist->Fill(EtaGenMuP);
	  double PhiGenMuP = GenMuP->phi();     PhiGenMuPHist->Fill(PhiGenMuP*180/TMath::Pi()); 	
        }
        if(GenMuM!=0 ) {
          double PtGenMuM  = GenMuM->pt();      PtGenMuMHist ->Fill(PtGenMuM);
	  double EtaGenMuM = GenMuM->eta();     EtaGenMuMHist->Fill(EtaGenMuM);
	  double PhiGenMuM = GenMuM->phi();     PhiGenMuMHist->Fill(PhiGenMuM*180/TMath::Pi());
        } 
        if(GenMuP!=0 && GenMuM!=0 ) {
	  TLorentzVector GenP4MuP = TLorentzVector(GenMuP->px(),GenMuP->py(),GenMuP->pz(),GenMuP->energy());
	  TLorentzVector GenP4MuM = TLorentzVector(GenMuM->px(),GenMuM->py(),GenMuM->pz(),GenMuM->energy());
	  double GenDilepMass = invMass(GenP4MuP,GenP4MuM);	
	  DilepMassGenHist->Fill(GenDilepMass); 	
	}
	
        double PtGenB   = GenB->pt();           PtGenBHist ->Fill(PtGenB); 
	double EtaGenB  = GenB->eta();          EtaGenBHist->Fill(EtaGenB);
	double PhiGenB  = GenB->phi();          PhiGenBHist->Fill(PhiGenB*180/TMath::Pi()); 
	
        double PtGenBb  = GenBb->pt();          PtGenBbHist ->Fill(PtGenBb);
	double EtaGenBb = GenBb->eta();         EtaGenBbHist->Fill(EtaGenBb);
	double PhiGenBb = GenBb->phi();         PhiGenBbHist->Fill(PhiGenBb*180/TMath::Pi());		
      }                      
    } //end of solutions loop         
  } //end of event loop
  
  // write root output file
  TFile* outFile = new TFile(*outputRootName,"RECREATE");  
  outFile->mkdir("top"); outFile->cd("top");
  AllTopMassHist ->Write();
  BestTopMassHist->Write();
  GenTopMassHist ->Write();
  
  PtGenTHist  ->Write();
  EtaGenTHist ->Write();  
  PhiGenTHist ->Write();  
  
  outFile->cd(); outFile->mkdir("muons_rec"); outFile->cd("muons_rec");
  PtMuPHist    ->Write();
  PtMuMHist    ->Write();
  EtaMuPHist   ->Write();
  EtaMuMHist   ->Write();
  PhiMuPHist   ->Write();
  PhiMuMHist   ->Write();
  DilepMassHist->Write(); 
  
  outFile->cd(); outFile->mkdir("muons_gen"); outFile->cd("muons_gen");
  PtGenMuPHist ->Write();
  PtGenMuMHist ->Write();
  EtaGenMuPHist->Write();
  EtaGenMuMHist->Write();
  PhiGenMuPHist->Write();
  PhiGenMuMHist->Write();  
  DilepMassGenHist->Write();  
   
  outFile->cd(); outFile->mkdir("jets_rec"); outFile->cd("jets_rec"); 
  PtBJetHist  ->Write();
  PtBbJetHist ->Write();
  EtaBJetHist ->Write();
  EtaBbJetHist->Write();
  PhiBJetHist ->Write();
  PhiBbJetHist->Write(); 
   
  outFile->cd(); outFile->mkdir("jets_gen"); outFile->cd("jets_gen"); 
  PtGenBHist  ->Write();
  PtGenBbHist ->Write();
  EtaGenBHist ->Write();
  EtaGenBbHist->Write();
  PhiGenBHist ->Write();
  PhiGenBbHist->Write();   
  
  outFile->cd(); outFile->mkdir("MET_rec"); outFile->cd("MET_rec"); 
  PtMetHist             ->Write();
  PhiMetHist            ->Write();
  maxEtInEmTowersHist   ->Write();
  maxEtInHadTowersHist  ->Write();
  etFractionHadronicHist->Write();
  etFractionEmHist      ->Write();
  hadEtInHOHist         ->Write();
  hadEtInHBHist         ->Write();
  hadEtInHEHist         ->Write();
  hadEtInHFHist         ->Write();
  emEtInEBHist          ->Write();
  emEtInEEHist          ->Write();
  emEtInHFHist          ->Write();

  outFile->cd(); outFile->mkdir("MET_gen"); outFile->cd("MET_gen");  
  PtGenMetHist ->Write();
  PhiGenMetHist->Write();
  outFile->Write();
  outFile->Close();   
  
  // histogram make up
  gROOT ->SetStyle("Plain");
  gStyle->SetOptFit(0001);
  
  AllTopMassHist ->SetXTitle("m_{t,rec}/GeV");
  AllTopMassHist ->SetYTitle("N_{entrs}");   
  
  BestTopMassHist->SetXTitle("m_{t,rec}/GeV");
  BestTopMassHist->SetYTitle("N_{entrs}");
  
  WeightMaxHist  ->SetXTitle("WeightMax");
  WeightMaxHist  ->SetYTitle("N_{entrs}");  
    
  NSolHist       ->SetXTitle("N_{sols}");
  NSolHist       ->SetYTitle("N_{evts}"); 
  
  // prepare fitting
  int fitRange = 10;  //in bins around the maximum
  
  int maxBinAll   = AllTopMassHist->GetMaximumBin();  
  int lowLimitAll = 100;
  int uppLimitAll = 300;  
  if(maxBinAll - fitRange > 0) {
    lowLimitAll = 100 + 4*(maxBinAll - fitRange);
  }
  if(maxBinAll + fitRange < 50) {
    uppLimitAll = 100 + 4*(maxBinAll + fitRange);
  }
  
  int maxBinBest   = BestTopMassHist->GetMaximumBin();  
  int lowLimitBest = 100;
  int uppLimitBest = 300;  
  if(maxBinBest - fitRange > 0) {
    lowLimitBest = 100 + 4*(maxBinBest - fitRange);
  }
  if(maxBinBest + fitRange < 100) {
    uppLimitBest = 100 + 4*(maxBinBest + fitRange);
  }    
     
  // print and save histograms as postscript  
  TPostScript ps (*outputPsName,111);     
  TCanvas* canvas = new TCanvas("mass", "mass", 600, 800);  
  
  canvas->Clear(); canvas->Divide(2,2);
  canvas->cd(1);   AllTopMassHist ->Fit("gaus","QM","E",lowLimitAll, uppLimitAll);
                   AllTopMassHist ->Draw();
		   GenTopMassHist ->SetLineColor(4);
		   GenTopMassHist ->SetLineStyle(2);
		   GenTopMassHist ->Draw("same");
  canvas->cd(2);   BestTopMassHist->Fit("gaus","QM","E",lowLimitBest,uppLimitBest);   
                   BestTopMassHist->Draw();  
  canvas->cd(3);   WeightMaxHist  ->Draw();  
  canvas->cd(4);   NSolHist       ->Draw();  
  canvas->cd(); canvas->Update(); 
  
  canvas->Clear(); canvas->Divide(2,2);
  canvas->cd(1);   PtGenTHist     ->SetLineColor(4);
                   PtGenTHist     ->SetLineStyle(2);
                   PtGenTHist     ->Draw();
  canvas->cd(2);   EtaGenTHist    ->SetLineColor(4);
                   EtaGenTHist    ->SetLineStyle(2);
                   EtaGenTHist    ->Draw();
  canvas->cd(3);   PhiGenTHist    ->SetMinimum(0);
                   PhiGenTHist    ->SetLineColor(4);
                   PhiGenTHist    ->SetLineStyle(2);
                   PhiGenTHist    ->Draw();
  canvas->cd(4);  
  canvas->cd(); canvas->Update();    
  
  canvas->Clear(); canvas->Divide(2,4);
  canvas->cd(1);  PtMuPHist    ->SetFillColor(5);  
                  PtMuPHist    ->Draw();
                  PtGenMuPHist ->SetLineColor(4);
                  PtGenMuPHist ->SetLineStyle(2);
                  PtGenMuPHist ->Draw("same");
  canvas->cd(2);  PtMuMHist    ->SetFillColor(5);  
                  PtMuMHist    ->Draw();
                  PtGenMuMHist ->SetLineColor(4);
                  PtGenMuMHist ->SetLineStyle(2);
                  PtGenMuMHist ->Draw("same");
  canvas->cd(3);  EtaMuPHist   ->SetFillColor(5);  
                  EtaMuPHist   ->Draw();
                  EtaGenMuPHist->SetLineColor(4);
                  EtaGenMuPHist->SetLineStyle(2);
                  EtaGenMuPHist->Draw("same");
  canvas->cd(4);  EtaMuMHist   ->SetFillColor(5);  
                  EtaMuMHist   ->Draw();  
                  EtaGenMuMHist->SetLineColor(4);  
                  EtaGenMuMHist->SetLineStyle(2);
                  EtaGenMuMHist->Draw("same");
  canvas->cd(5);  PhiMuPHist   ->SetFillColor(5); 
                  PhiMuPHist   ->SetMinimum(0); 
                  PhiMuPHist   ->Draw();
                  PhiGenMuPHist->SetLineColor(4);
                  PhiGenMuPHist->SetLineStyle(2);
                  PhiGenMuPHist->Draw("same");
  canvas->cd(6);  PhiMuMHist   ->SetFillColor(5);
                  PhiMuMHist   ->SetMinimum(0); 
                  PhiMuMHist   ->Draw();  
                  PhiGenMuMHist->SetLineColor(4);
                  PhiGenMuMHist->SetLineStyle(2); 
                  PhiGenMuMHist->Draw("same"); 
  canvas->cd(7);  DilepMassHist   ->SetFillColor(5);
                  DilepMassHist   ->SetMinimum(0); 
                  DilepMassHist   ->Draw();  
                  DilepMassGenHist->SetLineColor(4);
                  DilepMassGenHist->SetLineStyle(2); 
                  DilepMassGenHist->Draw("same"); 		  
  canvas->cd(); canvas->Update();
       
  canvas->Clear(); canvas->Divide(2,3);
  canvas->cd(1);  PtBJetHist  ->SetFillColor(5);  
                  PtBJetHist  ->Draw();
                  PtGenBHist  ->SetLineColor(4);
                  PtGenBHist  ->SetLineStyle(2);
                  PtGenBHist  ->Draw("same");
  canvas->cd(2);  PtBbJetHist ->SetFillColor(5);  
                  PtBbJetHist ->Draw();
                  PtGenBbHist ->SetLineColor(4);
                  PtGenBbHist ->SetLineStyle(2);
                  PtGenBbHist ->Draw("same");
  canvas->cd(3);  EtaBJetHist ->SetFillColor(5);  
                  EtaBJetHist ->Draw();
                  EtaGenBHist ->SetLineColor(4);
                  EtaGenBHist ->SetLineStyle(2);
                  EtaGenBHist ->Draw("same");
  canvas->cd(4);  EtaBbJetHist->SetFillColor(5);  
                  EtaBbJetHist->Draw(); 
                  EtaGenBbHist->SetLineColor(4);
                  EtaGenBbHist->SetLineStyle(2);
                  EtaGenBbHist->Draw("same");
  canvas->cd(5);  PhiBJetHist ->SetFillColor(5);
                  PhiBJetHist ->SetMinimum(0);
                  PhiBJetHist ->Draw();
                  PhiGenBHist ->SetLineColor(4);
                  PhiGenBHist ->SetLineStyle(2);
                  PhiGenBHist ->Draw("same");
  canvas->cd(6);  PhiBbJetHist->SetFillColor(5);
                  PhiBbJetHist->SetMinimum(0);
                  PhiBbJetHist->Draw(); 
                  PhiGenBbHist->SetLineColor(4);
                  PhiGenBbHist->SetLineStyle(2);
                  PhiGenBbHist->Draw("same");  
  canvas->cd(); canvas->Update();   
  
  canvas->Clear(); canvas->Divide(1,2);
  canvas->cd(1);  PtMetHist    ->SetFillColor(5);  
                  PtMetHist    ->Draw();
                  PtGenMetHist ->SetLineColor(4);
		  PtGenMetHist ->SetLineStyle(2);
		  PtGenMetHist ->SetLineWidth(2);
                  PtGenMetHist ->Draw("same");      
  canvas->cd(2);  PhiMetHist   ->SetFillColor(5);
                  PhiMetHist   ->SetMinimum(0);
                  PhiMetHist   ->Draw();
                  PhiGenMetHist->SetLineColor(4);
		  PhiGenMetHist->SetLineStyle(2);
		  PhiGenMetHist->SetLineWidth(2);
                  PhiGenMetHist->Draw("same");      
  canvas->cd(); canvas->Update();     
  
  canvas->Clear(); canvas->Divide(3,4);
  canvas->cd( 1);  maxEtInEmTowersHist   ->Draw();
  canvas->cd( 2);  maxEtInHadTowersHist  ->Draw();
  canvas->cd( 4);  etFractionHadronicHist->Draw();
  canvas->cd( 5);  etFractionEmHist      ->Draw();
  canvas->cd( 6);  hadEtInHOHist         ->Draw();
  canvas->cd( 7);  hadEtInHBHist         ->Draw();
  canvas->cd( 8);  hadEtInHEHist         ->Draw();
  canvas->cd( 9);  hadEtInHFHist         ->Draw();
  canvas->cd(10);  emEtInEBHist          ->Draw();
  canvas->cd(11);  emEtInEEHist          ->Draw();  
  canvas->cd(12);  emEtInHFHist          ->Draw();   
  canvas->Update();     
  canvas->Close();  
  ps.Close(); 
}

double invMass(TLorentzVector a, TLorentzVector b) {
  return sqrt((a+b)*(a+b));
}
