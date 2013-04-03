#ifndef JECBASE_H
#define JECBASE_H

#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "mathdefs.h"



namespace ztop{
  // typedef ROOT::Math::PolarLorentzVector<ROOT::Math::PxPyPzE4D<double> > PolarLorentzVector;


  class JECBase{
  public:

    JECBase(){is2012_=true;totalunc_=0;}
    JECBase(const ztop::JECBase &);
    JECBase & operator = (const ztop::JECBase &);
    ~JECBase();

    void setFile(std::string pathToFile, bool quiet=false);
    void setSystematics(std::string); //! up, down, no
    void setIs2012(bool is){is2012_=is; std::cout << "JEC mode changed; set File again!" << std::endl;}

    std::vector<unsigned int> &  sources(){return sources_;}

    void applyJECUncertainties(ztop::PolarLorentzVector &);
    void applyJECUncertainties(ztop::LorentzVector & v){
      ztop::PolarLorentzVector vp;
      vp=v;
      applyJECUncertainties(vp);
      v=vp;
    }

  protected:

    std::string pathToFile_;
    std::vector<JetCorrectionUncertainty*> vsrc_;
    JetCorrectionUncertainty* totalunc_;
    int noupdown_;
    std::vector<unsigned int> sources_;
    bool is2012_;
    void copyFrom(const ztop::JECBase &);

  };

}
#endif
