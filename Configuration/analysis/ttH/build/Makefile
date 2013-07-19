#ROOTLIBS=`root-config --ldflags --libs` -Wl,--no-as-needed -lGenVector
#ROOTLIBS=`root-config --ldflags --libs` -Wl,--no-as-needed -lGenVector -lTMVA
ROOTLIBS=`root-config --ldflags --libs` -Wl,--no-as-needed -lGenVector -lTMVA -lHistPainter
COMPFLAGS=`root-config --cflags` -Wall -Wextra -pedantic -Wno-vla -O2 -g -std=c++0x -DSTANDALONE_COMPILE
#COMPFLAGS=`root-config --cflags` -Wall -Wextra -O2 -g -std=c++0x -DSTANDALONE_COMPILE


# Directories where to find the source code
TopDir=$(CMSSW_BASE)/src/TopAnalysis/Configuration/analysis/diLeptonic/src
HiggsDir=$(CMSSW_BASE)/src/TopAnalysis/Configuration/analysis/ttH/src



all: load_Analysis Histo mva





utils.o: $(TopDir)/utils.cc $(TopDir)/utils.h
	g++ -c -o utils.o $(COMPFLAGS) $(TopDir)/utils.cc

CommandLineParameters.o: $(TopDir)/CommandLineParameters.cc $(TopDir)/CommandLineParameters.h
	g++ -c -o CommandLineParameters.o $(COMPFLAGS) $(TopDir)/CommandLineParameters.cc

HistoListReader.o: $(TopDir)/HistoListReader.cc $(TopDir)/HistoListReader.h
	g++ -c -o HistoListReader.o $(COMPFLAGS) $(TopDir)/HistoListReader.cc

higgsUtils.o: $(HiggsDir)/higgsUtils.cc $(HiggsDir)/higgsUtils.h
	g++ -c -o higgsUtils.o $(COMPFLAGS) $(HiggsDir)/higgsUtils.cc

sampleHelpers.o: $(TopDir)/sampleHelpers.cc $(TopDir)/sampleHelpers.h
	g++ -c -o sampleHelpers.o $(COMPFLAGS) $(TopDir)/sampleHelpers.cc





load_Analysis: dict.o load_Analysis.o AnalysisBase.o KinematicReconstruction.o KinematicReconstruction_LSroutines.o HiggsAnalysis.o utils.o CommandLineParameters.o HistoListReader.o sampleHelpers.o analysisHelpers.o PUReweighter.o KinReco.o JetCategories.o AnalysisHistograms.o JetCorrectionUncertainty.o JetCorrectorParameters.o SimpleJetCorrectionUncertainty.o MvaInputVariables.o analysisUtils.o ScaleFactors.o DijetAnalyzer.o analysisObjectStructs.o analysisStructs.o Playground.o
	g++ -o $@ $^ $(ROOTLIBS)

load_Analysis.o: $(HiggsDir)/load_Analysis.cc $(HiggsDir)/HiggsAnalysis.h $(TopDir)/utils.h $(TopDir)/sampleHelpers.h $(HiggsDir)/analysisHelpers.h $(HiggsDir)/JetCategories.h $(TopDir)/PUReweighter.h $(TopDir)/CommandLineParameters.h $(TopDir)/ScaleFactors.h $(HiggsDir)/MvaInputVariables.h $(HiggsDir)/DijetAnalyzer.h $(HiggsDir)/AnalysisHistograms.h $(HiggsDir)/Playground.h
	g++ -c -o load_Analysis.o $(COMPFLAGS) $(HiggsDir)/load_Analysis.cc

dict.o: dict.cc
	g++ -c -o $@ $(COMPFLAGS) dict.cc

dict.cc: $(TopDir)/AnalysisBase.h $(HiggsDir)/HiggsAnalysis.h $(HiggsDir)/AnalysisHistograms.h $(TopDir)/classes.h $(TopDir)/classesFwd.h $(TopDir)/HistoListReader.h $(TopDir)/PUReweighter.h $(HiggsDir)/LinkDef.h
	rootcint -f dict.cc -c -p Math/LorentzVector.h Math/PtEtaPhiM4D.h $^

analysisHelpers.o: $(HiggsDir)/analysisHelpers.cc $(HiggsDir)/analysisHelpers.h
	g++ -c -o analysisHelpers.o $(COMPFLAGS) $(HiggsDir)/analysisHelpers.cc

