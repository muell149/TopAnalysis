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





MvaInputTopJetsVariables::MvaInputTopJetsVariables(const std::vector<TString>& selectionSteps,
                                                   const char* mvaWeightsFile, const char* mvaInputDir):
selectorList_(0),
selectionSteps_(selectionSteps),
mvaInputDir_(mvaInputDir)
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
    
    // Book histograms concerning MVA
    TH1* h_trueStatus_step8 = store(new TH1D("trueStatus_step8", "True status of matched jets;Status;# jet pairs",2,0,2));
    h_trueStatus_step8->GetXaxis()->SetBinLabel(1, "swapped");
    h_trueStatus_step8->GetXaxis()->SetBinLabel(2, "correct");
    
    this->bookHistograms("jetChargeDiff_step8", "jetChargeDiff_step8;#Deltac_{rel}^{jet};# jet pairs",50,0,2);
    
    this->bookHistograms("meanDeltaPhi_b_met_step8", "meanDeltaPhi_b_met;0.5(|#Delta#phi(b,MET)|+|#Delta#phi(#bar{b},MET)|)  [rad];# jet pairs",20,0,3.2);
    this->bookHistograms("massDiff_recoil_bbbar_step8", "massDiff_recoil_Bbbar; m_{recoil}^{jets}-m^{b#bar{b}}  [GeV];# jet pairs",16,-600,600);
    this->bookHistograms("pt_b_antiLepton_step8", "pt_b_antiLepton; p_{T}^{bl^{+}}  [GeV];# jet pairs",20,0,500);
    this->bookHistograms("pt_antiB_lepton_step8", "pt_antiB_lepton; p_{T}^{#bar{b}l^{-}}  [GeV];# jet pairs",20,0,500);
    this->bookHistograms("deltaR_b_antiLepton_step8", "deltaR_b_antiLepton; #DeltaR(b,l^{+});# jet pairs",25,0,5);
    this->bookHistograms("deltaR_antiB_lepton_step8", "deltaR_antiB_lepton; #DeltaR(#bar{b},l^{-});# jet pairs",25,0,5);
    this->bookHistograms("btagDiscriminatorSum_step8", "btagDiscriminatorSum; d^{b}+d^{#bar{b}};# jet pairs",20,0,2);
    this->bookHistograms("deltaPhi_antiBLepton_bAntiLepton_step8", "deltaPhi_antiBLepton_bAntiLepton; |#Delta#phi(bl^{+},#bar{b}l^{-})|  [rad];# jet pairs",10,0,3.2);
    this->bookHistograms("massDiff_fullBLepton_bbbar_step8", "massDiff_fullBLepton_bbbar; m^{b#bar{b}l^{+}l^{-}}-m^{b#bar{b}}  [GeV];# jet pairs",13,0,1050);
    this->bookHistograms("meanMt_b_met_step8", "meanMt_b_met; 0.5(m_{T}^{b,MET}+m_{T}^{#bar{b},MET)}  [GeV];# jet pairs",21,0,630);
    this->bookHistograms("massSum_antiBLepton_bAntiLepton_step8", "massSum_antiBLepton_bAntiLepton; m^{#bar{b}l^{-}}+m^{bl^{+}}  [GeV];# jet pairs",21,0,840);
    this->bookHistograms("massDiff_antiBLepton_bAntiLepton_step8", "massDiff_antiBLepton_bAntiLepton; m^{#bar{b}l^{-}}-m^{bl^{+}}  [GeV];# jet pairs",41,-400,420);
    
    this->bookHistograms("dijet_mvaWeightCorrect_step8", "dijet MVA weight correct;w_{MVA}^{correct};# jet pairs", 80, -1.2, 0.2);
    this->bookHistograms("dijet_bestMvaWeightCorrect_step8", "dijet best MVA weight correct;w_{MVA,1}^{correct};# events", 80, -1.2, 0.2);
    this->bookHistograms("dijet_mvaWeightSwapped_step8", "dijet MVA weight swapped;w_{MVA}^{swapped};# jet pairs", 80, -1.2, 0.2);
    this->bookHistograms("dijet_bestMvaWeightSwapped_step8", "dijet best MVA weight swapped;w_{MVA,1}^{swapped};# events", 80, -1.2, 0.2);
    
    this->bookHistograms2D("dijet_mvaWeightCorrectVsSwapped_step8", "dijet MVA weight correct vs. swapped;w_{MVA}^{correct};w_{MVA}^{swapped}", 40, -1.2, 0.2, 40, -1.2, 0.2);
    this->bookHistograms2D("dijet_bestMvaWeightCorrectVsSwapped_step8", "dijet best MVA weight correct vs. swapped;w_{MVA,1}^{correct};w_{MVA,1}^{swapped}", 40, -1.2, 0.2, 40, -1.2, 0.2);
    
    // Fill histograms
    for(const auto& mvaTopJetsVariablesPerEvent : v_mvaTopJetsVariablesPerEvent_){
        
        for(const auto& mvaTopJetsVariables : mvaTopJetsVariablesPerEvent.variables()){
            
            //const bool bQuarkRecoJetMatched = mvaInputTopJetsStruct.bQuarkRecoJetMatched_;
            const double eventWeight(mvaTopJetsVariables.eventWeight_.value_);
            if(mvaTopJetsVariables.swappedCombination_.value_)h_trueStatus_step8->Fill(0.1, eventWeight);
            if(mvaTopJetsVariables.correctCombination_.value_)h_trueStatus_step8->Fill(1.1, eventWeight);
            
            
            // FIXME: replace by variable names
            this->fillHistograms("jetChargeDiff_step8", mvaTopJetsVariables.jetChargeDiff_.value_, mvaTopJetsVariables);
            
            this->fillHistograms("meanDeltaPhi_b_met_step8", mvaTopJetsVariables.meanDeltaPhi_b_met_.value_, mvaTopJetsVariables);
            this->fillHistograms("massDiff_recoil_bbbar_step8", mvaTopJetsVariables.massDiff_recoil_bbbar_.value_, mvaTopJetsVariables);
            this->fillHistograms("pt_b_antiLepton_step8", mvaTopJetsVariables.pt_b_antiLepton_.value_, mvaTopJetsVariables);
            this->fillHistograms("pt_antiB_lepton_step8", mvaTopJetsVariables.pt_antiB_lepton_.value_, mvaTopJetsVariables);
            this->fillHistograms("deltaR_b_antiLepton_step8", mvaTopJetsVariables.deltaR_b_antiLepton_.value_, mvaTopJetsVariables);
            this->fillHistograms("deltaR_antiB_lepton_step8", mvaTopJetsVariables.deltaR_antiB_lepton_.value_, mvaTopJetsVariables);
            this->fillHistograms("btagDiscriminatorSum_step8", mvaTopJetsVariables.btagDiscriminatorSum_.value_, mvaTopJetsVariables);
            this->fillHistograms("deltaPhi_antiBLepton_bAntiLepton_step8", mvaTopJetsVariables.deltaPhi_antiBLepton_bAntiLepton_.value_, mvaTopJetsVariables);
            this->fillHistograms("massDiff_fullBLepton_bbbar_step8", mvaTopJetsVariables.massDiff_fullBLepton_bbbar_.value_, mvaTopJetsVariables);
            this->fillHistograms("meanMt_b_met_step8", mvaTopJetsVariables.meanMt_b_met_.value_, mvaTopJetsVariables);
            this->fillHistograms("massSum_antiBLepton_bAntiLepton_step8", mvaTopJetsVariables.massSum_antiBLepton_bAntiLepton_.value_, mvaTopJetsVariables);
            this->fillHistograms("massDiff_antiBLepton_bAntiLepton_step8", mvaTopJetsVariables.massDiff_antiBLepton_bAntiLepton_.value_, mvaTopJetsVariables);
            
//             this->fillHistograms("dijet_mvaWeightCorrect_step8", mvaTopJetsVariables.mvaWeightCorrect_, mvaTopJetsVariables);
//             if(mvaTopJetsVariables.bestMvaWeightCorrect_>-990.) this->fillHistograms("dijet_bestMvaWeightCorrect_step8", mvaTopJetsVariables.bestMvaWeightCorrect_, mvaTopJetsVariables);
//             this->fillHistograms("dijet_mvaWeightSwapped_step8", mvaTopJetsVariables.mvaWeightSwapped_, mvaTopJetsVariables);
//             if(mvaTopJetsVariables.bestMvaWeightSwapped_>-990.) this->fillHistograms("dijet_bestMvaWeightSwapped_step8", mvaTopJetsVariables.bestMvaWeightSwapped_, mvaTopJetsVariables);
//             
//             this->fillHistograms2D("dijet_mvaWeightCorrectVsSwapped_step8", mvaTopJetsVariables.mvaWeightCorrect_, mvaTopJetsVariables.mvaWeightSwapped_, mvaTopJetsVariables);
//             if(mvaTopJetsVariables.bestMvaWeightCorrect_>-990. && mvaTopJetsVariables.bestMvaWeightSwapped_>-990.)
//                 this->fillHistograms2D("dijet_bestMvaWeightCorrectVsSwapped_step8", mvaTopJetsVariables.bestMvaWeightCorrect_, mvaTopJetsVariables.bestMvaWeightSwapped_, mvaTopJetsVariables);
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












