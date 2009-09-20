import FWCore.ParameterSet.Config as cms

## high level trigger filter
from HLTrigger.HLTfilters.hltHighLevel_cfi import *

## ---
##    setup trigger filter path
## ---
## single-muon trigger, threshold pt > 9 GeV, no isolation requirements
hltMu9 = hltHighLevel.clone(HLTPaths = ["HLT_Mu9"])
