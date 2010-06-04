import FWCore.ParameterSet.Config as cms

checkJetOverlapMuons = cms.EDProducer("MuonJetOverlapSelector",
  ## input muon collection
  muons = cms.InputTag("cleanPatMuons"),
  ## jet collection to check overlap
  jets = cms.InputTag("cleanPatJets"),
  ## define overlap region (<deltaR)
  deltaR = cms.double(0.3),
  ## choose whether you want to
  ## include/exclude overlapping
  ## muons in the created collection
  ## include: overlap = true,
  ## exclude: overlap = false
  overlap = cms.bool(False)                                     
)
