#include "TopAnalysis/TopAnalyzer/interface/GenJetComposition.h"

/// default constructor for generator level analysis in fw lite
GenJetComposition::GenJetComposition()
{
}

/// default constructor for full fw
GenJetComposition::GenJetComposition(const edm::ParameterSet& cfg) :
  index_( cfg.getParameter<int>( "index" ) )
{
}

/// histogramm booking for fwlite 
void GenJetComposition::book()
{
  // Jet Constituents plot for all jets
  hists_["JetConstituents"  ] = new TH1F( "JetConstituents", "JetConstituents",   600, -0.5 , 599.5 );
  // Jet Constituents plot for jets with muon
  hists_["JetConstituentsMu"] = new TH1F( "JetConstituentsFromMuJets", "JetConstituentsFromMuJets",   600, -0.5 , 599.5 );
  // Jet Constituents plot for jets with muon, muon-neutrino and tau-neutrino
  hists_["JetConstituentsMuNuNu"] = new TH1F( "JetConstituentsMuMuNuAndTauNu", "JetConstituentsMuMuNuAndTauNu",   600, -0.5 , 599.5 );
  // pt(jet) vs pt(jet without mu+muNu+tauNu)
  hists2D_["ptJetMuNuTau_"] = new TH2F( "ptMuNuTau_" , "ptMuNuTau_" ,  200,    0.,  200.,     200,   0.,  200.);
  // pt(jet) vs pt(without mu+muNu)
  hists2D_["ptJetMuNu_"   ] = new TH2F( "ptMuNu_"    , "ptMuNu_"    ,  200,    0.,  200.,     200,   0.,  200.);
  // pt(jet) vs pt(mu)
  hists2D_["ptJetMu_"     ] = new TH2F( "ptMu_"      , "ptMu_"      ,  200,    0.,  200.,     200,   0.,  200.);
}

/// histogramm booking for fw
void GenJetComposition::book(edm::Service<TFileService>& fs)
{
  // Jet Constituents plot for all jets
  hists_["JetConstituents"  ] = fs->make<TH1F>( "JetConstituents" , "JetConstituents" ,   600, -0.5 , 599.5 );
  // Jet Constituents plot for jets with muon
  hists_["JetConstituentsMu"] = fs->make<TH1F>( "JetConstituentsFromMuJets" , "JetConstituentsFromMuJets" ,   600, -0.5 , 599.5 );
  // Jet Constituents plot for jets with muon, muon-neutrino and tau-neutrino
  hists_["JetConstituentsMuNuNu"] = fs->make<TH1F>( "JetConstituentsMuMuNuAndTauNu", "JetConstituentsMuMuNuAndTauNu",   600, -0.5 , 599.5 );
  // pt(jet) vs pt(mu+muNu+tauNu)
  hists2D_["ptMuNuTau_"] = fs->make<TH2F>( "ptMuNuTau_" , "ptMuNuTau_"  ,  200,    0.,  200.,     200,   0.,  200.);
  // pt(jet) vs pt(mu+muNu)
  hists2D_["ptMuNu_"   ] = fs->make<TH2F>( "ptMuNu_"    , "ptMuNu_"     ,  200,    0.,  200.,     200,   0.,  200.);
  // pt(jet) vs pt(mu)
  hists2D_["ptMu_"     ] = fs->make<TH2F>( "ptMu_"      , "ptMu_"       ,  200,    0.,  200.,     200,   0.,  200.);



}


