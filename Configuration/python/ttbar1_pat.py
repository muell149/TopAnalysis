from TopAnalysis.Configuration.defines import sizes 
from TopAnalysis.Configuration.defines import source

######################################################################
## PAT Tuples:
## -----------
## /TauolaTTbar/Summer08_IDEAL_V9_v1/GEN-SIM-RECO
##
## Events      :    147000 (147000 processed)
## xsec(pb)  LO:       242
## xsec(pb) NLO:       414
## eff         :       1.0
######################################################################
sizes ['ttbarx1_0'] = 146996
source['ttbarx1_0'] ='\'file:/scratch/current/cms/user/rwolf/samples/ttbar2/patTuple_0_ttbar2.root\','
source['ttbarx1_0']+='\'file:/scratch/current/cms/user/rwolf/samples/ttbar2/patTuple_1_ttbar2.root\','
source['ttbarx1_0']+='\'file:/scratch/current/cms/user/rwolf/samples/ttbar2/patTuple_2_ttbar2.root\','
source['ttbarx1_0']+='\'file:/scratch/current/cms/user/rwolf/samples/ttbar2/patTuple_3_ttbar2.root\','
source['ttbarx1_0']+='\'file:/scratch/current/cms/user/rwolf/samples/ttbar2/patTuple_4_ttbar2.root\''

