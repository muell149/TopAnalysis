#include "TopAnalysis/TopAnalyzer/interface/JetId.h"


/// constructor for FWLite analyzer
JetId::JetId(int nJets):
  nJets_(nJets), normEvt_( 0 ), normJet_( 0 ) 
{
}

/// constructor for full FW analyzer
JetId::JetId(const edm::ParameterSet& cfg):
  nJets_( cfg.getParameter<int>( "nJets" ) ),
  normEvt_( 0 ), normJet_( 0 )
{
}

/// fill interface for full FW analyzer
void
JetId::fill(const edm::Event& evt, const std::vector<pat::Jet>& jets, const double& weight=1.)
{
  fill(jets, weight);
}

/// fill interface for full FW analyzer
void
JetId::fill(const std::vector<pat::Jet>& jets, const double& weight=1.)
{
  normEvt_+=weight;
  unsigned int idx=0;
  for(std::vector<pat::Jet>::const_iterator jet = jets.begin(); 
      jet!=jets.end(); ++jet, ++idx) {
    normJet_+=weight;
    aEmf_->Fill( jet->emEnergyFraction(), weight );
    aHad_->Fill( jet->energyFractionHadronic(), weight );
    aHof_->Fill( jet->hadEnergyInHO(), weight );
    
    if( idx<emf_.size() ) emf_[idx]->Fill( jet->emEnergyFraction(), weight );
    if( idx<had_.size() ) had_[idx]->Fill( jet->energyFractionHadronic(), weight );
    if( idx<hof_.size() ) hof_[idx]->Fill( jet->hadEnergyInHO(), weight );
    
    //---------------------------------------------
    // check jet profiles
    //---------------------------------------------
    nTwr_->Fill(jet->getCaloConstituents().size(), weight);
    if(jet->et()>0.){
      std::vector<CaloTowerPtr> caloTowerPtr = jet->getCaloConstituents();
      for(unsigned int jdx=0; jdx<caloTowerPtr.size(); ++jdx){
	aProfEta_->Fill( jet->eta()-caloTowerPtr[jdx]->eta(), caloTowerPtr[jdx]->et()/jet->et() );
	aProfPhi_->Fill( jet->phi()-caloTowerPtr[jdx]->phi(), caloTowerPtr[jdx]->et()/jet->et() );
	
	if( idx<profEta_.size()) profEta_[idx]->Fill( jet->eta()-caloTowerPtr[jdx]->eta(), caloTowerPtr[jdx]->et()/jet->et() );
	if( idx<profPhi_.size()) profPhi_[idx]->Fill( jet->phi()-caloTowerPtr[jdx]->phi(), caloTowerPtr[jdx]->et()/jet->et() );
      }
    }
  }
}

/// book for FWLite
void 
JetId::book()
{
  NameScheme id("id");
  aEmf_= new TH1F(id.name("allEmf"),  id.name("allEmf" ), 60, -0.1,  1.1);
  aHad_= new TH1F(id.name("allHdf"),  id.name("allHdf" ), 60, -0.1,  1.1);
  aHof_= new TH1F(id.name("allHdHO"), id.name("allHdHO"), 55, -10., 100.);
  
  for(int idx=0; idx<nJets_; ++idx){
    emf_.push_back( new TH1F(id.name("emf",idx), id.name("emf",idx), 60, -0.1,  1.1) );
    had_.push_back( new TH1F(id.name("had",idx), id.name("had",idx), 60, -0.1,  1.1) );
    hof_.push_back( new TH1F(id.name("hof",idx), id.name("hof",idx), 55, -10., 100.) );
  }
  NameScheme pro("pro");
  nTwr_ = new TH1F(pro.name("nTwr"), pro.name("nTwr"), 100, 0., 100.);
  aProfEta_= new TH1F(pro.name("allEta"), pro.name("allEta"), 50, -0.5, 0.5);
  aProfPhi_= new TH1F(pro.name("allPhi"), pro.name("allPhi"), 50, -0.5, 0.5);
  
  for(int idx=0; idx<nJets_; ++idx){
    profEta_.push_back( new TH1F(pro.name("eta", idx),pro.name("eta", idx), 50, -0.5, 0.5) );
    profPhi_.push_back( new TH1F(pro.name("phi", idx),pro.name("phi", idx), 50, -0.5, 0.5) );
  }
}

