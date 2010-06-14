import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file creating histograms needed for the
# determination of the charge asymmetry parameter.
# This is done for different jet multiplicities
# and all kind of leptons
#-------------------------------------------------
process = cms.Process("p1")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 100

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    '/store/user/henderle/Spring10/WJets_MAD_new/PATtuple_100_1.root'
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

#-------------------------------------------------
# charge asymmetry analysis
#-------------------------------------------------

## module to create plots for calculation of charge asymmetry parameter
process.load("TopAnalysis.TopAnalyzer.ChargeAsymmetry_cfi")
## module that contains gen lepton collections and cutflows
process.load("TopAnalysis.TopFilter.sequences.genSelection_cff")
## cross section module to plot gen niveau selected events
process.load("TopAnalysis.TopAnalyzer.MuonCrossSection_cfi")
## import gen Muon selection
from TopAnalysis.TopFilter.sequences.genSelection_cff import isolatedGenMuons
process.isolatedGenMuons = isolatedGenMuons
from TopAnalysis.TopFilter.sequences.genSelection_cff import selectedGenJetCollection
process.selectedGenJetCollection = selectedGenJetCollection 

## set up basic charge asymmetry plot modules for all leptons
process.analyzeChargeAsymmetryLeptons    = process.analyzeChargeAsymmetry.clone(src = 'genParticles',
                                           analyze = cms.PSet(index = cms.int32(-1),
                                                              lepton= cms.int32(-1)))
process.analyzeChargeAsymmetryMuons      = process.analyzeChargeAsymmetry.clone(src = 'selectedGenMuonCollection',
                                           analyze = cms.PSet(index = cms.int32(-1),
                                                              lepton= cms.int32(13)))
process.analyzeChargeAsymmetryWMuons     = process.analyzeChargeAsymmetry.clone(src = 'selectedGenWMuons',
                                           analyze = cms.PSet(index = cms.int32(-1),
                                                              lepton= cms.int32(13)))
process.analyzeChargeAsymmetryWElectrons = process.analyzeChargeAsymmetry.clone(src = 'selectedGenWElectrons',
                                           analyze = cms.PSet(index = cms.int32(-1),
                                                              lepton= cms.int32(11)))
process.analyzeChargeAsymmetryWTaus      = process.analyzeChargeAsymmetry.clone(src = 'selectedGenWTaus',
                                           analyze = cms.PSet(index = cms.int32(-1),
                                                              lepton= cms.int32(15)))

## plot some differential Kinematic quantities of the unselected gen lepton selections
process.analyzeMuon     = process.analyzeCrossSectionGenMuon.clone(srcA = 'simpleGenWMuons'    ,analyze= cms.PSet(index = cms.int32(-1)))
process.analyzeElectron = process.analyzeCrossSectionGenMuon.clone(srcA = 'simpleGenWElectrons',analyze= cms.PSet(index = cms.int32(-1)))
process.analyzeTau      = process.analyzeCrossSectionGenMuon.clone(srcA = 'simpleGenWTaus'     ,analyze= cms.PSet(index = cms.int32(-1)))

## set up jet cut steps
process.leadingGenJetSelectionNjets1= process.leadingGenJetSelection.clone(src = 'selectedGenJetCollection', minNumber = 1)
process.leadingGenJetSelectionNjets2= process.leadingGenJetSelection.clone(src = 'selectedGenJetCollection', minNumber = 2)
process.leadingGenJetSelectionNjets3= process.leadingGenJetSelection.clone(src = 'selectedGenJetCollection', minNumber = 3)
process.leadingGenJetSelectionNjets4= process.leadingGenJetSelection.clone(src = 'selectedGenJetCollection', minNumber = 4)

