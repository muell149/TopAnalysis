#ifndef GenLevelBJetAnalyzer_h
#define GenLevelBJetAnalyzer_h


/**
  \class GenLevelBJetAnalyzer GenLevelBJetAnalyzer.cc TopAnalysis/TopAnalyzer/plugins/GenLevelBJetAnalyzer.cc

  \brief matches GenJets versus b-hadrons

  * Identifies the b(c)-Jets inside the generator jets by matching it with the b(c)-hadrons.
*/


// system include files
#include <memory>
#include <algorithm>


// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

// added by me
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "AnalysisDataFormats/TopObjects/interface/TtGenEvent.h"

#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH1D.h"
#include "TH1I.h"
#include "TH2D.h"

//
// class declaration
//

class GenLevelBJetAnalyzer : public edm::EDAnalyzer
{
public:
    explicit GenLevelBJetAnalyzer ( const edm::ParameterSet& );
    ~GenLevelBJetAnalyzer();

//    static void fillDescriptions ( edm::ConfigurationDescriptions& descriptions );

private:
    virtual void beginJob() ;
    virtual void analyze( const edm::Event&, const edm::EventSetup& );
    virtual void endJob() ;

    virtual void beginRun ( edm::Run&, edm::EventSetup const& );
    virtual void endRun ( edm::Run&, edm::EventSetup const& );
    virtual void beginLuminosityBlock ( edm::LuminosityBlock&, edm::EventSetup const& );
    virtual void endLuminosityBlock ( edm::LuminosityBlock&, edm::EventSetup const& );

    std::vector<int> findHadronJets ( 
        const reco::GenJetCollection& genJets,  
        std::vector<int> &hadIndex, 
        std::vector<reco::GenParticle> &hadMothersGenPart, 
        std::vector<std::vector<int> > &hadMothersIndices, 
        std::vector<int> &hadFlavour );
    std::vector<int> getGenJetWith ( 
        const reco::Candidate* bQuark, 
        const reco::GenJetCollection& genJets, 
        std::vector<reco::GenParticle> &bHadronObjects, 
        std::vector<bool> &isFromBquark, 
        std::vector<int> &bHadronsInJet );
    int getGenJetNear ( const reco::Candidate* particle, std::vector<const reco::GenJet*> &genJets );
    typedef const reco::Candidate* pCRC;
    int analyzeMothers ( 
        const reco::Candidate* thisParticle, 
        pCRC *hadron, 
        std::vector<const reco::Candidate*> &hadMothers, 
        std::vector<std::vector<int> > &hadMothersIndices, 
        std::set<const reco::Candidate*> *analyzedParticles, 
        const int prevPartIndex );
    bool searchInMothers ( 
        const reco::Candidate* bQuark, 
        const reco::Candidate* thisParticle, 
        std::vector<const reco::Candidate*> particleChain, 
        pCRC *bHadron );
    bool putMotherIndex ( std::vector<std::vector<int> > &hadMothersIndices, int partIndex, int mothIndex );
    bool isHadron ( const int flavour, const reco::Candidate* thisParticle );
    bool isHadronPdgId ( const int flavour, const int pdgId );
    bool hasHadronDaughter ( const int flavour, const reco::Candidate* thisParticle );
    int isInList ( std::vector<const reco::Candidate*> particleList, const reco::Candidate* particle );
    void findInMothers ( 
        int idx, std::vector<int> &mothChains, 
        std::vector<std::vector<int> > &hadMothersIndices, 
        std::vector<reco::GenParticle> &hadMothers, 
        int status, int pdgId, bool pdgAbs, int firstLast, bool verbose );
    bool isNeutralPdg ( int pdgId );

    bool checkForLoop ( std::vector<const reco::Candidate*> &particleChain, const reco::Candidate* particle );
    std::string getParticleName ( int id ) const;

    bool fixExtraSameFlavours(
        const unsigned int hadId, const std::vector<int> &hadIndices, const std::vector<reco::GenParticle> &hadMothers, 
        const std::vector<std::vector<int> > &hadMothersIndices, const std::vector<std::vector<int> > &LastQuarkIds, 
        const std::vector<std::vector<int> > &LastQuarkMotherIds, std::vector<int> &lastQuarkIndices, std::vector<int> &hadronFlavour, 
        const int lastQuarkIndex);

    inline std::string printJetInfo ( const size_t iJet, const reco::GenJet* ) const;
    inline std::string printParticleChain ( const std::vector<const reco::Candidate*> &particleChain, const reco::Candidate *bHadron ) const;

// ----------member data ---------------------------
    edm::InputTag ttGenEvent_;
    edm::InputTag genJets_;
    double deltaR_;
    int flavour_;
    bool noBBbarResonances_;
    bool requireTopBquark_;
    bool resolveName_;
    bool doImprovedHadronMatching_;
    bool doValidationPlotsForImprovedHadronMatching_;
    bool toPlot;

    std::string flavourStr_;  // Name of the flavour specified in config file

    edm::ESHandle<ParticleDataTable> pdt_;


// -- testing histograms
    TH1I *h_nHad, *h_hadJetIndex;
    TH2D *h2_Q2MothPdg, *h2_Q2Moth_2Pdg;
    TH1D *h_jetdPt, *h_jetDeltaPt;
    TH2D *h2_QQMothSamePdg;
    TH1D *h_QQMothEFrac, *h_QHQPtFrac, *h_QQMothdR, *h_QQMothdR_min, *h_QHQdR;
    TH1D *h_QQMothEFrac_ambig, *h_QHQPtFrac_ambig, *h_QQMothdR_ambig, *h_QQMothdR_min_ambig, *h_QHQdR_ambig;
    TH1D *h_jetHad_dR, *h_jetHadOld_dR, *h_jetHadOldNoMatch_dR, *h_jetHad_dR_noFlav, *h_jetHadOldNoMatch_dR_noFlav;

    TH1I *h_nFirstQ,*h_firstQstatus, *h_firstQPdg;
    TH2D *h2_firstQFlav_HadFlav, *h2_firstQFlav_QMotherFlav;
    TH1I *h_nLastQ,*h_lastQstatus, *h_lastQPdg, *h_nHadTop, *h_nHadHiggs, *h_nHadGluon, *h_nHadZ, *h_nHadNo;
    TH2D *h2_lastQFlav_HadFlav, *h2_lastQFlav_QMotherFlav, *h2_lastQPdg_QMotherPdg;
    TH1D *h_lastQ_lastQ_dRmin, *h_hadJet_dRmin;
    TH1D *h_dEHadJet_T, *h_dEHadJet_H, *h_dEHadJet_Z, *h_dEHadJet_G, *h_dEHadJet_P, *h_dEHadJet_Q, *h_dEHadJet_Other, *h_dEHadJet[7];
    TH1I *h_nHadInJet, *h_hadFlavour;


};

#endif
