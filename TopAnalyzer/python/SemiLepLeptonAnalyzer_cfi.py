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
                                      # choose reco lepton collection
                                      # NOTE: the leading entry will be interpreted as reco lepton
                                      recLeptons = cms.InputTag('selectedPatMuons'),
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
                                      # within visible cross section range?
                                      ingenPS = cms.InputTag("visiblePhaseSpace", "inVisiblePS"),
                                      # produce rec level plots?
                                      recPlots = cms.bool(True),
                                      # use lepton kinematics as before the kinematic fit?
                                      useRecLepKinematicsBeforeFit= cms.bool(False),
                                      # create tree?
                                      useTree = cms.bool(False)
                                      )
