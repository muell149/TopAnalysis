#define AnalysisHistograms_cxx

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <iterator>

#include <TH1.h>
#include <TH1D.h>
#include <TString.h>
#include <TSelectorList.h>
#include <Math/VectorUtil.h>

#include "AnalysisHistograms.h"
#include "analysisStructs.h"
#include "JetCategories.h"
#include "higgsUtils.h"
#include "../../diLeptonic/src/analysisObjectStructs.h"
#include "../../diLeptonic/src/analysisUtils.h"
#include "../../diLeptonic/src/classes.h"





// --------------------------- Methods for AnalysisHistogramBase ---------------------------------------------



AnalysisHistogramsBase::AnalysisHistogramsBase(const TString& prefix,
                                               const std::vector<TString>& selectionStepsNoCategories,
                                               const std::vector<TString>& stepsForCategories,
                                               const JetCategories* jetCategories):
prefix_(prefix),
selectorList_(0),
selectionSteps_(selectionStepsNoCategories),
stepsForCategories_(stepsForCategories),
jetCategories_(jetCategories)
{
    if(!jetCategories_ && stepsForCategories_.size()>0){
        std::cerr<<"ERROR in constructor for AnalysisHistogramsBase! "
                 <<"No jet categories passed, but request for category-wise selection steps\n...break\n"<<std::endl;
        exit(234);
    }
    if(jetCategories_ && stepsForCategories_.size()==0){
        std::cerr<<"ERROR in constructor for AnalysisHistogramsBase! "
                 <<"Jet categories passed, but no category-wise selection steps defined\n...break\n"<<std::endl;
        exit(235);
    }
}



void AnalysisHistogramsBase::book(TSelectorList* output)
{
    // Set pointer to output, so that histograms are owned by it
    selectorList_ = output;
    
    // Book histograms for steps not separated in JetCategories
    for(const auto& stepShort : selectionSteps_){
        const TString step = tth::stepName(stepShort);
        this->addStep(step);
    }
    
    // Book histograms for steps exclusive in each JetCategory
    for(const auto& stepShort : stepsForCategories_){
        for(int category = 0; category<jetCategories_->numberOfCategories(); ++category){
            const TString step = tth::stepName(stepShort, category);
            this->addStep(step);
        }
    }
    
    // Book overview plot for each step divided in JetCategories
    for(const auto& stepShort : stepsForCategories_){
        const TString step = tth::stepName(stepShort) + "jetCategories";
        std::map<TString, TH1*>& m_histogram = m_stepHistograms_[step].m_histogram_;
        const int numberOfCategories(jetCategories_->numberOfCategories());
        TString name = "jetCategories";
        m_histogram[name] = this->store(new TH1D(prefix_+name+step, "Jet categories;# jets/b-jets; # events", numberOfCategories, 0, numberOfCategories));
        const std::vector<TString> v_binLabel(jetCategories_->binLabels());
        for(std::vector<TString>::const_iterator i_binLabel = v_binLabel.begin(); i_binLabel != v_binLabel.end(); ++i_binLabel){
            const TString binLabel(*i_binLabel);
            int position = std::distance(v_binLabel.begin(), i_binLabel) +1;
            m_histogram[name]->GetXaxis()->SetBinLabel(position, binLabel);
        }
    }
    
    // Cleanup
    selectorList_ = 0;
}



void AnalysisHistogramsBase::addStep(const TString& step)
{
    // Check whether step already exists
    if(this->checkExistence(step)){
        std::cout<<"Warning in addStep()! Selection step already contained: "<<step
                 <<"\n...skip this one\n";
        return;
    }

    // Book the histograms of the specific analyser
    std::map<TString, TH1*>& m_histogram = m_stepHistograms_[step].m_histogram_;
    this->bookHistos(step, m_histogram);
}



bool AnalysisHistogramsBase::checkExistence(const TString& step)const
{
    return m_stepHistograms_.find(step) != m_stepHistograms_.end();
}



