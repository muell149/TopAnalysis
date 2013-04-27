#include <iostream>
#include <cstdlib>

#include <TObjArray.h>
#include <TString.h>
#include <Rtypes.h>

#include "higgsUtils.h"





TString tth::extractSelectionStep(const TString& name)
{
    TString result(name);
    // Remove e.g. things like .root ??
    result = helper::stepFragmentByToken(result, ".");
    // Further separation by "_" to find string containing step
    result = helper::stepFragmentByToken(result, "_");
    //std::cout<<"The extracted selection step is (step/histogram name): "<<result<<" / "<<name<<std::endl;
    return result;
}



TString tth::extractCategoryBin(const TString& name)
{
    TString result(name);
    // Remove e.g. things like .root ??
    result = helper::binFragmentByToken(result, ".");
    // Further separation by "_" to find string containing step
    result = helper::binFragmentByToken(result, "_");
    //std::cout<<"The extracted category bin is (bin/histogram name): "<<result<<" / "<<name<<std::endl;
    return result;
}



TString tth::extractSelectionStepAndCategoryBin(const TString& name)
{
    const TString step(extractSelectionStep(name));
    const TString bin(extractCategoryBin(name));
    const TString result(bin==name ? step : step+"_"+bin);
    return result;
}



TString tth::helper::stepFragmentByToken(const TString& nameFragment, const TString& token)
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



TString tth::helper::binFragmentByToken(const TString& nameFragment, const TString& token)
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



