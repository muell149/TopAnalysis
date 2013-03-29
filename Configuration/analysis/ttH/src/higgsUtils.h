#ifndef higgsUtils_h
#define higgsUtils_h

#include <functional>
#include <vector>
#include <string>

class TH1;
class TString;





namespace Tools{
    
    /// Apply a flat (i.e. constant) weight to a histogram
    void applyFlatWeight(TH1* hist, const double weight);
    
    
    
    /// Get from a TString the selection step of pattern "step*"
    TString extractSelectionStep(const TString& filename);
    
    /// Helper function to get the fragment containing the selection step (needs to be separated by "_" or ".")
    TString stepFragmentByToken(const TString& filename, const TString& token);
    
    
    
    /// Template function to order two indices by comparison operator for the two elements of a vector
    /// corresponding to the indices of a given variable
    /// Result is: index1 > index2
    template<class T> void orderIndices(int& index1, int& index2, const std::vector<T>& v_variable);
    
    /// Template function to order vector of indices by comparison operator for the two elements of a vector
    /// corresponding to the indices of a given variable
    /// Result is: index1 > index2 > ... > indexN
    template<class T> void orderIndices(std::vector<int>& v_index, const std::vector<T>& v_variable);
    
    
    
    /**
     * Helper function to create a function which checks if a string found is in the
     * passed vector of string.
     * 
     * @param v_string a vector of allowed strings (std::string)
     * @return a function taking a std::string and returning a bool
     */
    std::function<bool(const std::string &s)> makeStringCheck(const std::vector<std::string> v_string);
}



template<class T> void Tools::orderIndices(int& index1, int& index2, const std::vector<T>& v_variable)
{
    const T& variable1 = v_variable.at(index1);
    const T& variable2 = v_variable.at(index2);
    if(variable1<variable2){const int tmpIndex2 = index1;
        index1 = index2;
        index2 = tmpIndex2;
    }
}



template<class T> void Tools::orderIndices(std::vector<int>& v_index, const std::vector<T>& v_variable)
{
    std::vector<int> v_indexResult;
    for(std::vector<int>::const_iterator i_index2 = v_index.begin(); i_index2 != v_index.end(); ++i_index2){
        const int index2(*i_index2);
        if(i_index2 == v_index.begin()){
            v_indexResult.push_back(index2);
            continue;
        }
        const T& variable2 = v_variable.at(index2);
        
        bool isInserted(false);
        for(std::vector<int>::iterator i_index1 = v_indexResult.begin(); i_index1 != v_indexResult.end(); ++i_index1){
            const T& variable1 = v_variable.at(*i_index1);
            if(variable1<variable2){
                v_indexResult.insert(i_index1, index2);
                isInserted = true;
                break;
            }
        }
        if(!isInserted) v_indexResult.push_back(index2);
    }
    v_index = v_indexResult;
}






#endif //higgsUtils_h







