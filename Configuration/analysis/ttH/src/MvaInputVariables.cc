#include <iostream>
#include <cstdlib>
#include <algorithm>

#include <TH1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TString.h>
#include <TSelectorList.h>
#include <TObject.h>
#include <Rtypes.h>

#include "MvaInputVariables.h"
#include "mvaStructs.h"
#include "AnalysisHistograms.h"





MvaInputTopJetsVariables::MvaInputTopJetsVariables(const std::vector<TString>& selectionStepsNoCategories):
selectorList_(0),
selectionSteps_(selectionStepsNoCategories)
{
    std::cout<<"--- Beginning control plots for MVA input\n";
    std::cout<<"=== Finishing control plots for MVA input\n\n";
}



void MvaInputTopJetsVariables::clear()
{
    v_mvaTopJetsVariablesPerEvent_.clear();
    selectorList_ = 0;
    m_plotStruct_.clear();
    m_plotStruct2D_.clear();
}



void MvaInputTopJetsVariables::mvaInputVariablesControlPlots(const std::string& f_savename)
{
    // Output file
    TFile outputFile(f_savename.c_str(),"RECREATE");
    std::cout<<"\nOutput file for MVA input control plots: "<<f_savename<<"\n";
    
    // Produce MVA input control plots and store them in output
    TSelectorList* output = new TSelectorList();
    this->mvaInputVariablesControlPlots(output);
    
    // Write file and cleanup
    TIterator* it = output->MakeIterator();
    while(TObject* obj = it->Next()){
        obj->Write();
    }
    outputFile.Close();
    output->SetOwner();
    output->Clear();
}



