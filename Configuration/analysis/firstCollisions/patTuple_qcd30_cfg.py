execfile("TopAnalysis/Configuration/analysis/firstCollisions/patTuple_cfg.py")

## correct global tag
process.GlobalTag.globaltag = 'START3X_V26::All'

## tighter jet cuts
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
process.goodJets.cut = ('abs(eta) < 2.6 & pt > 30. &'
                        '0.01 < emEnergyFraction &'
                        '0.99 > emEnergyFraction &'
                        'jetID.fHPD < 0.98 &'
                        'jetID.n90Hits > 1'
                        )

## different output file name
process.out.fileName = 'patTuple_qcd30.root'
