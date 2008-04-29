#ifndef ObjectAnalyzer_h
#define ObjectAnalyzer_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


template <typename Collection, typename Kin, typename Id, typename Res> 
class ObjectAnalyzer : public edm::EDAnalyzer {

 public:

  explicit ObjectAnalyzer(const edm::ParameterSet&);
  ~ObjectAnalyzer();
  
 private:
  
  virtual void beginJob(const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  
 private:

  edm::InputTag src_;
  edm::InputTag wgt_;
  std::string hist_;
  bool doId_,  doKin_, doRes_;

  Id  *id_;
  Kin *kin_;
  Res *res_;
};

template <typename Collection, typename Kin, typename Id, typename Res> 
ObjectAnalyzer<Collection, Kin, Id, Res>::ObjectAnalyzer(const edm::ParameterSet& cfg):
  src_( cfg.getParameter<edm::InputTag>( "input" ) ),
  wgt_( cfg.getParameter<edm::InputTag>( "weight" ) ),
  hist_ ( cfg.getParameter<std::string>( "hist" ) ),
  doId_ ( cfg.getParameter<bool>( "Id" ) ),
  doKin_( cfg.getParameter<bool>( "Kinematics" ) ),
  doRes_( cfg.getParameter<bool>( "Resolution" ) )
{
  if( doId_ ) id_  = new Id ( cfg );
  if( doKin_) kin_ = new Kin( cfg );
  if( doRes_) res_ = new Res( cfg );
}

template <typename Collection, typename Kin, typename Id, typename Res> 
ObjectAnalyzer<Collection, Kin, Id, Res>::~ObjectAnalyzer()
{
  if( doId_ ) delete id_;
  if( doKin_) delete kin_;
  if( doRes_) delete res_;
}

template <typename Collection, typename Kin, typename Id, typename Res> 
void ObjectAnalyzer<Collection, Kin, Id, Res>::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{
  edm::Handle<Collection> sources; 
  evt.getByLabel(src_, sources);

  edm::Handle<double> weight;
  evt.getByLabel(wgt_, weight);

  if( doId_ ) id_ ->fill(evt, *sources, *weight );
  if( doKin_) kin_->fill(evt, *sources, *weight );
  if( doRes_) res_->fill(evt, *sources, *weight );
}

template <typename Collection, typename Kin, typename Id, typename Res> 
void ObjectAnalyzer<Collection, Kin, Id, Res>::beginJob(const edm::EventSetup&)
{
  if(hist_.empty()){
    if( doId_ ) id_ ->book(    );
    if( doKin_) kin_->book(    );
    if( doRes_) res_->book(    );
  }
  else{
    ofstream hist(hist_.c_str(), std::ios::out);
    if( doId_ ) id_ ->book(hist);
    if( doKin_) kin_->book(hist);
    if( doRes_) res_->book(hist);
  }
}

#endif
