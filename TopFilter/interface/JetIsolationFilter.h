#ifndef JetIsolationFilter_h
#define JetIsolationFilter_h

#include <memory>
#include <string>
#include <vector>

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/Jet.h"


template <typename Collection> 
class JetIsolationFilter {

 public:

  explicit JetIsolationFilter(const edm::ParameterSet&);
  ~JetIsolationFilter(){};
  explicit JetIsolationFilter(const std::string&, const std::vector<double>&, const edm::InputTag&);


 public:

  bool operator()(edm::Event&, const Collection&);
  bool operator()(const edm::Event&, const Collection&);
  bool filter(edm::Handle<std::vector<pat::Jet> >& , const Collection&);  
  void summarize();

 private:

  edm::InputTag jets_;
  std::string name_;
  std::vector<double> iso_;

 private:

  unsigned int beforeCut_, afterCut_;
};

template <typename Collection> 
JetIsolationFilter<Collection>::JetIsolationFilter(const edm::ParameterSet& cfg):
  jets_( cfg.getParameter<edm::InputTag>("jets") ),
  name_( cfg.getParameter<std::string>("name") ),
  iso_ ( cfg.getParameter<std::vector<double> >( "JetIsolation" ) ),
  beforeCut_( 0 ), afterCut_( 0 )
{
}
template <typename Collection> 
JetIsolationFilter<Collection>::JetIsolationFilter(const std::string&name, const std::vector<double>&iso,const edm::InputTag& jets):
  jets_( jets ),
  name_( name),
  iso_ ( iso ),
  beforeCut_( 0 ), afterCut_( 0 )
{
}
template <typename Collection> 
bool JetIsolationFilter<Collection>::operator()(edm::Event& evt, const Collection& objs)
{
 edm::Handle<std::vector<pat::Jet> > jets;
 evt.getByLabel(jets_, jets);
 ++beforeCut_;
 if( filter(jets, objs) ){
   ++afterCut_;
   return true;
  }
 return false;
}
template <typename Collection> 
bool JetIsolationFilter<Collection>::operator()(const edm::Event& evt, const Collection& objs)
{
 edm::Handle<std::vector<pat::Jet> > jets;
 evt.getByLabel(jets_, jets);
 ++beforeCut_;
 if( filter(jets, objs) ){
   ++afterCut_;
   return true;
  }
 return false;
}
template <typename Collection> 

bool JetIsolationFilter<Collection>::filter(edm::Handle<std::vector<pat::Jet> >& jets, const Collection& objs)
{
 bool passed=true;

 if( objs.size()<iso_.size() )
   passed=false;

 unsigned int idx=0;
 for(typename Collection::const_iterator obj=objs.begin();
     obj!=objs.end(); ++obj) {
   if( idx<iso_.size() ){ // check for isolation as long as vector is long enough       
     double minDR=-1.;
     for(std::vector<pat::Jet>::const_iterator jet = jets->begin();
     jet!=jets->end(); ++jet) {
   double dR=deltaR(obj->eta(), obj->phi(), jet->eta(), jet->phi());
   if( minDR<0 || dR<minDR ) minDR=dR;
     }
     if( minDR<0 ){
   edm::LogWarning ( "NoJetFound" ) << "no jet nearest to object found";
   minDR=999.;
     }
     if( !(minDR>iso_[idx]) ) passed=false;
   }
   // break slope if both vector lengths are exceeded
   ++idx;
   if( idx>iso_.size() )
     break;
 }
 return passed;
}


template <typename Collection> 
void JetIsolationFilter<Collection>::summarize()
{
  using std::cout;
  using std::endl;

  cout << "******************************************************" << endl;
  for(unsigned int idx=0; idx<iso_.size(); ++idx)
    if(idx==0) cout << ::std::setw( 20 ) 
		    << name_ << ": " 
		    << " JetIsolation   < " << iso_[idx] << endl;
    else       cout << ::std::setw( 20 ) 
		    << ": " 
		    << " JetIsolation   < " << iso_[idx] << endl;
  cout << "------------------------------------------------------" << endl 
       << "  Events Before Cut: " << ::std::setw( 10 ) << ::std::right << beforeCut_ << endl
       << "  Events After  Cut: " << ::std::setw( 10 ) << ::std::right << afterCut_  << endl;
}

#endif
  
