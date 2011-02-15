import FWCore.ParameterSet.Config as cms

#----------------------------------------------------------------------------
# cfg file for patTuple production
#----------------------------------------------------------------------------

process = cms.Process("PAT")

#----------------------------------------------------------------------------
# process configuration
#----------------------------------------------------------------------------

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    #'/store/data/Run2010B/Mu/AOD/Nov4ReReco_v1/0001/003545B1-76EA-DF11-BC95-485B39800BF3.root'
    )#,
#    skipEvents = cms.untracked.uint32(0)

)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('GR_R_38X_V15::All')

#----------------------------------------------------------------------------
# beam scrap filter
#----------------------------------------------------------------------------
process.beamScrapFilter = cms.EDFilter("FilterOutScraping",
                                       applyfilter = cms.untracked.bool(True),
                                       debugOn     = cms.untracked.bool(False),
                                       numtrack    = cms.untracked.uint32(10),
                                       thresh      = cms.untracked.double(0.25)
                                      )

#----------------------------------------------------------------------------
# HBHE noise filter
#----------------------------------------------------------------------------
				      
process.load('CommonTools.RecoAlgos.HBHENoiseFilter_cfi')

#----------------------------------------------------------------------------
# filter on primary vertex
#----------------------------------------------------------------------------
process.primaryVertexFilter = cms.EDFilter("GoodVertexFilter",
                                           vertexCollection = cms.InputTag('offlinePrimaryVertices'),
                                           minimumNDOF = cms.uint32(4) ,
                                           maxAbsZ = cms.double(24), 
                                           maxd0 = cms.double(2) 
                                          )

#----------------------------------------------------------------------------
# pat configuration
#----------------------------------------------------------------------------

## include L1OffsetCorrections
process.load("PhysicsTools.PatAlgos.patTestJEC_cfi")

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

## dummy output module
process.out = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('drop *'),
    dropMetaData = cms.untracked.string("DROPPED"),                                     
    fileName = cms.untracked.string('rerecoData.root')
)

## remove cleaning as it is not used
from PhysicsTools.PatAlgos.tools.coreTools import *
removeCleaning(process)

## switch off MC matching
#from PhysicsTools.PatAlgos.tools.coreTools import *
removeMCMatching(process, ['All'])

## remove tau and photon collection
removeSpecificPATObjects(process, ['Taus', 'Photons'])

## use the correct jet energy corrections
process.patJetCorrFactors.flavorType = "T"

## calculate d0 wrt the beam spot
process.patMuons.usePV = False

## Add PfMET and TcMET to the event content
from PhysicsTools.PatAlgos.tools.metTools import *
addPfMET(process,'PF')
addTcMET(process,'JPT')
		
## add ak5JPTJets
from PhysicsTools.PatAlgos.tools.jetTools import *
addJetCollection(process,cms.InputTag('JetPlusTrackZSPCorJetAntiKt5'),'AK5', 'JPT',
                 doJTA        = True,
                 doBTagging   = True,
                 jetCorrLabel = ('AK5JPT', ['L1Offset', 'L2Relative','L3Absolute', 'L2L3Residual']),
                 doType1MET   = False,
                 doL1Cleaning = False,
                 doL1Counters = False,                 
                 genJetCollection = None,
                 doJetID      = True
                )
		 
## Add particle flow jets
addJetCollection(process,cms.InputTag('ak5PFJets'),'AK5','PF',
                 doJTA        = True,
                 doBTagging   = True,
                 jetCorrLabel = ('AK5PF', ['L1Offset, ''L2Relative','L3Absolute', 'L2L3Residual']),
                 doType1MET   = False,
                 doL1Cleaning = False,
                 doL1Counters = False,
                 genJetCollection=None,
                 doJetID      = True
                )

## add L1 offset corrections to MC Calo Jets
process.patJetCorrFactors.levels=['L1Offset', 'L2Relative','L3Absolute', 'L2L3Residual']

## remove L1 offset corrections
#process.patJetCorrFactors.levels.remove("L1Offset")
#process.patJetCorrFactorsAK5PF.levels.remove("L1Offset")
#process.patJetCorrFactorsAK5JPT.levels.remove("L1Offset")

## embedding of jet constituents into the jets
process.patJets.embedCaloTowers       = False
process.patJetsAK5JPT.embedCaloTowers = False
process.patJetsAK5PF.embedPFCandidates= False

## remove TagInfos from jets
process.patJets.addTagInfos       = False
process.patJetsAK5JPT.addTagInfos = False
process.patJetsAK5PF.addTagInfos  = False

## embed IsoDeposits
process.patMuons.isoDeposits = cms.PSet(
     tracker = cms.InputTag("muIsoDepositTk"),
     ecal    = cms.InputTag("muIsoDepositCalByAssociatorTowers","ecal"),
     hcal    = cms.InputTag("muIsoDepositCalByAssociatorTowers","hcal"),
     user    = cms.VInputTag(cms.InputTag("muIsoDepositCalByAssociatorTowers","ho"),
                             cms.InputTag("muIsoDepositJets")
                            ),
    )
    
