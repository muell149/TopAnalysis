# directories
#####################

add_custom_command(
    OUTPUT dict.cc
    COMMAND rootcint -f dict.cc -c -p Math/LorentzVector.h AnalysisBase.h TopAnalysis.h classes.h HistoListReader.h LinkDef.h
             && mv dict.cc dict.h ${CMAKE_BINARY_DIR}/src
    DEPENDS AnalysisBase.h TopAnalysis.h classes.h HistoListReader.h LinkDef.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(miscTools
    HistoListReader utils CommandLineParameters
)

add_library(unfolding
    DilepSVDFunctions 
    ../../unfolding/TopSVDFunctions ../../unfolding/TopSVDUnfold ../../unfolding/BaseSVDUnfold
)

add_executable(load_Analysis
    load_Analysis
    dict
    AnalysisBase TopAnalysis
    JetCorrectionUncertainty JetCorrectorParameters SimpleJetCorrectionUncertainty
    PUReweighter
    KinReco
)
TARGET_LINK_LIBRARIES(load_Analysis ${ROOT_LIBRARIES} miscTools) 

add_executable(Histo
    Histo
    plotterclass
)
TARGET_LINK_LIBRARIES(Histo ${ROOT_LIBRARIES} miscTools unfolding) 
    