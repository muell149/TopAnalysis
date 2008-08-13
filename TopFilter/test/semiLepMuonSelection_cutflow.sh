#!/bin/sh

##################################################
# look for argument on command line
##################################################
status=0
if [ $1 ]
    then
    if [ $1 = "top-sig" -o $1 = "top-bkg" -o $1 = "wjets" -o $1 = "zjets" -o $1 = "qcd" ]
	then
	echo "Option chosen: $1"
	status=1
    fi
fi

if [ $status = 0 ]
    then
    echo "Please choose one of the following options:"
    echo " top-sig top-bkg wjets zjets qcd"
    echo "Use the corresponding name as argument to this script:"
    echo " semiLepMuonSelection_cutflow.sh [option]"
    exit 0
fi

echo "-------------------------------------------------------"

##################################################
# choose steering files to use
##################################################
srcFile="TopAnalysis/Configuration/data/SourceInput.cff"
cfgFile="TopAnalysis/TopFilter/test/semiLepMuonSelection_cutflow.cfg"

if [ ! -e $srcFile ]
    then
    echo "ERROR! The following file is missing:"
    echo "... $srcFile"
    exit 0
fi
if [ ! -e $cfgFile ]
    then
    echo "ERROR! The following file is missing:"
    echo "... $cfgFile"
    exit 0
fi

echo "The following steering files will be used:"
echo "... $srcFile"
echo "... $cfgFile"

##################################################
# construct strings corresponding to chosen sample
##################################################
case $1 in
    top-sig) src="Ttbar"; out="ttbar_sig"; filter=" makeGenEvt, ttSemiLeptonicFilter,";;
    top-bkg) src="Ttbar"; out="ttbar_bkg"; filter=" makeGenEvt, !ttSemiLeptonicFilter,";;
    wjets) src="Wjets"; out="wjets"; filter="";;
    zjets) src="Zjets"; out="zjets"; filter="";;
    qcd) src="QCD"; out="qcd"; filter="";;
esac

sampleFile="TopAnalysis/Configuration/test/csa07AllEventsSkim_$src.cff"
outFile="analyzeSemiLepMuonEvents_cutflow_$out.root"
endPath="  endpath p = {$filter wght, cutflow }"

if [ ! -e $sampleFile ]
    then
    echo "ERROR! The following file is missing:"
    echo "... $sampleFile"
    exit 0
fi

echo "Data samples specified in the following file will be used:"
echo "... $sampleFile"

echo "Output file for TFileService will be:"
echo "... $outFile"

echo "The following endpath will be used in the cfg file:"
echo "... $endPath"

echo "-------------------------------------------------------"

##################################################
# ask for confirmation before starting to work
##################################################
status=0
while [ $status = 0 ]
  do
  echo -n "Start now? [y/n] "
  read answer
  case $answer in
      y|Y) status=1;;
      n|N) exit 0;;
      *) echo "Illegal answer, please try again...";;
  esac
done

echo "-------------------------------------------------------"

##################################################
# make backups of the original cff and cfg files
##################################################
cp $srcFile $srcFile.tmp
cp $cfgFile $cfgFile.tmp

##################################################
# edit cff file: first comment out all samples,
#                then uncomment sample of choice
##################################################
TEXT1="  include"
TEXT2="# include"
sed -i "s%$TEXT1%$TEXT2%" $srcFile
TEXT1="# include \"$sampleFile\""
TEXT2="  include \"$sampleFile\""
sed -i "s%$TEXT1%$TEXT2%" $srcFile

##################################################
# edit cfg file: adapt file name in TFileService,
#                adapt endpath
##################################################
TEXT1="analyzeSemiLepMuonEvents_cutflow_.*.root"
TEXT2=$outFile
sed -i "s%$TEXT1%$TEXT2%" $cfgFile
TEXT1="  endpath.*\}"
TEXT2="$endPath"
sed -i "s%$TEXT1%$TEXT2%" $cfgFile

##################################################
# run the job
##################################################
cmsRun TopAnalysis/TopFilter/test/semiLepMuonSelection_cutflow.cfg

##################################################
# restore the original cff and cfg files
##################################################
if [ -e $srcFile.tmp ]
    then
    mv $srcFile.tmp $srcFile
fi
if [ -e $cfgFile.tmp ]
    then
    mv $cfgFile.tmp $cfgFile
fi
