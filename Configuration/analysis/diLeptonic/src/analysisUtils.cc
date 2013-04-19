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
            std::cerr<<"Error in parametersLV! Lorentz vector parameter is not implemented\n...break\n";
            exit(638);
        }
    }
    return v_variable;
}



void ttbar::orderIndices(int& index1, int& index2, const VLV& v_lv, const ttbar::LVParameter& parameter, const bool absoluteValue)
{
    const std::vector<double> v_variable = parametersLV(v_lv, parameter);
    orderIndices(index1, index2, v_variable, absoluteValue);
}



void ttbar::orderIndices(std::vector<int>& v_index, const VLV& v_lv, const ttbar::LVParameter& parameter, const bool absoluteValue)
{
    const std::vector<double> v_variable = parametersLV(v_lv, parameter);
    orderIndices(v_index, v_variable, absoluteValue);
}



void ttbar::selectIndices(std::vector<int>& v_index, const VLV& v_lv, const ttbar::LVParameter& parameter,
                          const double cutValue, const bool lowerThreshold)
{
    const std::vector<double> v_variable = parametersLV(v_lv, parameter);
    selectIndices(v_index, v_variable, cutValue, lowerThreshold);
}



void ttbar::orderLV(LV& lv1, LV& lv2, const LV& inputLv1, const LV& inputLv2, const ttbar::LVParameter& parameter, const bool absoluteValue)
{
    double variable1;
    double variable2;
    if(parameter == LVpt){
        variable1 = inputLv1.pt();
        variable2 = inputLv2.pt();
    }
    else if(parameter == LVeta){
        variable1 = inputLv1.eta();
        variable2 = inputLv2.eta();
    }
    else{
        std::cerr<<"Error in orderLV! Lorentz vector parameter is not implemented\n...break\n";
        exit(639);
    }
    
    if(absoluteValue){
        variable1 = std::abs(variable1);
        variable2 = std::abs(variable2);
    }
    
    if (variable1 > variable2) {
        lv1 = inputLv1;
        lv2 = inputLv2;
    } else {
        lv1 = inputLv2;
        lv2 = inputLv1;
    }
}










