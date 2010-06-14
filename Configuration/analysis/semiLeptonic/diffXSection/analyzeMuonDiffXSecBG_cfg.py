## ---
##    this configfile does the same like analyzeMuonDiffXSec_cfg.py
##    but for ttbar BG
## ---

## get the mother file
execfile("/afs/naf.desy.de/user/g/goerner/semileptonic361/analyzeMuonDiffXSec_cfg.py")

## change gen level event filter to ttbarBG
process.ttSemiLeptonicFilter.invert = True
process.ttSemiLeptonicFilterb.invert = True

print "ttbar decay subset filter is inverted semileptonic muon decay" 

## change output name 
process.TFileService.fileName = 'analyzeDiffXSec_testBkg.root'
