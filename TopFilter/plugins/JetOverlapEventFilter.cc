#include "TopAnalysis/TopFilter/plugins/JetOverlapEventFilter.h"

#include <Math/VectorUtil.h>

JetOverlapEventFilter::JetOverlapEventFilter(const edm::ParameterSet& cfg):
  src_           ( cfg.getParameter<edm::InputTag>("src"            ) ),
  deltaR_        ( cfg.getParameter<double>       ("deltaR"         ) ),
  useEventWeight_( cfg.getParameter<bool>         ("useEventWeight" ) ),
  weight_        ( cfg.getParameter<edm::InputTag>("weight"         ) ),
  beforeCut_( 0 ), afterCut_( 0 ), beforeCutWeighted_( 0. ), afterCutWeighted_( 0. )
{
}

bool JetOverlapEventFilter::filter(edm::Event& event, const edm::EventSetup& setup)
{
  double weight = 1.;
  if(useEventWeight_) { 
    edm::Handle<double> weightHandle;
    event.getByLabel(weight_, weightHandle);
    weight = *weightHandle;
  }

  edm::Handle<std::vector<pat::Jet> > src;
  event.getByLabel(src_, src);

  bool overlap = false;

  for(unsigned int i = 0; i < src->size(); i++) {
    for(unsigned int j = 0; j < i; j++) {
      double dR = ROOT::Math::VectorUtil::DeltaR( (*src)[i].p4() , (*src)[j].p4() );
      overlap = (dR < deltaR_);
    }
  }

  ++beforeCut_;
  beforeCutWeighted_ += weight;

  if( !overlap ) {
    ++afterCut_;
    afterCutWeighted_ += weight;
  }

  return !overlap;
}

void JetOverlapEventFilter::beginJob(const edm::EventSetup& setup)
{
}

void JetOverlapEventFilter::endJob()
{
  edm::LogVerbatim log("topFilter");
  std::string name = "JetOverlapEventFilter";
  if(beforeCut_ != beforeCutWeighted_) {
    log << std::setw( 20 ) << std::left  << name << " : "
	<< std::setw( 10 ) << std::right << afterCut_ << " (" 
	<< std::setw( 10 ) << std::right << afterCutWeighted_  << ") out of "
	<< std::setw( 10 ) << std::right << beforeCut_<< " (" 
	<< std::setw( 10 ) << std::right << beforeCutWeighted_ << ")" << "\n";
  }
  else{
    log << std::setw( 20 ) << std::left  << name << " : "
	<< std::setw( 10 ) << std::right << afterCut_ << "  out of "
	<< std::setw( 10 ) << std::right << beforeCut_ << "\n";  
  }
}