void AnalysisHistogramsBase::bookHistos(const TString&, std::map<TString, TH1*>&)
{
    // WARNING: this is empty template method, overwrite for inherited histogram class
    
    std::cerr<<"ERROR! Dummy method bookHistos() in AnalysisHistogramBase is called, but overridden one should be used\n"
             <<"...break\n"<<std::endl;
    exit(567);
}



void AnalysisHistogramsBase::fill(const RecoObjects& recoObjects, const CommonGenObjects& commonGenObjects,
                                  const TopGenObjects& topGenObjects, const HiggsGenObjects& higgsGenObjects,
                                  const KinRecoObjects& kinRecoObjects,
                                  const tth::RecoObjectIndices& recoObjectIndices, const tth::GenObjectIndices& genObjectIndices,
                                  const tth::GenLevelWeights& genLevelWeights, const tth::RecoLevelWeights& recoLevelWeights,
                                  const double& weight, const TString& stepShort)
{
    // Number of selected jets and bjets
    const int numberOfJets = recoObjectIndices.jetIndices_.size();
    const int numberOfBjets = recoObjectIndices.bjetIndices_.size();
    
    // Set up step name and check if step exists
    const bool stepInCategory = stepShort.Contains("_cate");
    const TString step = stepInCategory ? stepShort : tth::stepName(stepShort);
    const bool stepExists(this->checkExistence(step));
    if(!stepInCategory && jetCategories_){
        const int categoryId = jetCategories_->categoryId(numberOfJets, numberOfBjets);
        
        // Fill the jetCategories histogram
        const TString stepForJetCategories = step + "jetCategories";
        if(this->checkExistence(stepForJetCategories)){
            std::map<TString, TH1*>& m_histogram = m_stepHistograms_[stepForJetCategories].m_histogram_;
            TString name = "jetCategories";
            m_histogram[name]->Fill(categoryId, weight);
        }
        
        // Here check the individual jet categories
        const TString fullStepName = tth::stepName(stepShort, categoryId);
        this->fill(recoObjects, commonGenObjects,
                   topGenObjects, higgsGenObjects,
                   kinRecoObjects,
                   recoObjectIndices, genObjectIndices,
                   genLevelWeights, recoLevelWeights,
                   weight, fullStepName);
    }
    if(!stepExists) return;
    
    // Fill the histograms of the specific analyser
    std::map<TString, TH1*>& m_histogram = m_stepHistograms_[step].m_histogram_;
    this->fillHistos(recoObjects, commonGenObjects,
                     topGenObjects, higgsGenObjects,
                     kinRecoObjects,
                     recoObjectIndices, genObjectIndices,
                     genLevelWeights, recoLevelWeights,
                     weight, step,
                     m_histogram);
}



void AnalysisHistogramsBase::fillHistos(const RecoObjects&, const CommonGenObjects&,
                                        const TopGenObjects&, const HiggsGenObjects&,
                                        const KinRecoObjects&,
                                        const tth::RecoObjectIndices&, const tth::GenObjectIndices&,
                                        const tth::GenLevelWeights&, const tth::RecoLevelWeights&,
                                        const double&, const TString&,
                                        std::map<TString, TH1*>&)
{
    // WARNING: this is empty template method, overwrite for inherited histogram class
    
    std::cerr<<"ERROR! Dummy method fillHistos() in AnalysisHistogramBase is called, but overridden one should be used\n"
             <<"...break\n"<<std::endl;
    exit(568);
}



void AnalysisHistogramsBase::clear()
{
    for(auto stepHistograms : m_stepHistograms_){
        stepHistograms.second.m_histogram_.clear();
    }
    m_stepHistograms_.clear();
    selectorList_ = 0;
}







// --------------------------- Methods for EventYieldHistograms ---------------------------------------------



EventYieldHistograms::EventYieldHistograms(const std::vector<TString>& selectionStepsNoCategories,
                                           const std::vector<TString>& stepsForCategories,
                                           const JetCategories* jetCategories):
