#define AnalysisHistograms_cxx

#include <iostream>
#include <algorithm>

#include <TH1.h>
#include <TH1D.h>
#include <TString.h>
#include <TSelectorList.h>
#include <Math/VectorUtil.h>

#include "AnalysisHistograms.h"
#include "analysisStructs.h"
#include "../../diLeptonic/src/analysisObjectStructs.h"
#include "../../diLeptonic/src/analysisUtils.h"
#include "../../diLeptonic/src/classes.h"





// --------------------------- Methods for AnalysisHistogramBase ---------------------------------------------



AnalysisHistogramsBase::AnalysisHistogramsBase(const std::vector<TString>& selectionSteps):
selectorList_(0),
selectionSteps_(selectionSteps)
{}



void AnalysisHistogramsBase::book(TSelectorList* output)
{
    for(const auto& step : selectionSteps_){
        this->addStep(step, output);
    }
}



void AnalysisHistogramsBase::addStep(const TString& step, TSelectorList* output)
{
    // Set pointer to output, so that histograms are owned by it
    selectorList_ = output;

    // Check whether step already exists
    if(this->checkExistence(step)){
        std::cout<<"Warning in addStep()! Selection step already contained: "<<step
                 <<"\n...skip this one\n";
        return;
    }

    // Book the histograms and cleanup
    this->bookHistos(step);
    selectorList_ = 0;
}



bool AnalysisHistogramsBase::checkExistence(const TString& step)const
{
    return m_stepHistograms_.find(step) != m_stepHistograms_.end();
}



