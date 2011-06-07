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


## collections below are added for summer 2011 e + jets ttbar analyses
## see also: https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopLeptonPlusJetsRefSel_el
##           https://twiki.cern.ch/twiki/bin/view/CMS/SimpleCutBasedEleID
from TopAnalysis.TopFilter.sequences.ElectronVertexDistanceSelector_cfi import *

## collection of allowed looser electrons (as long as they pass the Z veto when combined with goodElectrons)
looseElectronsEJ       = selectedPatElectrons.clone( src = 'selectedPatElectrons',
                                                     cut = 'test_bit( electronID(\"simpleEleId95cIso\"), 1 ) &'
                                                           'et       > 20   &'
                                                           'abs(eta) <  2.5 &'
                                                           '( abs(superCluster.eta) < 1.4442   |'
                                                           '  abs(superCluster.eta) > 1.5660 ) &'
                                                           '(dr03TkSumPt+dr03EcalRecHitSumEt+dr03HcalTowerSumEt)/et < 1.0'
                                                   )

## intermediate collection
tightElectronsEJ       = selectedPatElectrons.clone( src = 'vertexSelectedElectrons',                                      # | PV.z() - elec.vertex().z() | < 1.0 (need to be created)
                                                     cut = 'et > 30. &'
                                                           'abs(eta) <  2.1  &'
                                                           '( abs(superCluster.eta) < 1.4442   |'
                                                           '  abs(superCluster.eta) > 1.5660 ) &'
                                                           'abs(dB)  <  0.02 &'                                            # NB: needs "process.selectedPatElectrons.usePV = false" for PAT tuple production
                                                           'test_bit( electronID(\"simpleEleId70cIso\"), 1 ) &'
                                                           '(dr03TkSumPt+dr03EcalRecHitSumEt+dr03HcalTowerSumEt)/et < 0.2'
                                                   ) 

## intermediate collection
unconvTightElectronsEJ = selectedPatElectrons.clone( src = 'tightElectronsEJ',
                                                     cut = 'gsfTrack.trackerExpectedHitsInner.numberOfHits = 0' 
                                                   )

## final selection
goodElectronsEJ        = selectedPatElectrons.clone( src = 'unconvTightElectronsEJ',
                                                     cut = 'abs(convDcot) > 0.02 &'
                                                           'abs(convDist) > 0.02' 
                                                   )

##
## N-1 selections
##
noEtTightElectronsEJ   = selectedPatElectrons.clone( src = 'vertexSelectedElectrons', 
                                                     cut = #'et > 30. &'
                                                           'abs(eta) <  2.1  &'
                                                           '( abs(superCluster.eta) < 1.4442   |'
                                                           '  abs(superCluster.eta) > 1.5660 ) &'
                                                           'abs(dB)  <  0.02 &'
                                                           'test_bit( electronID(\"simpleEleId70cIso\"), 1 ) &'
                                                           '(dr03TkSumPt+dr03EcalRecHitSumEt+dr03HcalTowerSumEt)/et < 0.2 &'
                                                           'gsfTrack.trackerExpectedHitsInner.numberOfHits = 0 &' 
                                                           'abs(convDcot) > 0.02 &'
                                                           'abs(convDist) > 0.02' 
                                                   )

noEtaTightElectronsEJ  = selectedPatElectrons.clone( src = 'vertexSelectedElectrons', 
                                                     cut = 'et > 30. &'
                                                           #'abs(eta) <  2.1  &'
                                                           '( abs(superCluster.eta) < 1.4442   |'
                                                           '  abs(superCluster.eta) > 1.5660 ) &'
                                                           'abs(dB)  <  0.02 &'
                                                           'test_bit( electronID(\"simpleEleId70cIso\"), 1 ) &'
                                                           '(dr03TkSumPt+dr03EcalRecHitSumEt+dr03HcalTowerSumEt)/et < 0.2 &'
                                                           'gsfTrack.trackerExpectedHitsInner.numberOfHits = 0 &' 
                                                           'abs(convDcot) > 0.02 &'
                                                           'abs(convDist) > 0.02' 
                                                   )

noSCTightElectronsEJ   = selectedPatElectrons.clone( src = 'vertexSelectedElectrons', 
                                                     cut = 'et > 30. &'
                                                           'abs(eta) <  2.1  &'
                                                           #'( abs(superCluster.eta) < 1.4442   |'
                                                           #'  abs(superCluster.eta) > 1.5660 ) &'
                                                           'abs(dB)  <  0.02 &'
                                                           'test_bit( electronID(\"simpleEleId70cIso\"), 1 ) &'
                                                           '(dr03TkSumPt+dr03EcalRecHitSumEt+dr03HcalTowerSumEt)/et < 0.2 &'
                                                           'gsfTrack.trackerExpectedHitsInner.numberOfHits = 0 &' 
                                                           'abs(convDcot) > 0.02 &'
                                                           'abs(convDist) > 0.02' 
                                                   )