AnalysisHistogramsBase("events_", selectionStepsNoCategories, stepsForCategories, jetCategories)
{
    std::cout<<"--- Beginning setting up event yield histograms\n";
    std::cout<<"=== Finishing setting up event yield histograms\n\n";
}



void EventYieldHistograms::bookHistos(const TString& step, std::map<TString, TH1*>& m_histogram)
{
    TString name;
    
    name = "weighted";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step,"event yield;;# events",8,0,8));
    m_histogram[name]->Sumw2();
}



void EventYieldHistograms::fillHistos(const RecoObjects&, const CommonGenObjects&,
                                      const TopGenObjects&, const HiggsGenObjects&,
                                      const KinRecoObjects&,
                                      const tth::RecoObjectIndices&, const tth::GenObjectIndices&,
                                      const tth::GenLevelWeights&, const tth::RecoLevelWeights&,
                                      const double& weight, const TString&,
                                      std::map<TString, TH1*>& m_histogram)
{
    TString name;
    
    name = "weighted";
    m_histogram[name]->Fill(1., weight);
}









// --------------------------- Methods for DyScalingHistograms ---------------------------------------------



DyScalingHistograms::DyScalingHistograms(const std::vector<TString>& selectionSteps, const TString& looseStep):
AnalysisHistogramsBase("", selectionSteps),
looseStep_(looseStep)
{
    std::cout<<"--- Beginning setting up Drell-Yan scaling histograms\n";
    if(std::find(selectionSteps_.begin(), selectionSteps_.end(), looseStep_) == selectionSteps_.end()){
        std::cerr<<"ERROR in constructor of DyScalingHistograms!"
                 <<"Could not find in selection steps the step specified for loose histogram: "<<looseStep_
                 <<"\n...break\n"<<std::endl;
        exit(987);
    }
    std::cout<<"=== Finishing setting up Drell-Yan scaling histograms\n\n";
}



void DyScalingHistograms::bookHistos(const TString& step, std::map<TString, TH1*>& m_histogram)
{
    const TString looseStep = tth::stepName(looseStep_) + "zWindow";
    if(step == looseStep){
        m_histogram["h_loose"] = this->bookHisto(m_histogram["h_loose"], "Looseh1");
    }
    
    if(step.Contains("zWindow")){
        m_histogram["h_zWindow"] = this->bookHisto(m_histogram["h_zWindow"], "Zh1"+step);
    }
    else{
        m_histogram["h_all"] = this->bookHisto(m_histogram["h_all"], "Allh1"+step);
        m_histogram["h_zVeto"] = this->bookHisto(m_histogram["h_zVeto"], "TTh1"+step);
        this->bookHistos(step + "zWindow", m_stepHistograms_[step + "zWindow"].m_histogram_);
    }
}



TH1* DyScalingHistograms::bookHisto(TH1* histo, const TString& name)
{
    histo = this->store(new TH1D(name,"Dilepton Mass; m_{ll}; events",40,0,400));
    return histo;
}



