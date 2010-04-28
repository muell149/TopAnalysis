#include "TopAnalysis/TopAnalyzer/plugins/VertexAnalyzer.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Utilities/interface/EDMException.h"

VertexAnalyzer::VertexAnalyzer(const ParameterSet& cfg)
{
  vertices_ = cfg.getParameter<InputTag>("vertices");
}

VertexAnalyzer::~VertexAnalyzer()
{
}

void
VertexAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  if( !fs ){
    throw edm::Exception( edm::errors::Configuration,
                          "TFile Service is not registered in cfg file" ); 
  }
      
  isFake_= fs->make<TH1I>( "isFake", "Is Fake Vertex", 2,-0.5,1.5);
  isFake_->GetXaxis()->SetBinLabel( 1, "false" );
  isFake_->GetXaxis()->SetBinLabel( 1, "true" );  
  isFake_->GetYaxis()->SetTitle("N");   
  
  posX_= fs->make<TH1D>( "posX", "Vertex x-Position", 100,-2.,2.);
  posX_->GetXaxis()->SetTitle("x [cm]");
  posX_->GetYaxis()->SetTitle("N / 0.1cm");  
  
  posY_= fs->make<TH1D>( "posY", "Vertex y-Position", 100,-2.,2.);
  posY_->GetXaxis()->SetTitle("y [cm]");
  posY_->GetYaxis()->SetTitle("N / 0.1cm"); 
     
  posZ_= fs->make<TH1D>( "posZ", "Vertex z-Position", 100,-50.,50.);
  posZ_->GetXaxis()->SetTitle("z [cm]");
  posZ_->GetYaxis()->SetTitle("N / 1cm");  
  
  nTracks_= fs->make<TH1I>( "nTracks", "Number of Tracks at Vertex", 150,0,150);
  nTracks_->GetXaxis()->SetTitle("N_{tracks}");
  nTracks_->GetYaxis()->SetTitle("N");           
}

void
VertexAnalyzer::analyze(const Event& evt, const EventSetup&)
{
  Handle<std::vector<reco::Vertex> > vertices; 
  evt.getByLabel(vertices_, vertices); 

  reco::Vertex primaryVertex = vertices->front();
  
  isFake_->Fill(primaryVertex.isFake());
  
  if(primaryVertex.isFake()) return;
  
  posX_->Fill(primaryVertex.x());
  posY_->Fill(primaryVertex.y());  
  posZ_->Fill(primaryVertex.z());  
  
  nTracks_->Fill(primaryVertex.tracksSize());  
}

void
VertexAnalyzer::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( VertexAnalyzer );
