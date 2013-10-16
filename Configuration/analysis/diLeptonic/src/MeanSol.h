#ifndef MeanSol_h
#define MeanSol_h

#include <TLorentzVector.h>
//#include <Math/LorentzVector.h>
//#include <Math/PtEtaPhiM4D.h>

// #include <Rtypes.h>
// #include <TH1.h>
// #include <TH2.h>
// #include <TCanvas.h>

//class TH2D;
//class TH1F;

#include <vector>

using namespace std;

class MeanSol {

public:
    
  MeanSol(double topm);
 ~MeanSol();  
  void Add(TLorentzVector top,TLorentzVector topbar,TLorentzVector n,TLorentzVector nbar, double weight,double mbl_weight);
  void Add(TLorentzVector top,TLorentzVector topbar,TLorentzVector n,TLorentzVector nbar, double weight);
  void GetMeanVect(TLorentzVector& lv,vector<TLorentzVector> vlv,double mass);
  void GetMeanSol(TLorentzVector& top,TLorentzVector& topbar,TLorentzVector& n,TLorentzVector& nbar);
  double GetSumWeight();
  int GetNsol();
  void Clear();
  
  
  
  private:
    vector<TLorentzVector> v_top;
    vector<TLorentzVector> v_topbar;
    vector<TLorentzVector> v_n;
    vector<TLorentzVector> v_nbar;
    
    vector<double> v_weight;
    double sum_weight;  
    double max_sum_weight;

    double mass_top;
    
};

#endif