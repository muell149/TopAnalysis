import FWCore.ParameterSet.Config as cms

from TopAnalysis.TopAnalyzer.ElecAnalyzer_cfi import analyzeElec
## ------------------------------------------ Elec eta  |  Elec pt  | Muon eta  |  Muon pt  | Jets eta  |  Jets pt
fullLepElMuElec000pre = analyzeElec.clone()    ##     -     |     -     |     -     |     -     |     -     |     -
fullLepElMuElec100pre = analyzeElec.clone()    ##     x     |     -     |     -     |     -     |     -     |     -
fullLepElMuElec200pre = analyzeElec.clone()    ##     x     |     x     |     -     |     -     |     -     |     -
fullLepElMuElec210pre = analyzeElec.clone()    ##     x     |     x     |     x     |     -     |     -     |     -
fullLepElMuElec220pre = analyzeElec.clone()    ##     x     |     x     |     x     |     x     |     -     |     -
fullLepElMuElec221pre = analyzeElec.clone()    ##     x     |     x     |     x     |     x     |     x     |     -
fullLepElMuElec222pre = analyzeElec.clone()    ##     x     |     x     |     x     |     x     |     x     |     x

## put any extra configuration here:
fullLepElMuElec000pre.input = cms.InputTag("selectedLayer1Electrons")                         
fullLepElMuElec100pre.input = cms.InputTag("selectedLayer1Electrons")                          
fullLepElMuElec200pre.input = cms.InputTag("selectedLayer1Electrons")                           
fullLepElMuElec210pre.input = cms.InputTag("selectedLayer1Electrons")                         
fullLepElMuElec220pre.input = cms.InputTag("selectedLayer1Electrons")
fullLepElMuElec221pre.input = cms.InputTag("selectedLayer1Electrons")
fullLepElMuElec222pre.input = cms.InputTag("selectedLayer1Electrons")

fullLepElMuElec000pre.useEventWeight = cms.bool(False)
fullLepElMuElec100pre.useEventWeight = cms.bool(False)
fullLepElMuElec200pre.useEventWeight = cms.bool(False)
fullLepElMuElec210pre.useEventWeight = cms.bool(False)
fullLepElMuElec220pre.useEventWeight = cms.bool(False)
fullLepElMuElec221pre.useEventWeight = cms.bool(False)
fullLepElMuElec222pre.useEventWeight = cms.bool(False)

fullLepElMuElec000pre.doId = cms.bool(False)
fullLepElMuElec100pre.doId = cms.bool(False)
fullLepElMuElec200pre.doId = cms.bool(False)
fullLepElMuElec210pre.doId = cms.bool(False)
fullLepElMuElec220pre.doId = cms.bool(False)
fullLepElMuElec221pre.doId = cms.bool(False)
fullLepElMuElec222pre.doId = cms.bool(False)


from TopAnalysis.TopAnalyzer.MuonAnalyzer_cfi import analyzeMuon
## ------------------------------------------ Elec eta  |  Elec pt  | Muon eta  |  Muon pt  | Jets eta  |  Jets pt
fullLepElMuMuon000pre = analyzeMuon.clone()    ##     -     |     -     |     -     |     -     |     -     |     -
fullLepElMuMuon100pre = analyzeMuon.clone()    ##     x     |     -     |     -     |     -     |     -     |     -
fullLepElMuMuon200pre = analyzeMuon.clone()    ##     x     |     x     |     -     |     -     |     -     |     -
fullLepElMuMuon210pre = analyzeMuon.clone()    ##     x     |     x     |     x     |     -     |     -     |     -
fullLepElMuMuon220pre = analyzeMuon.clone()    ##     x     |     x     |     x     |     x     |     -     |     -
fullLepElMuMuon221pre = analyzeMuon.clone()    ##     x     |     x     |     x     |     x     |     x     |     -
fullLepElMuMuon222pre = analyzeMuon.clone()    ##     x     |     x     |     x     |     x     |     x     |     x

## put any extra configuration here:
fullLepElMuMuon000pre.input = cms.InputTag("selectedLayer1Muons")             
fullLepElMuMuon100pre.input = cms.InputTag("selectedLayer1Muons")                       
fullLepElMuMuon200pre.input = cms.InputTag("selectedLayer1Muons")                       
fullLepElMuMuon210pre.input = cms.InputTag("selectedLayer1Muons")                      
fullLepElMuMuon220pre.input = cms.InputTag("selectedLayer1Muons")
fullLepElMuMuon221pre.input = cms.InputTag("selectedLayer1Muons")
fullLepElMuMuon222pre.input = cms.InputTag("selectedLayer1Muons")

fullLepElMuMuon000pre.useEventWeight = cms.bool(False)
fullLepElMuMuon100pre.useEventWeight = cms.bool(False)
fullLepElMuMuon200pre.useEventWeight = cms.bool(False)
fullLepElMuMuon210pre.useEventWeight = cms.bool(False)
fullLepElMuMuon220pre.useEventWeight = cms.bool(False)
fullLepElMuMuon221pre.useEventWeight = cms.bool(False)
fullLepElMuMuon222pre.useEventWeight = cms.bool(False)
 

