#include <iostream>
#include <algorithm>
#include <functional>

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



TString Tools::extractSelectionStep(const TString& name)
{
    TString result(name);
    // Remove e.g. things like .root ??
    result = Tools::stepFragmentByToken(result, ".");
    // Further separation by "_" to find string containing step
    result = Tools::stepFragmentByToken(result, "_");
    //std::cout<<"The extracted selection step is (step/histogram name): "<<result<<" / "<<name<<std::endl;
    return result;
}



TString Tools::extractCategoryBin(const TString& name)
{
    TString result(name);
    // Remove e.g. things like .root ??
    result = Tools::binFragmentByToken(result, ".");
    // Further separation by "_" to find string containing step
    result = Tools::binFragmentByToken(result, "_");
    //std::cout<<"The extracted category bin is (bin/histogram name): "<<result<<" / "<<name<<std::endl;
    return result;
}



TString Tools::extractSelectionStepAndCategoryBin(const TString& name)
{
    const TString step(extractSelectionStep(name));
    const TString bin(extractCategoryBin(name));
    const TString result(bin==name ? step : step+"_"+bin);
    return result;
}



TString Tools::stepFragmentByToken(const TString& nameFragment, const TString& token)
{
    TString result(nameFragment);
    TObjArray* a_nameFragment = TString(nameFragment).Tokenize(token);
    bool alreadyFound(false);
    for(Int_t iFragment= 0; iFragment < a_nameFragment->GetEntriesFast(); ++iFragment){
        const TString& fragment = a_nameFragment->At(iFragment)->GetName();
        if(fragment.Contains("step")){
            if(alreadyFound && result!=fragment){
                std::cerr<<"Ambiguous string, histogram name contains \"step\" more than once in fragment, and is ambiguous: "<<nameFragment
                         <<"\n...cannot extract selection step, so break\n";
                exit(33);
            }
            alreadyFound = true;
            result = fragment;
        }
    }
    return result;
}



TString Tools::binFragmentByToken(const TString& nameFragment, const TString& token)
{
    TString result(nameFragment);
    TObjArray* a_nameFragment = TString(nameFragment).Tokenize(token);
    bool alreadyFound(false);
    for(Int_t iFragment= 0; iFragment < a_nameFragment->GetEntriesFast(); ++iFragment){
        const TString& fragment = a_nameFragment->At(iFragment)->GetName();
        if(fragment == "bin"){
            if(alreadyFound){
                std::cerr<<"Ambiguous string, file name contains \"bin\" more than once in fragment: "<<nameFragment
                         <<"\n...cannot extract bin, so break\n";
                exit(34);
            }
            alreadyFound = true;
            const TString binNo = a_nameFragment->At(iFragment+1)->GetName();
            result = fragment+binNo;
        }
    }
    return result;
}



std::function<bool(const std::string& s)> Tools::makeStringCheck(const std::vector<std::string> v_string)
{
    return [v_string](const std::string& test){
        return std::find(begin(v_string), end(v_string), test) != end(v_string);
    };
}


