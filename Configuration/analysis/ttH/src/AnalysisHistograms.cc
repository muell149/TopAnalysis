#define AnalysisHistograms_cxx

#include <iostream>
#include <algorithm>

#include <TH1D.h>
#include <TString.h>
#include <Math/VectorUtil.h>

#include "AnalysisHistograms.h"





// --------------------------- Methods for AnalysisHistogramBase ---------------------------------------------



void AnalysisHistogramsBase::addStep(const TString& step, TSelectorList* output)
{
    // Set pointer to output, so that histograms are owned by it
    selectorList_ = output;

    // Check whether step already exists
    if(this->checkExistence(step)){
        std::cout<<"Warning in addStep()! Drell-Yan scaling already contains selection step: "<<step
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

    std::map<TString, TH1D*>& m_histogram = m_stepHistograms_[step].m_histogram_;
    m_histogram["h_all"] = this->bookHisto(m_histogram["h_all"], "Allh1_step" + step);
    m_histogram["h_zVeto"] = this->bookHisto(m_histogram["h_zVeto"], "TTh1_step" + step);
    m_histogram["h_zWindow"] = this->bookHisto(m_histogram["h_zWindow"], "Zh1_step" + step);
}



TH1D* DyScalingHistograms::bookHisto(TH1D* histo, const TString& name)
{
    histo = this->store(new TH1D(name,"Dilepton Mass",40,0,400));
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
        std::cerr<<"Error in fillZWindow(): The following step is not defined for Drell-Yan scaling: "<<step
                 <<"\n...exiting\n";
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
        std::cerr<<"Error in fillZVeto(): The following step is not defined for Drell-Yan scaling: "<<step
                 <<"\n...exiting\n";
        exit(22);
    }

    // Fill histograms
    m_stepHistograms_[step].m_histogram_["h_zVeto"]->Fill(dileptonMass, weight);
    m_stepHistograms_[step].m_histogram_["h_all"]->Fill(dileptonMass, weight);
}








// --------------------------- Methods for AnalysisBasicHistograms ---------------------------------------------



