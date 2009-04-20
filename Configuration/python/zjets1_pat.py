from TopAnalysis.Configuration.defines import sizes 
from TopAnalysis.Configuration.defines import source

######################################################################
## PAT Tuples:
## -----------
## /ZJets-madgraph/Fall08_IDEAL_V9_reco-v2/GEN-SIM-RECO
##
## Events      :    190675 (1163479 processed)
## xsec(pb)  LO:      3700
## xsec(pb) NLO:       NAN
## eff         :      1.00
######################################################################
sizes ['zjetsx1_0'] = 109281
source['zjetsx1_0'] ='\'/store/user/rwolf/zjets/patTuple_zjets_v1_1.root\','
source['zjetsx1_0']+='\'/store/user/rwolf/zjets/patTuple_zjets_v1_2.root\','
source['zjetsx1_0']+='\'/store/user/rwolf/zjets/patTuple_zjets_v1_3.root\','
source['zjetsx1_0']+='\'/store/user/rwolf/zjets/patTuple_zjets_v1_4.root\','
source['zjetsx1_0']+='\'/store/user/rwolf/zjets/patTuple_zjets_v1_5.root\''

sizes ['zjetsx1_1'] = 81394
source['zjetsx1_1'] ='\'/store/user/rwolf/zjets/patTuple_zjets_v1_6.root\','
source['zjetsx1_1']+='\'/store/user/rwolf/zjets/patTuple_zjets_v1_7.root\','
source['zjetsx1_1']+='\'/store/user/rwolf/zjets/patTuple_zjets_v1_8.root\''

