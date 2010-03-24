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
    version = cms.untracked.string('$Revision: 1.168 $'),
    annotation = cms.untracked.string('QCD_Pt_15_99999_7TeV_cfi.py nevts:1000'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.maxEvents = cms.untracked.PSet(
    input  = cms.untracked.int32(1000000)
    #output = cms.untracked.int32(50000)
)
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)
# Input source
process.source = cms.Source("EmptySource")

# Output definition
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = process.AODSIMEventContent.outputCommands,
    fileName = cms.untracked.string('QCD_Pt_15_99999_7TeV_cfi_py_GEN_FASTSIM.root'),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-DIGI-RECO'),
        filterName = cms.untracked.string('')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)

# AodOutput definition
process.aodOutput = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('drop *', 
        'drop *', 
        'keep *_castorreco_*_*', 
        'keep *_CastorTowerReco_*_*', 
        'keep *_CastorClusterRecoAntiKt07_*_*', 
        'keep *_CastorJetEgammaRecoAntiKt07_*_*', 
        'keep *_selectDigi_*_*', 
        'keep EcalRecHitsSorted_reducedEcalRecHits*_*_*', 
        'keep *_hybridSuperClusters_*_*', 
        'keep recoSuperClusters_correctedHybridSuperClusters_*_*', 
        'keep *_multi5x5BasicClusters_*_*', 
        'keep recoSuperClusters_multi5x5SuperClusters_*_*', 
        'keep recoSuperClusters_multi5x5SuperClustersWithPreshower_*_*', 
        'keep recoSuperClusters_correctedMulti5x5SuperClustersWithPreshower_*_*', 
        'keep recoPreshowerClusters_multi5x5SuperClustersWithPreshower_*_*', 
        'keep recoPreshowerClusterShapes_multi5x5PreshowerClusterShape_*_*', 
        'drop recoClusterShapes_*_*_*', 
        'drop recoBasicClustersToOnerecoClusterShapesAssociation_*_*_*', 
        'drop recoBasicClusters_multi5x5BasicClusters_multi5x5BarrelBasicClusters_*', 
        'drop recoSuperClusters_multi5x5SuperClusters_multi5x5BarrelSuperClusters_*', 
        'keep recoTracks_GsfGlobalElectronTest_*_*', 
        'keep recoGsfTracks_electronGsfTracks_*_*', 
        'keep recoTracks_generalTracks_*_*', 
        'keep recoTracks_rsWithMaterialTracks_*_*', 
        'keep recoTracks_ctfPixelLess_*_*', 
        'keep *_dedxTruncated40_*_*', 
        'keep *_dedxHarmonic2_*_*', 
        'keep *_kt4CaloJets_*_*', 
        'keep *_kt6CaloJets_*_*', 
        'keep *_ak5CaloJets_*_*', 
        'keep *_ak7CaloJets_*_*', 
        'keep *_iterativeCone5CaloJets_*_*', 
        'keep *_iterativeCone15CaloJets_*_*', 
        'keep *_sisCone5CaloJets_*_*', 
        'keep *_sisCone7CaloJets_*_*', 
        'keep *_kt4PFJets_*_*', 
        'keep *_kt6PFJets_*_*', 
        'keep *_ak5PFJets_*_*', 
        'keep *_ak7PFJets_*_*', 
        'keep *_iterativeCone5PFJets_*_*', 
        'keep *_sisCone5PFJets_*_*', 
        'keep *_sisCone7PFJets_*_*', 
        'keep *_JetPlusTrackZSPCorJetIcone5_*_*', 
        'keep *_JetPlusTrackZSPCorJetSiscone5_*_*', 
        'keep *_JetPlusTrackZSPCorJetAntiKt5_*_*', 
        'keep *_ak5TrackJets_*_*', 
        'keep *_kt4TrackJets_*_*', 
        'keep recoRecoChargedRefCandidates_trackRefsForJets_*_*', 
        'keep *_caloTowers_*_*', 
        'keep *_towerMaker_*_*', 
        'keep *_ic5JetTracksAssociatorAtVertex_*_*', 
        'keep *_sisCone5JetTracksAssociatorAtVertex_*_*', 
        'keep *_ak5JetTracksAssociatorAtVertex_*_*', 
        'keep *_ak7JetTracksAssociatorAtVertex_*_*', 
        'keep *_iterativeCone5JetExtender_*_*', 
        'keep *_sisCone5JetExtender_*_*', 
        'keep *_kt4JetExtender_*_*', 
        'keep *_ak5JetExtender_*_*', 
        'keep *_ak7JetExtender_*_*', 
        'keep *_ak5JetID_*_*', 
        'keep *_ak7JetID_*_*', 
        'keep *_sc5JetID_*_*', 
        'keep *_sc7JetID_*_*', 
        'keep *_ic5JetID_*_*', 
        'keep *_kt4JetID_*_*', 
        'keep *_kt6JetID_*_*', 
        'keep recoCaloMETs_*_*_*', 
        'keep recoMETs_*_*_*', 
        'keep recoPFMETs_*_*_*', 
        'keep recoMuonMETCorrectionDataedmValueMap_*_*_*', 
        'drop recoHcalNoiseRBXs_*_*_*', 
        'keep HcalNoiseSummary_*_*_*', 
        'keep *GlobalHaloData_*_*_*', 
        'keep *BeamHaloSummary_*_*_*', 
        'keep recoTracks_standAloneMuons_*_*', 
        'keep recoTrackExtras_standAloneMuons_*_*', 
        'keep TrackingRecHitsOwned_standAloneMuons_*_*', 
        'keep recoTracks_globalMuons_*_*', 
        'keep recoTrackExtras_globalMuons_*_*', 
        'keep recoTracks_tevMuons_*_*', 
        'keep recoTrackExtras_tevMuons_*_*', 
        'keep recoTracksToOnerecoTracksAssociation_tevMuons_*_*', 
        'keep recoTracks_generalTracks_*_*', 
        'keep recoMuons_muons_*_*', 
        'keep booledmValueMap_muid*_*_*', 
        'keep recoMuonTimeExtraedmValueMap_muons_*_*', 
        'keep recoCaloMuons_calomuons_*_*', 
        'keep recoTracks_cosmicMuons_*_*', 
        'keep recoTrackExtras_cosmicMuons_*_*', 
        'keep TrackingRecHitsOwned_cosmicMuons_*_*', 
        'keep recoTracks_globalCosmicMuons_*_*', 
        'keep recoTrackExtras_globalCosmicMuons_*_*', 
        'keep TrackingRecHitsOwned_globalCosmicMuons_*_*', 
        'keep recoMuons_muonsFromCosmics_*_*', 
        'keep recoTracks_cosmicMuons1Leg_*_*', 
        'keep recoTrackExtras_cosmicMuons1Leg_*_*', 
        'keep TrackingRecHitsOwned_cosmicMuons1Leg_*_*', 
        'keep recoTracks_globalCosmicMuons1Leg_*_*', 
        'keep recoTrackExtras_globalCosmicMuons1Leg_*_*', 
        'keep TrackingRecHitsOwned_globalCosmicMuons1Leg_*_*', 
        'keep recoMuons_muonsFromCosmics1Leg_*_*', 
        'keep *_muIsoDepositTk_*_*', 
        'keep *_muIsoDepositCalByAssociatorTowers_*_*', 
        'keep *_muIsoDepositCalByAssociatorHits_*_*', 
        'keep *_muIsoDepositJets_*_*', 
        'keep *_impactParameterTagInfos_*_*', 
        'keep *_trackCountingHighEffBJetTags_*_*', 
        'keep *_trackCountingHighPurBJetTags_*_*', 
        'keep *_jetProbabilityBJetTags_*_*', 
        'keep *_jetBProbabilityBJetTags_*_*', 
        'keep *_secondaryVertexTagInfos_*_*', 
        'keep *_simpleSecondaryVertexBJetTags_*_*', 
        'keep *_combinedSecondaryVertexBJetTags_*_*', 
        'keep *_combinedSecondaryVertexMVABJetTags_*_*', 
        'keep *_btagSoftElectrons_*_*', 
        'keep *_softPFElectrons_*_*', 
        'keep *_softElectronTagInfos_*_*', 
        'keep *_softElectronBJetTags_*_*', 
        'keep *_softElectronByIP3dBJetTags_*_*', 
        'keep *_softElectronByPtBJetTags_*_*', 
        'keep *_softMuonTagInfos_*_*', 
        'keep *_softMuonBJetTags_*_*', 
        'keep *_softMuonByIP3dBJetTags_*_*', 
        'keep *_softMuonByPtBJetTags_*_*', 
        'keep *_pfRecoTauTagInfoProducer_*_*', 
        'keep *_fixedConePFTauProducer*_*_*', 
        'keep *_fixedConePFTauDiscrimination*_*_*', 
        'keep *_fixedConeHighEffPFTauProducer*_*_*', 
        'keep *_fixedConeHighEffPFTauDiscrimination*_*_*', 
        'keep *_shrinkingConePFTauProducer*_*_*', 
        'keep *_shrinkingConePFTauDecayModeIndexProducer*_*_*', 
        'keep *_shrinkingConePFTauDiscrimination*_*_*', 
        'keep *_caloRecoTauTagInfoProducer_*_*', 
        'keep recoCaloTaus_caloRecoTauProducer*_*_*', 
        'keep *_caloRecoTauDiscrimination*_*_*', 
        'keep  *_offlinePrimaryVertices_*_*', 
        'keep  *_offlinePrimaryVerticesWithBS_*_*', 
        'keep  *_offlinePrimaryVerticesFromCosmicTracks_*_*', 
        'keep  *_nuclearInteractionMaker_*_*', 
        'keep *_generalV0Candidates_*_*', 
        'keep recoGsfElectronCores_gsfElectronCores_*_*', 
        'keep recoGsfElectrons_gsfElectrons_*_*', 
        'keep floatedmValueMap_eidRobustLoose_*_*', 
        'keep floatedmValueMap_eidRobustTight_*_*', 
        'keep floatedmValueMap_eidRobustHighEnergy_*_*', 
        'keep floatedmValueMap_eidLoose_*_*', 
        'keep floatedmValueMap_eidTight_*_*', 
        'keep recoPhotonCores_photonCore_*_*', 
        'keep recoPhotons_photons_*_*', 
        'keep recoConversions_conversions_*_*', 
        'drop *_conversions_uncleanedConversions_*', 
        'keep recoConversions_trackerOnlyConversions_*_*', 
        'keep recoTracks_ckfOutInTracksFromConversions_*_*', 
        'keep recoTracks_ckfInOutTracksFromConversions_*_*', 
        'keep *_PhotonIDProd_*_*', 
        'keep *_hfRecoEcalCandidate_*_*', 
        'keep *_hfEMClusters_*_*', 
        'drop CaloTowersSorted_towerMakerPF_*_*', 
        'drop *_pfElectronTranslator_*_*', 
        'keep recoPFCandidates_*_*_*', 
        'keep recoCaloClusters_pfElectronTranslator_*_*', 
        'keep recoPreshowerClusters_pfElectronTranslator_*_*', 
        'keep recoSuperClusters_pfElectronTranslator_*_*', 
        'keep *_offlineBeamSpot_*_*', 
        'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*', 
        'keep *_l1GtRecord_*_*', 
        'keep *_l1GtTriggerMenuLite_*_*', 
        'keep *_l1extraParticles_*_*', 
        'keep LumiSummary_lumiProducer_*_*', 
        'drop *_hlt*_*_*', 
        'keep *_hltL1GtObjectMap_*_*', 
        'keep edmTriggerResults_*_*_*', 
        'keep triggerTriggerEvent_*_*_*', 
        'keep *_MEtoEDMConverter_*_*', 
        'keep L1AcceptBunchCrossings_*_*_*', 
        'keep L1TriggerScalerss_*_*_*', 
        'keep Level1TriggerScalerss_*_*_*', 
        'keep LumiScalerss_*_*_*', 
        'keep BeamSpotOnlines_*_*_*', 
        'keep DcsStatuss_*_*_*', 
        'keep *_logErrorHarvester_*_*', 
        'keep LHERunInfoProduct_source_*_*', 
        'keep LHEEventProduct_source_*_*', 
        'keep GenRunInfoProduct_generator_*_*', 
        'keep GenEventInfoProduct_generator_*_*', 
        'keep *_genParticles_*_*', 
        'keep *_allTrackMCMatch_*_*', 
        'keep *_kt4GenJets_*_*', 
        'keep *_kt6GenJets_*_*', 
        'keep *_ak5GenJets_*_*', 
        'keep *_ak7GenJets_*_*', 
        'keep *_iterativeCone5GenJets_*_*', 
        'keep *_sisCone5GenJets_*_*', 
        'keep *_sisCone7GenJets_*_*', 
        'keep *_genParticle_*_*', 
        'keep recoGenMETs_*_*_*', 
        'keep *_MEtoEDMConverter_*_*', 
        'keep LHERunInfoProduct_source_*_*', 
        'keep LHEEventProduct_source_*_*', 
        'keep GenRunInfoProduct_generator_*_*', 
        'keep GenEventInfoProduct_generator_*_*', 
        'keep *_genParticles_*_*', 
        'keep recoTracks_iterativeGSWithMaterialTracks_*_*', 
        'keep recoMuons_paramMuons_*_*', 
        'keep *_muParamGlobalIsoDepositCtfTk_*_*', 
        'keep *_muParamGlobalIsoDepositCalByAssociatorTowers_*_*', 
        'keep *_muParamGlobalIsoDepositCalByAssociatorHits_*_*', 
        'keep *_muParamGlobalIsoDepositJets_*_*', 
        'keep l1extraL1MuonParticles_l1ParamMuons_*_*'),
    fileName = cms.untracked.string('QCD_Pt_15_99999_7TeV_cfi_py_GEN_FASTSIM_AOD.root'),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('AODSIM')
    )
)

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
process.reconstruction = cms.Path(process.reconstructionWithFamos)
process.out_step = cms.EndPath(process.output)
process.out_stepAOD = cms.EndPath(process.aodOutput)


# How to filter on generated jets:
# 1) put the gen jet creation between fastsim and MC generator
# 2) define some filters
# 3) put it in front of all paths

process.someGenJetSelector = cms.EDProducer("CandViewSelector",
                                        src = cms.InputTag("ak5GenJets"),
                                        cut = cms.string("pt > 20 & abs( eta ) < 5.0")
                                        )
process.someGenJetFilter = cms.EDFilter("CandViewCountFilter",
                                        src = cms.InputTag("someGenJetSelector"),
                                        minNumber = cms.uint32(4)
                                       )

process.genJetFiltering = cms.Sequence(process.pgen * process.someGenJetSelector * process.someGenJetFilter)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.reconstruction,process.out_step,process.out_stepAOD])
# special treatment in case of production filter sequence  
for path in process.paths: 
#    getattr(process,path)._seq = process.generator*getattr(process,path)._seq
    getattr(process,path)._seq = process.generator * process.genJetFiltering * getattr(process,path)._seq
