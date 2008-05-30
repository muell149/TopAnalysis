#ifndef CutAnalyzer_h
#define CutAnalyzer_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"



#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"


//analyzer classes\ histogramm classes
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "TopAnalysis/TopFilter/interface/CutAnalyzer_fwd.h"

#include "TopAnalysis/TopAnalyzer/interface/JetId.h"
#include "TopAnalysis/TopAnalyzer/interface/JetKinematic.h"
#include "TopAnalysis/TopAnalyzer/interface/JetResolution.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopAnalyzer/interface/MuonId.h"
#include "TopAnalysis/TopAnalyzer/interface/MuonKinematic.h"
#include "TopAnalysis/TopAnalyzer/interface/MuonResolution.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "TopAnalysis/TopAnalyzer/interface/ElecId.h"
#include "TopAnalysis/TopAnalyzer/interface/ElecKinematic.h"
#include "TopAnalysis/TopAnalyzer/interface/ElecResolution.h"

//FIXME: Needs extension to analyze electrons as well

template <typename LeptonType, typename Id, typename Kin, typename Res>
class CutAnalyzer : public edm::EDAnalyzer {

 public:

  explicit CutAnalyzer(const edm::ParameterSet&);
  ~CutAnalyzer();
  
 private:
  
  virtual void beginJob(const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();
  
 private:
  edm::InputTag jets_;
  edm::InputTag leps_;
  edm::InputTag wgt_;
  std::string hist_;
  //std::string histJet_;
  bool passedFilter_;
  bool doId_,  doKin_, doRes_;
  bool doIdJet_,  doKinJet_, doResJet_;
  bool JetPtFilterOn_, JetEtaFilterOn_;
  bool MuonPtFilterOn_, MuonEtaFilterOn_;
  bool MuonJetIsolationFilterOn_, MuonCaloIsolationFilterOn_, MuonTrackIsolationFilterOn_;
 
 //class objects
  JetPtFilter *jetPtFilter_;
  JetEtaFilter *jetEtaFilter_; 
  MuonPtFilter *muonPtFilter_;
  MuonEtaFilter *muonEtaFilter_;
  MuonJetIsolationFilter *muonJetIsoFilter_;
  MuonCaloIsolationFilter *muonCaloIsoFilter_;
  MuonTrackIsolationFilter *muonTrackIsoFilter_;
  /* ElecPtEventFilter; */
/*   ElecEtaEventFilter; */
/*   ElecJetIsolationEventFilter; */
/*   ElecCaloIsolationEventFilter; */
/*   ElecTrackIsolationEventFilter; */
  Id  *id_;
  Kin *kin_;
  Res *res_;

  JetId  *idJet_;
  JetKinematic *kinJet_;
  JetResolution *resJet_;

};


template <typename LeptonType, typename Id, typename Kin, typename Res> 
CutAnalyzer<LeptonType, Id, Kin, Res>::CutAnalyzer(const edm::ParameterSet& cfg):
     jets_( cfg.getParameter<edm::InputTag>( "jets" ) ),
     leps_( cfg.getParameter<edm::InputTag>( "input" ) ),
     wgt_( cfg.getParameter<edm::InputTag>( "weight" ) ),
     hist_ ( cfg.getParameter<std::string>( "hist" ) ),
     doId_ ( cfg.getParameter<bool>( "id"  ) ),
     doKin_( cfg.getParameter<bool>( "kinematics" ) ),
     doRes_( cfg.getParameter<bool>( "resolution" ) ),
     doIdJet_ ( cfg.getParameter<bool>( "idJet"  ) ),
     doKinJet_( cfg.getParameter<bool>( "kinematicsJet" ) ),
     doResJet_( cfg.getParameter<bool>( "resolutionJet" ) ),
     JetPtFilterOn_( cfg.getParameter<bool>( "JetPtFilterOn" ) ),
     JetEtaFilterOn_( cfg.getParameter<bool>( "JetEtaFilterOn" ) ),
     MuonPtFilterOn_( cfg.getParameter<bool>("MuonPtFilterOn" ) ),
     MuonEtaFilterOn_( cfg.getParameter<bool>( "MuonEtaFilterOn" ) ),
     MuonJetIsolationFilterOn_( cfg.getParameter<bool>( "MuonJetIsolationFilterOn" ) ),
     MuonCaloIsolationFilterOn_( cfg.getParameter<bool>( "MuonCaloIsolationFilterOn" ) ),
     MuonTrackIsolationFilterOn_( cfg.getParameter<bool>( "MuonTrackIsolationFilterOn" ) )


