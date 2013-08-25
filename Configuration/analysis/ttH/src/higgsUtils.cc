#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <utility>
#include <sstream>
#include <algorithm>

#include <TObjArray.h>
#include <TString.h>
#include <Rtypes.h>

#include "higgsUtils.h"
#include "../../diLeptonic/src/RootFileReader.h"





std::vector<std::pair<TString, TString> > tth::nameStepPairs(const char* filename,
                                                             const char* objectNameFragment,
                                                             const std::vector<TString>& selectedSteps)
{
    std::vector<std::pair<TString, TString> > result;
    std::stringstream ss_step;
    std::stringstream ss_unselected;
    
    // Search for all steps
    RootFileReader* fileReader(RootFileReader::getInstance());
    const std::vector<TString>& v_treeName = fileReader->findObjects(filename, objectNameFragment, false);
    for(std::vector<TString>::const_iterator i_objectName = v_treeName.begin(); i_objectName != v_treeName.end(); ++i_objectName){
        const TString& step = tth::extractSelectionStepAndJetCategory(*i_objectName);
        
        // Reject steps in case only selected steps should be chosen
        if(selectedSteps.size() && std::find(selectedSteps.begin(), selectedSteps.end(), step) == selectedSteps.end()){
            ss_unselected<<step<<", ";
            continue;
        }
        
        // Add selection steps
        ss_step<<step<<", ";
        result.push_back(std::make_pair(*i_objectName, step));
    }
    
    std::cout<<"Found chosen selection steps:\n"<<ss_step.str()<<std::endl;
    if(selectedSteps.size() && ss_unselected.str()!="") std::cout<<"Found rejected selection steps:\n"<<ss_unselected.str()<<std::endl;
    return result;
}



TString tth::stepName(const TString& stepShort, const int& category)
{
    std::ostringstream result;
    result<<"_step"<<stepShort;
    if(category>=0){
        result<<"_cate"<<category;
    }
    return result.str().c_str();
}



TString tth::extractSelectionStep(const TString& name)
{
    TString result(name);
    // Remove e.g. things like .root ??
    result = helper::searchFragmentByToken(result, "step", ".");
    // Further separation by "_" to find string containing step
    result = helper::searchFragmentByToken(result, "step", "_");
    //std::cout<<"The extracted selection step is (step/histogram name): "<<result<<" / "<<name<<std::endl;
    return result;
}



TString tth::extractJetCategory(const TString& name)
{
    TString result(name);
    // Remove e.g. things like .root ??
    result = helper::searchFragmentByToken(result, "cate", ".");
    // Further separation by "_" to find string containing step
    result = helper::searchFragmentByToken(result, "cate", "_");
    //std::cout<<"The extracted category bin is (bin/histogram name): "<<result<<" / "<<name<<std::endl;
    return result;
}



TString tth::extractSelectionStepAndJetCategory(const TString& name)
{
    const TString step(extractSelectionStep(name));
    const TString cate(extractJetCategory(name));
    const TString result = step+cate;
    return result;
}



TString tth::helper::searchFragmentByToken(const TString& name, const TString& searchPattern, const TString& token)
{
    TString result;
    TObjArray* a_nameFragment = TString(name).Tokenize(token);
    bool alreadyFound(false);
    for(Int_t iFragment= 0; iFragment < a_nameFragment->GetEntriesFast(); ++iFragment){
        const TString& fragment = a_nameFragment->At(iFragment)->GetName();
        if(fragment.Contains(searchPattern)){
            if(alreadyFound){
                std::cerr<<"ERROR in searchFragmentByToken()! Ambiguous string, name contains search pattern \""<<searchPattern
                         <<"\" in more than one fragment: "<<name
                         <<"\n...cannot extract fragment, so break\n";
                exit(33);
            }
            alreadyFound = true;
            result = "_" + fragment;
        }
    }
    return result;
}







