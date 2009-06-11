import FWCore.ParameterSet.Config as cms

from TopAnalysis.TopAnalyzer.MuonAnalyzer_cfi import analyzeMuon
## -------------------------------------- Muon eta | Muon pt | Jet eta | Jet pt | Muon iso | Z-Veto | MET | #Jets  
fullLepMuon00 = analyzeMuon.clone()    ##     -    |    -    |    -    |   -    |    -     |   -    |  -  |   -
fullLepMuon10 = analyzeMuon.clone()    ##     x    |    -    |    -    |   -    |    -     |   -    |  -  |   -     
fullLepMuon20 = analyzeMuon.clone()    ##     x    |    -    |    -    |   -    |    -     |   -    |  -  |   -    
fullLepMuon30 = analyzeMuon.clone()    ##     x    |    x    |    -    |   -    |    -     |   -    |  -  |   -     
fullLepMuon40 = analyzeMuon.clone()    ##     x    |    x    |    -    |   -    |    -     |   -    |  -  |   -      
fullLepMuon01 = analyzeMuon.clone()    ##     -    |    -    |    x    |   -    |    -     |   -    |  -  |   -      
fullLepMuon02 = analyzeMuon.clone()    ##     -    |    -    |    x    |   -    |    -     |   -    |  -  |   -       
fullLepMuon03 = analyzeMuon.clone()    ##     -    |    -    |    x    |   x    |    -     |   -    |  -  |   -      
fullLepMuon04 = analyzeMuon.clone()    ##     -    |    -    |    x    |   x    |    -     |   -    |  -  |   -      
fullLepMuon44 = analyzeMuon.clone()    ##     -    |    -    |    -    |   -    |    -     |   -    |  -  |   -     
fullLepMuon54 = analyzeMuon.clone()    ##     -    |    -    |    -    |   -    |    x     |   -    |  -  |   -     
fullLepMuon64 = analyzeMuon.clone()    ##     -    |    -    |    -    |   -    |    x     |   -    |  -  |   -      
          
fullLepMuon74 = analyzeMuon.clone()    ##     -    |    -    |    -    |   -    |    -     |   x    |  -  |   -     
fullLepMuon75 = analyzeMuon.clone()    ##     -    |    -    |    -    |   -    |    -     |   x    |  x  |   -     
fullLepMuon76 = analyzeMuon.clone()    ##     -    |    -    |    -    |   -    |    -     |   x    |  x  |   x    


from TopAnalysis.TopAnalyzer.JetAnalyzer_cfi  import analyzeJets
## -------------------------------------- Muon eta | Muon pt | Jet eta | Jet pt | Muon iso | Z-Veto | MET | #Jets  
fullLepJets00 = analyzeJets.clone()    ##     -    |    -    |    -    |   -    |    -     |   -    |  -  |   -
fullLepJets10 = analyzeJets.clone()    ##     x    |    -    |    -    |   -    |    -     |   -    |  -  |   -     
fullLepJets20 = analyzeJets.clone()    ##     x    |    -    |    -    |   -    |    -     |   -    |  -  |   -    
fullLepJets30 = analyzeJets.clone()    ##     x    |    x    |    -    |   -    |    -     |   -    |  -  |   -     
fullLepJets40 = analyzeJets.clone()    ##     x    |    x    |    -    |   -    |    -     |   -    |  -  |   -      
fullLepJets01 = analyzeJets.clone()    ##     -    |    -    |    x    |   -    |    -     |   -    |  -  |   -      
fullLepJets02 = analyzeJets.clone()    ##     -    |    -    |    x    |   -    |    -     |   -    |  -  |   -       
fullLepJets03 = analyzeJets.clone()    ##     -    |    -    |    x    |   x    |    -     |   -    |  -  |   -      
fullLepJets04 = analyzeJets.clone()    ##     -    |    -    |    x    |   x    |    -     |   -    |  -  |   -      
fullLepJets44 = analyzeJets.clone()    ##     -    |    -    |    -    |   -    |    -     |   -    |  -  |   -     
fullLepJets54 = analyzeJets.clone()    ##     -    |    -    |    -    |   -    |    x     |   -    |  -  |   -     
fullLepJets64 = analyzeJets.clone()    ##     -    |    -    |    -    |   -    |    x     |   -    |  -  |   -      
          
