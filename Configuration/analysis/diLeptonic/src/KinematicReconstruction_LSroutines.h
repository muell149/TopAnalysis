#ifndef KinematicReconstruction_LSroutines_h
#define KinematicReconstruction_LSroutines_h

#include <TLorentzVector.h>
#include <Math/LorentzVector.h>
#include <Math/PtEtaPhiM4D.h>
#include <vector>
#include <TMath.h>
#include <TF2.h>
#include <TH1.h>
#include <TFile.h>
#include <Rtypes.h>
#include <iostream>
#include <stdio.h>
#include "classesFwd.h"


//#include "classesFwd.h"
//typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > LV;

class KinematicReconstruction_LSroutines {

public:
  KinematicReconstruction_LSroutines();
  KinematicReconstruction_LSroutines(double mass_l, double mass_al);
  KinematicReconstruction_LSroutines(double mass_l, double mass_al,double mass_Wp, double mass_Wm, TH1F* hvE[]);
  KinematicReconstruction_LSroutines(double mass_l, double mass_al,double mass_Wp, double mass_Wm, TH1F hneutrino);
  KinematicReconstruction_LSroutines(double mass_l, double mass_al,double mass_Wp, double mass_Wm);
  KinematicReconstruction_LSroutines(double mass_top, double mass_b, double mass_w, double mass_l, double mass_al);
      ~KinematicReconstruction_LSroutines();
  
  void Delete();    
      
      
  void ini(double mass_l, double mass_al,double mass_Wp, double mass_Wm);
    
  void SetConstraints(TLorentzVector LV_al, 
                      TLorentzVector LV_l, 
                      TLorentzVector LV_b, 
                      TLorentzVector LV_bbar,
                      double missPx,
                      double missPy
                     );
  
  void SetConstraints(LV LV_al, 
                      LV LV_l, 
                      LV LV_b, 
                      LV LV_bbar,
                      double missPx,
                      double missPy
                     );
  
  int GetNsol();

  void SetWeightOption(int wo);
  
  struct TopSolution {
        double TopPt;
        double AntiTopPt;
        double NeutrinoPx;
        double AntiNeutrinoPx;
        double ttPt;
        double mTop;
        double mAntiTop;
        double vw;
        double dTS;
        double dR;
        double dN;
        TLorentzVector top;
        TLorentzVector topbar;
        TLorentzVector neutrino;
        TLorentzVector neutrinobar;
        TLorentzVector wp;
        TLorentzVector wm;
        double cos_bTR_top;
        double cos_bbarTR_topbar;
        double cos1;
        double cos2;
        double Mtt;
        double ttpt_top;
        double ttpt_topbar;
        double mbl;
        double mblbar;
        
    };
  std::vector<TopSolution>* GetTtSol();
    
void SetTrueInfo(TLorentzVector LV_Top,TLorentzVector LV_AntiTop,TLorentzVector LV_Neutrino, TLorentzVector LV_AntiNeutrino);
void SortBy(std::string ch);
void Print();
TF1* GetNeutrinoPxF();

private:
    void FilldTS();
    void FilldR();
    void FilldN();
    void SWAPtopSol(TopSolution& sol1, TopSolution& sol2);
    void SortTopSol(std::vector<TopSolution> &v);
    void DoAll(); 
    void TopRec(double sol);
    void FindCoeff(double* koeficienty);
    void quartic_equation(double h0,double h1,double h2,double h3,double h4,std::vector<double>& v);
    void cubic_equation(double a,double b,double c,double d,std::vector<double> &v);
    void quadratic_equation(double a,double b,double c,std::vector<double> &v);
    void linear_equation(double a,double b,std::vector<double> &v);
    int sign(long double ld);
    double Landau2D(double x,double y);
    
  
      //Utility Methods
    double sqr(double x);
    void SWAP(double& realone, double& realtwo);
    
//private:
    int weight_option;   // weight option
    int nSol;
    double coeffs[5];
    std::vector<double> vect_pxv;
    std::vector<TopSolution> ttSol;
    TLorentzVector al;
    TLorentzVector l;
    TLorentzVector b;
    TLorentzVector bbar;
    TLorentzVector top;
    TLorentzVector topbar;
    TLorentzVector neutrino;
    TLorentzVector neutrinobar;
    TLorentzVector w;
    TLorentzVector wbar;
    TLorentzVector tt;
    
    TLorentzVector true_top;
    TLorentzVector true_topbar;
    TLorentzVector true_neutrino;
    TLorentzVector true_neutrinobar;

    TF1 * pol4_neutrinoPx; //("pol4_neutrinoPx","pol4",-100,100);
    
    TH1F hnw_cuts;
    TH1F* hneutrino_E[6];

    double px_miss;
    double py_miss;
  
    double mt;
    double mtbar;
    double mb;
    double mbbar;
    double mw;
    double mwbar;
    double ml;
    double mal;
    double mv;
    double mav;
  
    //TF2 * NeutrinoEventShape;  // ()  30.641000 57.941000 22.344000 57.533000 22.232000
    
   double a1,a2,a3,a4;
   double b1,b2,b3,b4;
   double c22,c21,c20,c11,c10,c00;
   double d22,d21,d20,d11,d10,d00;
   double d0,d1,d2;
   double c0,c1,c2;
    
  };


#endif
