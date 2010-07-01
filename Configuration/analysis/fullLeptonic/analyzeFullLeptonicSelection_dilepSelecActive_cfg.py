import FWCore.ParameterSet.Config as cms

# analyse muon quantities
process = cms.Process("Selection")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10000     #                                   !!!

##
## comment for genTag begin
##



##
## comment for genTag end
##


## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    '/store/user/rwolf/ttbar09/patTuple_all_0_ttbar09.root',
      '/store/user/rwolf/ttbar09/patTuple_all_1_ttbar09.root',
        '/store/user/rwolf/ttbar09/patTuple_all_2_ttbar09.root',
	  '/store/user/rwolf/ttbar09/patTuple_all_3_ttbar09.root',
	    '/store/user/rwolf/ttbar09/patTuple_all_4_ttbar09.root',
	      '/store/user/rwolf/ttbar09/patTuple_all_5_ttbar09.root',
	        '/store/user/rwolf/ttbar09/patTuple_all_6_ttbar09.root',
	          '/store/user/rwolf/ttbar09/patTuple_all_7_ttbar09.root',
	            '/store/user/rwolf/ttbar09/patTuple_all_8_ttbar09.root',
	              '/store/user/rwolf/ttbar09/patTuple_all_9_ttbar09.root'
			       
			  
##      '/store/user/henderle/OctEx/Wmunu/PATtuple_1.root',
## 	'/store/user/henderle/OctEx/Wmunu/PATtuple_2.root',
## 	  '/store/user/henderle/OctEx/Wmunu/PATtuple_3.root',
## 	    '/store/user/henderle/OctEx/Wmunu/PATtuple_4.root',
## 	      '/store/user/henderle/OctEx/Wmunu/PATtuple_5.root',
## 	        '/store/user/henderle/OctEx/Wmunu/PATtuple_6.root',
## 		  '/store/user/henderle/OctEx/Wmunu/PATtuple_7.root',
## 		    '/store/user/henderle/OctEx/Wmunu/PATtuple_8.root',
## 		      '/store/user/henderle/OctEx/Wmunu/PATtuple_9.root',
## 			'/store/user/henderle/OctEx/Wmunu/PATtuple_10.root'
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(200000)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeFullLeptonicSelection.root')
)


## std sequence to produce the ttGenEvt
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## filter for different ttbar decay channels
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")
process.ttDecaySelection.allowedTopDecays.decayBranchA.muon     = True
process.ttDecaySelection.allowedTopDecays.decayBranchB.electron = True

## filter for differnt final states on generator level
process.load("TopAnalysis.TopUtils.GenFinalStateSelector_cfi")

## number of expected electrons in the final state
process.genFinalStateSelector.elecs  = -1
#process.genFinalStateSelector.invert = True


## high level trigger filter
process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")


## top decay channel analyzer
process.load("Validation.Generator.TopDecayChannelDQM_cfi")


process.load("DQMServices.Core.DQM_cfg")
process.load("DQMServices.Components.DQMEnvironment_cfi")
process.DQM.collectorHost = ''

process.dqmSaver.workflow = cms.untracked.string('/Test/TopDecayChannelDQM/DataSet')


## sequence with filter for decay channel
process.genFilterSequence = cms.Sequence(process.makeGenEvt *
                                         ## process.ttDecaySelection
                                         process.genFinalStateSelector
                                         )

## sequence with filter for trigger selection
process.recFilterSequence = cms.Sequence(process.hltEle15
                                         )

## ## sequence with filter for optimal electrons --> jet analysis
## from PhysicsTools.PatAlgos.selectionLayer1.electronCountFilter_cfi import *
## process.electronSelection  = countLayer1Electrons.clone(src   = 'electronCF3',
##                                                     minNumber = 1,
##                                                     maxNumber = 1
##                                                     )

## ## sequence with filter for optimal jets  --> muon analysis
## from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *
## process.jetSelection1  = countLayer1Jets.clone(src = 'jetsCF2',  
##                                               minNumber = 2
##                                               )

## ## sequence with filter for optimal jets  --> muon analysis
## from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *
## process.jetSelection2  = countLayer1Jets.clone(src = 'jetsCF3HighPur',  
##                                               minNumber = 1
##                                               )


## ---
##    efficiency calculation event counting cuts
## ---

## sequence with filter for optimal electrons 
from PhysicsTools.PatAlgos.selectionLayer1.electronCountFilter_cfi import *
process.elecSelIdPtEta  = countLayer1Electrons.clone(src   = 'electronCF2',
                                                    minNumber = 1,
                                                    maxNumber = 1
                                                    )
## sequence with filter for optimal electrons 
from PhysicsTools.PatAlgos.selectionLayer1.electronCountFilter_cfi import *
process.elecSelRelIso  = countLayer1Electrons.clone(src   = 'electronCF3',
                                                    minNumber = 1,
                                                    maxNumber = 1
                                                    )



## sequence with filter for optimal jets  
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *
process.jetSelPtEtaEmf  = countLayer1Jets.clone(src = 'jetsCF2',  
                                                minNumber = 2
                                                )
## sequence with filter for optimal jets  
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *
process.jetSelBtag  = countLayer1Jets.clone(src = 'jetsCF3HighPur',  
                                            minNumber = 1
                                            )

## 
process.selectedLayer1MET = cms.EDFilter("PATMETSelector",
    src = cms.InputTag("layer1METs"),
    cut = cms.string('et>=30.')
)

process.selectEventsWithMET = cms.EDFilter("PATCandViewCountFilter",
    minNumber = cms.uint32(1),
    maxNumber = cms.uint32(999999),
    src = cms.InputTag("selectedLayer1MET")
)

## sequence with filter for optimal muon  
from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *
process.muonSelStAl  = countLayer1Muons.clone(src = 'muonCF1StAl',  
                                              minNumber = 1                                            
                                              )

## sequence with filter for optimal muon  
from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *
process.muonSelComb  = countLayer1Muons.clone(src = 'muonCF1Comb',  
                                              minNumber = 1                                            
                                              )


## sequence with filter for optimal muon  
from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *
process.muonSelTrkiso  = countLayer1Muons.clone(src = 'combTrkiso',          #                                  !!!
                                              minNumber = 1                                            
                                              )
process.muonSelReliso  = countLayer1Muons.clone(src = 'combReliso',          #                                  !!!
                                              minNumber = 1                                            
                                              )
process.muonSelCaliso  = countLayer1Muons.clone(src = 'combCaliso',           #                                 !!!
                                              minNumber = 1                                            
                                              )



## sequence with filter for optimal muon  
from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *
process.muonSelEcalHcal  = countLayer1Muons.clone(src = 'combEcalHcal',  
                                              minNumber = 1                                            
                                              )
## sequence with filter for optimal muon  
from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *
##process.muonSelTrackMu  = countLayer1Muons.clone(src = 'combValhitChi2Trksig',  
##                                              minNumber = 1                                            
##                                              )

process.muonSelValhit  = countLayer1Muons.clone(src = 'combValhit',  
                                                minNumber = 1                                            
                                                )

process.muonSelChi2  = countLayer1Muons.clone(src = 'combChi2',  
                                              minNumber = 1                                            
                                              )

process.muonSelTrksig  = countLayer1Muons.clone(src = 'combTrksig',  
                                                minNumber = 1                                            
                                                )


## ---
##    define selection
## ---

## electron selection
process.load("TopAnalysis.TopFilter.sequences.electronSelection_cff")

