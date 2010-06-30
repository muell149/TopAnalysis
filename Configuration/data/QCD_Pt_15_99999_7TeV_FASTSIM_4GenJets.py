# Auto generated configuration file
# using: 
# Revision: 1.168 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: QCD_Pt_120_170_7TeV_cfi.py -s GEN,FASTSIM --pileup=NoPileUp --conditions=FrontierConditions_GlobalTag,MC_3XY_V25::All --eventcontent=AODSIM --beamspot=Early7TeVCollision --datatier GEN-SIM-DIGI-RECO -n 1000
# Afterwards modified: Pt region, number of events to get processed, introduced genJet-Filter between ME generation and detector simulation
import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('FastSimulation.Configuration.RandomServiceInitialization_cff')
process.load('FastSimulation.PileUpProducer.PileUpSimulator7TeV_cfi')
process.load('FastSimulation.Configuration.FamosSequences_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('FastSimulation.Configuration.FamosSequences_cff')
process.load('FastSimulation.Configuration.HLT_1E31_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedParameters_cfi')
process.load('FastSimulation.Configuration.CommonInputs_cff')
process.load('FastSimulation.Configuration.EventContent_cff')

from IOMC.RandomEngine.RandomServiceHelper import RandomNumberServiceHelper
randHelper = RandomNumberServiceHelper(process.RandomNumberGeneratorService)
randHelper.populate()

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.1 $'),
    annotation = cms.untracked.string('QCD_Pt_15_99999_7TeV_cfi.py nevts:1000000'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
process.maxEvents = cms.untracked.PSet(
    input  = cms.untracked.int32(1000000)
    #output = cms.untracked.int32(50000)
)
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)
# Input source
process.source = cms.Source("EmptySource")

# Additional output definition

# Other statements
process.famosPileUp.PileUpSimulator = process.PileUpSimulatorBlock.PileUpSimulator
process.famosPileUp.PileUpSimulator.averageNumber = 0
process.famosSimHits.SimulateCalorimetry = True
process.famosSimHits.SimulateTracking = True
process.famosSimHits.ActivateDecays.comEnergy = 7000
process.simulation = cms.Sequence(process.simulationWithFamos)
process.HLTEndSequence = cms.Sequence(process.reconstructionWithFamos)

# set correct vertex smearing
process.Early7TeVCollisionVtxSmearingParameters.type = cms.string("BetaFunc")
process.famosSimHits.VertexGenerator = process.Early7TeVCollisionVtxSmearingParameters
process.famosPileUp.VertexGenerator = process.Early7TeVCollisionVtxSmearingParameters
# Apply Tracker and Muon misalignment
process.famosSimHits.ApplyAlignment = True
process.misalignedTrackerGeometry.applyAlignment = True

process.misalignedDTGeometry.applyAlignment = True
process.misalignedCSCGeometry.applyAlignment = True

process.GlobalTag.globaltag = 'MC_3XY_V25::All'
process.generator = cms.EDFilter("Pythia6GeneratorFilter",
    pythiaPylistVerbosity = cms.untracked.int32(0),
    filterEfficiency = cms.untracked.double(1.0),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    comEnergy = cms.double(7000.0),
    maxEventsToPrint = cms.untracked.int32(0),
    PythiaParameters = cms.PSet(
        pythiaUESettings = cms.vstring('MSTJ(11)=3     ! Choice of the fragmentation function', 
            'MSTJ(22)=2     ! Decay those unstable particles', 
            'PARJ(71)=10 .  ! for which ctau  10 mm', 
            'MSTP(2)=1      ! which order running alphaS', 
            'MSTP(33)=0     ! no K factors in hard cross sections', 
            'MSTP(51)=10042 ! structure function chosen (external PDF CTEQ6L1)', 
            'MSTP(52)=2     ! work with LHAPDF', 
            'MSTP(81)=1     ! multiple parton interactions 1 is Pythia default', 
            'MSTP(82)=4     ! Defines the multi-parton model', 
            'MSTU(21)=1     ! Check on possible errors during program execution', 
            'PARP(82)=1.8387   ! pt cutoff for multiparton interactions', 
            'PARP(89)=1960. ! sqrts for which PARP82 is set', 
            'PARP(83)=0.5   ! Multiple interactions: matter distrbn parameter', 
            'PARP(84)=0.4   ! Multiple interactions: matter distribution parameter', 
            'PARP(90)=0.16  ! Multiple interactions: rescaling power', 
            'PARP(67)=2.5    ! amount of initial-state radiation', 
            'PARP(85)=1.0  ! gluon prod. mechanism in MI', 
            'PARP(86)=1.0  ! gluon prod. mechanism in MI', 
            'PARP(62)=1.25   ! ', 
            'PARP(64)=0.2    ! ', 
            'MSTP(91)=1      !', 
            'PARP(91)=2.1   ! kt distribution', 
            'PARP(93)=15.0  ! '),
        processParameters = cms.vstring('MSEL=1               ! QCD hight pT processes', 
            'CKIN(3)=15.     ! minimum pt hat for hard interactions', 
            'CKIN(4)=99999.  ! maximum pt hat for hard interactions'),
        parameterSets = cms.vstring('pythiaUESettings', 
            'processParameters')
    )
)

# Path and EndPath definitions
process.generation_step = cms.Path(cms.SequencePlaceholder("randomEngineStateProducer"))
#process.reconstruction = cms.Path(process.reconstructionWithFamos)

# How to filter on generated jets:
# 1) put the gen jet creation between fastsim and MC generator
# 2) define some filters
# 3) put it in front of all paths

process.genJetSelector = cms.EDProducer("CandViewSelector",
                                        src = cms.InputTag("ak5GenJets"),
                                        cut = cms.string("pt > 20 & abs( eta ) < 5.0")
                                        )
process.genJetFilter = cms.EDFilter("CandViewCountFilter",
                                    src = cms.InputTag("genJetSelector"),
                                    minNumber = cms.uint32(4)
                                    )

#process.pgen_fast = cms.Sequence(randomEngineStateProducer+VtxSmeared+genParticles+genParticlesForJets*ak5GenJets)
process.genJetFiltering = cms.Sequence(process.pgen * process.genJetSelector * process.genJetFilter)

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

## process path
process.pat = cms.Path(process.patDefaultSequence)

#-------------------------------------------------
# event weight configuration
#-------------------------------------------------

## add event weight information
#process.load("TopAnalysis.TopUtils.EventWeightPlain_cfi")
#process.eventWeight.nevts= 1
#process.eventWeight.xsec = 1.
#process.eventWeight.eff  = 1.
#process.eventWeight.lumi = 1.

#process.wght = cms.Path(process.eventWeight)

#-------------------------------------------------
# configuration of additional jet collections
#-------------------------------------------------

from PhysicsTools.PatAlgos.tools.jetTools import *

addJetCollection(process,cms.InputTag('ak5PFJets'),'AK5','PF',
                 doJTA        = True,
                 doBTagging   = True,
                 jetCorrLabel = ('AK5', 'PF'),
                 doType1MET   = False,
                 doL1Cleaning = False,
                 doL1Counters = False,
                 genJetCollection=cms.InputTag("ak5GenJets"),
                 doJetID      = False
                 )

## sample type used for flavour dependend jet corrections
process.patJetCorrFactors.corrSample   = 'Summer09_7TeV'
process.patJetCorrFactors.sampleType   = 'ttbar'
process.patJetCorrFactorsAK5PF.corrSample = 'Summer09_7TeV'
process.patJetCorrFactorsAK5PF.sampleType = 'ttbar'

## embedding of jet constituents into the jets
process.patJets.embedCaloTowers = True
process.patJetsAK5PF.embedPFCandidates = True

#-------------------------------------------------
# preselection paths (involved jet collections
# need to be known first)
#-------------------------------------------------

## preselection for ak5 jets 
process.selectedPatJets.cut = 'abs(eta) < 3.0 & pt>20'
process.countPatJetsAK5 = process.countPatJets.clone(src = 'selectedPatJets' , minNumber = 6)
process.ak5Selection = cms.Path(process.countPatJetsAK5 )   

## preselection for ak5 pf jets 
process.selectedPatJetsAK5PF.cut = 'abs(eta) < 3.0 & pt>20'
process.countPatJetsAK5PF = process.countPatJets.clone(src = 'selectedPatJetsAK5PF' , minNumber = 6)
process.ak5PfSelection = cms.Path(process.countPatJetsAK5PF )   

#-------------------------------------------------
# process output; first the event selection is
# defined: only those events that have passed the
# full production path are selected and written
# to file; the event content has been defined
# above
#-------------------------------------------------

## define event selection
process.EventSelection = cms.PSet(
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('ak5PfSelection', 'ak5Selection')
    )
)

