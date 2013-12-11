
#include "MeanSol.h"
// #include <TLegend.h>
// #include <TText.h>
// #include <TStyle.h>
// #include <TF1.h>
// #include <stdio.h>
// #include <iostream>

MeanSol::MeanSol(double topm)
{
    mass_top=topm;
    sum_weight=0;
    max_sum_weight=0;
}

MeanSol::~MeanSol()
{

}
void MeanSol::Clear()
{
    v_top.clear();
    v_topbar.clear();
    v_n.clear();
    v_nbar.clear();
    v_weight.clear();
    sum_weight=0;
    max_sum_weight=0;
}

void MeanSol::Add(TLorentzVector top, TLorentzVector topbar,TLorentzVector n,TLorentzVector nbar,double weight,double mbl_weight)
{
    v_top.push_back(top);
    v_topbar.push_back(topbar);
    v_n.push_back(n);
    v_nbar.push_back(nbar);

    v_weight.push_back(weight);    
    sum_weight = sum_weight + weight;
    max_sum_weight = max_sum_weight + mbl_weight;
}


void MeanSol::Add(TLorentzVector top, TLorentzVector topbar,TLorentzVector n,TLorentzVector nbar,double weight)
{
    v_top.push_back(top);
    v_topbar.push_back(topbar);
    v_n.push_back(n);
    v_nbar.push_back(nbar);

    v_weight.push_back(weight);    
    sum_weight = sum_weight + weight;
    max_sum_weight = max_sum_weight +weight;
}

void MeanSol::GetMeanVect(TLorentzVector& lv,vector<TLorentzVector> vlv,double mass)
{
    double px_sum=0;
    double py_sum=0;
    double pz_sum=0;
    double px=0;
    double py=0;
    double pz=0;

    for(int i=0;i<((int)vlv.size());i++)
    {
          px_sum=px_sum+v_weight.at(i)*vlv.at(i).Px();
          py_sum=py_sum+v_weight.at(i)*vlv.at(i).Py();
          pz_sum=pz_sum+v_weight.at(i)*vlv.at(i).Pz();          
    }

      px=px_sum/sum_weight;
      py=py_sum/sum_weight;
      pz=pz_sum/sum_weight;
      
      lv.SetXYZM(px,py,pz,mass);

}


void MeanSol::GetMeanSol(TLorentzVector& top, TLorentzVector& topbar, TLorentzVector& n, TLorentzVector& nbar)
{
        GetMeanVect(top,v_top,mass_top);
        GetMeanVect(topbar,v_topbar,mass_top);
        GetMeanVect(n,v_n,0);
        GetMeanVect(nbar,v_nbar,0);
        
}

double MeanSol::GetSumWeight()
{
    return sum_weight; // for 1 weight
//     return max_sum_weight; // for 2 weights
    
}

int MeanSol::GetNsol()
{
    return (int)v_top.size();
}