/// book for full FW
void 
JetId::book(edm::Service<TFileService>& fs)
{
  NameScheme id("id");
  aEmf_= fs->make<TH1F>(id.name("allEmf"),  "em. energy frac. (jet)"  , 60, -0.1,  1.1);
  aHad_= fs->make<TH1F>(id.name("allHdf"),  "hadr. energy frac. (jet)", 60, -0.1,  1.1);
  aHof_= fs->make<TH1F>(id.name("allHdHO"), "E_{HO}(jet) [GeV]"       , 55, -10., 100.);
  
  for(int idx=0; idx<nJets_; ++idx){
    int idj = idx+1;
    TString titleBase = "(jet"; titleBase += idj; titleBase += ")";
    TString title_emf = "em. energy frac. "   + titleBase;
    TString title_had = "hadr. energy frac. " + titleBase;
    TString title_hof = "E_{HO}"              + titleBase + " [GeV]";
    emf_.push_back( fs->make<TH1F>(id.name("emf", idx), title_emf, 60, -0.1,  1.1) );
    had_.push_back( fs->make<TH1F>(id.name("had", idx), title_had, 60, -0.1,  1.1) );
    hof_.push_back( fs->make<TH1F>(id.name("hof", idx), title_hof, 55, -10., 100.) );
  }

  NameScheme pro("pro");
  nTwr_    = fs->make<TH1F>(pro.name("nTwr"  ), "N_{tower}(jet)"           , 100,   0., 100.);
  aProfEta_= fs->make<TH1F>(pro.name("allEta"), "(#eta_{jet}-#eta_{tower})",  50, -0.5,  0.5);
  aProfPhi_= fs->make<TH1F>(pro.name("allPhi"), "(#phi_{jet}-#phi_{tower})",  50, -0.5,  0.5);

  for(int idx=0; idx<nJets_; ++idx){
    int idj = idx+1;
    TString titleBase = "jet"; titleBase += idj;
    TString title_profEta = "(#eta_{" + titleBase + "}-#eta_{tower})";
    TString title_profPhi = "(#phi_{" + titleBase + "}-#phi_{tower})";
    profEta_.push_back( fs->make<TH1F>(pro.name("eta", idx), title_profEta, 50, -0.5, 0.5) );
    profPhi_.push_back( fs->make<TH1F>(pro.name("phi", idx), title_profPhi, 50, -0.5, 0.5) );
  }
}

/// book for full FW with output stream
void 
JetId::book(edm::Service<TFileService>& fs, ofstream& file)
{
  NameScheme id("id");
  aEmf_= fs->make<TH1F>(id.name(file, "allEmf"),  "em. energy frac. (jet)"  , 60, -0.1,  1.1);
  aHad_= fs->make<TH1F>(id.name(file, "allHdf"),  "hadr. energy frac. (jet)", 60, -0.1,  1.1);
  aHof_= fs->make<TH1F>(id.name(file, "allHdHO"), "E_{HO}(jet) [GeV]"       , 55, -10., 100.);
  
  for(int idx=0; idx<nJets_; ++idx){
    int idj = idx+1;
    TString titleBase = "(jet"; titleBase += idj; titleBase += ")";
    TString title_emf = "em. energy frac. "   + titleBase;
    TString title_had = "hadr. energy frac. " + titleBase;
    TString title_hof = "E_{HO}"              + titleBase + " [GeV]";
    emf_.push_back( fs->make<TH1F>(id.name(file, "emf", idx), title_emf, 60, -0.1,  1.1) );
    had_.push_back( fs->make<TH1F>(id.name(file, "had", idx), title_had, 60, -0.1,  1.1) );
    hof_.push_back( fs->make<TH1F>(id.name(file, "hof", idx), title_hof, 55, -10., 100.) );
  }

  NameScheme pro("pro");
  nTwr_    = fs->make<TH1F>(pro.name(file, "nTwr"  ), "N_{tower}(jet)"           , 100,   0., 100.);
  aProfEta_= fs->make<TH1F>(pro.name(file, "allEta"), "(#eta_{jet}-#eta_{tower})",  50, -0.5,  0.5);
  aProfPhi_= fs->make<TH1F>(pro.name(file, "allPhi"), "(#phi_{jet}-#phi_{tower})",  50, -0.5,  0.5);

  for(int idx=0; idx<nJets_; ++idx){
    int idj = idx+1;
    TString titleBase = "jet"; titleBase += idj;
    TString title_profEta = "(#eta_{" + titleBase + "}-#eta_{tower})";
    TString title_profPhi = "(#phi_{" + titleBase + "}-#phi_{tower})";
    profEta_.push_back( fs->make<TH1F>(pro.name(file, "eta", idx), title_profEta, 50, -0.5, 0.5) );
    profPhi_.push_back( fs->make<TH1F>(pro.name(file, "phi", idx), title_profPhi, 50, -0.5, 0.5) );
  }
}

/// write to file and free allocated space for FWLite
void 
JetId::write(const char* filename, const char* directory)
{
  /// save histograms to file
  TFile outFile( filename, "recreate" );
  outFile.mkdir( directory );
  outFile.cd( directory );

  /// basic kinematic
  aEmf_->Write( );
  aHad_->Write( );
  aHof_->Write( );
  nTwr_->Write( );
  aProfEta_->Write( );
  aProfPhi_->Write( );

  outFile.Close();

  // free allocated space
  delete aEmf_; 
  delete aHad_; 
  delete aHof_; 
  delete nTwr_; 
  delete aProfEta_;
  delete aProfPhi_; 
}
