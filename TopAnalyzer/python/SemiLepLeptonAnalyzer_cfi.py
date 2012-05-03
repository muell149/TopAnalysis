import FWCore.ParameterSet.Config as cms

#
# module to make kinematic distributions for leotons on gen and rec level
# gen level lepton is taken as leading entry in the genbParticle collection
# rec lepton taken from kinfit result
#

analyzeSemiLepLepton = cms.EDAnalyzer("SemiLepLeptonAnalyzer",
                                      # get kinematic fit output
                                      semiLepEvent = cms.InputTag("ttSemiLepEvent"),
                                      # specify kinematic fit hypothesis
                                      hypoKey = cms.string("kKinFit"),
                                      # choose genParticle collection
                                      # NOTE: the leading entry will be interpreted as gen lepton
                                      genLeptons = cms.InputTag('genParticles'),
                                      # output manager:
                                      # 0: no output, 1: info, >=2: debug
                                      output = cms.int32(0),
                                      # specify event weight
                                      weight = cms.InputTag(""),
                                      # produce gen level plots?
                                      genPlots = cms.bool(False), 
                                      # produce rec level plots?
                                      recPlots = cms.bool(True),
                                      # create tree?
                                      useTree = cms.bool(False)
                                      )
