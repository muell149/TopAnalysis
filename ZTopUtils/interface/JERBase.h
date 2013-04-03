#ifndef JERBASE_H
#define JERBASE_H

#include "mathdefs.h"
#include <vector>
#include "../interface/miscUtils.h"
#include <algorithm>
#include <iostream>

// following recommendation https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetResolution;   https://twiki.cern.ch/twiki/bin/viewauth/CMS/TWikiTopRefSyst

namespace ztop{

  // typedef ROOT::Math::PolarLorentzVector<ROOT::Math::PxPyPzE4D<double> > PolarLorentzVector;

  class JERBase{
  public:
    JERBase(){setSystematics("def");}
    ~JERBase(){}

    void setResolutionEtaRanges(std::vector<double> ranges){resranges_=ranges;}
    void setResolutionFactors(std::vector<double> factors){resfactors_=factors;}

    void setSystematics(std::string type);

    void correctP4(ztop::PolarLorentzVector & ,const ztop::PolarLorentzVector & );
    void correctP4(ztop::LorentzVector & v,const ztop::LorentzVector & vv){
      ztop::PolarLorentzVector vp,vvp;
      vp=v;
      vvp=vv;
      correctP4(vp,vvp);
      v=vp;
    }

  protected:

    std::vector<double> resranges_;
    std::vector<double> resfactors_;

  };
}
#endif
