#ifndef ObjectAnalyzer_h
#define ObjectAnalyzer_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


template <typename Collection, typename Id, typename Kin, typename Res> 
class ObjectAnalyzer : public edm::EDAnalyzer {

 public:

  explicit ObjectAnalyzer(const edm::ParameterSet&);
  ~ObjectAnalyzer();
  
 private:
  
  virtual void beginJob(const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();
  
 private:

  edm::InputTag src_;
  edm::InputTag wgt_;
  std::string hist_;
  bool doId_,  doKin_, doRes_;

  Id  *id_;
  Kin *kin_;
  Res *res_;
};

template <typename Collection, typename Id, typename Kin, typename Res> 
ObjectAnalyzer<Collection, Id, Kin, Res>::ObjectAnalyzer(const edm::ParameterSet& cfg):
  src_( cfg.getParameter<edm::InputTag>( "input" ) ),
  wgt_( cfg.getParameter<edm::InputTag>( "weight" ) ),
  hist_ ( cfg.getParameter<std::string>( "hist" ) ),
  doId_ ( cfg.getParameter<bool>( "doId"  ) ),
  doKin_( cfg.getParameter<bool>( "doKin" ) ),
  doRes_( cfg.getParameter<bool>( "doRes" ) )
{
  if( doId_ ) id_  = new Id ( cfg.getParameter<edm::ParameterSet>("id" ) );
  if( doKin_) kin_ = new Kin( cfg.getParameter<edm::ParameterSet>("kin") );
  if( doRes_) res_ = new Res( cfg.getParameter<edm::ParameterSet>("res") );
}

template <typename Collection, typename Id, typename Kin, typename Res> 
ObjectAnalyzer<Collection, Id, Kin, Res>::~ObjectAnalyzer()
{
  if( doId_ ) delete id_;
  if( doKin_) delete kin_;
  if( doRes_) delete res_;
}

template <typename Collection, typename Id, typename Kin, typename Res> 
void ObjectAnalyzer<Collection, Id, Kin, Res>::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{
  edm::Handle<Collection> src; 
  evt.getByLabel(src_, src);
  Collection sources = *src;

  edm::Handle<double> wgt;
  evt.getByLabel(wgt_, wgt);
  double weight = *wgt;

  if( doId_ ) id_ ->fill(evt, sources, weight );
  if( doKin_) kin_->fill(evt, sources, weight );
  if( doRes_) res_->fill(evt, sources, weight );
}

template <typename Collection, typename Id, typename Kin, typename Res> 
void ObjectAnalyzer<Collection, Id, Kin, Res>::beginJob(const edm::EventSetup&)
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

template <typename Collection, typename Id, typename Kin, typename Res> 
void ObjectAnalyzer<Collection, Id, Kin, Res>::endJob()
{
  if( doId_ ) id_ ->norm();
  if( doKin_) kin_->norm();
  if( doRes_) res_->norm();
}

#endif
