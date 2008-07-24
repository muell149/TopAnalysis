#include "TopAnalysis/TopAnalyzer/plugins/IsolationAnalyzer.h"
#include "DataFormats/PatCandidates/interface/MET.h"
//#include "DataFormats/METReco/interface/MET.h"
//#include "DataFormats/METReco/interface/METCollection.h"
//#include "DataFormats/METReco/interface/METFwd.h"
//#include "DataFormats/METReco/interface/CaloMETCollection.h"
//#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "AnalysisDataFormats/TopObjects/interface/TtGenEvent.h"

using std::cout;
using std::endl;
using reco::GenParticle;
using edm::LogInfo;

IsolationAnalyzer::IsolationAnalyzer(const edm::ParameterSet& cfg) :
	hist_(cfg.getParameter<std::string>("hist")),
			muons_(cfg.getParameter<edm::InputTag>("muons")),
			met_(cfg.getParameter<edm::InputTag>("missingEt")),
			ttgen_(cfg.getParameter<edm::InputTag>("genEvent")),
			jets_(cfg.getParameter<edm::InputTag>("jets")),
			ptBins_(cfg.getParameter<std::vector<double> >("ptBins")),
			ttbarMC_(cfg.getParameter<bool>("ttbarMC")) {
	isoMaxBin_ = 10.;
	isoBins_ = 10;
}

void IsolationAnalyzer::beginJob(const edm::EventSetup&) {
	if (hist_.empty() )
		return;

	edm::Service<TFileService> fs;
	if ( !fs) {
		throw edm::Exception( edm::errors::Configuration,
				"TFile Service is not registered in cfg file" );
	}

	ofstream hist(hist_.c_str(), std::ios::out);
	NameScheme nam("iso");
	TH2F *trackIsoMET, *caloIsoMET, *ptMET;
	isomon_ = new CorrelationMonitor();
	trackIsoMET = fs->make<TH2F>(nam.name(hist, "TrackIsoMETCorrelation"),
			nam.name("TrackIsoMETCorrelation"), 300, 0., 300., isoBins_, 0.,
			isoMaxBin_);
	caloIsoMET = fs->make<TH2F>(nam.name(hist, "CaloIsoMETCorrelation"),
			nam.name("CaloIsoMETCorrelation"), 300, 0., 300., 10, 0.,
			isoMaxBin_);
	ptMET = fs->make<TH2F>(nam.name(hist, "PtMETCorrelation"),
			nam.name("PtMETCorrelation"), 300, 0., 300., 300, 0., 300.);

	isomon_->addHist("trackIso", trackIsoMET);
	isomon_->addHist("caloIso", caloIsoMET);
	isomon_->addHist("pt", ptMET);

	if (ttbarMC_) {
		string histi = "ttbarMC_" + hist_;
		ofstream hist2(histi.c_str(), std::ios::out);
		//ttbar MC only
		//for each ptBin new IsolationMonitor
		for (unsigned int x=0; x< ptBins_.size()-1; x++) {
			std::stringstream had, semi;
			double t = ptBins_.at(x);
			had << "thad_" << t << "_";
			semi << "tsemi_" << t << "_";
			string st = semi.str() + "TrackIsoMETCorrelation";
			string sc = semi.str() + "CaloIsoMETCorrelation";
			string sp = semi.str() + "PtMETCorrelation";
			string ht = had.str() + "TrackIsoMETCorrelation";
			string hc = had.str() + "CaloIsoMETCorrelation";
			string hp = had.str() + "PtMETCorrelation";

			CorrelationMonitor *temph = new CorrelationMonitor();
			CorrelationMonitor *temps = new CorrelationMonitor();
			//TODO: addHist
			TH2F *trackIsoMET1, *caloIsoMET1, *ptMET1;
			TH2F *trackIsoMET2, *caloIsoMET2, *ptMET2;

			trackIsoMET1 = fs->make<TH2F>(nam.name(hist2, ht.c_str()),
					nam.name(ht.c_str()), 300, 0., 300., isoBins_, 0.,
					isoMaxBin_);
			caloIsoMET1 = fs->make<TH2F>(nam.name(hist2, hc.c_str()),
					nam.name(hc.c_str()), 300, 0., 300., isoBins_, 0.,
					isoMaxBin_);
			ptMET1 = fs->make<TH2F>(nam.name(hist2, hp.c_str()),
					nam.name(hp.c_str()), 300, 0., 300., 300, 0., 300.);

			trackIsoMET2 = fs->make<TH2F>(nam.name(hist2, st.c_str()),
					nam.name(st.c_str()), 300, 0., 300., isoBins_, 0.,
					isoMaxBin_);
			caloIsoMET2 = fs->make<TH2F>(nam.name(hist2, sc.c_str()),
					nam.name(sc.c_str()), 300, 0., 300., isoBins_, 0.,
					isoMaxBin_);
			ptMET2 = fs->make<TH2F>(nam.name(hist2, sp.c_str()),
					nam.name(sp.c_str()), 300, 0., 300., 300, 0., 300.);
			temph->addHist("trackCorrelation", trackIsoMET1);
			temph->addHist("caloCorrelation", caloIsoMET1);
			temph->addHist("pt", ptMET1);
			temps->addHist("trackCorrelation", trackIsoMET2);
			temps->addHist("caloCorrelation", caloIsoMET2);
			temps->addHist("pt", ptMET2);

			hmonitors_.push_back(temph);
			smonitors_.push_back(temps);
		}
		thadpt_ = fs->make<TH1F>(nam.name(hist2, "hadrTopPt"),
				nam.name("hadrTopPt"), 100, 0., 600.);
		tleppt_ = fs->make<TH1F>(nam.name(hist2, "leprTopPt"),
				nam.name("leprTopPt"), 100, 0., 600.);
		hcaloCorr_ = fs->make<TH1F>(nam.name(hist2, "hadTopCaloCorr"),
				nam.name("hadTopCaloCorr"), ptBins_.size()-1, 0.,
				ptBins_.size()-1*1.0);
		lcaloCorr_ = fs->make<TH1F>(nam.name(hist2, "lepTopCaloCorr"),
				nam.name("lepTopCaloCorr"), ptBins_.size()-1, 0.,
				ptBins_.size()-1*1.0);
		htrackCorr_ = fs->make<TH1F>(nam.name(hist2, "hadTopTrackCorr"),
				nam.name("hadTopTrackCorr"), ptBins_.size()-1, 0.,
				ptBins_.size()-1*1.0);
		ltrackCorr_ = fs->make<TH1F>(nam.name(hist2, "lepTopTrackCorr"),
				nam.name("lepTopTrackCorr"), ptBins_.size()-1, 0.,
				ptBins_.size()-1*1.0);
	}
	minDPhiMETJet_ = fs->make<TH1F>(nam.name(hist, "minDeltaPhiMETJets"),
			nam.name("minDeltaPhiMETJets"), 100, -4., 4.);
	dPhiMETjet1_ = fs->make<TH1F>(nam.name(hist, "deltaPhiMetJet1"),
			nam.name("deltaPhiMetJet1"), 80, -4., 4.);
	dPhiMETjet2_ = fs->make<TH1F>(nam.name(hist, "deltaPhiMetJet2"),
			nam.name("deltaPhiMetJet2"), 80, -4., 4.);
	dPhiMETjet3_ = fs->make<TH1F>(nam.name(hist, "deltaPhiMetJet3"),
			nam.name("deltaPhiMetJet3"), 80, -4., 4.);
	dPhiMETjet4_ = fs->make<TH1F>(nam.name(hist, "deltaPhiMetJet4"),
			nam.name("deltaPhiMetJet4"), 80, -4., 4.);
	dPhiMETmuon_ = fs->make<TH1F>(nam.name(hist, "deltaPhiMetleadingMuon"),
			nam.name("deltaPhiMetMuon"), 80, -4., 4.);
}

