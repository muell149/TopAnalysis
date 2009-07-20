#include "TopAnalysis/TopAnalyzer/interface/BSMKinematic.h"

/// constructor for FWLite analyzer
BSMKinematic::BSMKinematic(const edm::ParameterSet& cfg,int nMuons): 
  fwLite_(true ), jets_(),
  metSource_       ( cfg.getParameter<edm::InputTag>("metSource")),
  nMuons_(nMuons)
{ 
}

/// constructor for full FW analyzer
BSMKinematic::BSMKinematic(const edm::ParameterSet& cfg):
  fwLite_(false), jets_  ( cfg.getParameter<edm::InputTag>( "jets" )),
  metSource_       ( cfg.getParameter<edm::InputTag>("metSource")),
  nMuons_( cfg.getParameter<int>( "nMuons" ) )  
{
}

/// fill interface for full FW analyzer
void
BSMKinematic::fill(const edm::Event& evt, const std::vector<pat::Muon>& muons, const double& weight=1.)
{
  if(muons.begin()==muons.end()) return;
  
  edm::Handle<std::vector<pat::MET> > mets;
  evt.getByLabel(metSource_, mets);
  edm::Handle<std::vector<pat::Jet> > jets; 
  evt.getByLabel(jets_, jets);

  fill(evt,*jets, muons, *mets, weight);
}

