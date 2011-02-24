#include "TMath.h"

#include "TopAnalysis/TopAnalyzer/interface/ElectronNtupleAnalyzer.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"



ElectronNtupleAnalyzer::ElectronNtupleAnalyzer(const edm::ParameterSet& cfg):
  electrons_ ( cfg.getParameter<edm::InputTag>( "electrons" ) ),
  jets_  ( cfg.getParameter<edm::InputTag>( "jets"  ) ),
  mets_  ( cfg.getParameter<edm::InputTag>( "mets"  ) ),
  primaryVertex_  ( cfg.getParameter<edm::InputTag>( "primaryVertex"  ) )
{
}


ElectronNtupleAnalyzer::~ElectronNtupleAnalyzer()
{
}

void
ElectronNtupleAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{

  // zeros for tree
  irun=-1;
  ilumi=-1;
  ievent=-1;
  nprimary=-1;
  zvertex=-100.;
  METet=-1.;
  METphi=-1.;
  METpx=-100.;
  METpy=-100.;
  METSumEt=-1.;
  METut=-900.;
  METutpar=-900.;
  METutperp=-900.;
  METut2=-900.;
  ptel1=-1.;
  phiel1=-9.;
  etael1=-9.;
  chargeel1=-9.;
  trkisoel1=-9.;
  ecalisoel1=-9.;
  hcalisoel1=-9.;
  ptel2=-1.;
  phiel2=-9.;
  etael2=-9.;
  chargeel2=-9.;
  trkisoel2=-9.;
  ecalisoel2=-9.;
  hcalisoel2=-9.;
  dimass=-9.;
  ptjet1=-1.;
  phijet1=-9.;
  etajet1=-9.;
  TCHEdiscr1=-9.;
  SVHEdiscr1=-9.;
  jetflavour1=-9.;
  ptjet2=-1.;
  phijet2=-9.;
  etajet2=-9.;
  TCHEdiscr2=-9.;
  SVHEdiscr2=-9.;
  jetflavour2=-9.;
  dimassjet=-9.;

  // Fill tree with event number
  irun= evt.id().run();
  ilumi=evt.id().luminosityBlock();
  ievent=evt.id().event();

  // Fill vertex
  edm::Handle<reco::VertexCollection> primaryVertex;
  evt.getByLabel(primaryVertex_, primaryVertex);
  nprimary=primaryVertex->size();
  zvertex=primaryVertex->begin()->z();
  double xprimary=nprimary;
  Nprimary_->Fill(xprimary);
  Zvertex_->Fill(zvertex);

  edm::Handle<PatElectronCollection> electrons;
  evt.getByLabel(electrons_, electrons);

  edm::Handle<PatJetCollection> jets;
  evt.getByLabel(jets_, jets);

  edm::Handle<PatMETCollection> mets;
  evt.getByLabel(mets_, mets);

  // fill for two electrons, take two highest pt electrons
  if(electrons->size()>=2) {

    // get leading electrons
    PatElectronCollection::const_reference el1 = electrons->at(0);
    PatElectronCollection::const_reference el2 = electrons->at(1);

    // get transverse momentum of Z (for DY events) and fill electrons
    ptZVec = TVector2(el1.px()+el2.px(), el1.py()+el2.py());
    ptel1= el1.pt();
    phiel1=el1.phi();
    etael1=el1.eta();
    chargeel1=el1.charge();
    trkisoel1=el1.dr03TkSumPt();
    ecalisoel1=el1.dr03EcalRecHitSumEt();
    hcalisoel1=el1.dr03HcalTowerSumEt();
    ptel2= el2.pt();
    phiel2=el2.phi();
    etael2=el2.eta();
    chargeel2=el2.charge();
    trkisoel2=el2.dr03TkSumPt();
    ecalisoel2=el2.dr03EcalRecHitSumEt();
    hcalisoel2=el2.dr03HcalTowerSumEt();


    // calculate dimass
    TLorentzVector diLepVector = TLorentzVector(el1.px()+el2.px(), el1.py()+el2.py(),
                                                el1.pz()+el2.pz(), el1.energy()+el2.energy());
    dimass = (diLepVector).M();
  }

  // first jet
  if(jets->size()>0) {
    // get transverse momentum of Jet 1
    PatJetCollection::const_reference jet = jets->at(0);
    ptJetVec = TVector2(jet.px(), jet.py());
    ptjet1= jet.pt();
    phijet1 = jet.phi();
    etajet1 = jet.eta();
    TCHEdiscr1 = jet.bDiscriminator("trackCountingHighEffBJetTags");
    SVHEdiscr1 = jet.bDiscriminator("simpleSecondaryVertexHighEffBJetTags");
  }
  // second jet
  if(jets->size()>1) {
    // get transverse momentum of Jet 2
    PatJetCollection::const_reference jet1 = jets->at(0);
    PatJetCollection::const_reference jet2 = jets->at(1);
    ptjet2= jet2.pt();
    phijet2 = jet2.phi();
    etajet2 = jet2.eta();
    TCHEdiscr2 = jet2.bDiscriminator("trackCountingHighEffBJetTags");
    SVHEdiscr2= jet2.bDiscriminator("simpleSecondaryVertexHighEffBJetTags");

    // calculate dimassjet
    TLorentzVector diJetVector = TLorentzVector(jet1.px()+jet2.px(), jet1.py()+jet2.py(),
                                                jet1.pz()+jet2.pz(), jet1.energy()+jet2.energy());
    dimassjet = (diJetVector).M();

  }


  // Missing Transverse Energy
  PatMETCollection::const_reference met = mets->at(0);

  // for(PatMETCollection::const_iterator met = mets->begin(); met!= mets->end(); ++met) {
  TVector2 ptMetVec = TVector2(met.px(), met.py());
  METet=met.et();
  METphi=met.phi();
  METpx=met.px();
  METpy=met.py();
  METSumEt=met.sumEt();
  //}


  // Calculate Ut, rotate so that the Z direction is the new x-axis
  TVector2 UtVec =  ptMetVec-ptZVec;
  METut = TMath::Sqrt(UtVec.X()*UtVec.X()+UtVec.Y()*UtVec.Y());
  TVector2 UtVec2 = -1.*(ptMetVec+ptZVec); // which one is right?  sign -?
  METut2 = TMath::Sqrt(UtVec2.X()*UtVec2.X()+UtVec2.Y()*UtVec2.Y());
  TVector2 UtVecRot = UtVec.Rotate(-1.*ptZVec.Phi());
  METutpar = UtVecRot.X();
  METutperp= UtVecRot.Y();
  ut_->Fill(METut);
  upar_->Fill(METutpar);
  uperp_->Fill(METutperp);


  // fill ntuple
  Ntuple_->Fill();

}


