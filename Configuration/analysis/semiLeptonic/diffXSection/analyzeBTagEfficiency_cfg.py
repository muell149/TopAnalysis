## This cfg file produces histos for the determination of b tag efficiencies (for b, c and l jets)
## on MC in the phase space of our semileptonic ttbar selection

## NOTE!!!!!!!!
## Copy output root file to TopAnalysis/Configuration/data!

import FWCore.ParameterSet.Config as cms

process = cms.Process("analyzeBtagEfficiency")

## define input
#process.source = cms.Source("PoolSource",
                            #fileNames = cms.untracked.vstring(    
    ### add your favourite file here
    #'/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_9_1_HFr.root'
    #)
#)
process.load("TopAnalysis.Configuration.samples.Spring11_TTJets_D6T_madgraph_F10_cff")

## register TFileService => define output file
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeBTagEfficiency.root')
)

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

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
