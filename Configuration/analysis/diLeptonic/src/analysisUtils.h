#ifndef analysisUtils_h
#define analysisUtils_h

#include <vector>

#include "classes.h"







namespace ttbar{
    
    /// Setting up a vector with all indices corresonding to its size N {0, 1, 2, ..., N-1}
    template<class T> std::vector<int> initialiseIndices(const std::vector<T>& v_variable);
    
    
    
    /// Template function to order two indices by comparison operator for the two elements of a vector
    /// corresponding to the indices of a given variable
    /// Result is: variable.at(index1) > variable.at(index2)
    template<class T> void orderIndices(int& index1, int& index2, const std::vector<T>& v_variable);
    
    /// Template function to order a vector of indices by comparison operator for the two elements of a vector
    /// corresponding to the indices of a given variable
    /// Result is: variable.at(index1) > variable.at(index2) > ... > variable.at(indexN)
    template<class T> void orderIndices(std::vector<int>& v_index, const std::vector<T>& v_variable);
    
    /// Template function to select from a vector of indices those whose corresponding value in the vector
    /// survive the cut, i.e. variable.at(index) > cutValue (if lowerThreshold==true) or
    /// variable.at(index) < cutValue (if lowerThreshold==false)
    template<class T> void selectIndices(std::vector<int>& v_index, const std::vector<T>& v_variable,
                                         const T& cutValue, const bool lowerThreshold =true);
    
    
    
    /// Possible parameters of a lorentz vector to be used in following tools
    enum LVParameter{LVpt, LVeta};
    
    /// Extract a specific value for each entry of a vector of LVs
    std::vector<double> parametersLV(const VLV& v_lv, const LVParameter& parameter);
    
    /// Function to order two indices by comparison operator for the parameter of the LVs of a vector
    /// corresponding to the indices of a given variable
    /// Result is: LV.at(index1).parameter > LV.at(index2).parameter
    void orderIndices(int& index1, int& index2, const VLV& v_lv, const LVParameter& parameter);
    
    /// Function to order a vector of indices by comparison operator for the parameter of the lorentz vectors of a vector
    /// corresponding to the indices of a given variable
    /// Result is: LV.at(index1).parameter > LV.at(index2).parameter
    void orderIndices(std::vector<int>& v_index, const VLV& v_lv, const LVParameter& parameter);
    
    /// Function to select from a vector of indices those whose corresponding value of a LV parameter
    /// in the vector survive the cut
    void selectIndices(std::vector<int>& v_index, const VLV& v_lv, const LVParameter& parameter,
                                         const double cutValue, const bool lowerThreshold =true);
}




template<class T> std::vector<int> ttbar::initialiseIndices(const std::vector<T>& v_variable)
{
    std::vector<int> result;
    for(size_t i=0; i<v_variable.size(); ++i) result.push_back(i);
    return result;
}



template<class T> void ttbar::orderIndices(int& index1, int& index2, const std::vector<T>& v_variable)
{
    const T& variable1 = v_variable.at(index1);
    const T& variable2 = v_variable.at(index2);
    if(variable1<variable2){
        const int tmpIndex2 = index1;
        index1 = index2;
        index2 = tmpIndex2;
    }
}



template<class T> void ttbar::orderIndices(std::vector<int>& v_index, const std::vector<T>& v_variable)
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





template<class T> void ttbar::selectIndices(std::vector<int>& v_index, const std::vector<T>& v_variable,
                                     const T& cutValue, const bool lowerThreshold)
{
    std::vector<int> result;
    for(const int index : v_index){
        const T& variable(v_variable.at(index));
        if(lowerThreshold){
            if(variable<cutValue) continue;
        }
        else{
            if(variable>cutValue) continue;
        }
        result.push_back(index);
    }
    v_index.clear();
    v_index = result;
}







#endif //analysisUtils_h







