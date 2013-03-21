ROOTLIBS=`root-config --ldflags --libs` -Wl,--no-as-needed -lGenVector
COMPFLAGS=`root-config --cflags` -Wall -Wextra -pedantic -Wno-vla -O2 -g -std=c++0x -DSTANDALONE_COMPILE
#COMPFLAGS=`root-config --cflags` -Wall -Wextra -O2 -g -std=c++0x -DSTANDALONE_COMPILE


all: load_HiggsAnalysis Histo

load_HiggsAnalysis: dict.o AnalysisBase.o load_HiggsAnalysis.o PUReweighter.o utils.o HistoListReader.o KinReco.o CommandLineParameters.o JetCategories.o HiggsAnalysis.o DyScalingHistograms.o JetCorrectionUncertainty.o  JetCorrectorParameters.o SimpleJetCorrectionUncertainty.o
	g++ -o $@ $^ $(ROOTLIBS)

load_HiggsAnalysis.o: load_HiggsAnalysis.cc
	g++ -c -o load_HiggsAnalysis.o $(COMPFLAGS) $^

dict.o: dict.cc
	g++ -c -o $@ $(COMPFLAGS) $^

DyScalingHistograms.o: DyScalingHistograms.cc DyScalingHistograms.h
	g++ -c -o DyScalingHistograms.o $(COMPFLAGS) DyScalingHistograms.cc

dyScaleFactors.o: dyScaleFactors.C dyScaleFactors.h
	g++ -c -o dyScaleFactors.o $(COMPFLAGS) dyScaleFactors.C

utils.o: ../../diLeptonic/src/utils.cc ../../diLeptonic/src/utils.h
	g++ -c -o utils.o $(COMPFLAGS) ../../diLeptonic/src/utils.cc

higgsUtils.o: higgsUtils.C higgsUtils.h
	g++ -c -o higgsUtils.o $(COMPFLAGS) higgsUtils.C

CommandLineParameters.o: ../../diLeptonic/src/CommandLineParameters.cc ../../diLeptonic/src/CommandLineParameters.h
	g++ -c -o CommandLineParameters.o $(COMPFLAGS) ../../diLeptonic/src/CommandLineParameters.cc

KinReco.o: ../../diLeptonic/src/KinReco.h ../../diLeptonic/src/KinReco.cc
	g++ -c -o KinReco.o $(COMPFLAGS) ../../diLeptonic/src/KinReco.cc

dict.cc: ../../diLeptonic/src/AnalysisBase.h HiggsAnalysis.h ../../diLeptonic/src/classes.h ../../diLeptonic/src/HistoListReader.h LinkDef.h
	rootcint -f dict.cc -c -p Math/LorentzVector.h $^

PUReweighter.o: ../../diLeptonic/src/PUReweighter.h ../../diLeptonic/src/PUReweighter.cc
	g++ -c -o PUReweighter.o $(COMPFLAGS) ../../diLeptonic/src/PUReweighter.cc

AnalysisBase.o: ../../diLeptonic/src/AnalysisBase.cc ../../diLeptonic/src/AnalysisBase.h ../../diLeptonic/src/HistoListReader.h ../../diLeptonic/src/utils.h ../../diLeptonic/src/KinReco.h
	g++ -c -o AnalysisBase.o $(COMPFLAGS) ../../diLeptonic/src/AnalysisBase.cc

HiggsAnalysis.o: HiggsAnalysis.cc HiggsAnalysis.h ../../diLeptonic/src/HistoListReader.h ../../diLeptonic/src/utils.h ../../diLeptonic/src/KinReco.h ../../diLeptonic/src/AnalysisBase.h DyScalingHistograms.h
	g++ -c -o HiggsAnalysis.o $(COMPFLAGS) HiggsAnalysis.cc

JetCategories.o: JetCategories.cc JetCategories.h
	g++ -c -o JetCategories.o $(COMPFLAGS) JetCategories.cc

HistoListReader.o: ../../diLeptonic/src/HistoListReader.h ../../diLeptonic/src/HistoListReader.cc
	g++ -c -o HistoListReader.o $(COMPFLAGS) ../../diLeptonic/src/HistoListReader.cc

Histo.o: Histo.C
	g++ -c -o Histo.o $(COMPFLAGS) Histo.C
	
plotterHelpers.o: plotterHelpers.C plotterHelpers.h
	g++ -c -o plotterHelpers.o $(COMPFLAGS) plotterHelpers.C

plotterclass.o: plotterclass.cpp plotterclass.h utils.o higgsUtils.o plotterHelpers.o
	g++ -c -o plotterclass.o $(COMPFLAGS) plotterclass.cpp

Histo: Histo.o plotterclass.o plotterHelpers.o HistoListReader.o utils.o higgsUtils.o CommandLineParameters.o sampleHelpers.o samples.o eventYields.o dyScaleFactors.o
	g++ -o Histo Histo.o plotterclass.o plotterHelpers.o HistoListReader.o utils.o higgsUtils.o CommandLineParameters.o sampleHelpers.o samples.o eventYields.o dyScaleFactors.o $(ROOTLIBS)

eventYields.o: eventYields.C eventYields.h utils.o
	g++ -c -o eventYields.o $(COMPFLAGS) eventYields.C

JetCorrectionUncertainty.o: ../../diLeptonic/src/JetCorrectionUncertainty.cc JetCorrectorParameters.o SimpleJetCorrectionUncertainty.o
	g++ -c -o $@ $(COMPFLAGS) ../../diLeptonic/src/JetCorrectionUncertainty.cc

JetCorrectorParameters.o:  ../../diLeptonic/src/JetCorrectorParameters.cc
	g++ -c -o $@ $(COMPFLAGS) ../../diLeptonic/src/JetCorrectorParameters.cc

SimpleJetCorrectionUncertainty.o: ../../diLeptonic/src/SimpleJetCorrectionUncertainty.cc
	g++ -c -o $@ $(COMPFLAGS) ../../diLeptonic/src/SimpleJetCorrectionUncertainty.cc

sampleHelpers.o: sampleHelpers.C sampleHelpers.h
	g++ -c -o sampleHelpers.o $(COMPFLAGS) sampleHelpers.C

samples.o: samples.C samples.h sampleHelpers.o
	g++ -c -o samples.o $(COMPFLAGS) samples.C


.PHONY: clean
clean:
	-rm dict.cc dict.h
	-rm *.o
	-rm load_HiggsAnalysis
	-rm Histo
