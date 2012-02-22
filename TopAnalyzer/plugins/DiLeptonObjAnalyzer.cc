#include "TopAnalysis/TopAnalyzer/interface/PUEventWeight.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLorentzVector.h"
#include "TopAnalysis/TopAnalyzer/plugins/DiLeptonObjAnalyzer.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Framework/interface/MakerMacros.h"

using namespace std;
using namespace edm;

DiLeptonObjAnalyzer::DiLeptonObjAnalyzer( const edm::ParameterSet& ps ) {

  fileOutput_      = ps.getParameter<bool>("fileOutput");
  outputFile_      = ps.getUntrackedParameter<string>("outputFile");

  onlyFirst_       = ps.getParameter<bool>("onlyfirst");

  dileptons_       = ps.getParameter<edm::InputTag>("dileptons");
  jets_            = ps.getParameter<edm::InputTag>("jets");

  weight_          = ps.getParameter<edm::InputTag>("weight");

  if( fileOutput_ ) {
    const char *fileName = outputFile_.c_str();
    outfile.open (fileName);
  }

}


DiLeptonObjAnalyzer::~DiLeptonObjAnalyzer() {

}


void DiLeptonObjAnalyzer::beginJob() {

  edm::Service<TFileService> fs;

  if( !fs ){
    throw edm::Exception( edm::errors::Configuration,
                          "TFile Service is not registered in cfg file" );
  }


  Dimass = fs->make<TH1F>("Dimass", "Dilepton mass", 150, 0., 300.);

  Eta    = fs->make<TH1F>("Eta", "Dilepton eta", 30, -6., 6.);

  Phi    = fs->make<TH1F>("Phi", "Dilepton phi", 30, -6.4, 6.4);


  D_R_dilepton_jet    = fs->make<TH1F>("D_R_dilepton_jet",  "(#Delta R)_{min} dilepton-jets",  100, -1., 9.);
  D_R_lepton_lepton   = fs->make<TH1F>("D_R_lepton_lepton", "(#Delta R)_{min} lepton-lepton", 100, -1., 9.);

  D_eta_lepton_lepton = fs->make<TH1F>("D_eta_lepton_lepton", "#Delta eta leptons", 50, -5., 5.);
  D_phi_lepton_lepton = fs->make<TH1F>("D_phi_lepton_lepton", "#Delta phi leptons", 50, -5., 5.);

  Multi               = fs->make<TH1F>("dilepton_multi", "Dilepton multiplicity",10, 0, 10);

}


void DiLeptonObjAnalyzer::beginRun(const edm::Run& r, const edm::EventSetup& context) {

}

void DiLeptonObjAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& context) {
    double weight = getPUEventWeight(evt, weight_);

  // ------------------------
  //  Global Event Variables
  // ------------------------

  //int N_run   = (evt.id()).run();
  //int N_event = (evt.id()).event();
  //int N_lumi  =  evt.luminosityBlock();

  double DR;
  double DPhi;
  double DEta;

  double DEtaDLJ;
  double DPhiDLJ;
  double tempDRdilepjet;
  double DRdilepjet;

  edm::Handle< std::vector<pat::Jet> > jets;
  evt.getByLabel(jets_, jets);

  edm::Handle<reco::CandidateView> dileptons;
  evt.getByLabel(dileptons_, dileptons);

  Multi->Fill(dileptons->size());

   for (reco::CandidateView::const_iterator adiLepton = dileptons->begin() ; adiLepton != dileptons->end(); adiLepton++){

      DRdilepjet=99999;

      DEta = adiLepton->daughter(0)->eta() - adiLepton->daughter(1)->eta();
      DPhi = adiLepton->daughter(0)->phi() - adiLepton->daughter(1)->phi();
      DR = sqrt(DPhi*DPhi + DEta*DEta);

      Dimass              -> Fill(adiLepton->mass(), weight);
      Eta                 -> Fill(adiLepton->eta() , weight);
      Phi                 -> Fill(adiLepton->phi() , weight);
      D_R_lepton_lepton   -> Fill(DR, weight);
      D_eta_lepton_lepton -> Fill(DEta, weight);
      D_phi_lepton_lepton -> Fill(DPhi, weight);

      for (std::vector<pat::Jet>::const_iterator jet = jets->begin() ; jet != jets->end(); jet++){

	DEtaDLJ = adiLepton->eta() - jet->eta();
	DPhiDLJ = adiLepton->phi() - jet->phi();
	tempDRdilepjet = sqrt(DEtaDLJ*DEtaDLJ + DPhiDLJ*DPhiDLJ);

	if(tempDRdilepjet < DRdilepjet){
	  DRdilepjet = tempDRdilepjet;
	}
      }

      if(DRdilepjet!=99999) D_R_dilepton_jet -> Fill(DRdilepjet, weight);

      if(onlyFirst_) break;

    }



}


void DiLeptonObjAnalyzer::endRun(const edm::Run& r, const edm::EventSetup& context) {

}

void DiLeptonObjAnalyzer::endJob() {

  if(fileOutput_)  outfile.close();

}

DEFINE_FWK_MODULE( DiLeptonObjAnalyzer );
