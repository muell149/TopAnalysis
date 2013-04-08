#ROOTLIBS=`root-config --ldflags --libs` -Wl,--no-as-needed -lGenVector
#ROOTLIBS=`root-config --ldflags --libs` -Wl,--no-as-needed -lGenVector -lTMVA
ROOTLIBS=`root-config --ldflags --libs` -Wl,--no-as-needed -lGenVector -lTMVA -lHistPainter
COMPFLAGS=`root-config --cflags` -Wall -Wextra -pedantic -Wno-vla -O2 -g -std=c++0x -DSTANDALONE_COMPILE
#COMPFLAGS=`root-config --cflags` -Wall -Wextra -O2 -g -std=c++0x -DSTANDALONE_COMPILE


# Directories where to find the source code
TopDir=$(CMSSW_BASE)/src/TopAnalysis/Configuration/analysis/diLeptonic/src
HiggsDir=$(CMSSW_BASE)/src/TopAnalysis/Configuration/analysis/ttH/src



all: load_HiggsAnalysis Histo mva





utils.o: $(TopDir)/utils.cc $(TopDir)/utils.h $(TopDir)/classes.h
	g++ -c -o utils.o $(COMPFLAGS) $(TopDir)/utils.cc

CommandLineParameters.o: $(TopDir)/CommandLineParameters.cc $(TopDir)/CommandLineParameters.h
	g++ -c -o CommandLineParameters.o $(COMPFLAGS) $(TopDir)/CommandLineParameters.cc

HistoListReader.o: $(TopDir)/HistoListReader.cc $(TopDir)/HistoListReader.h
	g++ -c -o HistoListReader.o $(COMPFLAGS) $(TopDir)/HistoListReader.cc

higgsUtils.o: $(HiggsDir)/higgsUtils.cc $(HiggsDir)/higgsUtils.h
	g++ -c -o higgsUtils.o $(COMPFLAGS) $(HiggsDir)/higgsUtils.cc

sampleHelpers.o: $(HiggsDir)/sampleHelpers.cc $(HiggsDir)/sampleHelpers.h
	g++ -c -o sampleHelpers.o $(COMPFLAGS) $(HiggsDir)/sampleHelpers.cc





load_HiggsAnalysis: dict.o load_HiggsAnalysis.o AnalysisBase.o HiggsAnalysis.o utils.o higgsUtils.o CommandLineParameters.o HistoListReader.o sampleHelpers.o analysisHelpers.o PUReweighter.o KinReco.o JetCategories.o AnalysisHistograms.o JetCorrectionUncertainty.o JetCorrectorParameters.o SimpleJetCorrectionUncertainty.o MvaInputVariables.o
	g++ -o $@ $^ $(ROOTLIBS)

load_HiggsAnalysis.o: $(HiggsDir)/load_HiggsAnalysis.cc $(HiggsDir)/HiggsAnalysis.h $(HiggsDir)/higgsUtils.h $(HiggsDir)/sampleHelpers.h $(HiggsDir)/analysisHelpers.h $(TopDir)/utils.h $(TopDir)/PUReweighter.h $(TopDir)/CommandLineParameters.h
	g++ -c -o load_HiggsAnalysis.o $(COMPFLAGS) $(HiggsDir)/load_HiggsAnalysis.cc

dict.o: dict.cc
	g++ -c -o $@ $(COMPFLAGS) dict.cc

dict.cc: $(TopDir)/AnalysisBase.h $(HiggsDir)/HiggsAnalysis.h $(TopDir)/classes.h $(TopDir)/HistoListReader.h $(TopDir)/PUReweighter.h $(HiggsDir)/LinkDef.h
	rootcint -f dict.cc -c -p Math/LorentzVector.h Math/PtEtaPhiM4D.h $^

analysisHelpers.o: $(HiggsDir)/analysisHelpers.cc $(HiggsDir)/analysisHelpers.h
	g++ -c -o analysisHelpers.o $(COMPFLAGS) $(HiggsDir)/analysisHelpers.cc

AnalysisBase.o: $(TopDir)/AnalysisBase.cc $(TopDir)/AnalysisBase.h $(TopDir)/classes.h
	g++ -c -o AnalysisBase.o $(COMPFLAGS) $(TopDir)/AnalysisBase.cc

HiggsAnalysis.o: $(HiggsDir)/HiggsAnalysis.cc $(HiggsDir)/HiggsAnalysis.h $(HiggsDir)/higgsUtils.h $(TopDir)/AnalysisBase.h $(HiggsDir)/AnalysisHistograms.h $(HiggsDir)/JetCategories.h $(HiggsDir)/MvaInputVariables.h
	g++ -c -o HiggsAnalysis.o $(COMPFLAGS) $(HiggsDir)/HiggsAnalysis.cc

PUReweighter.o: $(TopDir)/PUReweighter.cc $(TopDir)/PUReweighter.h
	g++ -c -o PUReweighter.o $(COMPFLAGS) $(TopDir)/PUReweighter.cc

