#include "TopAnalysis/TopFilter/plugins/TriggerFilter.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"

using namespace edm;

TriggerFilter::TriggerFilter(const edm::ParameterSet& cfg)
{
    trigResults_ = cfg.getParameter<edm::InputTag>("TriggerResults");
    hltPaths_    = cfg.getParameter<std::vector<std::string> >("hltPaths" );
    vetoPaths_   = cfg.getParameter<std::vector<std::string> >("vetoPaths");
    printTriggers_ = cfg.getUntrackedParameter<bool>("printTriggers");
}

TriggerFilter::~TriggerFilter()
{
}

void
TriggerFilter::beginJob()
{
    n_TrigPaths = hltPaths_.size();
    n_VetoPaths = vetoPaths_.size();
}

bool
TriggerFilter::filter(edm::Event& evt, const edm::EventSetup&)
{
    Handle<TriggerResults> trigResults;
    evt.getByLabel(trigResults_, trigResults);

    if (trigResults.failedToGet()) {
        std::cerr << "Trigger: failed to get: " << trigResults_ << std::endl;
        return false;
    }

    bool pass = false;
    int n_Triggers = trigResults->size();

    TriggerNames trigName = evt.triggerNames(*trigResults);
    if (printTriggers_) {
        std::cout << std::endl
                  << "Run:Event " << evt.eventAuxiliary().run() << ":"
                  << evt.eventAuxiliary().event() << " - List of triggers:"
                  << std::endl;
    }

    for (int i_Trig = 0; i_Trig < n_Triggers; ++i_Trig) {
        if (printTriggers_) {
            std::cout << trigName.triggerName(i_Trig)
                      << (trigResults.product()->accept(i_Trig) ? " - has fired" : " - didn't fire")
                      << std::endl;
        }
        // triggers which have not fired are not of interest -> contiue
        if (!trigResults.product()->accept(i_Trig)) continue;
        // look if one of the HLT paths from config is among the paths having fired
        for (int i = 0; i < n_TrigPaths; i++) {
            // check for wildcards
            std::string path = hltPaths_[i].substr(0,hltPaths_[i].find('*'));
            std::string name = trigName.triggerName(i_Trig).substr(0,hltPaths_[i].find('*'));

            if (!(name==path)) continue;
            pass = true;
        }
        // don't pass the event if veto trigger has fired
        for (int i = 0; i<n_VetoPaths; i++) {
            // check for wildcards
            std::string path = vetoPaths_[i].substr(0,vetoPaths_[i].find('*'));
            std::string name = trigName.triggerName(i_Trig).substr(0,vetoPaths_[i].find('*'));
            if (!(name== path)) continue;
            return false;
        }
    }

    return pass;
}

void
TriggerFilter::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( TriggerFilter );