from TopAnalysis.TopFilter.sequences.electronSelection_cff import centralElectrons
process.centralElectrons = centralElectrons

from TopAnalysis.TopFilter.sequences.electronSelection_cff import highPtElectrons
process.highPtElectrons = highPtElectrons

from TopAnalysis.TopFilter.sequences.electronSelection_cff import tightElectrons
process.tightElectrons = tightElectrons



## jet selection
process.load("TopAnalysis.TopFilter.sequences.jetSelection_cff")

from TopAnalysis.TopFilter.sequences.jetSelection_cff import reliableJets
process.reliableJets = reliableJets

from TopAnalysis.TopFilter.sequences.jetSelection_cff import centralJets
process.centralJets = centralJets

from TopAnalysis.TopFilter.sequences.jetSelection_cff import goodJets
process.goodJets = goodJets



## muon selection
process.load("TopAnalysis.TopFilter.sequences.muonSelection_cff")

from TopAnalysis.TopFilter.sequences.muonSelection_cff import standAloneMuons
process.standAloneMuons = standAloneMuons


## ---
##    define monitoring
## ---


## ---
## electron kinematics analyzer
## ---
process.load("TopAnalysis.TopFilter.sequences.electronSelection_cff")
process.load("TopAnalysis.TopAnalyzer.ElectronKinematics_cfi")



## CUT FLOW   electrons
from PhysicsTools.PatAlgos.selectionLayer1.electronSelector_cfi import *

process.electronCF2 = selectedLayer1Electrons.clone(src = 'selectedLayer1Electrons', 
                                                    cut = 'electronID(\"eidRobustTight\") > 0.99 &'
                                                          'abs(eta) < 1.5 & et > 20.'
                                                   )
process.electronCF3 = selectedLayer1Electrons.clone(src = 'electronCF2', 
                                                    cut = '(trackIso+caloIso)/et <  0.1'
                                                    )

## 1. leading electron before any cut (selLay1): cut flow analysis                           CF0
process.eleKin_1st_CF0_selLay1 = process.analyzeElectronKinematics.clone(src = 'selectedLayer1Electrons',
                                                                         analyze = cms.PSet(index = cms.int32(0))
                                                                         )
## 1. leading electron with 1.cut (electronId: robust tight): cut flow analysis              CF1
process.eleKin_1st_CF1_roTigh  = process.analyzeElectronKinematics.clone(src = 'idOnlyElectrons',
                                                                         analyze = cms.PSet(index = cms.int32(0))
                                                                         )
## 1. leading electron with 2.cut (robust tight & abs(eta)<1.5 & et>20 ): cut flow analysis  CF2                    recap electron before isolation
process.eleKin_1st_CF2_ptEta   = process.analyzeElectronKinematics.clone(src = 'electronCF2',
                                                                         analyze = cms.PSet(index = cms.int32(0))
                                                                         )
## 1. leading electron after with 3. cut (rob. tight & abs(eta)<1.5 & et>20 & relIso<0.1 ):  CF3                    recap electron after isolation
process.eleKin_1st_CF3_relIso  = process.analyzeElectronKinematics.clone(src = 'electronCF3',
                                                                         analyze = cms.PSet(index = cms.int32(0))
                                                                         )

## define sequence
process.monitorElectronKinematics = cms.Sequence(process.eleKin_1st_CF0_selLay1     +
                                                 process.eleKin_1st_CF1_roTigh      +
                                                 process.eleKin_1st_CF2_ptEta       +
                                                 process.eleKin_1st_CF3_relIso     
                                                 )

### clones for after all cuts (aac)

## 1. leading electron before any cut (selLay1): cut flow analysis                           CF0
process.eleKin_1st_CF0_selLay1_aac = process.eleKin_1st_CF0_selLay1.clone()


## 1. leading electron with 1.cut (electronId: robust tight): cut flow analysis              CF1
process.eleKin_1st_CF1_roTigh_aac  = process.eleKin_1st_CF1_roTigh.clone()


## 1. leading electron with 2.cut (robust tight & abs(eta)<1.5 & et>20 ): cut flow analysis  CF2                    recap electron before isolation
process.eleKin_1st_CF2_ptEta_aac   = process.eleKin_1st_CF2_ptEta.clone()


## 1. leading electron after with 3. cut (rob. tight & abs(eta)<1.5 & et>20 & relIso<0.1 ):  CF3                    recap electron after isolation
process.eleKin_1st_CF3_relIso_aac  = process.eleKin_1st_CF3_relIso.clone()



## define sequence:  clones for after all cuts (aac
process.monitorElectronKinematics_aac = cms.Sequence(process.eleKin_1st_CF0_selLay1_aac     +
                                                     process.eleKin_1st_CF1_roTigh_aac      +
                                                     process.eleKin_1st_CF2_ptEta_aac       +
                                                     process.eleKin_1st_CF3_relIso_aac     
                                                     )


## ---
## electron quality analyzer
## ---
process.load("TopAnalysis.TopAnalyzer.ElectronQuality_cfi")


## 1. lead. electron with no restriction (selectedLayer1)  CF0
process.eleID_1st_CF0   = process.analyzeElectronQuality.clone (src = 'selectedLayer1Electrons',
                                                                analyze = cms.PSet(index = cms.int32(0))
                                                                )
## 1. lead. electron after restriction in electronID       CF1
process.eleID_1st_CF1   = process.analyzeElectronQuality.clone (src = 'idOnlyElectrons',
                                                                analyze = cms.PSet(index = cms.int32(0))
                                                                )

## 1. lead. electron after with restriction in electronID  &  eta and pt 
process.eleID_1st_CF2   = process.analyzeElectronQuality.clone (src = 'electronCF2',
                                                                analyze = cms.PSet(index = cms.int32(0))
                                                                )
## 1. lead. electron with restriction in electronID  &  eta and pt  &  rel.isolation
process.eleID_1st_CF3    = process.analyzeElectronQuality.clone (src = 'electronCF3',
                                                                 analyze = cms.PSet(index = cms.int32(0))
                                                                 )
## define sequence
process.monitorElectronQuality = cms.Sequence(process.eleID_1st_CF0    +
                                              process.eleID_1st_CF1    +
                                              process.eleID_1st_CF2    +
                                              process.eleID_1st_CF3   
                                              )


## ---
## electron quality analyzer  aac
## ---

## 1. lead. electron with no restriction (selectedLayer1)  CF0
process.eleID_1st_CF0_aac   =  process.eleID_1st_CF0.clone()


## 1. lead. electron after restriction in electronID       CF1
process.eleID_1st_CF1_aac   =  process.eleID_1st_CF1.clone()


## 1. lead. electron after with restriction in electronID  &  eta and pt 
process.eleID_1st_CF2_aac   =  process.eleID_1st_CF2.clone()


## 1. lead. electron with restriction in electronID  &  eta and pt  &  rel.isolation
process.eleID_1st_CF3_aac    =  process.eleID_1st_CF3.clone()


## define sequence
process.monitorElectronQuality_aac = cms.Sequence(process.eleID_1st_CF0_aac    +
                                                  process.eleID_1st_CF1_aac    +
                                                  process.eleID_1st_CF2_aac    +
                                                  process.eleID_1st_CF3_aac   
                                                  )






## CUT FLOW  jets
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *

process.jetsCF1 = selectedLayer1Jets.clone(src = 'selectedLayer1Jets', 
                                           cut = 'abs(eta)<3  &  pt>20'
                                           )

