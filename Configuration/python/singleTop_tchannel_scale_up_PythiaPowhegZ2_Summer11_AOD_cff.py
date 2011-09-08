import FWCore.ParameterSet.Config as cms

################################################################################################
# Dataset:
# Events :
# eff    : 1.0                                                                                 #
################################################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [


     ] );

secFiles.extend( [
               ] )

