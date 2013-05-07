#define AnalysisHistograms_cxx

#include <iostream>

#include <TH1.h>
#include <TH1D.h>
#include <TString.h>
#include <TSelectorList.h>
#include <Math/VectorUtil.h>

#include "AnalysisHistograms.h"
#include "../../diLeptonic/src/analysisUtils.h"
#include "../../diLeptonic/src/classes.h"





// --------------------------- Methods for AnalysisHistogramBase ---------------------------------------------



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








// --------------------------- Methods for DyScalingHistograms ---------------------------------------------



void DyScalingHistograms::bookHistos(const TString& step)
{
    if(!m_stepHistograms_.size()){
        h_loose_ = this->bookHisto(h_loose_, "Looseh1");
    }

    std::map<TString, TH1*>& m_histogram = m_stepHistograms_[step].m_histogram_;
    m_histogram["h_all"] = this->bookHisto(m_histogram["h_all"], "Allh1_step" + step);
    m_histogram["h_zVeto"] = this->bookHisto(m_histogram["h_zVeto"], "TTh1_step" + step);
    m_histogram["h_zWindow"] = this->bookHisto(m_histogram["h_zWindow"], "Zh1_step" + step);
}



TH1* DyScalingHistograms::bookHisto(TH1* histo, const TString& name)
{
    histo = this->store(new TH1D(name,"Dilepton Mass; m_{ll}; events",40,0,400));
    return histo;
}



void DyScalingHistograms::fillLoose(const double& dileptonMass, const double& weight)const
{
    h_loose_->Fill(dileptonMass, weight);
}



void DyScalingHistograms::fillZWindow(const double& dileptonMass, const double& weight, const TString& step)
{
    // Check if step exists
    const bool stepExists(this->checkExistence(step));
    if(!stepExists){
        std::cerr<<"Error in fillZWindow() of DyScalingHistograms! The following step is not defined for Drell-Yan scaling: "
                 <<step<<"\n...exiting\n";
        exit(22);
    }

    // Fill histograms
    m_stepHistograms_[step].m_histogram_["h_zWindow"]->Fill(dileptonMass, weight);
    m_stepHistograms_[step].m_histogram_["h_all"]->Fill(dileptonMass, weight);
}



void DyScalingHistograms::fillZVeto(const double& dileptonMass, const double& weight, const TString& step)
{
    // Check if step exists
    const bool stepExists(this->checkExistence(step));
    if(!stepExists){
        std::cerr<<"Error in fillZVeto() of DyScalingHistograms! The following step is not defined for Drell-Yan scaling: "
                 <<step<<"\n...exiting\n";
        exit(23);
    }

    // Fill histograms
    m_stepHistograms_[step].m_histogram_["h_zVeto"]->Fill(dileptonMass, weight);
    m_stepHistograms_[step].m_histogram_["h_all"]->Fill(dileptonMass, weight);
}








// --------------------------- Methods for BasicHistograms ---------------------------------------------



BasicHistograms::Input::Input(const std::vector<int>& leptonIndices, const std::vector<int>& antiLeptonIndices,
                              const std::vector<int>& jetIndices, const std::vector<int>& bjetIndices,
                              const VLV& allLeptons, const VLV& jets, const LV& met,
                              const std::vector<double>& btagDiscriminators):
leptonIndices_(leptonIndices),
antiLeptonIndices_(antiLeptonIndices),
jetIndices_(jetIndices),
bjetIndices_(bjetIndices),
allLeptons_(allLeptons),
jets_(jets),
met_(met),
btagDiscriminators_(btagDiscriminators)
{}



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



