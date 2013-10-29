#include <iostream>

#include <TFile.h>
#include <TString.h>
#include <TSelectorList.h>
#include <TIterator.h>
#include <TObject.h>
#include <TH1.h>
#include <TH1D.h>
#include <TH2.h>
#include <TH2D.h>

#include "MvaWeightsAnalyzer.h"
#include "MvaReader.h"
#include "mvaStructs.h"





MvaWeightsAnalyzer::MvaWeightsAnalyzer(const std::map<TString, std::vector<MvaTopJetsVariables> >& m_stepMvaVariables,
                                       const char* mvaWeightFileDirectory,
                                       const std::vector<MvaFactory::MvaSet>& v_mvaSetCorrect,
                                       const std::vector<MvaFactory::MvaSet>& v_mvaSetSwapped,
                                       const bool separationPowerPlots):
selectorList_(0),
m_stepMvaVariables_(m_stepMvaVariables),
plotExclusively_(separationPowerPlots),
mvaWeightFileDirectory_(mvaWeightFileDirectory),
v_mvaSetCorrect_(v_mvaSetCorrect),
v_mvaSetSwapped_(v_mvaSetSwapped)
{
    std::cout<<"--- Beginning setting up MVA weights histograms\n";
    std::cout<<"=== Finishing setting up MVA weights histograms\n\n";
}



void MvaWeightsAnalyzer::clear()
{
    selectorList_ = 0;
    
    for(auto stepHistograms : m_stepHistograms_){
        stepHistograms.second.m_histogram_.clear();
    }
    m_stepHistograms_.clear();
}



void MvaWeightsAnalyzer::plotVariables(const std::string& f_savename)
{
    // Output file
    TFile outputFile(f_savename.c_str(),"RECREATE");
    std::cout<<"\nOutput file for MVA input control plots: "<<f_savename<<"\n";
    
    // Produce MVA input control plots and store them in output
    TSelectorList* output = new TSelectorList();
    this->plotVariables(output);
    
    // Write file and cleanup
    TIterator* it = output->MakeIterator();
    while(TObject* obj = it->Next()){
        obj->Write();
    }
    outputFile.Close();
    output->SetOwner();
    output->Clear();
}



void MvaWeightsAnalyzer::plotVariables(TSelectorList* output)
{
    std::cout<<"--- Beginning MVA weights histograms\n";
    
    // Set pointer to output, so that histograms are owned by it
    selectorList_ = output;
    
    // Loop over steps and plot all histograms
    for(const auto& stepMvaVariables : m_stepMvaVariables_){
        const TString& step(stepMvaVariables.first);
        const std::vector<MvaTopJetsVariables>& v_mvaTopJetsVariables(stepMvaVariables.second);
        this->plotStep(step, v_mvaTopJetsVariables);
    }
    
    std::cout<<"=== Finishing MVA weights histograms\n\n";
}



void MvaWeightsAnalyzer::plotStep(const TString& step, const std::vector<MvaTopJetsVariables>& v_mvaTopJetsVariables)
{    
    const std::vector<MvaFactory::MvaSet> v_selectedSetCorrect = MvaFactory::selectSets(v_mvaSetCorrect_, step);
    const std::vector<MvaFactory::MvaSet> v_selectedSetSwapped = MvaFactory::selectSets(v_mvaSetSwapped_, step);
    if(!v_selectedSetCorrect.size() && !v_selectedSetSwapped.size()){
        std::cerr<<"ERROR in plotStep()! Defined step/category has no definitions of MVA sets: "<<step
        <<"\n...break\n"<<std::endl;
        exit(139);
    }
    
    
    // To produce 2D histograms, correct AND swapped trainings must have taken place
    if(!v_selectedSetCorrect.size() || !v_selectedSetSwapped.size()) return;
    
    // Loop over all trainings for correct and swapped combinations applied for specific step
    constexpr const char* methodPrefixCorrect = "correct";
    constexpr const char* methodPrefixSwapped = "swapped";
    constexpr const char* fileAppendix = ".weights.xml";
    TString name;
    constexpr const char* prefix = "";
    for(const MvaFactory::MvaSet& selectedSetCorrect : v_selectedSetCorrect){
        for(const MvaFactory::MvaConfig& mvaConfigCorrect : selectedSetCorrect.v_mvaConfig_){
            const TString methodTitleCorrect(mvaConfigCorrect.methodAppendix_);
            TString fileNameCorrect(mvaWeightFileDirectory_);
            fileNameCorrect.Append(methodPrefixCorrect);
            fileNameCorrect.Append(step).Append("_").Append(methodTitleCorrect).Append(fileAppendix);
            MvaReader weightsCorrect(fileNameCorrect, {});
            const std::vector<float> v_mvaWeightsCorrect = weightsCorrect.mvaWeights(v_mvaTopJetsVariables);
            
            for(const MvaFactory::MvaSet& selectedSetSwapped : v_selectedSetSwapped){
                for(const MvaFactory::MvaConfig& mvaConfigSwapped : selectedSetSwapped.v_mvaConfig_){
                    const TString methodTitleSwapped(mvaConfigSwapped.methodAppendix_);
                    TString fileNameSwapped(mvaWeightFileDirectory_);
                    fileNameSwapped.Append(methodPrefixSwapped);
                    fileNameSwapped.Append(step).Append("_").Append(methodTitleSwapped).Append(fileAppendix);
                    MvaReader weightsSwapped(fileNameSwapped, {});
                    const std::vector<float> v_mvaWeightsSwapped = weightsSwapped.mvaWeights(v_mvaTopJetsVariables);
                    
                    // Book histograms
                    std::map<TString, TH1*>& m_histogram = m_stepHistograms_[step].m_histogram_;
                    name = "";
                    name.Append(methodTitleCorrect).Append("_").Append(methodTitleSwapped);
                    this->bookHistosInclExcl2D(m_histogram, prefix, step, name, name+";w_{MVA}^{correct};w_{MVA}^{swapped}", 200, -2., 2., 200, -2., 2.);
                    
                    // Fill histograms
                    for(size_t iWeight = 0; iWeight < v_mvaWeightsCorrect.size(); ++iWeight){
                        const MvaTopJetsVariables& mvaTopJetsVariables = v_mvaTopJetsVariables.at(iWeight);
                        const double weight = mvaTopJetsVariables.eventWeight_.value_;
                        const float mvaWeightCorrect = v_mvaWeightsCorrect.at(iWeight);
                        const float mvaWeightSwapped = v_mvaWeightsSwapped.at(iWeight);
                        this->fillHistosInclExcl2D(m_histogram, name, mvaWeightCorrect, mvaWeightSwapped, mvaTopJetsVariables, weight);
                    }
                }
            }
        }
    }
}