process.jetsCF2 = selectedLayer1Jets.clone(src = 'jetsCF1', 
                                           cut = '0.05 < emEnergyFraction  &'
                                                 '0.95 > emEnergyFraction'
                                           )

process.jetsCF3HighPur = selectedLayer1Jets.clone(src = 'jetsCF2', 
                                                  cut = 'bDiscriminator(\"trackCountingHighPurBJetTags\") > 3.0'
                                                  )

process.jetsCF3HighEff = selectedLayer1Jets.clone(src = 'jetsCF2', 
                                                  cut = 'bDiscriminator(\"trackCountingHighEffBJetTags\") > 3.0'
                                                  )



process.bJetsCF2 = selectedLayer1Jets.clone(src = 'selectedLayer1Jets', 
                                            cut = 'abs(partonFlavour)==5    &'
                                                  'abs(eta)<3  &  pt>20     &'
                                                  '0.05 < emEnergyFraction  &'
                                                  '0.95 > emEnergyFraction'
                                            )

process.lightQJetsCF2 = selectedLayer1Jets.clone(src = 'selectedLayer1Jets', 
                                                 cut = 'abs(partonFlavour)!=5    &  abs(partonFlavour)!=4  &'
                                                       'abs(eta)<3  &  pt>20     &'
                                                       '0.05 < emEnergyFraction  &'
                                                       '0.95 > emEnergyFraction'
                                                 )

## ---
## jet kinematics analyzer
## ---
process.load("TopAnalysis.TopAnalyzer.JetKinematics_cfi")


## 1. leading jet before any cut
process.jetKin_1st_CF0_selLay1 = process.analyzeJetKinematics.clone (src = 'selectedLayer1Jets',
                                                                     analyze = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('abs'  ) )
                                                                     )
## 2. leading jet before any cut
process.jetKin_2nd_CF0_selLay1 = process.analyzeJetKinematics.clone (src = 'selectedLayer1Jets',
                                                                     analyze = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('abs'  ) )
                                                                     )
## all jets before any cut
process.jetKin_all_CF0_selLay1 = process.analyzeJetKinematics.clone (src = 'selectedLayer1Jets',
                                                                     analyze = cms.PSet(index = cms.int32(-1), correctionLevel = cms.string('abs'  ) )
                                                                     )


## 1. leading jet after restriction in pt & eta
process.jetKin_1st_CF1_ptEta  = process.analyzeJetKinematics.clone (src = 'jetsCF1',
                                                                    analyze = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('abs'  ) )
                                                                    )
## 2. leading jet after restriction in pt & eta
process.jetKin_2nd_CF1_ptEta  = process.analyzeJetKinematics.clone (src = 'jetsCF1',
                                                                    analyze = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('abs'  ) )
                                                                    )
## all jets after restriction in pt & eta
process.jetKin_all_CF1_ptEta  = process.analyzeJetKinematics.clone (src = 'jetsCF1',
                                                                    analyze = cms.PSet(index = cms.int32(-1), correctionLevel = cms.string('abs'  ) )
                                                                    )



## 1. leading jet after restriction in pt & eta & emf                                            leading jet mult before b-discr.
process.jetKin_1st_CF2_emf  = process.analyzeJetKinematics.clone (src = 'jetsCF2',            
                                                                    analyze = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('abs'  ) )
                                                                    )
## 2. leading jet after restriction in pt & eta & emf                                             2nd     jet mult before b-discr.
process.jetKin_2nd_CF2_emf  = process.analyzeJetKinematics.clone (src = 'jetsCF2',
                                                                    analyze = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('abs'  ) )
                                                                    )
## all jets after restriction in pt & eta & emf                                             2nd     jet mult before b-discr.
process.jetKin_all_CF2_emf  = process.analyzeJetKinematics.clone (src = 'jetsCF2',
                                                                    analyze = cms.PSet(index = cms.int32(-1), correctionLevel = cms.string('abs'  ) )
                                                                    )




## 1. leading jet after restriction in pt & eta & emf & b-discriminator                          leading jet mult after b-discr.
process.jetKin_1st_CF3_highPur  = process.analyzeJetKinematics.clone (src = 'jetsCF3HighPur',
                                                                      analyze = cms.PSet(index = cms.int32(0), correctionLevel = cms.string('abs'  ) )
                                                                      )
## 2. leading jet after restriction in pt & eta & emf & b-discriminator                          2nd     jet mult after b-discr.
process.jetKin_2nd_CF3_highPur  = process.analyzeJetKinematics.clone (src = 'jetsCF3HighPur',
                                                                      analyze = cms.PSet(index = cms.int32(1), correctionLevel = cms.string('abs'  ) )
                                                                      )
## all jets after restriction in pt & eta & emf & b-discriminator                          2nd     jet mult after b-discr.
process.jetKin_all_CF3_highPur  = process.analyzeJetKinematics.clone (src = 'jetsCF3HighPur',
                                                                      analyze = cms.PSet(index = cms.int32(-1), correctionLevel = cms.string('abs'  ) )
                                                                      )



## define sequence
process.monitorJetKinematics = cms.Sequence(process.jetKin_1st_CF0_selLay1   +
                                            process.jetKin_2nd_CF0_selLay1   +
                                            process.jetKin_all_CF0_selLay1   +
                                            
                                            process.jetKin_1st_CF1_ptEta     +
                                            process.jetKin_2nd_CF1_ptEta     +
                                            process.jetKin_all_CF1_ptEta     +
                                            
                                            process.jetKin_1st_CF2_emf       +
                                            process.jetKin_2nd_CF2_emf       +
                                            process.jetKin_all_CF2_emf       +
                                            
                                            process.jetKin_1st_CF3_highPur   +
                                            process.jetKin_2nd_CF3_highPur   +
                                            process.jetKin_all_CF3_highPur
                                            )



## ---
## jet kinematics analyzer  aac
## ---


## 1. leading jet before any cut  aac
process.jetKin_1st_CF0_selLay1_aac =  process.jetKin_1st_CF0_selLay1.clone()

## 2. leading jet before any cut  aac
process.jetKin_2nd_CF0_selLay1_aac =  process.jetKin_2nd_CF0_selLay1.clone()

## all jets before any cut  aac
process.jetKin_all_CF0_selLay1_aac =  process.jetKin_all_CF0_selLay1.clone()


## 1. leading jet after restriction in pt & eta  aac
process.jetKin_1st_CF1_ptEta_aac  =  process.jetKin_1st_CF1_ptEta.clone()

## 2. leading jet after restriction in pt & eta  aac
process.jetKin_2nd_CF1_ptEta_aac  =  process.jetKin_2nd_CF1_ptEta.clone()

## all jets after restriction in pt & eta  aac
process.jetKin_all_CF1_ptEta_aac  =  process.jetKin_all_CF1_ptEta.clone()



## 1. leading jet after restriction in pt & eta & emf  aac                                          leading jet mult before b-discr.
process.jetKin_1st_CF2_emf_aac  =  process.jetKin_1st_CF2_emf.clone()

## 2. leading jet after restriction in pt & eta & emf  aac                                           2nd     jet mult before b-discr.
process.jetKin_2nd_CF2_emf_aac  =  process.jetKin_2nd_CF2_emf.clone()

## all jets after restriction in pt & eta & emf  aac                                           2nd     jet mult before b-discr.
process.jetKin_all_CF2_emf_aac  =  process.jetKin_all_CF2_emf.clone()



