import FWCore.ParameterSet.Config as cms

## muon selector
from PhysicsTools.PatAlgos.selectionLayer1.electronSelector_cfi import *

## ---
##    setup electron quality studies
## ---

## getting started
idOnlyElectrons   = selectedLayer1Electrons.clone(src = 'selectedLayer1Electrons', 
                                                  cut = 'electronID(\"eidRobustTight\") > 0.99'                                                
                                                  )
centralElectrons  = selectedLayer1Electrons.clone(src = 'selectedLayer1Electrons', 
                                                  cut = 'abs(eta) < 2.4'
                                                  )
highPtElectrons   = selectedLayer1Electrons.clone(src = 'selectedLayer1Electrons', 
                                                  cut = 'abs(eta) < 2.4 & et > 20.'
                                                  )

## electron Id on top of kinematics
tightElectrons    = selectedLayer1Electrons.clone(src = 'selectedLayer1Electrons', 
                                                  cut = 'abs(eta) < 2.4 & et > 20.' 
                                                  '& electronID(\"eidRobustTight\") > 0.99'                                                
                                                  )

## isolated electrons
isolatedElectrons = selectedLayer1Electrons.clone(src = 'selectedLayer1Electrons', 
                                                  cut = 'abs(eta) < 2.4 & et > 20.' 
                                                  '& electronID(\"eidRobustTight\") > 0.99'                                                
                                                  '& (trackIso+caloIso)/et <  0.1'
                                                  )