/// fill interface for FWLite analyzer
void
BSMKinematic::fill(const edm::Event& evt,const std::vector<pat::Jet>& jets, 
		    const std::vector<pat::Muon>& muons, const std::vector<pat::MET>& mets,  const double& weight=1.)
{
  Missing_energy_->Fill( (mets)[0].et(), weight);
  
  //--------------------------------------------------
  //fill histogramms for angles between muons and MET
  //--------------------------------------------------
//   double angle_mu1mu2;
//   double angle_mu1MET;
//   double angle_mu2MET



//   angle_mu1mu2 = angle(muons[0], muons[1]);
//   angle_mu1MET = angle(muons[0], (mets)[0]);
//   angle_mu1mu2_->Fill(angle_mu1mu2, weight);
//   std::cout << "angle_mu1mu2" << std::endl;
//   angle_mu1MET_->Fill(angle_mu1MET, weight);

  std::cout << "AHA" << std::endl;
//   if(muons.size() > 1)
//     {
//       std::cout << "AHA1" << std::endl;
//       angle_mu2MET = angle(muons[1], (mets)[0]);
//       angle_mu2MET_->Fill(angle_mu2MET, weight);
//     }

  std::cout << "AHA2" << std::endl;

  unsigned int idx=0;
  //fill histogramms for all muons
  for(std::vector<pat::Muon>::const_iterator muon=muons.begin();muon!=muons.end();++muon,++idx){

    //---------------------------------------------
    // basic kinematics
    //---------------------------------------------
    allEn_ ->Fill( muon->energy(), weight );
    allPt_ ->Fill( muon->pt(),     weight );   
 
    allEta_->Fill( muon->eta(),    weight );
    allPhi_->Fill( muon->phi(),    weight );

    if (idx < en_.size()  ) en_ [idx]->Fill ( muon->energy(), weight );
    if (idx < pt_.size()  ) pt_ [idx]->Fill ( muon->pt(),     weight );    
    if (idx < eta_.size() ) eta_[idx]->Fill ( muon->eta(),    weight );
    if (idx < phi_.size() ) phi_[idx]->Fill ( muon->phi(),    weight );

    if (muons.size() > 1 && idx == 0 ) DeltaPhi_->Fill ( muons[0].phi() - muons[1].phi(), weight );
    
    //---------------------------------------------
    // jet isolation
    //---------------------------------------------
    double minDR   =-1.;
    double minDR_5 =-1.;
    double minDR_10=-1.;
    double minDR_15=-1.;
    double minDR_20=-1.;
    double minDR_25=-1.;
    double minDR_30=-1.;
    double minDR_35=-1.;
    double minDR_40=-1.;

    int jdx=0;
    for(std::vector<pat::Jet>::const_iterator jet = jets.begin(); 
	jet!=jets.end(); ++jet) {
      double dR=deltaR(muon->eta(), muon->phi(), jet->eta(), jet->phi());
      if( (minDR   <0 || dR<minDR   ) )                 minDR   =dR;
      if( (minDR_5 <0 || dR<minDR_5 ) && jet->pt()>5  ) minDR_5 =dR;
      if( (minDR_10<0 || dR<minDR_10) && jet->pt()>10 ) minDR_10=dR;
      if( (minDR_15<0 || dR<minDR_15) && jet->pt()>15 ) minDR_15=dR;
      if( (minDR_20<0 || dR<minDR_20) && jet->pt()>20 ) minDR_20=dR;
      if( (minDR_25<0 || dR<minDR_25) && jet->pt()>25 ) minDR_25=dR;
      if( (minDR_30<0 || dR<minDR_30) && jet->pt()>30 ) minDR_30=dR;
      if( (minDR_35<0 || dR<minDR_35) && jet->pt()>35 ) minDR_35=dR;
      if( (minDR_40<0 || dR<minDR_40) && jet->pt()>40 ) minDR_40=dR;
      //std::cout << "AHA" << std::endl;
      if(idx < 4 && jdx < 4) dR_muon_jet_[idx][jdx]->Fill(dR, weight);
     ++jdx;
    }
    if( minDR   >=0 ) isoJet_  ->Fill( minDR   , weight );
    if( minDR_5 >=0 ) isoJet5_ ->Fill( minDR_5 , weight );
    if( minDR_10>=0 ) isoJet10_->Fill( minDR_10, weight );
    if( minDR_15>=0 ) isoJet15_->Fill( minDR_15, weight );
    if( minDR_20>=0 ) isoJet20_->Fill( minDR_20, weight );
    if( minDR_25>=0 ) isoJet25_->Fill( minDR_25, weight );
    if( minDR_30>=0 ) isoJet30_->Fill( minDR_30, weight );
    if( minDR_35>=0 ) isoJet35_->Fill( minDR_35, weight );
    if( minDR_40>=0 ) isoJet40_->Fill( minDR_40, weight );

    std::cout << "AHA3" << std::endl;
    if (idx <  DeltaPhi_Jet_muon_.size())
      {
	std::cout << "AHA4" << std::endl;
	if(jets.size() == 1)
	  {
	    std::cout << "AHA5" << std::endl;
	    DeltaPhi_Jet_muon_[idx]->Fill(muon->phi()-jets[0].phi(), weight);
	  }
	
	if(jets.size() > 1)
	  {
	    std::cout << "AHA5" << std::endl;
	    float delta0 = deltaR(muon->eta(), muon->phi(), jets[0].eta(), jets[0].phi());
	    float delta1 = deltaR(muon->eta(), muon->phi(), jets[1].eta(), jets[1].phi());
	    
	    if(delta0 > delta1)
	      {
		DeltaPhi_farJet_muon_[idx]->Fill(muon->phi()-jets[0].phi(), weight);
		DeltaPhi_nearJet_muon_[idx]->Fill(muon->phi()-jets[1].phi(), weight);     
	      }
	    else
	      {
		DeltaPhi_farJet_muon_[idx]->Fill(muon->phi()-jets[1].phi(), weight);
		DeltaPhi_nearJet_muon_[idx]->Fill(muon->phi()-jets[0].phi(), weight);
	      }
	  }	
      }
    std::cout << "AHA6" << std::endl;
    
    //---------------------------------------------
    // track & calo isolation
    //---------------------------------------------
    const pat::IsoDeposit *trackDep=0, *ecalDep=0, *hcalDep=0;  
    trackDep = muon->trackerIsoDeposit();
    ecalDep  = muon->ecalIsoDeposit();
    hcalDep  = muon->hcalIsoDeposit();


    for(int bin = 1; bin <= dRTrkN_->GetNbinsX(); ++bin){
      // fill enegry flow and object flow histograms for all muons
      dRTrkN_  ->Fill( dRTrkN_  ->GetBinCenter(bin), 
		       trackDep ->countWithin  (dRTrkN_  ->GetBinLowEdge(bin)+dRTrkN_  ->GetBinWidth(bin))
		       );
      dREcalN_ ->Fill( dREcalN_ ->GetBinCenter(bin), 
		       ecalDep  ->countWithin  (dREcalN_ ->GetBinLowEdge(bin)+dREcalN_ ->GetBinWidth(bin)) -
		       ecalDep  ->countWithin  (dREcalN_ ->GetBinLowEdge(bin)) 
		       );
      dRHcalN_ ->Fill( dRHcalN_ ->GetBinCenter(bin),  
		       hcalDep  ->countWithin  (dRHcalN_ ->GetBinLowEdge(bin)+dRHcalN_ ->GetBinWidth(bin)) -
		       hcalDep  ->countWithin  (dRHcalN_ ->GetBinLowEdge(bin)) 		       
		       );
      dRTrkPt_ ->Fill( dRTrkPt_ ->GetBinCenter(bin), 
		       trackDep ->depositWithin(dRTrkPt_ ->GetBinLowEdge(bin)+dRTrkPt_ ->GetBinWidth(bin)) -
		       trackDep ->depositWithin(dRTrkPt_ ->GetBinLowEdge(bin))
		       );
      dREcalPt_->Fill( dREcalPt_->GetBinCenter(bin), 
		       ecalDep  ->depositWithin(dREcalPt_->GetBinLowEdge(bin)+dREcalPt_->GetBinWidth(bin)) -
		       ecalDep  ->depositWithin(dREcalPt_->GetBinLowEdge(bin)) 
		       );
      dRHcalPt_->Fill( dRHcalPt_->GetBinCenter(bin), 
		       hcalDep  ->depositWithin(dRHcalPt_->GetBinLowEdge(bin)+dRHcalPt_->GetBinWidth(bin)) -
		       hcalDep  ->depositWithin(dRHcalPt_->GetBinLowEdge(bin)) 
		       );

      // fill enegry flow and object flow histograms for each muon
      if (idx < muon_dRTrkN_.size() )
	{ 
	  muon_dRTrkN_[idx]  ->Fill( muon_dRTrkN_[idx]  ->GetBinCenter(bin), 
				     trackDep ->countWithin  (muon_dRTrkN_[idx]  ->GetBinLowEdge(bin)+muon_dRTrkN_[idx]  ->GetBinWidth(bin))
				     );
	  
	  muon_dREcalN_[idx] ->Fill( muon_dREcalN_[idx] ->GetBinCenter(bin), 
				     ecalDep  ->countWithin  (muon_dREcalN_[idx] ->GetBinLowEdge(bin)+muon_dREcalN_[idx] ->GetBinWidth(bin)) -
				     ecalDep  ->countWithin  (muon_dREcalN_[idx] ->GetBinLowEdge(bin)) 
				     );
	  muon_dRHcalN_[idx] ->Fill( muon_dRHcalN_[idx] ->GetBinCenter(bin),  
				     hcalDep  ->countWithin  (muon_dRHcalN_[idx] ->GetBinLowEdge(bin)+muon_dRHcalN_[idx] ->GetBinWidth(bin)) -
				     hcalDep  ->countWithin  (muon_dRHcalN_[idx] ->GetBinLowEdge(bin)) 		       
				     );
	  muon_dRTrkPt_[idx] ->Fill( muon_dRTrkPt_[idx] ->GetBinCenter(bin), 
				     trackDep ->depositWithin(muon_dRTrkPt_[idx] ->GetBinLowEdge(bin)+muon_dRTrkPt_[idx] ->GetBinWidth(bin)) -
				     trackDep ->depositWithin(muon_dRTrkPt_[idx] ->GetBinLowEdge(bin))
				     );
	  muon_dREcalPt_[idx]->Fill( muon_dREcalPt_[idx]->GetBinCenter(bin), 
				     ecalDep  ->depositWithin(muon_dREcalPt_[idx]->GetBinLowEdge(bin)+muon_dREcalPt_[idx]->GetBinWidth(bin)) -
				     ecalDep  ->depositWithin(muon_dREcalPt_[idx]->GetBinLowEdge(bin)) 
				     );
	  muon_dRHcalPt_[idx]->Fill( muon_dRHcalPt_[idx]->GetBinCenter(bin), 
				     hcalDep  ->depositWithin(muon_dRHcalPt_[idx]->GetBinLowEdge(bin)+muon_dRHcalPt_[idx]->GetBinWidth(bin)) -
				     hcalDep  ->depositWithin(muon_dRHcalPt_[idx]->GetBinLowEdge(bin)) 
				     );
	}

      // fill enegry and object histograms for all muons
      dRTrkN2_  ->Fill( dRTrkN2_  ->GetBinCenter(bin), 
		       trackDep ->countWithin  (dRTrkN2_  ->GetBinLowEdge(bin)+dRTrkN2_  ->GetBinWidth(bin))
		       );
      dREcalN2_ ->Fill( dREcalN2_ ->GetBinCenter(bin), 
		       ecalDep  ->countWithin  (dREcalN2_ ->GetBinLowEdge(bin)+dREcalN2_ ->GetBinWidth(bin)) 
		       );
      dRHcalN2_ ->Fill( dRHcalN2_ ->GetBinCenter(bin),  
		       hcalDep  ->countWithin  (dRHcalN2_ ->GetBinLowEdge(bin)+dRHcalN2_ ->GetBinWidth(bin))	       
		       );
      dRTrkPt2_ ->Fill( dRTrkPt2_ ->GetBinCenter(bin), 
		       trackDep ->depositWithin(dRTrkPt2_ ->GetBinLowEdge(bin)+dRTrkPt2_ ->GetBinWidth(bin))
		       );
      dREcalPt2_->Fill( dREcalPt2_->GetBinCenter(bin), 
		       ecalDep  ->depositWithin(dREcalPt2_->GetBinLowEdge(bin)+dREcalPt2_->GetBinWidth(bin))
		       );
      dRHcalPt2_->Fill( dRHcalPt2_->GetBinCenter(bin), 
		       hcalDep  ->depositWithin(dRHcalPt2_->GetBinLowEdge(bin)+dRHcalPt2_->GetBinWidth(bin)) 
		       );

      // fill enegry and object histograms for each muon
      if (idx < muon_dRTrkN2_.size() ) 
	{ 
	  muon_dRTrkN2_[idx]  ->Fill( muon_dRTrkN2_[idx]  ->GetBinCenter(bin), 
				      trackDep ->countWithin  (muon_dRTrkN2_[idx]  ->GetBinLowEdge(bin)+muon_dRTrkN2_[idx]  ->GetBinWidth(bin))
				      );
	  muon_dREcalN2_[idx] ->Fill( muon_dREcalN2_[idx] ->GetBinCenter(bin), 
				      ecalDep  ->countWithin  (muon_dREcalN2_[idx] ->GetBinLowEdge(bin)+muon_dREcalN2_[idx] ->GetBinWidth(bin)) 
				      );
	  muon_dRHcalN2_[idx] ->Fill( muon_dRHcalN2_[idx] ->GetBinCenter(bin),  
				      hcalDep  ->countWithin  (muon_dRHcalN2_[idx] ->GetBinLowEdge(bin)+muon_dRHcalN2_[idx] ->GetBinWidth(bin))	       
				      );
	  muon_dRTrkPt2_[idx] ->Fill( muon_dRTrkPt2_[idx] ->GetBinCenter(bin), 
				      trackDep ->depositWithin(muon_dRTrkPt2_[idx] ->GetBinLowEdge(bin)+muon_dRTrkPt2_[idx] ->GetBinWidth(bin))
				      );
	  muon_dREcalPt2_[idx]->Fill( muon_dREcalPt2_[idx]->GetBinCenter(bin), 
				      ecalDep  ->depositWithin(muon_dREcalPt2_[idx]->GetBinLowEdge(bin)+muon_dREcalPt2_[idx]->GetBinWidth(bin))
				      );
	  muon_dRHcalPt2_[idx]->Fill( muon_dRHcalPt2_[idx]->GetBinCenter(bin), 
				      hcalDep  ->depositWithin(muon_dRHcalPt2_[idx]->GetBinLowEdge(bin)+muon_dRHcalPt2_[idx]->GetBinWidth(bin)) 
				      );
	}
    }
	

    for(int bin = 1; bin <= 110 ; ++bin){
      if (idx < muon_isoRelPt2d_.size() )
      {
	float trDp = ( trackDep ->depositWithin(muon_isoRelPt2d_[idx]->GetBinLowEdge(bin)+muon_isoRelPt2d_[idx] ->GetBinWidth(bin)) );
	float ecDp = ( ecalDep ->depositWithin(muon_isoRelPt2d_[idx] ->GetBinLowEdge(bin)+muon_isoRelPt2d_[idx] ->GetBinWidth(bin)) );
	float hcDp = ( hcalDep ->depositWithin(muon_isoRelPt2d_[idx] ->GetBinLowEdge(bin)+muon_isoRelPt2d_[idx] ->GetBinWidth(bin)) );
	muon_isoRelPt2d_[idx] ->Fill( muon_isoRelPt2d_[idx]->GetBinCenter(bin) , (trDp + ecDp + hcDp) / muon->pt() , weight);
      }
    }

    // fill summed deposits for all muons
    double stdDR = 0.3;
    isoEcalN_->Fill( ecalDep ->countWithin(stdDR), weight );
    isoHcalN_->Fill( hcalDep ->countWithin(stdDR), weight );
    isoTrkN_ ->Fill( trackDep->countWithin(stdDR), weight );
    isoTrkPt_->Fill( muon->trackIso(), weight );
    isoCalPt_->Fill( muon->caloIso (), weight );

    double relIso =( ( muon->trackIso() + muon->caloIso() ) / muon->pt() );
    isoRelPt_->Fill( relIso, weight );

    // fill correlation plots for all muons  
    ptVsTrkIso_->Fill( muon->pt(), muon->trackIso() );
    ptVsCalIso_->Fill( muon->pt(), muon->caloIso () );

    if(idx < muon_isoEcalN_.size() )
      {
	// fill summed deposits for each muon 
	double stdDR = 0.3;
	muon_isoHcalN_[idx]->Fill( hcalDep ->countWithin(stdDR), weight );
	muon_isoTrkN_[idx] ->Fill( trackDep->countWithin(stdDR), weight );
	muon_isoTrkPt_[idx]->Fill( muon->trackIso(), weight );
	muon_isoCalPt_[idx]->Fill( muon->caloIso (), weight );
    
	// fill 2d-isolation histogramms
	double relIso1 = ( ( muon->trackIso() + muon->caloIso() ) / muon->pt() );
	double relIso2 = ( ( trackDep->depositWithin(stdDR) + ecalDep->depositWithin(stdDR) + hcalDep->depositWithin(stdDR) ) / muon->pt() );
	muon_isoRelPt_[idx]->Fill( relIso1, weight );
	muon_isoRelPt2_[idx]->Fill( relIso2, weight );

	int hdx=0;
	for(std::vector<pat::Muon>::const_iterator muon2 = muons.begin(); 
	    muon2!=muons.end(); ++muon2)
	  {
	    double relIso21 = ( ( muon2->trackIso() + muon2->caloIso() ) / muon2->pt() );
	    double relIso22 = ( ( muon2->trackerIsoDeposit()->depositWithin(stdDR) + muon2->ecalIsoDeposit()->depositWithin(stdDR) + hcalDep->depositWithin(stdDR) ) / muon2->pt() );
	    
	    if(idx < 4 && hdx < 4)
	      {
		dimuon_isoRelPt_[idx][hdx]->Fill( relIso1, relIso21, weight );
		dimuon_isoRelPt2_[idx][hdx]->Fill( relIso2, relIso22, weight );
	      }
	    ++hdx;
	  }
	
	// fill correlation plots for each muon 
	muon_ptVsTrkIso_[idx]->Fill( muon->pt(), muon->trackIso() );
	muon_ptVsCalIso_[idx]->Fill( muon->pt(), muon->caloIso () );
      }
  }

  //
  // fill invariant-mass histogramms
  //
  if(jets.size() >= 2 && muons.size() >= 2 )
    {
      reco::Particle::LorentzVector p4_di_mu=muons[0].p4()+muons[1].p4();
      reco::Particle::LorentzVector p4_di_jet=jets[0].p4()+jets[1].p4();
      double di_muon_mass = sqrt( p4_di_mu.Dot(p4_di_mu) );
      double di_muon_di_jet_mass = sqrt( (p4_di_mu+p4_di_jet).Dot(p4_di_mu+p4_di_jet) );
      Di_muon_mass_->Fill(di_muon_mass, weight);
      Di_muon_di_jet_mass_->Fill(di_muon_di_jet_mass, weight);
    }
  if(jets.size() >= 4 && muons.size() >= 4 )
    {
      reco::Particle::LorentzVector p4_quad_jet=jets[0].p4()+jets[1].p4()+jets[2].p4()+jets[3].p4();
      double quad_jet_mass = sqrt( (p4_quad_jet).Dot(p4_quad_jet) );
      Quad_jet_mass_->Fill(quad_jet_mass, weight);
    }
}

