from TopAnalysis.Configuration.defines import sizes 
from TopAnalysis.Configuration.defines import source

######################################################################
## PAT Tuples:
## -----------
## /WZ/Winter09_IDEAL_V12_FastSim_v1/GEN-SIM-DIGI-RECO
##
## Events      :     16340 (200000 processed)
## xsec(pb)  LO:      17.4
## xsec(pb) NLO:       NAN
## eff         :      1.00
######################################################################
sizes ['wzx0_0'] = 16340
source['wzx0_0'] ='\'/store/user/dammann/wz/patTuple_PATv2_wz_1.root\','
source['wzx0_0']+='\'/store/user/dammann/wz/patTuple_PATv2_wz_2.root\','
source['wzx0_0']+='\'/store/user/dammann/wz/patTuple_PATv2_wz_3.root\','
source['wzx0_0']+='\'/store/user/dammann/wz/patTuple_PATv2_wz_4.root\''

