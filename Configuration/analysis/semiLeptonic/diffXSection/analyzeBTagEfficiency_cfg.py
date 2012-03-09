## This cfg file produces histos for the determination of b tag efficiencies (for b, c and l jets)
## on MC in the phase space of our semileptonic ttbar selection

## NOTE!!!!!!!!
## Copy output root file to TopAnalysis/Configuration/data!

import FWCore.ParameterSet.Config as cms

process = cms.Process("analyzeBtagEfficiency")

## run PF2PAT?
## only possible for special pat tuples!!!
if(not globals().has_key('pfToPAT')):
    pfToPAT = True #False
print "run PF2PAT?: ",pfToPAT,"(won't work if the file does not contain the necessary information!)"

if(not globals().has_key('bTagAlgo')):
    bTagAlgo = "combinedSecondaryVertexBJetTags" #"simpleSecondaryVertexHighEffBJetTags"
print "-------------------------------------"
print "bTagAlgo: ",bTagAlgo
print "-------------------------------------"

if(not globals().has_key('bTagDiscrCut')):
    bTagDiscrCut = 0.679 #1.74
print "-------------------------------------"
print "bTagDiscrCut: ",bTagDiscrCut
print "-------------------------------------"

## define input
#process.source = cms.Source("PoolSource",
                            #fileNames = cms.untracked.vstring(    
    ### add your favourite file here
    #'/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_9_1_HFr.root'
    #)
#)
process.load("TopAnalysis/Configuration/Fall11/ttjets_MadgraphZ2_Fall11_v1_and_2_AOD_cff")

## register TFileService => define output file
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeBTagEfficiency.root')
)

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")

from Configuration.PyReleaseValidation.autoCond import autoCond
process.GlobalTag.globaltag = cms.string('START42_V17::All')

## ============================
##  MC PU reweighting
## ============================

process.load("TopAnalysis.TopUtils.EventWeightPU_cfi")

process.eventWeightPU        = process.eventWeightPU.clone()
process.eventWeightPUsysUp   = process.eventWeightPU.clone()
process.eventWeightPUsysDown = process.eventWeightPU.clone()

#### Configuration for Nominal PU Weights

process.eventWeightPU.WeightName          = "eventWeightPU"
process.eventWeightPU.Weight3DName        = "eventWeightPU3D"
process.eventWeightPU.DataFile            = "TopAnalysis/TopUtils/data/Data_PUDist_2011Full.root"
process.eventWeightPU.Data3DFile          = "TopAnalysis/TopUtils/data/Data_PUDist_2011Full.root"

process.eventWeightPU.CreateWeight3DHisto = False
process.eventWeightPU.Weight3DHistoFile   = "TopAnalysis/TopUtils/data/DefaultWeight3D.root"

#### Configuration for PU Up Variations

process.eventWeightPUsysUp.WeightName          = "eventWeightPUUp"
process.eventWeightPUsysUp.Weight3DName        = "eventWeightPU3DUp"
process.eventWeightPUsysUp.DataFile            = "TopAnalysis/TopUtils/data/Data_PUDist_sysUp_2011Full.root"
process.eventWeightPUsysUp.Data3DFile          = "TopAnalysis/TopUtils/data/Data_PUDist_sysUp_2011Full.root"

process.eventWeightPUsysUp.CreateWeight3DHisto = False
process.eventWeightPUsysUp.Weight3DHistoFile   = "TopAnalysis/TopUtils/data/DefaultWeight3DUp.root"

#### Configuration for PU Down Variations

process.eventWeightPUsysDown.WeightName          = "eventWeightPUDown"
process.eventWeightPUsysDown.Weight3DName        = "eventWeightPU3DDown"
process.eventWeightPUsysDown.DataFile            = "TopAnalysis/TopUtils/data/Data_PUDist_sysDown_2011Full.root"
process.eventWeightPUsysDown.Data3DFile          = "TopAnalysis/TopUtils/data/Data_PUDist_sysDown_2011Full.root"

process.eventWeightPUsysDown.CreateWeight3DHisto = False
process.eventWeightPUsysDown.Weight3DHistoFile   = "TopAnalysis/TopUtils/data/DefaultWeight3DDown.root"

process.makeEventWeightsPU = cms.Sequence(process.eventWeightPU        *
                                          process.eventWeightPUsysUp   *
                                          process.eventWeightPUsysDown  )

