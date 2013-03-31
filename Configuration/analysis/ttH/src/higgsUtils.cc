#include <iostream>
#include <algorithm>

#include <TObjArray.h>
#include <TH1.h>
#include <TString.h>
#include <Rtypes.h>

#include "higgsUtils.h"





void Tools::applyFlatWeight(TH1* hist, const double weight)
{
    if(weight == 0) {std::cout<<"Warning! The weight your applying is 0. This will remove your distribution."<<std::endl;}
    //if(weight >=1e3){std::cout<<"Warning: the weight your applying is >= 1e3. This will enlarge too much your distribution."<<std::endl;}
    hist->Scale(weight);
}



TString Tools::extractSelectionStep(const TString& histogramName)
{
    TString step(histogramName);
    // Remove .root
    step = Tools::stepFragmentByToken(step, ".");
    // Further separation by "_" to find string containing step
    step = Tools::stepFragmentByToken(step, "_");
    //std::cout<<"The extracted selection step is (step/histogram name): "<<step<<" / "<<histogramName<<std::endl;
    return step;
}



TString Tools::stepFragmentByToken(const TString& filenameFragment, const TString& token)
{
    TString stepFragment;
    TObjArray* a_nameFragment = TString(filenameFragment).Tokenize(token);
    bool stepAlreadyFound(false);
    for(Int_t iFragment= 0; iFragment < a_nameFragment->GetEntriesFast(); ++iFragment){
        const TString& fragment = a_nameFragment->At(iFragment)->GetName();
        if(fragment.Contains("step")){
            if(stepAlreadyFound){
                std::cerr<<"Ambiguous string, file name contains \"step\" more than once in fragment: "<<filenameFragment
                         <<"\n...cannot extract selection step, so break\n";
                exit(33);
            }
            stepAlreadyFound = true;
            stepFragment = fragment;
        }
    }
    return stepFragment;
}



std::function<bool(const std::string &s)> Tools::makeStringCheck(const std::vector<std::string> v_string)
{
    return [v_string](const std::string &test){
        return std::find(begin(v_string), end(v_string), test) != end(v_string);
    };
}


