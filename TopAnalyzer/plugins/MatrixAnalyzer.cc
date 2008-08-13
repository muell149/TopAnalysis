#include "TopAnalysis/TopAnalyzer/plugins/MatrixAnalyzer.h"

using std::cout;
using std::endl;
using reco::GenParticle;

MatrixAnalyzer::MatrixAnalyzer(const edm::ParameterSet& cfg) :
	hist_(cfg.getParameter<std::string> ("hist")),
	pmodulename_(cfg.getParameter<std::string> ("pmn")),
	before_(cfg.getParameter<bool> ("before")),
	muons_(cfg.getParameter<edm::InputTag> ("muons")),
	var_(cfg.getParameter<edm::InputTag> ("var")),
	varBins_(cfg.getParameter<std::vector<double> > ("varBins")) {
	debug_ = true;
	hadrCount_ = 0;
	lCount_ = 0;
	bgBefore_ = 0.0;
	slBefore_ = .0;
	llCount_ = 0;
	noBins_ = 5;
	beforeBin_ = 2;
	afterBin_ = 4;
	effBG_ = 0.0;
	effSL_ = 0.0;
	effDL_ = 0.0;
	effML_ = 0.0;
	mlCount_ = 0;
	rhadrCount_ = 0;
	rlCount_ = 0;
	rllCount_ = 0;
	rmlCount_ = 0;
	sampleweight_ = 0;
	whadrCount_ = 0;
	wlCount_ = 0;
	wllCount_ = 0;
	wmlCount_ = 0;

	weightedCounters_ = new LeptonCounter();
	matchedCounters_ = new LeptonCounter();
	simpleCounters_ = new LeptonCounter();
	weightedBefore_ = new LeptonCounter();
	effCounter_ = new LeptonCounter();
	effErrors_ =  new LeptonCounter();
	for (unsigned int x = 0; x < varBins_.size() - 1; x++) {
		std::stringstream tmp;
		tmp << varBins_.at(x);
		weightedCounters_->addCounter(tmp.str());
		matchedCounters_->addCounter(tmp.str());
		simpleCounters_->addCounter(tmp.str());
		weightedBefore_->addCounter(tmp.str());
		effCounter_->addCounter(tmp.str());
		effErrors_->addCounter(tmp.str());
	}
}

MatrixAnalyzer::~MatrixAnalyzer() {
}

void MatrixAnalyzer::beginJob(const edm::EventSetup&) {

	if (hist_.empty())
		return;

	//TODO: Beim 2ten durchlauf sollen die histogramme geladen werden.
	edm::Service<TFileService> fs;
	if (!fs) {
		throw edm::Exception(edm::errors::Configuration,
				"TFile Service is not registered in cfg file");
	}
	f_ = &fs->file();
	ofstream hist(hist_.c_str(), std::ios::out);

	NameScheme nam("mbg");

	//make histograms
	background_ = fs->make<TH1F> (nam.name(hist, "N_background"), nam.name(
			"background"), 300, 0, 1.);
	lep_ = fs->make<TH1F> (nam.name(hist, "N_semilepton"), nam.name("lepton"),
			300, 0, 1.);
	llep_ = fs->make<TH1F> (nam.name(hist, "N_dilepton"), nam.name("ll"), 300,
			0, 1.);
	multilep_ = fs->make<TH1F> (nam.name(hist, "N_multilepton"),
			nam.name("ml"), 300, 0, 1.);
	eff_ = fs->make<TH1F> (nam.name(hist, "efficency"), nam.name("eff"), 300,
			0, 1.);

	binnedBkg_ = fs->make<TH1F> (nam.name(hist, "binnedBkg"), nam.name(
			"binnedBkg"), varBins_.size()*2 + 2, 0, 1.);
	binnedSemiLep_ = fs->make<TH1F> (nam.name(hist, "binnedSemiLep"), nam.name(
			"binnedSemiLep"), varBins_.size()*2 + 2, 0, 1.);
	binnedDiLep_ = fs->make<TH1F> (nam.name(hist, "binnedDiLep"), nam.name(
			"binnedDiLep"), varBins_.size()*2 + 2, 0, 1.);
	binnedMultiLep_ = fs->make<TH1F> (nam.name(hist, "binnedMultiLep"),
			nam.name("binnedMultiLep"), varBins_.size()*2 + 2, 0, 1.);
	binnedEff_ = fs->make<TH1F> (nam.name(hist, "binnedEff"), nam.name(
			"binnedEff"), varBins_.size() + 2, 0, 1.);
	//set number of bins (noBins_)
	background_->SetBins(noBins_, 0., 5.);
	lep_->SetBins(noBins_, 0., 5.);
	llep_->SetBins(noBins_, 0., 5.);
	multilep_->SetBins(noBins_, 0., 5.);
	eff_->SetBins(9, 0., 5.);
}

