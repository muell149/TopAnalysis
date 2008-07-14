#include "TopAnalysis/TopAnalyzer/plugins/LeptonCounter.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

using std::cout;
using std::endl;
using reco::GenParticle;

LeptonCounter::LeptonCounter(const edm::ParameterSet& cfg) :	muons_(cfg.getParameter<edm::InputTag>("muons")),
			numberOfRatioBins_(cfg.getParameter<int>("numberOfRatioBins")),
			numberOfMuonBins_(cfg.getParameter<int>("numberOfMuonBins")),
			numberOfElecBins_(cfg.getParameter<int>("numberOfElecBins")),
			minRatio_(cfg.getParameter<double>("minRatio")),
			maxRatio_(cfg.getParameter<double>("maxRatio")),
			minNmuon_(cfg.getParameter<double>("minRatio")),
			maxNmuon_(cfg.getParameter<double>("maxRatio")),
			minNelec_(cfg.getParameter<double>("minRatio")),
			maxNelec_(cfg.getParameter<double>("maxRatio")) {
	eleCounter_ = 0;
	muCounter_ = 0;

	edm::Service<TFileService> fs;
	if ( !fs) {
		throw edm::Exception( edm::errors::Configuration,
				"TFile Service is not registered in cfg file" );
	}

	muonElecRatio_ = fs->make<TH1F>("MuonToElectronRatio",
			"MuonToElectronRatio", numberOfRatioBins_, minRatio_, maxRatio_);

	numberOfMuons_ = fs->make<TH1F>("numberOfMuons", "numberOfMuons",
			numberOfMuonBins_, minNmuon_, maxNmuon_);

	numberOfElecs_ = fs->make<TH1F>("numberOfElecs", "numberOfElecs",
			numberOfElecBins_, minNelec_, maxNelec_);
}

LeptonCounter::~LeptonCounter() {
}

void LeptonCounter::analyze(const edm::Event& evt, const edm::EventSetup& setup) {
	edm::Handle<reco::GenParticleCollection> genParticles;
	evt.getByLabel("genParticles", genParticles);

	edm::Handle<double> weightHandle;
	evt.getByLabel("eventWeight", weightHandle);

	double weight = *weightHandle;
	int evtEl, evtMu;
	evtEl = 0;
	evtMu = 0;
	for (reco::GenParticleCollection::const_iterator part =
			genParticles->begin(); part!=genParticles->end(); ++part) {
		if (fabs(part->pdgId()) == 13) {
			muCounter_++;
			evtMu++;
		}
		if (fabs(part->pdgId()) == 11) {
			eleCounter_++;
			evtEl++;
		}
	}
	muonElecRatio_->Fill(muCounter_/eleCounter_, weight);
	numberOfMuons_->Fill(evtMu, weight);
	numberOfElecs_->Fill(evtEl, weight);

}

void LeptonCounter::beginJob(const edm::EventSetup&) {

}

void LeptonCounter::endJob() {
	cout << "# of e :" << eleCounter_ << endl;
	cout << "# of mu :" << muCounter_ << endl;
}
