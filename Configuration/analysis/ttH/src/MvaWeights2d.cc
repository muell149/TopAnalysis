#include <iostream>

#include <TFile.h>
#include <TString.h>
#include <TSelectorList.h>
#include <TIterator.h>
#include <TObject.h>
#include <TObjArray.h>
#include <TObjString.h>
#include <TH1.h>
#include <TH1D.h>
#include <TH2.h>
#include <TH2D.h>

#include "MvaWeights2d.h"
#include "MvaReader.h"
#include "mvaSetup.h"
#include "mvaStructs.h"
#include "higgsUtils.h"





MvaWeights2d::MvaWeights2d(const std::map<TString, std::vector<MvaTopJetsVariables> >& m_stepMvaVariables,
                                       const char* mvaWeightFileDirectory,
                                       const std::vector<mvaSetup::MvaSet>& v_mvaSet,
                                       const bool separationPowerPlots):
selectorList_(0),
m_stepMvaVariables_(m_stepMvaVariables),
plotExclusively_(separationPowerPlots),
mvaWeightFileDirectory_(mvaWeightFileDirectory),
v_mvaSet_(v_mvaSet)
{
    std::cout<<"--- Beginning setting up MVA weights histograms\n";
    std::cout<<"=== Finishing setting up MVA weights histograms\n\n";
}



void MvaWeights2d::clear()
{
    selectorList_ = 0;

    for(auto stepHistograms : m_stepHistograms_){
        stepHistograms.second.m_histogram_.clear();
    }
    m_stepHistograms_.clear();
}



