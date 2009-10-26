#include "DataFormats/Math/interface/deltaR.h"
#include "TopAnalysis/TopAnalyzer/plugins/TagAndProbeAnalyzer.h"

TagAndProbeAnalyzer::TagAndProbeAnalyzer(const edm::ParameterSet& iConfig):
  muonTag_( iConfig.getParameter<edm::InputTag> ("ProbeMuonTag") ),
  elecTag_( iConfig.getParameter<edm::InputTag> ("ProbeElectronTag") ),
  //muonMCTag_( iConfig.getParameter<edm::InputTag> ("MCMuonTestTag") ),
  jetTag_( iConfig.getParameter<edm::InputTag> ("JetTag") ),
  metTag_( iConfig.getParameter<edm::InputTag> ("METTag") ),
  genTag_( iConfig.getParameter<edm::InputTag> ("GenTag") ),
  trackTag_( iConfig.getParameter<edm::InputTag> ("TrackTag") ),
  //first Variable
  numberOfBins_( iConfig.getParameter<int> ("NumberOfBins_1") ),
  variable_( iConfig.getParameter<std::string> ("Variable_1") ),
  equiBins_( iConfig.getParameter<bool> ("EquidistantBins_1") ),
  minValue_( iConfig.getParameter<double> ("MinVariableValue_1") ),
  maxValue_( iConfig.getParameter<double> ("MaxVariableValue_1") ),
  //second variable
  numberOfBins_2_( iConfig.getParameter<int> ("NumberOfBins_2") ),
  variable_2_( iConfig.getParameter<std::string> ("Variable_2") ),
  equiBins_2_( iConfig.getParameter<bool> ("EquidistantBins_2") ),
  minValue_2_( iConfig.getParameter<double> ("MinVariableValue_2") ),
  maxValue_2_( iConfig.getParameter<double> ("MaxVariableValue_2") ),

  matchingRadius_(iConfig.getParameter<double> ("MCmatchingRadius") ),
  staTrackMatchingRadius_(iConfig.getParameter<double> ("StaTrackMatchingRadius") ),
  getIsolationEff_( iConfig.getParameter<bool> ("getIsolationEff") ),
  getElectronIsolationEff_( iConfig.getParameter<bool> ("getElectronIsolationEff") ),
  getGlobalPromtTightEff_( iConfig.getParameter<bool> ("getGlobalPromtTightEff") ),
  getGlobalEff_( iConfig.getParameter<bool> ("getGlobalEff") ),
  getStandaloneEff_( iConfig.getParameter<bool> ("getStandAloneEff") )
 
{ 
  
   //now do what ever initialization is needed
  if (!binnedEff_.empty()) binnedEff_.clear();
  if (!binnedEff2D_.empty()) binnedEff2D_.clear();
  if (!binnedMCEff_.empty()) binnedMCEff_.clear();
  if (!binnedMCEff2D_.empty()) binnedMCEff2D_.clear();
 

  // hEff = new TH2F ("Efficiency","Efficiency",10,1,11,100,50,100); 
 
}


TagAndProbeAnalyzer::~TagAndProbeAnalyzer()
{
}

