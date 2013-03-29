ROOTLIBS=`root-config --ldflags --libs` -Wl,--no-as-needed -lGenVector
COMPFLAGS=`root-config --cflags` -Wall -Wextra -pedantic -Wno-vla -O2 -g -std=c++0x -DSTANDALONE_COMPILE
#COMPFLAGS=`root-config --cflags` -Wall -Wextra -O2 -g -std=c++0x -DSTANDALONE_COMPILE




all: load_HiggsAnalysis Histo





utils.o: ../../diLeptonic/src/utils.cc ../../diLeptonic/src/utils.h ../../diLeptonic/src/classes.h
	g++ -c -o utils.o $(COMPFLAGS) ../../diLeptonic/src/utils.cc

higgsUtils.o: higgsUtils.cc higgsUtils.h
	g++ -c -o higgsUtils.o $(COMPFLAGS) higgsUtils.cc

CommandLineParameters.o: ../../diLeptonic/src/CommandLineParameters.cc ../../diLeptonic/src/CommandLineParameters.h
	g++ -c -o CommandLineParameters.o $(COMPFLAGS) ../../diLeptonic/src/CommandLineParameters.cc

HistoListReader.o: ../../diLeptonic/src/HistoListReader.cc ../../diLeptonic/src/HistoListReader.h
	g++ -c -o HistoListReader.o $(COMPFLAGS) ../../diLeptonic/src/HistoListReader.cc

sampleHelpers.o: sampleHelpers.cc sampleHelpers.h
	g++ -c -o sampleHelpers.o $(COMPFLAGS) sampleHelpers.cc





load_HiggsAnalysis: dict.o load_HiggsAnalysis.o AnalysisBase.o HiggsAnalysis.o utils.o higgsUtils.o CommandLineParameters.o HistoListReader.o sampleHelpers.o analysisHelpers.o PUReweighter.o KinReco.o JetCategories.o DyScalingHistograms.o JetCorrectionUncertainty.o JetCorrectorParameters.o SimpleJetCorrectionUncertainty.o MvaInputVariables.o
	g++ -o $@ $^ $(ROOTLIBS)

load_HiggsAnalysis.o: load_HiggsAnalysis.cc HiggsAnalysis.h higgsUtils.h sampleHelpers.h analysisHelpers.h ../../diLeptonic/src/utils.h ../../diLeptonic/src/PUReweighter.h ../../diLeptonic/src/CommandLineParameters.h
	g++ -c -o load_HiggsAnalysis.o $(COMPFLAGS) load_HiggsAnalysis.cc

dict.o: dict.cc
	g++ -c -o $@ $(COMPFLAGS) $^

dict.cc: ../../diLeptonic/src/AnalysisBase.h HiggsAnalysis.h ../../diLeptonic/src/classes.h ../../diLeptonic/src/HistoListReader.h ../../diLeptonic/src/PUReweighter.h LinkDef.h
	rootcint -f dict.cc -c -p Math/LorentzVector.h Math/PtEtaPhiM4D.h $^

analysisHelpers.o: analysisHelpers.cc analysisHelpers.h
	g++ -c -o analysisHelpers.o $(COMPFLAGS) analysisHelpers.cc

AnalysisBase.o: ../../diLeptonic/src/AnalysisBase.cc ../../diLeptonic/src/AnalysisBase.h ../../diLeptonic/src/classes.h
	g++ -c -o AnalysisBase.o $(COMPFLAGS) ../../diLeptonic/src/AnalysisBase.cc

HiggsAnalysis.o: HiggsAnalysis.cc HiggsAnalysis.h higgsUtils.h ../../diLeptonic/src/AnalysisBase.h DyScalingHistograms.h JetCategories.h MvaInputVariables.h
	g++ -c -o HiggsAnalysis.o $(COMPFLAGS) HiggsAnalysis.cc

PUReweighter.o: ../../diLeptonic/src/PUReweighter.cc ../../diLeptonic/src/PUReweighter.h
	g++ -c -o PUReweighter.o $(COMPFLAGS) ../../diLeptonic/src/PUReweighter.cc

KinReco.o: ../../diLeptonic/src/KinReco.cc ../../diLeptonic/src/KinReco.h ../../diLeptonic/src/classes.h
	g++ -c -o KinReco.o $(COMPFLAGS) ../../diLeptonic/src/KinReco.cc

MvaInputVariables.o: MvaInputVariables.cc MvaInputVariables.h ../../diLeptonic/src/classes.h
	g++ -c -o MvaInputVariables.o $(COMPFLAGS) MvaInputVariables.cc

JetCorrectionUncertainty.o: ../../diLeptonic/src/JetCorrectionUncertainty.cc ../../diLeptonic/src/JetCorrectionUncertainty.h
	g++ -c -o $@ $(COMPFLAGS) ../../diLeptonic/src/JetCorrectionUncertainty.cc

JetCorrectorParameters.o: ../../diLeptonic/src/JetCorrectorParameters.cc ../../diLeptonic/src/JetCorrectorParameters.h
	g++ -c -o $@ $(COMPFLAGS) ../../diLeptonic/src/JetCorrectorParameters.cc

SimpleJetCorrectionUncertainty.o: ../../diLeptonic/src/SimpleJetCorrectionUncertainty.cc ../../diLeptonic/src/SimpleJetCorrectionUncertainty.h
	g++ -c -o $@ $(COMPFLAGS) ../../diLeptonic/src/SimpleJetCorrectionUncertainty.cc

DyScalingHistograms.o: DyScalingHistograms.cc DyScalingHistograms.h
	g++ -c -o DyScalingHistograms.o $(COMPFLAGS) DyScalingHistograms.cc

JetCategories.o: JetCategories.cc JetCategories.h
	g++ -c -o JetCategories.o $(COMPFLAGS) JetCategories.cc





Histo: Histo.o Plotter.o plotterHelpers.o utils.o higgsUtils.o HistoListReader.o CommandLineParameters.o sampleHelpers.o Samples.o EventYields.o DyScaleFactors.o
	g++ -o Histo $^ $(ROOTLIBS)

Histo.o: Histo.cc sampleHelpers.h Samples.h DyScaleFactors.h EventYields.h plotterHelpers.h Plotter.h higgsUtils.h ../../diLeptonic/src/HistoListReader.h ../../diLeptonic/src/CommandLineParameters.h
	g++ -c -o Histo.o $(COMPFLAGS) Histo.cc

plotterHelpers.o: plotterHelpers.cc plotterHelpers.h
	g++ -c -o plotterHelpers.o $(COMPFLAGS) plotterHelpers.cc

Samples.o: Samples.cc Samples.h sampleHelpers.h
	g++ -c -o Samples.o $(COMPFLAGS) Samples.cc

DyScaleFactors.o: DyScaleFactors.cc DyScaleFactors.h sampleHelpers.h
	g++ -c -o DyScaleFactors.o $(COMPFLAGS) DyScaleFactors.cc

EventYields.o: EventYields.cc EventYields.h DyScaleFactors.h sampleHelpers.h
	g++ -c -o EventYields.o $(COMPFLAGS) EventYields.cc

Plotter.o: Plotter.cc Plotter.h plotterHelpers.h DyScaleFactors.h sampleHelpers.h Samples.h
	g++ -c -o Plotter.o $(COMPFLAGS) Plotter.cc





.PHONY: clean
clean:
	-rm dict.cc dict.h
	-rm *.o
	-rm load_HiggsAnalysis
	-rm Histo
