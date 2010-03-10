import FWCore.ParameterSet.Config as cms

## muon selector
from PhysicsTools.PatAlgos.selectionLayer1.electronSelector_cfi import *

## ---
##    setup electron quality studies
## ---

## getting started
idOnlyElectrons   = selectedPatElectrons.clone(src = 'selectedPatElectrons', 
                                                  cut = 'electronID(\"eidRobustTight\") > 0.99'                                                
                                                  )
centralElectrons  = selectedPatElectrons.clone(src = 'selectedPatElectrons', 
                                                  cut = 'abs(eta) < 2.4'
                                                  )
highPtElectrons   = selectedPatElectrons.clone(src = 'selectedPatElectrons', 
                                                  cut = 'abs(eta) < 2.4 & et > 20.'
                                                  )

## electron Id on top of kinematics
tightElectrons    = selectedPatElectrons.clone(src = 'selectedPatElectrons', 
                                                  cut = 'abs(eta) < 2.4 & et > 20.' 
                                                  '& electronID(\"eidRobustTight\") > 0.99'                                                
                                                  )

## isolated electrons
isolatedElectrons = selectedPatElectrons.clone(src = 'selectedPatElectrons', 
                                                  cut = 'abs(eta) < 2.4 & et > 20.' 
                                                  '& electronID(\"eidRobustTight\") > 0.99'                                                
                                                  '& (trackIso+caloIso)/et <  0.1'
                                                  )