## 1. leading jet after restriction in pt & eta & emf & b-discriminator  aac                        leading jet mult after b-discr.
process.jetKin_1st_CF3_highPur_aac  =  process.jetKin_1st_CF3_highPur.clone()

## 2. leading jet after restriction in pt & eta & emf & b-discriminator  aac                        2nd     jet mult after b-discr.
process.jetKin_2nd_CF3_highPur_aac  =  process.jetKin_2nd_CF3_highPur.clone()

## all jets after restriction in pt & eta & emf & b-discriminator  aac                        2nd     jet mult after b-discr.
process.jetKin_all_CF3_highPur_aac  =  process.jetKin_all_CF3_highPur.clone()




## define sequence
process.monitorJetKinematics_aac = cms.Sequence(process.jetKin_1st_CF0_selLay1_aac   +
                                                process.jetKin_2nd_CF0_selLay1_aac   +
                                                process.jetKin_all_CF0_selLay1_aac   +
                                                
                                                process.jetKin_1st_CF1_ptEta_aac     +
                                                process.jetKin_2nd_CF1_ptEta_aac     +
                                                process.jetKin_all_CF1_ptEta_aac     +
                                                
                                                process.jetKin_1st_CF2_emf_aac       +
                                                process.jetKin_2nd_CF2_emf_aac       +
                                                process.jetKin_all_CF2_emf_aac       +
                                                
                                                process.jetKin_1st_CF3_highPur_aac   +
                                                process.jetKin_2nd_CF3_highPur_aac   +
                                                process.jetKin_all_CF3_highPur_aac
                                                )


## ---
## jet quality analyzer
## ---
process.load("TopAnalysis.TopAnalyzer.JetQuality_cfi")

## 1. leading jet w/o any restriction (selLay1)          CF0
process.jetID_1st_CF0  = process.analyzeJetQuality.clone  (src = 'selectedLayer1Jets',
                                                           analyze = cms.PSet(index = cms.int32(0), flavor = cms.string('uds' ) )
                                                           )

## 2. leading jet w/o any restriction (selLay1)          CF0
process.jetID_2nd_CF0  = process.analyzeJetQuality.clone (src = 'selectedLayer1Jets',
                                                          analyze = cms.PSet(index = cms.int32(1), flavor = cms.string('uds' ) )
                                                          )

## all jet w/o any restriction (selLay1)          CF0
process.jetID_all_CF0  = process.analyzeJetQuality.clone (src = 'selectedLayer1Jets',
                                                          analyze = cms.PSet(index = cms.int32(-1), flavor = cms.string('uds' ) )
                                                          )



## 1. leading jet after restriction in eta and pt        CF1
process.jetID_1st_CF1  = process.analyzeJetQuality.clone  (src = 'jetsCF1',
                                                           analyze = cms.PSet(index = cms.int32(0), flavor = cms.string('uds' ) )
                                                           )

## 2. leading jet after restriction in eta and pt        CF1
process.jetID_2nd_CF1  = process.analyzeJetQuality.clone (src = 'jetsCF1',
                                                          analyze = cms.PSet(index = cms.int32(1), flavor = cms.string('uds' ) )
                                                          )
## all jets after restriction in eta and pt        CF1
process.jetID_all_CF1  = process.analyzeJetQuality.clone (src = 'jetsCF1',
                                                          analyze = cms.PSet(index = cms.int32(-1), flavor = cms.string('uds' ) )
                                                          )



## 1. leading jet after restriction in eta, pt and emf   CF2
process.jetID_1st_CF2      = process.analyzeJetQuality.clone  (src = 'jetsCF2',
                                                               analyze = cms.PSet(index = cms.int32(0), flavor = cms.string('uds' ) )
                                                               )
## 2. leading jet after restriction in eta, pt and emf   CF2
process.jetID_2nd_CF2      = process.analyzeJetQuality.clone  (src = 'jetsCF2',
                                                               analyze = cms.PSet(index = cms.int32(1), flavor = cms.string('uds' ) )
                                                               )
## all jets after restriction in eta, pt and emf   CF2
process.jetID_all_CF2      = process.analyzeJetQuality.clone  (src = 'jetsCF2',
                                                               analyze = cms.PSet(index = cms.int32(-1), flavor = cms.string('uds' ) )
                                                               )




## 1. leading bQJet with restr. in eta, pt and emf       bQCF2
process.jetID_1st_bQCF2      = process.analyzeJetQuality.clone  (src = 'bJetsCF2',
                                                                 analyze = cms.PSet(index = cms.int32(0), flavor = cms.string('uds' ) )
                                                                 )
## 2. leading bQJet with restr. in eta, pt and emf       bQCF2
process.jetID_2nd_bQCF2      = process.analyzeJetQuality.clone   (src = 'bJetsCF2',
                                                                  analyze = cms.PSet(index = cms.int32(1), flavor = cms.string('uds' ) )
                                                                  )
## all bQJet with restr. in eta, pt and emf       bQCF2
process.jetID_all_bQCF2      = process.analyzeJetQuality.clone   (src = 'bJetsCF2',
                                                                  analyze = cms.PSet(index = cms.int32(-1), flavor = cms.string('uds' ) )
                                                                  )



## 1. leading lightQJet with restr. in eta, pt and emf       lightQCF2
process.jetID_1st_lightQCF2      = process.analyzeJetQuality.clone  (src = 'lightQJetsCF2',
                                                                     analyze = cms.PSet(index = cms.int32(0), flavor = cms.string('uds' ) )
                                                                     )

## 2. leading lightQJet with restr. in eta, pt and emf       lightQCF2
process.jetID_2nd_lightQCF2      = process.analyzeJetQuality.clone   (src = 'lightQJetsCF2',
                                                                      analyze = cms.PSet(index = cms.int32(1), flavor = cms.string('uds' ) )
                                                                      )
## all lightQJet with restr. in eta, pt and emf       lightQCF2
process.jetID_all_lightQCF2      = process.analyzeJetQuality.clone   (src = 'lightQJetsCF2',
                                                                      analyze = cms.PSet(index = cms.int32(-1), flavor = cms.string('uds' ) )
                                                                      )



## define sequence
process.monitorJetQuality = cms.Sequence(process.jetID_1st_CF0        +
                                         process.jetID_2nd_CF0        +
                                         process.jetID_all_CF0        +
                                         
                                         process.jetID_1st_CF1        +
                                         process.jetID_2nd_CF1        +
                                         process.jetID_all_CF1        +
                                         
                                         process.jetID_1st_CF2        +
                                         process.jetID_2nd_CF2        +
                                         process.jetID_all_CF2        +
                                         
                                         process.jetID_1st_bQCF2      +
                                         process.jetID_2nd_bQCF2      +
                                         process.jetID_all_bQCF2      +
                                         
                                         process.jetID_1st_lightQCF2  +
                                         process.jetID_2nd_lightQCF2  +
                                         process.jetID_all_lightQCF2
                                         )

## ---
## jet quality analyzer  aac
## ---


## 1. leading jet w/o any restriction (selLay1)          CF0
process.jetID_1st_CF0_aac  =  process.jetID_1st_CF0.clone()

## 2. leading jet w/o any restriction (selLay1)          CF0
process.jetID_2nd_CF0_aac  =  process.jetID_2nd_CF0.clone()

## all jets w/o any restriction (selLay1)          CF0
process.jetID_all_CF0_aac  =  process.jetID_all_CF0.clone()



