#include "TopAnalysis/TopAnalyzer/interface/FullHadSpecial.h"

/// default constructor for fw lite
FullHadSpecial::FullHadSpecial(const std::string& correctionLevel) : correctionLevel_(correctionLevel)
{
}

/// default constructor for fwfull
FullHadSpecial::FullHadSpecial(const edm::ParameterSet& cfg) :
  correctionLevel_( cfg.getParameter<std::string>( "correctionLevel" ) )
{
}

/// histogramm booking for fwlite 
void
FullHadSpecial::book()
{
  /// Ht, sum of Et of all jets
  hists_["ht"      ] = new TH1F( "ht"       , "ht"       ,  1000 ,  0. ,  5000. );
  /// real B-Quarks, -1 fake, 1 real
  hists_["realB"   ] = new TH1F( "realB"    , "realB"    ,     2 , -1. ,     1. );
  /// real B-Quarks, -1 fake, 1 real
  hists_["realBSSV"] = new TH1F( "realBSSV" , "realBSSV" ,     2 , -1. ,     1. );
  /// di-jet mass
  hists_["mjj"     ] = new TH1F( "mjj"      , "mjj"      ,  1000 ,  0. ,  5000. );
  /// tri-jet mass
  hists_["mjjj"    ] = new TH1F( "mjjj"     , "mjjj"     ,  1000 ,  0. ,  5000. );
  /// thrust
  hists_["thrust"  ] = new TH1F( "thrust"   , "thrust"   ,   100 ,  0. ,     1. );
  /// (thrust - real) vs Ht
  hists_["thrustHt"] = new TH1F( "thrustHt" , "thrustHt" ,   100 ,  0. ,     1. );
  /// eta-eta-moment
  hists_["etaeta"  ] = new TH1F( "etaeta"   , "etaeta"   ,   100 ,  0. ,     1. );
  /// eta-phi-moment
  hists_["etaphi"  ] = new TH1F( "etaphi"   , "etaphi"   ,   100 ,  0. ,     1. );
  /// phi-phi-moment
  hists_["phiphi"  ] = new TH1F( "phiphi"   , "phiphi"   ,   100 ,  0. ,     1. );
}

/// histogramm booking for full fw
void
FullHadSpecial::book(edm::Service<TFileService>& fs)
{
  /// Ht, sum of Et of all jets
  hists_["ht"      ] = fs->make<TH1F>( "ht"       , "ht"       ,  1000 ,  0. ,  5000. );
  /// real B-Quarks, -1 fake, 1 real
  hists_["realB"   ] = fs->make<TH1F>( "realB"    , "realB"    ,     2 , -1. ,     1. );
  /// real B-Quarks, -1 fake, 1 real
  hists_["realBSSV"] = fs->make<TH1F>( "realBSSV" , "realBSSV" ,     2 , -1. ,     1. );
  /// di-jet mass
  hists_["mjj"     ] = fs->make<TH1F>( "mjj"      , "mjj"      ,  1000 ,  0. ,  5000. );
  /// tri-jet mass
  hists_["mjjj"    ] = fs->make<TH1F>( "mjjj"     , "mjjj"     ,  1000 ,  0. ,  5000. );
  /// thrust
  hists_["thrust"  ] = fs->make<TH1F>( "thrust"   , "thrust"   ,   100 ,  0. ,     1. );
  /// (thrust - real) vs Ht
  hists_["thrustHt"] = fs->make<TH1F>( "thrustHt" , "thrustHt" ,   100 ,  0. ,     1. );
  /// eta-eta-moment
  hists_["etaeta"  ] = fs->make<TH1F>( "etaeta"   , "etaeta"   ,   100 ,  0. ,     1. );
  /// eta-phi-moment
  hists_["etaphi"  ] = fs->make<TH1F>( "etaphi"   , "etaphi"   ,   100 ,  0. ,     1. );
  /// phi-phi-moment
  hists_["phiphi"  ] = fs->make<TH1F>( "phiphi"   , "phiphi"   ,   100 ,  0. ,     1. );
}

/// histogram filling for fwlite and for full fw
void
FullHadSpecial::fill(const edm::View<pat::Jet>& jets, const double& weight)
{
/**
   Calculate variables and fill histograms
**/

  double ht_ = 0;

  for(unsigned int idx=0; idx<jets.size(); ++idx){

    ht_ += jets[idx].et();
/*
    hists_.find("etaeta")->second->Fill( jets[idx].etaetaMoment() , weight );
    hists_.find("etaphi")->second->Fill( jets[idx].etaphiMoment() , weight );
    hists_.find("phiphi")->second->Fill( jets[idx].phiphiMoment() , weight );
*/
    if(jets[idx].bDiscriminator("trackCountingHighPurBJetTags") > 3.){
      if(jets[idx].genParticle() != 0) {
	//std::cout << "PDG-ID of b-jet (HighPur): " << jets[idx].genParticle()->pdgId() << std::endl;
	if(jets[idx].genParticle()->pdgId() == 5 || jets[idx].genParticle()->pdgId() == -5){
	  hists_.find("realB")->second->Fill(  0.5 , weight );
	}
	else{
	  hists_.find("realB")->second->Fill( -0.5 , weight );	
	}
      }
    }

    if(jets[idx].bDiscriminator("simpleSecondaryVertexBJetTags") > 3.){
      if(jets[idx].genParticle() != 0) {
	//std::cout << "PDG-ID of b-jet (SecVert): " << jets[idx].genParticle()->pdgId() << std::endl;
	if(jets[idx].genParticle()->pdgId() == 5 || jets[idx].genParticle()->pdgId() == -5){
	  hists_.find("realBSSV")->second->Fill(  0.5 , weight );
	}
	else{
	  hists_.find("realBSSV")->second->Fill( -0.5 , weight );	
	}
      }
    }
  }

  hists_.find("ht")->second->Fill( ht_ , weight );

/**
   calculate di-jet and tri-jet masses
**/

  if(jets.size()>1){
    for(unsigned int idx=0; idx<jets.size()-1; ++idx) {
      for(unsigned int jdx=idx+1; jdx<jets.size(); ++jdx) {
	
	hists_.find("mjj")->second->Fill( (jets[idx].p4() + jets[jdx].p4()).mass(), weight );
	
	if(jets.size()>2 && (jets.size() - jdx)>1 ){
	  for(unsigned int kdx=jdx+1; kdx<jets.size(); ++kdx) {
	    
	    hists_.find("mjjj")->second->Fill( (jets[idx].p4() + jets[jdx].p4() + jets[kdx].p4()).mass(), weight );
	  }
	}
      }
    }
  }
}

/// return the desired correction step from the configuration string, which is expected to be of type 'step' or 'step:flavor'
const std::string FullHadSpecial::correctionStep() const
{
  std::string step;
  if(correctionLevel_.find(":")!=std::string::npos){
    step=correctionLevel_.substr(0,correctionLevel_.find(":"));
  }
  else{
    step=correctionLevel_;
  }
  return step;
}

/// return the desired correction flavor from the configuration string, which is expected to be of type 'step' or 'step:flavor'
const std::string FullHadSpecial::correctionFlavor() const
{
  std::string flavor;
  if(correctionLevel_.find(":")!=std::string::npos){
    flavor=correctionLevel_.substr(1+correctionLevel_.find(":"));
  }
  return flavor;
}

// /// histogram filling for fwlite and for full fw
// void
// FullHadSpecial::fill(const edm::View<reco::Candidate>& jets, const double& weight)
// {
// }