/// book for FWLite
void 
BSMKinematic::book()
{
  NameScheme kin("kin");
  angle_mu1mu2_= new TH1F(kin.name("angle_mu1mu2"), "angle_mu1mu2", 35, -3.5,  3.5);
  angle_mu1MET_= new TH1F(kin.name("angle_mu1MET"), "angle_mu1MET", 35, -3.5,  3.5);
  angle_mu2MET_= new TH1F(kin.name("angle_mu2MET"), "angle_mu2MET", 35, -3.5,  3.5);

  allEn_ = new TH1F(kin.name("allEn" ), "en" , 60,   0., 700.);
  allPt_ = new TH1F(kin.name("allPt" ), "pt" , 30,   0., 300.);
  allEta_= new TH1F(kin.name("allEta"), "eta", 68, -3.4,  3.4);
  allPhi_= new TH1F(kin.name("allPhi"), "phi", 35, -3.5,  3.5);

  DeltaPhi_=new TH1F(kin.name("DeltaPhi"), "DeltaPhi", 35, -3.5,  3.5); 

  Missing_energy_=new TH1F(kin.name("MET"), "MET", 60, 0., 600.);

  for(int idx=0; idx<nMuons_; ++idx){
    en_.push_back ( new TH1F(kin.name("e",  idx), kin.name("en",  idx), 50,   0., 700.) );
    pt_.push_back ( new TH1F(kin.name("et", idx), kin.name("et",  idx), 30,   0., 300.) );
    eta_.push_back( new TH1F(kin.name("eta",idx), kin.name("eta", idx), 68, -3.4,  3.4) );
    phi_.push_back( new TH1F(kin.name("phi",idx), kin.name("phi", idx), 35, -3.5,  3.5) );

    DeltaPhi_Jet_muon_.push_back( new TH1F(kin.name("DeltaPhi_Jet_muon",idx), kin.name("DeltaPhi_Jet_muon", idx), 35, -3.5,  3.5) );
    DeltaPhi_farJet_muon_.push_back( new TH1F(kin.name("DeltaPhi_farJet_muon",idx), kin.name("DeltaPhi_farJet_muon", idx), 35, -3.5, 3.5) );
    DeltaPhi_nearJet_muon_.push_back( new TH1F(kin.name("DeltaPhi_nearJet_muon",idx), kin.name("DeltaPhi_nearJet_muon", idx), 35, -3.5,3.5) );

  }

  Di_muon_mass_=new TH1F(kin.name("Di_muon_mass"), "Di_muon_mass", 50, 0., 350);
  Di_muon_di_jet_mass_=new TH1F(kin.name("Di_muon_di_jet_mass"), "Di_muon_di_jet_mass", 50, 0.,  1500);
  Quad_jet_mass_=new TH1F(kin.name("Quad_jet_mass"), "Quad_jet_mass", 50, 0.,  1900);

  NameScheme iso("iso");
  isoJet_    = new TH1F(iso.name("isoJet"  ), "isoJet"  , 80,   0.,  4.);
  isoJet5_   = new TH1F(iso.name("isoJet5" ), "isoJet5" , 80,   0.,  4.);
  isoJet10_  = new TH1F(iso.name("isoJet10"), "isoJet10", 80,   0.,  4.);
  isoJet15_  = new TH1F(iso.name("isoJet15"), "isoJet15", 80,   0.,  4.);
  isoJet20_  = new TH1F(iso.name("isoJet20"), "isoJet20", 80,   0.,  4.);
  isoJet25_  = new TH1F(iso.name("isoJet25"), "isoJet25", 80,   0.,  4.);
  isoJet30_  = new TH1F(iso.name("isoJet30"), "isoJet30", 80,   0.,  4.);
  isoJet35_  = new TH1F(iso.name("isoJet35"), "isoJet35", 80,   0.,  4.);
  isoJet40_  = new TH1F(iso.name("isoJet40"), "isoJet40", 80,   0.,  4.);
  isoTrkPt_  = new TH1F(iso.name("isoTrkPt"), "isoTrkPt", 60,  -1.,  5.);
  isoCalPt_  = new TH1F(iso.name("isoCalPt"), "isoCalPt", 40, -10., 30.);
  isoRelPt_  = new TH1F(iso.name("isoRelPt"), "isoRelPt", 45,   -0.025, 1.1);
  isoTrkN_   = new TH1F(iso.name("isoTrkN" ), "isoTrkN" , 20,   0., 20.);
  isoEcalN_  = new TH1F(iso.name("isoEcalN"), "isoEcalN", 30,   0., 30.);
  isoHcalN_  = new TH1F(iso.name("isoHcalN"), "isoHcalN", 30,   0., 30.);
  dRTrkPt_   = new TH1F(iso.name("dRTrkPt" ), "dRTrkPt" , 20,   0.,  1.);
  dRTrkN_    = new TH1F(iso.name("dRTrkN"  ), "dRTrkN"  , 20,   0.,  1.);
  dREcalPt_  = new TH1F(iso.name("dREcalPt"), "dREcalPt", 20,   0.,  1.);
  dREcalN_   = new TH1F(iso.name("dREcalN" ), "dREcalN" , 20,   0.,  1.);
  dRHcalPt_  = new TH1F(iso.name("dRHcalPt"), "dRHcalPt", 20,   0.,  1.);
  dRHcalN_   = new TH1F(iso.name("dRHcalN" ), "dRHcalN" , 20,   0.,  1.);
  dRTrkPt2_  = new TH1F(iso.name("dRTrkPt2" ),"dRTrkPt2" ,20,   0.,  1.);
  dRTrkN2_   = new TH1F(iso.name("dRTrkN2"  ),"dRTrkN2"  ,20,   0.,  1.);
  dREcalPt2_ = new TH1F(iso.name("dREcalPt2"),"dREcalPt2",20,   0.,  1.);
  dREcalN2_  = new TH1F(iso.name("dREcalN2" ),"dREcalN2" ,20,   0.,  1.);
  dRHcalPt2_ = new TH1F(iso.name("dRHcalPt2"),"dRHcalPt2",20,   0.,  1.);
  dRHcalN2_  = new TH1F(iso.name("dRHcalN2" ),"dRHcalN2" ,20,   0.,  1.);

  for(int idx=0; idx<nMuons_; ++idx){
    muon_dRTrkPt_.push_back   ( new TH1F(iso.name("muon_dRTrkPt",idx),  iso.name("muon_dRTrkPt",idx)   ,20,   0.,  1.) );
    muon_dRTrkN_.push_back    ( new TH1F(iso.name("muon_dRTrkN",idx),   iso.name("muon_dRTrkN",idx)    ,20,   0.,  1.) );
    muon_dREcalPt_.push_back  ( new TH1F(iso.name("muon_dREcalPt",idx), iso.name("muon_dREcalPt",idx)  ,20,   0.,  1.) );
    muon_dREcalN_.push_back   ( new TH1F(iso.name("muon_dREcalN",idx ), iso.name("muon_dREcalN",idx )  ,20,   0.,  1.) );
    muon_dRHcalPt_.push_back  ( new TH1F(iso.name("muon_dRHcalPt",idx), iso.name("muon_dRHcalPt",idx)  ,20,   0.,  1.) );
    muon_dRHcalN_.push_back   ( new TH1F(iso.name("muon_dRHcalN",idx),  iso.name("muon_dRHcalN",idx)   ,20,   0.,  1.) );
    muon_dRTrkPt2_.push_back  ( new TH1F(iso.name("muon_dRTrkPt2",idx), iso.name("muon_dRTrkPt2",idx)  ,20,   0.,  1.) );
    muon_dRTrkN2_.push_back   ( new TH1F(iso.name("muon_dRTrkN2",idx),  iso.name("muon_dRTrkN2",idx)   ,20,   0.,  1.) );
    muon_dREcalPt2_.push_back ( new TH1F(iso.name("muon_dREcalPt2",idx),iso.name("muon_dREcalPt2",idx) ,20,   0.,  1.) );
    muon_dREcalN2_.push_back  ( new TH1F(iso.name("muon_dREcalN2",idx), iso.name("muon_dREcalN2",idx)  ,20,   0.,  1.) );
    muon_dRHcalPt2_.push_back ( new TH1F(iso.name("muon_dRHcalPt2",idx),iso.name("muon_dRHcalPt2",idx) ,20,   0.,  1.) );
    muon_dRHcalN2_.push_back  ( new TH1F(iso.name("muon_dRHcalN2",idx), iso.name("muon_dRHcalN2",idx)  ,20,   0.,  1.) );
    muon_isoRelPt2d_.push_back( new TH2F(iso.name("muon_isoRelPt2d",idx), iso.name("muon_isoRelPt2d",idx)  ,110,   0.0,  1.1,110,  0.0,  1.1) );
    
    muon_isoTrkPt_.push_back  (new TH1F(iso.name("muon_isoTrkPt",idx), iso.name("muon_isoTrkPt",idx) , 60,  -1.,  5.) );
    muon_isoCalPt_.push_back  (new TH1F(iso.name("muon_isoCalPt",idx), iso.name("muon_isoCalPt",idx) , 40, -10., 30.) );
    muon_isoRelPt_.push_back  (new TH1F(iso.name("muon_isoRelPt",idx), iso.name("muon_isoRelPt",idx) , 45,   -0.025, 1.1) );
    muon_isoRelPt2_.push_back  (new TH1F(iso.name("muon_isoRelPt2",idx), iso.name("muon_isoRelPt2",idx) , 45,  - 0.025, 1.1) );
    muon_isoTrkN_.push_back   (new TH1F(iso.name("muon_isoTrkN" ,idx), iso.name("muon_isoTrkN" ,idx) , 20,   0., 20.) );
    muon_isoEcalN_.push_back  (new TH1F(iso.name("muon_isoEcalN",idx), iso.name("muon_isoEcalN",idx)  , 30,   0., 30.) );
    muon_isoHcalN_.push_back  (new TH1F(iso.name("muon_isoHcalN",idx), iso.name("muon_isoHcalN",idx) , 30,   0., 30.) );
    
    for (int jdx=0; jdx < 4; ++jdx){ 
      dR_muon_jet_[idx][jdx] = new TH1F(iso.name("dR_muon_jet",idx,jdx),iso.name("dR_muon_jet",idx,jdx),20,   0.,  1.);
      dimuon_isoRelPt_[idx][jdx] = new TH2F(iso.name("dimuon_isoRelPt",idx,jdx),iso.name("dimuon_isoRelPt",idx,jdx),120,   -0.1,  1.1,120,  -0.1,  1.1);
      dimuon_isoRelPt2_[idx][jdx] = new TH2F(iso.name("dimuon_isoRelPt2",idx,jdx),iso.name("dimuon_isoRelPt2",idx,jdx),120,   -0.1,  1.1,120,  -0.1,  1.1);
    }
  }

  NameScheme iso2d("iso2d");
  ptVsTrkIso_ = new TH2F(iso2d.name("ptVsTrkIso"), "ptVsTrkIso", 100, 0., 100., 50,   0., 25.);
  ptVsCalIso_ = new TH2F(iso2d.name("ptVsCalIso"), "ptVsCalIso", 100, 0., 100., 50, -10., 25.);
  
  for(int idx=0; idx<nMuons_; ++idx){
    muon_ptVsTrkIso_.push_back ( new TH2F(iso2d.name("ptVsTrkIso",idx), iso2d.name("ptVsTrkIso",idx) , 100, 0., 100., 50,   0., 25.) );
    muon_ptVsCalIso_.push_back ( new TH2F(iso2d.name("ptVsCalIso",idx), iso2d.name("ptVsCalIso",idx) , 100, 0., 100., 50, -10., 25.) ); 
  }
}