void MatrixAnalyzer::analyze(const edm::Event& evt,
		const edm::EventSetup& setup) {

	//get muons
	//	if (!before_)
	//		cout << "----------------------after-----------------------" << endl;
	//	else
	//		cout << "----------------------before-----------------------" << endl;
	edm::Handle<reco::GenParticleCollection> genParticles;
	evt.getByLabel("genParticles", genParticles);

	edm::Handle<TopMuonCollection> muons;
	evt.getByLabel(muons_, muons);

	edm::Handle<edm::View<pat::Muon> > recMuons;
	evt.getByLabel(muons_, recMuons);

	edm::Handle<edm::View<reco::RecoCandidate> > recVars;
	evt.getByLabel(var_, recVars);

	edm::Handle<edm::Association<reco::GenParticleCollection> > genMatch;
	evt.getByLabel("muonMatch", genMatch);

	edm::Handle<double> weightHandle;
	evt.getByLabel("eventWeight", weightHandle);

	sampleweight_ = *weightHandle;

	int matchedmu = 0;
	//	for (reco::GenParticleCollection::const_iterator part =
	//			genParticles->begin(); part!=genParticles->end(); ++part) {
	//		if (fabs(part->pdgId()) == 13) {
	//			if (part->numberOfMothers() > 0) {
	//				log("-------", "-------------", false);
	//				log(part->mother(0)->pdgId(), "::analyze >> genMother ID", true);
	//				log(part->mother(0)->status(), "::analyze >> genMother ST", true);
	//				log(part->mother(0)->eta(), "::analyze >> eta", true);
	//			}
	//			int size = muons->size();
	//			for (int i = 0; i != size; ++i) {
	//				//					reco::Muon
	//				pat::Muon mu = (pat::Muon)(* muons)[i];
	//				const reco::GenParticle genL = *((*muons)[i]).genLepton();
	//				//simple MC match
	//
	//				// TopMuon has no mother, but its genParticle has.
	//
	//				if (part->numberOfMothers() > 0 && genL.numberOfMothers() > 0) {
	//					//log("muons have mothers", "::analyze >> MCmatch", true);
	//					//					log(part->mother(0)->pdgId(), "::analyze >> MCmatch", true);
	//					//					log(genL.mother(0)->pdgId(), "::analyze >> MCmatch", true);
	//					if (part->mother(0) == genL.mother(0)) {
	//						mothermap_[part->mother(0)->pdgId()].push_back(mu);
	//						log("found match", "::analyze >> MCmatch", true);
	//						matchedmu++;
	//						log(genL.mother(0)->pdgId(),
	//								"::analyze >> MCmatch >> recoMother", true);
	//						log(part->mother(0)->pdgId(),
	//								"::analyze >> MCmatch >> genMother", true);
	//					}
	//				}
	//				if (genL.numberOfDaughters() > 0)
	//					log(genL.daughter(0)->pdgId(), "::analyze >> recoDaughter", true);
	//			}
	//
	//		}
	//	}

	//	log(matchedmu, "::analyze >> matched muons", true);

	Double_t pt = (*recVars)[0].pt();
	for (unsigned int i = 0; i < varBins_.size() - 1; i++) {
		if (pt >= varBins_[i] && pt < varBins_[i + 1]) {
			double t = varBins_.at(i);
			std::stringstream tmp;
			tmp << t;
			if (muons->size() < 1) {
				weightedCounters_->addPureHadronic(tmp.str(), sampleweight_);
			}
			else if (muons->size() == 1) {
				weightedCounters_->addSemiLeptonic(tmp.str(), sampleweight_);
			}
			else if (muons->size() == 2) {
				weightedCounters_->addDiLeptonic(tmp.str(),sampleweight_);
			}
			else if (muons->size() > 2) {
				weightedCounters_->addMultiLeptonic(tmp.str(), sampleweight_);
			}
		}
	}
	if (muons->size() < 1) {
		hadrCount_++;
		whadrCount_ += sampleweight_;
		//		weightedCounters_->addPureHadronic("", sampleweight_);
	}

	if (muons->size() == 1) {
		lCount_++;
		wlCount_ += sampleweight_;
	}
	if (muons->size() == 2) {
		llCount_++;
		wllCount_ += sampleweight_;
	}
	if (muons->size() > 2) {
		mlCount_++;
		wmlCount_ += sampleweight_;
	}

	//only matched muons:
	if (matchedmu < 1)
		rhadrCount_++;
	if (matchedmu == 1)
		rlCount_++;
	if (matchedmu == 2)
		rllCount_++;
	if (matchedmu > 2)
		rmlCount_++;

}

