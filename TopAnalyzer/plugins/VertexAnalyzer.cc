#include "TopAnalysis/TopAnalyzer/plugins/VertexAnalyzer.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Utilities/interface/EDMException.h"

VertexAnalyzer::VertexAnalyzer(const ParameterSet& cfg)
{
  vertices_ = cfg.getParameter<InputTag>("vertices"),
  muons_    = cfg.getParameter<InputTag>("muons");
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
  
  multi_= fs->make<TH1D>( "multi", "N of Vertices", 10,-0.5,9.5);
  multi_->GetXaxis()->SetTitle("N_{vrtcs}");  
  multi_->GetYaxis()->SetTitle("N");    
   
  goodMulti_= fs->make<TH1D>( "goodMulti", "N of good Vertices", 10,-0.5,9.5);
  goodMulti_->GetXaxis()->SetTitle("N_{vrtcs}");  
  goodMulti_->GetYaxis()->SetTitle("N"); 
   
    
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

  
  nTracks_= fs->make<TH1D>( "nTracks", "Number of Tracks at Vertex", 200,0,200);
  nTracks_->GetXaxis()->SetTitle("N_{tracks}");
  nTracks_->GetYaxis()->SetTitle("N");
  
  nDof_= fs->make<TH1D>( "nDof", "N_{dof} at Vertex", 200,0,200);
  nDof_->GetXaxis()->SetTitle("N_{dof}");
  nDof_->GetYaxis()->SetTitle("N"); 
  
  chi2_= fs->make<TH1D>( "chi2", "#chi^2 of Vertices", 200,0,200);
  chi2_->GetXaxis()->SetTitle("#chi^2");
  chi2_->GetYaxis()->SetTitle("N"); 
  
  nchi2_= fs->make<TH1D>( "nchi2", "#chi^2/N_{dof} of Vertices", 200,0,20);
  nchi2_->GetXaxis()->SetTitle("#chi^2/N_{dof}");
  nchi2_->GetYaxis()->SetTitle("N");       
  
  dzMu_= fs->make<TH1D>( "dzMu", "z-Distance #mu,Vrtx", 200,0,20);
  dzMu_->GetXaxis()->SetTitle("#Delta z [cm]");
  dzMu_->GetYaxis()->SetTitle("N");               
}

void
VertexAnalyzer::analyze(const Event& evt, const EventSetup&)
{
  Handle<std::vector<reco::Vertex> > vertices; 
  evt.getByLabel(vertices_, vertices); 
  
  multi_->Fill(vertices->size());
  
  int i=0;
  for(VertexCollection::const_iterator vrtx = vertices->begin(); vrtx!= vertices->end(); ++vrtx) { 
    
    bool isFake = vrtx->isFake();
    int ndof    = vrtx->ndof();
    int ntracks = vrtx->tracksSize(); 
    double rho  = vrtx->position().rho();
    double z    = vrtx->position().z();
    double chi2 = vrtx->chi2();
    double nchi2= chi2/ndof;
  
    if(!isFake && ndof>4 && abs(z)<24 && rho<2){
      i++;
      
      posX_  ->Fill(vrtx->x());
      posY_  ->Fill(vrtx->y());  
      posZ_  ->Fill(z);  
      posRho_->Fill(rho);   

      posXerr_->Fill(vrtx->xError());
      posYerr_->Fill(vrtx->yError());  
      posZerr_->Fill(vrtx->zError()); 
  
      nTracks_->Fill(ntracks); 
      nDof_   ->Fill(ndof);  
      chi2_   ->Fill(chi2);
      nchi2_  ->Fill(nchi2); 
      
      Handle<std::vector<pat::Muon> > muons; 
      evt.getByLabel(muons_, muons);     
  
      for(std::vector<pat::Muon>::const_iterator muon = muons->begin(); muon!= muons->end(); ++muon) {  
        dzMu_->Fill(abs(muon->vz()-z));
      }           
    }
    goodMulti_->Fill(i);    
  }
  
  
  
  
  
  
 
  
  
  
  
  
  
  
}

void
VertexAnalyzer::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( VertexAnalyzer );
