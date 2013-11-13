#include <iostream>
#include <cmath>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <map>
#include <vector>

#include <TString.h>
#include <TH1.h>
#include<TH1I.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TString.h>
#include <Math/VectorUtil.h>
#include <TProfile.h>

#include "JetChargeAnalyzer.h"
#include "analysisStructs.h"
#include "JetCategories.h"
#include "higgsUtils.h"
#include "../../diLeptonic/src/analysisUtils.h"
#include "../../diLeptonic/src/analysisObjectStructs.h"
#include "../../diLeptonic/src/classes.h"



JetChargeAnalyzer::JetChargeAnalyzer(const std::vector<TString>& selectionStepsNoCategories,
				     const std::vector<TString>& stepsForCategories,
				     const JetCategories* jetCategories):
				     AnalysisHistogramsBase("jetCharge_", selectionStepsNoCategories, stepsForCategories, jetCategories)
				     {
					     std::cout<<"--- Beginning setting up jetChargeAnalyzer\n";
					     std::cout<<"=== Finishing setting up jetChargeAnalyzer\n\n";
				     }
				     
				     
				     
				     void JetChargeAnalyzer::bookHistos(const TString& step, std::map<TString, TH1*>& m_histogram)
				     {
					     TString name;
					     
					     //b-quark plots
					     
					     name = "chargeBquark";
					     m_histogram[name] = store(new TH2D(prefix_+name+step, "b-quark flavour to jet charge correlation;jet charge;b-quark flavour",10,-1.5,1.5,40,-30.,30.));
					     
					     name = "chargeTopBquark";
					     m_histogram[name] = store(new TH1D(prefix_+name+step,"Top b-quark to jet charge correlation;jet charge;Events",10,-1.5,1.5));
					     
					     name = "chargeTopAntiBquark";
					     m_histogram[name] = store(new TH1D(prefix_+name+step,"Top b-quark to jet charge correlation;jet charge;Events",10,-1.5,1.5));
					     
					     name = "chargeHiggsBquark";
					     m_histogram[name] = store(new TH1D(prefix_+name+step,"Higgs b-quark to jet charge correlation;jet charge;Events",10,-1.5,1.5));
					     
					     name = "chargeHiggsAntiBquark";
					     m_histogram[name] = store(new TH1D(prefix_+name+step,"Higgs b-quark to jet charge correlation;jet charge;Events",10,-1.5,1.5));
					     
					     //b-hadron plots
					     
					     name = "chargeBPlushadron";
					     m_histogram[name] = store(new TH1D(prefix_+name+step," B+ hadron to jet charge correlation;jet charge;Events",10,-1.5,1.5));
					     
					     name = "chargeBMinushadron";
					     m_histogram[name] = store(new TH1D(prefix_+name+step,"B- hadron to jet charge correlation;jet charge;Events",10,-1.5,1.5));
					     
					     name = "chargeBZerohadron";
					     m_histogram[name] = store(new TH1D(prefix_+name+step,"B0 hadron to jet charge correlation;jet charge;Events",10,-1.5,1.5));
					     
					     name = "chargeAntiBZerohadron";
					     m_histogram[name] = store(new TH1D(prefix_+name+step,"Anti-B0 hadron to jet charge correlation;jet charge;Events",10,-1.5,1.5));
					     
					     //track related plots
					     
					     name  = "multiplicityTracks";
					     m_histogram[name] = store(new TH1I(prefix_+name+step,"Multiplicity of the tracks in the jets;multiplicity;Events",30,0,30));
					     
					     name = "jetPTvsTracks";
					     m_histogram[name] = store(new TH2D(prefix_+name+step,"jet pT to track multiplicity correlation;track multiplicity;jet pT",30,0,30,40,0,300));
					     
					     name = "jetEtaVsTracks";
					     m_histogram[name] = store(new TH2D(prefix_+name+step,"jet eta to track multiplicity correlation;track multiplicity;jet eta",30,0,30,40,-3.0,3.0));
					     
					     name = "jetChargeVsMultip";
					     m_histogram[name] = store(new TH2D(prefix_+name+step,"jet charge value in function of the jet track amounts;",20,0,40,30, -1.5, 1.5));
					     
					     name = "highestPtTrack";
					     m_histogram[name] = store(new TH1D(prefix_+name+step,"pT value of the highest pT track of each jet;pT track;Events",30,0,80));
					     
					     //different eta and pt region studies
					     
					     name = "lowerPtRegion";
					     m_histogram[name] = store(new TH1D(prefix_+name+step,"jet charge value for jet pT<50GeV ;jet charge;Events",30,-1.5,1.5));
					     
					     name = "middlePtRegion";
					     m_histogram[name] = store(new TH1D(prefix_+name+step,"jet charge value for jet 50<=pT<150GeV ;jet charge;Events",30,-1.5,1.5));
					     
					     name = "highPtRegion";
					     m_histogram[name] = store(new TH1D(prefix_+name+step,"jet charge value for jet pT>=150GeV ;jet charge;Events",30,-1.5,1.5));
					     
					     //some control plots
					     name = "jetPt";
					     m_histogram[name] = store(new TH1I(prefix_+name+step,"jet Pt;jet pT;Events",40,0,200));
					     
					     name = "jetTrackPt";
					     m_histogram[name] = store(new TH1I(prefix_+name+step,"jet track Pt;Events",40,0,30));
					     
					     //charge validation plots
					     
					     name = "jetChargeValidation";
					     m_histogram[name] = store(new TH1I(prefix_+name+step,"Jet charge recalculation;jet charge;Events",40,-1.2,1.2));
					     
					     name = "jetCharge";
					     m_histogram[name] = store(new TH1I(prefix_+name+step,"Jet charge original calculation;jet charge;Events",40,-1.2,1.2));
					     
				     }
				     
				     
				     
				     void JetChargeAnalyzer::fillHistos(const RecoObjects& recoObjects, const CommonGenObjects& commonGenObjects,
									const TopGenObjects& topGenObjects, const HiggsGenObjects& higgsGenObjects,
					    const KinRecoObjects& kinRecoObjects,
					    const tth::RecoObjectIndices& recoObjectIndices, const tth::GenObjectIndices& genObjectIndices,
					    const tth::GenLevelWeights& genLevelWeights, const tth::RecoLevelWeights& recoLevelWeights,
					    const double& weight, const TString& step, std::map<TString, TH1*>& m_histogram)
				     {
					     TString name;
					     
					     // Number of selected jets and bjets
					     //const int numberOfJets = recoObjectIndices.jetIndices_.size();
					     //const int numberOfBjets = recoObjectIndices.bjetIndices_.size(); //b-tagged jets
					     
					     // Extracting input data to more comfortable variables
					     
					     const VLV& allJets = *recoObjects.jets_; 
					     const std::vector<int>& jetsId = recoObjectIndices.jetIndices_;           // Selected jets (point to jets from allJets)
					     VLV* allGenJets = commonGenObjects.allGenJets_;
					     const std::vector<int>& bHadJetIndex = (topGenObjects.valuesSet_) ? *topGenObjects.genBHadJetIndex_ : std::vector<int>(0);
					     const std::vector<int>& bHadFlavour = (topGenObjects.valuesSet_) ? *topGenObjects.genBHadFlavour_ : std::vector<int>(0);
					     //const std::vector<int>& bHadIndex = (topGenObjects.valuesSet_) ? *topGenObjects.genBHadIndex_ : std::vector<int>(0);
					     //const std::vector<LV>& bHadPlusMothers = (topGenObjects.valuesSet_) ? *topGenObjects.genBHadPlusMothers_ : std::vector<LV>(0);
					     const std::vector<int>& bHadPlusMothersPdgId = (topGenObjects.valuesSet_) ? *topGenObjects.genBHadPlusMothersPdgId_ : std::vector<int>(0);
					     const std::vector<double>& jetChargeRelativePtWeighted = *recoObjects.jetChargeRelativePtWeighted_;
					     const std::vector<int>& jetTrackCharge = *recoObjects.jetTrackCharge_;
					     const std::vector<int>& jetTrackIndex = *recoObjects.jetTrackIndex_;
					     const std::vector<LV>& jetTrack = *recoObjects.jetTrack_;
					     
					     // =============================================================Now do calculations and filling of histograms===================================================================
					     
					     //create a new jet selection-> 20GeV 
					     
					     constexpr double lowerJetPtCUT = 20.;
					     
					     // Get jet indices, apply selection cuts and order them by pt (beginning with the highest value)                                                                                                                
					     const VLV& lowerPtCUTjets = *recoObjects.jets_;                                                
					     std::vector<int> lowerPtCUTJetIdx = ttbar::initialiseIndices(lowerPtCUTjets);                        
					     ttbar::selectIndices(lowerPtCUTJetIdx, lowerPtCUTjets, ttbar::LVpt, lowerJetPtCUT);                
					     ttbar::orderIndices(lowerPtCUTJetIdx, lowerPtCUTjets, ttbar::LVpt);                  //pt ordered jets                

					     
					     //b-quark vs jet charge plot
					     
					     double minR = 999.;
					     std::vector<int> recoIndex;
					     std::vector<int> genIndex;
					     std::vector<int> flavour;
					     std::vector<int> hadFlav;
					     std::vector <double> charge;
					     std::vector<int> rep;
					     bool repeated = false;
					     
					     //track related plots
					     if (jetTrack.size()==0 || jetTrackIndex.size()==0 || jetTrackCharge.size()==0) return;
					     
					     
					     for(size_t i_jet=0;i_jet!=lowerPtCUTJetIdx.size();i_jet++)
					     {
// 						     int jetIdx = jetsId.at(i_jet);
						     int jetIdx = lowerPtCUTJetIdx.at(i_jet);
						     //std::cout<<"jets are = "<<jetIdx<<std::endl;
						     LV* jets = new LV();
						     *jets = allJets.at(jetIdx);
						     
						     double chargeJets = jetChargeRelativePtWeighted.at(jetIdx);
						     double ptJets = jets->pt();
						     double etaJets = jets->eta();
						     double jetPx = jets->px();
						     double jetPy = jets->py();
						     double jetPz = jets->pz();
						     
						     int multiplicity = 0;
						     if (jetTrack.size()!= jetTrackIndex.size()) std::cout<<"ERROR"<<std::endl;
						     
						     double sumMomentum = 0;
						     double sumMomentumQ = 0; 
						     
						     double maxPtTrack = -999;
						     for (size_t i_track=0; i_track!=jetTrack.size();i_track++)
						     {
							     //access the track-LV and puting some easy definitions to help.
							     LV* tracks = new LV();
							     *tracks = jetTrack.at(i_track);
							     int trackIdx = jetTrackIndex.at(i_track);
							     
							     //here we check if the track is matched to a selected jet and in case it is, add one to the multiplicity.
							     int matched = 0;
							     if (jetIdx!=trackIdx) matched = -1;
							     //std::cout<<"jetIdx = "<<jetIdx<<" and "<<"jetTrackIndex at i_track = "<<jetTrackIndex.at(i_track)<<std::endl;
							     if (matched == -1) continue;
							     //std::cout<<"tracks belong to the jet = "<<jetTrackIndex.at(i_track)<<std::endl;  
							     multiplicity++;
							
							     //here we calculate the jet charge in the same way it is done at ntuple level to cross-check the information 
							     //we obtain from the trees is the same obtained directly from the RECO objects
							     const double constituentPx = tracks->px();
							     const double constituentPy = tracks->py();
							     const double constituentPz = tracks->pz();
							     const double product = constituentPx*jetPx + constituentPy*jetPy + constituentPz*jetPz;
							     sumMomentum += product;
							     sumMomentumQ += jetTrackCharge.at(i_track)*product;
							    
							     //Here we access the pt of the tracks in order to select the highest pt track.
							     double ptTracks = tracks->pt();
							     if (ptTracks>maxPtTrack) maxPtTrack = ptTracks;
							     
							     //some track multiplicity plots
							     
							     m_histogram["jetTrackPt"]->Fill(ptTracks, weight);
						     } //end of track loop
							     
						     ((TH2D*)m_histogram["jetPTvsTracks"])-> Fill(multiplicity,ptJets,weight);
						     ((TH2D*)m_histogram["jetEtaVsTracks"])-> Fill(multiplicity,etaJets,weight);
						     
						     if (jetIdx==0) m_histogram["highestPtTrack"]->Fill(maxPtTrack, weight);
						     //std::cout<<"The multiplicity is = "<<multiplicity<<std::endl;
						     m_histogram["multiplicityTracks"]->Fill(multiplicity,weight);
						     ((TH2D*)m_histogram["jetChargeVsMultip"])->Fill(multiplicity,chargeJets,weight);
						     
						     const double jetChargeValidator(sumMomentum>0 ? sumMomentumQ/sumMomentum : 0);
						     m_histogram["jetChargeValidation"]->Fill(jetChargeValidator, weight);
						     m_histogram["jetCharge"]->Fill(chargeJets, weight);
						     
						     //std::cout<<"========================================"<<std::endl;
						     
						     //====================================================================================UNTIL HERE TRACKS ISSUES=======================================
						     //====================================================================================================================================================
						     //====================================================================================HERE B-QUARK-B-HADRON THINGS================================
						     
						     //====================================
						     //Division into different pt and eta regions
						     //====================================
						     
						     m_histogram["jetPt"]->Fill(ptJets, weight);
						     if (ptJets<50.) m_histogram["lowerPtRegion"]->Fill(chargeJets,weight);
						     else if (ptJets>=50.&&ptJets<150.) m_histogram["middlePtRegion"]->Fill(chargeJets,weight);
						     else if (ptJets>=150.) m_histogram["highPtRegion"]->Fill(chargeJets,weight);
						     
						     //=========================================
						     //b-quark-jet charge plot
						     //=========================================
						     
						     int recoJetIndex(-1);
						     int genJetIndex(-1);
						     bool isMatched = false;
						     
						     for (size_t i_gen=0;i_gen!=allGenJets->size();++i_gen)
							     //FIXME should I also require the eta and pt cuts in gen jets??
						     {
							     double deltaR=999.;
							     deltaR = ROOT::Math::VectorUtil::DeltaR(allJets.at(jetIdx),allGenJets->at(i_gen));
							     
							     //only take matched pairs
							     if (deltaR>0.2) continue;
							     if (deltaR==999.) std::cout<<"ERROR!!"<<std::endl;
							     
							     //choose smallest R
							     if (deltaR>minR) continue;
							     if (deltaR<minR) minR = deltaR;
							     
							     //grep the indices associated to the smallest R
							     genJetIndex = i_gen;
							     recoJetIndex = jetIdx;
							     
						     }//i_gen
						     
						     //avoid cases in which we have no smallest deltaR
						     if (genJetIndex==-1 || recoJetIndex==-1) continue;
						     
						     //find if the jet with the smallest R is associated to a hadron
						    
						     for (size_t i_had=0;i_had!=bHadJetIndex.size();++i_had)
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
						     charge.push_back(jetChargeRelativePtWeighted.at(jetIdx));
						     
						     
					     } //end loop over jets
						     
						     
						     
						     //avoid that the same jet is associated to two gen jets and viceversa
						     
						     for (size_t i_vec=0;i_vec!=genIndex.size();++i_vec)
						     {
							     for(size_t  j_vec=i_vec+1;j_vec!=genIndex.size();++j_vec)
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
						     
						     for (size_t i_fill=0;i_fill!=charge.size();++i_fill)
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
						     
						     