/// histogram filling interface for reconstruction level for access with fwlite or full framework
void
GenJetComposition::fill(const edm::View<reco::GenJet>& jets, const double& weight)
{
  // index for the leading, 2. leading, 3. leading jet
  // to be compared with index_ from the module config
  // where index_=-1 means 'fill all jets' and index_=n,
  // n>=-1 means 'fill only n-th leading jet'

  int index=0;
  for(edm::View<reco::GenJet>::const_iterator jet=jets.begin(); jet!=jets.end(); ++jet, ++index){
    if( index_<0 || index_==index ){    
      
      std::vector<const reco::GenParticle*> constituents = jet->getGenConstituents();

      for(std::vector<const reco::GenParticle*>::const_iterator constituent=constituents.begin(); constituent!=constituents.end(); ++constituent){
	// see general jet content-filled for every jet
	hists_.find("JetConstituents")->second->Fill(abs((*constituent)->pdgId()) , weight);
	// a) for jets containing a muon continue
	if(abs((*constituent)->pdgId())==13){
	  // plot jet-pt with and without the mu
	  hists2D_.find("ptMu_")->second->Fill(jet->pt() , (jet->p4()-(*constituent)->p4()).pt() , weight);
	  // see decay chain of muons within jets (5 steps of ancestors if existing)
	  std::cout << (*constituent)->pdgId() << " (" << (*constituent)->status() << ")";
	  if((*constituent)->numberOfMothers()>0) std::cout << " <- " << (*constituent)->mother()->pdgId() << " (" << (*constituent)->mother()->status() << ")";
	  if((*constituent)->mother()->numberOfMothers()>0) std::cout << " <- " << (*constituent)->mother()->mother()->pdgId() << " (" << (*constituent)->mother()->mother()->status() << ")";
	  if((*constituent)->mother()->mother()->numberOfMothers()>0) std::cout << " <- " << (*constituent)->mother()->mother()->mother()->pdgId() << " (" << (*constituent)->mother()->mother()->mother()->status() << ")";
	  if((*constituent)->mother()->mother()->mother()->numberOfMothers()>0) std::cout << " <- " << (*constituent)->mother()->mother()->mother()->mother()->pdgId() << " (" << (*constituent)->mother()->mother()->mother()->mother()->status() << ")";
	  if((*constituent)->mother()->mother()->mother()->mother()->numberOfMothers()>0) std::cout << " <- " << (*constituent)->mother()->mother()->mother()->mother()->mother()->pdgId() << " (" << (*constituent)->mother()->mother()->mother()->mother()->mother()->status() << ")";
	    std::cout << std::endl;
	  // loop all jet constituents a 2nd time
	  for(std::vector<const reco::GenParticle*>::const_iterator constituentMu=constituents.begin(); constituentMu!=constituents.end(); ++constituentMu){
	    // see jet content of jets containig a muon
	    hists_.find("JetConstituentsMu")->second->Fill(abs((*constituentMu)->pdgId()) , weight);
	    // search for jets containing muon && muonNeutrino && tauNeutrino (all products from semimuonic tau-decay)
	    // b) if event content containes a muonNeutrino continue
	    if(abs((*constituentMu)->pdgId())==14){
	      std::cout << "contains also #nu_{#mu}";
	      // plot jet-pt with and without the mu and nu_mu
	      hists2D_.find("ptMuNu_")->second->Fill(jet->pt() , (jet->p4()-(*constituent)->p4()-(*constituentMu)->p4()).pt() , weight);
	      // loop all jet constituents a 3rd time
	      for(std::vector<const reco::GenParticle*>::const_iterator constituentMuNu=constituents.begin(); constituentMuNu!=constituents.end(); ++constituentMuNu){
		// c) if event content containes a tauNeutrino continue
		if(abs((*constituentMuNu)->pdgId())==16){ 
		  std::cout << " & #nu_{#tau}"; 
		  // plot jet-pt with and without the three objects from leptonic tau decay
		  hists2D_.find("ptMuNuTau_")->second->Fill(jet->pt() , (jet->p4()-(*constituent)->p4()-(*constituentMu)->p4()-(*constituentMuNu)->p4()).pt() , weight);
		    // loop all jet constituents a 4th time
		    for(std::vector<const reco::GenParticle*>::const_iterator constituentMuNuNu=constituents.begin(); constituentMuNuNu!=constituents.end(); ++constituentMuNuNu){
		      //  see content of jets containing mu, nu_mu and nu_tau
		      hists_.find("JetConstituentsMuNuNu")->second->Fill(abs((*constituentMuNuNu)->pdgId()) , weight);
		    }
		}
	      }
	      std::cout << std::endl;
	    }
	  }
	}
      }
    }
  }
}