void MvaWeightsAnalyzer::bookHistosInclExcl(std::map<TString, TH1*>& m_histogram, const TString& prefix, const TString& step,
                                        const TString& name, const TString& title,
                                        const int& nBinX, const double& xMin, const double& xMax)
{
    const TString correct("correct_");
    const TString swapped("swapped_");
    const TString wrong("wrong_");
    
    if(!plotExclusively_){
        m_histogram[name] = this->store(new TH1D(prefix+name+step, title, nBinX, xMin, xMax));
    }
    else{
        m_histogram[correct+name] = this->store(new TH1D(correct+prefix+name+step, title, nBinX, xMin, xMax));
        m_histogram[swapped+name] = this->store(new TH1D(swapped+prefix+name+step, title, nBinX, xMin, xMax));
        m_histogram[wrong+name] = this->store(new TH1D(wrong+prefix+name+step, title, nBinX, xMin, xMax));
    }
}



void MvaWeightsAnalyzer::bookHistosInclExcl2D(std::map<TString, TH1*>& m_histogram, const TString& prefix, const TString& step,
                                              const TString& name, const TString& title,
                                              const int& nBinX, const double& xMin, const double& xMax,
                                              const int& nBinY, const double& yMin, const double& yMax)
{
    const TString correct("correct_");
    const TString swapped("swapped_");
    const TString wrong("wrong_");
    const TString correctAndSwapped("correctAndSwapped_");
    
    if(!plotExclusively_){
        m_histogram[name] = this->store(new TH2D(prefix+name+step, title, nBinX, xMin, xMax, nBinY, yMin, yMax));
    }
    else{
        m_histogram[correctAndSwapped+name] = this->store(new TH2D(correctAndSwapped+prefix+name+step, title, nBinX, xMin, xMax, nBinY, yMin, yMax));
        m_histogram[correct+name] = this->store(new TH2D(correct+prefix+name+step, title, nBinX, xMin, xMax, nBinY, yMin, yMax));
        m_histogram[swapped+name] = this->store(new TH2D(swapped+prefix+name+step, title, nBinX, xMin, xMax, nBinY, yMin, yMax));
        m_histogram[wrong+name] = this->store(new TH2D(wrong+prefix+name+step, title, nBinX, xMin, xMax, nBinY, yMin, yMax));
    }
}



void MvaWeightsAnalyzer::fillHistosInclExcl(std::map<TString, TH1*>& m_histogram, const TString& name,
                                        const double& variable,
                                        const MvaTopJetsVariables& mvaTopJetsVariables, const double& weight)
{
    const TString correct("correct_");
    const TString swapped("swapped_");
    const TString wrong("wrong_");
    
    if(!plotExclusively_){
        m_histogram[name]->Fill(variable, weight);
    }
    else{
        if(mvaTopJetsVariables.correctCombination_.value_) m_histogram[correct+name]->Fill(variable, weight);
        else if(mvaTopJetsVariables.swappedCombination_.value_) m_histogram[swapped+name]->Fill(variable, weight);
        else m_histogram[wrong+name]->Fill(variable, weight);
    }
}



void MvaWeightsAnalyzer::fillHistosInclExcl2D(std::map<TString, TH1*>& m_histogram, const TString& name,
                                              const float& variable1, const float& variable2,
                                              const MvaTopJetsVariables& mvaTopJetsVariables, const double& weight)
{
    const TString correct("correct_");
    const TString swapped("swapped_");
    const TString wrong("wrong_");
    const TString correctAndSwapped("correctAndSwapped_");
    
    if(!plotExclusively_){
        ((TH2*)m_histogram[name])->Fill(variable1, variable2, weight);
    }
    else{
        if(mvaTopJetsVariables.correctCombination_.value_){
            ((TH2*)m_histogram[correct+name])->Fill(variable1, variable2, weight);
            ((TH2*)m_histogram[correctAndSwapped+name])->Fill(variable1, variable2, weight);
        }
        else if(mvaTopJetsVariables.swappedCombination_.value_){
            ((TH2*)m_histogram[swapped+name])->Fill(variable1, variable2, weight);
            ((TH2*)m_histogram[correctAndSwapped+name])->Fill(variable1, variable2, weight);
        }
        else ((TH2*)m_histogram[wrong+name])->Fill(variable1, variable2, weight);
    }
}