## 1. leading jet after restriction in eta and pt        CF1
process.jetID_1st_CF1_aac  =  process.jetID_1st_CF1.clone()

## 2. leading jet after restriction in eta and pt        CF1
process.jetID_2nd_CF1_aac  =  process.jetID_2nd_CF1.clone()

## all jets after restriction in eta and pt        CF1
process.jetID_all_CF1_aac  =  process.jetID_all_CF1.clone()



## 1. leading jet after restriction in eta, pt and emf   CF2
process.jetID_1st_CF2_aac      =  process.jetID_1st_CF2.clone()

## 2. leading jet after restriction in eta, pt and emf   CF2
process.jetID_2nd_CF2_aac      =  process.jetID_2nd_CF2.clone()

## all jets after restriction in eta, pt and emf   CF2
process.jetID_all_CF2_aac      =  process.jetID_all_CF2.clone()



## 1. leading bQJet with restr. in eta, pt and emf       bQCF2
process.jetID_1st_bQCF2_aac      =  process.jetID_1st_bQCF2.clone()

## 2. leading bQJet with restr. in eta, pt and emf       bQCF2
process.jetID_2nd_bQCF2_aac      =  process.jetID_2nd_bQCF2.clone()

## all bQJets with restr. in eta, pt and emf       bQCF2
process.jetID_all_bQCF2_aac      =  process.jetID_all_bQCF2.clone()



## 1. leading lightQJet with restr. in eta, pt and emf       lightQCF2
process.jetID_1st_lightQCF2_aac      =  process.jetID_1st_lightQCF2.clone()

## 2. leading lightQJet with restr. in eta, pt and emf       lightQCF2
process.jetID_2nd_lightQCF2_aac      =  process.jetID_2nd_lightQCF2.clone()

## all lightQJet with restr. in eta, pt and emf       lightQCF2
process.jetID_all_lightQCF2_aac      =  process.jetID_all_lightQCF2.clone()



## define sequence
process.monitorJetQuality_aac = cms.Sequence(process.jetID_1st_CF0_aac        +
                                             process.jetID_2nd_CF0_aac        +
                                             process.jetID_all_CF0_aac        +
                                             
                                             process.jetID_1st_CF1_aac        +
                                             process.jetID_2nd_CF1_aac        +
                                             process.jetID_all_CF1_aac        +
                                             
                                             process.jetID_1st_CF2_aac        +
                                             process.jetID_2nd_CF2_aac        +
                                             process.jetID_all_CF2_aac        +
                                                                                      
                                             process.jetID_1st_bQCF2_aac      +
                                             process.jetID_2nd_bQCF2_aac      +
                                             process.jetID_all_bQCF2_aac      +
                                             
                                             process.jetID_1st_lightQCF2_aac  +
                                             process.jetID_2nd_lightQCF2_aac  +
                                             process.jetID_all_lightQCF2_aac  
                                             )

## loade METKinematicsAnalyzer
process.load("TopAnalysis.TopAnalyzer.METKinematics_cfi")


## CUT FLOW   muon
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *


process.muonCF0 = selectedLayer1Muons.clone(src = 'selectedLayer1Muons', 
                                            cut = ''             
                                            )

process.muonCF1StAl = selectedLayer1Muons.clone(src = 'muonCF0', 
                                            cut = 'standAloneMuon.isNull = 0'             
                                            )

process.muonCF1Comb = selectedLayer1Muons.clone(src = 'muonCF0', 
                                            cut = 'combinedMuon.isNull = 0'             
                                            )



## ---
## muon kinematics analyzer
## ---
process.load("TopAnalysis.TopAnalyzer.MuonKinematics_cfi")

## 1. leading muon with standAlone restriction
process.muonKin_1st_CF0     = process.analyzeMuonKinematics.clone(src='muonCF0',
                                                                  analyze = cms.PSet(index = cms.int32(0))
                                                                  )

process.muonKin_1st_CF1StAl = process.analyzeMuonKinematics.clone(src='muonCF1StAl',
                                                                  analyze = cms.PSet(index = cms.int32(0))
                                                                  )

process.muonKin_1st_CF1Comb = process.analyzeMuonKinematics.clone(src='muonCF1Comb',

                                                                  analyze = cms.PSet(index = cms.int32(0))
                                                                  )

process.muonKin = cms.Sequence(process.muonKin_1st_CF0       +
                               process.muonKin_1st_CF1StAl   +
                               process.muonKin_1st_CF1Comb
                               )



process.muonKin_1st_CF0_aac     =  process.muonKin_1st_CF0.clone()

process.muonKin_1st_CF1StAl_aac =  process.muonKin_1st_CF1StAl.clone()

process.muonKin_1st_CF1Comb_aac =  process.muonKin_1st_CF1Comb.clone()


process.muonKin_aac = cms.Sequence(process.muonKin_1st_CF0_aac       +
                                   process.muonKin_1st_CF1StAl_aac   +
                                   process.muonKin_1st_CF1Comb_aac
                                   )




## ---
## muon quality analyzer 
## ---
process.load("TopAnalysis.TopAnalyzer.MuonQuality_cfi")

process.muonID_1st_CF0       =   process.analyzeMuonQuality.clone  (src     = 'muonCF0',
                                                                    analyze = cms.PSet(index = cms.int32(0) )
                                                                    )

process.muonID_1st_CF1Comb   =   process.analyzeMuonQuality.clone  (src     = 'muonCF1Comb',
                                                                    analyze = cms.PSet(index = cms.int32(0) )
                                                                    )


process.muonID = cms.Sequence(process.muonID_1st_CF0            +
                              ##process.muonID_1st_CF1StAl   +
                              process.muonID_1st_CF1Comb
                              )


## ---
## muon quality analyzer  aac
## ---

process.muonID_1st_CF0_aac      = process.muonID_1st_CF0.clone()

process.muonID_1st_CF1Comb_aac  = process.muonID_1st_CF1Comb.clone()


process.muonID_aac = cms.Sequence(process.muonID_1st_CF0_aac        +
                                  ##process.muonID_1st_CF1StAl_aac   +
                                  process.muonID_1st_CF1Comb_aac
                                  )



## ---
## probe efficiency analysis, to be applied after combined muon
## ---



## CUT FLOW  muon  for  effiecincy analysis  probe --> test

process.comb = selectedLayer1Muons.clone(src = 'muonCF0', 
                                         cut = 'combinedMuon.isNull = 0       &'
                                               '(trackIso+caloIso)/pt < 0.05'
                                         )

process.combValhit = selectedLayer1Muons.clone(src = 'comb', 
                                               cut = 'track.numberOfValidHits >= 11'
                                               )

process.combChi2 = selectedLayer1Muons.clone(src = 'comb', 
                                             cut = 'combinedMuon.normalizedChi2 < 10.0'
                                             )

process.combTrksig = selectedLayer1Muons.clone(src = 'comb', 
                                               cut = 'abs(dB) < 0.02'
                                               )


process.combValhitChi2Trksig = selectedLayer1Muons.clone(src = 'comb', 
                                                         cut = 'track.numberOfValidHits >= 11       &'
                                                               'combinedMuon.normalizedChi2 < 10.0  &'
                                                               'abs(dB) < 0.02'
                                                         )
## trackMu = combValhitChi2Trksig


process.trackMuEcal = selectedLayer1Muons.clone(src = 'combValhitChi2Trksig', 
                                                cut = 'ecalIsoDeposit.candEnergy < 4'           
                                                )

