#include "dyScalingHistograms.h"


#include <iostream>




void
DyScalingHistograms::addStep(const TString& step){
    if(!m_stepHistograms_.size()){
        h_loose_ = this->bookHisto(h_loose_, "Looseh1");
    }
    if(this->checkExistence(step)){
        std::cout<<"Warning in addStep()! Drell-Yan scaling already contains selection step: "<<step
                 <<"\n...skip this one\n";
        return;
    }
    this->bookHistos(step);
}



TH1D*
DyScalingHistograms::bookHisto(TH1D* histo, const TString& name){
    histo = this->store(new TH1D(name,"Dilepton Mass",40,0,400));
    return histo;
}



void
DyScalingHistograms::bookHistos(const TString& step){
    DyStepHistograms dyStepHistograms;
    dyStepHistograms.h_all_ = this->bookHisto(dyStepHistograms.h_all_, "Allh1_" + step);
    dyStepHistograms.h_zVeto_ = this->bookHisto(dyStepHistograms.h_zVeto_, "TTh1_" + step);
    dyStepHistograms.h_zWindow_ = this->bookHisto(dyStepHistograms.h_zWindow_, "Zh1_" + step);
    m_stepHistograms_[step] = dyStepHistograms;
}



void
DyScalingHistograms::fillLoose(const double& dileptonMass, const double& weight){
    h_loose_->Fill(dileptonMass, weight);
}



void
DyScalingHistograms::fillZWindow(const double& dileptonMass, const double& weight, const TString& step){
    const bool stepExists(this->checkExistence(step));
    if(!stepExists){
        std::cerr<<"Error in fillZWindow(): The following step is not defined for Drell-Yan scaling: "<<step
                 <<"\n...exiting\n";
        exit(22);
    }
    m_stepHistograms_[step].h_zWindow_->Fill(dileptonMass, weight);
    m_stepHistograms_[step].h_all_->Fill(dileptonMass, weight);
}



void
DyScalingHistograms::fillZVeto(const double& dileptonMass, const double& weight, const TString& step){
    const bool stepExists(this->checkExistence(step));
    if(!stepExists){
        std::cerr<<"Error in fillZVeto(): The following step is not defined for Drell-Yan scaling: "<<step
                 <<"\n...exiting\n";
        exit(22);
    }
    m_stepHistograms_[step].h_zVeto_->Fill(dileptonMass, weight);
    m_stepHistograms_[step].h_all_->Fill(dileptonMass, weight);
}



bool
DyScalingHistograms::checkExistence(const TString& step){
    return m_stepHistograms_.find(step) != m_stepHistograms_.end();
}









