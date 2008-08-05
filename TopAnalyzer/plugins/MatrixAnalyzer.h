#ifndef MatrixAnalyzer_h
#define MatrixAnalyzer_h
/**
 *  class:   MatrixAnalyzer.h
 * @author: Lukas Kreczko, Uni Hamburg (lkreczko@mail.desy.de)
 * version $Id: MatrixAnalyzer.h,v 1.2 2008/07/24 14:07:11 kreczko Exp $

 ________________________________________________________________**/
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/Candidate/interface/CandMatchMap.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "TopAnalysis/TopUtils/interface/RootSystem.h"
#include "TopAnalysis/TopUtils/interface/RootHistograms.h"

class MatrixAnalyzer: public edm::EDAnalyzer {

public:
	explicit MatrixAnalyzer(const edm::ParameterSet&);
	~MatrixAnalyzer();

private:
	virtual void beginJob(const edm::EventSetup&);
	virtual void analyze(const edm::Event&, const edm::EventSetup&);
	virtual void endJob();
	virtual void setEnv(int &);
	virtual void getBefore();
	virtual Double_t getHist(TString, TString, int&);
	//	virtual int pdgOfMother(pat::Muon matchedMuon,edm::Handle<reco::GenParticleCollection> genParticles);
	//	virtual bool matchedMuonIsContainedInDaughter(reco::GenParticleCollection::const_iterator part, reco::Muon muon);
	template<typename T1, typename T2> void log(T1 msg, T2 from, bool debug) {
		if (debug && debug_ || !debug)
			cout << from << ": " << msg << endl;
	}
	int numberOfmatchedMuons(edm::Handle<edm::View<pat::Muon> >,
			edm::Handle<edm::Association<reco::GenParticleCollection> >);
	std::string hist_, pmodulename_;
	bool before_, debug_;
	//int numberOfSignalL, numberOfSignalT, numberOfBgL, numberOfBgT;
	//double eff_Signal, eff_Bg;
	int hadrCount_, lCount_, llCount_, mlCount_, noBins_, beforeBin_, afterBin_;
	int rhadrCount_, rlCount_, rllCount_, rmlCount_;
	double whadrCount_, wlCount_, wllCount_, wmlCount_;
	Double_t bgBefore_, slBefore_, dlBefore_, mlBefore_;
	double effBG_, effSL_, effDL_, effML_, sampleweight_;
	edm::InputTag muons_;
	typedef std::vector<pat::Muon> TopMuonCollection;

	std::map<int, TopMuonCollection> mothermap_;
	TH1F *background_;

	TH1F *lep_;

	TH1F *llep_;

	TH1F * multilep_;

	TH1F *eff_;

	TFile *f_;

	//TODO: boolean for before and after. use same histogramms, but different bins
	//TODO: try to find a way to store double directly in root file

	class LeptonCounter {
	public:
		LeptonCounter() {
			slep = 0;
			dlep = 0;
			mlep = 0;
			had = 0;
		}

		void addSemiLeptonic() {
			slep++;
		}

		void addDiLeptonic() {
			dlep++;
		}

		void MaddMultiLeptonic() {
			mlep++;
		}

		void addPureHadronic() {
			had++;
		}

		int getSemiLeptonic() {
			return slep;
		}

		int getDiLeptonic() {
			return dlep;
		}

		int getMultiLeptonic() {
			return mlep;
		}

		int getPureHadronic() {
			return had;
		}
		//		explicit LeptonCounter();
		//		~LeptonCounter();
		//		void addSemiLeptonic();
		//		void addDiLeptonic();
		//		void addPureHadronic();
		//		void addMultiLeptonic();
		//		int getSemiLeptonic();
		//		int getDiLeptonic();
		//		int getMultiLeptonic();
		//		int getPureHadronic();
	private:
		int slep, dlep, mlep, had;

	};

};
#endif
