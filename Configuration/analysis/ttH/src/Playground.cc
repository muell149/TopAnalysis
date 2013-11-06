#include <iostream>
#include <cmath>
#include <cstdlib>
#include <utility>
#include <algorithm>

#include <TString.h>
#include <TH1.h>
#include<TH1I.h>
#include <TH1D.h>
#include <TH2D.h>
#include <Math/VectorUtil.h>
#include <TProfile.h>

#include "Playground.h"
#include "analysisStructs.h"
#include "JetCategories.h"
#include "higgsUtils.h"
#include "../../diLeptonic/src/analysisUtils.h"
#include "../../diLeptonic/src/analysisObjectStructs.h"
#include "../../diLeptonic/src/classes.h"

// #include "multiplicityTracks.cc"
// #include "isMatched.cc"



Playground::Playground(const std::vector<TString>& selectionStepsNoCategories,
                       const std::vector<TString>& stepsForCategories,
                       const JetCategories* jetCategories):
AnalysisHistogramsBase("test_", selectionStepsNoCategories, stepsForCategories, jetCategories)
{
    std::cout<<"--- Beginning setting up playground\n";
    std::cout<<"=== Finishing setting up playground\n\n";
}



void Playground::bookHistos(const TString& step, std::map<TString, TH1*>& m_histogram)
{
    TString name;
    
    //b-quark plots
    
    name = "chargeBquark";
    m_histogram[name] = store(new TH2D(prefix_+name+step, "b-quark flavour to jet charge correlation;jet charge;b-quark flavour",40,-1.5,1.5,40,-30.,30.));
    
    name = "chargeTopBquark";
    m_histogram[name] = store(new TH1D(prefix_+name+step,"Top b-quark to jet charge correlation;jet charge;Events",40,-1.5,1.5));
    
    name = "chargeTopAntiBquark";
    m_histogram[name] = store(new TH1D(prefix_+name+step,"Top b-quark to jet charge correlation;jet charge;Events",40,-1.5,1.5));
    
    name = "chargeHiggsBquark";
    m_histogram[name] = store(new TH1D(prefix_+name+step,"Top b-quark to jet charge correlation;jet charge;Events",40,-1.5,1.5));
    
    name = "chargeHiggsAntiBquark";
    m_histogram[name] = store(new TH1D(prefix_+name+step,"Top b-quark to jet charge correlation;jet charge;Events",40,-1.5,1.5));
    
    //b-hadron plots
    
    name = "chargeBPlushadron";
    m_histogram[name] = store(new TH1D(prefix_+name+step," B+ hadron to jet charge correlation;jet charge;Events",40,-1.5,1.5));
    
    name = "chargeBMinushadron";
    m_histogram[name] = store(new TH1D(prefix_+name+step,"B- hadron to jet charge correlation;jet charge;Events",40,-1.5,1.5));
    
    name = "chargeBZerohadron";
    m_histogram[name] = store(new TH1D(prefix_+name+step,"B0 hadron to jet charge correlation;jet charge;Events",40,-1.5,1.5));
    
    name = "chargeAntiBZerohadron";
    m_histogram[name] = store(new TH1D(prefix_+name+step,"Anti-B0 hadron to jet charge correlation;jet charge;Events",40,-1.5,1.5));
    
    //tracking plots
    
    name  = "multiplicityTracks";
    m_histogram[name] = store(new TH1I(prefix_+name+step,"Multiplicity of the tracks in the jets;multiplicity;Events",26,0,26));
    			      
    name = "jetPTvsTracks";
    m_histogram[name] = store(new TH2D(prefix_+name+step,"jet pT to track multiplicity correlation;track multiplicity;jet pT",40,0,30,40,0,200));
}