void
TagAndProbeAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
 
 edm::Service<TFileService> fs; 
  //read inpu collection
 
   edm::Handle<reco::GenParticleCollection> genParticles;
   if  ( !iEvent.getByLabel(genTag_, genParticles) ){
     edm::LogWarning("Z") << "Could not extract MET cands with input tag " 
		     << genTag_;
   }
   else iEvent.getByLabel(genTag_, genParticles) ; 
   //goodEvent = false;
   //std::cout<<probemuons->size()<<std::endl;
   //use std::map to associate t&p efficiency ordered in bins of test variable (pT,jet muliplicity,etc.)
   
  hEff = new TH1F("MCEfficiency","MC Efficiency",numberOfBins_,minValue_,maxValue_);
  hEff2D = new TH2F("Efficiency2D","Efficiency2D",numberOfBins_,minValue_,maxValue_,numberOfBins_2_,minValue_2_,maxValue_2_); 
  
   int bin = 0;
   int bin2D = 0;
   //test isolation efficiency
   // probe criteria should be including exactly one probe muon, so loop over muons is obsolete
   if(getElectronIsolationEff_){

     edm::Handle <edm::View<pat::Electron> >probeelecs;
     if ( !iEvent.getByLabel(elecTag_,probeelecs) ) {
       edm::LogWarning("Z") << "Could not extract tag electron cands with input tag " 
		       << elecTag_;
     }
     else iEvent.getByLabel(elecTag_,probeelecs) ;

     for (edm::View<pat::Electron>::const_iterator elec= probeelecs->begin(); elec!=probeelecs->end();++elec){
       //only count event if exactly one probe muon is found
       //then calculate bin and count number of total events +1
       
       bin = hEff->FindBin(GetVariable(iEvent,elec->eta(),elec->phi(),elec->pt(),variable_)); 
       bin2D = hEff2D->FindBin(GetVariable(iEvent,elec->eta(),elec->phi(),elec->pt(),variable_),GetVariable(iEvent,elec->eta(),elec->phi(),elec->pt(),variable_2_)); 
       
       if( (elec->trackIso()+elec->ecalIso()+elec->hcalIso())/elec->pt() > 0.5 )
	 {
	 ++binnedEff_[bin].failed;
	 ++binnedEff2D_[bin2D].failed; 
       }
       else {
	 ++binnedEff_[bin].passed;
	 ++binnedEff2D_[bin2D].passed;
       }
       ++binnedEff_[bin].total;
       ++binnedEff2D_[bin2D].total;
     }
   }//end electron isolation
   

   else{//muon
     edm::Handle <edm::View<pat::Muon> >probemuons;
     if ( !iEvent.getByLabel(muonTag_,probemuons) ) {
       edm::LogWarning("Z") << "Could not extract tag muon cands with input tag " 
		       << muonTag_;
     }
     else iEvent.getByLabel(muonTag_,probemuons) ;
     
     for (edm::View<pat::Muon>::const_iterator muon= probemuons->begin(); muon!=probemuons->end();++muon){
       //only count event if exactly one probe muon is found
       //then calculate bin and count number of total events +1
       
       bin = hEff->FindBin(GetVariable(iEvent,probemuons->begin()->eta(),probemuons->begin()->phi(),probemuons->begin()->pt(),variable_)); 
       bin2D = hEff2D->FindBin(GetVariable(iEvent,probemuons->begin()->eta(),probemuons->begin()->phi(),probemuons->begin()->pt(),variable_),GetVariable(iEvent,probemuons->begin()->eta(),probemuons->begin()->phi(),probemuons->begin()->pt(),variable_2_));                 
       /*
	 bin = this->GetHistoBin(iEvent,probemuons->begin()->eta(),probemuons->begin()->phi(),probemuons->begin()->pt(),numberOfBins_,variable_,minValue_,maxValue_);
	 bin2D = this->GetHistoBin2D(iEvent,probemuons->begin()->eta(),probemuons->begin()->phi(),probemuons->begin()->pt());
       */
       
       
     
       if (getIsolationEff_){
	 const reco::MuonIsolation muonIso = muon->isolationR03();
	 if ( (muonIso.emEt+ muonIso.hadEt +muonIso.sumPt )/muon->pt() < 0.1 )  {
	   ++binnedEff_[bin].passed;
	   ++binnedEff2D_[bin2D].passed;
	 }
	 else {
	   ++binnedEff_[bin].failed;
	   ++binnedEff2D_[bin2D].failed;
	 }
	 ++binnedEff_[bin].total; 
	 ++binnedEff2D_[bin2D].total; 
       }
       else if (getGlobalPromtTightEff_){
	 if ( muon->isGood("GlobalMuonPromptTight") )  {
	   ++binnedEff_[bin].passed;
	   ++binnedEff2D_[bin2D].passed;
	 }
	 
	 else  {
	   ++binnedEff_[bin].failed; 
	   ++binnedEff2D_[bin2D].failed;
	 }
	 ++binnedEff_[bin].total;
	 ++binnedEff2D_[bin2D].total; 
       }
       else if (getGlobalEff_){
	 if ( muon->isGlobalMuon() ) {
	   ++binnedEff_[bin].passed;
	   ++binnedEff2D_[bin2D].passed;
	 }
	 else  {
	   ++binnedEff_[bin].failed; 
	   ++binnedEff2D_[bin2D].failed;
	 }
	 ++binnedEff_[bin].total;
	 ++binnedEff2D_[bin2D].total;
       }
     }//end of probe muon loop
     
     reco::Track IsoTrack; //define here for reuse in MC eff
     bool IsIsoTrack = false;
     bool onlyOneProbe = true;
     
     if (getStandaloneEff_){
       /*
	 edm::Handle <pat::GenericParticle> probetracks;
	 if ( !iEvent.getByLabel(trackTag_,probetracks) ) {
	 edm::LogWarning("Z") << "Could not extract tag track cands with input tag " 
	 << trackTag_;
	 }*/
       edm::Handle <reco::TrackCollection> probetracks;
       if ( !iEvent.getByLabel(trackTag_,probetracks) ) {
	 edm::LogWarning("Z") << "Could not extract tag track cands with input tag " 
			 << trackTag_;
       }
       double dR = staTrackMatchingRadius_;
       pat::Muon StaMuonmatched;
       bool IsStaMuonmatched = false;
       //probe criteria should be including exactly one isolated track, so loop over tracks is obsolete
       //BUT here loop over all muons is important, input muon probe here as test collection
       //configuration in cfg.py has to be different for getStandaloneEff_
       //for ( pat::GenericParticle::const_iterator track= probetracks->begin(); track!=probetracks->end();++track){
       for ( reco::TrackCollection::const_iterator track= probetracks->begin(); track!=probetracks->end();++track){
	 double relIso = 0;
	 if(fabs(track->eta()) > 2.1)  continue;
	 for ( reco::TrackCollection::const_iterator track1= probetracks->begin(); track1!=probetracks->end();++track1){
	   if(deltaR(track->eta(),track->phi(),track1->eta(),track1->phi()) < 0.3)    relIso += track1->pt()/track->pt();
	 }
	 if( relIso < 1.05){  //same track is also counted therefore this 1+rel iso
	   if(!IsIsoTrack)   {
	     IsoTrack = *track; //check for only one (!)  isolated track       
	     IsIsoTrack = true;
	   }
	   else onlyOneProbe = false;
	 }
       }
       if( IsIsoTrack ){//  && onlyOneProbe){
	 
	 //this time muon collection is a test collection to track probe collection
	 //thus looping over all possible muon candidates is necesarry,possible: muon->size()>1
	 for (edm::View<pat::Muon>::const_iterator muon= probemuons->begin(); muon!=probemuons->end();++muon){
	   //	 double tmpdR =  deltaR(track->eta(),track->phi(), muon->eta(), muon->phi());
	   double tmpdR =  deltaR(IsoTrack.eta(),IsoTrack.phi(), muon->eta(), muon->phi());
	   if (tmpdR<dR){
	     dR =tmpdR;
	     StaMuonmatched= *muon;
	     IsStaMuonmatched = true;
	     std::cout<<"DR: "<<dR<<"  "<<IsStaMuonmatched<<std::endl;
	   }
	 }//end of muon loop
	 bin = hEff->FindBin(GetVariable(iEvent,IsoTrack.eta(),IsoTrack.phi(),IsoTrack.pt(),variable_)); 
	 bin2D = hEff2D->FindBin(GetVariable(iEvent,IsoTrack.eta(),IsoTrack.phi(),IsoTrack.pt(),variable_),GetVariable(iEvent,IsoTrack.eta(),IsoTrack.phi(),IsoTrack.pt(),variable_2_));   
	 /*
	   bin = this->GetHistoBin(iEvent,IsoTrack.eta(),IsoTrack.phi(),IsoTrack.pt(),numberOfBins_,variable_,minValue_,maxValue_);
	   bin2D = this->GetHistoBin2D(iEvent,probemuons->begin()->eta(),probemuons->begin()->phi(),probemuons->begin()->pt());
	 */
	 //total number of events is counted for each probe track
	 ++binnedEff_[bin].total;
	 ++binnedEff2D_[bin2D].total;
	 if (IsStaMuonmatched) {
	   ++binnedEff_[bin].passed;
	   ++binnedEff2D_[bin2D].passed;
	 }
	 else  {
	   ++binnedEff_[bin].failed; 
	   ++binnedEff2D_[bin2D].failed; 
	 }
	 
       }//end of if !StaMuonmatched
     }//end of if getStandaloneEff_
     
   
     ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
     //for reco efficiencies MC efficiency is calculatd as well
     //////////////////////////////////////////////////////////////////////////////////////////////////////////////
     
     if(getGlobalPromtTightEff_||getGlobalEff_ || getIsolationEff_){
       
       double dR = matchingRadius_;
       reco::GenParticle matchedmuon;
       bool Ismatchedmuon = false;
       
       for(reco::GenParticleCollection::const_iterator cand = genParticles->begin(); cand!=genParticles->end(); ++cand) {
	 if(abs(cand->pdgId())!=13) continue; 
	 double tmpdR =  deltaR(cand->eta(),cand->phi(), probemuons->begin()->eta(), probemuons->begin()->phi());
	 if (tmpdR<dR){
	   dR =tmpdR;
	   matchedmuon= *(cand);
	   Ismatchedmuon = true;
	 }
       }
       
       
       if (Ismatchedmuon){
	 int MCbin = hEff->FindBin(GetVariable(iEvent, matchedmuon.eta(),matchedmuon.phi(),matchedmuon.pt(),variable_)); 
	 int MCbin2D = hEff2D->FindBin(GetVariable(iEvent, matchedmuon.eta(),matchedmuon.phi(),matchedmuon.pt(),variable_),GetVariable(iEvent, matchedmuon.eta(),matchedmuon.phi(),matchedmuon.pt(),variable_2_)); 
	 /*
	   int MCbin= GetHistoBin(iEvent, matchedmuon.eta(),matchedmuon.phi(),matchedmuon.pt(),numberOfBins_,variable_,minValue_,maxValue_);
	   int MCbin2D= GetHistoBin2D(iEvent, matchedmuon.eta(),matchedmuon.phi(),matchedmuon.pt());
	 */
	 if (getGlobalPromtTightEff_){
	   if (  probemuons->begin()->isGood("GlobalMuonPromptTight") ) {
	     ++binnedMCEff_[MCbin].passed;
	     ++binnedMCEff2D_[MCbin2D].passed;
	   }
	   else  {
	     ++binnedMCEff_[MCbin].failed;
	     ++binnedMCEff2D_[MCbin2D].failed;
	   }
	 }
	 else if (getGlobalEff_){
	   if (  probemuons->begin()->isGlobalMuon() ) {
	     ++binnedMCEff_[MCbin].passed;
	     ++binnedMCEff2D_[MCbin2D].passed;
	   }
	   else  {
	     ++binnedMCEff_[MCbin].failed;
	     ++binnedMCEff2D_[MCbin2D].failed; 
	   }
	 }
	 
	 else if (getIsolationEff_){
	   const reco::MuonIsolation muonIso = probemuons->begin()->isolationR03();
	   if ( (muonIso.emEt+ muonIso.hadEt +muonIso.sumPt )/probemuons->begin()->pt() < 0.1 )  {
	     ++binnedMCEff_[MCbin].passed;
	     ++binnedMCEff2D_[MCbin2D].passed;
	   }
	   else {
	     ++binnedMCEff_[MCbin].failed;
	     ++binnedMCEff2D_[MCbin2D].failed; 
	   }
	 }
	 ++binnedMCEff_[MCbin].total;
	 ++binnedMCEff2D_[MCbin2D].total;
       }
     }
     
     //STA eff requires probe track matching
     
     else if(getStandaloneEff_  &&  IsIsoTrack ){// && onlyOneProbe){
       /*
	 edm::Handle <pat::GenericParticle> probetracks;
	 if ( !iEvent.getByLabel(trackTag_,probetracks) ) {
	 edm::LogWarning("Z") << "Could not extract tag track cands with input tag " 
	 << trackTag_;
	 }*/
       /* edm::Handle <reco::TrackCollection> probetracks;
	  if ( !iEvent.getByLabel(trackTag_,probetracks) ) {
	  edm::LogWarning("Z") << "Could not extract tag track cands with input tag " 
	  << trackTag_;
	  }*/
       double dR = matchingRadius_;
       reco::GenParticle matchedtrack;
       bool Ismatchedtrack = false;
       
       for(reco::GenParticleCollection::const_iterator cand = genParticles->begin(); cand!=genParticles->end(); ++cand) {
	 if(abs(cand->pdgId())!=13) continue; 
	 //double tmpdR =  deltaR(cand->eta(),cand->phi(), probetracks->begin()->eta(), probetracks->begin()->phi());
	 double tmpdR =  deltaR(cand->eta(),cand->phi(), IsoTrack.eta(),  IsoTrack.phi());
	 if (tmpdR<dR){
	   dR =tmpdR;
	   matchedtrack= *(cand);
	   Ismatchedtrack = true;
	 }
       } 
       if(Ismatchedtrack){
	 pat::Muon StaMuonmatched;
	 bool IsStaMuonmatched = false;
	 dR = staTrackMatchingRadius_;
	 //this time muon collection is a test collection to track probe collection
	 //thus looping over all possible muon candidates is necesarry,possible: muon->size()>1
	 for (edm::View<pat::Muon>::const_iterator muon= probemuons->begin(); muon!=probemuons->end();++muon){
	   //	   double tmpdR =  deltaR(probetracks->begin()->eta(),probetracks->begin()->phi(), muon->eta(), muon->phi());
	   double tmpdR =  deltaR(IsoTrack.eta(),IsoTrack.phi(), muon->eta(), muon->phi());
	   if (tmpdR<dR){
	     dR =tmpdR;
	     StaMuonmatched=(*muon);
	     IsStaMuonmatched = true;
	   }
	 }//end of muon loop
	 
	 int MCbin = hEff->FindBin(GetVariable(iEvent,IsoTrack.eta(),IsoTrack.phi(),IsoTrack.pt(),variable_)); 
	 int MCbin2D = hEff2D->FindBin(GetVariable(iEvent,IsoTrack.eta(),IsoTrack.phi(),IsoTrack.pt(),variable_),GetVariable(iEvent,IsoTrack.eta(),IsoTrack.phi(),IsoTrack.pt(),variable_2_));  
	 /*
	   int MCbin = this->GetHistoBin(iEvent,IsoTrack.eta(),IsoTrack.phi(),IsoTrack.pt(),numberOfBins_,variable_,minValue_,maxValue_);
	   int MCbin2D = this->GetHistoBin2D(iEvent,IsoTrack.eta(),IsoTrack.phi(),IsoTrack.pt());
	 */
	 //total number of events is counted for each probe track
	 ++binnedMCEff_[bin].total;
	 ++binnedMCEff2D_[bin2D].total;
	 if ( IsStaMuonmatched ) {
	   ++binnedMCEff_[MCbin].passed;
	   ++binnedMCEff2D_[MCbin2D].passed;
	 }
	 else {
	   ++binnedMCEff_[MCbin].failed; 
	   ++binnedMCEff2D_[MCbin2D].failed; 
	 }
	 std::cout<<"MC  : "<< ( IsStaMuonmatched)<<std::endl;
       }
     }//end of if getStandaloneEff_
   }//end of muon
   delete hEff;
   delete hEff2D;
}

