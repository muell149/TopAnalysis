#!/bin/sh

#####################################################################################
##  If while compiling you get a virtual memory error please execute the next steps:
##
##    cd ${CMSSW_BASE}/src
##    ulimit -v 10000000
##    ulimit -m 10000000
##    scram b distclean
##    scram b -j8
##
#####################################################################################


###### TOP 2013  ########
CMS_version=CMSSW_5_3_11
export SCRAM_ARCH=slc5_amd64_gcc462



minimalInstall="False"
if [ $# -ge 1 ] ; then
    if [ $# -ge 2 ] || [ $1 != "min" ] ; then
        echo "Usage for full installation: $0"
        echo "Usage for minimal installation (analysis on nTuple level): $0 min"
        exit 1
    else
        minimalInstall="True"
    fi
fi

scram p -s CMSSW ${CMS_version}
cd ${CMS_version}/src

echo export SCRAM_ARCH=${SCRAM_ARCH} > SCRAM_ARCH
chmod u+x SCRAM_ARCH

eval `scramv1 runtime -sh`


###### Hamburg TOP package (plus dependencies) #####
#cvs co -d TopAnalysis UserCode/Bromo/TopAnalysis
if [ -z "${TOP_TAG}" ]; then
    echo "Installing the HEAD version of the TopAnalysis code from GIT."
    echo "  To use specific tag, 'export TOP_TAG=<TAG_NAME>' before running the install script"
    echo "  or execute 'git checkout <TAG_NAME>' in the TopAnalysis directory after the script execution."
    echo "  To see available tags, execute: 'git tag'"
    git clone https://git.cern.ch/reps/TopAnalysis
    echo
else
    echo "Installing the TopAnalysis code from GIT with tag: ${TOP_TAG}"
    git clone https://git.cern.ch/reps/TopAnalysis
    cd ./TopAnalysis
    git checkout ${TOP_TAG}
    cd -
    echo
fi


if [[ "$minimalInstall" == True ]] ; then
    echo
    echo "Minimal installation successfully done"
    exit 0
fi



###### PAT #####
### From: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePATReleaseNotes52X#V08_09_59_CMSSW_5_3_11   (revision 148)

addpkg DataFormats/PatCandidates V06-05-06-12
addpkg PhysicsTools/PatAlgos

###### Jet Energy Corrections #####

###### Electron ID #####

#electron mva id stuff (following top reference twiki, and TQAF TWiki page rev.223)
cvs co -r V00-00-30-01 -d EGamma/EGammaAnalysisTools UserCode/EGamma/EGammaAnalysisTools
cd $CMSSW_BASE/src/EGamma/EGammaAnalysisTools/data
cat download.url | xargs wget
cd -

###### ParticleFlow #####

cvs co -r V15-02-06       RecoParticleFlow/PFProducer


###### TQAF #####

### From: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideTQAFRecipes#CMSSW_5_3_X  (revision 224)
addpkg AnalysisDataFormats/TopObjects
addpkg TopQuarkAnalysis/Configuration
addpkg TopQuarkAnalysis/Examples
addpkg TopQuarkAnalysis/TopEventProducers
addpkg TopQuarkAnalysis/TopEventSelection
addpkg TopQuarkAnalysis/TopHitFit
addpkg TopQuarkAnalysis/TopJetCombination
addpkg TopQuarkAnalysis/TopKinFitter
addpkg TopQuarkAnalysis/TopObjectResolutions
addpkg TopQuarkAnalysis/TopSkimming          V07-01-04
addpkg TopQuarkAnalysis/TopTools             V06-07-13


# for full memory option of LHAPDF, we NEED to compile ElectroWeakAnalysis/Utilities after scram setup lhapdffull for speeding it up.
#For more information check the ElectroWeakAnalysis/Utilities/README file
scram setup lhapdffull
addpkg ElectroWeakAnalysis/Utilities


#checkdeps -a

scram b -j 8

echo
echo "Full installation successfully done"

