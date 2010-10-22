#ifndef HTlepTemplate_h
#define HTlepTemplate_h

#include "TTree.h"
#include "TopAnalysis/TopAnalyzer/interface/DoubleObject.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

/**
   \class   HTlepTemplate HTlepTemplate.h "TopAnalysis/TopAnalyzer/interface/HTlepTemplate.h"

*/

class HTlepTemplate : public DoubleObject<const edm::View<reco::MET>, const edm::View<pat::Muon> > {

public:
  /// default constructor for fw lite
  explicit HTlepTemplate();
  /// default constructor for fw full
  explicit HTlepTemplate(const edm::ParameterSet&);
  /// default destructor
  ~HTlepTemplate(){};

  /// histogram booking for fw lite 
  void book();
  /// histogram booking for fw full
  void book(edm::Service<TFileService>& fileService);
  /// tree filling
  void fill(const edm::View<reco::MET>& met, const double& weight=1.);
  /// tree filling
  void fill(const edm::View<reco::MET>& met, const edm::View<pat::Muon>& muon, const double& weight=1.);
  /// everything after the filling of the histograms
  void process();
  
 private:

  TTree* tree;
  float MET;
  float lepET;
  float HTlep;
  float relIso;
  float dB;

};

#endif
