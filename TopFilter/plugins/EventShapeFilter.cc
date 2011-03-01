#include "TopAnalysis/TopFilter/plugins/EventShapeFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

EventShapeFilter::EventShapeFilter(const edm::ParameterSet& cfg):
  src_           ( cfg.getParameter<edm::InputTag>("src"            ) ),
  maxIsotropy_   ( cfg.getParameter<double>       ("maxIsotropy"    ) ),
  minIsotropy_   ( cfg.getParameter<double>       ("minIsotropy"    ) ),
  maxCircularity_( cfg.getParameter<double>       ("maxCircularity" ) ),
  minCircularity_( cfg.getParameter<double>       ("minCircularity" ) ),
  maxSphericity_ ( cfg.getParameter<double>       ("maxSphericity"  ) ),
  minSphericity_ ( cfg.getParameter<double>       ("minSphericity"  ) ),
  maxAplanarity_ ( cfg.getParameter<double>       ("maxAplanarity"  ) ),
  minAplanarity_ ( cfg.getParameter<double>       ("minAplanarity"  ) ),
  maxC_          ( cfg.getParameter<double>       ("maxC"           ) ),
  minC_          ( cfg.getParameter<double>       ("minC"           ) ),
  maxD_          ( cfg.getParameter<double>       ("maxD"           ) ),
  minD_          ( cfg.getParameter<double>       ("minD"           ) ),
  useEventWeight_( cfg.getParameter<bool>         ("useEventWeight" ) ),
  weight_        ( cfg.getParameter<edm::InputTag>("weight"         ) ),
  beforeCut_( 0 ), afterCut_( 0 ), beforeCutWeighted_( 0. ), afterCutWeighted_( 0. )
{
}

std::vector<math::XYZVector> makeVecForEventShape(std::vector<pat::Jet> jets, double scale = 1.) {
  std::vector<math::XYZVector> p;
  unsigned int i=1;
  for (std::vector<pat::Jet>::const_iterator jet = jets.begin(); jet != jets.end(); jet++) {
    math::XYZVector Vjet(jet->px() * scale, jet->py() * scale, jet->pz() * scale);
    p.push_back(Vjet);
    ++i;
    if(i==6) break;
  }
  return p;
}

bool EventShapeFilter::filter(edm::Event& event, const edm::EventSetup& setup)
{
  double weight = 1.;
  if(useEventWeight_) { 
    edm::Handle<double> weightHandle;
    event.getByLabel(weight_, weightHandle);
    weight = *weightHandle;
  }

  edm::Handle<std::vector<pat::Jet> > src;
  event.getByLabel(src_, src);

  bool pass = false;

  EventShapeVariables eventshape(makeVecForEventShape((*src)));

  if(maxAplanarity_  >= eventshape.aplanarity()  && maxSphericity_  >= eventshape.sphericity() &&
     maxCircularity_ >= eventshape.circularity() && maxIsotropy_    >= eventshape.isotropy()   &&
     maxC_           >= eventshape.C()           && maxD_           >= eventshape.D()          &&
     minAplanarity_  <= eventshape.aplanarity()  && minSphericity_  <= eventshape.sphericity() &&
     minCircularity_ <= eventshape.circularity() && minIsotropy_    <= eventshape.isotropy()   &&
     minC_           <= eventshape.C()           && minD_           <= eventshape.D()             ){

    pass=true;
  }

  ++beforeCut_;
  beforeCutWeighted_ += weight;

  if( pass ) {
    ++afterCut_;
    afterCutWeighted_ += weight;
  }

  return pass;
}

void EventShapeFilter::beginJob(const edm::EventSetup& setup)
{
}

void EventShapeFilter::endJob()
{
//   edm::LogVerbatim log("topFilter");
//   std::string name = "EventShapeFilter";
//   if(beforeCut_ != beforeCutWeighted_) {
//     log << std::setw( 20 ) << std::left  << name << " : "
// 	<< std::setw( 10 ) << std::right << afterCut_ << " (" 
// 	<< std::setw( 10 ) << std::right << afterCutWeighted_  << ") out of "
// 	<< std::setw( 10 ) << std::right << beforeCut_<< " (" 
// 	<< std::setw( 10 ) << std::right << beforeCutWeighted_ << ")" << "\n";
//   }
//   else{
//     log << std::setw( 20 ) << std::left  << name << " : "
// 	<< std::setw( 10 ) << std::right << afterCut_ << "  out of "
// 	<< std::setw( 10 ) << std::right << beforeCut_ << "\n";  
//  }
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( EventShapeFilter );