from TopAnalysis.TopAnalyzer.JetAnalyzer_cfi  import analyzeJets
## ------------------------------------------ Elec eta  |  Elec pt  | Muon eta  |  Muon pt  | Jets eta  |  Jets pt
fullLepElMuJets000pre = analyzeJets.clone()    ##     -     |     -     |     -     |     -     |     -     |     -
fullLepElMuJets100pre = analyzeJets.clone()    ##     x     |     -     |     -     |     -     |     -     |     -
fullLepElMuJets200pre = analyzeJets.clone()    ##     x     |     x     |     -     |     -     |     -     |     -
fullLepElMuJets210pre = analyzeJets.clone()    ##     x     |     x     |     x     |     -     |     -     |     -
fullLepElMuJets220pre = analyzeJets.clone()    ##     x     |     x     |     x     |     x     |     -     |     -
fullLepElMuJets221pre = analyzeJets.clone()    ##     x     |     x     |     x     |     x     |     x     |     -
fullLepElMuJets222pre = analyzeJets.clone()    ##     x     |     x     |     x     |     x     |     x     |     x

## put any extra configuration here:
fullLepElMuJets000pre.input = cms.InputTag("selectedLayer1Jets")    
fullLepElMuJets100pre.input = cms.InputTag("selectedLayer1Jets")                          
fullLepElMuJets200pre.input = cms.InputTag("selectedLayer1Jets")    
fullLepElMuJets210pre.input = cms.InputTag("selectedLayer1Jets")    
fullLepElMuJets220pre.input = cms.InputTag("selectedLayer1Jets")
fullLepElMuJets221pre.input = cms.InputTag("selectedLayer1Jets")
fullLepElMuJets222pre.input = cms.InputTag("selectedLayer1Jets")

fullLepElMuJets000pre.useEventWeight = False
fullLepElMuJets100pre.useEventWeight = False                   
fullLepElMuJets200pre.useEventWeight = False
fullLepElMuJets210pre.useEventWeight = False
fullLepElMuJets220pre.useEventWeight = False
fullLepElMuJets221pre.useEventWeight = False
fullLepElMuJets222pre.useEventWeight = False


## import selection cuts here
from TopAnalysis.TopFilter.selections.fullLepElMuSelection_step0_cff import *

from TopAnalysis.TopFilter.filters.EtaEventFilter_cfi import filterElecEta
prefilterFullLepElMu100 = filterElecEta.clone()
from TopAnalysis.TopFilter.filters.EtaEventFilter_cfi import filterMuonEta
prefilterFullLepElMu010 = filterMuonEta.clone()
from TopAnalysis.TopFilter.filters.EtaEventFilter_cfi import filterJetsEta
prefilterFullLepElMu001 = filterJetsEta.clone()
from TopAnalysis.TopFilter.filters.PtEventFilter_cfi  import filterElecPt
prefilterFullLepElMu200 = filterElecPt.clone()
from TopAnalysis.TopFilter.filters.PtEventFilter_cfi  import filterMuonPt
prefilterFullLepElMu020 = filterMuonPt.clone()
from TopAnalysis.TopFilter.filters.PtEventFilter_cfi  import filterJetsPt
prefilterFullLepElMu002 = filterJetsPt.clone()

## put any extra configuration here:
prefilterFullLepElMu100.cuts = fullLepElecEta
prefilterFullLepElMu010.cuts = fullLepMuonEta
prefilterFullLepElMu001.cuts = fullLepJetsEta
prefilterFullLepElMu200.cuts = fullLepElecPt
prefilterFullLepElMu020.cuts = fullLepMuonPt
prefilterFullLepElMu002.cuts = fullLepJetsPt

prefilterFullLepElMu100.useEventWeight = False
prefilterFullLepElMu010.useEventWeight = False
prefilterFullLepElMu001.useEventWeight = False
prefilterFullLepElMu200.useEventWeight = False
prefilterFullLepElMu020.useEventWeight = False
prefilterFullLepElMu002.useEventWeight = False


## define sequences
preselectFullLepElMu = cms.Sequence(fullLepElMuElec000pre + fullLepElMuMuon000pre + fullLepElMuJets000pre *
                                    prefilterFullLepElMu100 *
                                    fullLepElMuElec100pre + fullLepElMuMuon100pre + fullLepElMuJets100pre *
                                    prefilterFullLepElMu200 *
                                    fullLepElMuElec200pre + fullLepElMuMuon200pre + fullLepElMuJets200pre *
                                    prefilterFullLepElMu010 *
                                    fullLepElMuElec210pre + fullLepElMuMuon210pre + fullLepElMuJets210pre *
                                    prefilterFullLepElMu020 *
                                    fullLepElMuElec220pre + fullLepElMuMuon220pre + fullLepElMuJets220pre #*
                                    #prefilterFullLepElMu001 *
                                    #fullLepElMuElec221pre + fullLepElMuMuon221pre + fullLepElMuJets221pre *
                                    #prefilterFullLepElMu002 *				    
                                    #fullLepElMuElec222pre + fullLepElMuMuon222pre + fullLepElMuJets222pre				    
                                   )


