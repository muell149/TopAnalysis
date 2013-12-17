#ifndef MATHDEFS_H
#define MATHDEFS_H

#ifndef __CINT__
#include "DataFormats/Math/interface/LorentzVector.h"
#else
#include <Math/LorentzVector.h>
#include <Math/PtEtaPhiM4D.h>
#endif

namespace ztop {
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzVector;
typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > PolarLorentzVector;

}

#endif
