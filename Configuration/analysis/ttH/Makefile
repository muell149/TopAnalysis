ROOTLIBS=`root-config --ldflags --libs` -Wl,--no-as-needed -lGenVector
COMPFLAGS=`root-config --cflags` -Wall -Wextra -pedantic -Wno-vla -O2 -g -std=c++0x -DSTANDALONE_COMPILE
#COMPFLAGS=`root-config --cflags` -Wall -Wextra -O2 -g -std=c++0x -DSTANDALONE_COMPILE


all: load_HiggsAnalysis Histo

# HIGGSING
#load_Analysis: dict.o Analysis.o load_Analysis.o PUReweighter.o utils.o HistoListReader.o KinReco.o CommandLineParameters.o
#	g++ -o $@ $^ $(ROOTLIBS)

#load_Analysis.o: ../diLeptonic/load_Analysis.C
#	g++ -c -o load_Analysis.o $(COMPFLAGS) $^

load_HiggsAnalysis: dict.o Analysis.o load_HiggsAnalysis.o PUReweighter.o utils.o HistoListReader.o KinReco.o CommandLineParameters.o JetCategories.o HiggsAnalysis.o
	g++ -o $@ $^ $(ROOTLIBS)

load_HiggsAnalysis.o: load_HiggsAnalysis.C
	g++ -c -o load_HiggsAnalysis.o $(COMPFLAGS) $^
# ENDHIGGSING

dict.o: dict.cpp
	g++ -c -o $@ $(COMPFLAGS) $^

utils.o: ../diLeptonic/utils.cpp ../diLeptonic/utils.h
	g++ -c -o utils.o $(COMPFLAGS) ../diLeptonic/utils.cpp

CommandLineParameters.o: ../diLeptonic/CommandLineParameters.cc ../diLeptonic/CommandLineParameters.hh
	g++ -c -o CommandLineParameters.o $(COMPFLAGS) ../diLeptonic/CommandLineParameters.cc

KinReco.o: ../diLeptonic/KinReco.h ../diLeptonic/KinReco.cpp
	g++ -c -o KinReco.o $(COMPFLAGS) ../diLeptonic/KinReco.cpp

# HIGGSING
#dict.cpp: ../diLeptonic/Analysis.h ../diLeptonic/classes.h ../diLeptonic/HistoListReader.h ../diLeptonic/LinkDef.h
#	rootcint -f dict.cpp -c -p Math/LorentzVector.h $^
dict.cpp: ../diLeptonic/Analysis.h HiggsAnalysis.h ../diLeptonic/classes.h ../diLeptonic/HistoListReader.h ../diLeptonic/LinkDef.h
	rootcint -f dict.cpp -c -p Math/LorentzVector.h $^
# ENDHIGGSING

PUReweighter.o: ../diLeptonic/PUReweighter.h ../diLeptonic/PUReweighter.cpp
	g++ -c -o PUReweighter.o $(COMPFLAGS) ../diLeptonic/PUReweighter.cpp

Analysis.o: ../diLeptonic/Analysis.C ../diLeptonic/Analysis.h ../diLeptonic/HistoListReader.h ../diLeptonic/utils.h ../diLeptonic/KinReco.h
	g++ -c -o Analysis.o $(COMPFLAGS) ../diLeptonic/Analysis.C

# HIGGSING
HiggsAnalysis.o: HiggsAnalysis.C HiggsAnalysis.h ../diLeptonic/HistoListReader.h ../diLeptonic/utils.h ../diLeptonic/KinReco.h ../diLeptonic/Analysis.h
	g++ -c -o HiggsAnalysis.o $(COMPFLAGS) HiggsAnalysis.C

JetCategories.o: JetCategories.C JetCategories.h
	g++ -c -o JetCategories.o $(COMPFLAGS) JetCategories.C
# ENDHIGGSING

HistoListReader.o: ../diLeptonic/HistoListReader.h ../diLeptonic/HistoListReader.cpp
	g++ -c -o HistoListReader.o $(COMPFLAGS) ../diLeptonic/HistoListReader.cpp

Histo.o: ../diLeptonic/Histo.C
	g++ -c -o Histo.o $(COMPFLAGS) ../diLeptonic/Histo.C
	
DilepSVDFunctions.o: ../diLeptonic/DilepSVDFunctions.h ../diLeptonic/DilepSVDFunctions.C 
	g++ -c -o DilepSVDFunctions.o $(COMPFLAGS) ../diLeptonic/DilepSVDFunctions.C 

TopSVDFunctions.o: ../unfolding/TopSVDFunctions.C 
	g++ -c -o TopSVDFunctions.o $(COMPFLAGS) ../unfolding/TopSVDFunctions.C 
	
TopSVDUnfold.o: ../unfolding/TopSVDUnfold.C
	g++ -c -o TopSVDUnfold.o $(COMPFLAGS) ../unfolding/TopSVDUnfold.C

BaseSVDUnfold.o: ../unfolding/BaseSVDUnfold.C
	g++ -c -o BaseSVDUnfold.o $(COMPFLAGS) ../unfolding/BaseSVDUnfold.C

plotterclass.o: ../diLeptonic/plotterclass.cpp ../diLeptonic/plotterclass.h utils.o
	g++ -c -o plotterclass.o $(COMPFLAGS) ../diLeptonic/plotterclass.cpp

Histo: Histo.o plotterclass.o HistoListReader.o utils.o DilepSVDFunctions.o TopSVDFunctions.o TopSVDUnfold.o BaseSVDUnfold.o CommandLineParameters.o
	g++ -o Histo Histo.o plotterclass.o HistoListReader.o utils.o DilepSVDFunctions.o TopSVDFunctions.o TopSVDUnfold.o BaseSVDUnfold.o CommandLineParameters.o $(ROOTLIBS)

TypicalError: GetTypicalErrors.C CommandLineParameters.o
	g++ -o TypicalError GetTypicalErrors.C $(COMPFLAGS) $(ROOTLIBS) CommandLineParameters.o

kinRecoEfficienciesAndSF: ../diLeptonic/kinRecoEfficienciesAndSF.cpp utils.o
	g++ -o kinRecoEfficienciesAndSF ../diLeptonic/kinRecoEfficienciesAndSF.cpp $(COMPFLAGS) $(ROOTLIBS) utils.o

printGenXsec: ../diLeptonic/printGenXsec.C utils.o
	g++ -o printGenXsec ../diLeptonic/printGenXsec.C $(COMPFLAGS) $(ROOTLIBS) utils.o


.PHONY: clean
clean:
	-rm dict.cpp dict.h
	-rm *.o
	-rm load_HiggsAnalysis
	-rm Histo