## clone charge asymmetry plots for different cut steps
process.analyzeChargeAsymmetryLeptonsNjets1    = process.analyzeChargeAsymmetryLeptons.clone()   
process.analyzeChargeAsymmetryMuonsNjets1      = process.analyzeChargeAsymmetryMuons.clone()
process.analyzeChargeAsymmetryWMuonsNjets1     = process.analyzeChargeAsymmetryWMuons.clone()
process.analyzeChargeAsymmetryWElectronsNjets1 = process.analyzeChargeAsymmetryWElectrons.clone()
process.analyzeChargeAsymmetryWTausNjets1      = process.analyzeChargeAsymmetryWTaus.clone()
process.analyzeChargeAsymmetryLeptonsNjets2    = process.analyzeChargeAsymmetryLeptons.clone()   
process.analyzeChargeAsymmetryMuonsNjets2      = process.analyzeChargeAsymmetryMuons.clone()
process.analyzeChargeAsymmetryWMuonsNjets2     = process.analyzeChargeAsymmetryWMuons.clone()
process.analyzeChargeAsymmetryWElectronsNjets2 = process.analyzeChargeAsymmetryWElectrons.clone()
process.analyzeChargeAsymmetryWTausNjets2      = process.analyzeChargeAsymmetryWTaus.clone()
process.analyzeChargeAsymmetryLeptonsNjets3    = process.analyzeChargeAsymmetryLeptons.clone()   
process.analyzeChargeAsymmetryMuonsNjets3      = process.analyzeChargeAsymmetryMuons.clone()
process.analyzeChargeAsymmetryWMuonsNjets3     = process.analyzeChargeAsymmetryWMuons.clone()
process.analyzeChargeAsymmetryWElectronsNjets3 = process.analyzeChargeAsymmetryWElectrons.clone()
process.analyzeChargeAsymmetryWTausNjets3      = process.analyzeChargeAsymmetryWTaus.clone()
process.analyzeChargeAsymmetryLeptonsNjets4    = process.analyzeChargeAsymmetryLeptons.clone()   
process.analyzeChargeAsymmetryMuonsNjets4      = process.analyzeChargeAsymmetryMuons.clone()
process.analyzeChargeAsymmetryWMuonsNjets4     = process.analyzeChargeAsymmetryWMuons.clone()
process.analyzeChargeAsymmetryWElectronsNjets4 = process.analyzeChargeAsymmetryWElectrons.clone()
process.analyzeChargeAsymmetryWTausNjets4      = process.analyzeChargeAsymmetryWTaus.clone()

## collect the plot modules for each cut step
process.analyzeChargeAsymmetryNjets1= cms.Sequence(#process.analyzeChargeAsymmetryLeptonsNjets1 +
                                                   process.analyzeChargeAsymmetryMuonsNjets1   +
                                                   process.analyzeChargeAsymmetryWMuonsNjets1  +
                                                   process.analyzeChargeAsymmetryWElectronsNjets1 +
                                                   process.analyzeChargeAsymmetryWTausNjets1
                                                   )
process.analyzeChargeAsymmetryNjets2= cms.Sequence(#process.analyzeChargeAsymmetryLeptonsNjets2 +
                                                   process.analyzeChargeAsymmetryMuonsNjets2 +  
                                                   process.analyzeChargeAsymmetryWMuonsNjets2 + 
                                                   process.analyzeChargeAsymmetryWElectronsNjets2 +
                                                   process.analyzeChargeAsymmetryWTausNjets2
                                                   )
process.analyzeChargeAsymmetryNjets3= cms.Sequence(#process.analyzeChargeAsymmetryLeptonsNjets3 +
                                                   process.analyzeChargeAsymmetryMuonsNjets3  + 
                                                   process.analyzeChargeAsymmetryWMuonsNjets3 + 
                                                   process.analyzeChargeAsymmetryWElectronsNjets3 +
                                                   process.analyzeChargeAsymmetryWTausNjets3
                                                   )

process.analyzeChargeAsymmetryNjets4= cms.Sequence(#process.analyzeChargeAsymmetryLeptonsNjets4 +
                                                   process.analyzeChargeAsymmetryMuonsNjets4  + 
                                                   process.analyzeChargeAsymmetryWMuonsNjets4 + 
                                                   process.analyzeChargeAsymmetryWElectronsNjets4 +
                                                   process.analyzeChargeAsymmetryWTausNjets4
                                                   )

## register TFileService
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('analyzeChargeAsymmetry.root')

)

