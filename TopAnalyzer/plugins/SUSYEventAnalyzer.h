#ifndef SUSYEventAnalyzer_h  
#define SUSYEventAnalyzer_h

#include "TH1.h"
#include "TH2.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Math/interface/angle.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

class SUSYEventAnalyzer : public edm::EDAnalyzer {

 public:
  
  explicit SUSYEventAnalyzer(const edm::ParameterSet&);
  ~SUSYEventAnalyzer();

 private:

  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
           	
  //edm::InputTag inputGenEvent_;
  edm::InputTag src_;
  edm::InputTag met_;
  edm::InputTag jets_;


  TH1F *Missing_energy_;
  TH1F *HT_;
  TH1F *njets_;
  
  TH1F *tbW_red_;
  TH1F *btW_red_;
  TH1F *tWb_red_;
  TH1F *bWt_red_;
  TH1F *tt_red_;
  TH1F *all_red_;

  TH1F *tbW_;
  TH1F *btW_;
  TH1F *tWb_;
  TH1F *bWt_;
  TH1F *tt_;
  TH1F *bb_;
  TH1F *all_;

  TH2F *all_red_MET_;
  TH2F *all_red_HT_;
  TH2F *all_red_njets_;

};  

#endif  
