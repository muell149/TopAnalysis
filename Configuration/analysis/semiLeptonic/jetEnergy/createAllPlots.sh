#!/bin/sh

codeDir=TopAnalysis/Configuration/analysis/semiLeptonic/jetEnergy
targetDir=~/latex/tdr2/notes/AN-10-094/trunk

compare=$codeDir/compareSamples
anaRes=$codeDir/analyzeResolutionBias
anaCor=$codeDir/analyzeCorrections

echo -n "Convert eps files to pdf ? [y/n] "
read doPdf

echo -n "Copy results to $targetDir ? [y/n] "
read cpDir

##################################################
## JER bias plots
##################################################

echo "VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV"
echo -n "Produce JER bias plots? [y/n] "
read answer
if [[ $answer == "y" ]]
    then

    cd $codeDir
    make resolution
    if [ "$?" -ne "0" ]; then
	exit $?
    fi
    cd -

    $anaRes "analyzeJetEnergyResolutionBias.root" "analyzeJetEnergyResolutionBias_mcatnlo.root"

    if [[ $doPdf == "y" ]]
	then
	nFiles=`ls -l analyzeJetEnergyResolutionBias/*.eps | wc -l`
	echo -n "Converting analyzeJetEnergyResolutionBias/*.eps ($nFiles files) to pdf... "
	for file in `ls analyzeJetEnergyResolutionBias/*.eps`
	  do
	  epstopdf $file
	  rm -f $file
	  echo -n "."
	done
	echo " Done."
    fi

    if [[ $cpDir == "y" ]]
	then
	cp -r analyzeJetEnergyResolutionBias $targetDir
    fi

fi

##################################################
## sample comparison plots
##################################################

echo "VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV"
echo -n "Produce sample comparison plots? [y/n] "
read answer
if [[ $answer == "y" ]]
    then

    cd $codeDir
    make comparison
    if [ "$?" -ne "0" ]; then
	exit $?
    fi
    cd -

    $compare "analyzeJetEnergyCorrections_ak5.root" "analyzeJetEnergyCorrections_ak5_mcatnlo.root"

    if [[ $doPdf == "y" ]]
	then
	nFiles=`ls -l compareJetEnergyCorrectionSamples/*.eps | wc -l`
	echo -n "Converting compareJetEnergyCorrectionSamples/*.eps ($nFiles files) to pdf... "
	for file in `ls compareJetEnergyCorrectionSamples/*.eps`
	  do
	  epstopdf $file
	  rm -f $file
	  echo -n "."
	done
	echo " Done."
    fi

    if [[ $cpDir == "y" ]]
	then
	cp -r compareJetEnergyCorrectionSamples $targetDir
    fi

fi

##################################################
## JEC validation plots
##################################################

echo "VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV"
echo -n "Produce JEC validation plots? [y/n] "
read answer
if [[ $answer == "y" ]]
    then

    cd $codeDir
    make corrections
    if [ "$?" -ne "0" ]; then
	exit $?
    fi
    cd -

    $anaCor "analyzeJetEnergyCorrections_ak5.root"         "GenMatch"
    $anaCor "analyzeJetEnergyCorrections_ak5_mcatnlo.root" "GenMatch"
    $anaCor "analyzeJetEnergyCorrections_ic5.root"         "GenMatch"
    $anaCor "analyzeJetEnergyCorrections_kt4.root"         "GenMatch"

    if [[ $doPdf == "y" ]]
	then
	nFiles=`ls -l analyzeJetEnergyCorrections_*/*.eps | wc -l`
	echo -n "Converting analyzeJetEnergyCorrections_*/*.eps ($nFiles files) to pdf... "
	for file in `ls analyzeJetEnergyCorrections_*/*.eps`
	  do
	  epstopdf $file
	  rm -f $file
	  echo -n "."
	done
	echo " Done."
    fi

    if [[ $cpDir == "y" ]]
	then
	cp -r analyzeJetEnergyCorrections_ak5/         $targetDir
	cp -r analyzeJetEnergyCorrections_ak5_mcatnlo/ $targetDir
	cp -r analyzeJetEnergyCorrections_ic5/         $targetDir
	cp -r analyzeJetEnergyCorrections_kt4/         $targetDir
    fi

fi

