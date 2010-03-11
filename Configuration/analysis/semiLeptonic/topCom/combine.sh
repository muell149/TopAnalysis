#!/bin/sh

# muon multiplicity in different bins of jet multiplicity non-isolated
root -l -b -q 'combine.C++("MuonKinemat2"   , "n",  "2 Jets / non-Isolated", 1)'
root -l -b -q 'combine.C++("MuonKinemat3"   , "n",  "3 Jets / non-Isolated", 1)'
root -l -b -q 'combine.C++("MuonKinemat4"   , "n",  "4 Jets / non-Isolated", 1)'

# muon pt in different bins of jet multiplicity non-isolated
root -l -b -q 'combine.C++("MuonKinemat2"   , "pt", "2 Jets / non-Isolated", 1)'
root -l -b -q 'combine.C++("MuonKinemat3"   , "pt", "3 Jets / non-Isolated", 1)'
root -l -b -q 'combine.C++("MuonKinemat4"   , "pt", "4 Jets / non-Isolated", 1)'

# muon multiplicity in different bins of jet multiplicity isolated
root -l -b -q 'combine.C++("MuonKinemat2Iso", "n",  "2 Jets / Isolated"    , 1)'
root -l -b -q 'combine.C++("MuonKinemat3Iso", "n",  "3 Jets / Isolated"    , 1)'
root -l -b -q 'combine.C++("MuonKinemat4iso", "n",  "4 Jets / Isolated"    , 1)'

# muon pt in different bins of jet multiplicity isolated
root -l -b -q 'combine.C++("MuonKinemat2Iso", "pt", "2 Jets / Isolated"    , 1)'
root -l -b -q 'combine.C++("MuonKinemat3Iso", "pt", "3 Jets / Isolated"    , 1)'
root -l -b -q 'combine.C++("MuonKinemat4Iso", "pt", "4 Jets / Isolated"    , 1)'

# muon track isolation in bins of jet multiplicity
root -l -b -q 'combine.C++("MuonQuality2"   , "trkIso_", "2 Jets", 0)'
root -l -b -q 'combine.C++("MuonQuality3"   , "trkIso_", "3 Jets", 0)'
root -l -b -q 'combine.C++("MuonQuality4"   , "trkIso_", "4 Jets", 0)'

# muon calorimeter isolation in bins of jet multiplicity
root -l -b -q 'combine.C++("MuonQuality2"   , "calIso_", "2 Jets", 0)'
root -l -b -q 'combine.C++("MuonQuality3"   , "calIso_", "3 Jets", 0)'
root -l -b -q 'combine.C++("MuonQuality4"   , "calIso_", "4 Jets", 0)'

# muon relative isolation in bins of jet multiplicity
root -l -b -q 'combine.C++("MuonQuality2"   , "relIso" , "2 Jets", 0)'
root -l -b -q 'combine.C++("MuonQuality3"   , "relIso" , "3 Jets", 0)'
root -l -b -q 'combine.C++("MuonQuality4"   , "relIso" , "4 Jets", 0)'