/// book for full FW
void 
BSMKinematic::book(edm::Service<TFileService>& fs)
{
  NameScheme kin("kin");
  angle_mu1mu2_= fs->make<TH1F>(kin.name("angle_mu1mu2"), "angle_mu1mu2", 35, -3.5,  3.5);
  angle_mu1MET_= fs->make<TH1F>(kin.name("angle_mu1MET"), "angle_mu1MET", 35, -3.5,  3.5);
  angle_mu2MET_= fs->make<TH1F>(kin.name("angle_mu2MET"), "angle_mu2MET", 35, -3.5,  3.5);

  allEn_ = fs->make<TH1F>(kin.name("allEn" ), "E(muon) [GeV]"    , 60,   0., 700.);
  allPt_ = fs->make<TH1F>(kin.name("allPt" ), "p_{T}(muon) [GeV]", 30,   0., 300.);
  allEta_= fs->make<TH1F>(kin.name("allEta"), "#eta(muon)"       , 68, -3.4,  3.4);
  allPhi_= fs->make<TH1F>(kin.name("allPhi"), "#phi(muon)"       , 35, -3.5,  3.5);

  DeltaPhi_= fs->make<TH1F>(kin.name("DeltaPhi"), "DeltaPhi", 35, -3.5,  3.5);

  Missing_energy_=fs->make<TH1F>(kin.name("MET"), "MET", 60, 0., 600.);

  for(int idx=0; idx<nMuons_; ++idx){
    en_.push_back (  fs->make<TH1F>(kin.name("e",  idx), kin.name("en",  idx), 50,   0., 700.) );
    pt_.push_back (  fs->make<TH1F>(kin.name("et", idx), kin.name("et",  idx), 30,   0., 300.) );
    eta_.push_back(  fs->make<TH1F>(kin.name("eta",idx), kin.name("eta", idx), 68, -3.4,  3.4) );
    phi_.push_back(  fs->make<TH1F>(kin.name("phi",idx), kin.name("phi", idx), 35, -3.5,  3.5) );

    DeltaPhi_Jet_muon_.push_back( fs->make<TH1F>(kin.name("DeltaPhi_Jet_muon",idx), kin.name("DeltaPhi_Jet_muon", idx), 35, -3.5, 3.5) );
    DeltaPhi_farJet_muon_.push_back( fs->make<TH1F>(kin.name("DeltaPhi_farJet_muon",idx), kin.name("DeltaPhi_farJet_muon", idx), 35, -3.5, 3.5) );
    DeltaPhi_nearJet_muon_.push_back( fs->make<TH1F>(kin.name("DeltaPhi_nearJet_muon",idx), kin.name("DeltaPhi_nearJet_muon", idx), 35, -3.5,3.5) );

  }

  Di_muon_mass_=fs->make<TH1F>(kin.name("Di_muon_mass"), "Di_muon_mass", 50, 0., 350);
  Di_muon_di_jet_mass_=fs->make<TH1F>(kin.name("Di_muon_di_jet_mass"), "Di_muon_di_jet_mass", 50, 0.,  1500);
  Quad_jet_mass_=fs->make<TH1F>(kin.name("Quad_jet_mass"), "Quad_jet_mass", 50, 0.,  1900);

  NameScheme iso("iso");
  isoJet_  = fs->make<TH1F>(iso.name("isoJet"  ), "smallest dR(muon,jet_{all})"   , 35,   0., 3.5);
  isoJet5_ = fs->make<TH1F>(iso.name("isoJet5" ), "smallest dR(muon,jet_{5 GeV})" , 35,   0., 3.5);
  isoJet10_= fs->make<TH1F>(iso.name("isoJet10"), "smallest dR(muon,jet_{10 GeV})", 35,   0., 3.5);
  isoJet15_= fs->make<TH1F>(iso.name("isoJet15"), "smallest dR(muon,jet_{15 GeV})", 35,   0., 3.5);
  isoJet20_= fs->make<TH1F>(iso.name("isoJet20"), "smallest dR(muon,jet_{20 GeV})", 35,   0., 3.5);
  isoJet25_= fs->make<TH1F>(iso.name("isoJet25"), "smallest dR(muon,jet_{25 GeV})", 35,   0., 3.5);
  isoJet30_= fs->make<TH1F>(iso.name("isoJet30"), "smallest dR(muon,jet_{30 GeV})", 35,   0., 3.5);
  isoJet35_= fs->make<TH1F>(iso.name("isoJet35"), "smallest dR(muon,jet_{35 GeV})", 35,   0., 3.5);
  isoJet40_= fs->make<TH1F>(iso.name("isoJet40"), "smallest dR(muon,jet_{40 GeV})", 35,   0., 3.5);
  isoTrkPt_= fs->make<TH1F>(iso.name("isoTrkPt"), "muon trk. isol. [GeV]"         , 20,   0., 10.);
  isoCalPt_= fs->make<TH1F>(iso.name("isoCalPt"), "muon cal. isol. [GeV]"         , 20,   0., 10.);
  isoRelPt_= fs->make<TH1F>(iso.name("isoRelPt"), "rel. comb. isol."              , 45,   -0.025, 1.1);
  isoTrkN_ = fs->make<TH1F>(iso.name("isoTrkN" ), "N_{track}^{dR<0.3}"            , 20,   0., 20.);
  isoEcalN_= fs->make<TH1F>(iso.name("isoEcalN"), "N_{tower,ECAL}^{dR<0.3}"       , 30,   0., 30.);
  isoHcalN_= fs->make<TH1F>(iso.name("isoHcalN"), "N_{tower,HCAL}^{dR<0.3}"       , 30,   0., 30.);
  dRTrkPt_ = fs->make<TH1F>(iso.name("dRTrkPt" ), "dR(muon,track)"                , 20,   0.,  1.);
  dRTrkN_  = fs->make<TH1F>(iso.name("dRTrkN"  ), "dR(muon,track)"                , 20,   0.,  1.);
  dREcalPt_= fs->make<TH1F>(iso.name("dREcalPt"), "dR(muon,ECAL-tower)"           , 20,   0.,  1.);
  dREcalN_ = fs->make<TH1F>(iso.name("dREcalN" ), "dR(muon,ECAL-tower)"           , 20,   0.,  1.);
  dRHcalPt_= fs->make<TH1F>(iso.name("dRHcalPt"), "dR(muon,HCAL-tower)"           , 20,   0.,  1.);
  dRHcalN_ = fs->make<TH1F>(iso.name("dRHcalN" ), "dR(muon,HCAL-tower)"           , 20,   0.,  1.);
  dRTrkPt2_= fs->make<TH1F>(iso.name("dRTrkPt2" ), "dRTrkPt2" , 20,   0.,  1.);
  dRTrkN2_ = fs->make<TH1F>(iso.name("dRTrkN2"  ), "dRTrkN2"  , 20,   0.,  1.);
  dREcalPt2_= fs->make<TH1F>(iso.name("dREcalPt2"), "dREcalPt2", 20,   0.,  1.);
  dREcalN2_ = fs->make<TH1F>(iso.name("dREcalN2" ), "dREcalN2" , 20,   0.,  1.);
  dRHcalPt2_= fs->make<TH1F>(iso.name("dRHcalPt2"), "dRHcalPt2", 20,   0.,  1.);
  dRHcalN2_ = fs->make<TH1F>(iso.name("dRHcalN2" ), "dRHcalN2" , 20,   0.,  1.);

  for(int idx=0; idx<nMuons_; ++idx){
    muon_dRTrkPt_.push_back   ( fs->make<TH1F>(iso.name("muon_dRTrkPt",idx),  iso.name("muon_dRTrkPt",idx)   ,20,   0.,  1.) );
    muon_dRTrkN_.push_back    ( fs->make<TH1F>(iso.name("muon_dRTrkN",idx),   iso.name("muon_dRTrkN",idx)    ,20,   0.,  1.) );
    muon_dREcalPt_.push_back  ( fs->make<TH1F>(iso.name("muon_dREcalPt",idx), iso.name("muon_dREcalPt",idx)  ,20,   0.,  1.) );
    muon_dREcalN_.push_back   ( fs->make<TH1F>(iso.name("muon_dREcalN",idx ), iso.name("muon_dREcalN",idx )  ,20,   0.,  1.) );
    muon_dRHcalPt_.push_back  ( fs->make<TH1F>(iso.name("muon_dRHcalPt",idx), iso.name("muon_dRHcalPt",idx)  ,20,   0.,  1.) );
    muon_dRHcalN_.push_back   ( fs->make<TH1F>(iso.name("muon_dRHcalN",idx),  iso.name("muon_dRHcalN",idx)   ,20,   0.,  1.) );
    muon_dRTrkPt2_.push_back  ( fs->make<TH1F>(iso.name("muon_dRTrkPt2",idx), iso.name("muon_dRTrkPt2",idx)  ,20,   0.,  1.) );
    muon_dRTrkN2_.push_back   ( fs->make<TH1F>(iso.name("muon_dRTrkN2",idx),  iso.name("muon_dRTrkN2",idx)   ,20,   0.,  1.) );
    muon_dREcalPt2_.push_back ( fs->make<TH1F>(iso.name("muon_dREcalPt2",idx),iso.name("muon_dREcalPt2",idx) ,20,   0.,  1.) );
    muon_dREcalN2_.push_back  ( fs->make<TH1F>(iso.name("muon_dREcalN2",idx), iso.name("muon_dREcalN2",idx)  ,20,   0.,  1.) );
    muon_dRHcalPt2_.push_back ( fs->make<TH1F>(iso.name("muon_dRHcalPt2",idx),iso.name("muon_dRHcalPt2",idx) ,20,   0.,  1.) );
    muon_dRHcalN2_.push_back  ( fs->make<TH1F>(iso.name("muon_dRHcalN2",idx), iso.name("muon_dRHcalN2",idx)  ,20,   0.,  1.) );
    muon_isoRelPt2d_.push_back( fs->make<TH2F>(iso.name("muon_isoRelPt2d",idx), iso.name("muon_isoRelPt2d",idx)  ,120,   0.,  1.1,110,  -0.1,  1.1) );

    muon_isoTrkPt_.push_back  (fs->make<TH1F>(iso.name("muon_isoTrkPt",idx), iso.name("muon_isoTrkPt",idx) , 60,  -1.,  5.) );
    muon_isoCalPt_.push_back  (fs->make<TH1F>(iso.name("muon_isoCalPt",idx), iso.name("muon_isoCalPt",idx) , 40, -10., 30.) );
    muon_isoRelPt_.push_back  (fs->make<TH1F>(iso.name("muon_isoRelPt",idx), iso.name("muon_isoRelPt",idx) , 45,   -0.025, 1.1) );
    muon_isoRelPt2_.push_back  (fs->make<TH1F>(iso.name("muon_isoRelPt2",idx), iso.name("muon_isoRelPt2",idx) , 45,   -0.025, 1.1) );
    muon_isoTrkN_.push_back   (fs->make<TH1F>(iso.name("muon_isoTrkN" ,idx), iso.name("muon_isoTrkN" ,idx) , 20,   0., 20.) );
    muon_isoEcalN_.push_back  (fs->make<TH1F>(iso.name("muon_isoEcalN",idx), iso.name("muon_isoEcalN",idx) , 30,   0., 30.) );
    muon_isoHcalN_.push_back  (fs->make<TH1F>(iso.name("muon_isoHcalN",idx), iso.name("muon_isoHcalN",idx) , 30,   0., 30.) );
    
    for (int jdx=0; jdx < 4; ++jdx){
      dR_muon_jet_[idx][jdx] = fs->make<TH1F>(iso.name("dR_muon_jet",idx,jdx),iso.name("dR_muon_jet",idx,jdx),20,   0.,  1.);
      dimuon_isoRelPt_[idx][jdx] = fs->make<TH2F>(iso.name("dimuon_isoRelPt",idx,jdx),iso.name("dimuon_isoRelPt",idx,jdx),120,   -0.1,  1.1,120,  -0.1,  1.1);
      dimuon_isoRelPt2_[idx][jdx] = fs->make<TH2F>(iso.name("dimuon_isoRelPt2",idx,jdx),iso.name("dimuon_isoRelPt2",idx,jdx),120,   -0.1,  1.1,120,  -0.1,  1.1);
    }
  }

  NameScheme iso2d("iso2d");
  ptVsTrkIso_ = fs->make<TH2F>(iso2d.name("ptVsTrkIso"), "ptVsTrkIso", 100, 0., 100., 50,   0., 25.);
  ptVsCalIso_ = fs->make<TH2F>(iso2d.name("ptVsCalIso"), "ptVsCalIso", 100, 0., 100., 50, -10., 25.);
  
  for(int idx=0; idx<nMuons_; ++idx){
    muon_ptVsTrkIso_.push_back ( fs->make<TH2F>(iso2d.name("ptVsTrkIso",idx), iso2d.name("ptVsTrkIso",idx) , 100, 0., 100., 50,   0., 25.) );
    muon_ptVsCalIso_.push_back ( fs->make<TH2F>(iso2d.name("ptVsCalIso",idx), iso2d.name("ptVsCalIso",idx) , 100, 0., 100., 50, -10., 25.) );
  }
}

