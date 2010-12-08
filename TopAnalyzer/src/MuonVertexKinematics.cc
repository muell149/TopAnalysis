#include "TopAnalysis/TopAnalyzer/interface/MuonVertexKinematics.h"

/// default constructor for fw lite
MuonVertexKinematics::MuonVertexKinematics(const int index) : index_(index)
{
}

/// default constructor for fwfull
MuonVertexKinematics::MuonVertexKinematics(const edm::ParameterSet& cfg) :
  index_( cfg.getParameter<int>( "index" ) )
{
}

/// histogramm booking for fwlite 
void
MuonVertexKinematics::book()
{
  /** 
      Kinematic Variables
  **/
  // distance of the muon to the PV in z direction
  hists_["dzPV"] = new TH1F( "dzPV" , "dzPV" , 320 , 0 , 8 );
}

/// histogramm booking for full fw
void
MuonVertexKinematics::book(edm::Service<TFileService>& fs)
{
  /** 
      Kinematic Variables
  **/
  hists_["dzPV"] = fs->make<TH1F>( "dzPV" , "dzPV" , 320 , 0 , 8 );
}

/// histogram filling for fwlite and for full fw
void
MuonVertexKinematics::fill(const edm::View<pat::Muon>& muons, const edm::View<reco::Vertex>&  primaryVertex, const double& weight)
{
  /** 
      Fill Kinematic Variables
  **/

  // index for the leading, 2. leading, 3. leading muon
  // to be compared with index_ from the module config
  // where index_=-1 means 'fill all muons' and index_=n
  // n>-1 means 'fill only (n-1)-th leading muon'
  int index=0;
  for(edm::View<pat::Muon>::const_iterator muon=muons.begin(); muon!=muons.end(); ++muon, ++index){
    if( index_<0 || index_==index ){
      // consider only PV 
      fillValue( "dzPV", std::abs(muon->vertex().z() - primaryVertex.begin()->z()), weight );
    }
  }

}
