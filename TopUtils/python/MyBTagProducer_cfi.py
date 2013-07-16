import FWCore.ParameterSet.Config as cms

createMyBTags = cms.EDProducer("MyBTagProducer",
                               ## has to be derived from reco::Jet
                               jetSrc = cms.InputTag("ak5GenJets"),
                               bDiscValue = cms.double(999.9),
                               ## tag the Xth leading jet
                               ## if numbers are given the hadron content of GenJets is ignored
                               jetsToTag = cms.vint32()
                               )
