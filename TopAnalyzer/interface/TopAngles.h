#ifndef TopAngles_h
#define TopAngles_h

#include <Math/VectorUtil.h>
#include <Math/Boost.h>
#include <Math/GenVector/LorentzVector.h>
#include <iostream>

class TopAngles {

 public:
  /// default constructor 
  /// name convention:
  /// decay channel             semilep.          dilept.             fullhad.
  /// inputVectors1-3: Branch1 (bhad, q  , qbar   blep1, lep1, nu1    bhad1, q, qbar)
  /// inputVectors4-6: Branch2 (blep, lep, nu     blep2, lep2, nu2    bhad2, p, pbar)
  explicit TopAngles(const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> >& inVector1,
		     const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> >& inVector2,
		     const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> >& inVector3,
		     const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> >& inVector4,
		     const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> >& inVector5,
		     const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> >& inVector6);
  /// default destructor
  ~TopAngles(){};

  double ttDetFrame()          const;
  double bbDetFrame()          const;
  double bbTtbarFrame()        const;
  double WWTtbarFrame()        const;
  double tBBranch1TtbarFrame() const;
  double tBBranch2TtbarFrame() const;
  double bWBranch1TtbarFrame() const;
  double bWBranch2TtbarFrame() const;
  double tWBranch1TopInTtbarFrameWInTopFrame() const;
  double tWBranch2TopInTtbarFrameWInTopFrame() const;
  /// specific getter functions for semileptonic decay channel
  double qQbarTopFrame()       const;
  double qQbarDetFrame()       const;
  double blepQTtbarFrame()     const;
  double blepQbarTtbarFrame()  const;
  double bhadQTopFrame()       const;
  double bhadQbarTopFrame()    const;
  double lepBlepTopFrame()     const;
  double lepBlepTtbarFrame()   const;
  double lepBhadTtbarFrame()   const;
  double lepQTtbarFrame()      const;
  double lepQbarTtbarFrame()   const;
  double lepNuTopFrame()       const;
  double nuBlepTopFrame()      const;
  double nuBhadTtbarFrame()    const;
  double nuQTtbarFrame()       const;
  double nuQBarTtbarFrame()    const;
  double lepWlepLepInWFrameWInDetFrame() const;
  double nuWlepNuInWFrameWInDetFrame()   const;
  double qWhadQInWFrameWInDetFrame()     const;
  double qbarWhadQInWFrameWInDetFrame()  const;
  /// specific getter functions for dileptonic decay channel
  double NuNuTtbarFrame()      const;
  double LepLepTtbarFrame()    const;
  double lep1Blep1TopFrame()   const;
  double lep1Blep2TtbarFrame() const;
  double lep2Blep1TtbarFrame() const;
  double lep2Blep2TopFrame()   const;
  double lep1Nu1TopFrame()     const;
  double lep1Nu1DetFrame()     const;
  double lep1Nu2TtbarFrame()   const;
  double lep2Nu1TtbarFrame()   const;
  double lep2Nu2TopFrame()     const;
  double nu1Blep1TopFrame()    const;
  double nu1Blep2TtbarFrame()  const;
  double nu2Blep1TtbarFrame()  const;
  double nu2Blep2TopFrame()    const;
  double lep1InW1FrameW1InDetFrame() const;
  double nu1InW1FrameW1InDetFrame()  const;
  double lep2InW2FrameW2InDetFrame() const;
  double nu2InW2FrameW2InDetFrame()  const;
  /// specific getter functions for all hadronic decay channel
  /// double qQbar()       const; -> implemented in semileptonic decay channel
  double pPbarTopFrame()       const;
  double pQbarTtbarFrame()     const;
  double pQTtbarFrame()        const;
  double pbarQbarTtbarFrame()  const;
  double pbarQTtbarFrame()     const;
  double bhad1QTopFrame()      const;
  double bhad1QbarTopFrame()   const;
  double bhad1PTtbarFrame()    const;
  double bhad1PbarTtbarFrame() const;
  double bhad2QTtbarFrame()    const;
  double bhad2QbarTtbarFrame() const;
  double bhad2PTopFrame()      const;
  double bhad2PbarTopFrame()   const;
  double qInW1FrameW1InDetFrame()    const;
  double qbarInW1FrameW1InDetFrame() const;
  double pInW2FrameW2InDetFrame()    const;
  double pbarInW2FrameW2InDetFrame() const;

 private:
  /// input 4 momentum vectors (ttbar decay products)
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > inputVector1;
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > inputVector2;
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > inputVector3;
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > inputVector4;
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > inputVector5;
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > inputVector6;

  /// reconstructed 4 momentum vectors of the ttbar system
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > W1;
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > W2;
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > top1;
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > top2;
  const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > ttbar;

  /// boost to different reconstructed particle systems
  const ROOT::Math::Boost CoMBoostTtbar;
  const ROOT::Math::Boost CoMBoostTop1;
  const ROOT::Math::Boost CoMBoostTop2;
  const ROOT::Math::Boost CoMBoostW1;
  const ROOT::Math::Boost CoMBoostW2;
};

#endif
