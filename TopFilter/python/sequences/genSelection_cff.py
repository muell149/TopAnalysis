import FWCore.ParameterSet.Config as cms

## gen collection creator
from TopAnalysis.TopUtils.GenCandSelector_cfi import *

## gen jet selector
from TopAnalysis.TopUtils.CommonGenJetSelector_cfi import *
## gen muon selector
from TopAnalysis.TopUtils.CommonGenParticleSelector_cfi import *

## jet count filter
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *
## muon count filter
from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *

## set up simple (gen) lepton collections coming directly from W without cuts
simpleGenWMuons = isolatedGenMuons.clone(src="genParticles",
                                     target = cms.PSet(pdgId  = cms.vstring("13"),
                                                       status = cms.int32( 3)    ),
                                   ancestor = cms.PSet(pdgId = cms.vstring("24") ) )

simpleGenWElectrons = isolatedGenMuons.clone(src="genParticles",
                                         target = cms.PSet(pdgId  = cms.vstring("11"),
                                                           status = cms.int32( 3)    ),
                                       ancestor = cms.PSet(pdgId = cms.vstring("24") ) )
simpleGenWTaus = isolatedGenMuons.clone(src="genParticles",
                                    target = cms.PSet(pdgId  = cms.vstring("15"),
                                                      status = cms.int32( 3)    ),
                                  ancestor = cms.PSet(pdgId = cms.vstring("24") ) )



## configure jet and Muon selections for cutflow
selectedGenJetCollection = selectedGenJets.clone(src = 'ak5GenJets',
                                                 cut = 'abs(eta) < 2.4 & pt > 30.'
                                                 )

selectedGenMuonCollection = selectedGenParticles.clone(src = 'isolatedGenMuons',
                                                       cut = 'abs(eta) < 2.1 & pt > 20.'
                                                       )


semiLeptGenCollections = cms.Sequence(selectedGenMuonCollection  *
                                      selectedGenJetCollection
                                      )

## set up the muon selection
genMuonSelection  = countPatMuons.clone(src = 'selectedGenMuonCollection',
                                        minNumber = 1,
                                        maxNumber = 1
                                        )

## set up the jet selection 
leadingGenJetSelection = countPatJets.clone(src = 'selectedGenJetCollection',
                                            minNumber = 4
                                            )

## collect different steps within sequences
introduceGenWCollections = cms.Sequence(simpleGenWMuons     *
                                        simpleGenWElectrons *
                                        simpleGenWTaus
                                        )
fullGenSelection = cms.Sequence(isolatedGenMuons*
                                genMuonSelection*
                                leadingGenJetSelection                                
                                )
