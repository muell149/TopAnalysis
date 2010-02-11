execfile("TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy/analyzeJetEnergyCorrections_aod_ak5_ttbarOther_cfg.py")

process.p1.remove(process.patDefaultSequence)

process.source.fileNames = ['/store/user/snaumann/semiLep/ttbar/SemiLepPatTuple_1.root',
                            '/store/user/snaumann/semiLep/ttbar/SemiLepPatTuple_2.root',
                            '/store/user/snaumann/semiLep/ttbar/SemiLepPatTuple_3.root']

## total number of events, 200/pb: 1165
##                         100/pb:  583
##                          50/pb:  291
process.maxEvents.input = -1

process.TFileService.fileName = 'analyzeJetEnergyCorrections_ak5_ttbarOther.root'
