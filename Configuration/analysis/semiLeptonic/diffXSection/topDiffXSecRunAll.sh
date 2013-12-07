#!/bin/sh

## this shell script runs the whole analysis (topDiffXSecAnalysis2012.sh) for all channels, phase spaces and closure tests

## (A) data analysis e/mu channel combination on event yield level
./topDiffXSecAnalysis2012.sh combined2 extrapolate parton
./topDiffXSecAnalysis2012.sh combined2 visible hadron

## (A2) pseudo data analysis closure tests e/mu channel combination on event yield level
#./topDiffXSecAnalysis2012.sh combined2 extrapolate parton NoDistort
#./topDiffXSecAnalysis2012.sh combined2 visible hadron NoDistort
#./topDiffXSecAnalysis2012.sh combined2 extrapolate parton topPtUp
#./topDiffXSecAnalysis2012.sh combined2 visible hadron topPtUp
#./topDiffXSecAnalysis2012.sh combined2 extrapolate parton topPtDown
#./topDiffXSecAnalysis2012.sh combined2 visible hadron topPtDown
#./topDiffXSecAnalysis2012.sh combined2 extrapolate parton ttbarMassUp
#./topDiffXSecAnalysis2012.sh combined2 visible hadron ttbarMassUp
#./topDiffXSecAnalysis2012.sh combined2 extrapolate parton ttbarMassDown
#./topDiffXSecAnalysis2012.sh combined2 visible hadron ttbarMassDown
#./topDiffXSecAnalysis2012.sh combined2 extrapolate parton data
#./topDiffXSecAnalysis2012.sh combined2 visible hadron data
#./topDiffXSecAnalysis2012.sh combined2 extrapolate parton 1000
#./topDiffXSecAnalysis2012.sh combined2 visible hadron 1000

## (B) data analysis separate channels
## Parton level full phase space
#./topDiffXSecAnalysis2012.sh muon extrapolate parton
#./topDiffXSecAnalysis2012.sh electron extrapolate parton
#./topDiffXSecAnalysis2012.sh combined extrapolate parton

## Hadron level visible phase space
#./topDiffXSecAnalysis2012.sh muon visible hadron
#./topDiffXSecAnalysis2012.sh electron visible hadron
#./topDiffXSecAnalysis2012.sh combined visible hadron