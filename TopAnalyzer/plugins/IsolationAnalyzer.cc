#include "TopAnalysis/TopAnalyzer/plugins/IsolationAnalyzer.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "AnalysisDataFormats/TopObjects/interface/TtGenEvent.h"

using std::cout;
using std::endl;
using reco::GenParticle;
using edm::LogInfo;

IsolationAnalyzer::IsolationAnalyzer(const edm::ParameterSet& cfg) :
	hist_(cfg.getParameter<std::string> ("hist")), muons_(cfg.getParameter<edm::InputTag> ("muons")), met_(
			cfg.getParameter<edm::InputTag> ("missingEt")), ttgen_(cfg.getParameter<edm::InputTag> ("genEvent")),
			jets_(cfg.getParameter<edm::InputTag> ("jets")),
			ptBins_(cfg.getParameter<std::vector<double> > ("ptBins")), ttbarMC_(cfg.getParameter<bool> ("ttbarMC")),
			useMVA_(cfg.getParameter<bool> ("useMVA")), module_(cfg.getParameter<std::string> ("modulename")),
			discinput_(cfg.getParameter<std::string> ("discriminator")) {
	ttbarMC_ = false;
}

void IsolationAnalyzer::beginJob(const edm::EventSetup&) {
	if (hist_.empty())
		return;

	edm::Service<TFileService> fs;
	if (!fs) {
		throw edm::Exception(edm::errors::Configuration, "TFile Service is not registered in cfg file");
	}

	helper_ = new IsolationHelper(fs, hist_);

	//disable ttbarMC for now
	if (ttbarMC_) {
		//for each ptBin new IsolationHelper
		for (unsigned int x = 0; x < ptBins_.size() - 1; x++) {
			IsolationHelper *helper = new IsolationHelper(fs, "ttbarMC_" + hist_);
			double bin = ptBins_.at(x);
			double nextBin = ptBins_.at(x + 1);
			stringstream name;
			name << ptBins_.at(x);
			stringstream pres;
			pres << "Ttbar_ " << bin << "-" << nextBin << "_";
			string pre = pres.str();
			helper->addHistogram(pre + "invariantMassJ3andJ4", 40, 0., 80.);
			helper->addHistogram(pre + "minDeltaPhiMETJets", 100, 0., 4.);
			helper->addHistogram(pre + "deltaPhiMetJet1", 80, -4., 4.);
			helper->addHistogram(pre + "deltaPhiMetJet2", 80, -4., 4.);
			helper->addHistogram(pre + "deltaPhiMetJet3", 80, -4., 4.);
			helper->addHistogram(pre + "deltaPhiMetJet4", 80, -4., 4.);
			helper->addHistogram(pre + "deltaPhiMetleadingMuon", 80, -4., 4.);
			helper->addHistogram(pre + "deltaPhiMetMuons", 80, -4., 4.);
			helper->addHistogram(pre + "DeltaPhiTimesDeltaEta", 50, -10., 10.);
			helper->addHistogram(pre + "METTimesleadingJetEt", 70, 0., 7000.);
			helper->addHistogram(pre + "Jet3EtOverJet1EtJet3Et", 25, 0., 0.5);
			helper->addHistogram(pre + "Jet3EtOverJet2EtJet3Et", 25, 0., 0.5);
			helper->addHistogram(pre + "Jet4EtOverJet1EtJet4Et", 25, 0., 0.5);
			helper->addHistogram(pre + "Jet4EtOverJet2EtJet3Et", 25, 0., 0.5);
			helper->addHistogram(pre + "JetEtSum34", 150, 0., 300.);
			helper->addHistogram(pre + "DeltaPhiMuonJet3", 80, -4., 4.);
			helper->addHistogram(pre + "DeltaPhiMuonJet4", 80, -4., 4.);
			helper->addHistogram(pre + "DeltaPhiMuonJet12", 80, -4., 4.);
			helper->addHistogram(pre + "SumJet1ET2TimesMuEt", 80, 60., 500);
			helper->addHistogram(pre + "Sum4JetsMuEt", 100, 100., 600);
			helper->addHistogram(pre + "VectorSumJetsMu", 60, 0., 300.);
			helper->addHistogram(pre + "MET", 70, 0., 350.);
			ttBarHelper_.insert(make_pair(name.str(), helper));
		}
	}
	helper_->addHistogram("invariantMassJ3andJ4", 50, 0., 200.);
	helper_->addHistogram("minDeltaPhiMETJets", 100, 0., 4.);
	helper_->addHistogram("deltaPhiMetJet1", 80, -4., 4.);
	helper_->addHistogram("deltaPhiMetJet2", 80, -4., 4.);
	helper_->addHistogram("deltaPhiMetJet3", 80, -4., 4.);
	helper_->addHistogram("deltaPhiMetJet4", 80, -4., 4.);
	helper_->addHistogram("deltaPhiMetleadingMuon", 80, -4., 4.);
	helper_->addHistogram("deltaPhiMetMuons", 80, -4., 4.);
	helper_->addHistogram("DeltaPhiTimesDeltaEta", 50, -10., 10.);
	helper_->addHistogram("METTimesleadingJetEt", 70, 0., 7000.);
	helper_->addHistogram("Jet3EtOverJet1EtJet3Et", 30, 0., 6.);
	helper_->addHistogram("Jet3EtOverJet2EtJet3Et", 30, 0., 6.);
	helper_->addHistogram("Jet4EtOverJet1EtJet4Et", 30, 0., 6.);
	helper_->addHistogram("Jet4EtOverJet2EtJet3Et", 30, 0., 6.);
	helper_->addHistogram("JetEtSum34", 150, 0., 300.);
	helper_->addHistogram("DeltaPhiMuonJet3", 80, -4., 4.);
	helper_->addHistogram("DeltaPhiMuonJet4", 80, -4., 4.);
	helper_->addHistogram("DeltaPhiMuonJet12", 80, -7., 7.);
	helper_->addHistogram("SumJet1ET2TimesMuEt", 80, 60., 500);
	helper_->addHistogram("Sum4JetsMuEt", 100, 100., 600);
	helper_->addHistogram("VectorSumJetsMu", 70, 0., 350.);
	helper_->addHistogram("MET", 70, 0., 350.);
	helper_->addHistogram("deltaPhiTtbar", 80, -4., 4.);
	helper_->addHistogram("fabsDeltaPhiTtbar", 80, 0, 4.);
	helper_->addHistogram("deltaPhiJet1Jet2", 80, -4, 4.);
	helper_->addHistogram("TriJetTMass", 70, 60., 350); //5GeV Schritte
	helper_->addHistogram("muon_pt", 24, 0., 120.);
	helper_->addHistogram("circularity", 100, 0., 1.);
	if (useMVA_)
		helper_->addHistogram("MVAdisc", 20, 0., 1.);
	NameScheme nam("var");
	ofstream off(hist_.c_str(), std::ios::app);
	sumDeltaPhiMuvsdeltaPhiJ1J2_ = fs->make<TH2F> (nam.name(off, "dPhiSumMuTwoJestvsdPhij1j2"), nam.name(
			"dPhiSumMuTwoJestvsdPhij1j2"), 80, -7., 7., 80, -4., 4.);
	recoMETUncorrectedMET_ = fs->make<TH1F> (nam.name(off, "recoMETUncorrectedMET"), nam.name("recoMETUncorrectedMET"),
			200, -100., 100.);
	genMetRecoDiff_ = fs->make<TH1F> (nam.name(off, "recoMETGenMET"), nam.name("recoMETGenMET"), 200, -100., 100.);
	norm_genMetRecoDiff_ = fs->make<TH1F> (nam.name(off, "normed_recoMETGenMET"), nam.name("recoMETGenMET"), 1000,
			-50., 50.);
	realWPt_ = fs->make<TH1F> (nam.name(off, "var_realWPt"), nam.name("var_realWPt"), 200,
			0., 100.);
}

