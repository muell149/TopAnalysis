import FWCore.ParameterSet.Config as cms

selectEvents = cms.EDAnalyzer("RunEventFilter",
    
    #select a range of runs you want to select
    runs = cms.string('122314'),
    
    #select runs or ranges of runs which you want to exclude
    #excludedRuns = cms.string(''),
    
    
    #use this if you want to select or reject events in certain runs
    # if you want to exclude events instead of selecting them
    # start the selected_evts string with a '!'    
    selectedEvents = cms.VPSet(        
      cms.PSet(
        run_number  = cms.uint32(122314),
	selected_evts = cms.string('13688798,13693046-13702674')
      )                    
    )
)