process.trackMuHcal = selectedLayer1Muons.clone(src = 'combValhitChi2Trksig', 
                                                cut = 'hcalIsoDeposit.candEnergy < 6'           
                                                )

process.trackMuEcalHcal = selectedLayer1Muons.clone(src = 'combValhitChi2Trksig', 
                                                    cut = 'ecalIsoDeposit.candEnergy < 4  &'
                                                          'hcalIsoDeposit.candEnergy < 6'           
                                                    )


process.trackMuTrkiso = selectedLayer1Muons.clone(src = 'combValhitChi2Trksig', 
                                                  cut = 'trackIso < 1.'           
                                                  )

process.trackMuCaliso = selectedLayer1Muons.clone(src = 'combValhitChi2Trksig', 
                                                  cut = 'caloIso  < 5.'           
                                                  )

process.trackMuReliso = selectedLayer1Muons.clone(src = 'combValhitChi2Trksig', 
                                                  cut = '(trackIso+caloIso)/pt < 0.05'           
                                                  )



process.combEcal = selectedLayer1Muons.clone(src = 'comb', 
                                             cut = 'ecalIsoDeposit.candEnergy < 4'           
                                             )

process.combHcal = selectedLayer1Muons.clone(src = 'comb', 
                                             cut = 'hcalIsoDeposit.candEnergy < 6'           
                                             )

process.combEcalHcal = selectedLayer1Muons.clone(src = 'comb', 
                                                 cut = 'ecalIsoDeposit.candEnergy < 4  &'
                                                       'hcalIsoDeposit.candEnergy < 6'           
                                                 )

process.combEcalHcalTrkiso = selectedLayer1Muons.clone(src = 'combEcalHcal', 
                                                       cut = 'trackIso < 1.'
                                                       )

process.combEcalHcalCaliso = selectedLayer1Muons.clone(src = 'combEcalHcal', 
                                                       cut = 'caloIso  < 5.'
                                                       )

process.combEcalHcalReliso = selectedLayer1Muons.clone(src = 'combEcalHcal', 
                                                       cut = '(trackIso+caloIso)/pt < 0.05'
                                                       )
 


process.combTrkiso = selectedLayer1Muons.clone(src = 'comb', 
                                               cut = 'trackIso < 1.'                      #                       !!!      
                                               )

process.combCaliso = selectedLayer1Muons.clone(src = 'comb', 
                                               cut = 'caloIso  < 5.'                      #                       !!!
                                               )

process.combReliso = selectedLayer1Muons.clone(src = 'comb', 
                                               cut = '(trackIso+caloIso)/pt < 0.05'       #                       !!!     
                                               )

process.combTrkisoEcal = selectedLayer1Muons.clone(src = 'combTrkiso', 
                                                   cut = 'ecalIsoDeposit.candEnergy < 4'           
                                                   )

process.combTrkisoHcal = selectedLayer1Muons.clone(src = 'combTrkiso', 
                                                   cut = 'hcalIsoDeposit.candEnergy < 6'           
                                                   )

process.combTrkisoCaliso = selectedLayer1Muons.clone(src = 'combTrkiso', 
                                                     cut = 'caloIso  < 5.'           
                                                     )





process.trackMuEcalHcalTrkiso = selectedLayer1Muons.clone(src = 'trackMuEcalHcal', 
                                                          cut = 'trackIso < 1.'
                                                          )

process.trackMuEcalHcalCaliso = selectedLayer1Muons.clone(src = 'trackMuEcalHcal', 
                                                          cut = 'caloIso  < 5.'
                                                          )

process.trackMuEcalHcalReliso = selectedLayer1Muons.clone(src = 'trackMuEcalHcal', 
                                                          cut = '(trackIso+caloIso)/pt < 0.05'
                                                          )






process.cutFlowProbeTest = cms.Sequence(process.comb                        +
                                        process.combValhit                  +
                                        process.combChi2                    +
                                        process.combTrksig                  +
                                        process.combValhitChi2Trksig        +

                                        process.trackMuEcal                 +
                                        process.trackMuHcal                 +
                                        process.trackMuEcalHcal             +
                                        process.trackMuTrkiso               +
                                        process.trackMuCaliso               +
                                        process.trackMuReliso               +


                                        process.trackMuEcalHcalTrkiso       +
                                        process.trackMuEcalHcalCaliso       +
                                        process.trackMuEcalHcalReliso       +
                                                                       
                                        process.combEcal                    +
                                        process.combHcal                    +
                                        process.combEcalHcal                +
                                        process.combEcalHcalTrkiso          +
                                        process.combEcalHcalCaliso          +
                                        process.combEcalHcalReliso          +



                                        process.combTrkiso                  +
                                        process.combCaliso                  +
                                        process.combReliso                  +
                                        process.combTrkisoEcal              +
                                        process.combTrkisoHcal              +
                                        process.combTrkisoCaliso            
                                                                               
                                        )                                       


## ---
## tagAndProbeAnalyzer
## ---


process.load("TopAnalysis.TopAnalyzer.TagAndProbeAnalyzer_cfi")



process.comb_combValhit                     = process.tagAndProbeAnalyzer.clone(probes = "comb", tests = "combValhit"             ,   jets = "jetsCF2"    )
process.comb_combChi2                       = process.tagAndProbeAnalyzer.clone(probes = "comb", tests = "combChi2"               ,   jets = "jetsCF2"    )
process.comb_combTrksig                     = process.tagAndProbeAnalyzer.clone(probes = "comb", tests = "combTrksig"             ,   jets = "jetsCF2"    )
process.comb_combTrackMu                    = process.tagAndProbeAnalyzer.clone(probes = "comb", tests = "combValhitChi2Trksig"   ,   jets = "jetsCF2"    )
process.comb_combEcal                       = process.tagAndProbeAnalyzer.clone(probes = "comb", tests = "combEcal"               ,   jets = "jetsCF2"    )
process.comb_combHcal                       = process.tagAndProbeAnalyzer.clone(probes = "comb", tests = "combHcal"               ,   jets = "jetsCF2"    )
process.comb_combEcalHcal                   = process.tagAndProbeAnalyzer.clone(probes = "comb", tests = "combEcalHcal"           ,   jets = "jetsCF2"    )
process.comb_combTrackMuEcalHcal            = process.tagAndProbeAnalyzer.clone(probes = "comb", tests = "trackMuEcalHcal"        ,   jets = "jetsCF2"    )


process.trackMu_combEcal                   = process.tagAndProbeAnalyzer.clone(probes = "combValhitChi2Trksig", tests = "trackMuEcal"    ,   jets = "jetsCF2"    )
process.trackMu_combHcal                   = process.tagAndProbeAnalyzer.clone(probes = "combValhitChi2Trksig", tests = "trackMuHcal"    ,   jets = "jetsCF2"    )
process.trackMu_combEcalHcal               = process.tagAndProbeAnalyzer.clone(probes = "combValhitChi2Trksig", tests = "trackMuEcalHcal",   jets = "jetsCF2"    )
process.trackMu_combTrkiso                 = process.tagAndProbeAnalyzer.clone(probes = "combValhitChi2Trksig", tests = "trackMuTrkiso"  ,   jets = "jetsCF2"    )
process.trackMu_combCaliso                 = process.tagAndProbeAnalyzer.clone(probes = "combValhitChi2Trksig", tests = "trackMuCaliso"  ,   jets = "jetsCF2"    )
process.trackMu_combReliso                 = process.tagAndProbeAnalyzer.clone(probes = "combValhitChi2Trksig", tests = "trackMuReliso"  ,   jets = "jetsCF2"    )