# relevant PU event weights (potentially merged with shape distortion weights)
PUweightraw     = cms.InputTag("eventWeightPU",       "eventWeightPU")
PUweightrawUp   = cms.InputTag("eventWeightPUsysUp",  "eventWeightPUUp")
PUweightrawDown = cms.InputTag("eventWeightPUsysDown","eventWeightPUDown")

##-----------------------------------------------------------------------
## semileptonic selection
process.load("TopAnalysis.TopFilter.sequences.semiLeptonicSelection_cff")
### redefine veto jets to be sure it is also replaced when running on PF
from TopAnalysis.TopFilter.sequences.jetSelection_cff import goodJets
process.vetoJets.src="goodJets"
process.vetoJets.cut=''

process.leadingJetSelectionNjets = process.leadingJetSelection.clone (src = 'tightLeadingPFJets', minNumber = 4)

## calculate b tag efficiencies
process.load("TopAnalysis.TopAnalyzer.BTagEfficiencyAnalyzer_cfi")
## NOTE: process needs to be named bTagEff, so that BTagSFEventWeight.cc can find the histo
process.bTagEff = process.analyzeBTagEfficiency.clone(jets         = "tightLeadingPFJets",
                                                      bTagAlgo     = bTagAlgo,
                                                      #bTagAlgo    = "simpleSecondaryVertexHighEffBJetTags",
                                                      bTagDiscrCut = bTagDiscrCut, ## CSVM
                                                      #bTagDiscrCut = 1.74 ## SSVHEM
                                                      weight       = PUweightraw
                                                     )

##-----------------------------------------------------------------------
process.p1 = cms.Path(
                      ## PU reweighting
                      process.makeEventWeightsPU                    *
                      ## introduce some collections
                      process.semiLeptonicSelection                 *
                      ## muon selection
                      process.muonSelection                         *
                      ## veto on additional leptons
                      process.secondMuonVeto                        *
                      process.electronVeto                          *
                      ## jet selection
                      process.leadingJetSelectionNjets              *
		      ## b tag Eff determination on MC
	              process.bTagEff
  )


## remove CaloJetCollections as not available anymore in Spring11
from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
massSearchReplaceAnyInputTag(process.p1, 'goodJets'        , 'goodJetsPF30'      )
process.p1.remove(process.centralJets)
process.p1.remove(process.reliableJets)
process.p1.remove(process.goodJets)
process.p1.remove(process.tightLeadingJets)
process.p1.remove(process.tightBottomJets)

# switch to PF2PAT
if(pfToPAT):
    from TopAnalysis.TopUtils.usePatTupleWithParticleFlow_cff import prependPF2PATSequence
    allpaths  = process.paths_().keys()
    recoPaths=['p1']
    # define general options
    PFoptions = {
        'runOnMC': True,
        'runOnAOD': True,
        'switchOffEmbedding': False,
        'addResolutions': True,
	'resolutionsVersion': 'summer11',
        'runOnOLDcfg': True,
        'cutsMuon': 'pt > 10. & abs(eta) < 2.5',
        'cutsElec': 'et > 15. & abs(eta) < 2.5',
        'cutsJets': 'pt > 10 & abs(eta) < 5.0', 
        'electronIDs': ['CiC','classical'],
        'pfIsoConeMuon': 0.4,
        'pfIsoConeElec': 0.4,
        'pfIsoValMuon': 0.2,
        'pfIsoValElec': 0.2,
        'skipIfNoPFMuon': True,
        'skipIfNoPFElec': False,
        'addNoCutPFMuon': False,
        'addNoCutPFElec': False,
        'noMuonTopProjection': False,
        'noElecTopProjection': False,
        'analyzersBeforeMuonIso':cms.Sequence(),
	'analyzersBeforeElecIso':cms.Sequence(),
        'excludeElectronsFromWsFromGenJets': True,
	'METCorrectionLevel': 1
        }
    prependPF2PATSequence(process, recoPaths, PFoptions)
    #for path in recoPaths:
        # replace object consistently with names from PF2PAT
        #massSearchReplaceAnyInputTag(getattr(process,path), 'patMETsPF', 'patMETs')
        #massSearchReplaceAnyInputTag(getattr(process,path), 'selectedPatJetsAK5PF', 'selectedPatJets')