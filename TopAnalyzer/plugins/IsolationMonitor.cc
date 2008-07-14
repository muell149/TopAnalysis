#include "TopAnalysis/TopAnalyzer/plugins/IsolationMonitor.h"

IsolationMonitor::IsolationMonitor(std::string name) {
	edm::Service<TFileService> fs;
	if ( !fs) {
		throw edm::Exception( edm::errors::Configuration,
				"TFile Service is not registered in cfg file" );
	}
	//string -> const char*
	std::string t = "iso_" + name + "_";
	NameScheme nam(t.c_str());
	trackIsoMET_ = fs->make<TH2F>(nam.name("TrackIsoMETCorrelation"),
			nam.name("TrackIsoMETCorrelation"), 300, 0., 300., 60, 0., 60.);
	caloIsoMET_ = fs->make<TH2F>(nam.name("CaloIsoMETCorrelation"),
			nam.name("CaloIsoMETCorrelation"), 300, 0., 300., 60, 0., 60.);
	//box and temperature plots
	TStyle *st = new TStyle();
	st->SetPalette(1);
		trackIsoMET_->SetDrawOption("COLZ");
		caloIsoMET_->SetDrawOption("COLZ");
	//	minDisJetIsoMET_ = fs->make<TH2F>(nam.name("minDisJetIsoMETCorrelation"),
	//			nam.name("minDisJetIsoMETCorrelation"), 300, 0., 300., 300, 0., 300.);
}

IsolationMonitor::IsolationMonitor() {
	edm::Service<TFileService> fs;
	if ( !fs) {
		throw edm::Exception( edm::errors::Configuration,
				"TFile Service is not registered in cfg file" );
	}

	NameScheme nam("iso");
	trackIsoMET_ = fs->make<TH2F>(nam.name("TrackIsoMETCorrelation"),
			nam.name("TrackIsoMETCorrelation"), 300, 0., 300., 60, 0., 60.);
	caloIsoMET_ = fs->make<TH2F>(nam.name("CaloIsoMETCorrelation"),
			nam.name("CaloIsoMETCorrelation"), 300, 0., 300., 60, 0., 60.);
	//box and temperature plots
	//	trackIsoMET_->SetDrawOption("COLZ");
	//	caloIsoMET_->SetDrawOption("COLZ");
	//	minDisJetIsoMET_ = fs->make<TH2F>(nam.name("minDisJetIsoMETCorrelation"),
	//			nam.name("minDisJetIsoMETCorrelation"), 300, 0., 300., 300, 0., 300.);
}
IsolationMonitor::~IsolationMonitor() {
}

void IsolationMonitor::fill(const pat::Muon& topmu, const pat::MET& met,
		double weight) {
	//	cout << "MET: " << met.pt() << endl;
	//	cout << "trackiso: " << topmu.getTrackIso() << endl;
	//	cout << "caloist: " << topmu.getCaloIso() << endl;
	//	cout << "weight: " << weight << endl;
	trackIsoMET_->Fill(met.pt(), topmu.trackIso(), weight);
	caloIsoMET_->Fill(met.pt(), topmu.caloIso(), weight);
	//	minDisJetIsoMET_->Fill(topmu.getTrackIso(), met.pt(), weight);
}

void IsolationMonitor::book(ofstream& file) {

}

void IsolationMonitor::printCorrelation() {
	cout << trackIsoMET_->GetTitle() << "Track Corr: "
			<< trackIsoMET_->GetCorrelationFactor(1, 2) << endl;
	cout << caloIsoMET_->GetTitle() << "Calo Corr: "
			<< caloIsoMET_->GetCorrelationFactor(1, 2) << endl;
	cout << trackIsoMET_->GetTitle() << "Track Conv: "
			<< trackIsoMET_->GetCovariance(1, 2) << endl;
	cout << caloIsoMET_->GetTitle() << "Calo Conv: "
			<< caloIsoMET_->GetCovariance(1, 2) << endl;
}

Double_t IsolationMonitor::getCaloCorrelationFactor(){
	return caloIsoMET_->GetCorrelationFactor(1, 2);
}

Double_t IsolationMonitor::getTrackCorrelationFactor(){
	return trackIsoMET_->GetCorrelationFactor(1, 2);
}
