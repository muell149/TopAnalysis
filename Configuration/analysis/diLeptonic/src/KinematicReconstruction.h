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
};

class KinematicReconstruction {

public:
  KinematicReconstruction(const LV& leptonMinus, const LV& leptonPlus, const VLV *jets, const std::vector<double> *btags, const LV* met);
  KinematicReconstruction(const LV& leptonMinus, const LV& leptonPlus, const VLV *jets, const std::vector<double> *btags, const LV* met, bool mass_loop_on);

int GetNSol()const;
struct_KinematicReconstruction GetSol()const;

private:

//private:
    int nSol;
    struct_KinematicReconstruction sol;

  };


#endif
