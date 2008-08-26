#include "TopAnalysis/TopFilter/interface/EtaFilter.h"


EtaFilter::EtaFilter(const edm::ParameterSet& cfg):
  name_ ( cfg.getParameter<std::string>("name") ),
  minEta_( cfg.getParameter<std::vector<double> >( "minEta" ) ),
  maxEta_( cfg.getParameter<std::vector<double> >( "maxEta" ) ),
  beforeCut_( 0 ), afterCut_( 0 ),
  beforeCutWeighted_( 0. ), afterCutWeighted_( 0. )
{
}

bool EtaFilter::operator()(edm::Event& evt, const std::vector<edm::View<reco::Candidate> >& objs, const double& weight)
{
   ++beforeCut_;
  beforeCutWeighted_ += weight;
  if( filter(objs) ) {
    ++afterCut_;
    afterCutWeighted_ += weight;
    return true;
  }
  return false;
}

bool EtaFilter::filter(const std::vector<edm::View<reco::Candidate> >& objs)
{
  bool passedWeak=false, passedStrong=true;
  for(unsigned int jdx=0; jdx<objs.size(); ++jdx){
    bool passedOnce=true;
    // skip if this collection has less members than required
    // by the length of the vectors of minEta_ or maxEta_ 
    if( objs[jdx].size()<minEta_.size() || objs[jdx].size()<maxEta_.size() )
      passedOnce=false;
    
    unsigned int idx=0;
    for(edm::View<reco::Candidate>::const_iterator obj=objs[jdx].begin();
	obj!=objs[jdx].end(); ++obj) {
      if( idx<minEta_.size() ) // check for minEta as long as vector is long enough
	if( !(obj->eta()>minEta_[idx]) ) passedOnce=false;
      if( idx<maxEta_.size() ) // check for maxEta as long as vector is long enough
	if( !(obj->eta()<maxEta_[idx]) ) passedOnce=false;
      
      // break slope if both vector lengths are exceeded
      ++idx;
      if( idx>minEta_.size() && idx>maxEta_.size())
	break;
    }
    if(  passedOnce ) passedWeak=true;
    if( !passedOnce ) passedStrong=false;
  }
  return passedWeak;
}

void EtaFilter::summarize()
{
  using std::cout;
  using std::endl;

  unsigned int maxSize=minEta_.size();
  if(maxEta_.size()>maxSize) maxSize=maxEta_.size();
  cout << "******************************************************" << endl;
  for(unsigned int idx=0; idx<maxSize; ++idx){
    cout << ::std::setw( 20 );
    if(idx==0) cout << name_; else cout << " ";
    cout << ": ";
    if(idx<minEta_.size()) cout << minEta_[idx] << " < Eta"; else cout << "   Eta"; 
    if(idx<maxEta_.size()) cout << " < " << maxEta_[idx] << endl;
  }
  cout << "------------------------------------------------------" << endl 
       << " Events Before Cut (Weighted): "
       << ::std::setw( 10 ) << ::std::right << beforeCut_
       << " (" << ::std::setw( 10 ) << ::std::right << beforeCutWeighted_ << ")" << endl
       << " Events After  Cut (Weighted): "
       << ::std::setw( 10 ) << ::std::right << afterCut_ 
       << " (" << ::std::setw( 10 ) << ::std::right << afterCutWeighted_  << ")" << endl;
}