// ------------ method called once each job just before starting event loop  ------------
void 
TagAndProbeAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TagAndProbeAnalyzer::endJob() {
  //to be able to run the analyzer in parallel mode
  //save efficiency variables in tree to be able to merge these
  //calculate ans plot the efficiency using test/PlotEfficiency.C
  edm::Service<TFileService> fs; 
  TTree *tree = fs->make<TTree>("EfficiencyVariables","EfficiencyVariables");

  int tmpbin = 0;
  unsigned int tmptotal = 0;
  unsigned int tmppassed = 0;
  unsigned int tmpfailed = 0;
  double stepWidth = (maxValue_ - minValue_) / numberOfBins_;
  TString variableName = variable_.c_str();
  //char* tmpvar = const_cast< char*>(variableName.Data());
  tree->Branch("variableBin",& tmpbin,"variableBin/I" ); // address of pointer!
  tree->Branch("BinWidth",&stepWidth ,"BinWidth/D" );
  tree->Branch("totalEventsPerBin",& tmptotal,"totalEventsPerBin/i" );
  tree->Branch("passedEventsPerBin",& tmppassed, "passedEventsPerBin/i" );
  tree->Branch("failedEventsPerBin",& tmpfailed, "failedEventsPerBin/i" );
  tree->Branch("variableName",& variableName,"variableName/C" ); // address of pointer!

  hEff=fs->make<TH1F>("Efficiency","Efficiency",numberOfBins_,minValue_,maxValue_); 
  hEff->SetMarkerStyle(1);

  hMCEff = fs->make<TH1F>("MCEfficiency","MC Efficiency",numberOfBins_,minValue_,maxValue_);
  hMCEff->SetMarkerStyle(1);
  //2D:
  hEff2D=fs->make<TH2F>("Efficiency2D","Efficiency2D",numberOfBins_,minValue_,maxValue_,numberOfBins_2_,minValue_2_,maxValue_2_); 
  hEff2D->SetMarkerStyle(1);

  hMCEff2D = fs->make<TH2F>("MCEfficiency2D","MC Efficiency2D",numberOfBins_,minValue_,maxValue_,numberOfBins_2_,minValue_2_,maxValue_2_);
  hMCEff2D->SetMarkerStyle(1);


  //std::map<int,TagAndProbeAnalyzer::EffCalculator_>::iterator it = 0;
    
  //std::map<int,TagAndProbeAnalyzer::EffCalculator_>::iterator last = binnedEff_.end();--last ;//last element

  for(int count = 1; count < numberOfBins_; ++count){
    tmpbin = count;
    tmptotal = 0;
    tmppassed = 0;
    tmpfailed = 0;
    //double HistValue = minValue_ + count * stepWidth + 0.0001;
    hEff->SetBinContent(count,binnedEff_[count].getEff());
    hEff->SetBinError(count,binnedEff_[count].getErr());
    std::cout<<"Efficiency in bin: "<<count<<" :"<<binnedEff_[count].getEff()<<std::endl;
      
    tmpbin = count;
    tmptotal = binnedEff_[count].total;
    tmppassed = binnedEff_[count].passed;
    tmpfailed = binnedEff_[count].failed;
    tree->Fill();

  //MC:

    hMCEff->SetBinContent(count,binnedMCEff_[count].getEff());
    hMCEff->SetBinError(count,binnedMCEff_[count].getErr());
    std::cout<<"MC Efficiency in bin: "<<count<<" :"<<binnedMCEff_[count].getEff()<<std::endl;
  }
  //2D:
  for(int count = 1; count < numberOfBins_ * numberOfBins_2_ ; ++count){
    //double HistValue = minValue_ + count * stepWidth + 0.0001;
    hEff2D->SetBinContent(count,binnedEff2D_[count].getEff());
    hEff2D->SetBinError(count,binnedEff2D_[count].getErr());
    std::cout<<"Efficiency in 2D-bin: "<<count<<" :"<<binnedEff2D_[count].getEff()<<std::endl;
    
    //MC:
    
    hMCEff2D->SetBinContent(count,binnedMCEff2D_[count].getEff());
    hMCEff2D->SetBinError(count,binnedMCEff2D_[count].getErr());
    std::cout<<"MC Efficiency in 2D-bin: "<<count<<" :"<<binnedMCEff2D_[count].getEff()<<std::endl;
  }



}



  double TagAndProbeAnalyzer::GetVariable(const edm::Event& iEvent, double probeMuonEta,double probeMuonPhi,double probeMuonPt,std::string VarName)
{
  edm::Handle <edm::View<pat::Jet> >jets;
  if ( !iEvent.getByLabel(jetTag_,jets) ) {
    edm::LogWarning("Z") << "Could not extract jet cands with input tag " 
		    << jetTag_;
  }
  edm::Handle <edm::View<pat::MET> >mets;
  if ( !iEvent.getByLabel(metTag_,mets) ) {
    edm::LogWarning("Z") << "Could not extract MET cands with input tag " 
		    << metTag_;
  }
  else iEvent.getByLabel(metTag_,mets) ;
   double PtClosestJet = 0;
  double Var = 0;
  //double VarStep = (MaxV -  MinV) / NoBins; 
  if(VarName == "JetMult")
    {
      for (edm::View<pat::Jet>::const_iterator jet= jets->begin(); jet!=jets->end();++jet){
	if (jet->pt()>20) ++Var;
      }
    }
 
  
  if(VarName == "Eta")  Var = probeMuonEta;//probeMuon.eta();
  
  if(VarName == "DeltaR")
    {
      double minDR = 1000;
      double DR = 1000;
     
       for (edm::View<pat::Jet>::const_iterator jet= jets->begin(); jet!=jets->end();++jet){
	 if (jet->pt() > 20)   DR = deltaR( probeMuonEta,probeMuonPhi, jet->eta(), jet->phi());//probeMuon.eta(), probeMuon.phi(), jet->eta(), jet->phi());
	 if(DR < minDR) {
	   minDR = DR;
	   PtClosestJet = jet->pt();
	 }
       }
       Var = minDR;
    }

  if(VarName == "Pt")  {
    double minDR = 1000;
    double DR = 1000;
    for (edm::View<pat::Jet>::const_iterator jet= jets->begin(); jet!=jets->end();++jet){
	 if (jet->pt() > 20)   DR = deltaR( probeMuonEta,probeMuonPhi, jet->eta(), jet->phi());//probeMuon.eta(), probeMuon.phi(), jet->eta(), jet->phi());
	 if(DR < minDR) {
	   minDR = DR;
	   PtClosestJet = jet->pt();
	 }
    }
    Var = probeMuonPt/PtClosestJet;//probeMuon.pt();
    std::cout<<"Variable2= 2d "<<VarName<<" "<<Var<<std::endl;
  }
  if(VarName == "SumEt")
    {
      Var = mets->begin()->corSumEt();
    }
  return Var;
}


