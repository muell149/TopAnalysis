# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# WW sample, sqrt(s) = 10TeV from Winter09 production,
# preselected for ttbar single muon, dimuon and electron muon channel 
# 
# 16932 events 	
# sigma = 44.8 pb
#
# see: https://twiki.cern.ch/twiki/bin/view/CMS/HamburgWikiAnalysisDatasets
#
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
import FWCore.ParameterSet.Config as cms

source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/user/dammann/ww/patTuple_ww_1.root',
        '/store/user/dammann/ww/patTuple_ww_2.root',
        '/store/user/dammann/ww/patTuple_ww_3.root',
        '/store/user/dammann/ww/patTuple_ww_4.root'			
    )
)