void DyScalingHistograms::fillHistos(const RecoObjects& recoObjects, const CommonGenObjects&,
                                     const TopGenObjects&, const HiggsGenObjects&,
                                     const KinRecoObjects&,
                                     const tth::RecoObjectIndices& recoObjectIndices, const tth::GenObjectIndices&,
                                     const tth::GenLevelWeights&, const tth::RecoLevelWeights&,
                                     const double& weight, const TString& step,
                                     std::map<TString, TH1*>& m_histogram)
{
    const int leadingLeptonIndex = recoObjectIndices.leadingLeptonIndex_;
    const int nLeadingLeptonIndex = recoObjectIndices.nLeadingLeptonIndex_;
    
    // FIXME: should use one common function in HiggsAnalysis and here
    //bool hasLeptonPair(false);
    if(leadingLeptonIndex!=-1 && nLeadingLeptonIndex!=-1){
        ;//hasLeptonPair = true;
    }
    else return;
    
    const LV dilepton = recoObjects.allLeptons_->at(leadingLeptonIndex) + recoObjects.allLeptons_->at(nLeadingLeptonIndex);
    const double dileptonMass = dilepton.M();
    const bool isZregion = dileptonMass>76. && dileptonMass<106.;
    
    
    // Fill histograms
    const TString looseStep = tth::stepName(looseStep_) + "zWindow";
    if(step == looseStep) m_stepHistograms_[looseStep].m_histogram_["h_loose"]->Fill(dileptonMass, weight);
    
    if(step.Contains("zWindow")){
        m_histogram["h_zWindow"]->Fill(dileptonMass, weight);
        TString stepNoZ(step);
        stepNoZ.ReplaceAll("zWindow", "");
        m_stepHistograms_[stepNoZ].m_histogram_["h_all"]->Fill(dileptonMass, weight);
    }
    else if(!isZregion){
        m_histogram["h_zVeto"]->Fill(dileptonMass, weight);
        m_histogram["h_all"]->Fill(dileptonMass, weight);
    }
}








// --------------------------- Methods for BasicHistograms ---------------------------------------------



BasicHistograms::BasicHistograms(const std::vector<TString>& selectionStepsNoCategories,
                                 const std::vector<TString>& stepsForCategories,
                                 const JetCategories* jetCategories):
AnalysisHistogramsBase("basic_", selectionStepsNoCategories, stepsForCategories, jetCategories)
{
    std::cout<<"--- Beginning setting up basic histograms\n";
    std::cout<<"=== Finishing setting up basic histograms\n\n";
}



void BasicHistograms::bookHistos(const TString& step, std::map<TString, TH1*>& m_histogram)
{
    TString name;
    
    // Leptons
    name = "lepton_multiplicity";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "Lepton multiplicity;N leptons;Events",10,0,10));
    name = "lepton_pt";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "Lepton p_{t};p_{t}^{l} [GeV];Leptons",50,0,250));
    name = "lepton_eta";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "Lepton #eta;#eta^{l};Leptons",50,-2.6,2.6));
    name = "lepton_phi";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "Lepton #phi;#phi^{l};Leptons",50,-3.2,3.2));
    
    // Leading lepton and antilepton
    name = "lepton1st_pt";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "1-st Lepton p_{t};p_{t}^{l_{1}} [GeV];Leptons",50,0,250));
    name = "lepton1st_eta";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "1-st Lepton #eta;#eta^{l_{1}};Leptons",50,-2.6,2.6));
    name = "lepton1st_phi";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "1-st Lepton #phi;#phi^{l_{1}};Leptons",50,-3.2,3.2));
    name = "lepton2nd_pt";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "2-nd Lepton p_{t};p_{t}^{l_{2}} [GeV];Leptons",50,0,250));
    name = "lepton2nd_eta";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "2-nd Lepton #eta;#eta^{l_{2}};Leptons",50,-2.6,2.6));
    name = "lepton2nd_phi";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "2-nd Lepton #phi;#phi^{l_{2}};Leptons",50,-3.2,3.2));

    // Dilepton
    name = "dilepton_mass";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "Dilepton mass;m^{l^{+}l^{-}} [GeV];Events",50,0,350));
    name = "dilepton_pt";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "Dilepton p_{t};p_{t}^{l^{+}l^{-}} [GeV];Events",50,0,300));
    name = "dilepton_rapidity";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "Dilepton rapidity;y^{l^{+}l^{-}};Events",50,-2.6,2.6));
    name = "dilepton_phi";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "Dilepton #phi;#phi^{l^{+}l^{-}};Events",50,-3.2,3.2));
    name = "dilepton_deltaEta";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "Dilepton #Delta#eta;#eta^{l^{+}}-#eta^{l^{-}};Events",50,-5,5));
    name = "dilepton_deltaPhi";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "Dilepton #Delta#phi;#phi^{l^{+}}-#phi^{l^{-}};Events",50,-3.2,3.2));

    // Jets
    name = "jet_multiplicity";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "Jet Multiplicity;N jets;Events",20,0,20));
    name = "jet_pt";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "Jet p_{t};p_{t}^{jet} [GeV];Jets",50,0,300));
    name = "jet_eta";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "Jet #eta;#eta^{jet};Jets",50,-2.6,2.6));
    name = "jet_phi";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "Jet #phi;#phi^{jet};Jets",50,-3.2,3.2));
    name = "jet_btagDiscriminator";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "b-tag Discriminator d;d;Jets",60,-0.1,1.1));
    name = "jet_chargeGlobalPtWeighted";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "jetChargeGlobalPtWeighted c_{glob}^{jet}; c_{glob}^{jet};# jets", 110, -1.1, 1.1));
    name = "jet_chargeRelativePtWeighted";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "jetChargeRelativePtWeighted c_{rel}^{jet}; c_{rel}^{jet};# jets", 110, -1.1, 1.1));
    
    // Bjets
    name = "bjet_multiplicity";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "B-Jet Multiplicity;N b-jets;Events",20,0,20));
    name = "bjet_pt";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "B-Jet p_{t};p_{t}^{b-jet} [GeV];B-Jets",50,0,300));
    name = "bjet_eta";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "B-Jet #eta;#eta^{b-jet};B-Jets",50,-2.6,2.6));
    name = "bjet_phi";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "B-Jet #phi;#phi^{b-jet};B-Jets",50,-3.2,3.2));

    // Met
    name = "met_et";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "Met E_{t};E_{t}^{met};Events",50,0,300));
    name = "met_phi";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "Met #phi;#phi^{met};Events",50,-3.2,3.2));
}