## embedding of resolutions into the patObjects
process.load("TopQuarkAnalysis.TopObjectResolutions.stringResolutions_etEtaPhi_cff")
process.patJets.addResolutions = True
process.patJets.resolutions = cms.PSet(
default = cms.string("udscResolution"),
bjets = cms.string("bjetResolution"),
)
process.patJetsAK5PF.addResolutions = True
process.patJetsAK5PF.resolutions = cms.PSet(
default = cms.string("udscResolutionPF"),
bjets = cms.string("bjetResolutionPF"),
)
process.patElectrons.addResolutions = True
process.patElectrons.resolutions = cms.PSet( default = cms.string("elecResolution") )
process.patMuons.addResolutions = True
process.patMuons.resolutions = cms.PSet( default = cms.string("muonResolution") )
process.patMETs.addResolutions = True
process.patMETs.resolutions = cms.PSet( default = cms.string("metResolution") )
process.patMETsPF.addResolutions = True
process.patMETsPF.resolutions = cms.PSet( default = cms.string("metResolutionPF") )     

## adding electron identification
process.load("ElectroWeakAnalysis.WENu.simpleEleIdSequence_cff")

process.patElectrons.addElectronID     = cms.bool( True )
process.patElectrons.electronIDSources = cms.PSet( simpleEleId95relIso = cms.InputTag("simpleEleId95relIso"),
                                                   simpleEleId90relIso = cms.InputTag("simpleEleId90relIso"),
                                                   simpleEleId85relIso = cms.InputTag("simpleEleId85relIso"),
                                                   simpleEleId80relIso = cms.InputTag("simpleEleId80relIso"),
                                                   simpleEleId70relIso = cms.InputTag("simpleEleId70relIso"),
                                                   simpleEleId60relIso = cms.InputTag("simpleEleId60relIso"),
                                                   simpleEleId95cIso   = cms.InputTag("simpleEleId95cIso"),
                                                   simpleEleId90cIso   = cms.InputTag("simpleEleId90cIso"),
                                                   simpleEleId85cIso   = cms.InputTag("simpleEleId85cIso"),
                                                   simpleEleId80cIso   = cms.InputTag("simpleEleId80cIso"),
                                                   simpleEleId70cIso   = cms.InputTag("simpleEleId70cIso"),
                                                   simpleEleId60cIso   = cms.InputTag("simpleEleId60cIso")
                                                   )

process.patElectronIDs = cms.Sequence( process.simpleEleIdSequence )

process.makePatElectrons = cms.Sequence(process.patElectronIDs       *
                                        process.patElectronIsolation *
#                                        process.electronMatch        *
                                        process.patElectrons
                                        )

#process.p = cms.Path(process.patDefaultSequence)

#----------------------------------------------------------------------------
# trigger preselection: 
#   HLT_Mu9 OR HLT_Mu11 OR HLT_Mu15_v1
#----------------------------------------------------------------------------
from TopAnalysis.TopFilter.filters.TriggerFilter_cfi import filterTrigger
process.filterHltMu9           = filterTrigger.clone()
process.filterHltMu9.hltPaths  = cms.vstring('HLT_Mu9')

process.filterHltMu11          = filterTrigger.clone()
process.filterHltMu11.hltPaths = cms.vstring('HLT_Mu11')

process.filterHltMu15          = filterTrigger.clone()
process.filterHltMu15.hltPaths = cms.vstring('HLT_Mu15_v1')
					   
#----------------------------------------------------------------------------
# selection paths
#----------------------------------------------------------------------------
		    
process.hltMu9Path = cms.Path(process.filterHltMu9 *
			      process.beamScrapFilter *
			      process.HBHENoiseFilter *
			      process.primaryVertexFilter *
			      process.patDefaultSequence
		             )
		     
process.hltMu11Path = cms.Path(process.filterHltMu11 *
			       process.beamScrapFilter *
			       process.HBHENoiseFilter *
			       process.primaryVertexFilter *
		               process.patDefaultSequence
		              )	
			      
process.hltMu15Path = cms.Path(process.filterHltMu15 *                               
			       process.beamScrapFilter *
			       process.HBHENoiseFilter *
			       process.primaryVertexFilter *
		               process.patDefaultSequence
		              )			      	     		    		    

## define event selection
process.EventSelection = cms.PSet(
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('hltMu9Path',
                                   'hltMu11Path',
                                   'hltMu15Path',
                                  )
    )
)


## configure output module
process.out = cms.OutputModule("PoolOutputModule",
    process.EventSelection,
    outputCommands = cms.untracked.vstring('drop *'),
    dropMetaData = cms.untracked.string("DROPPED"),                                     
    fileName = cms.untracked.string('RerecoDataL1.root')
)

## save pat output
from PhysicsTools.PatAlgos.patEventContent_cff import *
process.out.outputCommands += patExtraAodEventContent
process.out.outputCommands += patEventContentNoCleaning
process.out.outputCommands += ['drop *_towerMaker_*_*',
                               'keep *_TriggerResults_*_*',
                               'keep *_hltTriggerSummaryAOD_*_*',
                               'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*',
                               'keep *_ak5JetID_*_*'
                               ]

process.outpath = cms.EndPath(process.out)
