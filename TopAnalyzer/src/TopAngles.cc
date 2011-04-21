#include <TopAnalysis/TopAnalyzer/interface/TopAngles.h>

/// constructor
/// add 4 momentum vectors of the ttbar system
/// add boost to reco particle systems

TopAngles::TopAngles(const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> >& inVector1,
		     const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> >& inVector2,
		     const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> >& inVector3,
		     const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> >& inVector4,
		     const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> >& inVector5,
		     const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> >& inVector6):
  inputVector1(inVector1),
  inputVector2(inVector2),
  inputVector3(inVector3),
  inputVector4(inVector4),
  inputVector5(inVector5),
  inputVector6(inVector6),
  W1(inVector2+inVector3),
  W2(inVector5+inVector6),
  top1(inVector1+inVector2+inVector3),
  top2(inVector4+inVector5+inVector6),
  ttbar(inVector1+inVector2+inVector3+inVector4+inVector5+inVector6),
  CoMBoostTtbar(ttbar.BoostToCM()),
  CoMBoostTop1 (top1.BoostToCM()),
  CoMBoostTop2 (top2.BoostToCM()),
  CoMBoostW1   (W1.BoostToCM()),
  CoMBoostW2   (W2.BoostToCM())
{
}

  /// define getter functions (different for all decay channels)
    /// define common getter functions for all decay channels
    double TopAngles::ttDetFrame()   const{ return ROOT::Math::VectorUtil::Angle(top1,top2);}
    double TopAngles::bbDetFrame()   const{ return ROOT::Math::VectorUtil::Angle(inputVector1,inputVector4);}
    double TopAngles::bbTtbarFrame() const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTtbar(inputVector1), CoMBoostTtbar(inputVector4));}
    double TopAngles::WWTtbarFrame() const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTtbar(W1),CoMBoostTtbar(W2));}
    double TopAngles::tBBranch1TtbarFrame() const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTtbar(top1),CoMBoostTtbar(inputVector1));}
    double TopAngles::tBBranch2TtbarFrame() const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTtbar(top2),CoMBoostTtbar(inputVector4));}
    double TopAngles::bWBranch1TtbarFrame() const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTtbar(W1)  ,CoMBoostTtbar(inputVector1));}
    double TopAngles::bWBranch2TtbarFrame() const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTtbar(W2)  ,CoMBoostTtbar(inputVector4));}
    double TopAngles::tWBranch1TopInTtbarFrameWInTopFrame() const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTtbar(top1),CoMBoostTop1(W1));}
    double TopAngles::tWBranch2TopInTtbarFrameWInTopFrame() const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTtbar(top2),CoMBoostTop2(W2));}
    /// define getter functions for the semileptonic decay channel
    double TopAngles::qQbarTopFrame() const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTop1(inputVector2),CoMBoostTop1(inputVector3));}
    double TopAngles::qQbarDetFrame() const{ return ROOT::Math::VectorUtil::Angle(inputVector2,inputVector3);}
    double TopAngles::blepQTtbarFrame()    const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTtbar(inputVector4),CoMBoostTtbar(inputVector2));}
    double TopAngles::blepQbarTtbarFrame() const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTtbar(inputVector4),CoMBoostTtbar(inputVector3));}
    double TopAngles::bhadQTopFrame()    const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTop1(inputVector1),CoMBoostTop1(inputVector2));}
    double TopAngles::bhadQbarTopFrame() const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTop1(inputVector1),CoMBoostTop1(inputVector3));}
    double TopAngles::lepBlepTopFrame()  const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTop2(inputVector5),CoMBoostTop2(inputVector4));}
    double TopAngles::lepBlepTtbarFrame() const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTtbar(inputVector5),CoMBoostTtbar(inputVector4));}
    double TopAngles::lepBhadTtbarFrame() const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTtbar(inputVector5),CoMBoostTtbar(inputVector1));}
    double TopAngles::lepQTtbarFrame()    const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTtbar(inputVector5),CoMBoostTtbar(inputVector2));}
    double TopAngles::lepQbarTtbarFrame() const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTtbar(inputVector5),CoMBoostTtbar(inputVector3));}
    double TopAngles::lepNuTopFrame()    const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTop2(inputVector5),CoMBoostTop2(inputVector6));}
    double TopAngles::nuBlepTopFrame()   const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTop2(inputVector6),CoMBoostTop2(inputVector4));}
    double TopAngles::nuBhadTtbarFrame() const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTtbar(inputVector6),CoMBoostTtbar(inputVector1));}
    double TopAngles::nuQTtbarFrame()    const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTtbar(inputVector6),CoMBoostTtbar(inputVector2));}
    double TopAngles::nuQBarTtbarFrame() const{ return ROOT::Math::VectorUtil::Angle(CoMBoostTtbar(inputVector6),CoMBoostTtbar(inputVector3));}
    double TopAngles::lepWlepLepInWFrameWInDetFrame() const{ return ROOT::Math::VectorUtil::Angle(CoMBoostW2(inputVector5), W2);}
    double TopAngles::nuWlepNuInWFrameWInDetFrame()   const{ return ROOT::Math::VectorUtil::Angle(CoMBoostW2(inputVector6), W2);}
    double TopAngles::qWhadQInWFrameWInDetFrame()     const{ return ROOT::Math::VectorUtil::Angle(CoMBoostW1(inputVector2), W1);}
    double TopAngles::qbarWhadQInWFrameWInDetFrame()  const{ return ROOT::Math::VectorUtil::Angle(CoMBoostW1(inputVector3), W1);}

    /// specific getter functions for dileptonic decay channel
    /// decay channel             semilep.          dilept.             fullhad.
    /// inputVectors1-3: Branch1 (bhad, q  , qbar   blep1, lep1, nu1    bhad1, q, qbar)
    /// inputVectors4-6: Branch2 (blep, lep, nu     blep2, lep2, nu2    bhad2, p, pbar)
    double TopAngles::NuNuTtbarFrame()      const{return TopAngles::nuQBarTtbarFrame();  }
    double TopAngles::LepLepTtbarFrame()    const{return TopAngles::lepQTtbarFrame();    }
    double TopAngles::lep1Blep1TopFrame()   const{return TopAngles::bhadQTopFrame();     }
    double TopAngles::lep1Blep2TtbarFrame() const{return TopAngles::blepQTtbarFrame();   }
    double TopAngles::lep2Blep1TtbarFrame() const{return TopAngles::lepBhadTtbarFrame(); }
    double TopAngles::lep2Blep2TopFrame()   const{return TopAngles::lepBlepTopFrame();   }
    double TopAngles::lep1Nu1TopFrame()     const{return TopAngles::qQbarTopFrame();     } 
    double TopAngles::lep1Nu1DetFrame()     const{return TopAngles::qQbarDetFrame();     }
    double TopAngles::lep1Nu2TtbarFrame()   const{return TopAngles::nuQTtbarFrame();     }
    double TopAngles::lep2Nu1TtbarFrame()   const{return TopAngles::lepQbarTtbarFrame(); }
    double TopAngles::lep2Nu2TopFrame()     const{return TopAngles::lepNuTopFrame();     }
    double TopAngles::nu1Blep1TopFrame()    const{return TopAngles::bhadQbarTopFrame();  }
    double TopAngles::nu1Blep2TtbarFrame()  const{return TopAngles::blepQbarTtbarFrame();}
    double TopAngles::nu2Blep1TtbarFrame()  const{return TopAngles::nuBhadTtbarFrame();  }
    double TopAngles::nu2Blep2TopFrame()    const{return TopAngles::nuBlepTopFrame();    }
    double TopAngles::lep1InW1FrameW1InDetFrame() const{return TopAngles::qWhadQInWFrameWInDetFrame();    }
    double TopAngles::nu1InW1FrameW1InDetFrame()  const{return TopAngles::qbarWhadQInWFrameWInDetFrame(); }
    double TopAngles::lep2InW2FrameW2InDetFrame() const{return TopAngles::lepWlepLepInWFrameWInDetFrame();}
    double TopAngles::nu2InW2FrameW2InDetFrame()  const{return TopAngles::nuWlepNuInWFrameWInDetFrame();  }

    /// specific getter functions for all hadronic decay channel
    /// decay channel             semilep.          dilept.             fullhad.
    /// inputVectors1-3: Branch1 (bhad, q  , qbar   blep1, lep1, nu1    bhad1, q, qbar)
    /// inputVectors4-6: Branch2 (blep, lep, nu     blep2, lep2, nu2    bhad2, p, pbar)
    double TopAngles::pPbarTopFrame()       const{return TopAngles::lep2Nu2TopFrame();    }
    double TopAngles::pQbarTtbarFrame()     const{return TopAngles::lep2Nu1TtbarFrame();  }
    double TopAngles::pQTtbarFrame()        const{return TopAngles::LepLepTtbarFrame();   }
    double TopAngles::pbarQbarTtbarFrame()  const{return TopAngles::NuNuTtbarFrame();     }
    double TopAngles::pbarQTtbarFrame()     const{return TopAngles::lep1Nu2TtbarFrame();  }
    double TopAngles::bhad1QTopFrame()      const{return TopAngles::lep1Blep1TopFrame();  }
    double TopAngles::bhad1QbarTopFrame()   const{return TopAngles::nu1Blep1TopFrame();   }
    double TopAngles::bhad1PTtbarFrame()    const{return TopAngles::lep2Blep1TtbarFrame();}
    double TopAngles::bhad1PbarTtbarFrame() const{return TopAngles::nu2Blep1TtbarFrame(); }
    double TopAngles::bhad2QTtbarFrame()    const{return TopAngles::lep1Blep2TtbarFrame();}
    double TopAngles::bhad2QbarTtbarFrame() const{return TopAngles::nu1Blep2TtbarFrame(); }
    double TopAngles::bhad2PTopFrame()      const{return TopAngles::lep2Blep2TopFrame();  }
    double TopAngles::bhad2PbarTopFrame()   const{return TopAngles::nu2Blep2TopFrame();}
    double TopAngles::qInW1FrameW1InDetFrame() const{return TopAngles::lep1InW1FrameW1InDetFrame();   }
    double TopAngles::qbarInW1FrameW1InDetFrame() const{return TopAngles::nu1InW1FrameW1InDetFrame(); }
    double TopAngles::pInW2FrameW2InDetFrame()    const{return TopAngles::lep2InW2FrameW2InDetFrame();}
    double TopAngles::pbarInW2FrameW2InDetFrame() const{return TopAngles::nu2InW2FrameW2InDetFrame(); }
