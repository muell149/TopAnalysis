#include "TopAnalysis/TopAnalyzer/plugins/MatrixAnalyzer.h"

using std::cout;
using std::endl;
using reco::GenParticle;

MatrixAnalyzer::MatrixAnalyzer(const edm::ParameterSet& cfg) :
	hist_(cfg.getParameter<std::string>("hist")),
			pmodulename_(cfg.getParameter<std::string>("pmn")),
			before_(cfg.getParameter<bool>("before")),
			muons_(cfg.getParameter<edm::InputTag>("muons")) {
	debug_ = true;
	hadrCount_ = 0;
	lCount_ = 0;
	bgBefore_ = 0.0;
	slBefore_ = .0;
	llCount_= 0;
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
}

MatrixAnalyzer::~MatrixAnalyzer() {
}

void MatrixAnalyzer::beginJob(const edm::EventSetup&) {

	if (hist_.empty() )
		return;

	//TODO: Beim 2ten durchlauf sollen die histogramme geladen werden.
	edm::Service<TFileService> fs;
	if ( !fs) {
		throw edm::Exception( edm::errors::Configuration,
				"TFile Service is not registered in cfg file" );
	}
	f_ = &fs->file();
	ofstream hist(hist_.c_str(), std::ios::out);

	NameScheme nam("mbg");

	//make histograms
	background_ = fs->make<TH1F>(nam.name(hist, "N_background"),
			nam.name("background"), 300, 0, 1.);
	lep_ = fs->make<TH1F>(nam.name(hist, "N_semilepton"), nam.name("lepton"),
			300, 0, 1.);
	llep_ = fs->make<TH1F>(nam.name(hist, "N_dilepton"), nam.name("ll"), 300, 0,
			1.);
	multilep_ = fs->make<TH1F>(nam.name(hist, "N_multilepton"), nam.name("ml"),
			300, 0, 1.);
	eff_ = fs->make<TH1F>(nam.name(hist, "efficency"), nam.name("eff"), 300, 0,
			1.);

	//set number of bins (noBins_)
	background_->SetBins(noBins_, 0., 5.);
	lep_->SetBins(noBins_, 0., 5.);
	llep_->SetBins(noBins_, 0., 5.);
	multilep_->SetBins(noBins_, 0., 5.);
	eff_->SetBins(9, 0., 5.);
}

void MatrixAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& setup) {

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

	edm::Handle<edm::Association<reco::GenParticleCollection> > genMatch;
	evt.getByLabel("muonMatch", genMatch);

	edm::Handle<double> weightHandle;
	evt.getByLabel("eventWeight", weightHandle);

	sampleweight_ = *weightHandle;
	//	cout << "sw: " << sampleweight_ << endl;

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

	if (muons->size() < 1) {
		hadrCount_++;
		whadrCount_ += sampleweight_;
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
	//    if(!make_)
	//    {
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
		if (bgBefore_ !=0) {
			effBG_ = hadrCount_/bgBefore_;
			deff_bg = sqrt(effBG_*(1-effBG_)/bgBefore_);
		}

		if (slBefore_ != 0) {
			effSL_ = lCount_/slBefore_;
			deff_sl = sqrt(effSL_*(1-effSL_)/slBefore_);
			//log(deffs, "::endjob >> delta_eff", true);
		}

		if (dlBefore_ != 0) {
			effDL_ = llCount_/dlBefore_;
			deff_dl = sqrt(effDL_*(1-effDL_)/dlBefore_);
		}

		if (mlBefore_ != 0) {
			effML_ = mlCount_/mlBefore_;
			deff_ml = sqrt(effML_*(1-effML_)/mlBefore_);
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
		cout << "total matched mu from " << (*iter).first << " : " << (*iter).second.size() << endl;
	}

}

void MatrixAnalyzer::setEnv(int &bin) {
	cout << "hadr >> " << whadrCount_<< "(" << hadrCount_ << ")"<< "("
			<< rhadrCount_ << ")" << endl;
	cout << "lep >> " << wlCount_ << "(" << lCount_ << ")" << "(" << rlCount_
			<< ")" << endl;
	cout << "llep >> " <<wllCount_ << "(" << llCount_ << ")" << "("
			<< rllCount_ << ")" << endl;
	cout << "mlep >> " << wmlCount_ << "(" << mlCount_ << ")" << "("
			<< rmlCount_ << ")" << endl;

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
}

Double_t MatrixAnalyzer::getHist(TString dir, TString hist, int & bin) {
	TH1F *dummy;
	TString directory(dir);
	directory+="/";
	TString name;
	name = hist;
	directory+=name;

	dummy = (TH1F*)f_->Get(directory);

	if ( !dummy) {
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
	for (int i=0; i< size; ++i) {
		edm::RefToBase<reco::Candidate> muonRef = recMuons->refAt(i)->originalObjectRef();
		reco::GenParticleRef genMuon = (*genMatch)[muonRef];

		int mid = 0;
		int st = 0;
		if (genMuon->numberOfMothers() > 0) {
			mid = genMuon->mother(0)->pdgId();
			st = genMuon->mother(0)->status();
			cout << "mothers " <<genMuon->numberOfMothers() << endl;
			if (genMuon->mother(0)->numberOfMothers() > 0) {
				cout << genMuon->mother(0)->pdgId() << endl;
				cout << genMuon->mother(0)->status() << endl;
				cout << genMuon->mother(0)->numberOfMothers() << endl;
			}
		}

		cout << "<" << genMuon->pdgId() << "," << genMuon->status()<< ","
				<< mid << "," << st<<"> ";
		if (fabs(mid) == 13)
			matchedmu++;
	}
	cout << "\n";
	return matchedmu;
}