void MatrixAnalyzer::endJob() {
	//and store them.
	double deff_bg, deff_sl, deff_dl, deff_ml;
	deff_bg = 0;
	deff_sl = 0;
	deff_dl = 0;
	deff_ml = 0;

	if (before_) {
		cout << "#----- before -----#" << endl;
		setEnv(beforeBin_);
		cout << endl;
	} else {

		getBefore();
		if (bgBefore_ != 0) {
			effBG_ = whadrCount_ / bgBefore_;
			deff_bg = sqrt(effBG_ * (1 - effBG_) / bgBefore_);
		}

		if (slBefore_ != 0) {
			effSL_ = wlCount_ / slBefore_;
			deff_sl = sqrt(effSL_ * (1 - effSL_) / slBefore_);
		}

		if (dlBefore_ != 0) {
			effDL_ = wllCount_ / dlBefore_;
			deff_dl = sqrt(effDL_ * (1 - effDL_) / dlBefore_);
		}

		if (mlBefore_ != 0) {
			effML_ = wmlCount_ / mlBefore_;
			deff_ml = sqrt(effML_ * (1 - effML_) / mlBefore_);
		}

		for (unsigned int i = 0; i < varBins_.size() - 1; i++) {
			std::stringstream tmp;
			tmp << varBins_.at(i);
			double b, s, d, m, bb, sb, db, mb;
			b = weightedCounters_->getPureHadronic(tmp.str());
			s = weightedCounters_->getSemiLeptonic(tmp.str());
			d = weightedCounters_->getDiLeptonic(tmp.str());
			m = weightedCounters_->getMultiLeptonic(tmp.str());

			bb = weightedBefore_->getPureHadronic(tmp.str());
			sb = weightedBefore_->getSemiLeptonic(tmp.str());
			db = weightedBefore_->getDiLeptonic(tmp.str());
			mb = weightedBefore_->getMultiLeptonic(tmp.str());
			if (bb != 0.) {
				double eff,err;
				eff = b / bb;
				err = sqrt(eff * (1 - eff) / bb);
				effCounter_->setPureHadronic(tmp.str(), eff);
				effErrors_->setPureHadronic(tmp.str(), err);
				cout << tmp.str() << " (had) " << eff << " +- " << err << endl;
			}
			if (sb != 0.) {
				double eff,err;
				eff = s/sb;
				err = sqrt(eff * (1 - eff) / sb);
				effCounter_->setSemiLeptonic(tmp.str(), eff);
				effErrors_->setSemiLeptonic(tmp.str(), err);
				cout << tmp.str() << " (semi) " << eff << " +- " << err << endl;
			}
			if (db != 0.) {
				double eff, err;
				eff = d / db;
				err = sqrt(eff * (1 - eff) / db);
				effCounter_->setDiLeptonic(tmp.str(),eff);
				effErrors_->setDiLeptonic(tmp.str(), err);
				cout << tmp.str() << " (di) " << eff << " +- " << err << endl;
			}
			if (mb != 0.) {
				double eff, err;
				eff = m / mb;
				err = sqrt(eff * (1 - eff) / mb);
				effCounter_->setMultiLeptonic(tmp.str(), eff);
				effErrors_->setMultiLeptonic(tmp.str(), err);
				cout << tmp.str() << " (multi) " << eff << " +- " << err << endl;
			}
			binnedEff_->SetBinContent(i+1, effCounter_->getSemiLeptonic(tmp.str()));
			binnedEff_->SetBinError(i+1, effErrors_->getSemiLeptonic(tmp.str()));
		}


		eff_->SetBinContent(2, effBG_);
		eff_->SetBinError(2, deff_bg);

		eff_->SetBinContent(4, effSL_);
		eff_->SetBinError(4, deff_sl);

		eff_->SetBinContent(6, effDL_);
		eff_->SetBinError(6, deff_dl);

		eff_->SetBinContent(8, effML_);
		eff_->SetBinError(8, deff_ml);

		background_->SetBinContent(beforeBin_, bgBefore_);
		lep_->SetBinContent(beforeBin_, slBefore_);
		llep_->SetBinContent(beforeBin_, dlBefore_);
		multilep_->SetBinContent(beforeBin_, mlBefore_);

		cout << "#----- after -----#" << endl;
		log(sampleweight_, "::endJob >> sampleweight", false);
		setEnv(afterBin_);
		cout.precision(10);
		cout << "bg eff >> " << effBG_ << " +- " << deff_bg << endl;
		cout << "S eff >> " << effSL_ << " +- " << deff_sl << endl;
		cout << "ll eff >> " << effDL_ << " +- " << deff_dl << endl;
		cout << "ml eff >> " << effML_ << " +- " << deff_ml << endl;
	}
	//TODO: Fill in histogram.
	for (map<int, TopMuonCollection>::iterator iter = mothermap_.begin(); iter
			!= mothermap_.end(); iter++) {
		cout << "total matched mu from " << (*iter).first << " : "
				<< (*iter).second.size() << endl;
	}

}

