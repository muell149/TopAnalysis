#include "TopAnalysis/TopAnalyzer/interface/JetKinematicBSM.h"


/// constructor for FWLite analyzer
JetKinematicBSM::JetKinematicBSM(const edm::ParameterSet& cfg, int nJets):
  nJets_(nJets),
  metSource_       ( cfg.getParameter<edm::InputTag>("metSource"))
{
}

/// constructor for full FW analyzer
JetKinematicBSM::JetKinematicBSM(const edm::ParameterSet& cfg):
  nJets_( cfg.getParameter<int>( "nJets" ) ),
  metSource_       ( cfg.getParameter<edm::InputTag>("metSource"))
{
}

/// fill interface for full FW analyzer
void
JetKinematicBSM::fill(const edm::Event& evt, const std::vector<pat::Jet>& jets, const double& weight)
{

  edm::Handle<std::vector<pat::MET> > mets;
  evt.getByLabel(metSource_, mets);

  fill(evt, jets, *mets, weight);
}

/// fill interface for FWLite analyzer
void
JetKinematicBSM::fill(const edm::Event& evt, const std::vector<pat::Jet>& jets, const std::vector<pat::MET>& mets, const double& weight)
{
  double sumEt=0;
  unsigned int idx=0;
  int n10=0, n20=0, n30=0, n40=0, n50=0, n60=0, n70=0, n80=0, n90=0, n100=0;

  float Missing_energy=(mets)[0].et();

  for(std::vector<pat::Jet>::const_iterator jet = jets.begin(); 
      jet!=jets.end(); ++jet, ++idx) {
    allEn_ ->Fill( jet->energy(), weight );
    allEt_ ->Fill( jet->et(), weight );
    allEta_->Fill( jet->eta(), weight );
    allPhi_->Fill( jet->phi(), weight );
    
    if( idx< en_.size() ) en_ [idx]->Fill( jet->energy(), weight );
    if( idx< et_.size() ) et_ [idx]->Fill( jet->et(), weight );
    if( idx<eta_.size() ) eta_[idx]->Fill( jet->eta(), weight );
    if( idx<phi_.size() ) phi_[idx]->Fill( jet->phi(), weight );

    //---------------------------------------------
    // check scalar sum pt
    //---------------------------------------------    
    sumEt+=jet->et();
    scalSum_->Fill( sumEt, weight);
    if(idx == 2) scalSum3_->Fill( sumEt, weight );
    if(idx == 3) scalSum4_->Fill( sumEt, weight );
    if(idx == 4) scalSum5_->Fill( sumEt, weight );
    if(idx == 5) scalSum6_->Fill( sumEt, weight );

    //---------------------------------------------
    // check jet multiplicities
    //---------------------------------------------
    if( jet->et() > 10 ) ++n10;
    if( jet->et() > 20 ) ++n20;
    if( jet->et() > 30 ) ++n30;
    if( jet->et() > 40 ) ++n40;
    if( jet->et() > 50 ) ++n50;
    if( jet->et() > 60 ) ++n60;
    if( jet->et() > 70 ) ++n70;
    if( jet->et() > 80 ) ++n80;
    if( jet->et() > 90 ) ++n90;
    if( jet->et() > 100 ) ++n100;

    //-------------------------------------------
    // check correlations between MET and Jet-ET
    //-------------------------------------------

    if( idx< MET_JetET_.size()) MET_JetET_[idx]->Fill(Missing_energy, jet->et());

  }
  mult_->Fill( jets.size(), weight );
  n10_ ->Fill( n10, weight );
  n20_ ->Fill( n20, weight );
  n30_ ->Fill( n30, weight );
  n40_ ->Fill( n40, weight );
  n50_ ->Fill( n50, weight );
  n60_ ->Fill( n60, weight );
  n70_ ->Fill( n70, weight );
  n80_ ->Fill( n80, weight );
  n90_ ->Fill( n90, weight );
  n100_ ->Fill( n100, weight );

  //-------------------------------------------
  // check correlations between MET and #Jets
  //-------------------------------------------

  MET_n30_->Fill(Missing_energy, n30);
  MET_n40_->Fill(Missing_energy, n40);
  MET_n50_->Fill(Missing_energy, n50);
  MET_n60_->Fill(Missing_energy, n60);
}

