from TopAnalysis.Configuration.defines import sizes 
from TopAnalysis.Configuration.defines import source

######################################################################
## PAT Tuples:
## -----------
## /WW/Winter09_IDEAL_V12_FastSim_v1/GEN-SIM-DIGI-RECO
##
## Events      :     16932 (200000 processed)
## xsec(pb)  LO:      44.8
## xsec(pb) NLO:       NAN
## eff         :      1.00
######################################################################
sizes ['wwx0_0'] = 16932
source['wwx0_0'] ='\'/store/user/dammann/ww/patTuple_ww_1.root\','
source['wwx0_0']+='\'/store/user/dammann/ww/patTuple_ww_2.root\','
source['wwx0_0']+='\'/store/user/dammann/ww/patTuple_ww_3.root\','
source['wwx0_0']+='\'/store/user/dammann/ww/patTuple_ww_4.root\''