  {  
  //initialize filter classes using explicit constructor
 
  if (JetPtFilterOn_) jetPtFilter_ = new JetPtFilter(cfg.getParameter<std::string>( "JetPt_name" ),cfg.getParameter<vector <double> >( "JetminPt" ),cfg.getParameter<vector <double> >( "JetmaxPt" ) );
  if (JetEtaFilterOn_) jetEtaFilter_ = new JetEtaFilter (cfg.getParameter<std::string>( "JetEta_name" ),cfg.getParameter<vector <double> >( "JetminEta" ),cfg.getParameter<vector <double> >( "JetmaxEta" ));
  if (MuonPtFilterOn_) muonPtFilter_= new MuonPtFilter (cfg.getParameter<std::string>( "MuonPt_name" ),cfg.getParameter<vector <double> >( "MuonminPt" ),cfg.getParameter<vector <double> >( "MuonmaxPt" ));
  if (MuonEtaFilterOn_) muonEtaFilter_= new MuonEtaFilter (cfg.getParameter<std::string>( "MuonEta_name" ),cfg.getParameter<vector <double> >( "MuonminEta" ),cfg.getParameter<vector <double> >( "MuonmaxEta" ));
  if (MuonJetIsolationFilterOn_) muonJetIsoFilter_ = new MuonJetIsolationFilter (cfg.getParameter<std::string>( "MuonJetIsolation_name" ),cfg.getParameter<vector <double> >( "JetIsolation" ), cfg.getParameter<edm::InputTag>("jets"));
  if (MuonCaloIsolationFilterOn_) muonCaloIsoFilter_ = new MuonCaloIsolationFilter (cfg.getParameter<std::string>( "MuonCaloIsolation_name" ),cfg.getParameter<vector <double> >( "CaloIsolation" ));
  if (MuonTrackIsolationFilterOn_) muonTrackIsoFilter_ = new MuonTrackIsolationFilter (cfg.getParameter<std::string>( "MuonTrackIsolation_name" ),cfg.getParameter<vector <double> >( "TrackIsolation" ));
  //... all filters


  //initialize histo classes
  if( doId_ ) id_  = new Id( cfg );
  if( doKin_) kin_ = new Kin( cfg );
  if( doRes_) res_ = new Res( cfg );
  if( doIdJet_ ) idJet_  = new JetId ( cfg );
  if( doKinJet_) kinJet_ = new JetKinematic( cfg );
  if( doResJet_) resJet_ = new JetResolution( cfg );


}


template <typename LeptonType, typename Id, typename Kin, typename Res> 
CutAnalyzer<LeptonType, Id, Kin, Res>::~CutAnalyzer()
{ 
  //delete class instances
  if( doId_ ) delete id_;
  if( doKin_) delete kin_;
  if( doRes_) delete res_;
  if( doIdJet_ ) delete idJet_;
  if( doKinJet_) delete kinJet_;
  if( doResJet_) delete resJet_;

}


template <typename LeptonType, typename Id, typename Kin, typename Res> 
void CutAnalyzer<LeptonType, Id, Kin, Res>::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{
  edm::Handle<double> wgt;
  evt.getByLabel(wgt_, wgt);
  double weight = *wgt;

  edm::Handle<std::vector<pat::Jet> > jets; 
  evt.getByLabel(jets_, jets);
  
  edm::Handle<LeptonType> leps; 
  evt.getByLabel(leps_, leps);
  LeptonType lepton = *leps;

  //check if event passes all N-1(x) filters
  passedFilter_=true;
  if (JetPtFilterOn_) {
     if (!jetPtFilter_->operator()( evt,*jets)){
      passedFilter_ = false; 
    
    }
  }
  if (JetEtaFilterOn_) {
    if (!jetEtaFilter_->operator()(evt,*jets)){
      passedFilter_ = false; 
     
    }
  }
 if (MuonPtFilterOn_) {
    if (!muonPtFilter_->operator()(evt,lepton)){
      passedFilter_ = false; 
     
    }
  }
  if (MuonEtaFilterOn_) {
    if (!muonEtaFilter_->operator()(evt,lepton)){
      passedFilter_ = false; 
      
    }
  }
 if (MuonJetIsolationFilterOn_) {
    if (!muonJetIsoFilter_->operator()(evt,lepton)){
      passedFilter_ = false; 
    
    }
  }
  if (MuonCaloIsolationFilterOn_) {
    if (!muonCaloIsoFilter_->operator()(evt,lepton)){
      passedFilter_ = false; 
     
    }
  }  
  if (MuonTrackIsolationFilterOn_) {
    if (!muonTrackIsoFilter_->operator()(evt,lepton)){
      passedFilter_ = false; 
     
    }
  }


  if (passedFilter_){
    if( doId_ ) id_ ->fill(evt, lepton, weight );
    if( doKin_) kin_->fill(evt, lepton, weight );
    if( doRes_) res_->fill(evt, lepton, weight );
    if( doIdJet_ ) idJet_ ->fill(evt, *jets, weight );
    if( doKinJet_) kinJet_->fill(evt, *jets, weight );
    if( doResJet_) resJet_->fill(evt, *jets, weight );



  }
}
//template <typename Collection, typename Id, typename Kin, typename Res> 
template <typename LeptonType, typename Id, typename Kin, typename Res> 
void CutAnalyzer<LeptonType, Id, Kin, Res>::beginJob(const edm::EventSetup&)
{
  if(hist_.empty()){
    if( doId_ ) id_ ->book(    );
    if( doKin_) kin_->book(    );
    if( doRes_) res_->book(    );
    if( doIdJet_ ) idJet_ ->book(    );
    if( doKinJet_) kinJet_->book(    );
    if( doResJet_) resJet_->book(    );
  }
  else{
    ofstream hist(hist_.c_str(), std::ios::out);
    if( doId_ ) id_ ->book(hist);
    if( doKin_) kin_->book(hist);
    if( doRes_) res_->book(hist);
    if( doIdJet_ ) idJet_ ->book(hist);
    if( doKinJet_) kinJet_->book(hist);
    if( doResJet_) resJet_->book(hist);
  }
 
}


template <typename LeptonType, typename Id, typename Kin, typename Res> 
void CutAnalyzer<LeptonType, Id, Kin, Res>::endJob()
{
  if( doId_ ) id_ ->norm();
  if( doKin_) kin_->norm();
  if( doRes_) res_->norm();
  if( doIdJet_ ) idJet_ ->norm();
  if( doKinJet_) kinJet_->norm();
  if( doResJet_) resJet_->norm();
}

#endif
