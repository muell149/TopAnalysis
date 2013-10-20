#ifndef KinematicReconstruction_h
#define KinematicReconstruction_h

#include <TLorentzVector.h>
#include <Math/LorentzVector.h>
#include <Math/PtEtaPhiM4D.h>
#include <vector>
#include <TMath.h>
#include <TF2.h>
#include <Rtypes.h>
#include <iostream>
#include <stdio.h>

#include <TH1F.h>

#include "classesFwd.h"


//typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > LV;

struct struct_KinematicReconstruction {
    TLorentzVector lp, lm;
    TLorentzVector jetB, jetBbar;
    size_t jetB_index, jetBbar_index;
    TLorentzVector met;
    TLorentzVector Wplus, Wminus;
    TLorentzVector top, topBar;
    TLorentzVector neutrino, neutrinoBar;
    TLorentzVector ttbar;
    double recMtop;
    double weight;
    int ntags;
    void angle_rot(double alpha, double e, TLorentzVector jet, TLorentzVector & jet_sm);
};

class KinematicReconstruction {

public:

  KinematicReconstruction();
//  KinematicReconstruction(const LV& leptonMinus, const LV& leptonPlus, const VLV *jets, const std::vector<double> *btags, const LV* met);
  
int GetNSol()const;
struct_KinematicReconstruction GetSol()const;

void loadData();
void kinReco(const LV& leptonMinus, const LV& leptonPlus, const VLV *jets, const std::vector<double> *btags, const LV* met);
void kinReco(const LV& leptonMinus, const LV& leptonPlus, const VLV *jets, const std::vector<double> *btags, const LV* met, bool mass_loop_on);

private:

//private:
    int nSol;
    struct_KinematicReconstruction sol;
    
//     // W mass
    TH1F * h_wmass;
// 
//     // jet resolution
    TH1F * h_jetAngleRes;
    TH1F * h_jetEres;
//        
//     //lepton resolution
    TH1F * h_lepAngleRes;
    TH1F * h_lepEres;
// 
//     //MET resolution
//     double ptBins[14];
    std::vector<double> ptBins;
    TH1F * h_metAngleRes[13];
    TH1F * h_metPtres[13];
// 
    TH1F *h_nwcuts;
// 
// //  E 1d bins
        TH1F* hvE[6];
// 
// // mbl
        TH1F *h_mbl_w;

  };


#endif
