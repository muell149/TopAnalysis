#!/bin/sh

## this shell script runs the whole analysis (topDiffXSecAnalysis2012.sh) for all channels, phase spaces and levels

# combined channel analysis on event yield level
./topDiffXSecAnalysis2012.sh combined2 extrapolate parton
./topDiffXSecAnalysis2012.sh combined2 visible hadron
./topDiffXSecAnalysis2012.sh combined2 visible parton

## single channels

## Parton level full phase space
./topDiffXSecAnalysis2012.sh muon extrapolate parton
./topDiffXSecAnalysis2012.sh electron extrapolate parton
#./topDiffXSecAnalysis2012.sh combined extrapolate parton

## Hadron level visible phase space
./topDiffXSecAnalysis2012.sh muon visible hadron
./topDiffXSecAnalysis2012.sh electron visible hadron
#./topDiffXSecAnalysis2012.sh combined visible hadron

## Parton level visible phase space
./topDiffXSecAnalysis2012.sh muon visible parton
./topDiffXSecAnalysis2012.sh electron visible parton
#./topDiffXSecAnalysis2012.sh combined visible parton