void MvaWeights2d::plotVariables(const std::string& f_savename)
{
    // Output file
    TFile outputFile(f_savename.c_str(),"RECREATE");
    std::cout<<"\nOutput file for MVA 2D weights: "<<f_savename<<"\n";

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



void MvaWeights2d::plotVariables(TSelectorList* output)
{
    std::cout<<"--- Beginning MVA weights histograms\n";

    // Set pointer to output, so that histograms are owned by it
    selectorList_ = output;

    // Loop over all MVA sets and plot all histograms
    for(const mvaSetup::MvaSet& mvaSet : v_mvaSet_){
        this->plotStep(mvaSet);
    }

    std::cout<<"=== Finishing MVA weights histograms\n\n";
}



void MvaWeights2d::plotStep(const mvaSetup::MvaSet& mvaSet)
{
    const TString step = tth::stepName(mvaSet.step_, mvaSet.v_category_);
    const std::vector<MvaTopJetsVariables>& v_mvaTopJetsVariables(m_stepMvaVariables_.at(step));
    const std::vector<mvaSetup::MvaConfig>& v_mvaConfigCorrect = mvaSet.v_mvaConfigCorrect_;
    const std::vector<mvaSetup::MvaConfig>& v_mvaConfigSwapped = mvaSet.v_mvaConfigSwapped_;

    TObjArray* trainingsCorrect = new TObjArray();
    TObjArray* trainingsSwapped = new TObjArray();




    constexpr const char* methodPrefixCorrect = "correct";
    constexpr const char* methodPrefixSwapped = "swapped";
    constexpr const char* fileAppendix = ".weights.xml";
    TString name;
    constexpr const char* prefix = "";

    // Loop over all trainings for correct and swapped combinations
    for(const mvaSetup::MvaConfig& mvaConfigCorrect : v_mvaConfigCorrect){
        const TString methodTitleCorrect(mvaConfigCorrect.methodAppendix_);
        TString fileNameCorrect(mvaWeightFileDirectory_);
        fileNameCorrect.Append(methodPrefixCorrect);
        fileNameCorrect.Append(step).Append("_").Append(methodTitleCorrect).Append(fileAppendix);
        MvaReader weightsCorrect(fileNameCorrect);
        const std::vector<float> v_mvaWeightsCorrect = weightsCorrect.mvaWeights(v_mvaTopJetsVariables);

        // Creating the name of the correct training
        TString trainingName(methodPrefixCorrect);
        trainingName.Append(step).Append("_").Append(methodTitleCorrect);
        trainingsCorrect->Add(new TObjString(trainingName));

        for(const mvaSetup::MvaConfig& mvaConfigSwapped : v_mvaConfigSwapped){
            const TString methodTitleSwapped(mvaConfigSwapped.methodAppendix_);
            TString fileNameSwapped(mvaWeightFileDirectory_);
            fileNameSwapped.Append(methodPrefixSwapped);
            fileNameSwapped.Append(step).Append("_").Append(methodTitleSwapped).Append(fileAppendix);
            MvaReader weightsSwapped(fileNameSwapped);
            const std::vector<float> v_mvaWeightsSwapped = weightsSwapped.mvaWeights(v_mvaTopJetsVariables);

            // Preventing adding the same swapped training multiple times
            if((size_t)trainingsCorrect->GetEntries() < 2) {
                // Creating the name of the swapped training
                TString trainingName(methodPrefixSwapped);
                trainingName.Append(step).Append("_").Append(methodTitleSwapped);
                trainingsSwapped->Add(new TObjString(trainingName));
            }

            // Book histograms
            std::map<TString, TH1*>& m_histogram = m_stepHistograms_[step].m_histogram_;
            name = "_";
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

    trainingsCorrect->Write("trainingsCorrect", TObject::kSingleKey);
    trainingsSwapped->Write("trainingsSwapped", TObject::kSingleKey);
    delete trainingsCorrect;
    delete trainingsSwapped;

}



void MvaWeights2d::bookHistosInclExcl(std::map<TString, TH1*>& m_histogram, const TString& prefix, const TString& step,
                                        const TString& name, const TString& title,
                                        const int& nBinX, const double& xMin, const double& xMax)
{
    const TString correct("correct");
    const TString swapped("swapped");
    const TString wrong("wrong");

    if(!plotExclusively_){
        m_histogram[name] = this->store(new TH1D(prefix+step+name, title, nBinX, xMin, xMax));
    }
    else{
        m_histogram[correct+name] = this->store(new TH1D(correct+prefix+step+name, title, nBinX, xMin, xMax));
        m_histogram[swapped+name] = this->store(new TH1D(swapped+prefix+step+name, title, nBinX, xMin, xMax));
        m_histogram[wrong+name] = this->store(new TH1D(wrong+prefix+step+name, title, nBinX, xMin, xMax));
    }
}



void MvaWeights2d::bookHistosInclExcl2D(std::map<TString, TH1*>& m_histogram, const TString& prefix, const TString& step,
                                              const TString& name, const TString& title,
                                              const int& nBinX, const double& xMin, const double& xMax,
                                              const int& nBinY, const double& yMin, const double& yMax)
{
    const TString correct("correct");
    const TString swapped("swapped");
    const TString wrong("wrong");
    const TString combined("combined");

    if(!plotExclusively_){
        m_histogram[name] = this->store(new TH2D(prefix+step+name, title, nBinX, xMin, xMax, nBinY, yMin, yMax));
    }
    else{
        m_histogram[combined+name] = this->store(new TH2D(combined+prefix+step+name, title, nBinX, xMin, xMax, nBinY, yMin, yMax));
        m_histogram[correct+name] = this->store(new TH2D(correct+prefix+step+name, title, nBinX, xMin, xMax, nBinY, yMin, yMax));
        m_histogram[swapped+name] = this->store(new TH2D(swapped+prefix+step+name, title, nBinX, xMin, xMax, nBinY, yMin, yMax));
        m_histogram[wrong+name] = this->store(new TH2D(wrong+prefix+step+name, title, nBinX, xMin, xMax, nBinY, yMin, yMax));
    }
}



void MvaWeights2d::fillHistosInclExcl(std::map<TString, TH1*>& m_histogram, const TString& name,
                                        const double& variable,
                                        const MvaTopJetsVariables& mvaTopJetsVariables, const double& weight)
{
    const TString correct("correct");
    const TString swapped("swapped");
    const TString wrong("wrong");

    if(!plotExclusively_){
        m_histogram[name]->Fill(variable, weight);
    }
    else{
        if(mvaTopJetsVariables.correctCombination_.value_) m_histogram[correct+name]->Fill(variable, weight);
        else if(mvaTopJetsVariables.swappedCombination_.value_) m_histogram[swapped+name]->Fill(variable, weight);
        else m_histogram[wrong+name]->Fill(variable, weight);
    }
}



void MvaWeights2d::fillHistosInclExcl2D(std::map<TString, TH1*>& m_histogram, const TString& name,
                                              const float& variable1, const float& variable2,
                                              const MvaTopJetsVariables& mvaTopJetsVariables, const double& weight)
{
    const TString correct("correct");
    const TString swapped("swapped");
    const TString wrong("wrong");
    const TString correctAndSwapped("combined");

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