void Playground::fillHistos(const RecoObjects& recoObjects, const CommonGenObjects& commonGenObjects,
                            const TopGenObjects& topGenObjects, const HiggsGenObjects& higgsGenObjects,
                            const KinRecoObjects& kinRecoObjects,
                            const tth::RecoObjectIndices& recoObjectIndices, const tth::GenObjectIndices& genObjectIndices,
                            const tth::GenLevelWeights& genLevelWeights, const tth::RecoLevelWeights& recoLevelWeights,
                            const double& weight, const TString& step, std::map<TString, TH1*>& m_histogram)
{
    TString name;
    
    // Number of selected jets and bjets
    const int numberOfJets = recoObjectIndices.jetIndices_.size();
    const int numberOfBjets = recoObjectIndices.bjetIndices_.size(); //b-tagged jets
    
    // Extracting input data to more comfortable variables
    
    const VLV& allJets = *recoObjects.jets_; 
    VLV* allGenJets = commonGenObjects.allGenJets_;
    const std::vector<int>& bHadJetIndex = (topGenObjects.valuesSet_) ? *topGenObjects.genBHadJetIndex_ : std::vector<int>(0);
    const std::vector<int>& bHadFlavour = (topGenObjects.valuesSet_) ? *topGenObjects.genBHadFlavour_ : std::vector<int>(0);
    const std::vector<int>& bHadIndex = (topGenObjects.valuesSet_) ? *topGenObjects.genBHadIndex_ : std::vector<int>(0);
    const std::vector<LV>& bHadPlusMothers = (topGenObjects.valuesSet_) ? *topGenObjects.genBHadPlusMothers_ : std::vector<LV>(0);
    const std::vector<int>& bHadPlusMothersPdgId = (topGenObjects.valuesSet_) ? *topGenObjects.genBHadPlusMothersPdgId_ : std::vector<int>(0);
    const std::vector<double>& jetChargeRelativePtWeighted = *recoObjects.jetChargeRelativePtWeighted_;
//     if(!recoObjects.jetTrack_ || !recoObjects.jetTrackIndex_ || !recoObjects.jetTrackCharge_) return;
//     const std::vector<int>& jetTrackCharge = *recoObjects.jetTrackCharge_;
//     const std::vector<int>& jetTrackIndex = *recoObjects.jetTrackIndex_;
//     const std::vector<LV>& jetTrack = *recoObjects.jetTrack_;
    
    // =============================================================Now do calculations and filling of histograms===================================================================
    
    //b-quark vs jet charge plot
    
    double minR = 999.;
    std::vector<int> recoIndex;
    std::vector<int> genIndex;
    std::vector<int> flavour;
    std::vector<int> hadFlav;
    std::vector <double> charge;
    std::vector<int> rep;
    bool repeated = false;

    //track multiplicity plot   
//     if (jetTrack.size()==0 || jetTrackIndex.size()==0 || jetTrackCharge.size()==0) return;
//   
//    for(unsigned int i_jet=0;i_jet!=allJets.size();i_jet++)
//    {
// 	   LV* jets = new LV();
// 	   *jets = allJets.at(i_jet);
// 	   int multiplicity = multiplicityTracks(i_jet,jetTrackIndex);
// 	   m_histogram["multiplicityTracks"]->Fill(multiplicity,weight);
// 	   if (jetTrack.size()!= jetTrackIndex.size()) std::cout<<"ERROR"<<std::endl;
// 	   for (int i_track=0; i_track!=jetTrack.size();i_track++)
// 	   {
// 		 LV* tracks = new LV();
// 		 *tracks = jetTrack.at(i_track);  
// 		 bool matched = isMatched(i_jet,i_track);
// 		 if (isMatched == false) continue;
// 		 double ptJets = jets->pt();
// 		 ((TH2D*)m_histogram["jetPTvsTracks"])-> Fill(multiplicity,ptJets,weight);
// 	   }
//    }
//    std::cout<<"========================================"<<std::endl;

    
	    
    //b-quark-jet charge plot
    
    for (unsigned int i_reco=0;i_reco!=allJets.size();++i_reco)    
    {
		    int recoJetIndex(-1);
		    int genJetIndex(-1);
		    bool isMatched = false;
		    
		    for (unsigned int i_gen=0;i_gen!=allGenJets->size();++i_gen)
		    {
			    double deltaR=999.;
			    deltaR = ROOT::Math::VectorUtil::DeltaR(allJets.at(i_reco),allGenJets->at(i_gen));
			    
			    //only take matched pairs
			    if (deltaR>0.2) continue;
			    if (deltaR==999.) std::cout<<"ERROR!!"<<std::endl;
			    
			    //choose smallest R
			    if (deltaR>minR) continue;
			    if (deltaR<minR) minR = deltaR;
			    
			    //grep the indices associated to the smallest R
			    genJetIndex = i_gen;
			    recoJetIndex = i_reco;
			    
		    }//i_gen
		    
		    //avoid cases in which we have no smallest deltaR
		    if (genJetIndex==-1 || recoJetIndex==-1) continue;
		    
		    //find if the jet with the smallest R is associated to a hadron
		    for (unsigned int i_had=0;i_had!=bHadJetIndex.size();++i_had)
		    {
			    if (genJetIndex!=bHadJetIndex.at(i_had)) continue;
			    flavour.push_back(bHadFlavour.at(i_had));
			    hadFlav.push_back(bHadPlusMothersPdgId.at(i_had));
			    isMatched=true;
		    }
		    //if the jet is not matched to a hadron, we continue
		    if (isMatched==false) continue;
		    genIndex.push_back(genJetIndex);
		    recoIndex.push_back(recoJetIndex);
		    charge.push_back(jetChargeRelativePtWeighted.at(i_reco));
    }//i_reco
    
    //avoid that the same jet is associated to two gen jets and viceversa
    
    for (unsigned int i_vec=0;i_vec!=genIndex.size();++i_vec)
    {
	    for(int  j_vec=i_vec+1;j_vec!=genIndex.size();++j_vec)
	    {
		    if (genIndex.at(i_vec) == genIndex.at(j_vec)) repeated=true;
		    if (repeated==true)
		    {
			    rep.push_back(j_vec);
		    }
	    }
    }
    
    if (repeated==true) std::cout<<"size of the repetition = "<<rep.size()<<std::endl;
    
    //We fill the histograms here
    
    for (unsigned int i_fill=0;i_fill!=charge.size();++i_fill)
    {
	    if (repeated==true) continue;
	    ((TH2D*)m_histogram["chargeBquark"])->Fill(charge.at(i_fill),flavour.at(i_fill), weight);
	    
	    if (flavour.at(i_fill) == 6)  m_histogram["chargeTopBquark"]->Fill(charge.at(i_fill),weight);
	    else if (flavour.at(i_fill) == -6) m_histogram["chargeTopAntiBquark"]->Fill(charge.at(i_fill),weight);
	    else if (flavour.at(i_fill) == 25) m_histogram["chargeHiggsBquark"]->Fill(charge.at(i_fill),weight);
	    else if (flavour.at(i_fill) == -25) m_histogram["chargeHiggsAntiBquark"]->Fill(charge.at(i_fill),weight);
	    
	    if (hadFlav.at(i_fill) == 511) m_histogram["chargeBPlushadron"]->Fill(charge.at(i_fill),weight);
	    else if (hadFlav.at(i_fill) == -511) m_histogram["chargeBMinushadron"]->Fill(charge.at(i_fill),weight);
	    else if (hadFlav.at(i_fill) == 521) m_histogram["chargeBZerohadron"]->Fill(charge.at(i_fill),weight);
	    else if (hadFlav.at(i_fill) == -521) m_histogram["chargeAntiBZerohadron"]->Fill(charge.at(i_fill),weight);
    }
    
}






