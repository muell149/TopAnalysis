import FWCore.ParameterSet.Config as cms

## gen collection creator
from TopAnalysis.TopUtils.GenCandSelector_cfi import *

## gen jet selector
from TopAnalysis.TopUtils.CommonGenJetSelector_cfi import *
## gen muon/electron selector
from TopAnalysis.TopUtils.CommonGenParticleSelector_cfi import *

## jet count filter
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *
## muon count filter
from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *
## electron count filter
from PhysicsTools.PatAlgos.selectionLayer1.electronCountFilter_cfi import *

# define generic name for isolated gen leptons
isolatedGenLeptons  = cms.Sequence( isolatedGenMuons *
                                    isolatedGenElectrons 
                                  )

## set up simple (gen) lepton collections coming directly from W without cuts
simpleGenWMuons     = isolatedGenMuons.clone(src="genParticles",
                                 target = cms.PSet(pdgId  = cms.vstring("13"), status = cms.int32( 3)),
                                 ancestor = cms.PSet(pdgId = cms.vstring("24") )                      )

simpleGenWElectrons = isolatedGenMuons.clone(src="genParticles",
                                 target = cms.PSet(pdgId  = cms.vstring("11"), status = cms.int32( 3)),
                                 ancestor = cms.PSet(pdgId = cms.vstring("24") )                      )

simpleGenWTaus      = isolatedGenMuons.clone(src="genParticles",
                                 target = cms.PSet(pdgId  = cms.vstring("15"), status = cms.int32( 3)),
                                 ancestor = cms.PSet(pdgId = cms.vstring("24") )                      )


## introduce kinematic range for collections with lepton from W
selectedGenWMuons     = selectedGenParticles.clone(src = 'simpleGenWMuons',
                                                   cut = 'abs(eta) < 2.1 & pt > 20.')

selectedGenWElectrons = selectedGenParticles.clone(src = 'simpleGenWElectrons',
                                                   cut = 'abs(eta) < 2.5 & pt > 30.')

selectedGenWTaus      = selectedGenParticles.clone(src = 'simpleGenWTaus',
                                                   cut = 'abs(eta) < 2.1 & pt > 20.')

## configure jet and Muon selections for cutflow
selectedGenJetCollection  = selectedGenJets.clone(src = 'ak5GenJets',
                                                  cut = 'abs(eta) < 2.4 & pt > 30.')

selectedGenMuonCollection = selectedGenParticles.clone(src = 'isolatedGenMuons',
                                                       cut = 'abs(eta) < 2.1 & pt > 20.')

selectedGenElectronCollection = selectedGenParticles.clone(src = 'isolatedGenElectrons',
                                                       cut = 'abs(eta) < 2.5 & pt > 30.')

semiLeptGenCollections = cms.Sequence(selectedGenMuonCollection     *
				      selectedGenElectronCollection *
                                      selectedGenJetCollection
                                      )

## inroduce some distributions to investigate genjet-cut effects
status1GenWMuons    = isolatedGenMuons.clone(src="genParticles",
                                 target = cms.PSet(pdgId  = cms.vstring("13"), status = cms.int32( 1)),
                                 ancestor = cms.PSet(pdgId = cms.vstring("24") )                      )

centralStatus3WMuons = selectedGenParticles.clone(src = 'simpleGenWMuons',
                                                  cut = 'abs(eta) < 2.1'  )

centralStatus1WMuons = selectedGenParticles.clone(src = 'status1GenWMuons',
                                                  cut = 'abs(eta) < 2.1'  )

centralStatus1WTauMuons = selectedGenParticles.clone(src = 'isolatedGenMuons',
                                                     cut = 'abs(eta) < 2.1'  )

## set up the muon selection
genMuonSelection  = countPatMuons.clone(src = 'selectedGenMuonCollection',
                                        minNumber = 1,
                                        maxNumber = 1
                                        )

## set up the electron selection
genElectronSelection = countPatElectrons.clone( src = 'selectedGenElectronCollection',
                                                minNumber = 1,
                                                maxNumber = 1
                                              )

## set up the jet selection 
leadingGenJetSelection = countPatJets.clone(src = 'selectedGenJetCollection',
                                            minNumber = 4
                                            )

## collect different steps within sequences
introduceGenWCollections = cms.Sequence(simpleGenWMuons       *
                                        simpleGenWElectrons   *
                                        simpleGenWTaus        *
                                        selectedGenWMuons     *
                                        selectedGenWElectrons *
                                        selectedGenWTaus      )

fullGenSelection = cms.Sequence(isolatedGenMuons*
                                genMuonSelection*
                                leadingGenJetSelection                                
                                )

introduceTestMuCollections = cms.Sequence(status1GenWMuons*
                                          centralStatus3WMuons*
                                          centralStatus1WMuons*
                                          centralStatus1WTauMuons
                                          )
