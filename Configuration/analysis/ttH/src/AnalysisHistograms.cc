#define AnalysisHistograms_cxx

#include <iostream>

#include <TH1D.h>
#include <TString.h>

#include "AnalysisHistograms.h"





// --------------------------- Methods for AnalysisHistogtramBase ---------------------------------------------



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













