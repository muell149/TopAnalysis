#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "AnalysisDataFormats/TopObjects/interface/TtGenEvent.h"
#include "TopAnalysis/TopAnalyzer/plugins/SUSYEventAnalyzer.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"
#include  <stdio.h>
#include "DataFormats/METReco/interface/CaloMETCollection.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/GenMETCollection.h"


using namespace std;
 
SUSYEventAnalyzer::SUSYEventAnalyzer(const edm::ParameterSet& cfg):
  //inputGenEvent_(cfg.getParameter<edm::InputTag>("genEvent")),
  src_          (cfg.getParameter<edm::InputTag>("source")),
  met_          (cfg.getParameter<edm::InputTag>("met")),
  jets_          (cfg.getParameter<edm::InputTag>("jets"))
{ 
  edm::Service<TFileService> fs;

  Missing_energy_ = fs->make<TH1F>("MET","MET", 50, 0., 1000.);
  HT_ = fs->make<TH1F>("HT","HT", 100, 0., 2000.);
  njets_ = fs->make<TH1F>("njets","njets",15 , 0.5, 15.5);

  tbW_red_    = fs->make<TH1F>("tbW_red",    "m(tbW)",     260, 0., 1300.);
  btW_red_    = fs->make<TH1F>("btW_red",    "m(btW)",     260, 0., 1300.);
  tWb_red_    = fs->make<TH1F>("tWb_red",    "m(tWb)",     260, 0., 1300.);
  bWt_red_    = fs->make<TH1F>("bWt_red",    "m(bWt)",     260, 0., 1300.);
  tt_red_     = fs->make<TH1F>("tt_red",    "m(tt)",     260, 0., 1300.);
  all_red_    = fs->make<TH1F>("all_red",    "m(tt-like)",     260, 0., 1300.);

  tbW_    = fs->make<TH1F>("tbW",    "m(tbW)",     260, 0., 1300.);
  btW_    = fs->make<TH1F>("btW",    "m(btW)",     260, 0., 1300.);
  tWb_    = fs->make<TH1F>("tWb",    "m(tWb)",     260, 0., 1300.);
  bWt_    = fs->make<TH1F>("bWt",    "m(bWt)",     260, 0., 1300.);
  tt_     = fs->make<TH1F>("tt",     "m(tt)",     260, 0., 1300.);
  bb_     = fs->make<TH1F>("tt",     "m(tt)",     260, 0., 1300.);
  all_    = fs->make<TH1F>("all",    "m(tt-like)",     260, 0., 1300.);

  all_red_MET_ = fs->make<TH2F>("all_red_MET","all_MET", 260, 0., 1300.,50, 0., 1000);
  all_red_HT_ = fs->make<TH2F>("all_red_HT","all_HT", 260, 0., 1300.,100, 0., 2000);
  all_red_njets_ = fs->make<TH2F>("all_red_njets","all_njets", 260, 0., 1300.,10 , 0.5, 10.5);

}

SUSYEventAnalyzer::~SUSYEventAnalyzer()
{
}