/// book for FWLite
void 
JetKinematicBSM::book()
{
  NameScheme kin("kin");
  allEn_ = new TH1F(kin.name("allE"  ), kin.name("allE"  ), 50, 0., 1300.);
  allEt_ = new TH1F(kin.name("allEt" ), kin.name("allEt" ), 50, 0., 1000.);
  allEta_= new TH1F(kin.name("allEta"), kin.name("allEta"), 34, -3.4,  3.4);
  allPhi_= new TH1F(kin.name("allPhi"), kin.name("allPhi"), 35, -3.5,  3.5);
  scalSum_ = new TH1F(kin.name("scalSum"), kin.name("scalSum"), 40, 0., 2400.);
  scalSum3_ = new TH1F(kin.name("scalSum3"), kin.name("scalSum3"), 40, 0., 1800.);
  scalSum4_ = new TH1F(kin.name("scalSum4"), kin.name("scalSum4"), 40, 0., 1800.);
  scalSum5_ = new TH1F(kin.name("scalSum5"), kin.name("scalSum5"), 40, 0., 1800.);
  scalSum6_ = new TH1F(kin.name("scalSum6"), kin.name("scalSum6"), 40, 0., 1800.);

  for(int idx=0; idx<nJets_; ++idx){
    en_.push_back ( new TH1F(kin.name("e",  idx), kin.name("en",  idx), 50,  0., 1300.) );
    et_.push_back ( new TH1F(kin.name("et", idx), kin.name("et",  idx), 30,  0., 900.) );
    eta_.push_back( new TH1F(kin.name("eta",idx), kin.name("eta", idx), 34, -3.4,  3.4) );
    phi_.push_back( new TH1F(kin.name("phi",idx), kin.name("phi", idx), 35, -3.5,  3.5) );
    MET_JetET_.push_back( new TH2F(kin.name("MET_JetET",idx), kin.name("MET_JetET", idx), 60, 0.,  600., 90, 0., 900.) );
  }

  mult_= new TH1F(kin.name("n"  ), kin.name("n"  ), 15, 0., 15.);
  n10_ = new TH1F(kin.name("n10"), kin.name("n10"), 15, 0., 15.);
  n20_ = new TH1F(kin.name("n20"), kin.name("n20"), 15, 0., 15.);
  n30_ = new TH1F(kin.name("n30"), kin.name("n30"), 15, 0., 15.);
  n40_ = new TH1F(kin.name("n40"), kin.name("n40"), 15, 0., 15.);
  n50_ = new TH1F(kin.name("n50"), kin.name("n50"), 15, 0., 15.);
  n60_ = new TH1F(kin.name("n60"), kin.name("n60"), 15, 0., 15.);
  n70_ = new TH1F(kin.name("n70"), kin.name("n70"), 15, 0., 15.);
  n80_ = new TH1F(kin.name("n80"), kin.name("n80"), 15, 0., 15.);
  n90_ = new TH1F(kin.name("n90"), kin.name("n90"), 15, 0., 15.);
  n100_ = new TH1F(kin.name("n100"), kin.name("n100"), 15, 0., 15.);

  MET_n30_= new TH2F(kin.name("MET_n30"), kin.name("MET_n30"), 60, 0., 600., 15, 0., 15.);
  MET_n40_= new TH2F(kin.name("MET_n40"), kin.name("MET_n40"), 60, 0., 600., 15, 0., 15.);
  MET_n50_= new TH2F(kin.name("MET_n50"), kin.name("MET_n50"), 60, 0., 600., 15, 0., 15.);
  MET_n60_= new TH2F(kin.name("MET_n60"), kin.name("MET_n60"), 60, 0., 600., 15, 0., 15.);
}