IsolationAnalyzer::~IsolationAnalyzer() {
}

void IsolationAnalyzer::analyze(const edm::Event& evt,
		const edm::EventSetup& setup) {

	const pat::MET *met;

	edm::Handle<std::vector<pat::MET> > metH;
	evt.getByLabel(met_, metH);

	edm::Handle<TopMuonCollection> muons;
	evt.getByLabel(muons_, muons);

	//the event
	edm::Handle<TtGenEvent> genEvt;
	evt.getByLabel(ttgen_, genEvt);

	edm::Handle<double> weightHandle;
	evt.getByLabel("eventWeight", weightHandle);

	edm::Handle<TopJetCollection> jets;
	evt.getByLabel(jets_, jets);

	met = &(*metH)[0];

	double weight = *weightHandle;

	//MC information @deprecated
	TtGenEvent event = *genEvt;
	const reco::GenParticle* thad = event.hadronicDecayTop();
	const reco::GenParticle* tlep = event.leptonicDecayTop();
	if (ttbarMC_) {
		if (tlep) {
			LogInfo("IsolationAnalyzer") << "tlep-pt | weight " << tlep->pt()
					<< " | " << weight << endl;
			tleppt_->Fill(tlep->pt(), weight);
		}

		if (thad) {
			LogInfo("IsolationAnalyzer") << "thad-pt | weight" << thad->pt()
					<< " | " << weight << endl;
			thadpt_->Fill(thad->pt(), weight);
		}
	}

	if (jets->size() >= 4) {
		double dp1, dp2, dp3, dp4;
		TopJetCollection::const_iterator jet = jets->begin();
		dp1 = deltaPhi(met->phi(), jet->phi());
		LogInfo("IsolationAnalyzer") << "1st jet-met dPhi: " << dp1 << endl;

		++jet;
		dp2 = deltaPhi(met->phi(), jet->phi());
		LogInfo("IsolationAnalyzer") << "2nd jet-met dPhi: " << dp2 << endl;

		++jet;
		dp3 = deltaPhi(met->phi(), jet->phi());
		LogInfo("IsolationAnalyzer") << "3rd jet-met dPhi: " << dp3 << endl;

		++jet;
		dp4 = deltaPhi(met->phi(), jet->phi());
		LogInfo("IsolationAnalyzer") << "4st jet-met dPhi: " << dp4 << endl;

		double mindp;
		mindp = min(dp1, dp2);
		mindp = min(mindp, dp3);
		mindp = min(mindp, dp4);
		LogInfo("IsolationAnalyzer") << "Min-delta-phi: " << mindp << endl;

		minDPhiMETJet_->Fill(mindp, weight);
		dPhiMETjet1_->Fill(dp1, weight);
		dPhiMETjet2_->Fill(dp2, weight);
		dPhiMETjet3_->Fill(dp3, weight);
		dPhiMETjet4_->Fill(dp4, weight);
	}

	int size = muons->size();
	for (int i = 0; i < size; ++i) {
		pat::Muon mu = (pat::Muon) (*muons)[i];
		LogInfo("IsolationAnalyzer") << "mu-pt: " << mu.pt() << endl;
		LogInfo("IsolationAnalyzer") << "mu-trackIso: " << mu.trackIso()
				<< endl;
		LogInfo("IsolationAnalyzer") << "mu-caloIso: " << mu.caloIso() << endl;
		LogInfo("IsolationAnalyzer") << "MET-pt: " << met->pt() << endl;

		isomon_->fill("trackIso", met->pt(), mu.trackIso(), weight);
		isomon_->fill("caloIso", met->pt(), mu.caloIso(), weight);
		isomon_->fill("pt", met->pt(), mu.pt(), weight);
		//delta-phi between leading muon and MET
		if (i == 0)
			dPhiMETmuon_->Fill(deltaPhi(mu.phi(), met->phi()), weight);
		//pt bins of top (MC only, later on reco-lvl):
		//TODO: get top-pt from reco lvl
		if (ttbarMC_) {
			for (unsigned int i=0; i < ptBins_.size()-1; i++) {
				if (thad && tlep) {
					if (thad->pt() >= ptBins_[i] && thad->pt() < ptBins_[i+1]) {
						hmonitors_[i]->fill("trackCorrelation", met->pt(),
								mu.trackIso(), weight);
						hmonitors_[i]->fill("caloCorrelation", met->pt(),
								mu.caloIso(), weight);
						hmonitors_[i]->fill("pt", met->pt(), mu.pt(), weight);
					}

					if (tlep->pt() >= ptBins_[i] && tlep->pt() < ptBins_[i+1]) {
						//					smonitors_[i]->fill(mu, *met, weight);
						smonitors_[i]->fill("trackCorrelation", met->pt(),
								mu.trackIso(), weight);
						smonitors_[i]->fill("caloCorrelation", met->pt(),
								mu.caloIso(), weight);
						smonitors_[i]->fill("pt", met->pt(), mu.pt(), weight);
					}
				}
			}
		}
	}
	LogInfo("IsolationAnalyzer") << "MET: " << met->pt() << endl;

}