process.p1 = cms.Path(#introduce selections
                      process.introduceGenWCollections        *
                      process.isolatedGenMuons                *
                      process.semiLeptGenCollections          *
                      process.introduceTestMuCollections      *
                      #look @ collections
                      process.analyzeMuon                     *                     
                      process.analyzeElectron                 *
                      process.analyzeTau                      *
                      #charge asymmetry without jet selection
                      #process.analyzeChargeAsymmetryLeptons   *
                      process.analyzeChargeAsymmetryMuons     *
                      process.analyzeChargeAsymmetryWMuons    *  
                      process.analyzeChargeAsymmetryWElectrons*
                      process.analyzeChargeAsymmetryWTaus     *
                      #charge asymmetry min.1 genJet
                      process.leadingGenJetSelectionNjets1    *
                      process.analyzeChargeAsymmetryNjets1    *
                      #charge asymmetry min.2 genJet
                      process.leadingGenJetSelectionNjets2    *
                      process.analyzeChargeAsymmetryNjets2    *
                      #charge asymmetry min.3 genJet
                      process.leadingGenJetSelectionNjets3    *
                      process.analyzeChargeAsymmetryNjets3    *
                      #charge asymmetry min.4 genJet
                      process.leadingGenJetSelectionNjets4    *
                      process.analyzeChargeAsymmetryNjets4    
                      )


## ## TEST area

## ## configure w->mu(stat3) filter
## process.genStatus3MuonSelection = process.genMuonSelection.clone(src = 'centralStatus3WMuons',
##                                                                  minNumber = 1,
##                                                                  maxNumber = 1)
## ## configure modules
## process.centralStatus1MuonsFromW = process.analyzeChargeAsymmetry.clone(src = 'centralStatus1WMuons',
##                                                                         analyze = cms.PSet(index = cms.int32(-1),
##                                                                                            lepton= cms.int32(13)))

## process.centralStatus3MuonsFromW = process.analyzeChargeAsymmetry.clone(src = 'centralStatus3WMuons',
##                                                                         analyze = cms.PSet(index = cms.int32(-1),
##                                                                                            lepton= cms.int32(13)))

## process.centralStatus1MuonsFromWorWTau = process.analyzeChargeAsymmetry.clone(src = 'centralStatus1WTauMuons',
##                                                                               analyze = cms.PSet(index = cms.int32(-1),
##                                                                                                  lepton= cms.int32(13)))

## process.centralStatus1MuonsFromWNjets1 = process.centralStatus1MuonsFromW.clone()
## process.centralStatus3MuonsFromWNjets1 = process.centralStatus3MuonsFromW.clone()
## process.centralStatus1MuonsFromWorWTauNjets1 = process.centralStatus1MuonsFromWorWTau.clone()

## ## a) status 3 #mu and status 1 #mu from W->mu & W->tau->mu
## process.p1 = cms.Path(#introduce selections
##                       process.isolatedGenMuons                *
##                       process.introduceGenWCollections        *
##                       process.semiLeptGenCollections          *
##                       process.introduceTestMuCollections      *
##                       #charge asymmetry without jet selection
##                       process.centralStatus3MuonsFromW        *
##                       process.centralStatus1MuonsFromWorWTau  *
##                       #charge asymmetry min.1 genJet
##                       process.leadingGenJetSelectionNjets1    *
##                       process.centralStatus3MuonsFromWNjets1       *
##                       process.centralStatus1MuonsFromWorWTauNjets1                       
##                       )

## ## b) status 1 #mu from W->mu only
## process.p2 = cms.Path(#introduce selections
##                       process.isolatedGenMuons                *
##                       process.introduceGenWCollections        *
##                       process.semiLeptGenCollections          *
##                       process.introduceTestMuCollections      *
##                       #do selection for W->Mu
##                       process.genStatus3MuonSelection         *
##                       #charge asymmetry without jet selection
##                       process.centralStatus1MuonsFromW        *
##                       #charge asymmetry min.1 genJet
##                       process.leadingGenJetSelectionNjets1    *
##                       process.centralStatus1MuonsFromWNjets1  
##                       )
