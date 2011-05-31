#include "TopAnalysis/TopAnalyzer/interface/JetAnalyzer.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

JetAnalyzer::JetAnalyzer(const edm::ParameterSet& cfg):
  jets_   ( cfg.getParameter<edm::InputTag>    ( "jets"        ) ),
  fromTo_ ( cfg.getParameter<std::vector<int> >( "from_to"     ) )
{
}

JetAnalyzer::~JetAnalyzer()
{
}

void
JetAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{
  edm::Handle<edm::View< pat::Jet > > jets;
  evt.getByLabel(jets_, jets);

  multi_->Fill(jets->size());

  int i=0;
  
  int ntagsTCHEL  =0;
  int ntagsTCHEM  =0;
  int ntagsTCHET  =0;   
  int ntagsTCHPL  =0;
  int ntagsTCHPM  =0;
  int ntagsTCHPT  =0;    
  int ntagsSSVHEM =0;
  int ntagsSSVHET =0;  
  int ntagsSSVHPM =0;
  
  double TCHELcut  =  1.70;
  double TCHEMcut  =  3.40;
  double TCHETcut  = 10.20;
  double TCHPLcut  =  1.19;
  double TCHPMcut  =  1.93;
  double TCHPTcut  =  3.41;	
  double SSVHEMcut =  1.74;
  double SSVHETcut =  3.05; 
  double SSVHPMcut =  2.00; //not finaly defined

  for(edm::View<pat::Jet>::const_iterator jet = jets->begin();jet != jets->end(); ++jet) {

    double TCHEdiscr  = jet->bDiscriminator("trackCountingHighEffBJetTags");
    double TCHPdiscr  = jet->bDiscriminator("trackCountingHighPurBJetTags");    
    double SSVHEdiscr = jet->bDiscriminator("simpleSecondaryVertexHighEffBJetTags");  
    double SSVHPdiscr = jet->bDiscriminator("simpleSecondaryVertexHighPurBJetTags");          

    if(TCHEdiscr >TCHELcut ) ntagsTCHEL++;
    if(TCHEdiscr >TCHEMcut ) ntagsTCHEM++;
    if(TCHEdiscr >TCHETcut ) ntagsTCHET++;
    if(TCHPdiscr >TCHPLcut ) ntagsTCHPL++;
    if(TCHPdiscr >TCHPMcut ) ntagsTCHPM++;
    if(TCHPdiscr >TCHPTcut ) ntagsTCHPT++;    
    if(SSVHEdiscr>SSVHEMcut) ntagsSSVHEM++;
    if(SSVHEdiscr>SSVHETcut) ntagsSSVHET++;
    if(SSVHPdiscr>SSVHPMcut) ntagsSSVHPM++;
    
    // only take the jets from the selected range
    if(i<fromTo_[0]) continue;
    if(i>fromTo_[1]) continue;
    ++i;

    pt_      ->Fill(jet->pt());
    et_      ->Fill(jet->et());
    eta_     ->Fill(jet->eta());

    if(!jet->isCaloJet()){
      chargedHadronFrac_  ->Fill(jet->chargedHadronEnergyFraction());
      neutralHadronFrac_  ->Fill(jet->neutralHadronEnergyFraction());
      chargedEmFrac_      ->Fill(jet->chargedEmEnergyFraction());
      neutralEmFrac_      ->Fill(jet->neutralEmEnergyFraction());
      chargedMulti_       ->Fill(jet->chargedMultiplicity());
      nConst_             ->Fill(jet->nConstituents());
    }

    bDiscTCHE_ ->Fill(TCHEdiscr );
    bDiscTCHP_ ->Fill(TCHPdiscr );
    bDiscSSVHE_->Fill(SSVHEdiscr);
    bDiscSSVHP_->Fill(SSVHPdiscr);
  }  
  multiTCHEL_ ->Fill(ntagsTCHEL);
  multiTCHEM_ ->Fill(ntagsTCHEM);
  multiTCHET_ ->Fill(ntagsTCHET);  
  multiTCHPL_ ->Fill(ntagsTCHPL);
  multiTCHPM_ ->Fill(ntagsTCHPM);
  multiTCHPT_ ->Fill(ntagsTCHPT);   
  multiSSVHEM_->Fill(ntagsSSVHEM);
  multiSSVHET_->Fill(ntagsSSVHET); 
  multiSSVHPM_->Fill(ntagsSSVHPM);   
}