## configure output module
process.out = cms.OutputModule("PoolOutputModule",
    process.EventSelection,
    outputCommands = cms.untracked.vstring('drop *'),
    dropMetaDataForDroppedData = cms.untracked.bool(True),                                     
    fileName = cms.untracked.string('patTuple.root')
)

## add selectedPatCandidates
from PhysicsTools.PatAlgos.tools.coreTools import removeCleaning
removeCleaning(process)
## add PfMET
from PhysicsTools.PatAlgos.tools.metTools import addPfMET
addPfMET(process)

# save PAT Layer 1 output
from PhysicsTools.PatAlgos.patEventContent_cff import *
process.out.outputCommands += patTriggerEventContent
process.out.outputCommands += patExtraAodEventContent
process.out.outputCommands += patEventContentNoCleaning
process.out.outputCommands += ["keep *_selectedPatJets*_*_*",
                               "keep *_patMETs*_*_*"]
#process.out.outputCommands += ["keep *_eventWeight_*_*"]
# drop stuff which is not needed
process.out.outputCommands += ["drop *_towerMaker_*_*"]

process.outpath = cms.EndPath(process.out)


# Schedule definition
process.schedule = cms.Schedule(process.generation_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.ak5Selection,process.ak5PfSelection,process.outpath])#,process.out_step,process.out_stepAOD])process.EventSelection,
# special treatment in case of production filter sequence  
for path in process.paths: 
#    getattr(process,path)._seq = process.generator*getattr(process,path)._seq
    getattr(process,path)._seq = process.generator * process.genJetFiltering * process.famosWithEverything * process.patDefaultSequence * getattr(process,path)._seq
