#ifndef IsolationMonitor_h
#define IsolationMonitor_h

#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "TopAnalysis/TopUtils/interface/RootSystem.h"
#include "TopAnalysis/TopUtils/interface/RootHistograms.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/MET.h"

class IsolationMonitor {
public:
	explicit IsolationMonitor();
//	IsolationMonitor(std::string);
	~IsolationMonitor();
	void book(ofstream& file);
	void fill(const pat::Muon&, const pat::MET&, double);
	void fill(std::string, double, double, double);
	/**
	 *  adds a histogram to the Isolation Monitor
	 */
	void addHist(std::string, TH2F*);
	/**
	 * prints the CorrelationFactors of the histograms
	 */
	void printCorrelation();
	/**
	 * Gives the correlation-factors of the histograms in a 
	 * map<histogramname,correlation-factor>
	 */
//	map<string,double> getCorrelationFactors();
	Double_t getCaloCorrelationFactor();
	Double_t getTrackCorrelationFactor();
	Double_t getCorrelationFactor(std::string);

private:
	std::map<string, TH2F*> histos_;
//	TH2F *trackIsoMET_;
//	TH2F *caloIsoMET_;
//	std::string name_;
	//	TH2F *minDisJetIsoMET_;
};
#endif
