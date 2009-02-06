#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "TopAnalysis/TopFilter/interface/ViewFilter.h"
#include "FWCore/Utilities/interface/EDMException.h"

/// default constructor
ViewFilter::ViewFilter(const edm::ParameterSet& cfg):
  beforeCut_( 0 ), afterCut_( 0 ), beforeCutWeighted_( 0. ), afterCutWeighted_( 0. ),  
  name_( cfg.getParameter<std::string>("name") ),
  min_ ( cfg.getParameter<std::vector<double> >("min") ),
  max_ ( cfg.getParameter<std::vector<double> >("max") )
{
  // choose operation mode (weak or strong filtering)
  switch(cfg.getParameter<unsigned>("mode")){
  case  0: mode_=kStrong; break;
  case  1: mode_=kWeak;   break;
  default: throw edm::Exception(edm::errors::Configuration, 
				"unknown mode for filter; choose between 0(strong) or 1(weak) \n");				
  }
  
  // print cuts
  unsigned int maxSize=min_.size();
  edm::LogVerbatim log("topFilter");
  if(max_.size()>maxSize) maxSize=max_.size();
  for(unsigned int idx=0; idx<maxSize; ++idx){
    log << ::std::setw( 20 ) << ::std::left;
    if(idx==0) log << name_; else log << " ";
    log << ": ";
    if(idx<min_.size()) log << "min = " << ::std::setw( 8 ) << ::std::right 
			    <<  min_[idx] << "  "; else log << "   "; 
    if(idx<max_.size()) log << "max = " << ::std::setw( 8 ) << ::std::right
			    <<  max_[idx] 
			    << "\n";
  }
}

/// counter and filter wrapper
bool ViewFilter::operator()(edm::Event& evt, const std::vector<edm::View<reco::Candidate> >& objs, const double& weight)
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

/// summarize event counting
void ViewFilter::summarize()
{
  // if no event weight or dummy weight is in 
  // use a simplified summary format is taken
  edm::LogVerbatim log("topFilter");
  if(beforeCut_ != beforeCutWeighted_){
  log << ::std::setw( 20 ) << ::std::left  << name_ << " : "
      << ::std::setw( 10 ) << ::std::right << afterCut_ << " (" 
      << ::std::setw( 10 ) << ::std::right << afterCutWeighted_  << ") out of "
      << ::std::setw( 10 ) << ::std::right << beforeCut_<< " (" 
      << ::std::setw( 10 ) << ::std::right << beforeCutWeighted_ << ")" << "\n";
  }
  else{
    log << ::std::setw( 20 ) << ::std::left  << name_ << " : "
	<< ::std::setw( 10 ) << ::std::right << afterCut_ << "  out of "
	<< ::std::setw( 10 ) << ::std::right << beforeCut_ << "\n";  
  }
}
