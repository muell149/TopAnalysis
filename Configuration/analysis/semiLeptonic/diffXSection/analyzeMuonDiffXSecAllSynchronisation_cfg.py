## ---
##    this configfile does the same like analyzeEventIdDiffXSecCorrected_cfg.py
##    but is done without filtering on gen level
##    In addition: cutflow SYNCHRONISATION (i.e. without skipping non iso leptons)
## ---

## remove ttbar gen level event filter
synchSample = "ttbar" #"data" ##"wjets" #"ttbar"
decayChannel = "muon" #'electron'
additionalEventWeights  = False
removeGenTtbar = True
eventFilter='all'
cutflowSynch  = True
effSFReweigthing = False
BtagReweigthing = False
applyKinFit = False
printCutflowEvents = True
MCversion = "Fall11"
if(synchSample == "data"):
    PUreweigthing = False
    jsonFile = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions11/7TeV/Prompt/Cert_160404-172802_7TeV_PromptReco_Collisions11_JSON_v3.txt"
    runningOnData = "data"
    ## use L2L3Residual correction in analyzers
    corrLevel="L2L3Residual"

## get the mother file
## if JER rescaling is desired:
#execfile("analyzeMuonDiffXSecCorrected_cfg.py")
## if no JER rescaling is desired:
execfile("analyzeTopDiffXSec_cfg.py")

## ttbar file:
if(synchSample == "ttbar"):
  if(MCversion=="Summer11"):
    fileNames = ["/store/mc/Summer11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FEEE3638-\F297-E011-AAF8-00304867BEC0.root"]
  elif(MCversion=="Fall11"):
    fileNames = ["/store/mc/Fall11/TTJets_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/00CAD0AC-17FA-E011-A4F4-00304867905A.root"]

## WJets file:
if(synchSample == "wjets"):
    fileNames = ["/store/mc/Summer11/WJetsToLNu_TuneZ2_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0001/FED96BE1-859A-E011-836E-001A92971B56.root"]
    
## data file:
if(synchSample == "data"):
    fileNames = ["/store/data/Run2011A/SingleMu/AOD/PromptReco-v6/000/172/620/92127CFF-41C0-E011-ABC2-BCAEC532971F.root"]
    
process.source.fileNames = fileNames
print "analyzed sample: ", fileNames

## reduce events
process.maxEvents.input = 10000
if(synchSample == "data"):
    process.maxEvents.input = -1
    


## skip first n events of root file
#process.source.skipEvents = 9700

## reduce output (needed when running over QCD samples)
process.MessageLogger.cerr.FwkReport.reportEvery = 100

## change output name 
process.TFileService.fileName = 'analyzeDiffXSecCorr_testAllSynchronisation.root'

## PU weighting input distribution
#process.eventWeightPU.MCSampleFile = cms.FileInPath("TopAnalysis/TopUtils/data/Pileup_2011_to_172802_LP_LumiScale.root")

## choose unprescaled trigger
process.hltFilter.TriggerResultsTag = "TriggerResults::HLT"
#process.hltFilter.HLTPaths = ["HLT_Mu15_v*"]
#process.hltFilter.HLTPaths = ["HLT_Mu17_TriCentralJet30_v*"]
#process.hltFilter.HLTPaths = ["*"]

## change veto isolation
#process.looseMuons.cut = 'isGlobalMuon & abs(eta) < 2.5 & pt > 10. & (chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.25'
#process.looseElectrons.cut = 'et > 15. & abs(eta) < 2.5 & (chargedHadronIso+neutralHadronIso+photonIso)/et < 0.25'

## switch DeltaR(mu,jet)>0.3 cut off
process.tightMuons.src = "trackMuons"
#process.tightMuons.cut = '(chargedHadronIso+neutralHadronIso+photonIso)/pt < 0.1'
#process.trackMuons.src = "selectedPatMuons"
#process.goodJetsPF20.cut = 'pt > 20. && abs(eta) < 2.4 && numberOfDaughters > 1 && chargedEmEnergyFraction < 0.99 && neutralHadronEnergyFraction < 0.99 && neutralEmEnergyFraction < 0.99 && (chargedHadronEnergyFraction > 0. || abs(eta) >= 2.4) && (chargedMultiplicity > 0 || abs(eta) >= 2.4)'
#process.GlobalTag.globaltag = cms.string('START42_V12::All')
#process.muonCuts = cms.Sequence(process.muonSelection)
#process.goodOfflinePrimaryVertices.filterParams.minNdof=7
#process.PVSelection.minNdof = 7
#process.pfMuonsFromVertex.vertices = cms.InputTag("offlinePrimaryVertices")
#process.pfElectronsFromVertex.vertices = cms.InputTag("offlinePrimaryVertices")
#process.patMuons.pvSrc = cms.InputTag("offlinePrimaryVertices")
#process.patElectrons.pvSrc = cms.InputTag("offlinePrimaryVertices")
#process.patElectrons.usePV = False

