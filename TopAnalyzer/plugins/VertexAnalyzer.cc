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
   
  
  posX_= fs->make<TH1D>( "posX", "Vertex x-Position", 400,-2.,2.);
  posX_->GetXaxis()->SetTitle("x [cm]");
  posX_->GetYaxis()->SetTitle("N / 0.01cm");  
  
  posY_= fs->make<TH1D>( "posY", "Vertex y-Position", 400,-2.,2.);
  posY_->GetXaxis()->SetTitle("y [cm]");
  posY_->GetYaxis()->SetTitle("N / 0.01cm"); 
     
  posZ_= fs->make<TH1D>( "posZ", "Vertex z-Position", 1000,-50.,50.);
  posZ_->GetXaxis()->SetTitle("z [cm]");
  posZ_->GetYaxis()->SetTitle("N / 0.1cm"); 
  
  posRho_= fs->make<TH1D>( "posRho", "Vertex #rho-Position", 500,-2.5,2.5);
  posRho_->GetXaxis()->SetTitle("#rho [cm]");
  posRho_->GetYaxis()->SetTitle("N / 0.01cm");  
  
    
  posXerr_= fs->make<TH1D>( "posXerr", "Vertex x-Position Error", 100,0.,1.);
  posXerr_->GetXaxis()->SetTitle("#delta x [cm]");
  posXerr_->GetYaxis()->SetTitle("N / 0.01cm");  
  
  posYerr_= fs->make<TH1D>( "posYerr", "Vertex y-Position Error", 100,0.,1.);
  posYerr_->GetXaxis()->SetTitle("#delta y [cm]");
  posYerr_->GetYaxis()->SetTitle("N / 0.01cm"); 
     
  posZerr_= fs->make<TH1D>( "posZerr", "Vertex z-Position Error", 100,0.,1.);
  posZerr_->GetXaxis()->SetTitle("#delta z [cm]");
  posZerr_->GetYaxis()->SetTitle("N / 0.01cm"); 

  
  nTracks_= fs->make<TH1I>( "nTracks", "Number of Tracks at Vertex", 200,0,200);
  nTracks_->GetXaxis()->SetTitle("N_{tracks}");
  nTracks_->GetYaxis()->SetTitle("N");
  
  nDof_= fs->make<TH1I>( "nDof", "N_{dof} at Vertex", 200,0,200);
  nDof_->GetXaxis()->SetTitle("N_{dof}");
  nDof_->GetYaxis()->SetTitle("N");             
}

void
VertexAnalyzer::analyze(const Event& evt, const EventSetup&)
{
  Handle<std::vector<reco::Vertex> > vertices; 
  evt.getByLabel(vertices_, vertices); 

  reco::Vertex primaryVertex = vertices->front();
  
  isFake_->Fill(primaryVertex.isFake());
  
  if(primaryVertex.isFake()) return;
  
  posX_  ->Fill(primaryVertex.x());
  posY_  ->Fill(primaryVertex.y());  
  posZ_  ->Fill(primaryVertex.z());  
  posRho_->Fill(primaryVertex.position().rho());   

  posXerr_->Fill(primaryVertex.xError());
  posYerr_->Fill(primaryVertex.yError());  
  posZerr_->Fill(primaryVertex.zError()); 
  
  nTracks_->Fill(primaryVertex.tracksSize()); 
  nDof_   ->Fill(primaryVertex.ndof());    
}

void
VertexAnalyzer::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( VertexAnalyzer );
