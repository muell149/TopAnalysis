#include <iostream>
#include <cstdlib>

#include "analysisUtils.h"





std::vector<double> ttbar::parametersLV(const VLV& v_lv, const ttbar::LVParameter& parameter)
{
    std::vector<double> v_variable;
    for(const LV& lv : v_lv){
        if(parameter==LVpt) v_variable.push_back(lv.pt());
        else if (parameter==LVeta) v_variable.push_back(lv.eta());
        else{
            std::cerr<<"Error in orderIndices! Lorentz vector parameter is not implemented\n...break\n";
            exit(638);
        }
    }
    return v_variable;
}



void ttbar::orderIndices(int& index1, int& index2, const VLV& v_lv, const ttbar::LVParameter& parameter)
{
    const std::vector<double> v_variable = parametersLV(v_lv, parameter);
    orderIndices(index1, index2, v_variable);
}



void ttbar::orderIndices(std::vector<int>& v_index, const VLV& v_lv, const ttbar::LVParameter& parameter){
    const std::vector<double> v_variable = parametersLV(v_lv, parameter);
    orderIndices(v_index, v_variable);
}



void ttbar::selectIndices(std::vector<int>& v_index, const VLV& v_lv, const ttbar::LVParameter& parameter,
                          const double cutValue, const bool lowerThreshold)
{
    const std::vector<double> v_variable = parametersLV(v_lv, parameter);
    selectIndices(v_index, v_variable, cutValue, lowerThreshold);
}