void BasicHistograms::fill(const Input& input, const double& weight, const TString& step)
{
    // Check if step exists
    const bool stepExists(this->checkExistence(step));
    if(!stepExists){
        std::cerr<<"Error in fill() of BasicHistograms! The following step is not defined for basic histograms: "
                 <<step<<"\n...exiting\n";
        exit(24);
    }
    
    
    // Switch this off for now, potentially add again if desired
    // Updating  titles of the histograms for b jets
    //if(m_stepHistograms_[step].m_histogram_["basicBjetMultiplicity"]->GetEntries()<1) {
    //    char addStr[20];
    //    std::sprintf(addStr," (#geq %.2f)", BtagWP);
    //    
    //    TH1* histo;
    //    histo = m_stepHistograms_[step].m_histogram_["basicBjetMultiplicity"];
    //    histo->SetTitle(TString(histo->GetTitle())+addStr);
    //    histo = m_stepHistograms_[step].m_histogram_["basicBjetPt"];
    //    histo->SetTitle(TString(histo->GetTitle())+addStr);
    //    histo = m_stepHistograms_[step].m_histogram_["basicBjetEta"];
    //    histo->SetTitle(TString(histo->GetTitle())+addStr);
    //    histo = m_stepHistograms_[step].m_histogram_["basicBjetPhi"];
    //    histo->SetTitle(TString(histo->GetTitle())+addStr);
    //}
    
    
    // Leptons
    m_stepHistograms_[step].m_histogram_["basicLepton_multiplicity"]->Fill(input.allLeptons_.size(), weight);
    for(const int index : input.leptonIndices_){
        m_stepHistograms_[step].m_histogram_["basicLepton_pt"]->Fill(input.allLeptons_.at(index).Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicLepton_eta"]->Fill(input.allLeptons_.at(index).Eta(), weight);
        m_stepHistograms_[step].m_histogram_["basicLepton_phi"]->Fill(input.allLeptons_.at(index).Phi(), weight);
    }
    for(const int index : input.antiLeptonIndices_){
        m_stepHistograms_[step].m_histogram_["basicLepton_pt"]->Fill(input.allLeptons_.at(index).Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicLepton_eta"]->Fill(input.allLeptons_.at(index).Eta(), weight);
        m_stepHistograms_[step].m_histogram_["basicLepton_phi"]->Fill(input.allLeptons_.at(index).Phi(), weight);
    }
    
    const int leptonIndex = input.leptonIndices_.size()>0 ? input.leptonIndices_.at(0) : -1;
    const int antiLeptonIndex = input.antiLeptonIndices_.size()>0 ? input.antiLeptonIndices_.at(0) : -1;
    const bool hasLeptonPair = (leptonIndex!=-1 && antiLeptonIndex!=-1);
    
    // Leading lepton and antilepton
    int leadingLeptonIndex(leptonIndex);
    int nLeadingLeptonIndex(antiLeptonIndex);
    if(hasLeptonPair){
        ttbar::orderIndices(leadingLeptonIndex, nLeadingLeptonIndex, input.allLeptons_, ttbar::LVpt);
        
        m_stepHistograms_[step].m_histogram_["basicLepton1st_pt"]->Fill(input.allLeptons_.at(leadingLeptonIndex).Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicLepton1st_eta"]->Fill(input.allLeptons_.at(leadingLeptonIndex).Eta(), weight);
        m_stepHistograms_[step].m_histogram_["basicLepton1st_phi"]->Fill(input.allLeptons_.at(leadingLeptonIndex).Phi(), weight);
        
        m_stepHistograms_[step].m_histogram_["basicLepton2nd_pt"]->Fill(input.allLeptons_.at(nLeadingLeptonIndex).Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicLepton2nd_eta"]->Fill(input.allLeptons_.at(nLeadingLeptonIndex).Eta(), weight);
        m_stepHistograms_[step].m_histogram_["basicLepton2nd_phi"]->Fill(input.allLeptons_.at(nLeadingLeptonIndex).Phi(), weight);
    }
    
    
    // Dilepton
    if(hasLeptonPair){
        LV dilepton(0.,0.,0.,0.);
        dilepton = input.allLeptons_.at(leadingLeptonIndex) + input.allLeptons_.at(nLeadingLeptonIndex);
        
        m_stepHistograms_[step].m_histogram_["basicDilepton_mass"]->Fill(dilepton.M(), weight);
        m_stepHistograms_[step].m_histogram_["basicDilepton_pt"]->Fill(dilepton.Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicDilepton_rapidity"]->Fill(dilepton.Rapidity(), weight);
        m_stepHistograms_[step].m_histogram_["basicDilepton_phi"]->Fill(dilepton.Phi(), weight);

        m_stepHistograms_[step].m_histogram_["basicDilepton_deltaEta"]->Fill(input.allLeptons_.at(leadingLeptonIndex).Eta() - input.allLeptons_.at(nLeadingLeptonIndex).Eta(), weight);
        m_stepHistograms_[step].m_histogram_["basicDilepton_deltaPhi"]->Fill(ROOT::Math::VectorUtil::DeltaPhi(input.allLeptons_.at(leadingLeptonIndex), input.allLeptons_.at(nLeadingLeptonIndex)), weight);
    }


    // Jets
    m_stepHistograms_[step].m_histogram_["basicJet_multiplicity"]->Fill(input.jetIndices_.size(), weight);
    for(const int index : input.jetIndices_){
        m_stepHistograms_[step].m_histogram_["basicJet_pt"]->Fill(input.jets_.at(index).Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicJet_eta"]->Fill(input.jets_.at(index).Eta(), weight);
        m_stepHistograms_[step].m_histogram_["basicJet_phi"]->Fill(input.jets_.at(index).Phi(), weight);
        m_stepHistograms_[step].m_histogram_["basicJet_btagDiscriminator"]->Fill(input.btagDiscriminators_.at(index), weight);
    }
    
    
    // Bjets
     m_stepHistograms_[step].m_histogram_["basicBjet_multiplicity"]->Fill(input.bjetIndices_.size(), weight);
    for(const int index : input.bjetIndices_){
        m_stepHistograms_[step].m_histogram_["basicBjet_pt"]->Fill(input.jets_.at(index).Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicBjet_eta"]->Fill(input.jets_.at(index).Eta(), weight);
        m_stepHistograms_[step].m_histogram_["basicBjet_phi"]->Fill(input.jets_.at(index).Phi(), weight);
    }
    
    
    // Met
    m_stepHistograms_[step].m_histogram_["basicMet_et"]->Fill(input.met_.E(), weight);
    m_stepHistograms_[step].m_histogram_["basicMet_phi"]->Fill(input.met_.Phi(), weight);
}








