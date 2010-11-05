#include "TopAnalysis/TopAnalyzer/interface/HTlepTemplate.h"

/// default constructor for fwlite
HTlepTemplate::HTlepTemplate()
{
}

/// default constructor for fwfull
HTlepTemplate::HTlepTemplate(const edm::ParameterSet& cfg)
{

}

/// histogramm booking for fwlite 
void HTlepTemplate::book()
{

}


/// histogramm booking for fwfull
void HTlepTemplate::book(edm::Service<TFileService>& fs)
{
  /** 
      Tree
  **/
  tree = fs->make<TTree>("HTleptree","HTleptree",0);
  tree->Branch("MET", &MET, "MET/F");
  tree->Branch("lepET", &lepET, "lepET/F");
  tree->Branch("HTlep", &HTlep, "HTlep/F");
  tree->Branch("relIso", &relIso, "relIso/F");
  tree->Branch("dB", &dB, "dB/F");
  tree->Branch("MT", &MT, "MT/F");
}

/// histogram filling with fwlite or full framework
void
HTlepTemplate::fill(const edm::View<reco::MET>& met, const double& weight)
{
  MET = met.begin()->et();
}

/// histogram filling with fwlite or full framework
void
HTlepTemplate::fill(const edm::View<reco::MET>& met, const edm::View<pat::Muon>& muon, const double& weight)
{
  if(met.begin()->et() && muon.size() && muon.begin()->pt()){
    MET = met.begin()->et();
    lepET = muon.begin()->pt();
    HTlep = MET+lepET;
    relIso = (muon.begin()->trackIso()+muon.begin()->ecalIso()+muon.begin()->hcalIso())/muon.begin()->pt();
    dB = muon.begin()->dB();
    MT = sqrt((MET+muon.begin()->et())*(MET+muon.begin()->et())-((met.begin()->px()+muon.begin()->px())*(met.begin()->px()+muon.begin()->px())+(met.begin()->py()+muon.begin()->py())*(met.begin()->py()+muon.begin()->py())));

    tree->Fill();
  }
}

void
HTlepTemplate::process() 
{
}
