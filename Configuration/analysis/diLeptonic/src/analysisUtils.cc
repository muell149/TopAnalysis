#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstdio>

#include <TLorentzVector.h>

#include "analysisUtils.h"
#include "classes.h"






// --- Several conversion functions -------------------------------------------------------------------------------------

void ttbar::LVtod4(const LV& lv, double* d)
{
    d[0] = lv.E();
    d[1] = lv.Px();
    d[2] = lv.Py();
    d[3] = lv.Pz();
}



std::string ttbar::d2s(const double& d)
{
    char result[100];
    if(std::abs(d) < 5) {
        std::sprintf(result, "%.3f", d);
        std::string s = std::string(result);
        while (s.length() > 0 && s[s.length()-1] == '0') s.erase(s.end()-1);
        if (s.length() > 0 && s[s.length()-1] == '.') s.erase(s.end()-1);
        return s;
    }
    else {
        std::sprintf(result, "%.0f", d);
        return std::string(result);
    }
}



const TLorentzVector ttbar::LVtoTLV(const LV& lv)
{
    return TLorentzVector(lv.X(), lv.Y(), lv.Z(), lv.T());
}



const LV ttbar::TLVtoLV(const TLorentzVector& lv)
{
    LV result; 
    result.SetXYZT(lv.X(), lv.Y(), lv.Z(), lv.T());
    return result;
}







// --- Functions concerning the treatment of indices of vectors (for working with data stored in nTuple branches) -------------

std::vector<double> ttbar::parametersLV(const VLV& v_lv, const ttbar::LVParameter& parameter)
{
    std::vector<double> v_variable;
    for(const LV& lv : v_lv){
        if(parameter == LVpt) v_variable.push_back(lv.pt());
        else if (parameter == LVeta) v_variable.push_back(lv.eta());
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



int ttbar::extremumIndex(const VLV& v_lv, const ttbar::LVParameter& parameter, const bool maximumValue)
{
    const std::vector<double> v_variable = parametersLV(v_lv, parameter);
    return extremumIndex(v_variable, maximumValue);
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









