#!/bin/sh

##########################
## create output folder ##
##########################
mkdir Analysis/analysisRootFiles

###############
## add files ##
###############

## default
hadd Analysis/analysisRootFiles/muonDiffXSecSigMadD6TFall10PF.root Analysis/ttbarMadD6TSG/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecBkgMadD6TFall10PF.root Analysis/ttbarMadD6TBG/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecSingleTopSchannelMadZ2Fall10PF.root Analysis/singleTopSchannelZ2/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecSingleTopTchannelMadZ2Fall10PF.root Analysis/singleTopTchannelZ2/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecSingleTopTWchannelMadZ2Fall10PF.root Analysis/singleTopTWchannelZ2/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecWjetsMadD6TFall10PF.root Analysis/WLNuD6T/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecZjetsMadD6TFall10PF.root Analysis/DYD6T/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecQCDPythiaZ2Fall10PF.root Analysis/QCDPythiaZ2/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecWWPytia6Z2Fall10PF.root Analysis/WWPythia6Z2/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecWZPytia6Z2Fall10PF.root Analysis/WZPythia6Z2/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecZZPytia6Z2Fall10PF.root Analysis/ZZPythia6Z2/res/*.root

## ISR/FSR
## up
hadd Analysis/analysisRootFiles/muonDiffXSecSigMadD6TFall10ISRFSRupPF.root Analysis/ttbarMadD6TSGIFSRUp/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecBkgMadD6TFall10ISRFSRupPF.root Analysis/ttbarMadD6TBGIFSRUp/res/*.root
## down
hadd Analysis/analysisRootFiles/muonDiffXSecSigMadD6TFall10ISRFSRdownPF.root Analysis/ttbarMadD6TSGIFSRDown/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecBkgMadD6TFall10ISRFSRdownPF.root Analysis/ttbarMadD6TBGIFSRDown/res/*.root

## JES
## up
hadd Analysis/analysisRootFiles/muonDiffXSecSigMadD6TFall10JESupPF.root Analysis/ttbarMadD6TSGJES11/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecBkgMadD6TFall10JESupPF.root Analysis/ttbarMadD6TBGJES11/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecSingleTopSchannelMadZ2Fall10JESupPF.root Analysis/singleTopSchannelZ2JES11/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecSingleTopTchannelMadZ2Fall10JESupPF.root Analysis/singleTopTchannelZ2JES11/res/*.root 
hadd Analysis/analysisRootFiles/muonDiffXSecSingleTopTWchannelMadZ2Fall10JESupPF.root Analysis/singleTopTWchannelZ2JES11/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecZjetsMadD6TFall10JESupPF.root Analysis/DYD6TJES11/res/*.root 
hadd Analysis/analysisRootFiles/muonDiffXSecWjetsMadD6TFall10JESupPF.root Analysis/WLNuD6TJES11/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecQCDPythiaZ2Fall10JESupPF.root Analysis/QCDPythiaZ2JES11/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecWWPytia6Z2Fall10JESupPF.root Analysis/WWPythia6Z2JES11/res/*.root 
hadd Analysis/analysisRootFiles/muonDiffXSecWZPytia6Z2Fall10JESupPF.root Analysis/WZPythia6Z2JES11/res/*.root 
hadd Analysis/analysisRootFiles/muonDiffXSecZZPytia6Z2Fall10JESupPF.root Analysis/ZZPythia6Z2JES11/res/*.root 
### down
hadd Analysis/analysisRootFiles/muonDiffXSecSigMadD6TFall10JESdownPF.root Analysis/ttbarMadD6TSGJES09/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecBkgMadD6TFall10JESdownPF.root Analysis/ttbarMadD6TBGJES09/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecSingleTopSchannelMadZ2Fall10JESdownPF.root Analysis/singleTopSchannelZ2JES09/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecSingleTopTchannelMadZ2Fall10JESdownPF.root Analysis/singleTopTchannelZ2JES09/res/*.root 
hadd Analysis/analysisRootFiles/muonDiffXSecSingleTopTWchannelMadZ2Fall10JESdownPF.root Analysis/singleTopTWchannelZ2JES09/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecWjetsMadD6TFall10JESdownPF.root Analysis/WLNuD6TJES09/res/*.root 
hadd Analysis/analysisRootFiles/muonDiffXSecZjetsMadD6TFall10JESdownPF.root Analysis/DYD6TJES09/res/*.root 
hadd Analysis/analysisRootFiles/muonDiffXSecQCDPythiaZ2Fall10JESdownPF.root Analysis/QCDPythiaZ2JES09/res/*.root 
hadd Analysis/analysisRootFiles/muonDiffXSecWWPytia6Z2Fall10JESdownPF.root Analysis/WWPythia6Z2JES09/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecWZPytia6Z2Fall10JESdownPF.root Analysis/WZPythia6Z2JES09/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecZZPytia6Z2Fall10JESdownPF.root Analysis/ZZPythia6Z2JES09/res/*.root 

## JER
## up
hadd Analysis/analysisRootFiles/muonDiffXSecSigMadD6TFall10JERupPF.root Analysis/ttbarMadD6TSGJERup/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecBkgMadD6TFall10JERupPF.root Analysis/ttbarMadD6TBGJERup/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecSingleTopSchannelMadZ2Fall10JERupPF.root Analysis/singleTopSchannelZ2JERup/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecSingleTopTchannelMadZ2Fall10JERupPF.root Analysis/singleTopTchannelZ2JERup/res/*.root 
hadd Analysis/analysisRootFiles/muonDiffXSecSingleTopTWchannelMadZ2Fall10JERupPF.root Analysis/singleTopTWchannelZ2JERup/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecWjetsMadD6TFall10JERupPF.root Analysis/WLNuD6TJERup/res/*.root 
hadd Analysis/analysisRootFiles/muonDiffXSecZjetsMadD6TFall10JERupPF.root Analysis/DYD6TJERup/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecQCDPythiaZ2Fall10JERupPF.root Analysis/QCDPythiaZ2JERup/res/*.root 
hadd Analysis/analysisRootFiles/muonDiffXSecWWPytia6Z2Fall10JERupPF.root Analysis/WWPythia6Z2JERup/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecWZPytia6Z2Fall10JERupPF.root Analysis/WZPythia6Z2JERup/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecZZPytia6Z2Fall10JERupPF.root Analysis/ZZPythia6Z2JERdown/res/*.root 
## down
hadd Analysis/analysisRootFiles/muonDiffXSecSigMadD6TFall10JERdownPF.root Analysis/ttbarMadD6TSGJERdown/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecBkgMadD6TFall10JERdownPF.root Analysis/ttbarMadD6TBGJERdown/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecSingleTopSchannelMadZ2Fall10JERdownPF.root Analysis/singleTopSchannelZ2JERdown/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecSingleTopTchannelMadZ2Fall10JERdownPF.root Analysis/singleTopTchannelZ2JERdown/res/*.root 
hadd Analysis/analysisRootFiles/muonDiffXSecSingleTopTWchannelMadZ2Fall10JERdownPF.root Analysis/singleTopTWchannelZ2JERdown/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecWjetsMadD6TFall10JERdownPF.root Analysis/WLNuD6TJERdown/res/*.root 
hadd Analysis/analysisRootFiles/muonDiffXSecZjetsMadD6TFall10JERdownPF.root Analysis/DYD6TJERdown/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecQCDPythiaZ2Fall10JERdownPF.root Analysis/QCDPythiaZ2JERdown/res/*.root 
hadd Analysis/analysisRootFiles/muonDiffXSecWWPytia6Z2Fall10JERdownPF.root Analysis/WWPythia6Z2JERdown/res/*.root 
hadd Analysis/analysisRootFiles/muonDiffXSecWZPytia6Z2Fall10JERdownPF.root Analysis/WZPythia6Z2JERdown/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecZZPytia6Z2Fall10JERdownPF.root Analysis/ZZPythia6Z2JERup/res/*.root 

## PU
hadd Analysis/analysisRootFiles/muonDiffXSecSigMadD6TFall10PileUpPF.root Analysis/ttbarMadD6TSGPileUp/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecBkgMadD6TFall10PileUpPF.root Analysis/ttbarMadD6TBGPileUp/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecWjetsMadD6TFall10PileUpPF.root Analysis/WLNuD6TPileUp/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecSingleTopSchannelMadZ2Fall10PileUpPF.root Analysis/singleTopSchannelZ2PileUp/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecSingleTopTchannelMadZ2Fall10PileUpPF.root Analysis/singleTopTchannelZ2PileUp/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecSingleTopTWchannelMadZ2Fall10PileUpPF.root Analysis/singleTopTWchannelZ2PileUp/res/*.root 
hadd Analysis/analysisRootFiles/muonDiffXSecZjetsMadD6TFall10PileUpPF.root Analysis/DYD6TPileUp/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecWWPytia6Z2Fall10PileUpPF.root Analysis/WWPythia6Z2PileUp/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecWZPytia6Z2Fall10PileUpPF.root Analysis/WZPythia6Z2PileUp/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecZZPytia6Z2Fall10PileUpPF.root Analysis/ZZPythia6Z2PileUp/res/*.root

## Scale
## up
hadd Analysis/analysisRootFiles/muonDiffXSecSigMadD6TFall10ScaleUpPF.root Analysis/ttbarMadD6TSGScaleUp/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecBkgMadD6TFall10ScaleUpPF.root Analysis/ttbarMadD6TBGScaleUp/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecWjetsMadD6TFall10ScaleUpPF.root Analysis/WLNuD6TScaleUp/res/*.root 
hadd Analysis/analysisRootFiles/muonDiffXSecZjetsMadD6TFall10ScaleUpPF.root Analysis/DYD6TScaleUp/res/*.root
## down
hadd Analysis/analysisRootFiles/muonDiffXSecSigMadD6TFall10ScaleDownPF.root Analysis/ttbarMadD6TSGScaleDown/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecBkgMadD6TFall10ScaleDownPF.root Analysis/ttbarMadD6TBGScaleDown/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecWjetsMadD6TFall10ScaleDownPF.root Analysis/WLNuD6TScaleDown/res/*.root 
hadd Analysis/analysisRootFiles/muonDiffXSecZjetsMadD6TFall10ScaleDownPF.root Analysis/DYD6TScaleDown/res/*.root 

## Matching
## up
hadd Analysis/analysisRootFiles/muonDiffXSecSigMadD6TFall10MatchUpPF.root Analysis/ttbarMadD6TSGMatchingUp/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecBkgMadD6TFall10MatchUpPF.root Analysis/ttbarMadD6TBGMatchingUp/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecWjetsMadD6TFall10MatchUpPF.root Analysis/WLNuD6TMatchingUp/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecZjetsMadD6TFall10MatchUpPF.root Analysis/DYD6TMatchingUp/res/*.root 
## down
hadd Analysis/analysisRootFiles/muonDiffXSecSigMadD6TFall10MatchDownPF.root Analysis/ttbarMadD6TSGMatchingDown/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecBkgMadD6TFall10MatchDownPF.root Analysis/ttbarMadD6TBGMatchingDown/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecWjetsMadD6TFall10MatchDownPF.root Analysis/WLNuD6TMatchingDown/res/*.root
hadd Analysis/analysisRootFiles/muonDiffXSecZjetsMadD6TFall10MatchDownPF.root Analysis/DYD6TMatchingDown/res/*.root 