void MvaInputTopJetsVariables::mvaInputVariablesControlPlots(TSelectorList* output)
{
    std::cout<<"--- Beginning control plots for MVA variables\n";
    
    // Set pointer to output, so that histograms are owned by it
    selectorList_ = output;
    
    const TString step("_step8");
    
    // Book histograms concerning MVA
    TH1* h_trueStatus_step8 = store(new TH1D("trueStatus_step8", "True status of matched jets;Status;# jet pairs",2,0,2));
    h_trueStatus_step8->GetXaxis()->SetBinLabel(1, "swapped");
    h_trueStatus_step8->GetXaxis()->SetBinLabel(2, "correct");
    
    this->bookHistograms("jetChargeDiff"+step, "jetChargeDiff;#Deltac_{rel}^{jet};# jet pairs",50,0,2);
    
    this->bookHistograms("meanDeltaPhi_b_met"+step, "meanDeltaPhi_b_met;0.5(|#Delta#phi(b,MET)|+|#Delta#phi(#bar{b},MET)|)  [rad];# jet pairs",20,0,3.2);
    this->bookHistograms("massDiff_recoil_bbbar"+step, "massDiff_recoil_Bbbar; m_{recoil}^{jets}-m^{b#bar{b}}  [GeV];# jet pairs",16,-600,600);
    this->bookHistograms("pt_b_antiLepton"+step, "pt_b_antiLepton; p_{T}^{bl^{+}}  [GeV];# jet pairs",20,0,500);
    this->bookHistograms("pt_antiB_lepton"+step, "pt_antiB_lepton; p_{T}^{#bar{b}l^{-}}  [GeV];# jet pairs",20,0,500);
    this->bookHistograms("deltaR_b_antiLepton"+step, "deltaR_b_antiLepton; #DeltaR(b,l^{+});# jet pairs",25,0,5);
    this->bookHistograms("deltaR_antiB_lepton"+step, "deltaR_antiB_lepton; #DeltaR(#bar{b},l^{-});# jet pairs",25,0,5);
    this->bookHistograms("btagDiscriminatorSum"+step, "btagDiscriminatorSum; d^{b}+d^{#bar{b}};# jet pairs",20,0,2);
    this->bookHistograms("deltaPhi_antiBLepton_bAntiLepton"+step, "deltaPhi_antiBLepton_bAntiLepton; |#Delta#phi(bl^{+},#bar{b}l^{-})|  [rad];# jet pairs",10,0,3.2);
    this->bookHistograms("massDiff_fullBLepton_bbbar"+step, "massDiff_fullBLepton_bbbar; m^{b#bar{b}l^{+}l^{-}}-m^{b#bar{b}}  [GeV];# jet pairs",13,0,1050);
    this->bookHistograms("meanMt_b_met"+step, "meanMt_b_met; 0.5(m_{T}^{b,MET}+m_{T}^{#bar{b},MET)}  [GeV];# jet pairs",21,0,630);
    this->bookHistograms("massSum_antiBLepton_bAntiLepton"+step, "massSum_antiBLepton_bAntiLepton; m^{#bar{b}l^{-}}+m^{bl^{+}}  [GeV];# jet pairs",21,0,840);
    this->bookHistograms("massDiff_antiBLepton_bAntiLepton"+step, "massDiff_antiBLepton_bAntiLepton; m^{#bar{b}l^{-}}-m^{bl^{+}}  [GeV];# jet pairs",41,-400,420);
    
    // Fill histograms
    for(const auto& mvaTopJetsVariablesPerEvent : v_mvaTopJetsVariablesPerEvent_){
        
        for(const auto& mvaTopJetsVariables : mvaTopJetsVariablesPerEvent.variables()){
            
            //const bool bQuarkRecoJetMatched = mvaInputTopJetsStruct.bQuarkRecoJetMatched_;
            const double eventWeight(mvaTopJetsVariables.eventWeight_.value_);
            if(mvaTopJetsVariables.swappedCombination_.value_)h_trueStatus_step8->Fill(0.1, eventWeight);
            if(mvaTopJetsVariables.correctCombination_.value_)h_trueStatus_step8->Fill(1.1, eventWeight);
            
            
            // FIXME: replace by variable names
            this->fillHistograms("jetChargeDiff"+step, mvaTopJetsVariables.jetChargeDiff_.value_, mvaTopJetsVariables);
            
            this->fillHistograms("meanDeltaPhi_b_met"+step, mvaTopJetsVariables.meanDeltaPhi_b_met_.value_, mvaTopJetsVariables);
            this->fillHistograms("massDiff_recoil_bbbar"+step, mvaTopJetsVariables.massDiff_recoil_bbbar_.value_, mvaTopJetsVariables);
            this->fillHistograms("pt_b_antiLepton"+step, mvaTopJetsVariables.pt_b_antiLepton_.value_, mvaTopJetsVariables);
            this->fillHistograms("pt_antiB_lepton"+step, mvaTopJetsVariables.pt_antiB_lepton_.value_, mvaTopJetsVariables);
            this->fillHistograms("deltaR_b_antiLepton"+step, mvaTopJetsVariables.deltaR_b_antiLepton_.value_, mvaTopJetsVariables);
            this->fillHistograms("deltaR_antiB_lepton"+step, mvaTopJetsVariables.deltaR_antiB_lepton_.value_, mvaTopJetsVariables);
            this->fillHistograms("btagDiscriminatorSum"+step, mvaTopJetsVariables.btagDiscriminatorSum_.value_, mvaTopJetsVariables);
            this->fillHistograms("deltaPhi_antiBLepton_bAntiLepton"+step, mvaTopJetsVariables.deltaPhi_antiBLepton_bAntiLepton_.value_, mvaTopJetsVariables);
            this->fillHistograms("massDiff_fullBLepton_bbbar"+step, mvaTopJetsVariables.massDiff_fullBLepton_bbbar_.value_, mvaTopJetsVariables);
            this->fillHistograms("meanMt_b_met"+step, mvaTopJetsVariables.meanMt_b_met_.value_, mvaTopJetsVariables);
            this->fillHistograms("massSum_antiBLepton_bAntiLepton"+step, mvaTopJetsVariables.massSum_antiBLepton_bAntiLepton_.value_, mvaTopJetsVariables);
            this->fillHistograms("massDiff_antiBLepton_bAntiLepton"+step, mvaTopJetsVariables.massDiff_antiBLepton_bAntiLepton_.value_, mvaTopJetsVariables);
        }
    }
    
    std::cout<<"=== Finishing control plots for MVA variables\n\n";
}