void AnalysisHistogramsBase::bookHistos(const TString&)
{
    // WARNING: this is empty template method, overwrite for inherited histogram class
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



EventYieldHistograms::EventYieldHistograms(const std::vector<TString>& selectionSteps):
AnalysisHistogramsBase(selectionSteps)
{
    std::cout<<"--- Beginning setting up event yield histograms\n";
    std::cout<<"=== Finishing setting up event yield histograms\n\n";
}


void EventYieldHistograms::bookHistos(const TString& step)
{
    std::map<TString, TH1*>& m_histogram = m_stepHistograms_[step].m_histogram_;
    
    m_histogram["events"] = this->store(new TH1D("events_step"+step,"event count (no weight);;# events",8,0,8));
    m_histogram["events"]->Sumw2();
}



void EventYieldHistograms::fill(const double& weight, const TString& step)
{
    // Check if step exists
    const bool stepExists(this->checkExistence(step));
    if(!stepExists){
        return;
        //std::cerr<<"Error in fill() of EventYieldHistograms! The following step is not defined: "
        //         <<step<<"\n...exiting\n";
        //exit(25);
    }
    
    m_stepHistograms_[step].m_histogram_["events"]->Fill(1., weight);
}









// --------------------------- Methods for DyScalingHistograms ---------------------------------------------



DyScalingHistograms::DyScalingHistograms(const std::vector<TString>& selectionSteps, const TString& looseStep):
AnalysisHistogramsBase(selectionSteps),
looseStep_(looseStep)
{
    std::cout<<"--- Beginning setting up Drell-Yan scaling histograms\n";
    if(std::find(selectionSteps_.begin(), selectionSteps_.end(), looseStep_) == selectionSteps_.end()){
        std::cerr<<"ERROR in constructor of DyScalingHistograms!"
                 <<"Could not find in selection steps the step specified for loose histogram: "<<looseStep_
                 <<"\n...break\n"<<std::endl;
    }
    std::cout<<"=== Finishing setting up Drell-Yan scaling histograms\n\n";
}



void DyScalingHistograms::bookHistos(const TString& step)
{
    std::map<TString, TH1*>& m_histogram = m_stepHistograms_[step].m_histogram_;
    
    if(step == looseStep_+"zWindow"){
        m_histogram["h_loose"] = this->bookHisto(m_histogram["h_loose"], "Looseh1");
    }
    
    if(step.Contains("zWindow")){
        m_histogram["h_zWindow"] = this->bookHisto(m_histogram["h_zWindow"], "Zh1_step" + step);
    }
    else{
        m_histogram["h_all"] = this->bookHisto(m_histogram["h_all"], "Allh1_step" + step);
        m_histogram["h_zVeto"] = this->bookHisto(m_histogram["h_zVeto"], "TTh1_step" + step);
        this->bookHistos(step + "zWindow");
    }
}



TH1* DyScalingHistograms::bookHisto(TH1* histo, const TString& name)
{
    histo = this->store(new TH1D(name,"Dilepton Mass; m_{ll}; events",40,0,400));
    return histo;
}



void DyScalingHistograms::fill(const RecoObjects& recoObjects, const tth::RecoObjectIndices& recoObjectIndices,
                               const double& weight, const TString& step)
{
    // Check if step exists
    const bool stepExists(this->checkExistence(step));
    if(!stepExists){
        return;
        //std::cerr<<"Error in fillZWindow() of DyScalingHistograms! The following step is not defined: "
        //         <<step<<"\n...exiting\n";
        //exit(22);
    }
    
    const int leadingLeptonIndex = recoObjectIndices.leadingLeptonIndex_;
    const int nLeadingLeptonIndex = recoObjectIndices.nLeadingLeptonIndex_;
    
    // FIXME: should use one common function in HiggsAnalysis and here
    bool hasLeptonPair(false);
    if(leadingLeptonIndex!=-1 && nLeadingLeptonIndex!=-1){
        hasLeptonPair = true;
    }
    else return;
    
    const LV dilepton = recoObjects.allLeptons_->at(leadingLeptonIndex) + recoObjects.allLeptons_->at(nLeadingLeptonIndex);
    const double dileptonMass = dilepton.M();
    const bool isZregion = dileptonMass > 76 && dileptonMass < 106;
    
    
    // Fill histograms
    if(step == looseStep_+"zWindow") m_stepHistograms_[looseStep_+"zWindow"].m_histogram_["h_loose"]->Fill(dileptonMass, weight);
    
    if(step.Contains("zWindow")){
        m_stepHistograms_[step].m_histogram_["h_zWindow"]->Fill(dileptonMass, weight);
        TString stepNoZ(step);
        stepNoZ.ReplaceAll("zWindow", "");
        m_stepHistograms_[stepNoZ].m_histogram_["h_all"]->Fill(dileptonMass, weight);
    }
    else if(!isZregion){
        m_stepHistograms_[step].m_histogram_["h_zVeto"]->Fill(dileptonMass, weight);
        m_stepHistograms_[step].m_histogram_["h_all"]->Fill(dileptonMass, weight);
    }
}








// --------------------------- Methods for BasicHistograms ---------------------------------------------



BasicHistograms::BasicHistograms(const std::vector<TString>& selectionSteps):
AnalysisHistogramsBase(selectionSteps)
{
    std::cout<<"--- Beginning setting up basic histograms\n";
    std::cout<<"=== Finishing setting up basic histograms\n\n";
}



void BasicHistograms::bookHistos(const TString& step)
{
    std::map<TString, TH1*>& m_histogram = m_stepHistograms_[step].m_histogram_;
    TString name;

    // Leptons
    name = "basicLepton_multiplicity";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Lepton multiplicity;N leptons;Events",10,0,10));
    name = "basicLepton_pt";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Lepton p_{t};p_{t}^{l} [GeV];Leptons",50,0,250));
    name = "basicLepton_eta";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Lepton #eta;#eta^{l};Leptons",50,-2.6,2.6));
    name = "basicLepton_phi";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Lepton #phi;#phi^{l};Leptons",50,-3.2,3.2));
    
    // Leading lepton and antilepton
    name = "basicLepton1st_pt";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "1-st Lepton p_{t};p_{t}^{l_{1}} [GeV];Leptons",50,0,250));
    name = "basicLepton1st_eta";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "1-st Lepton #eta;#eta^{l_{1}};Leptons",50,-2.6,2.6));
    name = "basicLepton1st_phi";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "1-st Lepton #phi;#phi^{l_{1}};Leptons",50,-3.2,3.2));
    name = "basicLepton2nd_pt";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "2-nd Lepton p_{t};p_{t}^{l_{2}} [GeV];Leptons",50,0,250));
    name = "basicLepton2nd_eta";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "2-nd Lepton #eta;#eta^{l_{2}};Leptons",50,-2.6,2.6));
    name = "basicLepton2nd_phi";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "2-nd Lepton #phi;#phi^{l_{2}};Leptons",50,-3.2,3.2));

    // Dilepton
    name = "basicDilepton_mass";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Dilepton mass;m^{l^{+}l^{-}} [GeV];Events",50,0,350));
    name = "basicDilepton_pt";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Dilepton p_{t};p_{t}^{l^{+}l^{-}} [GeV];Events",50,0,300));
    name = "basicDilepton_rapidity";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Dilepton rapidity;y^{l^{+}l^{-}};Events",50,-2.6,2.6));
    name = "basicDilepton_phi";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Dilepton #phi;#phi^{l^{+}l^{-}};Events",50,-3.2,3.2));
    name = "basicDilepton_deltaEta";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Dilepton #Delta#eta;#eta^{l^{+}}-#eta^{l^{-}};Events",50,-5,5));
    name = "basicDilepton_deltaPhi";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Dilepton #Delta#phi;#phi^{l^{+}}-#phi^{l^{-}};Events",50,-3.2,3.2));

    // Jets
    name = "basicJet_multiplicity";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Jet Multiplicity;N jets;Events",20,0,20));
    name = "basicJet_pt";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Jet p_{t};p_{t}^{jet} [GeV];Jets",50,0,300));
    name = "basicJet_eta";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Jet #eta;#eta^{jet};Jets",50,-2.6,2.6));
    name = "basicJet_phi";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Jet #phi;#phi^{jet};Jets",50,-3.2,3.2));
    name = "basicJet_btagDiscriminator";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "b-tag Discriminator d;d;Jets",60,-0.1,1.1));
    
    // Bjets
    name = "basicBjet_multiplicity";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "B-Jet Multiplicity;N b-jets;Events",20,0,20));
    name = "basicBjet_pt";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "B-Jet p_{t};p_{t}^{b-jet} [GeV];B-Jets",50,0,300));
    name = "basicBjet_eta";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "B-Jet #eta;#eta^{b-jet};B-Jets",50,-2.6,2.6));
    name = "basicBjet_phi";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "B-Jet #phi;#phi^{b-jet};B-Jets",50,-3.2,3.2));

    // Met
    name = "basicMet_et";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Met E_{t};E_{t}^{met};Events",50,0,300));
    name = "basicMet_phi";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Met #phi;#phi^{met};Events",50,-3.2,3.2));
}



