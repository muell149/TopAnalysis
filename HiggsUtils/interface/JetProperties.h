#ifndef JetProperties_h
#define JetProperties_h



#include <vector>

#include "DataFormats/Math/interface/LorentzVector.h"




class JetProperties{

public:

    JetProperties();
    
    JetProperties(const double& jetChargeGlobalPtWeighted, const double& jetChargeRelativePtWeighted,
                  const int& jetAssociatedPartonPdgId, const math::PtEtaPhiMLorentzVectorD& jetAssociatedParton);
    
    JetProperties(const JetProperties& jetProperties);
    
    double jetChargeGlobalPtWeighted()const;
    double jetChargeRelativePtWeighted()const;
    int jetAssociatedPartonPdgId()const;
    math::PtEtaPhiMLorentzVectorD jetAssociatedParton()const;
    
private:
    
    double jetChargeGlobalPtWeighted_;
    double jetChargeRelativePtWeighted_;
    int jetAssociatedPartonPdgId_;
    math::PtEtaPhiMLorentzVectorD jetAssociatedParton_;
};







#endif // JetProperties_h