void
JetAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  if( !fs ){
    throw edm::Exception( edm::errors::Configuration,
                          "TFile Service is not registered in cfg file" );
  }

  multi_= fs->make<TH1D>( "multi" , "N_{Jets} per Event",  10, -0.5, 9.5);
  multi_->GetXaxis()->SetTitle("N_{jets}");
  multi_->GetYaxis()->SetTitle("N_{evts}");

  pt_= fs->make<TH1D>( "pt" , "Jet Transverse Momentum", 200, 0., 400.);
  pt_->GetXaxis()->SetTitle("p_{t,jet} [GeV]");
  pt_->GetYaxis()->SetTitle("N");

  et_= fs->make<TH1D>( "et" , "Jet Transverse Energy", 200, 0., 400.);
  et_->GetXaxis()->SetTitle("E_{t,jet} [GeV]");
  et_->GetYaxis()->SetTitle("N");

  eta_= fs->make<TH1D>( "eta", "Jet Pseudorapididty", 100, -5., 5.);
  eta_->GetXaxis()->SetTitle("#eta_{jet}");
  eta_->GetYaxis()->SetTitle("N");


  chargedHadronFrac_= fs->make<TH1D>( "chargedHadronFrac", "Charged Hadron Fraction", 100, 0., 1.);
  chargedHadronFrac_->GetXaxis()->SetTitle("charged hdr frac");
  chargedHadronFrac_->GetYaxis()->SetTitle("N");

  neutralHadronFrac_= fs->make<TH1D>( "neutralHadronFrac", "neutral Hadron Fraction", 100, 0., 1.);
  neutralHadronFrac_->GetXaxis()->SetTitle("neutral hdr frac");
  neutralHadronFrac_->GetYaxis()->SetTitle("N");

  chargedEmFrac_= fs->make<TH1D>( "chargedEmFrac", "Charged Em Fraction", 100, 0., 1.);
  chargedEmFrac_->GetXaxis()->SetTitle("charged em frac");
  chargedEmFrac_->GetYaxis()->SetTitle("N");

  neutralEmFrac_= fs->make<TH1D>( "neutralEmFrac", "neutral Em Fraction", 100, 0., 1.);
  neutralEmFrac_->GetXaxis()->SetTitle("neutral em frac");
  neutralEmFrac_->GetYaxis()->SetTitle("N");

  chargedMulti_= fs->make<TH1D>( "chargedMulti", "Charged Multiplicity", 100, 0., 100.);
  chargedMulti_->GetXaxis()->SetTitle("multiplicity");
  chargedMulti_->GetYaxis()->SetTitle("N");

  nConst_= fs->make<TH1D>( "nConst", "Number of Constituents", 100, 0., 100.);
  nConst_->GetXaxis()->SetTitle("em fraction");
  nConst_->GetYaxis()->SetTitle("N");


  bDiscTCHE_= fs->make<TH1D>( "bDiscTCHE", "TCHE Discriminator" , 300, -10., 50.);
  bDiscTCHE_->GetXaxis()->SetTitle("discriminator");
  bDiscTCHE_->GetYaxis()->SetTitle("N");
  
  bDiscTCHP_= fs->make<TH1D>( "bDiscTCHP", "TCHP Discriminator" , 300, -10., 50.);
  bDiscTCHP_->GetXaxis()->SetTitle("discriminator");
  bDiscTCHP_->GetYaxis()->SetTitle("N");  

  bDiscSSVHE_= fs->make<TH1D>( "bDiscSSVHE", "SSVHE Discriminator" , 110, -1.,  10.);
  bDiscSSVHE_->GetXaxis()->SetTitle("discriminator");
  bDiscSSVHE_->GetYaxis()->SetTitle("N");
  
  bDiscSSVHP_= fs->make<TH1D>( "bDiscSSVHP", "SSVHP Discriminator" , 110, -1.,  10.);
  bDiscSSVHP_->GetXaxis()->SetTitle("discriminator");
  bDiscSSVHP_->GetYaxis()->SetTitle("N");  

  multiTCHEL_= fs->make<TH1D>( "multiTCHEL" , "N_{b-tags} TCHEL",  10, -0.5, 9.5);
  multiTCHEL_->GetXaxis()->SetTitle("N_{jets,tagged}");
  multiTCHEL_->GetYaxis()->SetTitle("N_{evts}");

  multiTCHEM_= fs->make<TH1D>( "multiTCHEM" , "N_{b-tags} TCHEM",  10, -0.5, 9.5);
  multiTCHEM_->GetXaxis()->SetTitle("N_{jets,tagged}");
  multiTCHEM_->GetYaxis()->SetTitle("N_{evts}");
  
  multiTCHET_= fs->make<TH1D>( "multiTCHET" , "N_{b-tags} TCHET",  10, -0.5, 9.5);
  multiTCHET_->GetXaxis()->SetTitle("N_{jets,tagged}");
  multiTCHET_->GetYaxis()->SetTitle("N_{evts}"); 
  
  multiTCHPL_= fs->make<TH1D>( "multiTCHPL" , "N_{b-tags} TCHPL",  10, -0.5, 9.5);
  multiTCHPL_->GetXaxis()->SetTitle("N_{jets,tagged}");
  multiTCHPL_->GetYaxis()->SetTitle("N_{evts}");

  multiTCHPM_= fs->make<TH1D>( "multiTCHPM" , "N_{b-tags} TCHPM",  10, -0.5, 9.5);
  multiTCHPM_->GetXaxis()->SetTitle("N_{jets,tagged}");
  multiTCHPM_->GetYaxis()->SetTitle("N_{evts}");
  
  multiTCHPT_= fs->make<TH1D>( "multiTCHPT" , "N_{b-tags} TCHPT",  10, -0.5, 9.5);
  multiTCHPT_->GetXaxis()->SetTitle("N_{jets,tagged}");
  multiTCHPT_->GetYaxis()->SetTitle("N_{evts}");   
   
  multiSSVHEM_= fs->make<TH1D>( "multiSSVHEM" , "N_{b-tags} SSVHEM",  10, -0.5, 9.5);
  multiSSVHEM_->GetXaxis()->SetTitle("N_{jets,tagged}");
  multiSSVHEM_->GetYaxis()->SetTitle("N_{evts}");
  
  multiSSVHET_= fs->make<TH1D>( "multiSSVHET" , "N_{b-tags} SSVHET",  10, -0.5, 9.5);
  multiSSVHET_->GetXaxis()->SetTitle("N_{jets,tagged}");
  multiSSVHET_->GetYaxis()->SetTitle("N_{evts}"); 
  
  multiSSVHPM_= fs->make<TH1D>( "multiSSVHPM" , "N_{b-tags} SSVHPM",  10, -0.5, 9.5);
  multiSSVHPM_->GetXaxis()->SetTitle("N_{jets,tagged}");
  multiSSVHPM_->GetYaxis()->SetTitle("N_{evts}");   
}


void
JetAnalyzer::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE( JetAnalyzer );