void BasicHistograms::fillHistos(const RecoObjects& recoObjects, const CommonGenObjects&,
                                 const TopGenObjects&, const HiggsGenObjects&,
                                 const KinRecoObjects&,
                                 const tth::RecoObjectIndices& recoObjectIndices, const tth::GenObjectIndices&,
                                 const tth::GenLevelWeights&, const tth::RecoLevelWeights&,
                                 const double& weight, const TString&,
                                 std::map< TString, TH1* >& m_histogram)
{
    // Leptons
    m_histogram["lepton_multiplicity"]->Fill(recoObjectIndices.allLeptonIndices_.size(), weight);
    for(const int index : recoObjectIndices.leptonIndices_){
        m_histogram["lepton_pt"]->Fill(recoObjects.allLeptons_->at(index).Pt(), weight);
        m_histogram["lepton_eta"]->Fill(recoObjects.allLeptons_->at(index).Eta(), weight);
        m_histogram["lepton_phi"]->Fill(recoObjects.allLeptons_->at(index).Phi(), weight);
    }
    for(const int index : recoObjectIndices.antiLeptonIndices_){
        m_histogram["lepton_pt"]->Fill(recoObjects.allLeptons_->at(index).Pt(), weight);
        m_histogram["lepton_eta"]->Fill(recoObjects.allLeptons_->at(index).Eta(), weight);
        m_histogram["lepton_phi"]->Fill(recoObjects.allLeptons_->at(index).Phi(), weight);
    }
    
    const int leptonIndex = recoObjectIndices.leptonIndices_.size()>0 ? recoObjectIndices.leptonIndices_.at(0) : -1;
    const int antiLeptonIndex = recoObjectIndices.antiLeptonIndices_.size()>0 ? recoObjectIndices.antiLeptonIndices_.at(0) : -1;
    const bool hasLeptonPair = (leptonIndex!=-1 && antiLeptonIndex!=-1);
    
    // Leading lepton and antilepton
    int leadingLeptonIndex(leptonIndex);
    int nLeadingLeptonIndex(antiLeptonIndex);
    if(hasLeptonPair){
        ttbar::orderIndices(leadingLeptonIndex, nLeadingLeptonIndex, *recoObjects.allLeptons_, ttbar::LVpt);
        
        m_histogram["lepton1st_pt"]->Fill(recoObjects.allLeptons_->at(leadingLeptonIndex).Pt(), weight);
        m_histogram["lepton1st_eta"]->Fill(recoObjects.allLeptons_->at(leadingLeptonIndex).Eta(), weight);
        m_histogram["lepton1st_phi"]->Fill(recoObjects.allLeptons_->at(leadingLeptonIndex).Phi(), weight);
        
        m_histogram["lepton2nd_pt"]->Fill(recoObjects.allLeptons_->at(nLeadingLeptonIndex).Pt(), weight);
        m_histogram["lepton2nd_eta"]->Fill(recoObjects.allLeptons_->at(nLeadingLeptonIndex).Eta(), weight);
        m_histogram["lepton2nd_phi"]->Fill(recoObjects.allLeptons_->at(nLeadingLeptonIndex).Phi(), weight);
    }
    
    
    // Dilepton
    if(hasLeptonPair){
        LV dilepton(0.,0.,0.,0.);
        dilepton = recoObjects.allLeptons_->at(leadingLeptonIndex) + recoObjects.allLeptons_->at(nLeadingLeptonIndex);
        
        m_histogram["dilepton_mass"]->Fill(dilepton.M(), weight);
        m_histogram["dilepton_pt"]->Fill(dilepton.Pt(), weight);
        m_histogram["dilepton_rapidity"]->Fill(dilepton.Rapidity(), weight);
        m_histogram["dilepton_phi"]->Fill(dilepton.Phi(), weight);

        m_histogram["dilepton_deltaEta"]->Fill(recoObjects.allLeptons_->at(leadingLeptonIndex).Eta() - recoObjects.allLeptons_->at(nLeadingLeptonIndex).Eta(), weight);
        m_histogram["dilepton_deltaPhi"]->Fill(ROOT::Math::VectorUtil::DeltaPhi(recoObjects.allLeptons_->at(leadingLeptonIndex), recoObjects.allLeptons_->at(nLeadingLeptonIndex)), weight);
    }


    // Jets
    m_histogram["jet_multiplicity"]->Fill(recoObjectIndices.jetIndices_.size(), weight);
    for(const int index : recoObjectIndices.jetIndices_){
        m_histogram["jet_pt"]->Fill(recoObjects.jets_->at(index).Pt(), weight);
        m_histogram["jet_eta"]->Fill(recoObjects.jets_->at(index).Eta(), weight);
        m_histogram["jet_phi"]->Fill(recoObjects.jets_->at(index).Phi(), weight);
        double btagDiscriminator = recoObjects.jetBTagCSV_->at(index);
        if(btagDiscriminator < -0.1) btagDiscriminator = -0.05;
        m_histogram["jet_btagDiscriminator"]->Fill(btagDiscriminator, weight);
        m_histogram["jet_chargeGlobalPtWeighted"]->Fill(recoObjects.jetChargeGlobalPtWeighted_->at(index), weight);
        m_histogram["jet_chargeRelativePtWeighted"]->Fill(recoObjects.jetChargeRelativePtWeighted_->at(index), weight);
    }
    
    
    // Bjets
     m_histogram["bjet_multiplicity"]->Fill(recoObjectIndices.bjetIndices_.size(), weight);
    for(const int index : recoObjectIndices.bjetIndices_){
        m_histogram["bjet_pt"]->Fill(recoObjects.jets_->at(index).Pt(), weight);
        m_histogram["bjet_eta"]->Fill(recoObjects.jets_->at(index).Eta(), weight);
        m_histogram["bjet_phi"]->Fill(recoObjects.jets_->at(index).Phi(), weight);
    }
    
    
    // Met
    m_histogram["met_et"]->Fill(recoObjects.met_->E(), weight);
    m_histogram["met_phi"]->Fill(recoObjects.met_->Phi(), weight);
}