void
SUSYEventAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{  

  //--------------------------------------------------
  // Handles
  //-------------------------------------------------
  edm::Handle<reco::GenParticleCollection> src;
  evt.getByLabel(src_, src);
  edm::Handle<std::vector<pat::MET> > met;
  evt.getByLabel(met_, met);
  edm::Handle<std::vector<pat::Jet> > jets;
  evt.getByLabel(jets_, jets);

  //-------------------------------------------------
  // HT, MET, njets
  //-------------------------------------------------

  const std::vector<pat::MET>& Met=*met;
  const std::vector<pat::Jet>& Jets=*jets;

  double HT=0;
  int njets=0;
  
  //std::cout << "Nr. of jets: " << jets->size() << std::endl;
  
  for(std::vector<pat::Jet>::const_iterator jet = Jets.begin(); jet!=Jets.end(); ++jet)
    {
      HT=HT+jet->et();
      njets=njets+1;
    }

  //--------------------------------------------------
  // Find cascades
  //--------------------------------------------------

  reco::GenParticleCollection collection=*src;
  reco::GenParticleCollection::const_iterator g=collection.begin();

  int gluino=0;
  int lep=0;
  bool tau_veto=false;
  bool top1=false;
  bool bottom1=false;
  bool top2=false;
  bool bottom2=false;
  bool W2=false;
  bool top3=false;
  bool bottom3=false;
  bool W3=false;
  reco::Particle::LorentzVector p4_top1_red;
  reco::Particle::LorentzVector p4_bottom1;
  reco::Particle::LorentzVector p4_top2_red;
  reco::Particle::LorentzVector p4_bottom2;
  reco::Particle::LorentzVector p4_W2_red;
  reco::Particle::LorentzVector p4_top3_red;
  reco::Particle::LorentzVector p4_bottom3;
  reco::Particle::LorentzVector p4_W3_red;

  reco::Particle::LorentzVector p4_top1;
  reco::Particle::LorentzVector p4_top2;
  reco::Particle::LorentzVector p4_W2;
  reco::Particle::LorentzVector p4_top3;
  reco::Particle::LorentzVector p4_W3;


  double inv_mass_red=0;
  double inv_mass=0;

  for( ;g!=collection.end();++g)
    { 
      std::cout << "===========================================" << std::endl;
      std::cout << "===========================pdgId: " << g->pdgId() << std::endl;
      std::cout << "===========================================" << std::endl;

      // if particle1 is gluino
      if(abs(g->pdgId())==1000021 && g->status()==3 )
	{
	  for(reco::GenParticle::const_iterator gd=g->begin(); gd!=g->end(); ++gd)
	    {
	      std::cout << "daughter: " << gd->pdgId() << std::endl;

	      if(abs(gd->pdgId())==6)
		{
		  top1=true;
		  p4_top1_red = gd->p4();
		  p4_top1 = gd->p4();

		  for(reco::GenParticle::const_iterator td1=gd->begin(); td1!=gd->end(); ++td1)
		    {		    
		      if(abs(td1->pdgId())==24)
			{
			  for(reco::GenParticle::const_iterator Wd1=td1->begin(); Wd1!=td1->end(); ++Wd1)
			    {			    
			      if(abs(Wd1->pdgId())==12 || abs(Wd1->pdgId())==14)
				{
				  lep=lep+1;
				  p4_top1_red=p4_top1_red-(Wd1->p4());
				}
			      if(abs(Wd1->pdgId())==15)
				{
				  tau_veto=true;
				}
			    }
			}
		    }
		}
	      if(abs(gd->pdgId())==5)
		{
		  bottom1=true;
		  p4_bottom1 = gd->p4();
		}

	      // if particle2 is stop1, sbottom1, stop2 or sbottom2
	      if( (abs(gd->pdgId())==1000006 || abs(gd->pdgId())==1000005 || abs(gd->pdgId())==1000006 || abs(gd->pdgId())==1000005) && gd->status()==3)
		{
		  for(reco::GenParticle::const_iterator gdd=gd->begin(); gdd!=gd->end(); ++gdd)
		    {
		      //std::cout << "daughterdaughter: " << gdd->pdgId() << std::endl;

		      if(abs(gdd->pdgId())== 6)
			{ 
			  top2=true;
			  p4_top2_red = gdd->p4();
			  p4_top2 = gdd->p4();

			  for(reco::GenParticle::const_iterator td2=gdd->begin(); td2!=gdd->end(); ++td2)
			    {		    
			      if(abs(td2->pdgId())==24)
				{
				  for(reco::GenParticle::const_iterator Wd2=td2->begin(); Wd2!=td2->end(); ++Wd2)
				    {			    
				      if(abs(Wd2->pdgId())==12 || abs(Wd2->pdgId())==14)
					{
					  lep=lep+1;
					  p4_top2_red=p4_top2_red-(Wd2->p4());
					}
				      if(abs(Wd2->pdgId())==15)
					{
					  tau_veto=true;
					}
				    }
				}
			    }
			}

		      if(abs(gdd->pdgId())== 5)
			{ 
			  bottom2=true;
			  p4_bottom2 = gdd->p4();
			}
		      if(abs(gdd->pdgId())== 24)
			{ 
			  W2=true;
			  p4_W2_red = gdd->p4();
			  p4_W2 = gdd->p4();

			  for(reco::GenParticle::const_iterator WWd2=gdd->begin(); WWd2!=gdd->end(); ++WWd2)
			    {			    
			      if(abs(WWd2->pdgId())==12 || abs(WWd2->pdgId())==14)
				{
				  lep=lep+1;
				  p4_W2_red=p4_W2_red-(WWd2->p4());
				}
			      if(abs(WWd2->pdgId())==15)
				{
				  tau_veto=true;
				}
			    }
			}
		      // if particle3 is stop1, sbottom1, stop2, sbottom2, chargino1 or chargino2
		      if( (abs(gd->pdgId())==1000006 || abs(gd->pdgId())==1000005 || abs(gd->pdgId())==1000006 || abs(gd->pdgId())==1000005 || abs(gdd->pdgId())==1000024 || abs(gdd->pdgId())==1000037 ) && gdd->status()==3)
			{
			  for(reco::GenParticle::const_iterator gddd=gdd->begin(); gddd!=gdd->end(); ++gddd)
			    { 
			      if(abs(gddd->pdgId())== 6)
				{ 
				  top3=true;
				  p4_top3_red = gddd->p4();
				  p4_top3 = gddd->p4();
				  
				  for(reco::GenParticle::const_iterator td3=gddd->begin(); td3!=gddd->end(); ++td3)
				    {		    
				      if(abs(td3->pdgId())==24)
					{
					  for(reco::GenParticle::const_iterator Wd3=td3->begin(); Wd3!=td3->end(); ++Wd3)
					    {			    
					      if(abs(Wd3->pdgId())==12 || abs(Wd3->pdgId())==14)
						{
						  lep=lep+1;
						  p4_top3_red=p4_top3_red-(Wd3->p4());
						}
					      if(abs(Wd3->pdgId())==15)
						{
						  tau_veto=true;
						}
					    }
					}
				    }
				}
			      if(abs(gddd->pdgId())== 5)
				{ 
				  bottom3=true;
				  p4_bottom3 = gddd->p4();
				}
			      if(abs(gddd->pdgId())== 24)
				{ 
				  W3=true;
				  p4_W3_red = gddd->p4();
				  p4_W3 = gddd->p4();
				  
				  for(reco::GenParticle::const_iterator WWd3=gddd->begin(); WWd3!=gddd->end(); ++WWd3)
				    {			    
				      if(abs(WWd3->pdgId())==12 || abs(WWd3->pdgId())==14)
					{
					  lep=lep+1;
					  p4_W3_red=p4_W3_red-(WWd3->p4());
					}
				      if(abs(WWd3->pdgId())==15)
					{
					  tau_veto=true;
					}
				    }
				}
			    }
			}     
		    }
		}
	    }  
	}
    }

  if(lep <=2 && tau_veto==false && gluino==0)
    {

      if( top1==true && bottom2==true && W3==true)
	{
	  inv_mass_red=sqrt( (p4_top1_red+p4_bottom2+p4_W3_red).Dot(p4_top1_red+p4_bottom2+p4_W3_red) );
	  //std::cout << "Invariant mass: " << inv_mass_red << std::endl;
	  tbW_red_->Fill(inv_mass_red);
	  all_red_->Fill(inv_mass_red);

	  inv_mass=sqrt( (p4_top1+p4_bottom2+p4_W3).Dot(p4_top1+p4_bottom2+p4_W3) );
	  //std::cout << "Invariant mass: " << inv_mass << std::endl;
	  tbW_->Fill(inv_mass);
	  all_->Fill(inv_mass);

	  Missing_energy_->Fill((Met)[0].et());
	  HT_->Fill(HT);
	  njets_->Fill(njets);

	  all_red_MET_->Fill(inv_mass_red, (Met)[0].et());
	  all_red_HT_->Fill(inv_mass_red, HT);
	  all_red_njets_->Fill(inv_mass_red, njets);

	  gluino=gluino+1;
	}
      if( top2==true && bottom1==true && W3==true)
	{
	  inv_mass_red=sqrt( (p4_top2_red+p4_bottom1+p4_W3_red).Dot(p4_top2_red+p4_bottom1+p4_W3_red) );
	  //std::cout << "Invariant mass: " << inv_mass_red << std::endl;
	  btW_red_->Fill(inv_mass_red);
	  all_red_->Fill(inv_mass_red);

	  inv_mass=sqrt( (p4_top2+p4_bottom1+p4_W3).Dot(p4_top2+p4_bottom1+p4_W3) );
	  //std::cout << "Invariant mass: " << inv_mass << std::endl;
	  btW_->Fill(inv_mass);
	  all_->Fill(inv_mass);

	  Missing_energy_->Fill((Met)[0].et());
	  HT_->Fill(HT);
	  njets_->Fill(njets);

	  all_red_MET_->Fill(inv_mass_red, (Met)[0].et());
	  all_red_HT_->Fill(inv_mass_red, HT);
	  all_red_njets_->Fill(inv_mass_red, njets);

	  gluino=gluino+1;
	}
      if( top1==true && bottom3==true && W2==true)
	{
	  inv_mass_red=sqrt( (p4_top1_red+p4_bottom3+p4_W2_red).Dot(p4_top1_red+p4_bottom3+p4_W2_red) );
	  //std::cout << "Invariant mass: " << inv_mass_red << std::endl;
	  tWb_red_->Fill(inv_mass_red);
	  all_red_->Fill(inv_mass_red);

	  inv_mass=sqrt( (p4_top1+p4_bottom3+p4_W2).Dot(p4_top1+p4_bottom3+p4_W2) );
	  //std::cout << "Invariant mass: " << inv_mass << std::endl;
	  tWb_->Fill(inv_mass);
	  all_->Fill(inv_mass);

	  Missing_energy_->Fill((Met)[0].et());
	  HT_->Fill(HT);
 	  njets_->Fill(njets);

	  all_red_MET_->Fill(inv_mass_red, (Met)[0].et());
	  all_red_HT_->Fill(inv_mass_red, HT);
	  all_red_njets_->Fill(inv_mass_red, njets);

	  gluino=gluino+1;
	}
      if( top3==true && bottom1==true && W2==true)
	{
	  inv_mass_red=sqrt( (p4_top3_red+p4_bottom1+p4_W2_red).Dot(p4_top3_red+p4_bottom1+p4_W2_red) );
	  //std::cout << "Invariant mass: " << inv_mass_red << std::endl;
	  bWt_red_->Fill(inv_mass_red);
	  all_red_->Fill(inv_mass_red);

	  inv_mass=sqrt( (p4_top3+p4_bottom1+p4_W2).Dot(p4_top3+p4_bottom1+p4_W2) );
	  //std::cout << "Invariant mass: " << inv_mass << std::endl;
	  bWt_->Fill(inv_mass);
	  all_->Fill(inv_mass);

	  Missing_energy_->Fill((Met)[0].et());
	  HT_->Fill(HT);
	  njets_->Fill(njets);

	  all_red_MET_->Fill(inv_mass_red, (Met)[0].et());
	  all_red_HT_->Fill(inv_mass_red, HT);
	  all_red_njets_->Fill(inv_mass_red, njets);

	  gluino=gluino+1;
	}
      if( top1==true && top2==true )
	{
	  inv_mass_red=sqrt( (p4_top1_red+p4_top2_red).Dot(p4_top1_red+p4_top2_red) );
	  //std::cout << "Invariant mass: " << inv_mass_red << std::endl;
	  tt_red_->Fill(inv_mass_red);
	  all_red_->Fill(inv_mass_red);

	  inv_mass=sqrt( (p4_top1+p4_top2).Dot(p4_top1+p4_top2) );
	  //std::cout << "Invariant mass: " << inv_mass << std::endl;
	  tt_->Fill(inv_mass);
	  all_->Fill(inv_mass);

	  Missing_energy_->Fill((Met)[0].et());
	  HT_->Fill(HT);
	  njets_->Fill(njets);

	  all_red_MET_->Fill(inv_mass_red, (Met)[0].et());
	  all_red_HT_->Fill(inv_mass_red, HT);
	  all_red_njets_->Fill(inv_mass_red, njets);

	  gluino=gluino+1;
	}
      if( bottom1==true && bottom2==true )
	{
	  inv_mass=sqrt( (p4_bottom1+p4_bottom2).Dot(p4_bottom1+p4_bottom2) );
	  //std::cout << "Invariant mass: " << inv_mass << std::endl;
	  bb_->Fill(inv_mass);
	  //all_->Fill(inv_mass);

	  //Missing_energy_->Fill((Met)[0].et());
	  //HT_->Fill(HT);
	  //njets_->Fill(njets);

	  //all_red_MET_->Fill(inv_mass_red, (Met)[0].et());
	  //all_red_HT_->Fill(inv_mass_red, HT);
	  //all_red_njets_->Fill(inv_mass_red, njets);

	  gluino=gluino+1;
	}
    }      
}


void SUSYEventAnalyzer::beginJob()
{  
} 

void SUSYEventAnalyzer::endJob()
{
}


DEFINE_FWK_MODULE(SUSYEventAnalyzer);
