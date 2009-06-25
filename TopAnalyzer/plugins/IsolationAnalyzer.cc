#include "TopAnalysis/TopAnalyzer/plugins/IsolationAnalyzer.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
//#include "AnalysisDataFormats/TopObjects/interface/TtGenEvent.h"
//#include "TopQuarkAnalysis/TopTools/interface/EventShapeVariables.h"


using std::cout;
using std::endl;
using reco::GenParticle;
using edm::LogInfo;

double newWeightPt(double var, bool signalLike = true) {
	double y1 = 0.1 * var - 1.8;
	double y2 = 1 / y1;
	double ret = 1.;
	if (var <= 80) {
		if (signalLike)
			ret = y1;
		else
			ret = y2;
	}
	return ret;
}
double newWeightDphiMuJ1J2(double var, bool signalLike = true) {
	var = fabs(var);
	double y1 = (1 / M_PI / M_PI) * var * var - 5 / M_PI / 2 * var + 2;
	double y2 = -(1 / M_PI / M_PI) * var * var + 2 / M_PI * var;
	double ret = 1.;
	if (signalLike)
		ret = y1;
	else
		ret = y2;
	return ret;
}

double newWeightDphiMETMu(double var, bool signalLike = true) {
	var = fabs(var);
	double y1 = 1.5 / M_PI * var + 0.5;
	double y2 = 1 / y1;
	double ret = 1;
	if (signalLike)
		ret = y1;
	else
		ret = y2;
	return ret;
}

double newWeightCirc(double var, bool signalLike = true) {
	double y1 = var * var - 2 * var + 1;
	double y2 = 1 - y1;
	double ret = 1.;
	if (signalLike)
		ret = y2;
	else
		ret = y1;
	return ret;
}
/**
 * Tests several variables for correlation with lepton isolation
 * For more information see IsolationAnalyzer twiki page
 * Twiki page link:
 * http://
 */
IsolationAnalyzer::IsolationAnalyzer(const edm::ParameterSet& cfg) :
	muons_(cfg.getParameter<edm::InputTag> ("muons")),
			met_(cfg.getParameter<edm::InputTag> ("missingEt")),// ttgen_(cfg.getParameter<edm::InputTag> ("genEvent")),
			jets_(cfg.getParameter<edm::InputTag> ("jets")),
			//			ptBins_(cfg.getParameter<std::vector<double> > ("ptBins")),
			useMVA_(cfg.getParameter<bool> ("useMVA")), module_(cfg.getParameter<std::string> ("modulename")),
			discinput_(cfg.getParameter<std::string> ("discriminator")) {
}