/// book for full FW with output stream
void 
BSMKinematic::book(edm::Service<TFileService>& fs, ofstream& file)
{
  NameScheme kin("kin");
  angle_mu1mu2_= fs->make<TH1F>(kin.name("angle_mu1mu2"), "angle_mu1mu2", 35, -3.5,  3.5);
  angle_mu1MET_= fs->make<TH1F>(kin.name("angle_mu1MET"), "angle_mu1MET", 35, -3.5,  3.5);
  angle_mu2MET_= fs->make<TH1F>(kin.name("angle_mu2MET"), "angle_mu2MET", 35, -3.5,  3.5);

  allEn_ = fs->make<TH1F>(kin.name(file, "allEn" ), "E(muon) [GeV]"    , 60,   0., 700.);
  allPt_ = fs->make<TH1F>(kin.name(file, "allPt" ), "p_{T}(muon) [GeV]", 30,   0., 300.);
  allEta_= fs->make<TH1F>(kin.name(file, "allEta"), "#eta(muon)"       , 68, -3.4,  3.4);
  allPhi_= fs->make<TH1F>(kin.name(file, "allPhi"), "#phi(muon)"       , 35, -3.5,  3.5);

  DeltaPhi_=fs->make<TH1F>(kin.name("DeltaPhi"), "DeltaPhi", 35, -3.5,  3.5);

  Missing_energy_=fs->make<TH1F>(kin.name("MET"), "MET", 60, 0., 600.);

  for(int idx=0; idx<nMuons_; ++idx){
    en_.push_back (  fs->make<TH1F>(kin.name("e",  idx), kin.name("en",  idx), 50,   0., 700.) );
    pt_.push_back (  fs->make<TH1F>(kin.name("et", idx), kin.name("et",  idx), 30,   0., 300.) );
    eta_.push_back(  fs->make<TH1F>(kin.name("eta",idx), kin.name("eta", idx), 68, -3.4,  3.4) );
    phi_.push_back(  fs->make<TH1F>(kin.name("phi",idx), kin.name("phi", idx), 35, -3.5,  3.5) );

    DeltaPhi_Jet_muon_.push_back( fs->make<TH1F>(kin.name("DeltaPhi_Jet_muon",idx), kin.name("DeltaPhi_Jet_muon", idx), 35, -3.5, 3.5) );
    DeltaPhi_farJet_muon_.push_back( fs->make<TH1F>(kin.name("DeltaPhi_farJet_muon",idx), kin.name("DeltaPhi_farJet_muon", idx), 35, -3.5, 3.5) );
    DeltaPhi_nearJet_muon_.push_back( fs->make<TH1F>(kin.name("DeltaPhi_nearJet_muon",idx), kin.name("DeltaPhi_nearJet_muon", idx), 35, -3.5,3.5) );

  }
  Di_muon_mass_=fs->make<TH1F>(kin.name("Di_muon_mass"), "Di_muon_mass", 50, 0., 350);
  Di_muon_di_jet_mass_=fs->make<TH1F>(kin.name("Di_muon_di_jet_mass"), "Di_muon_di_jet_mass", 50, 0.,  1500);
  Quad_jet_mass_=fs->make<TH1F>(kin.name("Quad_jet_mass"), "Quad_jet_mass", 50, 0.,  1900);

  NameScheme iso("iso");
  isoJet_  = fs->make<TH1F>(iso.name(file, "isoJet"  ), "smallest dR(muon,jet_{all})"   , 35,   0., 3.5);
  isoJet5_ = fs->make<TH1F>(iso.name(file, "isoJet5" ), "smallest dR(muon,jet_{5 GeV})" , 35,   0., 3.5);
  isoJet10_= fs->make<TH1F>(iso.name(file, "isoJet10"), "smallest dR(muon,jet_{10 GeV})", 35,   0., 3.5);
  isoJet15_= fs->make<TH1F>(iso.name(file, "isoJet15"), "smallest dR(muon,jet_{15 GeV})", 35,   0., 3.5);
  isoJet20_= fs->make<TH1F>(iso.name(file, "isoJet20"), "smallest dR(muon,jet_{20 GeV})", 35,   0., 3.5);
  isoJet25_= fs->make<TH1F>(iso.name(file, "isoJet25"), "smallest dR(muon,jet_{25 GeV})", 35,   0., 3.5);
  isoJet30_= fs->make<TH1F>(iso.name(file, "isoJet30"), "smallest dR(muon,jet_{30 GeV})", 35,   0., 3.5);
  isoJet35_= fs->make<TH1F>(iso.name(file, "isoJet35"), "smallest dR(muon,jet_{35 GeV})", 35,   0., 3.5);
  isoJet40_= fs->make<TH1F>(iso.name(file, "isoJet40"), "smallest dR(muon,jet_{40 GeV})", 35,   0., 3.5);
  isoTrkPt_= fs->make<TH1F>(iso.name(file, "isoTrkPt"), "muon trk. isol. [GeV]"         , 20,   0., 10.);
  isoCalPt_= fs->make<TH1F>(iso.name(file, "isoCalPt"), "muon cal. isol. [GeV]"         , 20,   0., 10.);
  isoRelPt_= fs->make<TH1F>(iso.name(file, "isoRelPt"), "rel. comb. isol."              , 45,   -0.025, 1.1);
  isoTrkN_ = fs->make<TH1F>(iso.name(file, "isoTrkN" ), "N_{track}^{dR<0.3}"            , 20,   0., 20.);
  isoEcalN_= fs->make<TH1F>(iso.name(file, "isoEcalN"), "N_{tower,ECAL}^{dR<0.3}"       , 30,   0., 30.);
  isoHcalN_= fs->make<TH1F>(iso.name(file, "isoHcalN"), "N_{tower,HCAL}^{dR<0.3}"       , 30,   0., 30.);
  dRTrkPt_ = fs->make<TH1F>(iso.name(file, "dRTrkPt" ), "dR(muon,track)"                , 20,   0.,  1.);
  dRTrkN_  = fs->make<TH1F>(iso.name(file, "dRTrkN"  ), "dR(muon,track)"                , 20,   0.,  1.);
  dREcalPt_= fs->make<TH1F>(iso.name(file, "dREcalPt"), "dR(muon,ECAL-tower)"           , 20,   0.,  1.);
  dREcalN_ = fs->make<TH1F>(iso.name(file, "dREcalN" ), "dR(muon,ECAL-tower)"           , 20,   0.,  1.);
  dRHcalPt_= fs->make<TH1F>(iso.name(file, "dRHcalPt"), "dR(muon,HCAL-tower)"           , 20,   0.,  1.);
  dRHcalN_ = fs->make<TH1F>(iso.name(file, "dRHcalN" ), "dR(muon,HCAL-tower)"           , 20,   0.,  1.);
  dRTrkPt2_= fs->make<TH1F>(iso.name("dRTrkPt2" ), "dRTrkPt2" , 20,   0.,  1.);
  dRTrkN2_ = fs->make<TH1F>(iso.name("dRTrkN2"  ), "dRTrkN2"  , 20,   0.,  1.);
  dREcalPt2_= fs->make<TH1F>(iso.name("dREcalPt2"), "dREcalPt2", 20,   0.,  1.);
  dREcalN2_ = fs->make<TH1F>(iso.name("dREcalN2" ), "dREcalN2" , 20,   0.,  1.);
  dRHcalPt2_= fs->make<TH1F>(iso.name("dRHcalPt2"), "dRHcalPt2", 20,   0.,  1.);
  dRHcalN2_ = fs->make<TH1F>(iso.name("dRHcalN2" ), "dRHcalN2" , 20,   0.,  1.);

  for(int idx=0; idx<nMuons_; ++idx){
    muon_dRTrkPt_.push_back   ( fs->make<TH1F>(iso.name("muon_dRTrkPt",idx),  iso.name("muon_dRTrkPt",idx)   ,20,   0.,  1.) );
    muon_dRTrkN_.push_back    ( fs->make<TH1F>(iso.name("muon_dRTrkN",idx),   iso.name("muon_dRTrkN",idx)    ,20,   0.,  1.) );
    muon_dREcalPt_.push_back  ( fs->make<TH1F>(iso.name("muon_dREcalPt",idx), iso.name("muon_dREcalPt",idx)  ,20,   0.,  1.) );
    muon_dREcalN_.push_back   ( fs->make<TH1F>(iso.name("muon_dREcalN",idx ), iso.name("muon_dREcalN",idx )  ,20,   0.,  1.) );
    muon_dRHcalPt_.push_back  ( fs->make<TH1F>(iso.name("muon_dRHcalPt",idx), iso.name("muon_dRHcalPt",idx)  ,20,   0.,  1.) );
    muon_dRHcalN_.push_back   ( fs->make<TH1F>(iso.name("muon_dRHcalN",idx),  iso.name("muon_dRHcalN",idx)   ,20,   0.,  1.) );
    muon_dRTrkPt2_.push_back  ( fs->make<TH1F>(iso.name("muon_dRTrkPt2",idx), iso.name("muon_dRTrkPt2",idx)  ,20,   0.,  1.) );
    muon_dRTrkN2_.push_back   ( fs->make<TH1F>(iso.name("muon_dRTrkN2",idx),  iso.name("muon_dRTrkN2",idx)   ,20,   0.,  1.) );
    muon_dREcalPt2_.push_back ( fs->make<TH1F>(iso.name("muon_dREcalPt2",idx),iso.name("muon_dREcalPt2",idx) ,20,   0.,  1.) );
    muon_dREcalN2_.push_back  ( fs->make<TH1F>(iso.name("muon_dREcalN2",idx), iso.name("muon_dREcalN2",idx)  ,20,   0.,  1.) );
    muon_dRHcalPt2_.push_back ( fs->make<TH1F>(iso.name("muon_dRHcalPt2",idx),iso.name("muon_dRHcalPt2",idx) ,20,   0.,  1.) );
    muon_dRHcalN2_.push_back  ( fs->make<TH1F>(iso.name("muon_dRHcalN2",idx), iso.name("muon_dRHcalN2",idx)  ,20,   0.,  1.) );
    muon_isoRelPt2d_.push_back( fs->make<TH2F>(iso.name("muon_isoRelPt2d",idx), iso.name("muon_isoRelPt2d",idx)  ,120,   0.,  1.1,110,  -0.1,  1.1) );
    
    muon_isoTrkPt_.push_back  (fs->make<TH1F>(iso.name("muon_isoTrkPt",idx), iso.name("muon_isoTrkPt",idx) , 60,  -1.,  5.) );
    muon_isoCalPt_.push_back  (fs->make<TH1F>(iso.name("muon_isoCalPt",idx), iso.name("muon_isoCalPt",idx) , 40, -10., 30.) );
    muon_isoRelPt_.push_back  (fs->make<TH1F>(iso.name("muon_isoRelPt",idx), iso.name("muon_isoRelPt",idx) , 45,   -0.025, 1.1) );
    muon_isoRelPt2_.push_back  (fs->make<TH1F>(iso.name("muon_isoRelPt2",idx), iso.name("muon_isoRelPt2",idx) , 45,   -0.025, 1.1) );
    muon_isoTrkN_.push_back   (fs->make<TH1F>(iso.name("muon_isoTrkN" ,idx), iso.name("muon_isoTrkN" ,idx) , 20,   0., 20.) );
    muon_isoEcalN_.push_back  (fs->make<TH1F>(iso.name("muon_isoEcalN",idx), iso.name("muon_isoEcalN",idx) , 30,   0., 30.) );
    muon_isoHcalN_.push_back  (fs->make<TH1F>(iso.name("muon_isoHcalN",idx), iso.name("muon_isoHcalN",idx) , 30,   0., 30.) );
    
    for (int jdx=0; jdx < 4; ++jdx){
      dR_muon_jet_[idx][jdx] = fs->make<TH1F>(iso.name("dR_muon_jet",idx,jdx),iso.name("dR_muon_jet",idx,jdx),20,   0.,  1.);
      dimuon_isoRelPt_[idx][jdx] = fs->make<TH2F>(iso.name("dimuon_isoRelPt",idx,jdx),iso.name("dimuon_isoRelPt",idx,jdx),120,   -0.1,  1.1,120,  -0.1,  1.1);
      dimuon_isoRelPt2_[idx][jdx] = fs->make<TH2F>(iso.name("dimuon_isoRelPt2",idx,jdx),iso.name("dimuon_isoRelPt2",idx,jdx),120,   -0.1,  1.1,120,  -0.1,  1.1);
    }
  }

  NameScheme iso2d("iso2d");
  ptVsTrkIso_ = fs->make<TH2F>(iso2d.name("ptVsTrkIso"), "ptVsTrkIso", 100, 0., 100., 50,   0., 25.);
  ptVsCalIso_ = fs->make<TH2F>(iso2d.name("ptVsCalIso"), "ptVsCalIso", 100, 0., 100., 50, -10., 25.);
  
  for(int idx=0; idx<nMuons_; ++idx){
    muon_ptVsTrkIso_.push_back ( fs->make<TH2F>(iso2d.name("ptVsTrkIso",idx), iso2d.name("ptVsTrkIso",idx) , 100, 0., 100., 50,   0., 25.) );
    muon_ptVsCalIso_.push_back ( fs->make<TH2F>(iso2d.name("ptVsCalIso",idx), iso2d.name("ptVsCalIso",idx) , 100, 0., 100., 50, -10., 25.) );
  }
}