process.combEcalHcal_trackMu               = process.tagAndProbeAnalyzer.clone(probes = "combEcalHcal", tests = "trackMuEcalHcal"    ,       jets = "jetsCF2"    )
process.combEcalHcal_combTrkiso            = process.tagAndProbeAnalyzer.clone(probes = "combEcalHcal", tests = "combEcalHcalTrkiso" ,       jets = "jetsCF2"    )
process.combEcalHcal_combCaliso            = process.tagAndProbeAnalyzer.clone(probes = "combEcalHcal", tests = "combEcalHcalCaliso" ,       jets = "jetsCF2"    )
process.combEcalHcal_combReliso            = process.tagAndProbeAnalyzer.clone(probes = "combEcalHcal", tests = "combEcalHcalReliso" ,       jets = "jetsCF2"    )


process.trackMuEcalHcal_combTrkiso         = process.tagAndProbeAnalyzer.clone(probes = "trackMuEcalHcal", tests = "trackMuEcalHcalTrkiso" , jets = "jetsCF2"    )
process.trackMuEcalHcal_combCaliso         = process.tagAndProbeAnalyzer.clone(probes = "trackMuEcalHcal", tests = "trackMuEcalHcalCaliso" , jets = "jetsCF2"    )
process.trackMuEcalHcal_combReliso         = process.tagAndProbeAnalyzer.clone(probes = "trackMuEcalHcal", tests = "trackMuEcalHcalReliso" , jets = "jetsCF2"    )


process.combTrkiso_trackMu                 = process.tagAndProbeAnalyzer.clone(probes = "combTrkiso", tests = "trackMuTrkiso"              , jets = "jetsCF2"    )
process.combTrkiso_combEcal                = process.tagAndProbeAnalyzer.clone(probes = "combTrkiso", tests = "combTrkisoEcal"             , jets = "jetsCF2"    )
process.combTrkiso_combHcal                = process.tagAndProbeAnalyzer.clone(probes = "combTrkiso", tests = "combTrkisoHcal"             , jets = "jetsCF2"    )
process.combTrkiso_combEcalHcal            = process.tagAndProbeAnalyzer.clone(probes = "combTrkiso", tests = "combEcalHcalTrkiso"         , jets = "jetsCF2"    )
process.combTrkiso_combCaliso              = process.tagAndProbeAnalyzer.clone(probes = "combTrkiso", tests = "combTrkisoCaliso"           , jets = "jetsCF2"    )




process.probeTestAnalysis = cms.Sequence(process.comb_combValhit              +
                                         process.comb_combChi2                +
                                         process.comb_combTrksig              +
                                         process.comb_combTrackMu             +
                                         process.comb_combEcal                +
                                         process.comb_combHcal                +
                                         process.comb_combEcalHcal            +
                                         process.comb_combTrackMuEcalHcal     +

                                         process.trackMu_combEcal             +
                                         process.trackMu_combHcal             +
                                         process.trackMu_combEcalHcal         +
                                         process.trackMu_combTrkiso           +
                                         process.trackMu_combCaliso           +
                                         process.trackMu_combReliso           +

                                         process.combEcalHcal_trackMu         +   
                                         process.combEcalHcal_combTrkiso      +
                                         process.combEcalHcal_combCaliso      +
                                         process.combEcalHcal_combReliso      +

                                         process.trackMuEcalHcal_combTrkiso   +
                                         process.trackMuEcalHcal_combCaliso   +
                                         process.trackMuEcalHcal_combReliso   +

                                         process.combTrkiso_trackMu           +
                                         process.combTrkiso_combEcal          +
                                         process.combTrkiso_combHcal          +
                                         process.combTrkiso_combEcalHcal      +
                                         process.combTrkiso_combCaliso       
                                         )



process.comb_combValhit_2               =  process.comb_combValhit.clone()             
process.comb_combChi2_2                 =  process.comb_combChi2.clone()               
process.comb_combTrksig_2               =  process.comb_combTrksig.clone()           
process.comb_combTrackMu_2              =  process.comb_combTrackMu.clone()         
process.comb_combEcal_2                 =  process.comb_combEcal.clone()              
process.comb_combHcal_2                 =  process.comb_combHcal.clone()            
process.comb_combEcalHcal_2             =  process.comb_combEcalHcal.clone()          


process.trackMu_combEcal_2              =  process.trackMu_combEcal.clone()
process.trackMu_combHcal_2              =  process.trackMu_combHcal.clone()
process.trackMu_combEcalHcal_2          =  process.trackMu_combEcalHcal.clone()
process.trackMu_combTrkiso_2            =  process.trackMu_combTrkiso.clone()
process.trackMu_combCaliso_2            =  process.trackMu_combCaliso.clone()
process.trackMu_combReliso_2            =  process.trackMu_combReliso.clone()

process.combEcalHcal_trackMu_2          =  process.combEcalHcal_trackMu.clone()  
process.combEcalHcal_combTrkiso_2       =  process.combEcalHcal_combTrkiso.clone()
process.combEcalHcal_combCaliso_2       =  process.combEcalHcal_combCaliso.clone()
process.combEcalHcal_combReliso_2       =  process.combEcalHcal_combReliso.clone()

process.trackMuEcalHcal_combTrkiso_2    =  process.trackMuEcalHcal_combTrkiso.clone()
process.trackMuEcalHcal_combCaliso_2    =  process.trackMuEcalHcal_combCaliso.clone()
process.trackMuEcalHcal_combReliso_2    =  process.trackMuEcalHcal_combReliso.clone()

process.combTrkiso_trackMu_2            =  process.combTrkiso_trackMu.clone()
process.combTrkiso_combEcal_2           =  process.combTrkiso_combEcal.clone()
process.combTrkiso_combHcal_2           =  process.combTrkiso_combHcal.clone()
process.combTrkiso_combEcalHcal_2       =  process.combTrkiso_combEcalHcal.clone()
process.combTrkiso_combCaliso_2         =  process.combTrkiso_combCaliso.clone()



process.probeTestAnalysis_2 = cms.Sequence(

                                         process.comb_combValhit_2              +
                                         process.comb_combChi2_2                +
                                         process.comb_combTrksig_2              +
                                         process.comb_combTrackMu_2             +
                                         process.comb_combEcal_2                +
                                         process.comb_combHcal_2                +
                                         process.comb_combEcalHcal_2            + 

                                         process.trackMu_combEcal_2             +
                                         process.trackMu_combHcal_2             +
                                         process.trackMu_combEcalHcal_2         +
                                         process.trackMu_combTrkiso_2           +
                                         process.trackMu_combCaliso_2           +
                                         process.trackMu_combReliso_2           +

                                         process.combEcalHcal_trackMu_2         +   
                                         process.combEcalHcal_combTrkiso_2      +
                                         process.combEcalHcal_combCaliso_2      +
                                         process.combEcalHcal_combReliso_2      +

                                         process.trackMuEcalHcal_combTrkiso_2   +
                                         process.trackMuEcalHcal_combCaliso_2   +
                                         process.trackMuEcalHcal_combReliso_2   +

                                         process.combTrkiso_trackMu_2           +
                                         process.combTrkiso_combEcal_2          +
                                         process.combTrkiso_combHcal_2          +
                                         process.combTrkiso_combEcalHcal_2      +
                                         process.combTrkiso_combCaliso_2       
                                         )





