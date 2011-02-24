#include "TLorentzVector.h"
#include "TopAnalysis/TopAnalyzer/interface/DiElectronAnalyzer.h"
#include "DataFormats/Math/interface/deltaR.h"

/// default constructor
DiElectronAnalyzer::DiElectronAnalyzer(const edm::ParameterSet& cfg):
  electrons_    ( cfg.getParameter<edm::InputTag>        ( "electrons"          ) ),
  massBins_     ( cfg.getParameter<std::vector<double> > ( "massBins"       ) ),
  useEvtWgt_    ( cfg.getParameter<bool>                 ( "useEventWeight" ) ),
  correct2width_( cfg.getParameter<bool>                 ( "correctToWidth" ) )
{
}

/// default destructor
DiElectronAnalyzer::~DiElectronAnalyzer()
{
}

/// everything which has to be done before the event loop: book fileservice and histograms
void
DiElectronAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  if( !fs ){
    throw edm::Exception( edm::errors::Configuration,
                          "TFile Service is not registered in cfg file" );
  }

  // define logarithmic bins for a histogram with 50 bins going from 10 to 10^3 = 1000
  const int nbins = 100;
  double logmin =  1.0;
  double logmax =  3.0;
  double bins[nbins+1];
  for (int i = 0; i <= nbins; i++) {
    double log = logmin + (logmax-logmin)*i/nbins;
    bins[i] = std::pow(10.0, log);
  }
  /**
     histogram definitions
  **/
  // invariant electron electron mass for right charge (log binning)
  dimassLogRC_= fs->make<TH1D>( "dimassLogRC", "dimassLogRC", nbins, bins);
  dimassLogRC_->GetXaxis()->SetTitle("m_{ee} [GeV]");
  dimassLogRC_->GetYaxis()->SetTitle("N / 1GeV");

  // invariant electron electron mass for wrong charge (log binning)
  dimassLogWC_= fs->make<TH1D>( "dimassLogWC", "dimassLogWC", nbins, bins);
  dimassLogWC_->GetXaxis()->SetTitle("m_{ee} [GeV]");
  dimassLogWC_->GetYaxis()->SetTitle("N / 1GeV");

  // invariant electron electron mass for right charge
  dimassRC_= fs->make<TH1D>( "dimassRC", "Invariant ee mass, unlike charge", 150,10.,310);
  dimassRC_->GetXaxis()->SetTitle("m_{ee} [GeV]");
  dimassRC_->GetYaxis()->SetTitle("N / 2GeV");

  // invariant electron electron mass for wrong charge
  dimassWC_= fs->make<TH1D>( "dimassWC", "Invariant ee mass, same charge", 150,10.,310);
  dimassWC_->GetXaxis()->SetTitle("m_{ee} [GeV]");
  dimassWC_->GetYaxis()->SetTitle("N / 2GeV");

  // dr between leading electrons, unlike sign
  drElRC_ = fs->make<TH1D>( "drElRC", "#Delta r (ee), unlike charge",100,   0., 10.);
  drElRC_->GetXaxis()->SetTitle("#Delta r");
  drElRC_->GetYaxis()->SetTitle("N_{evts}");

  // dr between leading electrons, like sign
  drElWC_ = fs->make<TH1D>( "drElWC", "#Delta r (ee), same charge",100,   0., 10.);
  drElWC_->GetXaxis()->SetTitle("#Delta r");
  drElWC_->GetYaxis()->SetTitle("N_{evts}");

  // number of electrons in collection
  nEl_  = fs->make<TH1D>( "nEl" , "Number of Electrons"  , 10, -0.5, 9.5);
  nEl_->GetXaxis()->SetTitle("N_{e}");
  nEl_->GetYaxis()->SetTitle("N_{evts}");

  nEntries_ = fs->make<TH1D>( "nEntries", "nEntries" ,massBins_.size(), massBins_[0], massBins_[massBins_.size()-1]);
}

/// everything which has to be done during the event loop: analyze and fill histos
void
DiElectronAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup&)
{
  // get handle on electron collection
  edm::Handle<PatElectronCollection> electrons;
  evt.getByLabel(electrons_, electrons);

  // get weight when indicated, else weight is 1
  double weight = 1.;
  if(useEvtWgt_){
    edm::Handle<double> weightHandle;
    evt.getByLabel("eventWeight", weightHandle);
    weight = *weightHandle;
  }

  nEl_->Fill(electrons->size());

  // test if electron collection contains at least two electrons
  if(electrons->size()<2) return;

  // get leading electrons
  PatElectronCollection::const_reference el1 = electrons->at(0);
  PatElectronCollection::const_reference el2 = electrons->at(1);

  // calculate dimass
  TLorentzVector diLepLVector = TLorentzVector(el1.px()+el2.px(), el1.py()+el2.py(),
                                               el1.pz()+el2.pz(), el1.energy()+el2.energy());
  double dilepMass = (diLepLVector).M();

  // wrong or right charge?
  isWrongCharge = false;
  if(el1.charge()*el2.charge()>0.) isWrongCharge = true;

  // fill dielectron mass histograms:
  //right charge
  if(!isWrongCharge){
    dimassLogRC_->Fill( dilepMass, weight);
    dimassRC_   ->Fill( dilepMass, weight);
    drElRC_->Fill(deltaR(el1.eta(), el1.phi() ,el2.eta(), el2.phi()));
  }
  // wrong charge
  else{
    dimassLogWC_->Fill( dilepMass, weight);
    dimassWC_   ->Fill( dilepMass, weight);
    drElWC_->Fill(deltaR(el1.eta(), el1.phi() ,el2.eta(), el2.phi()));
  }


  // fill nEntries_
  for(int i=massBins_.size()-1; i>=0; --i){
    if(isWrongCharge) continue;
    if(dilepMass > massBins_[i]){
      nEntries_->SetBinContent(i+1,nEntries_->GetBinContent(i+1)+1.);
      break;
    }
  }

  //   std::cout << "++++++++++++++++++++++++++++" << std::endl;
  //   std::cout << "Run # = " << evt.id().run()   << std::endl;
  //   std::cout << "Evt # = " << evt.id().event() << std::endl;
  //   if(isWrongCharge){
  //     std::cout << "Like sign electron combination!" << std::endl;
  //   }
  //   std::cout << "invariant mass = " << dilepMass << std::endl;
  //   std::cout << "++++++++++++++++++++++++++++" << std::endl;

}

/// everything which has to be done during the event loop: analyze and fill histos: empty
void
DiElectronAnalyzer::endJob()
{
  // correct entries in dielectron mass histograms to bin width
  if(!correct2width_) return;

  for(int i=1; i<=dimassLogRC_->GetNbinsX(); ++i){
    dimassLogRC_->SetBinContent(i,dimassLogRC_->GetBinContent(i)/dimassLogRC_->GetBinWidth(i));
    dimassLogWC_->SetBinContent(i,dimassLogWC_->GetBinContent(i)/dimassLogWC_->GetBinWidth(i));
  }
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( DiElectronAnalyzer );
