#include "DataFormats/PatCandidates/interface/Jet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "TopAnalysis/TopUtils/interface/RootHistograms.h"
#include "TopAnalysis/TopAnalyzer/interface/BJetTag.h"

BJetTag::BJetTag(const edm::ParameterSet& cfg):
  algorithm_( cfg.getParameter<string>         ( "algorithm") ),
  cut_      ( cfg.getParameter<double>         ( "b_dis_cut") ),  
  etaBin_   ( cfg.getParameter<vector<double> >( "eta_bins" ) ),
  ptBin_    ( cfg.getParameter<vector<double> >( "pt_bins"  ) )    
{ 
}

BJetTag::~BJetTag()
{
}

void
BJetTag::fill(const pat::Jet& jet, double weight)
{
  trkCountHighEffBJetTags_ ->Fill(jet.bDiscriminator("trackCountingHighEffBJetTags"      ), weight);
  trkCountHighPurBJetTags_ ->Fill(jet.bDiscriminator("trackCountingHighPurBJetTags"      ), weight);  
  jetProbBJetTags_         ->Fill(jet.bDiscriminator("jetProbabilityBJetTags"            ), weight);  
  jetBProbBJetTags_        ->Fill(jet.bDiscriminator("jetBProbabilityBJetTags"           ), weight);  
  impactParMVABJetTags_    ->Fill(jet.bDiscriminator("impactParameterMVABJetTags"        ), weight);  
  simpleSvBJetTags_        ->Fill(jet.bDiscriminator("simpleSecondaryVertexBJetTags"     ), weight); 
  combSvBJetTags_          ->Fill(jet.bDiscriminator("combinedSecondaryVertexBJetTags"   ), weight);  
  combSvMvaBJetTags_       ->Fill(jet.bDiscriminator("combinedSecondaryVertexMVABJetTags"), weight);  
  softMuonBJetTags_        ->Fill(jet.bDiscriminator("softMuonBJetTags"                  ), weight);  
  softMuonNoIPBJetTags_    ->Fill(jet.bDiscriminator("softMuonNoIPBJetTags"              ), weight);  
  softElecBJetTags_        ->Fill(jet.bDiscriminator("softElectronBJetTags"              ), weight);  
  
  for(size_t i=0; i<etaBin_.size(); ++i){
    if(fabs(jet.eta())>fabs(etaBin_[i]) && fabs(jet.eta()) < fabs(etaBin_[i+1])) 
      etaHist_[i]->Fill(jet.bDiscriminator(algorithm_.c_str()), weight);
  }
  
  for(size_t i=0; i<ptBin_.size(); ++i){
    if(jet.pt()>ptBin_[i] && jet.pt() < ptBin_[i+1]) 
      ptHist_[i]->Fill(jet.bDiscriminator(algorithm_.c_str()), weight);
  }  
}

void 
BJetTag::book(ofstream& file, char* name)
{
  edm::Service<TFileService> fs;

  NameScheme e(name);
  trkCountHighEffBJetTags_ = fs->make<TH1F>(e.name( file, "trkCountHighEffBJetTags" ), e.name("trkCountHighEffBJetTags"), 50, 0. , 5.0 ); 
  trkCountHighPurBJetTags_ = fs->make<TH1F>(e.name( file, "trkCountHighPurBJetTags" ), e.name("trkCountHighPurBJetTags"), 50, 0. , 5.0 );  
  jetProbBJetTags_         = fs->make<TH1F>(e.name( file, "jetProbBJetTags"         ), e.name("jetProbBJetTags"        ), 50, 0. , 1.0 );  
  jetBProbBJetTags_        = fs->make<TH1F>(e.name( file, "jetBProbBJetTags"        ), e.name("jetBProbBJetTags"       ), 50, 0. , 1.0 );  
  impactParMVABJetTags_    = fs->make<TH1F>(e.name( file, "impactParMVABJetTags"    ), e.name("impactParMVABJetTags"   ), 50, 0. , 1.0 );  
  simpleSvBJetTags_        = fs->make<TH1F>(e.name( file, "simpleSvBJetTags"        ), e.name("simpleSvBJetTags"       ), 50, 0. , 5.0 );  
  combSvBJetTags_          = fs->make<TH1F>(e.name( file, "combSvBJetTags"          ), e.name("combSvBJetTags"         ), 50, 0. , 1.0 );  
  combSvMvaBJetTags_       = fs->make<TH1F>(e.name( file, "combSvMvaBJetTags"       ), e.name("combSvMvaBJetTags"      ), 50, 0. , 1.0 );  
  softMuonBJetTags_        = fs->make<TH1F>(e.name( file, "softMuonBJetTags"        ), e.name("softMuonBJetTags"       ), 50, 0. , 1.0 );  
  softMuonNoIPBJetTags_    = fs->make<TH1F>(e.name( file, "softMuonNoIPBJetTags"    ), e.name("softMuonNoIPBJetTags"   ), 50, 0. , 1.0 );  
  softElecBJetTags_        = fs->make<TH1F>(e.name( file, "softElecBJetTags"        ), e.name("softElecBJetTags"       ), 50, 0. , 1.0 );  
  
  for(size_t i=0; i<etaBin_.size(); ++i){
    TH1F* hist = fs->make<TH1F>(e.name(file, "etaBins", i), e.name("etaBins", i), 50, 0., 1.0);
    etaHist_.push_back(hist); 
  }
  
  for(size_t i=0; i<ptBin_.size(); ++i){
    TH1F* hist = fs->make<TH1F>(e.name(file, "ptBins", i), e.name("ptBins", i), 50, 0., 1.0);
    ptHist_.push_back(hist); 
  }     
  
  etaEff_= fs->make<TH1F>(e.name( file, "etaEff" ), e.name("etaEff"), etaBin_.size()-1, &etaBin_.front());
  ptEff_ = fs->make<TH1F>(e.name( file, "ptEff"  ), e.name("ptEff" ), ptBin_.size()-1 , &ptBin_.front() ); 
}

void
BJetTag::evaluate()
{  
  for(size_t i=0; i<etaBin_.size(); ++i){
    int bin = cut_*50+1;
    double norm = etaHist_[i]->Integral();
    double integral = etaHist_[i]->Integral(bin, 50);
    double efficency = integral/norm; 
    double error = binomerror(integral, norm); 
    etaEff_->SetBinContent(i+1, efficency);
    etaEff_->SetBinError(i+1, error);
  }

  for(size_t i=0; i<ptBin_.size(); ++i){  
    int bin = cut_*50+1;
    double norm = ptHist_[i]->Integral();
    double integral = ptHist_[i]->Integral(bin, 50);
    double efficency = integral/norm; 
    double error = binomerror(integral, norm); 
    ptEff_->SetBinContent(i+1, efficency);
    ptEff_->SetBinError(i+1, error);
  }  
}

double
BJetTag::binomerror(double numerator, double denominator)
{
  if(numerator>denominator) return 999999.;
  
  double error;  
  error=sqrt((1-numerator/denominator)
   *numerator/denominator/denominator);
   
  return error;
}
