ROOTLIBS=`root-config --ldflags --libs` -Wl,--no-as-needed -lGenVector
COMPFLAGS=`root-config --cflags` -Wall -Wextra -pedantic -Wno-vla -O2 -g -std=c++0x -DSTANDALONE_COMPILE
#COMPFLAGS=`root-config --cflags` -Wall -Wextra -O2 -g -std=c++0x -DSTANDALONE_COMPILE


all: load_HiggsAnalysis Histo

load_HiggsAnalysis: dict.o Analysis.o load_HiggsAnalysis.o PUReweighter.o utils.o HistoListReader.o KinReco.o CommandLineParameters.o JetCategories.o HiggsAnalysis.o dyScalingHistograms.o JetCorrUncertainty.o  JetCorrParameters.o SimpleJetCorrUncert.o
	g++ -o $@ $^ $(ROOTLIBS)

load_HiggsAnalysis.o: load_HiggsAnalysis.C
	g++ -c -o load_HiggsAnalysis.o $(COMPFLAGS) $^

dict.o: dict.cpp
	g++ -c -o $@ $(COMPFLAGS) $^

dyScalingHistograms.o: dyScalingHistograms.C dyScalingHistograms.h
	g++ -c -o dyScalingHistograms.o $(COMPFLAGS) dyScalingHistograms.C

dyScaleFactors.o: dyScaleFactors.C dyScaleFactors.h
	g++ -c -o dyScaleFactors.o $(COMPFLAGS) dyScaleFactors.C

utils.o: ../diLeptonic/utils.cpp ../diLeptonic/utils.h
	g++ -c -o utils.o $(COMPFLAGS) ../diLeptonic/utils.cpp

higgsUtils.o: higgsUtils.C higgsUtils.h
	g++ -c -o higgsUtils.o $(COMPFLAGS) higgsUtils.C

CommandLineParameters.o: ../diLeptonic/CommandLineParameters.cc ../diLeptonic/CommandLineParameters.hh
	g++ -c -o CommandLineParameters.o $(COMPFLAGS) ../diLeptonic/CommandLineParameters.cc

KinReco.o: ../diLeptonic/KinReco.h ../diLeptonic/KinReco.cpp
	g++ -c -o KinReco.o $(COMPFLAGS) ../diLeptonic/KinReco.cpp

dict.cpp: ../diLeptonic/Analysis.h HiggsAnalysis.h ../diLeptonic/classes.h ../diLeptonic/HistoListReader.h LinkDef.h
	rootcint -f dict.cpp -c -p Math/LorentzVector.h $^

PUReweighter.o: ../diLeptonic/PUReweighter.h ../diLeptonic/PUReweighter.cpp
	g++ -c -o PUReweighter.o $(COMPFLAGS) ../diLeptonic/PUReweighter.cpp

Analysis.o: ../diLeptonic/Analysis.C ../diLeptonic/Analysis.h ../diLeptonic/HistoListReader.h ../diLeptonic/utils.h ../diLeptonic/KinReco.h
	g++ -c -o Analysis.o $(COMPFLAGS) ../diLeptonic/Analysis.C

HiggsAnalysis.o: HiggsAnalysis.C HiggsAnalysis.h ../diLeptonic/HistoListReader.h ../diLeptonic/utils.h ../diLeptonic/KinReco.h ../diLeptonic/Analysis.h dyScalingHistograms.h
	g++ -c -o HiggsAnalysis.o $(COMPFLAGS) HiggsAnalysis.C

JetCategories.o: JetCategories.C JetCategories.h
	g++ -c -o JetCategories.o $(COMPFLAGS) JetCategories.C

HistoListReader.o: ../diLeptonic/HistoListReader.h ../diLeptonic/HistoListReader.cpp
	g++ -c -o HistoListReader.o $(COMPFLAGS) ../diLeptonic/HistoListReader.cpp

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

JetCorrUncertainty.o: ../diLeptonic/JetCorrectionUncertainty.cc JetCorrParameters.o SimpleJetCorrUncert.o
	g++ -c -o $@ $(COMPFLAGS) ../diLeptonic/JetCorrectionUncertainty.cc

JetCorrParameters.o:  ../diLeptonic/JetCorrectorParameters.cc
	g++ -c -o $@ $(COMPFLAGS) ../diLeptonic/JetCorrectorParameters.cc

SimpleJetCorrUncert.o: ../diLeptonic/SimpleJetCorrectionUncertainty.cc
	g++ -c -o $@ $(COMPFLAGS) ../diLeptonic/SimpleJetCorrectionUncertainty.cc

sampleHelpers.o: sampleHelpers.C sampleHelpers.h
	g++ -c -o sampleHelpers.o $(COMPFLAGS) sampleHelpers.C

samples.o: samples.C samples.h sampleHelpers.o
	g++ -c -o samples.o $(COMPFLAGS) samples.C


.PHONY: clean
clean:
	-rm dict.cpp dict.h
	-rm *.o
	-rm load_HiggsAnalysis
	-rm Histo