/// book for full FW
void 
JetKinematicBSM::book(edm::Service<TFileService>& fs)
{
  NameScheme kin("kin");
  allEn_    = fs->make<TH1F>(kin.name("allE"    ), "E(jet) [GeV]"     , 50, 0., 1300.);
  allEt_    = fs->make<TH1F>(kin.name("allEt"   ), "E_{T}(jet) [GeV]" , 50, 0., 1000.);
  allEta_   = fs->make<TH1F>(kin.name("allEta"  ), "#eta(jet)", 34, -3.4,  3.4);
  allPhi_   = fs->make<TH1F>(kin.name("allPhi"  ), "#phi(jet)", 35, -3.5,  3.5);
  scalSum_  = fs->make<TH1F>(kin.name("scalSum"), "#Sigma_{all jets}(E_{T}) [GeV]", 40, 0., 2400.);
  scalSum3_ = fs->make<TH1F>(kin.name("scalSum3"), "#Sigma_{jet1-jet3}(E_{T}) [GeV]", 40, 0., 1800.);
  scalSum4_ = fs->make<TH1F>(kin.name("scalSum4"), "#Sigma_{jet1-jet4}(E_{T}) [GeV]", 40, 0., 1800.);
  scalSum5_ = fs->make<TH1F>(kin.name("scalSum5"), "#Sigma_{jet1-jet5}(E_{T}) [GeV]", 40, 0., 1800.);
  scalSum6_ = fs->make<TH1F>(kin.name("scalSum6"), "#Sigma_{jet1-jet6}(E_{T}) [GeV]", 40, 0., 1800.);

  for(int idx=0; idx<nJets_; ++idx){
    int idj = idx+1;
    TString titleBase = "(jet"; titleBase += idj; titleBase += ")";
    TString title_en  = "E"     + titleBase + " [GeV]";
    TString title_et  = "E_{T}" + titleBase + " [GeV]";
    TString title_eta = "#eta"  + titleBase;
    TString title_phi = "phi"   + titleBase;
    en_.push_back ( fs->make<TH1F>(kin.name("e",  idx), title_en , 50,   0., 1300.) );
    et_.push_back ( fs->make<TH1F>(kin.name("et", idx), title_et , 30,   0., 900.) );
    eta_.push_back( fs->make<TH1F>(kin.name("eta",idx), title_eta, 34, -3.4,  3.4) );
    phi_.push_back( fs->make<TH1F>(kin.name("phi",idx), title_phi, 35, -3.5,  3.5) );
    MET_JetET_.push_back( fs->make<TH2F>(kin.name("MET_JetET",idx), kin.name("MET_JetET", idx), 60, 0.,  600., 90, 0., 900.) );

  }

  mult_= fs->make<TH1F>(kin.name("n"  ), "N_{jets}"              , 15, 0., 15.);
  n10_ = fs->make<TH1F>(kin.name("n10"), "N_{jets}(p_{T}>10GeV)", 15, 0., 15.);
  n20_ = fs->make<TH1F>(kin.name("n20"), "N_{jets}(p_{T}>20GeV)", 15, 0., 15.);
  n30_ = fs->make<TH1F>(kin.name("n30"), "N_{jets}(p_{T}>30GeV)", 15, 0., 15.);
  n40_ = fs->make<TH1F>(kin.name("n40"), "N_{jets}(p_{T}>40GeV)", 15, 0., 15.);
  n50_ = fs->make<TH1F>(kin.name("n50"), kin.name("n50"), 15, 0., 15.);
  n60_ = fs->make<TH1F>(kin.name("n60"), kin.name("n60"), 15, 0., 15.);
  n70_ = fs->make<TH1F>(kin.name("n70"), kin.name("n70"), 15, 0., 15.);
  n80_ = fs->make<TH1F>(kin.name("n80"), kin.name("n80"), 15, 0., 15.);
  n90_ = fs->make<TH1F>(kin.name("n90"), kin.name("n90"), 15, 0., 15.);
  n100_ = fs->make<TH1F>(kin.name("n100"), kin.name("n100"), 15, 0., 15.);

  MET_n30_= fs->make<TH2F>(kin.name("MET_n30"), kin.name("MET_n30"), 60, 0., 600., 15, 0., 15.);
  MET_n40_= fs->make<TH2F>(kin.name("MET_n40"), kin.name("MET_n40"), 60, 0., 600., 15, 0., 15.);
  MET_n50_= fs->make<TH2F>(kin.name("MET_n50"), kin.name("MET_n50"), 60, 0., 600., 15, 0., 15.);
  MET_n60_= fs->make<TH2F>(kin.name("MET_n60"), kin.name("MET_n60"), 60, 0., 600., 15, 0., 15.);
}

