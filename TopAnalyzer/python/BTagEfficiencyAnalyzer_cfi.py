import FWCore.ParameterSet.Config as cms

analyzeBTagEfficiency = cms.EDAnalyzer("BTagEfficiencyAnalyzer",
  ## jet collection (after jet selection, before b-tagging)
    jets  = cms.InputTag("tightLeadingPFJets"),
  ## name of b tag algorithm in pat::Jet
    bTagAlgo = cms.string("simpleSecondaryVertexHighEffBJetTags"),
  ## b tag discriminator cut value (here: medium working point)
    bTagDiscrCut = cms.double(1.74),
  ## set to 1 if terminal text output is desired
    #verbose  = cms.int32(  0)
  ## bin edges for variable bins: vector of low-edges for each bin (including overflow), i.e. nBins+1 entries
    binsPt     = cms.vdouble(  0.,10.,20.,30.,40.,50.,60.,80.,140.,250.),
    binsEta    = cms.vdouble(0.,0.45,0.9,1.2,1.65,2.1,2.4,3. )
)