analysisStructs.o: $(HiggsDir)/analysisStructs.cc $(HiggsDir)/analysisStructs.h
	g++ -c -o analysisStructs.o $(COMPFLAGS) $(HiggsDir)/analysisStructs.cc

AnalysisBase.o: $(TopDir)/AnalysisBase.cc $(TopDir)/AnalysisBase.h $(TopDir)/storeTemplate.h $(TopDir)/classesFwd.h
	g++ -c -o AnalysisBase.o $(COMPFLAGS) $(TopDir)/AnalysisBase.cc

HiggsAnalysis.o: $(HiggsDir)/HiggsAnalysis.cc $(HiggsDir)/HiggsAnalysis.h $(TopDir)/classesFwd.h $(TopDir)/AnalysisBase.h $(HiggsDir)/AnalysisHistograms.h $(HiggsDir)/MvaInputVariables.h
	g++ -c -o HiggsAnalysis.o $(COMPFLAGS) $(HiggsDir)/HiggsAnalysis.cc

analysisUtils.o: $(TopDir)/analysisUtils.cc $(TopDir)/analysisUtils.h $(TopDir)/classesFwd.h
	g++ -c -o analysisUtils.o $(COMPFLAGS) $(TopDir)/analysisUtils.cc

analysisObjectStructs.o: $(TopDir)/analysisObjectStructs.cc $(TopDir)/analysisObjectStructs.h $(TopDir)/classesFwd.h
	g++ -c -o analysisObjectStructs.o $(COMPFLAGS) $(TopDir)/analysisObjectStructs.cc

PUReweighter.o: $(TopDir)/PUReweighter.cc $(TopDir)/PUReweighter.h
	g++ -c -o PUReweighter.o $(COMPFLAGS) $(TopDir)/PUReweighter.cc

KinReco.o: $(TopDir)/KinReco.cc $(TopDir)/KinReco.h $(TopDir)/classesFwd.h
	g++ -c -o KinReco.o $(COMPFLAGS) $(TopDir)/KinReco.cc

KinematicReconstruction.o: $(TopDir)/KinematicReconstruction.cc $(TopDir)/KinematicReconstruction.h $(TopDir)/classesFwd.h $(TopDir)/KinematicReconstruction_LSroutines.h
	g++ -c -o KinematicReconstruction.o $(COMPFLAGS) $(TopDir)/KinematicReconstruction.cc

KinematicReconstruction_LSroutines.o: $(TopDir)/KinematicReconstruction_LSroutines.cc $(TopDir)/KinematicReconstruction_LSroutines.h $(TopDir)/classesFwd.h
	g++ -c -o KinematicReconstruction_LSroutines.o $(COMPFLAGS) $(TopDir)/KinematicReconstruction_LSroutines.cc

MvaInputVariables.o: $(HiggsDir)/MvaInputVariables.cc $(HiggsDir)/MvaInputVariables.h $(TopDir)/classesFwd.h $(TopDir)/storeTemplate.h
	g++ -c -o MvaInputVariables.o $(COMPFLAGS) $(HiggsDir)/MvaInputVariables.cc

JetCorrectionUncertainty.o: $(TopDir)/JetCorrectionUncertainty.cc $(TopDir)/JetCorrectionUncertainty.h
	g++ -c -o $@ $(COMPFLAGS) $(TopDir)/JetCorrectionUncertainty.cc

JetCorrectorParameters.o: $(TopDir)/JetCorrectorParameters.cc $(TopDir)/JetCorrectorParameters.h
	g++ -c -o $@ $(COMPFLAGS) $(TopDir)/JetCorrectorParameters.cc

SimpleJetCorrectionUncertainty.o: $(TopDir)/SimpleJetCorrectionUncertainty.cc $(TopDir)/SimpleJetCorrectionUncertainty.h
	g++ -c -o $@ $(COMPFLAGS) $(TopDir)/SimpleJetCorrectionUncertainty.cc

AnalysisHistograms.o: $(HiggsDir)/AnalysisHistograms.cc $(HiggsDir)/AnalysisHistograms.h $(TopDir)/storeTemplate.h $(TopDir)/classesFwd.h
	g++ -c -o AnalysisHistograms.o $(COMPFLAGS) $(HiggsDir)/AnalysisHistograms.cc

JetCategories.o: $(HiggsDir)/JetCategories.cc $(HiggsDir)/JetCategories.h
	g++ -c -o JetCategories.o $(COMPFLAGS) $(HiggsDir)/JetCategories.cc