process.comb_combValhit_3               =  process.comb_combValhit.clone()             
process.comb_combChi2_3                 =  process.comb_combChi2.clone()               
process.comb_combTrksig_3               =  process.comb_combTrksig.clone()           
process.comb_combTrackMu_3              =  process.comb_combTrackMu.clone()         
process.comb_combEcal_3                 =  process.comb_combEcal.clone()              
process.comb_combHcal_3                 =  process.comb_combHcal.clone()            
process.comb_combEcalHcal_3             =  process.comb_combEcalHcal.clone()          


process.trackMu_combEcal_3              =  process.trackMu_combEcal.clone()
process.trackMu_combHcal_3              =  process.trackMu_combHcal.clone()
process.trackMu_combEcalHcal_3          =  process.trackMu_combEcalHcal.clone()
process.trackMu_combTrkiso_3            =  process.trackMu_combTrkiso.clone()
process.trackMu_combCaliso_3            =  process.trackMu_combCaliso.clone()
process.trackMu_combReliso_3            =  process.trackMu_combReliso.clone()

process.combEcalHcal_trackMu_3          =  process.combEcalHcal_trackMu.clone()  
process.combEcalHcal_combTrkiso_3       =  process.combEcalHcal_combTrkiso.clone()
process.combEcalHcal_combCaliso_3       =  process.combEcalHcal_combCaliso.clone()
process.combEcalHcal_combReliso_3       =  process.combEcalHcal_combReliso.clone()

process.trackMuEcalHcal_combTrkiso_3    =  process.trackMuEcalHcal_combTrkiso.clone()
process.trackMuEcalHcal_combCaliso_3    =  process.trackMuEcalHcal_combCaliso.clone()
process.trackMuEcalHcal_combReliso_3    =  process.trackMuEcalHcal_combReliso.clone()

process.combTrkiso_trackMu_3            =  process.combTrkiso_trackMu.clone()
process.combTrkiso_combEcal_3           =  process.combTrkiso_combEcal.clone()
process.combTrkiso_combHcal_3           =  process.combTrkiso_combHcal.clone()
process.combTrkiso_combEcalHcal_3       =  process.combTrkiso_combEcalHcal.clone()
process.combTrkiso_combCaliso_3         =  process.combTrkiso_combCaliso.clone()


process.probeTestAnalysis_3 = cms.Sequence(

                                         process.comb_combValhit_3              +
                                         process.comb_combChi2_3                +
                                         process.comb_combTrksig_3              +
                                         process.comb_combTrackMu_3             +
                                         process.comb_combEcal_3                +
                                         process.comb_combHcal_3                +
                                         process.comb_combEcalHcal_3            + 

                                         process.trackMu_combEcal_3             +
                                         process.trackMu_combHcal_3             +
                                         process.trackMu_combEcalHcal_3         +
                                         process.trackMu_combTrkiso_3           +
                                         process.trackMu_combCaliso_3           +
                                         process.trackMu_combReliso_3           +

                                         process.combEcalHcal_trackMu_3         +   
                                         process.combEcalHcal_combTrkiso_3      +
                                         process.combEcalHcal_combCaliso_3      +
                                         process.combEcalHcal_combReliso_3      +

                                         process.trackMuEcalHcal_combTrkiso_3   +
                                         process.trackMuEcalHcal_combCaliso_3   +
                                         process.trackMuEcalHcal_combReliso_3   +

                                         process.combTrkiso_trackMu_3           +
                                         process.combTrkiso_combEcal_3          +
                                         process.combTrkiso_combHcal_3          +
                                         process.combTrkiso_combEcalHcal_3      +
                                         process.combTrkiso_combCaliso_3       
                                         )



                                        

## ---
## muon quality analyzer
## ---
process.load("TopAnalysis.TopAnalyzer.MuonQuality_cfi")

## 1. leading muon with standAlone restriction
process.muonID_1st_CF1StAl = process.analyzeMuonQuality.clone(src='muonCF1StAl')



## ---
##    run the final sequence
## ---
process.p1 = cms.Path(## do the gen event selection (decay channel)
                      process.genFilterSequence  *
                      ## the trigger selection (hltEle15)
                      process.recFilterSequence  *

                                        
                      ## get corresponding electron collection
                      process.idOnlyElectrons           *
                      process.centralElectrons          *
                      process.highPtElectrons           *
                      process.tightElectrons            *
                      process.electronCF2               *
                      process.electronCF3               *
                 
                      ## do the electron monitoring
                      process.monitorElectronKinematics *
                      process.monitorElectronQuality    *


                      ## do the electron event selection
                           ##process.electronSelection         *
                      process.elecSelIdPtEta            *
                      process.elecSelRelIso             *

                   
                      ## get corresponding jet collections
                      process.reliableJets              *
                      process.centralJets               *
                      process.goodJets                  *
                      process.jetsCF1                   *
                      process.jetsCF2                   *
                      process.bJetsCF2                  *
                      process.lightQJetsCF2             *
                      process.jetsCF3HighPur            *
                      process.jetsCF3HighEff            *

                      ## do the jet monitoring
                      process.monitorJetKinematics      *
                      process.monitorJetQuality         *


                      ## do the jet event selection
                           ##process.jetSelection1             *
                           ##process.jetSelection2             *
                      process.jetSelPtEtaEmf            *
                      process.jetSelBtag                *


                      process.analyzeMETKinematics      *
                      ## missing ET selection
                      process.selectedLayer1MET         *
                      process.selectEventsWithMET       *

                     
                      ## get corresponding muon collection
                      process.muonCF0                   *
                      process.muonCF1StAl               *
                      process.muonCF1Comb               *           

                      ## do the muon monitoring
                      process.muonKin                   *
                      process.muonID                    *


                      ## CUT FLOW  (from below because of application in muon selection)
                      process.cutFlowProbeTest          *


                      ## do the muon event selection
                      process.muonSelStAl               *
                      process.muonSelComb               *

                      #process.muonSelTrkiso             *
                      process.muonSelReliso               *
                      #process.muonSelCaliso               *



                      ## END of TAG !!!                                            !!!!!


                      
                      ##process.muonSelEcalHcal           *
                      ##process.muonSelTrackMu            *
                      
                    

                      ## electron monitoring  aac (after all cuts) 
                      process.monitorElectronKinematics_aac  *
                      process.monitorElectronQuality_aac     *

                      ## jet monitoring  aac
                      process.monitorJetKinematics_aac       *
                      process.monitorJetQuality_aac          *

                      ## muon monitoring  aac
                      process.muonKin_aac                    *
                      process.muonID_aac                     *

                      ## remains of muon event selection
                      ## process.muonSelComb                    *


                      ## probeTest analysis


                      ## CUT FLOW (above)
                     

                      ## tagAndProbeAnalyzer  
                      process.probeTestAnalysis              *


                      ## further muon event selection for statistics
                      ##process.muonSelTrackMu

                      process.muonSelValhit                  *
                      process.muonSelChi2                    *
                      process.muonSelTrksig                  *


                      ## further muon event selection
                      process.muonSelEcalHcal                *


                      process.probeTestAnalysis_2            *


                      ## single-muon trigger, threshold pt > 9 GeV, no isolation requirements
                      process.hltMu9                         *

                      ## 2nd tagAndProbeAnalyzer
                      process.probeTestAnalysis_3            
                      
                      ## test of top decay channels 
                      #process.topDecayChannelDQM    + 
                      #process.dqmSaver
                      
                      )