void BasicHistograms::fill(const RecoObjects& recoObjects, const tth::RecoObjectIndices& recoObjectIndices,
                           const double& weight, const TString& step)
{
    // Check if step exists
    const bool stepExists(this->checkExistence(step));
    if(!stepExists){
        return;
        //std::cerr<<"Error in fill() of BasicHistograms! The following step is not defined: "
        //         <<step<<"\n...exiting\n";
        //exit(24);
    }
    
    
    // Leptons
    m_stepHistograms_[step].m_histogram_["basicLepton_multiplicity"]->Fill(recoObjects.allLeptons_->size(), weight);
    for(const int index : recoObjectIndices.leptonIndices_){
        m_stepHistograms_[step].m_histogram_["basicLepton_pt"]->Fill(recoObjects.allLeptons_->at(index).Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicLepton_eta"]->Fill(recoObjects.allLeptons_->at(index).Eta(), weight);
        m_stepHistograms_[step].m_histogram_["basicLepton_phi"]->Fill(recoObjects.allLeptons_->at(index).Phi(), weight);
    }
    for(const int index : recoObjectIndices.antiLeptonIndices_){
        m_stepHistograms_[step].m_histogram_["basicLepton_pt"]->Fill(recoObjects.allLeptons_->at(index).Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicLepton_eta"]->Fill(recoObjects.allLeptons_->at(index).Eta(), weight);
        m_stepHistograms_[step].m_histogram_["basicLepton_phi"]->Fill(recoObjects.allLeptons_->at(index).Phi(), weight);
    }
    
    const int leptonIndex = recoObjectIndices.leptonIndices_.size()>0 ? recoObjectIndices.leptonIndices_.at(0) : -1;
    const int antiLeptonIndex = recoObjectIndices.antiLeptonIndices_.size()>0 ? recoObjectIndices.antiLeptonIndices_.at(0) : -1;
    const bool hasLeptonPair = (leptonIndex!=-1 && antiLeptonIndex!=-1);
    
    // Leading lepton and antilepton
    int leadingLeptonIndex(leptonIndex);
    int nLeadingLeptonIndex(antiLeptonIndex);
    if(hasLeptonPair){
        ttbar::orderIndices(leadingLeptonIndex, nLeadingLeptonIndex, *recoObjects.allLeptons_, ttbar::LVpt);
        
        m_stepHistograms_[step].m_histogram_["basicLepton1st_pt"]->Fill(recoObjects.allLeptons_->at(leadingLeptonIndex).Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicLepton1st_eta"]->Fill(recoObjects.allLeptons_->at(leadingLeptonIndex).Eta(), weight);
        m_stepHistograms_[step].m_histogram_["basicLepton1st_phi"]->Fill(recoObjects.allLeptons_->at(leadingLeptonIndex).Phi(), weight);
        
        m_stepHistograms_[step].m_histogram_["basicLepton2nd_pt"]->Fill(recoObjects.allLeptons_->at(nLeadingLeptonIndex).Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicLepton2nd_eta"]->Fill(recoObjects.allLeptons_->at(nLeadingLeptonIndex).Eta(), weight);
        m_stepHistograms_[step].m_histogram_["basicLepton2nd_phi"]->Fill(recoObjects.allLeptons_->at(nLeadingLeptonIndex).Phi(), weight);
    }
    
    
    // Dilepton
    if(hasLeptonPair){
        LV dilepton(0.,0.,0.,0.);
        dilepton = recoObjects.allLeptons_->at(leadingLeptonIndex) + recoObjects.allLeptons_->at(nLeadingLeptonIndex);
        
        m_stepHistograms_[step].m_histogram_["basicDilepton_mass"]->Fill(dilepton.M(), weight);
        m_stepHistograms_[step].m_histogram_["basicDilepton_pt"]->Fill(dilepton.Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicDilepton_rapidity"]->Fill(dilepton.Rapidity(), weight);
        m_stepHistograms_[step].m_histogram_["basicDilepton_phi"]->Fill(dilepton.Phi(), weight);

        m_stepHistograms_[step].m_histogram_["basicDilepton_deltaEta"]->Fill(recoObjects.allLeptons_->at(leadingLeptonIndex).Eta() - recoObjects.allLeptons_->at(nLeadingLeptonIndex).Eta(), weight);
        m_stepHistograms_[step].m_histogram_["basicDilepton_deltaPhi"]->Fill(ROOT::Math::VectorUtil::DeltaPhi(recoObjects.allLeptons_->at(leadingLeptonIndex), recoObjects.allLeptons_->at(nLeadingLeptonIndex)), weight);
    }


    // Jets
    m_stepHistograms_[step].m_histogram_["basicJet_multiplicity"]->Fill(recoObjectIndices.jetIndices_.size(), weight);
    for(const int index : recoObjectIndices.jetIndices_){
        m_stepHistograms_[step].m_histogram_["basicJet_pt"]->Fill(recoObjects.jets_->at(index).Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicJet_eta"]->Fill(recoObjects.jets_->at(index).Eta(), weight);
        m_stepHistograms_[step].m_histogram_["basicJet_phi"]->Fill(recoObjects.jets_->at(index).Phi(), weight);
        m_stepHistograms_[step].m_histogram_["basicJet_btagDiscriminator"]->Fill(recoObjects.jetBTagCSV_->at(index), weight);
    }
    
    
    // Bjets
     m_stepHistograms_[step].m_histogram_["basicBjet_multiplicity"]->Fill(recoObjectIndices.bjetIndices_.size(), weight);
    for(const int index : recoObjectIndices.bjetIndices_){
        m_stepHistograms_[step].m_histogram_["basicBjet_pt"]->Fill(recoObjects.jets_->at(index).Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicBjet_eta"]->Fill(recoObjects.jets_->at(index).Eta(), weight);
        m_stepHistograms_[step].m_histogram_["basicBjet_phi"]->Fill(recoObjects.jets_->at(index).Phi(), weight);
    }
    
    
    // Met
    m_stepHistograms_[step].m_histogram_["basicMet_et"]->Fill(recoObjects.met_->E(), weight);
    m_stepHistograms_[step].m_histogram_["basicMet_phi"]->Fill(recoObjects.met_->Phi(), weight);
}