void MvaInputTopJetsVariables::bookHistograms(const TString& name, const TString& title,
                                              const int nBin, const double xMin, const double xMax)
{
    // Check if histograms with given name already exist
    if(m_plotStruct_.find(name) != m_plotStruct_.end()){
        std::cerr<<"ERROR! Trial of booking already existing histogram with name: "<<name
                 <<"\n...break\n"<<std::endl;
        exit(876);
    }
    
    const TString nameCorrect("correct_" + name);
    const TString nameSwapped("swapped_" + name);
    const TString nameWrong("wrong_" + name);
    
    // Book histograms
    PlotStruct plotStruct;
    plotStruct.h_correctCombination = store(new TH1D(nameCorrect, title, nBin, xMin, xMax));
    plotStruct.h_swappedCombination = store(new TH1D(nameSwapped, title, nBin, xMin, xMax));
    plotStruct.h_wrongCombinations = store(new TH1D(nameWrong, title, nBin, xMin, xMax));
    plotStruct.h_allCombinations = store(new TH1D(name, title, nBin, xMin, xMax));
    m_plotStruct_[name] = plotStruct;
}



void MvaInputTopJetsVariables::bookHistograms2D(const TString& name, const TString& title, const int nBinX, const double xMin, const double xMax, const int nBinY, const double yMin, const double yMax)
{
    // Check if histograms with given name already exist
    if(m_plotStruct2D_.find(name) != m_plotStruct2D_.end()){
        std::cerr<<"ERROR! Trial of booking already existing histogram with name: "<<name
                 <<"\n...break\n"<<std::endl;
        exit(876);
    }
    
    const TString nameCorrect("correct_" + name);
    const TString nameSwapped("swapped_" + name);
    const TString nameWrong("wrong_" + name);
    
    // Book histograms
    PlotStruct2D plotStruct;
    plotStruct.h_correctCombination = store(new TH2D(nameCorrect, title, nBinX, xMin, xMax, nBinY, yMin, yMax));
    plotStruct.h_swappedCombination = store(new TH2D(nameSwapped, title, nBinX, xMin, xMax, nBinY, yMin, yMax));
    plotStruct.h_wrongCombinations = store(new TH2D(nameWrong, title, nBinX, xMin, xMax, nBinY, yMin, yMax));
    plotStruct.h_allCombinations = store(new TH2D(name, title, nBinX, xMin, xMax, nBinY, yMin, yMax));
    m_plotStruct2D_[name] = plotStruct;
}



void MvaInputTopJetsVariables::fillHistograms(const TString& name, const Float_t& variable, const MvaTopJetsVariables& mvaTopJetsVariables)
{
    // Check if histograms with given name already exist
    if(m_plotStruct_.find(name) == m_plotStruct_.end()){
        std::cerr<<"ERROR! Trial of filling non-existing histogram with name: "<<name
                 <<"\n...break\n"<<std::endl;
        exit(876);
    }
    PlotStruct& plotStruct = m_plotStruct_.at(name);
    
    // Access relevant information
    const double& eventWeight(mvaTopJetsVariables.eventWeight_.value_);
    const bool correctCombination(mvaTopJetsVariables.correctCombination_.value_);
    const bool swappedCombination(mvaTopJetsVariables.swappedCombination_.value_);
    
    // Fill histograms
    if(correctCombination) plotStruct.h_correctCombination->Fill(variable, eventWeight);
    else if(swappedCombination) plotStruct.h_swappedCombination->Fill(variable, eventWeight);
    else plotStruct.h_wrongCombinations->Fill(variable, eventWeight);
    plotStruct.h_allCombinations->Fill(variable, eventWeight);
}



void MvaInputTopJetsVariables::fillHistograms2D(const TString& name, const double& variable1, const double& variable2,
                                                const MvaTopJetsVariables& mvaTopJetsVariables)
{
    // Check if histograms with given name already exist
    if(m_plotStruct2D_.find(name) == m_plotStruct2D_.end()){
        std::cerr<<"ERROR! Trial of filling non-existing histogram with name: "<<name
                 <<"\n...break\n"<<std::endl;
        exit(876);
    }
    PlotStruct2D& plotStruct = m_plotStruct2D_.at(name);
    
    // Access relevant information
    const double& eventWeight(mvaTopJetsVariables.eventWeight_.value_);
    const bool correctCombination(mvaTopJetsVariables.correctCombination_.value_);
    const bool swappedCombination(mvaTopJetsVariables.swappedCombination_.value_);
    
    // Fill histograms
    if(correctCombination) plotStruct.h_correctCombination->Fill(variable1, variable2, eventWeight);
    else if(swappedCombination) plotStruct.h_swappedCombination->Fill(variable1, variable2, eventWeight);
    else plotStruct.h_wrongCombinations->Fill(variable1, variable2, eventWeight);
    plotStruct.h_allCombinations->Fill(variable1, variable2, eventWeight);
}