void IsolationAnalyzer::endJob() {

	isomon_->printCorrelation();
	if (ttbarMC_) {
		for (unsigned int x = 0; x< smonitors_.size(); x++) {
			hcaloCorr_->SetBinContent(x+1,
					hmonitors_[x]->getCorrelationFactor("caloCorrelation"));
			lcaloCorr_->SetBinContent(x+1,
					smonitors_[x]->getCorrelationFactor("caloCorrelation"));

			htrackCorr_->SetBinContent(x+1,
					hmonitors_[x]->getCorrelationFactor("trackCorrelation"));
			ltrackCorr_->SetBinContent(x+1,
					smonitors_[x]->getCorrelationFactor("trackCorrelation"));

			hptCorr_->SetBinContent(x+1,
					hmonitors_[x]->getCorrelationFactor("pt"));
			lptCorr_->SetBinContent(x+1,
					smonitors_[x]->getCorrelationFactor("pt"));

			std::stringstream xlabel;
			xlabel << ptBins_.at(x) << "-" << ptBins_.at(x+1);
			hcaloCorr_->GetXaxis()->SetBinLabel(x+1, xlabel.str().c_str());
			lcaloCorr_->GetXaxis()->SetBinLabel(x+1, xlabel.str().c_str());
			htrackCorr_->GetXaxis()->SetBinLabel(x+1, xlabel.str().c_str());
			ltrackCorr_->GetXaxis()->SetBinLabel(x+1, xlabel.str().c_str());
			hptCorr_->GetXaxis()->SetBinLabel(x+1, xlabel.str().c_str());
			lptCorr_->GetXaxis()->SetBinLabel(x+1, xlabel.str().c_str());

			smonitors_[x]->printCorrelation();
			hmonitors_[x]->printCorrelation();
		}
	}
}