/// write to file and free allocated space for FWLite
void 
BSMKinematic::write(TFile& file, const char* directory)
{
  file.cd( directory );
  angle_mu1mu2_ ->Write( );
  angle_mu1MET_ ->Write( );
  angle_mu2MET_ ->Write( );

  allEn_        ->Write( );
  allPt_        ->Write( );
  allEta_       ->Write( );
  allPhi_       ->Write( );
  DeltaPhi_     ->Write( );
  Missing_energy_->Write( );

  isoJet_    ->Write( );
  isoJet5_   ->Write( );
  isoJet10_  ->Write( );
  isoJet15_  ->Write( );
  isoJet20_  ->Write( );
  isoJet25_  ->Write( );
  isoJet30_  ->Write( );
  isoJet35_  ->Write( );
  isoJet40_  ->Write( );
  isoTrkPt_  ->Write( );
  isoCalPt_  ->Write( );
  isoRelPt_  ->Write( );
  isoTrkN_   ->Write( );
  isoEcalN_  ->Write( );
  isoHcalN_  ->Write( );
  dRTrkPt_   ->Write( );
  dRTrkN_    ->Write( );
  dREcalPt_  ->Write( );
  dREcalN_   ->Write( );
  dRHcalPt_  ->Write( );
  dRHcalN_   ->Write( );
  dRTrkPt2_   ->Write( );
  dRTrkN2_    ->Write( );
  dREcalPt2_  ->Write( );
  dREcalN2_   ->Write( );
  dRHcalPt2_  ->Write( );
  dRHcalN2_   ->Write( );
  ptVsTrkIso_->Write( );
  ptVsCalIso_->Write( );
  Di_muon_mass_->Write();
  Di_muon_di_jet_mass_->Write();
  Quad_jet_mass_->Write();
}
