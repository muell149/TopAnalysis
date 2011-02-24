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
  int ntagsTCHEloose  =0;
  int ntagsTCHEmedium =0;
  int ntagsSVHEloose  =0;

  double TCHEcutLoose  = 1.70;
  double TCHEcutMedium = 3.40;
  double SVHEcutLoose  = 1.74;

  for(edm::View<pat::Jet>::const_iterator jet = jets->begin();jet != jets->end(); ++jet) {

    double TCHEdiscr = jet->bDiscriminator("trackCountingHighEffBJetTags");
    double SVHEdiscr = jet->bDiscriminator("simpleSecondaryVertexHighEffBJetTags");

    if(TCHEdiscr>TCHEcutLoose ) ntagsTCHEloose++;
    if(TCHEdiscr>TCHEcutMedium) ntagsTCHEmedium++;
    if(SVHEdiscr>SVHEcutLoose ) ntagsSVHEloose++;

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

    bDiscTCHE_->Fill(TCHEdiscr);
    bDiscSVHE_->Fill(SVHEdiscr);
  }
  tagMultiTCHEloose_ ->Fill(ntagsTCHEloose );
  tagMultiTCHEmedium_->Fill(ntagsTCHEmedium);
  tagMultiSVHEloose_ ->Fill(ntagsSVHEloose );
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

  bDiscSVHE_= fs->make<TH1D>( "bDiscSVHE", "TCHE Discriminator" , 110, -1.,  10.);
  bDiscSVHE_->GetXaxis()->SetTitle("discriminator");
  bDiscSVHE_->GetYaxis()->SetTitle("N");

  tagMultiTCHEloose_= fs->make<TH1D>( "tagMultiTCHEloose" , "N_{b-tags} TCHE loose",  10, -0.5, 9.5);
  tagMultiTCHEloose_->GetXaxis()->SetTitle("N_{jets,tagged}");
  tagMultiTCHEloose_->GetYaxis()->SetTitle("N_{evts}");

  tagMultiTCHEmedium_= fs->make<TH1D>( "tagMultiTCHEmedium" , "N_{b-tags} TCHE medium",  10, -0.5, 9.5);
  tagMultiTCHEmedium_->GetXaxis()->SetTitle("N_{jets,tagged}");
  tagMultiTCHEmedium_->GetYaxis()->SetTitle("N_{evts}");

  tagMultiSVHEloose_= fs->make<TH1D>( "tagMultiSVHEloose" , "N_{b-tags} SVHE loose",  10, -0.5, 9.5);
  tagMultiSVHEloose_->GetXaxis()->SetTitle("N_{jets,tagged}");
  tagMultiSVHEloose_->GetYaxis()->SetTitle("N_{evts}");
}


void
JetAnalyzer::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE( JetAnalyzer );