/// book for full FW with output stream
void 
JetKinematicBSM::book(edm::Service<TFileService>& fs, ofstream& file)
{
  NameScheme kin("kin");
  allEn_    = fs->make<TH1F>(kin.name(file, "allE"    ), "E(jet) [GeV]"  , 50, 0., 1300.);
  allEt_    = fs->make<TH1F>(kin.name(file, "allEt"   ), "E_{T}(jet) [GeV]" , 50, 0., 1000.);
  allEta_   = fs->make<TH1F>(kin.name(file, "allEta"  ), "#eta(jet)", 34, -3.4,  3.4);
  allPhi_   = fs->make<TH1F>(kin.name(file, "allPhi"  ), "#phi(jet)", 35, -3.5,  3.5);
  scalSum_  = fs->make<TH1F>(kin.name("scalSum"), "#Sigma_{all jets}(E_{T}) [GeV]", 40, 0., 2400.);
  scalSum3_ = fs->make<TH1F>(kin.name(file, "scalSum3"), "#Sigma_{jet1-jet3}(E_{T}) [GeV]", 40, 0., 1800.);
  scalSum4_ = fs->make<TH1F>(kin.name(file, "scalSum4"), "#Sigma_{jet1-jet4}(E_{T}) [GeV]", 40, 0., 1800.);
  scalSum5_ = fs->make<TH1F>(kin.name(file, "scalSum5"), "#Sigma_{jet1-jet5}(E_{T}) [GeV]", 40, 0., 1800.);
  scalSum6_ = fs->make<TH1F>(kin.name(file, "scalSum6"), "#Sigma_{jet1-jet6}(E_{T}) [GeV]", 40, 0., 1800.);

  for(int idx=0; idx<nJets_; ++idx){
    int idj = idx+1;
    TString titleBase = "(jet"; titleBase += idj; titleBase += ")";
    TString title_en  = "E"     + titleBase + " [GeV]";
    TString title_et  = "E_{T}" + titleBase + " [GeV]";
    TString title_eta = "#eta"  + titleBase;
    TString title_phi = "#phi"   + titleBase;
    en_.push_back ( fs->make<TH1F>(kin.name(file, "e",  idx), title_en , 50,   0., 1300.) );
    et_.push_back ( fs->make<TH1F>(kin.name(file, "et", idx), title_et , 30,   0., 900.) );
    eta_.push_back( fs->make<TH1F>(kin.name(file, "eta",idx), title_eta, 34, -3.4,  3.4) );
    phi_.push_back( fs->make<TH1F>(kin.name(file, "phi",idx), title_phi, 35, -3.5,  3.5) );
    MET_JetET_.push_back( fs->make<TH2F>(kin.name("MET_JetET",idx), kin.name("MET_JetET", idx), 60, 0.,  600., 90, 0., 900.));
  }

  mult_= fs->make<TH1F>(kin.name(file, "n"  ), "N_{jets}"              , 15, 0., 15.);
  n10_ = fs->make<TH1F>(kin.name(file, "n10"), "N_{jets}(p_{T}>10GeV)", 15, 0., 15.);
  n20_ = fs->make<TH1F>(kin.name(file, "n20"), "N_{jets}(p_{T}>20GeV)", 15, 0., 15.);
  n30_ = fs->make<TH1F>(kin.name(file, "n30"), "N_{jets}(p_{T}>30GeV)", 15, 0., 15.);
  n40_ = fs->make<TH1F>(kin.name(file, "n40"), "N_{jets}(p_{T}>40GeV)", 15, 0., 15.);
  n50_ = fs->make<TH1F>(kin.name("n50"), kin.name("n50"), 15, 0., 15.);
  n60_ = fs->make<TH1F>(kin.name("n60"), kin.name("n60"), 15, 0., 15.);
  n70_ = fs->make<TH1F>(kin.name("n70"), kin.name("n70"), 15, 0., 15.);
  n80_ = fs->make<TH1F>(kin.name("n80"), kin.name("n80"), 15, 0., 15.);
  n90_ = fs->make<TH1F>(kin.name("n90"), kin.name("n90"), 15, 0., 15.);
  n100_ = fs->make<TH1F>(kin.name("n100"), kin.name("n100"), 15, 0., 15.);

  MET_n30_= fs->make<TH2F>(kin.name("MET_n30"), kin.name("MET_n30"), 60, 0., 600., 15, 0., 15.);
  MET_n40_= fs->make<TH2F>(kin.name("MET_n40"), kin.name("MET_n40"), 60, 0., 600., 15, 0., 15.);
  MET_n50_= fs->make<TH2F>(kin.name("MET_n50"), kin.name("MET_n50"), 60, 0., 600., 15, 0., 15.);
  MET_n60_= fs->make<TH2F>(kin.name("MET_n60"), kin.name("MET_n60"), 60, 0., 600., 15, 0., 15.);
}

/// write to file and free allocated space for FWLite
void 
JetKinematicBSM::write(const char* filename, const char* directory)
{
  /// save histograms to file
  TFile outFile( filename, "recreate" );
  outFile.mkdir( directory );
  outFile.cd( directory );

  /// basic kinematic
  mult_->Write( );
  n10_ ->Write( );
  n20_ ->Write( );
  n30_ ->Write( );
  n40_ ->Write( );
  n50_ ->Write( );
  n60_ ->Write( );
  n70_ ->Write( );
  n80_ ->Write( );
  n90_ ->Write( );
  n100_ ->Write( );

  MET_n30_->Write();
  MET_n40_->Write();
  MET_n50_->Write();
  MET_n60_->Write();

  outFile.Close();

  // free allocated space
  delete mult_;
  delete n10_;
  delete n20_;
  delete n30_;
  delete n40_;
  delete n50_;
  delete n60_;
  delete n70_;
  delete n80_;
  delete n90_;
  delete n100_;

  delete MET_n30_;
  delete MET_n40_;
  delete MET_n50_;
  delete MET_n60_;
}