ScaleFactors.o: $(TopDir)/ScaleFactors.cc $(TopDir)/ScaleFactors.h $(TopDir)/storeTemplate.h $(TopDir)/classesFwd.h
	g++ -c -o ScaleFactors.o $(COMPFLAGS) $(TopDir)/ScaleFactors.cc

Playground.o: $(HiggsDir)/Playground.cc $(HiggsDir)/Playground.h $(HiggsDir)/AnalysisHistograms.h
	g++ -c -o Playground.o $(COMPFLAGS) $(HiggsDir)/Playground.cc

DijetAnalyzer.o: $(HiggsDir)/DijetAnalyzer.cc $(HiggsDir)/DijetAnalyzer.h $(HiggsDir)/JetCategories.h $(TopDir)/classesFwd.h $(TopDir)/storeTemplate.h
	g++ -c -o DijetAnalyzer.o $(COMPFLAGS) $(HiggsDir)/DijetAnalyzer.cc




Histo: Histo.o Plotter.o plotterHelpers.o utils.o plotterUtils.o higgsUtils.o HistoListReader.o CommandLineParameters.o sampleHelpers.o Samples.o EventYields.o DyScaleFactors.o RootFileReader.o
	g++ -o Histo $^ $(ROOTLIBS)

Histo.o: $(HiggsDir)/Histo.cc $(TopDir)/utils.h $(TopDir)/sampleHelpers.h $(HiggsDir)/Samples.h $(HiggsDir)/DyScaleFactors.h $(HiggsDir)/EventYields.h $(HiggsDir)/plotterHelpers.h $(HiggsDir)/Plotter.h $(TopDir)/HistoListReader.h $(TopDir)/CommandLineParameters.h
	g++ -c -o Histo.o $(COMPFLAGS) $(HiggsDir)/Histo.cc

plotterHelpers.o: $(HiggsDir)/plotterHelpers.cc $(HiggsDir)/plotterHelpers.h
	g++ -c -o plotterHelpers.o $(COMPFLAGS) $(HiggsDir)/plotterHelpers.cc

plotterUtils.o: $(TopDir)/plotterUtils.cc $(TopDir)/plotterUtils.h
	g++ -c -o plotterUtils.o $(COMPFLAGS) $(TopDir)/plotterUtils.cc

Samples.o: $(HiggsDir)/Samples.cc $(HiggsDir)/Samples.h $(HiggsDir)/SamplesFwd.h $(TopDir)/sampleHelpers.h
	g++ -c -o Samples.o $(COMPFLAGS) $(HiggsDir)/Samples.cc

DyScaleFactors.o: $(HiggsDir)/DyScaleFactors.cc $(HiggsDir)/DyScaleFactors.h $(TopDir)/sampleHelpers.h
	g++ -c -o DyScaleFactors.o $(COMPFLAGS) $(HiggsDir)/DyScaleFactors.cc

EventYields.o: $(HiggsDir)/EventYields.cc $(HiggsDir)/EventYields.h $(HiggsDir)/DyScaleFactors.h $(TopDir)/sampleHelpers.h
	g++ -c -o EventYields.o $(COMPFLAGS) $(HiggsDir)/EventYields.cc

Plotter.o: $(HiggsDir)/Plotter.cc $(HiggsDir)/Plotter.h $(HiggsDir)/plotterHelpers.h $(TopDir)/sampleHelpers.h $(HiggsDir)/SamplesFwd.h
	g++ -c -o Plotter.o $(COMPFLAGS) $(HiggsDir)/Plotter.cc

RootFileReader.o: $(TopDir)/RootFileReader.cc $(TopDir)/RootFileReader.h
	g++ -c -o RootFileReader.o $(COMPFLAGS) $(TopDir)/RootFileReader.cc





mva: mva.o sampleHelpers.o MvaInputVariables.o CommandLineParameters.o utils.o
	g++ -o mva $^ $(ROOTLIBS)

mva.o: $(HiggsDir)/train_bdt_topSystemJetAssignment.cc $(TopDir)/sampleHelpers.h $(HiggsDir)/MvaInputVariables.h $(TopDir)/CommandLineParameters.h $(TopDir)/utils.h
	g++ -c -o mva.o $(COMPFLAGS) $(HiggsDir)/train_bdt_topSystemJetAssignment.cc





.PHONY: clean
clean:
	-rm *.o
	-rm dict.cc dict.h
	-rm load_Analysis
	-rm Histo
	-rm mva


