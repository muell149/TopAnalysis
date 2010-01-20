import FWCore.ParameterSet.Config as cms

## high level trigger filter
from HLTrigger.HLTfilters.hltHighLevel_cfi import *

## ---
##    setup trigger filter path
## ---
## single-muon trigger, threshold pt > 9 GeV, no isolation requirements
hltMu9 = hltHighLevel.clone(HLTPaths = ["HLT_Mu9"])
## 4 jet trigger, threshold pt > 30 GeV
hltQuadJet30 = hltHighLevel.clone(HLTPaths = ["HLT_QuadJet30"])
## sum of pts of jets HT > 200 GeV
hltHt200 = hltHighLevel.clone(HLTPaths = ["HLT_HT200"])
