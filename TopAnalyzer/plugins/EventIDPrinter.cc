#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include <string>
#include <DataFormats/PatCandidates/interface/Jet.h>
#include <DataFormats/PatCandidates/interface/Muon.h>
#include <DataFormats/PatCandidates/interface/MET.h>

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
    bool showDetails_;
    edm::InputTag elecs_;
    edm::InputTag muons_;
    edm::InputTag jets_;
    edm::InputTag mets_;
};

EventIDPrinter::EventIDPrinter( const edm::ParameterSet& ps ) {
    outputString_ = ps.getParameter<std::string>("outputString");
    runOnMC_ = ps.getParameter<bool>("runOnMC");
    showDetails_ = ps.getParameter<bool>("showDetails");
    elecs_ = ps.getParameter<edm::InputTag>("elecs");
    muons_ = ps.getParameter<edm::InputTag>("muons");
    jets_ = ps.getParameter<edm::InputTag>("jets");
    mets_ = ps.getParameter<edm::InputTag>("mets");
}


EventIDPrinter::~EventIDPrinter() {

}

void EventIDPrinter::beginJob() {
}

void EventIDPrinter::analyze(const edm::Event& evt, const edm::EventSetup& context) {
    if (runOnMC_ || evt.isRealData()) {
        std::cout << outputString_ << evt.eventAuxiliary().id() << std::endl;
        if (showDetails_) {
            edm::Handle< std::vector<pat::Muon> > muons;
            evt.getByLabel(muons_, muons);
            std::cout << outputString_;
            for (std::vector<pat::Muon>::const_iterator it = muons->begin(); it != muons->end(); ++it) {
                std::cout << "Muon pT: " << it->pt() << "\teta: " << it->eta() << "\t";
                std::cout << "pfiso: " << (it->chargedHadronIso()+it->neutralHadronIso()+it->photonIso()) / it->pt()  << "\t";
            }
            std::cout << std::endl;

            edm::Handle< std::vector<pat::Electron> > electrons;
            evt.getByLabel(elecs_, electrons);
            std::cout << outputString_;
            for (std::vector<pat::Electron>::const_iterator it = electrons->begin(); it != electrons->end(); ++it) {
                std::cout << "Electron pT: " << it->pt() << "\teta: " << it->eta() << "\t";
                std::cout << "pfiso: " << (it->chargedHadronIso()+it->neutralHadronIso()+it->photonIso()) / it->pt()  << "\t";
            }
            std::cout << std::endl;

            edm::Handle< std::vector<pat::Jet> > jets;
            evt.getByLabel(jets_, jets);
            std::cout << outputString_;
            for (std::vector<pat::Jet>::const_iterator it = jets->begin(); it != jets->end(); ++it) {
                std::cout << "Jet pT: " << it->pt() << "\teta: " << it->eta() << "\t";
            }
            std::cout << std::endl;

            edm::Handle< std::vector<pat::MET> > mets;
            evt.getByLabel(mets_, mets);
            std::cout << outputString_;
            for (std::vector<pat::MET>::const_iterator it = mets->begin(); it != mets->end(); ++it) {
                std::cout << "MET eT: " << it->et() << "\tphi: " << it->phi() << "\t";
            }
            std::cout << std::endl;

        }
    }
}

void EventIDPrinter::endJob() {
}

DEFINE_FWK_MODULE( EventIDPrinter );
