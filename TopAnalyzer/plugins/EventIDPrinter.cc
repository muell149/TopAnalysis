#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include <string>

class EventIDPrinter : public edm::EDAnalyzer {

public:

    EventIDPrinter(const edm::ParameterSet&);
    ~EventIDPrinter();

protected:
    void beginJob();
    void analyze(const edm::Event&, const edm::EventSetup&);
    void endJob();
private:
    std::string outputString_;
    bool runOnMC_;
};

EventIDPrinter::EventIDPrinter( const edm::ParameterSet& ps ) {
    outputString_ = ps.getParameter<std::string>("outputString");
    runOnMC_ = ps.getParameter<bool>("runOnMC");
}


EventIDPrinter::~EventIDPrinter() {

}

void EventIDPrinter::beginJob() {
}

void EventIDPrinter::analyze(const edm::Event& evt, const edm::EventSetup& context) {
    if (runOnMC_ || evt.isRealData())
        std::cout << outputString_ << evt.eventAuxiliary().id() << std::endl;
}

void EventIDPrinter::endJob() {
}

DEFINE_FWK_MODULE( EventIDPrinter );
