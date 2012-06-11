#ifndef EventWeightAnalyzer_h_
#define EventWeightAnalyzer_h_

#include <memory>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include <TROOT.h>
#include <TObject.h>
#include <TFile.h>
#include <TH1.h>

class EventWeightAnalyzer : public edm::EDAnalyzer {

   public:
      explicit EventWeightAnalyzer(const edm::ParameterSet&);
      ~EventWeightAnalyzer();

   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data --------------------------- 

      TH1F* histoEventWeightAbs ;
      TH1F* histoEventWeightNorm;

      edm::InputTag inTag_EventWeight;
};

#endif