void MatrixAnalyzer::setEnv(int &bin) {
	cout << "hadr >> " << whadrCount_ << "(" << hadrCount_ << ")" << "("
			<< rhadrCount_ << ")" << endl;
	cout << "lep >> " << wlCount_ << "(" << lCount_ << ")" << "(" << rlCount_
			<< ")" << endl;
	cout << "llep >> " << wllCount_ << "(" << llCount_ << ")" << "("
			<< rllCount_ << ")" << endl;
	cout << "mlep >> " << wmlCount_ << "(" << mlCount_ << ")" << "("
			<< rmlCount_ << ")" << endl;

	for (unsigned int i = 0; i < varBins_.size() - 1; i++) {
		std::stringstream tmp;
		tmp << varBins_.at(i);
		double b, s, d, m;
		b = weightedCounters_->getPureHadronic(tmp.str());
		s = weightedCounters_->getSemiLeptonic(tmp.str());
		d = weightedCounters_->getDiLeptonic(tmp.str());
		m = weightedCounters_->getMultiLeptonic(tmp.str());

		cout << varBins_[i] << " (had):" << b << endl;
		cout << varBins_[i] << " (semi):" << s << endl;
		cout << varBins_[i] << " (di):" << d <<endl;
		cout << varBins_[i] << " (multi):" << m << endl;
		if(bin == 2){
			binnedBkg_->SetBinContent(2*i+1, b);
			binnedSemiLep_->SetBinContent(2*i+1, s);
			binnedDiLep_->SetBinContent(2*i+1, d);
			binnedMultiLep_->SetBinContent(2*i+1, m);
		}
		else{
			binnedBkg_->SetBinContent(2*i+2, b);
			binnedSemiLep_->SetBinContent(2*i+2, s);
			binnedDiLep_->SetBinContent(2*i+2, d);
			binnedMultiLep_->SetBinContent(2*i+2, m);
		}

	}

	background_->SetBinContent(bin, whadrCount_);
	lep_->SetBinContent(bin, wlCount_);
	llep_->SetBinContent(bin, wllCount_);
	multilep_->SetBinContent(bin, wmlCount_);
}

