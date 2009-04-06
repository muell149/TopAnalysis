# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# ZZ sample, sqrt(s) = 10TeV from Winter09 production,
# preselected for ttbar single muon, dimuon and electron muon channel 
# 
# 13319 events 	
# sigma = 7.1 pb
#
# see: https://twiki.cern.ch/twiki/bin/view/CMS/HamburgWikiAnalysisDatasets
#
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
import FWCore.ParameterSet.Config as cms

source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/user/dammann/zz/patTuple_zz_1.root',
        '/store/user/dammann/zz/patTuple_zz_2.root',
        '/store/user/dammann/zz/patTuple_zz_3.root',
        '/store/user/dammann/zz/patTuple_zz_4.root'		
    )
)
