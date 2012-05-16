#!/bin/sh

docDir=/afs/desy.de/group/uh2/www/wwwiexp.desy.de/groups/cms/topphysics/TopAnalysis

export CVSROOT=:pserver:anonymous@cmscvs.cern.ch:/local/reps/CMSSW
export VO_CMS_SW_DIR=/afs/naf.desy.de/group/cms/sw/
export SCRAM_ARCH=slc5_amd64_gcc434
source $VO_CMS_SW_DIR/cmsset_default.sh

############################################################
# setup fresh CMSSW release area and add some packages on top
############################################################

cmsrel CMSSW_4_2_8_patch7
cd CMSSW_4_2_8_patch7/src
cmsenv

echo "+++ Retrieving code from the CVS repository..."

cvs -Q checkout -r V06-04-19 DataFormats/PatCandidates
cvs -Q checkout -r V00-03-07 PhysicsTools/KinFitter
cvs -Q checkout -r V08-03-17 PhysicsTools/Utilities
cvs -Q checkout -r V06-07-13 TopQuarkAnalysis/TopEventSelection
cvs -Q checkout -r V06-07-18 TopQuarkAnalysis/TopKinFitter
cvs -Q checkout -r V06-07-09 TopQuarkAnalysis/TopObjectResolutions

############################################################
# update our UserCode with the CVS head and compile
############################################################

cvs -Q checkout -d TopAnalysis -r HEAD UserCode/Bromo/TopAnalysis

showtags
showtags -r -t > $docDir/showtags.txt

echo "+++ Compiling..."

scram b > scram.txt 2> scram.txt
if [ -e $docDir/scram.txt ]
    then
    rm -f $docDir/scram.txt
fi
cp scram.txt $docDir/scram.txt

############################################################
# check for compiler warnings and errors
############################################################

if [ `grep -ic error scram.txt` -eq 0 ]
    then
    if [ `grep -ic warning scram.txt` -eq 0 ]
	then
	echo "+++ No errors or warnings from SCRAM."
	cp $docDir/passed.jpg $docDir/scram.jpg
    else
	echo "+++ Got warnings from SCRAM!"
	cp $docDir/warnings.jpg $docDir/scram.jpg
    fi
else
    cp $docDir/errors.jpg $docDir/scram.jpg
    echo "+++ Got errors from SCRAM!"
fi

############################################################
# run the libchecker
############################################################

echo "+++ Checking libraries with the libchecker..."

if [ -e $docDir/libchecker.txt ]
    then
    rm -f $docDir/libchecker.txt
fi
for file in `ls $CMSSW_BASE/lib/$SCRAM_ARCH/*TopAnalysis*.so`
  do
  echo $file >> $docDir/libchecker.txt
  libchecker.pl $file >> $docDir/libchecker.txt 2> /dev/null
done

############################################################
# generate code documentation using doxygen
############################################################

echo "+++ Running doxygen to update documentation..."

rm -f $docDir/*.html
rm -f $docDir/*.png
rm -f $docDir/doxyWarn.log

cd TopAnalysis

doxygen Configuration/doc/Doxyfile > /dev/null

cd $docDir

# if log file from doxygen exists but does not have a size large than zero
if [ -e doxyWarn.log -a ! -s doxyWarn.log ]
    then
    echo "No warnings from doxygen." > doxyWarn.log
    cp passed.jpg doxyWarn.jpg
else
    cp warnings.jpg doxyWarn.jpg
    echo "+++ Got warnings from doxygen!"
fi

echo "+++ Done."