IsolationAnalyzer::~IsolationAnalyzer() {
}

void IsolationAnalyzer::analyze(const edm::Event& evt,
		const edm::EventSetup& setup) {

//	const pat::MET *met;
//	event_++;
//
//	edm::Handle<std::vector<pat::MET> > metH;
//	evt.getByLabel(met_, metH);
//
//	edm::Handle<TopMuonCollection> muons;
//	evt.getByLabel(muons_, muons);
//
//	//the event
//	edm::Handle<TtGenEvent> genEvt;
//	evt.getByLabel(ttgen_, genEvt);
//
//	edm::Handle<double> weightHandle;
//	evt.getByLabel("eventWeight", weightHandle);
//
//	edm::Handle<TopJetCollection> jets;
//	evt.getByLabel(jets_, jets);
//
//	met = &(*metH)[0];
//
//	double weight = *weightHandle;
//
//	//MC information @deprecated
//	TtGenEvent event = *genEvt;
//	const reco::GenParticle* thad = event.hadronicDecayTop();
//	const reco::GenParticle* tlep = event.leptonicDecayTop();
//	if (ttbarMC_) {
//		if (tlep) {
//			LogInfo("IsolationAnalyzer") << "tlep-pt | weight " << tlep->pt()
//					<< " | " << weight << endl;
//			tleppt_->Fill(tlep->pt(), weight);
//		}
//
//		if (thad) {
//			LogInfo("IsolationAnalyzer") << "thad-pt | weight" << thad->pt()
//					<< " | " << weight << endl;
//			thadpt_->Fill(thad->pt(), weight);
//		}
//	}
//
//	if (jets->size() >= 4) {
//		TopJetCollection::const_iterator jet = jets->begin();
//
//		double dp1, dp2, dp3, dp4, dpTde;
//		dpTde = 10000.;
//		unsigned int jetno = getClosestJet(jets, met);
//		unsigned int x = 1;
//
//		dp1 = deltaPhi(met->phi(), jet->phi());
//		LogInfo("IsolationAnalyzer") << "1st jet-met dPhi: " << dp1 << endl;
//		if (x == jetno)
//			dpTde = dp1 * fabs(met->eta() - jet->eta());
//		x++;
//
//		++jet;
//		dp2 = deltaPhi(met->phi(), jet->phi());
//		LogInfo("IsolationAnalyzer") << "2nd jet-met dPhi: " << dp2 << endl;
//		if (x == jetno)
//			dpTde = dp2 * fabs(met->eta() - jet->eta());
//		x++;
//
//		++jet;
//		dp3 = deltaPhi(met->phi(), jet->phi());
//		LogInfo("IsolationAnalyzer") << "3rd jet-met dPhi: " << dp3 << endl;
//		if (x == jetno)
//			dpTde = dp3 * fabs(met->eta() - jet->eta());
//		x++;
//
//		++jet;
//		dp4 = deltaPhi(met->phi(), jet->phi());
//		LogInfo("IsolationAnalyzer") << "4st jet-met dPhi: " << dp4 << endl;
//		if (x == jetno)
//			dpTde = dp4 * fabs(met->eta() - jet->eta());
//		x++;
//
//		double mindp;
//		mindp = min(fabs(dp1), fabs(dp2));
//		mindp = min(mindp, fabs(dp3));
//		mindp = min(mindp, fabs(dp4));
//		LogInfo("IsolationAnalyzer") << "Min-delta-phi: " << mindp << endl;
//
//		minDPhiMETJet_->Fill(mindp, weight);
//		dPhiMETjet1_->Fill(dp1, weight);
//		dPhiMETjet2_->Fill(dp2, weight);
//		dPhiMETjet3_->Fill(dp3, weight);
//		dPhiMETjet4_->Fill(dp4, weight);
//		phiTimesDelta->Fill(dpTde, weight);
//	}
//
//	int size = muons->size();
//	for (int i = 0; i < size; ++i) {
//		pat::Muon mu = (pat::Muon) (*muons)[i];
//		LogInfo("IsolationAnalyzer") << "mu-pt: " << mu.pt() << endl;
//		LogInfo("IsolationAnalyzer") << "mu-trackIso: " << mu.trackIso()
//				<< endl;
//		LogInfo("IsolationAnalyzer") << "mu-caloIso: " << mu.caloIso() << endl;
//		LogInfo("IsolationAnalyzer") << "MET-pt: " << met->pt() << endl;
//
//		isomon_->fill("trackIso", met->pt(), mu.trackIso(), weight);
//		isomon_->fill("caloIso", met->pt(), mu.caloIso(), weight);
//		isomon_->fill("pt", met->pt(), mu.pt(), weight);
//		//delta-phi between leading muon and MET
//		if (i == 0)
//			dPhiMETmuon_->Fill(deltaPhi(mu.phi(), met->phi()), weight);
//		//pt bins of top (MC only, later on reco-lvl):
//		//TODO: get top-pt from reco lvl
//		if (ttbarMC_) {
//			if(thad) hDeltaPhi_->SetPoint(event_, thad->pt(), fabs(deltaPhi(mu.phi(), met->phi())));
//			if(tlep) lDeltaPhi_->SetPoint(event_, tlep->pt(), fabs(deltaPhi(mu.phi(), met->phi())));
//			for (unsigned int i = 0; i < ptBins_.size() - 1; i++) {
//				if (thad && tlep) {
//					if (thad->pt() >= ptBins_[i] && thad->pt() < ptBins_[i + 1]) {
//						hmonitors_[i]->fill("trackCorrelation", met->pt(),
//								mu.trackIso(), weight);
//						hmonitors_[i]->fill("caloCorrelation", met->pt(),
//								mu.caloIso(), weight);
//						hmonitors_[i]->fill("pt", met->pt(), mu.pt(), weight);
//					}
//
//					if (tlep->pt() >= ptBins_[i] && tlep->pt() < ptBins_[i + 1]) {
//						//					smonitors_[i]->fill(mu, *met, weight);
//						smonitors_[i]->fill("trackCorrelation", met->pt(),
//								mu.trackIso(), weight);
//						smonitors_[i]->fill("caloCorrelation", met->pt(),
//								mu.caloIso(), weight);
//						smonitors_[i]->fill("pt", met->pt(), mu.pt(), weight);
//					}
//				}
//			}
//		}
//	}
//	LogInfo("IsolationAnalyzer") << "MET: " << met->pt() << endl;

}

void IsolationAnalyzer::endJob() {
}

pat::Jet IsolationAnalyzer::getClosestJetInDeltaPhi(edm::Handle<TopJetCollection> & j, double phi) {
	pat::Jet closestJet;
	if (j->size() >= 4) {
		double dr2 = 999.;
		TopJetCollection::const_iterator jet = j->begin();
		//only the four highest jets
		for (unsigned x = 0; x < 4; x++) {
			if (jet == j->end())
				break;
			double temp = fabs(deltaPhi(jet->phi(), phi));
			if (temp < dr2) {
				dr2 = temp;
				closestJet = *jet;
			}
			++jet;
		}
	}
	return closestJet;
}

