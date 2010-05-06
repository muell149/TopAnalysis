## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but for ttbar BG
## ---

## get the mother file
execfile("/afs/naf.desy.de/user/g/goerner/semileptonic356/analyzeMuonDiffXSec_cfg.py")

## change gen level event filter to ttbarBG
process.ttSemiLeptonicFilter.invert = True

## change output name 
process.TFileService.fileName = 'analyzeDiffXSec_testBkg.root'