void IsolationAnalyzer::beginJob(const edm::EventSetup&) {
	edm::Service<TFileService> fs;
	if (!fs) {
		throw edm::Exception(edm::errors::Configuration, "TFile Service is not registered in cfg file");
	}

	helper_ = new IsolationHelper(fs);

	helper_->addHistogram("invariantMassJ3andJ4", 50, 0., 200.);
	helper_->addHistogram("minDeltaPhiMETJets", 100, 0., 4.);
	helper_->addHistogram("deltaPhiMetJet1", 80, 0., 4.);
	helper_->addHistogram("deltaPhiMetJet2", 80, 0., 4.);
	helper_->addHistogram("deltaPhiMetJet3", 80, 0., 4.);
	helper_->addHistogram("deltaPhiMetJet4", 80, 0., 4.);
	helper_->addHistogram("deltaPhiMetleadingMuon", 80, 0., 4.);
	helper_->addHistogram("DeltaPhiTimesDeltaEta", 50, -10., 10.);
	helper_->addHistogram("METTimesleadingJetEt", 70, 0., 7000.);
	helper_->addHistogram("Jet3EtOverJet1EtJet3Et", 50, 0., 1.);
	helper_->addHistogram("Jet3EtOverJet2EtJet3Et", 50, 0., 1.);
	helper_->addHistogram("Jet4EtOverJet1EtJet4Et", 50, 0., 1.);
	helper_->addHistogram("Jet4EtOverJet2EtJet4Et", 50, 0., 1.);
	helper_->addHistogram("JetEtSum34", 150, 0., 300.);
	helper_->addHistogram("DeltaPhiMuonJet3", 80, 0., 4.);
	helper_->addHistogram("DeltaPhiMuonJet4", 80, 0., 4.);
	helper_->addHistogram("DeltaPhiMuonJet12", 80, -7., 7.);
	helper_->addHistogram("SumJet1ET2TimesMuEt", 80, 60., 500);
	helper_->addHistogram("Sum4JetsMuEt", 100, 100., 600);
	helper_->addHistogram("VectorSumJetsMu", 70, 0., 350.);
	helper_->addHistogram("MET", 70, 0., 350.);
	helper_->addHistogram("DeltaPhiTtbar", 80, 0, 4.);
	helper_->addHistogram("deltaPhiJet1Jet2", 80, 0, 4.);
	helper_->addHistogram("TriJetTMass", 70, 60., 350); //5GeV Schritte
	helper_->addHistogram("muon_pt", 24, 0., 120.);
	helper_->addHistogram("circularity", 100, 0., 1.);
	if (useMVA_)
		helper_->addHistogram("MVAdisc", 20, 0., 1.);
	NameScheme nam("spec");
	sumDeltaPhiMuvsdeltaPhiJ1J2_ = fs->make<TH2F> (nam.name("dPhiSumMuTwoJestvsdPhij1j2"), nam.name(
			"dPhiSumMuTwoJestvsdPhij1j2"), 80, -7., 7., 80, -4., 4.);
	recoMETUncorrectedMET_ = fs->make<TH1F> (nam.name("recoMETUncorrectedMET"), nam.name("recoMETUncorrectedMET"), 200,
			-100., 100.);
	genMetRecoDiff_ = fs->make<TH1F> (nam.name("recoMETGenMET"), nam.name("recoMETGenMET"), 200, -100., 100.);
	norm_genMetRecoDiff_
			= fs->make<TH1F> (nam.name("normed_recoMETGenMET"), nam.name("recoMETGenMET"), 1000, -50., 50.);
	//	realWPt_ = fs->make<TH1F> (nam.name("var_realWPt"), nam.name("var_realWPt"), 200, 0., 100.);
}

IsolationAnalyzer::~IsolationAnalyzer() {
}

void IsolationAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& setup) {

	edm::Handle<double> disc_handle;
	double disc = 0.;
	if (useMVA_) {
		evt.getByLabel(module_, discinput_, disc_handle);
		disc = *disc_handle;
	}

	const pat::MET *met;
	reco::Particle::LorentzVector vec;

	edm::Handle<std::vector<pat::MET> > metH;
	evt.getByLabel(met_, metH);

	edm::Handle<TopMuonCollection> muons;
	evt.getByLabel(muons_, muons);

	edm::Handle<double> weightHandle;
	evt.getByLabel("eventWeight", weightHandle);

	edm::Handle<TopJetCollection> jet_handle;
	evt.getByLabel(jets_, jet_handle);
	const TopJetCollection jets = *jet_handle;
	double weight = *weightHandle;

	met = &(*metH)[0];
	//	std::vector<TVector3> p;
	if (jets.size() >= 4 && muons->size() > 0) {
		const pat::Muon *mu = &(*muons)[0];
		selector = new QCDBkgEstimateSelector(jets, mu, met);

		//set the event-weight
		helper_->setWeight(weight);
//		for reweighting of the input variables for MVA
//		helper_->setWeight(weight*newWeightPt(mu->pt()));
//		helper_->setWeight(weight*newWeightCirc(selector->circularity()));
//		helper_->setWeight(weight*newWeightDphiMETMu(selector->dphiMETLepton()));
//		helper_->setWeight(weight*newWeightDphiMuJ1J2(selector->dphiMuJ1J2()));

		double caloIso = mu->caloIso();
		double trackIso = mu->trackIso();

		//set isolation
		helper_->setAbsCaloIso(caloIso);
		helper_->setAbsTrackIso(trackIso);
//		helper_->setJetIso(jetIso);

		helper_->setRelCaloIso(caloIso / mu->pt());
		helper_->setRelTrackIso(trackIso / mu->pt());

		helper_->setAbsCombIso(caloIso + trackIso);
		helper_->setRelCombIso((caloIso + trackIso) / mu->pt());
		//fill histograms
		helper_->fill("invariantMassJ3andJ4", selector->invariantMassJ3andJ4());
		helper_->fill("minDeltaPhiMETJets", selector->minDeltaPhiMETJets());
		helper_->fill("deltaPhiMetJet1", selector->dphiMETJet1());
		helper_->fill("deltaPhiMetJet2", selector->dphiMETJet2());
		helper_->fill("deltaPhiMetJet3", selector->dphiMETJet3());
		helper_->fill("deltaPhiMetJet4", selector->dphiMETJet4());
		helper_->fill("deltaPhiMetleadingMuon", selector->dphiMETLepton());
		helper_->fill("DeltaPhiTimesDeltaEta", selector->DeltaPhiTimesDeltaEta());
		helper_->fill("METTimesleadingJetEt", selector->METTimesLeadingJet());
		helper_->fill("Jet3EtOverJet1EtJet3Et", selector->Jet3EtOverJet1EtJet3Et());
		helper_->fill("Jet3EtOverJet2EtJet3Et", selector->Jet3EtOverJet2EtJet3Et());
		helper_->fill("Jet4EtOverJet1EtJet4Et", selector->Jet4EtOverJet1EtJet4Et());
		helper_->fill("Jet4EtOverJet2EtJet4Et", selector->Jet4EtOverJet2EtJet4Et());
		helper_->fill("JetEtSum34", selector->sumEtJet3And4());
		helper_->fill("DeltaPhiMuonJet3", selector->DeltaPhiMuonJet3());
		helper_->fill("DeltaPhiMuonJet4", selector->DeltaPhiMuonJet4());
		helper_->fill("DeltaPhiMuonJet12", selector->dphiMuJ1J2());
		helper_->fill("SumJet1ET2TimesMuEt", selector->sumEtleadingJetAnd2TimesLeptonPt());
		helper_->fill("Sum4JetsMuEt", selector->sumAllJetsEtAndLepton());
		helper_->fill("VectorSumJetsMu", selector->vecSumAllJetsAndLepton());
		helper_->fill("MET", selector->MET());
		helper_->fill("DeltaPhiTtbar", selector->DeltaPhiTtbar());
		helper_->fill("deltaPhiJet1Jet2", selector->deltaPhiJet1Jet2());
		helper_->fill("TriJetTMass", selector->TriJetTMass());
		helper_->fill("muon_pt", selector->leptonPt());
		helper_->fill("circularity", selector->circularity());
		if (useMVA_)
			helper_->fill("MVAdisc", disc);
		sumDeltaPhiMuvsdeltaPhiJ1J2_->Fill(selector->dphiMuJ1J2(), selector->deltaPhiJet1Jet2(), weight);
		recoMETUncorrectedMET_->Fill(met->et() - met->uncorrectedPt(), weight);
		double genMetreco = (met->et() - met->genMET()->et());
		genMetRecoDiff_->Fill(genMetreco, weight);
		norm_genMetRecoDiff_->Fill(genMetreco / met->genMET()->et(), weight);
	}
}

void IsolationAnalyzer::endJob() {
	helper_->makeSummaryPlots();

	if (recoMETUncorrectedMET_->Integral() != 0) {
		recoMETUncorrectedMET_->Scale(1 / recoMETUncorrectedMET_->Integral());
	}
}