#process.pfPileUp.checkClosestZVertex = False

#process.goodJetsPF20     = selectedPatJets.clone(src = 'selectedPatJets',
                                         #cut = 'abs(eta) < 2.4 & pt > 20.          &'
                                               #'chargedHadronEnergyFraction > 0.0  &'
                                               #'neutralHadronEnergyFraction < 0.99 &'
                                               #'chargedEmEnergyFraction     < 0.99 &'
                                               #'neutralEmEnergyFraction     < 0.99 &'
                                               #'chargedMultiplicity > 0            &'
                                               ##'numberOfDaughters > 1'
                                                 #'nConstituents > 1'
                                         #)

process.load("TopQuarkAnalysis.Examples.TopMuonAnalyzer_cfi")
process.load("TopQuarkAnalysis.Examples.TopElecAnalyzer_cfi")
process.load("TopQuarkAnalysis.Examples.TopJetAnalyzer_cfi")

process.analyzeElecEleVeto = process.analyzeElec.clone()

process.p1.replace(process.muonSelection, process.muonSelection * process.analyzeMuon * process.analyzeElec * process.analyzeJet)
process.p1.replace(process.electronVeto, process.electronVeto * process.analyzeElecEleVeto)

##---------------------------
## prints event ID in txt file
##---------------------------
if(printCutflowEvents):
    process.load("TopAnalysis.TopAnalyzer.EventIdAnalyzer_cfi")
    
    #process.analyzeEventIdCut1 = process.analyzeEventId.clone( 
	#verbose = True
	#)

    process.analyzeEventIdCut1 = process.analyzeEventId.clone( 
	verbose = False,
	textFileName = cms.string("cutflowEventsCut1"+synchSample+".txt")
	)
    process.analyzeEventIdCut2 = process.analyzeEventId.clone( 
	verbose = False,
	textFileName = cms.string("cutflowEventsCut2"+synchSample+".txt")
	)
    process.analyzeEventIdCut3 = process.analyzeEventId.clone( 
	verbose = False,
	textFileName = cms.string("cutflowEventsCut3"+synchSample+".txt")
	)
    process.analyzeEventIdCut4a = process.analyzeEventId.clone( 
	verbose = False,
	textFileName = cms.string("cutflowEventsCut4a"+synchSample+".txt")
	)
    process.analyzeEventIdCut4b = process.analyzeEventId.clone( 
	verbose = False,
	textFileName = cms.string("cutflowEventsCut4b"+synchSample+".txt")
	)
    process.analyzeEventIdCut4c = process.analyzeEventId.clone( 
	verbose = False,
	textFileName = cms.string("cutflowEventsCut4c"+synchSample+".txt")
	)
    process.analyzeEventIdCut4d = process.analyzeEventId.clone( 
	verbose = False,
	textFileName = cms.string("cutflowEventsCut4d"+synchSample+".txt")
	)
    process.analyzeEventIdCut5 = process.analyzeEventId.clone(
	verbose = False,
	textFileName = cms.string("cutflowEventsCut5"+synchSample+".txt")
	)
    
    process.p1.replace(process.muonSelection, process.muonSelection * process.analyzeEventIdCut1)
    process.p1.replace(process.secondMuonVeto, process.secondMuonVeto * process.analyzeEventIdCut2)
    process.p1.replace(process.electronVeto, process.electronVeto * process.analyzeEventIdCut3)
    process.p1.replace(process.leadingJetSelectionNjets1, process.leadingJetSelectionNjets1 * process.analyzeEventIdCut4a)
    process.p1.replace(process.leadingJetSelectionNjets2, process.leadingJetSelectionNjets2 * process.analyzeEventIdCut4b)
    process.p1.replace(process.leadingJetSelectionNjets3, process.leadingJetSelectionNjets3 * process.analyzeEventIdCut4c)
    process.p1.replace(process.leadingJetSelectionNjets4, process.leadingJetSelectionNjets4 * process.analyzeEventIdCut5)
