#!/bin/sh

## this shell script runs the whole analysis (topDiffXSecAnalysis2011.sh) for all channels, phase spaces and levels

## Hadron level visible phase space
./topDiffXSecAnalysis2011.sh muon visible hadron
./topDiffXSecAnalysis2011.sh electron visible hadron
./topDiffXSecAnalysis2011.sh combined visible hadron

## Parton level visible phase space
./topDiffXSecAnalysis2011.sh muon visible parton
./topDiffXSecAnalysis2011.sh electron visible parton
./topDiffXSecAnalysis2011.sh combined visible parton

## Parton level full phase space
./topDiffXSecAnalysis2011.sh muon extrapolate parton
./topDiffXSecAnalysis2011.sh electron extrapolate parton
./topDiffXSecAnalysis2011.sh combined extrapolate parton

# combined event yield analysis
#./topDiffXSecAnalysis2011.sh combined2 visible hadron
#./topDiffXSecAnalysis2011.sh combined2 visible parton
#./topDiffXSecAnalysis2011.sh combined2 extrapolate parton