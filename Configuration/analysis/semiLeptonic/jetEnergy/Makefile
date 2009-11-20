C = g++
L = g++

ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS   = $(shell root-config --libs)

analyze: analyzeJetEnergyCorrections.o
	$(L) $(ROOTLIBS) -o analyze analyzeJetEnergyCorrections.o

analyzeJetEnergyCorrections.o: analyzeJetEnergyCorrections.C
	$(C) $(ROOTCFLAGS) -c analyzeJetEnergyCorrections.C
