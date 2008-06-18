#include "TopAnalysis/TopFilter/interface/PtFilter.h"


PtFilter::PtFilter(const edm::ParameterSet& cfg):
  name_ ( cfg.getParameter<std::string>("name") ),
  minPt_( cfg.getParameter<std::vector<double> >( "minPt" ) ),
  maxPt_( cfg.getParameter<std::vector<double> >( "maxPt" ) ),
  beforeCut_( 0 ), afterCut_( 0 )
{
}

bool 
PtFilter::operator()(edm::Event& evt, const std::vector<edm::View<reco::Candidate> >& objs)
{
  ++beforeCut_;
  if( filter(objs) ) {
    ++afterCut_;
    return true;
  }
  return false;
}

bool 
PtFilter::filter(const std::vector<edm::View<reco::Candidate> >& objs)
{
  bool passedWeak=false, passedStrong=true;
  for(unsigned int jdx=0; jdx<objs.size(); ++jdx){
    bool passedOnce=true;
    // skip if this collection has less members than required
    // by the length of the vectors of minPt_ or maxPt_ 
    if( objs[jdx].size()<minPt_.size() || objs[jdx].size()<maxPt_.size() )
      passedOnce=false;
    
    unsigned int idx=0;
    for(edm::View<reco::Candidate>::const_iterator obj=objs[jdx].begin();
	obj!=objs[jdx].end(); ++obj) {
      if( idx<minPt_.size() ) // check for minPt as long as vector is long enough
	if( !(obj->pt()>minPt_[idx]) ) passedOnce=false;
      if( idx<maxPt_.size() ) // check for maxPt as long as vector is long enough
	if( !(obj->pt()<maxPt_[idx]) ) passedOnce=false;
      
      // break slope if both vector lengths are exceeded
      ++idx;
      if( idx>minPt_.size() && idx>maxPt_.size())
	break;
    }
    if(  passedOnce ) passedWeak=true;
    if( !passedOnce ) passedStrong=false;
  }
  return passedWeak;
}

void 
PtFilter::summarize()
{
  using std::cout;
  using std::endl;

  unsigned int maxSize=minPt_.size();
  if(maxPt_.size()>maxSize) maxSize=maxPt_.size();
  cout << "******************************************************" << endl;
  for(unsigned int idx=0; idx<maxSize; ++idx){
    cout << ::std::setw( 20 );
    if(idx==0) cout << name_; else cout << "   "; 
    cout << ": ";
    if(idx<minPt_.size()) cout << minPt_[idx] << " < Pt"; else cout << "   Pt"; 
    if(idx<maxPt_.size()) cout << " < " << maxPt_[idx] << endl;
  }
  cout << "------------------------------------------------------" << endl 
       << "  Events Before Cut: " << ::std::setw( 10 ) << ::std::right << beforeCut_ << endl
       << "  Events After  Cut: " << ::std::setw( 10 ) << ::std::right << afterCut_  << endl;
}