void
ElectronNtupleAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  if( !fs ){
    throw edm::Exception( edm::errors::Configuration,
                          "TFile Service is not registered in cfg file" );
  }

  Nprimary_= fs->make<TH1D>( "Nprimary" , "Number of vertices", 10, 0., 10.);
  Nprimary_->GetXaxis()->SetTitle("N vertices");
  Nprimary_->GetYaxis()->SetTitle("N");

  Zvertex_= fs->make<TH1D>( "Zvertex" , "Z vertex", 200, -100., 100.);
  Zvertex_->GetXaxis()->SetTitle("z_{vertex} [cm]");
  Zvertex_->GetYaxis()->SetTitle("N");

  ut_=  fs->make<TH1D>("Ut",  "Ut",   300, 0. , 300. ) ;
  ut_->GetXaxis()->SetTitle("Ut");
  ut_->GetYaxis()->SetTitle("N");


  upar_=  fs->make<TH1D>("Upar",  "Upar",   300, -200. , 100. ) ;
  upar_->GetXaxis()->SetTitle("Upar");
  upar_->GetYaxis()->SetTitle("N");

  uperp_= fs->make<TH1D>("Uperp", "Uperp", 200, -100. , 100. ) ;
  uperp_->GetXaxis()->SetTitle("Uperp");
  uperp_->GetYaxis()->SetTitle("N");


  Ntuple_=fs->make<TTree>("Ntuple","MET studies");
  Ntuple_->Branch("irun",&irun,"irun/I");
  Ntuple_->Branch("ilumi",&ilumi,"ilumi/I");
  Ntuple_->Branch("ievent",&ievent,"ievent/I");
  Ntuple_->Branch("nprimary",&nprimary,"nprimary/I");
  Ntuple_->Branch("zvertex",&zvertex,"zvertex/D");
  Ntuple_->Branch("METet",&METet,"METet/D");
  Ntuple_->Branch("METphi",&METphi,"METphi/D");
  Ntuple_->Branch("METpx",&METpx,"METpx/D");
  Ntuple_->Branch("METpy",&METpy,"METpy/D");
  Ntuple_->Branch("METSumEt",&METSumEt,"METSumEt/D");
  Ntuple_->Branch("METut",&METut,"METut/D");
  Ntuple_->Branch("METutpar",&METutpar,"METutpar/D");
  Ntuple_->Branch("METutperp",&METutperp,"METutperp/D");
  Ntuple_->Branch("METut2",&METut2,"METut2/D");
  Ntuple_->Branch("ptel1",&ptel1,"ptel1/D");
  Ntuple_->Branch("phiel1",&phiel1,"phiel1/D");
  Ntuple_->Branch("etael1",&etael1,"etael1/D");
  Ntuple_->Branch("ptel2",&ptel2,"ptel2/D");
  Ntuple_->Branch("chargeel1",&chargeel1,"chargeel1/D");
  Ntuple_->Branch("trkisoel1",&trkisoel1,"trkisoel1/D");
  Ntuple_->Branch("ecalisoel1",&ecalisoel1,"ecalisoel1/D");
  Ntuple_->Branch("hcalisoel1",&hcalisoel1,"hcalisoel1/D");
  Ntuple_->Branch("phiel2",&phiel2,"phiel2/D");
  Ntuple_->Branch("etael2",&etael2,"etael2/D");
  Ntuple_->Branch("chargeel2",&chargeel2,"chargeel2/D");
  Ntuple_->Branch("trkisoel2",&trkisoel2,"trkisoel2/D");
  Ntuple_->Branch("ecalisoel2",&ecalisoel2,"ecalisoel2/D");
  Ntuple_->Branch("hcalisoel2",&hcalisoel2,"hcalisoel2/D");
  Ntuple_->Branch("dimass",&dimass,"dimass/D");
  Ntuple_->Branch("ptjet1",&ptjet1,"ptjet1/D");
  Ntuple_->Branch("phijet1",&phijet1,"phijet1/D");
  Ntuple_->Branch("etajet1",&etajet1,"etajet1/D");
  Ntuple_->Branch("TCHEdiscr1",&TCHEdiscr1,"TCHEdiscr1/D");
  Ntuple_->Branch("SVHEdiscr1",&SVHEdiscr1,"SVHEdiscr1/D");
  Ntuple_->Branch("ptjet2",&ptjet2,"ptjet2/D");
  Ntuple_->Branch("phijet2",&phijet2,"phijet2/D");
  Ntuple_->Branch("etajet2",&etajet2,"etajet2/D");
  Ntuple_->Branch("TCHEdiscr2",&TCHEdiscr2,"TCHEdiscr2/D");
  Ntuple_->Branch("SVHEdiscr2",&SVHEdiscr2,"SVHEdiscr2/D");
  Ntuple_->Branch("dimassjet",&dimassjet,"dimassjet/D");


}

void
ElectronNtupleAnalyzer::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE( ElectronNtupleAnalyzer );