nodBTightElectronsEJ   = selectedPatElectrons.clone( src = 'vertexSelectedElectrons', 
                                                     cut = 'et > 30. &'
                                                           'abs(eta) <  2.1  &'
                                                           '( abs(superCluster.eta) < 1.4442   |'
                                                           '  abs(superCluster.eta) > 1.5660 ) &'
                                                           #'abs(dB)  <  0.02 &'
                                                           'test_bit( electronID(\"simpleEleId70cIso\"), 1 ) &'
                                                           '(dr03TkSumPt+dr03EcalRecHitSumEt+dr03HcalTowerSumEt)/et < 0.2 &'
                                                           'gsfTrack.trackerExpectedHitsInner.numberOfHits = 0 &' 
                                                           'abs(convDcot) > 0.02 &'
                                                           'abs(convDist) > 0.02' 
                                                   )

noIDTightElectronsEJ   = selectedPatElectrons.clone( src = 'vertexSelectedElectrons', 
                                                     cut = 'et > 30. &'
                                                           'abs(eta) <  2.1  &'
                                                           '( abs(superCluster.eta) < 1.4442   |'
                                                           '  abs(superCluster.eta) > 1.5660 ) &'
                                                           'abs(dB)  <  0.02 &'
                                                           #'test_bit( electronID(\"simpleEleId70cIso\"), 1 ) &'
                                                           '(dr03TkSumPt+dr03EcalRecHitSumEt+dr03HcalTowerSumEt)/et < 0.2 &'
                                                           'gsfTrack.trackerExpectedHitsInner.numberOfHits = 0 &' 
                                                           'abs(convDcot) > 0.02 &'
                                                           'abs(convDist) > 0.02' 
                                                   )

noIsoTightElectronsEJ  = selectedPatElectrons.clone( src = 'vertexSelectedElectrons', 
                                                     cut = 'et > 30. &'
                                                           'abs(eta) <  2.1  &'
                                                           '( abs(superCluster.eta) < 1.4442   |'
                                                           '  abs(superCluster.eta) > 1.5660 ) &'
                                                           'abs(dB)  <  0.02 &'
                                                           'test_bit( electronID(\"simpleEleId70cIso\"), 1 ) &'
                                                           #'(dr03TkSumPt+dr03EcalRecHitSumEt+dr03HcalTowerSumEt)/et < 0.2'
                                                           'gsfTrack.trackerExpectedHitsInner.numberOfHits = 0 &' 
                                                           'abs(convDcot) > 0.02 &'
                                                           'abs(convDist) > 0.02' 
                                                   )

noHitsTightElectronsEJ = selectedPatElectrons.clone( src = 'vertexSelectedElectrons', 
                                                     cut = 'et > 30. &'
                                                           'abs(eta) <  2.1  &'
                                                           '( abs(superCluster.eta) < 1.4442   |'
                                                           '  abs(superCluster.eta) > 1.5660 ) &'
                                                           'abs(dB)  <  0.02 &'
                                                           'test_bit( electronID(\"simpleEleId70cIso\"), 1 ) &'
                                                           '(dr03TkSumPt+dr03EcalRecHitSumEt+dr03HcalTowerSumEt)/et < 0.2 &'
                                                           #'gsfTrack.trackerExpectedHitsInner.numberOfHits = 0' 
                                                           'abs(convDcot) > 0.02 &'
                                                           'abs(convDist) > 0.02' 
                                                   )

noDcotTightElectronsEJ = selectedPatElectrons.clone( src = 'vertexSelectedElectrons', 
                                                     cut = 'et > 30. &'
                                                           'abs(eta) <  2.1  &'
                                                           '( abs(superCluster.eta) < 1.4442   |'
                                                           '  abs(superCluster.eta) > 1.5660 ) &'
                                                           'abs(dB)  <  0.02 &'
                                                           'test_bit( electronID(\"simpleEleId70cIso\"), 1 ) &'
                                                           '(dr03TkSumPt+dr03EcalRecHitSumEt+dr03HcalTowerSumEt)/et < 0.2 &'
                                                           'gsfTrack.trackerExpectedHitsInner.numberOfHits = 0 &' 
                                                           #'abs(convDcot) > 0.02 &'
                                                           'abs(convDist) > 0.02' 
                                                   )

noDistTightElectronsEJ = selectedPatElectrons.clone( src = 'vertexSelectedElectrons', 
                                                     cut = 'et > 30. &'
                                                           'abs(eta) <  2.1  &'
                                                           '( abs(superCluster.eta) < 1.4442   |'
                                                           '  abs(superCluster.eta) > 1.5660 ) &'
                                                           'abs(dB)  <  0.02 &'
                                                           'test_bit( electronID(\"simpleEleId70cIso\"), 1 ) &'
                                                           '(dr03TkSumPt+dr03EcalRecHitSumEt+dr03HcalTowerSumEt)/et < 0.2 &'
                                                           'gsfTrack.trackerExpectedHitsInner.numberOfHits = 0 &' 
                                                           'abs(convDcot) > 0.02'
                                                           #'abs(convDist) > 0.02' 
                                                   )

## collection of the N-1 collections
selectNMinusOneElectrons = cms.Sequence( noEtTightElectronsEJ    *
                                         noEtaTightElectronsEJ   *
                                         noSCTightElectronsEJ    *
                                         nodBTightElectronsEJ    *
                                         noIDTightElectronsEJ    *
                                         noIsoTightElectronsEJ   *
                                         noHitsTightElectronsEJ  *
                                         noDcotTightElectronsEJ  *
                                         noDistTightElectronsEJ 
                                       )