void AnalysisBasicHistograms::bookHistos(const TString& step)
{

    std::map<TString, TH1D*>& m_histogram = m_stepHistograms_[step].m_histogram_;
    int nBins = 50;
    TString name;

    // Leptons
    name="basicLeptonMult";
    m_histogram[name] = this->store(new TH1D(name+"_"+step, "Lepton Multiplicity;N leptons;Events",10,0,10));
    name="basicLeptonPt";
    m_histogram[name] = this->store(new TH1D(name+"_"+step, "Lepton Pt;Pt(l) [GeV];Leptons",nBins,0,250));
    name="basicLeptonEta";
    m_histogram[name] = this->store(new TH1D(name+"_"+step, "Lepton #eta;#eta(l);Leptons",nBins,-2.6,2.6));
    name="basicLeptonPt_1st";
    m_histogram[name] = this->store(new TH1D(name+"_"+step, "1-st Lepton Pt;Pt(l_{1}) [GeV];Leptons",nBins,0,250));
    name="basicLeptonEta_1st";
    m_histogram[name] = this->store(new TH1D(name+"_"+step, "1-st Lepton #eta;#eta(l_{1});Leptons",nBins,-2.6,2.6));
    name="basicLeptonPt_2nd";
    m_histogram[name] = this->store(new TH1D(name+"_"+step, "2-nd Lepton Pt;Pt(l_{2}) [GeV];Leptons",nBins,0,250));
    name="basicLeptonEta_2nd";
    m_histogram[name] = this->store(new TH1D(name+"_"+step, "2-nd Lepton #eta(l_{2});#eta;Leptons",nBins,-2.6,2.6));

    // diLepton
    name="basicDiLeptonMass";
    m_histogram[name] = this->store(new TH1D(name+"_"+step, "DiLepton Mass;Mass(l^{+}+l^{-}) [GeV];Events",nBins,0,350));
    name="basicDiLeptonPt";
    m_histogram[name] = this->store(new TH1D(name+"_"+step, "DiLepton Pt;Pt(l^{+}+l^{-}) [GeV];Events",nBins,0,300));
    name="basicDiLeptonRap";
    m_histogram[name] = this->store(new TH1D(name+"_"+step, "DiLepton Rapidity;Rapidity(l^{+}+l^{-});Events",nBins,-2.6,2.6));
    name="basicDiLeptonDPhi";
    m_histogram[name] = this->store(new TH1D(name+"_"+step, "DiLepton d#phi;| #phi(l^{+}) - #phi(l^{-}) |;Events",nBins,0,3.2));
    name="basicDiLeptonDEta";
    m_histogram[name] = this->store(new TH1D(name+"_"+step, "DiLepton d#eta;| #eta(l^{+}) - #eta(l^{-}) |;Events",nBins,0,4));

    // Jets
    name="basicJetMult";
    m_histogram[name] = this->store(new TH1D(name+"_"+step, "Jet Multiplicity;N jets;Events",20,0,20));
    name="basicJetPt";
    m_histogram[name] = this->store(new TH1D(name+"_"+step, "Jet Pt;Pt(jet) [GeV];Jets",nBins,0,300));
    name="basicJetEta";
    m_histogram[name] = this->store(new TH1D(name+"_"+step, "Jet #eta;#eta(jet);Jets",nBins,-2.6,2.6));
    name="basicJetBTagOut";
    m_histogram[name] = this->store(new TH1D(name+"_"+step, "Jet bTag output;Value;Jets",nBins+1,0.0-1.0/nBins,1.001));
    name="basicJetBMult";
    m_histogram[name] = this->store(new TH1D(name+"_"+step, "B-Jet Multiplicity;N jets;Events",20,0,20));
    name="basicJetBPt";
    m_histogram[name] = this->store(new TH1D(name+"_"+step, "B-Jet Pt;Pt(jet) [GeV];Jets",nBins,0,300));
    name="basicJetBEta";
    m_histogram[name] = this->store(new TH1D(name+"_"+step, "B-Jet #eta;#eta(jet);Jets",nBins,-2.6,2.6));

    // MEt
    name="basicMEt";
    m_histogram[name] = this->store(new TH1D(name+"_"+step, "Missing Et;MEt;Events",nBins,0,300));
    name="basicMEtPhi";
    m_histogram[name] = this->store(new TH1D(name+"_"+step, "Missing Et Phi;Phi(MEt);Events",nBins,-3.2,3.2));
}


