#include "TopAnalysis/TopAnalyzer/interface/JetEnergyCorrections.h"

/// default constructor
JetEnergyCorrections::JetEnergyCorrections(const edm::ParameterSet& cfg) :
  hypoKey_( cfg.getParameter<std::string>("hypoKey") ) { }

/// histogramm booking
void JetEnergyCorrections::book(edm::Service<TFileService>& fs)
{



}

/// histogram filling
void
JetEnergyCorrections::fill(const TtSemiLeptonicEvent& semiLepEvt, const double& weight)
{



}
