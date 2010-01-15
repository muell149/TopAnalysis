C = g++
L = g++

ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS   = $(shell root-config --libs)

corrections: analyzeJetEnergyCorrections.o
	$(L) $(ROOTLIBS) -o analyzeCorrections analyzeJetEnergyCorrections.o

analyzeJetEnergyCorrections.o: analyzeJetEnergyCorrections.C
	$(C) $(ROOTCFLAGS) -c analyzeJetEnergyCorrections.C

resolution: analyzeJetEnergyResolutionBias.o
	$(L) $(ROOTLIBS) -o analyzeResolutionBias analyzeJetEnergyResolutionBias.o

analyzeJetEnergyResolutionBias.o: analyzeJetEnergyResolutionBias.C
	$(C) $(ROOTCFLAGS) -c analyzeJetEnergyResolutionBias.C
