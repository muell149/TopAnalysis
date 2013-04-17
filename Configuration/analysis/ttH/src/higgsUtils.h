#ifndef higgsUtils_h
#define higgsUtils_h

#include <iostream>
#include <cstdlib>
#include <functional>
#include <vector>
#include <string>

#include <TSelectorList.h>

class TH1;
class TString;





namespace Tools{
    
    /// Apply a flat (i.e. constant) weight to a histogram
    void applyFlatWeight(TH1* hist, const double weight);
    
    
    
    /// Get from a TString the selection step of pattern "step*"
    TString extractSelectionStep(const TString& filename);
    
    /// Helper function to get the fragment containing the selection step (needs to be separated by "_" or ".")
    TString stepFragmentByToken(const TString& filename, const TString& token);
    
    
    
    /// Store the object in the given selectorList and return it
    template<class T> T* store(T* obj, TSelectorList* selectorList);
    
    
    
    /**
     * Helper function to create a function which checks if a string found is in the
     * passed vector of string.
     * 
     * @param v_string a vector of allowed strings (std::string)
     * @return a function taking a std::string and returning a bool
     */
    #ifndef __CINT__
    std::function<bool(const std::string &s)> makeStringCheck(const std::vector<std::string> v_string);
    #endif
}






template<class T> T* Tools::store(T* obj, TSelectorList* selectorList)
{
    if(!selectorList){
        std::cerr<<"ERROR in function store()!\n"
                 <<"Selector list does not exist, so cannot store object with name: "<<obj->GetName()
                 <<"\n...break\n"<<std::endl;
        exit(73);
    }
    selectorList->Add(obj);
    return obj;
}





#endif //higgsUtils_h







