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


## define input
#process.source = cms.Source("PoolSource",
                            #fileNames = cms.untracked.vstring(    
    ### add your favourite file here
    #'/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_9_1_HFr.root'
    #)
#)
process.load("TopAnalysis/Configuration/ttjets_MadgraphZ2_Summer11_AOD_cff")

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
process.GlobalTag.globaltag = cms.string('START42_V13::All')

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
                                                      bTagAlgo     = "simpleSecondaryVertexHighEffBJetTags",
                                                      bTagDiscrCut = 1.74
                                                     )

##-----------------------------------------------------------------------
process.p1 = cms.Path(
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
        'excludeElectronsFromWsFromGenJets': True
        }
    prependPF2PATSequence(process, recoPaths, PFoptions)
    for path in recoPaths:
        # replace object consistently with names from PF2PAT
        massSearchReplaceAnyInputTag(getattr(process,path), 'patMETsPF', 'patMETs')
        massSearchReplaceAnyInputTag(getattr(process,path), 'selectedPatJetsAK5PF', 'selectedPatJets')