void AnalysisBasicHistograms::fill(const VLV* leptons, const int& LeadLeptonId, const int& NLeadLeptonId, const VLV* jets, const std::vector<int>* SelJetIds, const std::vector<double>* bTagOutput, const double& BTagWP, const LV* MEt, const double& weight, const TString& step)
{

    // Check if step exists
    const bool stepExists(this->checkExistence(step));
    if(!stepExists){
        std::cerr<<"Error in fill(): The following step is not defined for basic histograms: "<<step
                 <<"\n...exiting\n";
        exit(22);
    }


    // Updating  titles of the histograms for B-Jets
    if(m_stepHistograms_[step].m_histogram_["basicJetBMult"]->GetEntries()<1) {
        char addStr[20];
        sprintf(addStr," (#geq %.2f)",BTagWP);

        TH1* histo;
        histo = m_stepHistograms_[step].m_histogram_["basicJetBMult"];
        histo->SetTitle(TString(histo->GetTitle())+addStr);
        histo = m_stepHistograms_[step].m_histogram_["basicJetBPt"];
        histo->SetTitle(TString(histo->GetTitle())+addStr);
        histo = m_stepHistograms_[step].m_histogram_["basicJetBEta"];
        histo->SetTitle(TString(histo->GetTitle())+addStr);
    }


    // Leptons
    m_stepHistograms_[step].m_histogram_["basicLeptonMult"]->Fill(leptons->size(), weight);
    for(size_t iLep=0; iLep<leptons->size(); iLep++) {
        m_stepHistograms_[step].m_histogram_["basicLeptonPt"]->Fill(leptons->at(iLep).Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicLeptonEta"]->Fill(leptons->at(iLep).Eta(), weight);
        if(LeadLeptonId==(int)iLep) {
            m_stepHistograms_[step].m_histogram_["basicLeptonPt_1st"]->Fill(leptons->at(iLep).Pt(), weight);
            m_stepHistograms_[step].m_histogram_["basicLeptonEta_1st"]->Fill(leptons->at(iLep).Eta(), weight);
        }
        if(NLeadLeptonId==(int)iLep) {
            m_stepHistograms_[step].m_histogram_["basicLeptonPt_2nd"]->Fill(leptons->at(iLep).Pt(), weight);
            m_stepHistograms_[step].m_histogram_["basicLeptonEta_2nd"]->Fill(leptons->at(iLep).Eta(), weight);
        }
    }

    // diLepton
    while(LeadLeptonId>=0 && NLeadLeptonId>=0) {
        if(LeadLeptonId == NLeadLeptonId) break;
        if(LeadLeptonId >= (int)leptons->size() || NLeadLeptonId >= (int)leptons->size()) break;
        LV diLepton = leptons->at(LeadLeptonId) + leptons->at(NLeadLeptonId);

        m_stepHistograms_[step].m_histogram_["basicDiLeptonMass"]->Fill(diLepton.M(), weight);
        m_stepHistograms_[step].m_histogram_["basicDiLeptonPt"]->Fill(diLepton.Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicDiLeptonRap"]->Fill(diLepton.Rapidity(), weight);

        m_stepHistograms_[step].m_histogram_["basicDiLeptonDPhi"]->Fill(fabs( ROOT::Math::VectorUtil::DeltaPhi(leptons->at(LeadLeptonId), leptons->at(NLeadLeptonId)) ), weight);
        m_stepHistograms_[step].m_histogram_["basicDiLeptonDEta"]->Fill(fabs( leptons->at(LeadLeptonId).Eta() - leptons->at(NLeadLeptonId).Eta() ), weight);

        break;
    }


    // Jets
    int nBJets = 0;
    m_stepHistograms_[step].m_histogram_["basicJetMult"]->Fill(jets->size(), weight);
    for(size_t iJet=0; iJet<jets->size(); iJet++) {
        if(SelJetIds) {     // Skipping jets that are not included in the list of selected jets
            if( std::find(SelJetIds->begin(), SelJetIds->end(), (int)iJet) == SelJetIds->end() ) continue;
        }

        m_stepHistograms_[step].m_histogram_["basicJetPt"]->Fill(jets->at(iJet).Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicJetEta"]->Fill(jets->at(iJet).Eta(), weight);
        m_stepHistograms_[step].m_histogram_["basicJetBTagOut"]->Fill(bTagOutput->at(iJet), weight);
        if(bTagOutput->at(iJet)<BTagWP) continue;

        // B-Jets
        nBJets++;
        m_stepHistograms_[step].m_histogram_["basicJetBPt"]->Fill(jets->at(iJet).Pt(), weight);
        m_stepHistograms_[step].m_histogram_["basicJetBEta"]->Fill(jets->at(iJet).Eta(), weight);
    }
    m_stepHistograms_[step].m_histogram_["basicJetBMult"]->Fill(nBJets, weight);

    // MEt
    m_stepHistograms_[step].m_histogram_["basicMEt"]->Fill(MEt->E(), weight);
    m_stepHistograms_[step].m_histogram_["basicMEtPhi"]->Fill(MEt->Phi(), weight);

}