/*

 
int 
  //TagAndProbeAnalyzer::GetHistoBin(const edm::Event& iEvent,const pat::Muon &probeMuon) {
TagAndProbeAnalyzer::GetHistoBin(const edm::Event& iEvent,double probeMuonEta ,double probeMuonPhi, double probeMuonPt,    int NoBins, std::string VarName, double MinV,double MaxV) {
 edm::Handle <edm::View<pat::Jet> >jets;
   if ( !iEvent.getByLabel(jetTag_,jets) ) {
     edm::LogWarning("Z") << "Could not extract jet cands with input tag " 
		     << jetTag_;
   }
   edm::Handle <edm::View<pat::MET> >mets;
   if ( !iEvent.getByLabel(metTag_,mets) ) {
     edm::LogWarning("Z") << "Could not extract MET cands with input tag " 
		     << metTag_;
   }
   else iEvent.getByLabel(metTag_,mets) ;

   double Var = 0;
   double VarStep = (MaxV -  MinV) / NoBins; 
   if(VarName == "JetMult")
     {
       for (edm::View<pat::Jet>::const_iterator jet= jets->begin(); jet!=jets->end();++jet){
	 if (jet->pt()>20) ++Var;
       }
     }
   if(VarName == "Pt")  Var = probeMuonPt;//probeMuon.pt();
     
   if(VarName == "Eta")  Var = probeMuonEta;//probeMuon.eta();

   if(VarName == "DeltaR")
     {
       double minDR = 1000;
       double DR = 1000;
       for (edm::View<pat::Jet>::const_iterator jet= jets->begin(); jet!=jets->end();++jet){
	 if (jet->pt() > 20)   DR = deltaR( probeMuonEta,probeMuonPhi, jet->eta(), jet->phi());//probeMuon.eta(), probeMuon.phi(), jet->eta(), jet->phi());
	 if(DR < minDR) minDR = DR;
       }
       Var = minDR;
     }
   if(VarName == "SumEt")
     {
       Var = mets->begin()->corSumEt();
     }


   hEff= new TH1F("Efficiency","Efficiency",numberOfBins_,minValue_,maxValue_);
   hEff2D = new TH2F("Efficiency2D","Efficiency2D",numberOfBins_,minValue_,maxValue_,numberOfBins_2_,minValue_2_,maxValue_2_); 

   int bin = 0;

   delete hEff;
   delete hEff2D;


   for(double VarValue =MinV; VarValue < MaxV; VarValue += VarStep)
     { 
       if(VarValue > Var) continue;
       bin++;
     }
   return bin;
}


int TagAndProbeAnalyzer::GetHistoBin2D(const edm::Event& iEvent,double probeMuonEta ,double probeMuonPhi, double probeMuonPt){
  int bin2D = 0;
  int bin1 = GetHistoBin(iEvent,probeMuonEta,probeMuonPhi,probeMuonPt,numberOfBins_,variable_,minValue_,maxValue_);
  int bin2 = GetHistoBin(iEvent,probeMuonEta,probeMuonPhi,probeMuonPt,numberOfBins_2_,variable_2_,minValue_2_,maxValue_2_ );
  bin2D = bin1 * numberOfBins_2_ + bin2;

  return bin2D;
}
*/

#include "FWCore/Framework/interface/MakerMacros.h"
//define this as a plug-in
DEFINE_FWK_MODULE(TagAndProbeAnalyzer);
