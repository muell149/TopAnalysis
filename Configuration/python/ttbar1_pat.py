from TopAnalysis.Configuration.defines import sizes 
from TopAnalysis.Configuration.defines import source

######################################################################
## PAT Tuples:
## -----------
## /TauolaTTbar/Summer08_IDEAL_V9_v1/GEN-SIM-RECO
##
## Events      :    146996 (146996 processed)
## xsec(pb)  LO:       242
## xsec(pb) NLO:       414
## eff         :       1.0
######################################################################
sizes ['ttbarx1_0'] = 106540
source['ttbarx1_0'] ='\'/store/user/rwolf/ttbar/patTuple_PATv2_ttbar_tauola_1.root\','
source['ttbarx1_0']+='\'/store/user/rwolf/ttbar/patTuple_PATv2_ttbar_tauola_2.root\','
source['ttbarx1_0']+='\'/store/user/rwolf/ttbar/patTuple_PATv2_ttbar_tauola_3.root\''