fullLepJets74 = analyzeJets.clone()    ##     -    |    -    |    -    |   -    |    -     |   x    |  -  |   -     
fullLepJets75 = analyzeJets.clone()    ##     -    |    -    |    -    |   -    |    -     |   x    |  x  |   -     
fullLepJets76 = analyzeJets.clone()    ##     -    |    -    |    -    |   -    |    -     |   x    |  x  |   x 

## import and clone Filter
from TopAnalysis.TopFilter.filters.etaEventFilters_cff       import *
from TopAnalysis.TopFilter.filters.ptEventFilters_cff        import *
from TopAnalysis.TopFilter.filters.IsolationEventFilter_cfi  import *

filterFullLep10 = filterMuonEta.clone()
filterFullLep20 = filterMuonEta.clone()
filterFullLep30 = filterMuonPt.clone()
filterFullLep40 = filterMuonPt.clone()
filterFullLep01 = filterJetsEta.clone()
filterFullLep02 = filterJetsEta.clone()
filterFullLep03 = filterJetsPt.clone()
filterFullLep04 = filterJetsPt.clone()
filterFullLep50 = filterMuonIso.clone()
filterFullLep60 = filterMuonIso.clone()

from TopAnalysis.TopFilter.filters.BSMFilter_cfi            import *

filterFullLep70 = filterDiMuonMass.clone()
filterFullLep05 = filterMET.clone()
filterFullLep06 = filterJetsnr.clone()


## import selection cuts here
from TopAnalysis.TopFilter.selections.fullLepMuonSelection_BSM_cff import *

filterFullLep10.cuts = firstLepMuonEta
filterFullLep20.cuts = fullLepMuonEta
filterFullLep30.cuts = firstLepMuonPt
filterFullLep40.cuts = fullLepMuonPt
filterFullLep01.cuts = firstLepJetsEta
filterFullLep02.cuts = fullLepJetsEta
filterFullLep03.cuts = firstLepJetsPt
filterFullLep04.cuts = fullLepJetsPt
filterFullLep50.cuts = firstLepCombIsolation
filterFullLep60.cuts = fullLepCombIsolation

filterFullLep05.cuts = fullLepMET
filterFullLep06.cuts = fullLepJetsnr

## define sequences
selectFullMuonMuonKinematics = cms.Sequence(fullLepMuon00 + fullLepJets00 *
                                            filterFullLep10 *
                                            fullLepMuon10 + fullLepJets10 *
                                            filterFullLep20 *
                                            fullLepMuon20 + fullLepJets20 *
                                            filterFullLep30 *
                                            fullLepMuon30 + fullLepJets30 *
                                            filterFullLep40 *
                                            fullLepMuon40 + fullLepJets40
                                           )

selectFullMuonJetsKinematics = cms.Sequence(fullLepMuon00 + fullLepJets00 *
                                            filterFullLep01 *
                                            fullLepMuon01 + fullLepJets01 *
                                            filterFullLep02 *
                                            fullLepMuon02 + fullLepJets02 *
                                            filterFullLep03 *
                                            fullLepMuon03 + fullLepJets03 *
                                            filterFullLep04 *
                                            fullLepMuon04 + fullLepJets04
                                           )

selectFullMuonMuonIsolation  = cms.Sequence(fullLepMuon44 + fullLepJets44 * 
                                            filterFullLep50 *
                                            fullLepMuon54 + fullLepJets54 *
                                            filterFullLep60 *
                                            fullLepMuon64 + fullLepJets64
                                            )

selectFullMuonBSM  = cms.Sequence          (fullLepMuon64 + fullLepJets64 *
                                            filterFullLep70 *
                                            fullLepMuon75 + fullLepJets75 *
                                            filterFullLep05 *
                                            fullLepMuon75 + fullLepJets75 *
                                            filterFullLep06 *
                                            fullLepMuon76 + fullLepJets76
                                            )
