#ifndef DiElectronAnalyzer_h
#define DiElectronAnalyzer_h

#include <iostream>

#include "TH1D.h"
#include "TString.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"


class DiElectronAnalyzer : public edm::EDAnalyzer {

public:
  /// default constructor
  explicit DiElectronAnalyzer(const edm::ParameterSet&);
  /// default destructor
  ~DiElectronAnalyzer();

private:
  /// everything which has to be done before the event loop: book fileservice and histograms
  virtual void beginJob();
  /// everything which has to be done during the event loop: analyze and fill histos
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  /// everything which has to be done after the event loop: empty
  virtual void endJob();

  /// input electron collection
  edm::InputTag electrons_;
  /// mass bins in which number of entries is counted
  std::vector<double> massBins_;
  /// input bool: use a event weight?
  bool useEvtWgt_;
  /// input bool: correct histos to width of log bins?
  bool correct2width_;
  /// define a PatElectronCollection as a vector of PatElectrons
  typedef std::vector<pat::Electron> PatElectronCollection;
  /// true if leading electrons have same charge
  bool isWrongCharge;
  /// log binning plot for right-charge dielectron mass
  TH1D * dimassLogRC_;
  /// log binning plot for wrong-charge dielectron mass
  TH1D * dimassLogWC_;
  /// plot for right-charge dielectron mass
  TH1D * dimassRC_;
  /// plot for wrong-charge dielectron mass
  TH1D * dimassWC_;
  /// dr between leading electrons, unlike sign
  TH1D * drElRC_;
  /// dr between leading electrons, like sign
  TH1D * drElWC_;
  /// number of electrons
  TH1D * nEl_;


  /// counts number of entries in given bins of invariant mass (will be used for DY BG estiamtion)
  TH1D * nEntries_;
};

#endif