void MatrixAnalyzer::getBefore() {
	bgBefore_ = getHist(pmodulename_, "mbg_N_background", beforeBin_);
	slBefore_ = getHist(pmodulename_, "mbg_N_semilepton", beforeBin_);
	dlBefore_ = getHist(pmodulename_, "mbg_N_dilepton", beforeBin_);
	mlBefore_ = getHist(pmodulename_, "mbg_N_multilepton", beforeBin_);
	for (unsigned int i = 0; i < varBins_.size() - 1; i++) {
		std::stringstream tmp;
		tmp << varBins_.at(i);
		double b, s, d, m;
		int bbin = 2 * i + 1;
		b = getHist(pmodulename_, "mbg_binnedBkg", bbin);
		s = getHist(pmodulename_, "mbg_binnedSemiLep", bbin);
		d = getHist(pmodulename_, "mbg_binnedDiLep", bbin);
		m = getHist(pmodulename_, "mbg_binnedMultiLep", bbin);

		weightedBefore_->setPureHadronic(tmp.str(), b);
		weightedBefore_->setSemiLeptonic(tmp.str(), s);
		weightedBefore_->setDiLeptonic(tmp.str(), d);
		weightedBefore_->setMultiLeptonic(tmp.str(), m);
	}
}

Double_t MatrixAnalyzer::getHist(TString dir, TString hist, int & bin) {
	TH1F *dummy;
	TString directory(dir);
	directory += "/";
	TString name;
	name = hist;
	directory += name;

	dummy = (TH1F*) f_->Get(directory);

	if (!dummy) {
		cerr << "WARNING:" << " Didn't find indicated hist" << " ["
				<< directory << "]" << endl;
		return 0.0;
	}
	return dummy->GetBinContent(bin);
}

int MatrixAnalyzer::numberOfmatchedMuons(
		edm::Handle<edm::View<pat::Muon> > recMuons,
		edm::Handle<edm::Association<reco::GenParticleCollection> > genMatch) {
	int matchedmu = 0;
	int size = recMuons->size();
	cout << "<pdgId, status, mother.pdgId>" << endl;
	cout << "ID: ";
	for (int i = 0; i < size; ++i) {
		edm::RefToBase<reco::Candidate> muonRef =
				recMuons->refAt(i)->originalObjectRef();
		reco::GenParticleRef genMuon = (*genMatch)[muonRef];

		int mid = 0;
		int st = 0;
		if (genMuon->numberOfMothers() > 0) {
			mid = genMuon->mother(0)->pdgId();
			st = genMuon->mother(0)->status();
			cout << "mothers " << genMuon->numberOfMothers() << endl;
			if (genMuon->mother(0)->numberOfMothers() > 0) {
				cout << genMuon->mother(0)->pdgId() << endl;
				cout << genMuon->mother(0)->status() << endl;
				cout << genMuon->mother(0)->numberOfMothers() << endl;
			}
		}

		cout << "<" << genMuon->pdgId() << "," << genMuon->status() << ","
				<< mid << "," << st << "> ";
		if (fabs(mid) == 13)
			matchedmu++;
	}
	cout << "\n";
	return matchedmu;
}

