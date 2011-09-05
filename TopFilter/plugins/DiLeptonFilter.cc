#include "TopAnalysis/TopFilter/plugins/DiLeptonFilter.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

/// default constructor
DiLeptonFilter::DiLeptonFilter ( const edm::ParameterSet& cfg ) :
    electrons_ ( cfg.getParameter<edm::InputTag> ( "electrons" ) ),
    muons_ ( cfg.getParameter<edm::InputTag> ( "muons" ) ),
    isVeto_ ( cfg.getParameter<bool> ( "isVeto" ) ),
    Cut_ ( cfg.getParameter<std::vector<double> > ( "Cut" ) ),
    fltrChrg_ ( cfg.getParameter<int> ( "filterCharge" ) )
{

    produces<std::vector<pat::Electron> >();
    produces<std::vector<pat::Muon> >();

}

/// default destructor
DiLeptonFilter::~DiLeptonFilter()
{
}

/// sanity check
void
DiLeptonFilter::beginJob()
{
    if ( Cut_.size() !=2 )  edm::LogError ( "DiLeptonFilter" ) << "Cut has wrong size. Size has to be 2!\n";
    if ( Cut_[0]>Cut_[1] ) edm::LogError ( "DiLeptonFilter" ) << "Lower cut value is higher than upper one!\n";
}

/// event veto
bool
DiLeptonFilter::filter ( edm::Event& event, const edm::EventSetup& setup )
{
    enum channel_t { kMM, kEM, kEE };
    // fetch the input collections from the event content
    edm::Handle<std::vector<pat::Electron> > electrons;
    event.getByLabel ( electrons_, electrons );

    edm::Handle<std::vector<pat::Muon> > muons;
    event.getByLabel ( muons_, muons );

    // skip events with less than 2 leptons
    if ( electrons->size() + muons->size() < 2 ) return false;

    double maxsumpt = -1;
    const reco::RecoCandidate *lep1 = 0, *lep2 = 0;
    channel_t channel;
    
    //mumu combinations
    for (std::vector<pat::Muon>::const_iterator muon1 = muons->begin(); muon1 != muons->end(); ++muon1) {
        for (std::vector<pat::Muon>::const_iterator muon2 = muon1+1; muon2 != muons->end(); ++muon2) {
            if (! fltrChrg_ || muon1->charge()*muon2->charge() == fltrChrg_) {
                double sumpt = muon1->pt() + muon2->pt();
                if (sumpt > maxsumpt) {
                    //we have found a better solution
                    maxsumpt = sumpt;
                    lep1 = &(*muon1);
                    lep2 = &(*muon2);
                    channel = kMM;
                } else break;
            }
        }
    }
    
    //emu combinations
    for (std::vector<pat::Muon>::const_iterator muon = muons->begin(); muon != muons->end(); ++muon) {
        for (std::vector<pat::Electron>::const_iterator elec = electrons->begin(); elec != electrons->end(); ++elec) {
            if (! fltrChrg_ || muon->charge()*elec->charge() == fltrChrg_) {
                double sumpt = muon->pt() + elec->pt();
                if (sumpt > maxsumpt) {
                    //we have found a better solution
                    maxsumpt = sumpt;
                    lep1 = &(*muon);
                    lep2 = &(*elec);
                    channel = kEM;
                } else break;
            }
        }
    }
    
    //ee combinations
    for (std::vector<pat::Electron>::const_iterator elec1 = electrons->begin(); elec1 != electrons->end(); ++elec1) {
        for (std::vector<pat::Electron>::const_iterator elec2 = elec1+1; elec2 != electrons->end(); ++elec2) {
            if (! fltrChrg_ || elec1->charge()*elec2->charge() == fltrChrg_) {
                double sumpt = elec1->pt() + elec2->pt();
                if (sumpt > maxsumpt) {
                    //we have found a better solution
                    maxsumpt = sumpt;
                    lep1 = &(*elec1);
                    lep2 = &(*elec2);
                    channel = kEE;
                } else break;
            }
        }
    }
    
    if (maxsumpt < 0) return false;

    double diLeptonMass = (lep1->p4() + lep2->p4()).M();
    
    // check if events in mass window are to be selected or vetoed
    if ( isVeto_ ) {
        if ( diLeptonMass >= Cut_[0] && diLeptonMass <= Cut_[1] ) return false;
    } else {
        if ( diLeptonMass < Cut_[0] || diLeptonMass > Cut_[1] ) return false;
    }
    
    // prepare result vectors
    std::auto_ptr<std::vector<pat::Electron> > selectedElectrons ( new std::vector<pat::Electron> );
    std::auto_ptr<std::vector<pat::Muon> > selectedMuons ( new std::vector<pat::Muon> );

    if (channel == kEE) {
        selectedElectrons->push_back(* static_cast<const pat::Electron*>(lep1));
        selectedElectrons->push_back(* static_cast<const pat::Electron*>(lep2));
    } else if (channel == kEM) {
        selectedMuons->push_back(* static_cast<const pat::Muon*>(lep1));
        selectedElectrons->push_back(* static_cast<const pat::Electron*>(lep2));
    } else {
        selectedMuons->push_back(* static_cast<const pat::Muon*>(lep1));
        selectedMuons->push_back(* static_cast<const pat::Muon*>(lep2));
    }

    event.put ( selectedElectrons );
    event.put ( selectedMuons );

    return true;
}