KinReco.o: $(TopDir)/KinReco.cc $(TopDir)/KinReco.h $(TopDir)/classes.h
	g++ -c -o KinReco.o $(COMPFLAGS) $(TopDir)/KinReco.cc

MvaInputVariables.o: $(HiggsDir)/MvaInputVariables.cc $(HiggsDir)/MvaInputVariables.h $(TopDir)/classes.h $(HiggsDir)/higgsUtils.h
	g++ -c -o MvaInputVariables.o $(COMPFLAGS) $(HiggsDir)/MvaInputVariables.cc

JetCorrectionUncertainty.o: $(TopDir)/JetCorrectionUncertainty.cc $(TopDir)/JetCorrectionUncertainty.h
	g++ -c -o $@ $(COMPFLAGS) $(TopDir)/JetCorrectionUncertainty.cc

JetCorrectorParameters.o: $(TopDir)/JetCorrectorParameters.cc $(TopDir)/JetCorrectorParameters.h
	g++ -c -o $@ $(COMPFLAGS) $(TopDir)/JetCorrectorParameters.cc

SimpleJetCorrectionUncertainty.o: $(TopDir)/SimpleJetCorrectionUncertainty.cc $(TopDir)/SimpleJetCorrectionUncertainty.h
	g++ -c -o $@ $(COMPFLAGS) $(TopDir)/SimpleJetCorrectionUncertainty.cc

AnalysisHistograms.o: $(HiggsDir)/AnalysisHistograms.cc $(HiggsDir)/AnalysisHistograms.h $(HiggsDir)/higgsUtils.h
	g++ -c -o AnalysisHistograms.o $(COMPFLAGS) $(HiggsDir)/AnalysisHistograms.cc

JetCategories.o: $(HiggsDir)/JetCategories.cc $(HiggsDir)/JetCategories.h
	g++ -c -o JetCategories.o $(COMPFLAGS) $(HiggsDir)/JetCategories.cc





Histo: Histo.o Plotter.o plotterHelpers.o utils.o higgsUtils.o HistoListReader.o CommandLineParameters.o sampleHelpers.o Samples.o EventYields.o DyScaleFactors.o
	g++ -o Histo $^ $(ROOTLIBS)

Histo.o: $(HiggsDir)/Histo.cc $(HiggsDir)/sampleHelpers.h $(HiggsDir)/Samples.h $(HiggsDir)/DyScaleFactors.h $(HiggsDir)/EventYields.h $(HiggsDir)/plotterHelpers.h $(HiggsDir)/Plotter.h $(HiggsDir)/higgsUtils.h $(TopDir)/HistoListReader.h $(TopDir)/CommandLineParameters.h
	g++ -c -o Histo.o $(COMPFLAGS) $(HiggsDir)/Histo.cc

plotterHelpers.o: $(HiggsDir)/plotterHelpers.cc $(HiggsDir)/plotterHelpers.h
	g++ -c -o plotterHelpers.o $(COMPFLAGS) $(HiggsDir)/plotterHelpers.cc

Samples.o: $(HiggsDir)/Samples.cc $(HiggsDir)/Samples.h $(HiggsDir)/sampleHelpers.h
	g++ -c -o Samples.o $(COMPFLAGS) $(HiggsDir)/Samples.cc

DyScaleFactors.o: $(HiggsDir)/DyScaleFactors.cc $(HiggsDir)/DyScaleFactors.h $(HiggsDir)/sampleHelpers.h
	g++ -c -o DyScaleFactors.o $(COMPFLAGS) $(HiggsDir)/DyScaleFactors.cc

EventYields.o: $(HiggsDir)/EventYields.cc $(HiggsDir)/EventYields.h $(HiggsDir)/DyScaleFactors.h $(HiggsDir)/sampleHelpers.h
	g++ -c -o EventYields.o $(COMPFLAGS) $(HiggsDir)/EventYields.cc

Plotter.o: $(HiggsDir)/Plotter.cc $(HiggsDir)/Plotter.h $(HiggsDir)/plotterHelpers.h $(HiggsDir)/DyScaleFactors.h $(HiggsDir)/sampleHelpers.h $(HiggsDir)/Samples.h
	g++ -c -o Plotter.o $(COMPFLAGS) $(HiggsDir)/Plotter.cc





mva: mva.o sampleHelpers.o
	g++ -o mva $^ $(ROOTLIBS)

mva.o: $(HiggsDir)/train_bdt_topSystemJetAssignment.cc $(HiggsDir)/sampleHelpers.h
	g++ -c -o mva.o $(COMPFLAGS) $(HiggsDir)/train_bdt_topSystemJetAssignment.cc





.PHONY: clean
clean:
	-rm *.o
	-rm dict.cc dict.h
	-rm load_HiggsAnalysis
	-rm Histo
	-rm mva


