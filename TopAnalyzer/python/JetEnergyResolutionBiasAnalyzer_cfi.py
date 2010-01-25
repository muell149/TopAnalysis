import FWCore.ParameterSet.Config as cms

analyzeJetEnergyResolutionBias = cms.EDAnalyzer("JetEnergyResolutionBiasAnalyzer",
  ####################################################################
  ## upper cut performed on the absolute value of eta
  ####################################################################
  etaCut = cms.double(2.4),

  ####################################################################
  ## overall factor applied to the width of the resolution function,
  ## this can be set to 0.0 in order to turn off all resolution effects
  ## or to 1.2 or 0.8 in order to change the resolution by +/- 20%
  ####################################################################
  resFact = cms.double(1.0),

  ####################################################################
  ## parameters of the resolution function:
  ## (sigma/E)^2 = (N/E)^2 + (S/sqrt(pt))^2 + C^2
  ## where S is the stochastic,
  ##       N the noise and
  ##       C the constant term
  ####################################################################
  resParN = cms.double(4.44),
  resParS = cms.double(1.11),
  resParC = cms.double(0.03)
)
