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
    name = "basicLeptonMultiplicity";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Lepton Multiplicity;N leptons;Events",10,0,10));
    name = "basicLeptonPt";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Lepton Pt;Pt(l) [GeV];Leptons",50,0,250));
    name = "basicLeptonEta";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Lepton #eta;#eta(l);Leptons",50,-2.6,2.6));
    name = "basicLeptonPhi";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Lepton #phi;#phi(l);Leptons",50,-3.2,3.2));
    name = "basicLeptonPt_1st";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "1-st Lepton Pt;Pt(l_{1}) [GeV];Leptons",50,0,250));
    name = "basicLeptonEta_1st";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "1-st Lepton #eta;#eta(l_{1});Leptons",50,-2.6,2.6));
    name = "basicLeptonPhi_1st";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "1-st Lepton #phi;#phi(l_{1});Leptons",50,-3.2,3.2));
    name = "basicLeptonPt_2nd";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "2-nd Lepton Pt;Pt(l_{2}) [GeV];Leptons",50,0,250));
    name = "basicLeptonEta_2nd";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "2-nd Lepton #eta;#eta(l_{2});Leptons",50,-2.6,2.6));
    name = "basicLeptonPhi_2nd";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "2-nd Lepton #phi;#phi(l_{2});Leptons",50,-3.2,3.2));

    // diLepton
    name = "basicDileptonMass";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Dilepton Mass;Mass(l^{+}+l^{-}) [GeV];Events",50,0,350));
    name = "basicDileptonPt";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Dilepton Pt;Pt(l^{+}+l^{-}) [GeV];Events",50,0,300));
    name = "basicDileptonRapidity";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Dilepton Rapidity;Rapidity(l^{+}+l^{-});Events",50,-2.6,2.6));
    name = "basicDileptonDeltaEta";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Dilepton #Delta#eta;|#eta(l^{+})-#eta(l^{-})|;Events",50,-5,5));
    name = "basicDileptonDeltaPhi";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Dilepton #Delta#phi;|#phi(l^{+})-#phi(l^{-})|;Events",50,-3.2,3.2));

    // Jets
    name = "basicJetMultiplicity";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Jet Multiplicity;N jets;Events",20,0,20));
    name = "basicJetPt";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Jet Pt;Pt(jet) [GeV];Jets",50,0,300));
    name = "basicJetEta";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Jet #eta;#eta(jet);Jets",50,-2.6,2.6));
    name = "basicJetPhi";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Jet #phi;#phi(jet);Jets",50,-3.2,3.2));
    name = "basicJetBtagDiscriminator";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "b tag Discriminator d;d;Jets",60,0.1,1.1));
    name = "basicBjetMultiplicity";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "B-Jet Multiplicity;N b-jets;Events",20,0,20));
    name = "basicBjetPt";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "B-Jet Pt;Pt(b-jet) [GeV];B-Jets",50,0,300));
    name = "basicBjetEta";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "B-Jet #eta;#eta(b-jet);B-Jets",50,-2.6,2.6));
    name = "basicBjetPhi";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "B-Jet #phi;#phi(b-jet);B-Jets",50,-3.2,3.2));

    // MEt
    name = "basicMet";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Missing Et;met;Events",50,0,300));
    name = "basicMetPhi";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "Missing Et #phi;#phi(met);Events",50,-3.2,3.2));
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
    //    sprintf(addStr," (#geq %.2f)", BtagWP);
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
    m_stepHistograms_[step].m_histogram_["basicLeptonMultiplicity"]->Fill(input.allLeptons_.size(), weight);
    for(const int index : input.leptonIndices_){
        m_stepHistograms_[step].m_histogram_["basicLeptonPt"]->Fill(input.allLeptons_.at(index).Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicLeptonEta"]->Fill(input.allLeptons_.at(index).Eta(), weight);
        m_stepHistograms_[step].m_histogram_["basicLeptonPhi"]->Fill(input.allLeptons_.at(index).Phi(), weight);
    }
    for(const int index : input.antiLeptonIndices_){
        m_stepHistograms_[step].m_histogram_["basicLeptonPt"]->Fill(input.allLeptons_.at(index).Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicLeptonEta"]->Fill(input.allLeptons_.at(index).Eta(), weight);
        m_stepHistograms_[step].m_histogram_["basicLeptonPhi"]->Fill(input.allLeptons_.at(index).Phi(), weight);
    }
    
    const int leptonIndex = input.leptonIndices_.size()>0 ? input.leptonIndices_.at(0) : -1;
    const int antiLeptonIndex = input.antiLeptonIndices_.size()>0 ? input.antiLeptonIndices_.at(0) : -1;
    const bool hasLeptonPair = (leptonIndex!=-1 && antiLeptonIndex!=-1);
    
    int leadingLeptonIndex(leptonIndex);
    int nLeadingLeptonIndex(antiLeptonIndex);
    if(hasLeptonPair){
        ttbar::orderIndices(leadingLeptonIndex, nLeadingLeptonIndex, input.allLeptons_, ttbar::LVpt);
        
        m_stepHistograms_[step].m_histogram_["basicLeptonPt_1st"]->Fill(input.allLeptons_.at(leadingLeptonIndex).Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicLeptonEta_1st"]->Fill(input.allLeptons_.at(leadingLeptonIndex).Eta(), weight);
        m_stepHistograms_[step].m_histogram_["basicLeptonPhi_1st"]->Fill(input.allLeptons_.at(leadingLeptonIndex).Phi(), weight);
        
        m_stepHistograms_[step].m_histogram_["basicLeptonPt_2nd"]->Fill(input.allLeptons_.at(nLeadingLeptonIndex).Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicLeptonEta_2nd"]->Fill(input.allLeptons_.at(nLeadingLeptonIndex).Eta(), weight);
        m_stepHistograms_[step].m_histogram_["basicLeptonPhi_2nd"]->Fill(input.allLeptons_.at(nLeadingLeptonIndex).Phi(), weight);
    }
    
    
    // Dilepton
    if(hasLeptonPair){
        LV dilepton(0.,0.,0.,0.);
        dilepton = input.allLeptons_.at(leadingLeptonIndex) + input.allLeptons_.at(nLeadingLeptonIndex);
        
        m_stepHistograms_[step].m_histogram_["basicDileptonMass"]->Fill(dilepton.M(), weight);
        m_stepHistograms_[step].m_histogram_["basicDileptonPt"]->Fill(dilepton.Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicDileptonRapidity"]->Fill(dilepton.Rapidity(), weight);

        m_stepHistograms_[step].m_histogram_["basicDileptonDeltaPhi"]->Fill(ROOT::Math::VectorUtil::DeltaPhi(input.allLeptons_.at(leadingLeptonIndex), input.allLeptons_.at(nLeadingLeptonIndex)), weight);
        m_stepHistograms_[step].m_histogram_["basicDileptonDeltaEta"]->Fill(input.allLeptons_.at(leadingLeptonIndex).Eta() - input.allLeptons_.at(nLeadingLeptonIndex).Eta(), weight);
    }


    // Jets
    m_stepHistograms_[step].m_histogram_["basicJetMultiplicity"]->Fill(input.jetIndices_.size(), weight);
    for(const int index : input.jetIndices_){
        m_stepHistograms_[step].m_histogram_["basicJetPt"]->Fill(input.jets_.at(index).Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicJetEta"]->Fill(input.jets_.at(index).Eta(), weight);
        m_stepHistograms_[step].m_histogram_["basicJetPhi"]->Fill(input.jets_.at(index).Phi(), weight);
        m_stepHistograms_[step].m_histogram_["basicJetBtagDiscriminator"]->Fill(input.btagDiscriminators_.at(index), weight);
    }
    
    
    // b jets
     m_stepHistograms_[step].m_histogram_["basicBjetMultiplicity"]->Fill(input.bjetIndices_.size(), weight);
    for(const int index : input.bjetIndices_){
        m_stepHistograms_[step].m_histogram_["basicBjetPt"]->Fill(input.jets_.at(index).Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicBjetEta"]->Fill(input.jets_.at(index).Eta(), weight);
        m_stepHistograms_[step].m_histogram_["basicBjetPhi"]->Fill(input.jets_.at(index).Phi(), weight);
    }
    
    
    // Met
    m_stepHistograms_[step].m_histogram_["basicMet"]->Fill(input.met_.E(), weight);
    m_stepHistograms_[step].m_histogram_["basicMetPhi"]->Fill(input.met_.Phi(), weight);
}








