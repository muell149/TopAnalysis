#include "TopAnalysis/TopAnalyzer/plugins/LeptonCounter.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

using std::cout;
using std::endl;
using reco::GenParticle;

LeptonCounter::LeptonCounter(const edm::ParameterSet& cfg) :
	muons_(cfg.getParameter<edm::InputTag>("muons")) {
	eleCounter_ = 0;
	muCounter_ = 0;

	edm::Service<TFileService> fs;
	if ( !fs) {
		throw edm::Exception( edm::errors::Configuration,
				"TFile Service is not registered in cfg file" );
	}

	muonElecRatio_ = fs->make<TH1F>("MuonToElectronRatio",
			"MuonToElectronRatio", 600, 0., 300.);
}

LeptonCounter::~LeptonCounter() {
}

void LeptonCounter::analyze(const edm::Event& evt, const edm::EventSetup& setup) {
	edm::Handle<reco::GenParticleCollection> genParticles;
	evt.getByLabel("genParticles", genParticles);

	edm::Handle<double> weightHandle;
	evt.getByLabel("weight", "weight", weightHandle);

	double weight = *weightHandle;
//	LogInfo("ControlOutput") << "weight:  " << weight << endl;

	//	edm::Handle<edm::View<pat::Muon> > recMuons;
	//	evt.getByLabel(muons_, recMuons);
	//
	//	cout << "Muons in sample: " << recMuons->size() << endl;
	for (reco::GenParticleCollection::const_iterator part =
			genParticles->begin(); part!=genParticles->end(); ++part) {
		if (fabs(part->pdgId()) == 13) {
			muCounter_++;
		}
		if (fabs(part->pdgId()) == 11) {
			eleCounter_++;
		}
	}
	muonElecRatio_->Fill(muCounter_/eleCounter_, weight);

}

void LeptonCounter::beginJob(const edm::EventSetup&) {

}

void LeptonCounter::endJob() {
	cout << "# of e :" << eleCounter_ << endl;
	cout << "# of mu :" << muCounter_ << endl;
}
