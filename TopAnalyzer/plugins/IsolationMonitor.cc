#include "TopAnalysis/TopAnalyzer/plugins/IsolationMonitor.h"

//IsolationMonitor::IsolationMonitor(std::string name) {
//	edm::Service<TFileService> fs;
//	if ( !fs) {
//		throw edm::Exception( edm::errors::Configuration,
//				"TFile Service is not registered in cfg file" );
//	}
//	//new
//	name_ = name;
//	//string -> const char*
//	std::string t = "iso_" + name + "_";
//	NameScheme nam(t.c_str());
//	trackIsoMET_ = fs->make<TH2F>(nam.name("TrackIsoMETCorrelation"),
//			nam.name("TrackIsoMETCorrelation"), 300, 0., 300., 60, 0., 60.);
//	caloIsoMET_ = fs->make<TH2F>(nam.name("CaloIsoMETCorrelation"),
//			nam.name("CaloIsoMETCorrelation"), 300, 0., 300., 60, 0., 60.);
//	//box and temperature plots
//	TStyle *st = new TStyle();
//	st->SetPalette(1);
//	trackIsoMET_->SetDrawOption("COLZ");
//	caloIsoMET_->SetDrawOption("COLZ");
//	//	minDisJetIsoMET_ = fs->make<TH2F>(nam.name("minDisJetIsoMETCorrelation"),
//	//			nam.name("minDisJetIsoMETCorrelation"), 300, 0., 300., 300, 0., 300.);
//}

IsolationMonitor::IsolationMonitor() {
	edm::Service<TFileService> fs;
	if ( !fs) {
		throw edm::Exception( edm::errors::Configuration,
				"TFile Service is not registered in cfg file" );
	}

//	NameScheme nam("iso");
//	trackIsoMET_ = fs->make<TH2F>(nam.name("TrackIsoMETCorrelation"),
//			nam.name("TrackIsoMETCorrelation"), 300, 0., 300., 60, 0., 60.);
//	caloIsoMET_ = fs->make<TH2F>(nam.name("CaloIsoMETCorrelation"),
//			nam.name("CaloIsoMETCorrelation"), 300, 0., 300., 60, 0., 60.);
	//box and temperature plots
//		trackIsoMET_->SetDrawOption("COLZ");
//		caloIsoMET_->SetDrawOption("COLZ");
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
//	trackIsoMET_->Fill(met.pt(), topmu.trackIso(), weight);
//	caloIsoMET_->Fill(met.pt(), topmu.caloIso(), weight);
	//	minDisJetIsoMET_->Fill(topmu.getTrackIso(), met.pt(), weight);
}

void IsolationMonitor::fill(std::string name, double v1, double v2, double weight) {
	map<string,TH2F*>::iterator iter = histos_.find(name);
	if( iter != histos_.end() ) {
		iter->second->Fill(v1,v2,weight);
	}
}

void IsolationMonitor::book(ofstream& file) {

}

void IsolationMonitor::printCorrelation() {
//	cout << trackIsoMET_->GetTitle() << "Track Corr: "
//			<< trackIsoMET_->GetCorrelationFactor(1, 2) << endl;
//	cout << caloIsoMET_->GetTitle() << "Calo Corr: "
//			<< caloIsoMET_->GetCorrelationFactor(1, 2) << endl;
//	cout << trackIsoMET_->GetTitle() << "Track Conv: "
//			<< trackIsoMET_->GetCovariance(1, 2) << endl;
//	cout << caloIsoMET_->GetTitle() << "Calo Conv: "
//			<< caloIsoMET_->GetCovariance(1, 2) << endl;

	map<string,TH2F*>::iterator iter;
	for (iter = histos_.begin(); iter != histos_.end(); ++iter) {
		cout << iter->second->GetTitle() << " " << iter->first << " Cor. "
				<< iter->second->GetCorrelationFactor(1, 2) << endl;
		cout << iter->second->GetTitle() << " " << iter->first << " Con. "
				<< iter->second->GetCovariance(1, 2) << endl;
	}
}

Double_t IsolationMonitor::getCaloCorrelationFactor() {
	return -2.;//caloIsoMET_->GetCorrelationFactor(1, 2);
}

Double_t IsolationMonitor::getTrackCorrelationFactor() {
	return -2.;//trackIsoMET_->GetCorrelationFactor(1, 2);
}

Double_t IsolationMonitor::getCorrelationFactor(std::string name) {
	map<string,TH2F*>::iterator iter = histos_.find(name);
	if (iter != histos_.end() ) {
		return iter->second->GetCorrelationFactor(1, 2);
	}
	else{
		return -2.;// factor goes from -1 to 1
	}
}

void IsolationMonitor::addHist(string name, TH2F* hist) {
//	std::string t = "iso_" + name_ + "_"+hist->GetName();
//	hist->SetName(t.c_str());
//	t = "iso_" + name_ + "_"+hist->GetTitle();
//	hist->SetTitle(t.c_str());

	histos_.insert(make_pair(name, hist));
}
