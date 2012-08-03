#!/bin/sh

# export VO_CMS_SW_DIR=/data/group/top/cmssw 
# source $VO_CMS_SW_DIR/cmsset_default.sh

###### TOP 2012  ########
CMS_version=CMSSW_5_2_5
export SCRAM_ARCH=slc5_amd64_gcc462

scram p -s CMSSW ${CMS_version}
cd ${CMS_version}/src
if [ $? != 0 ]; then
    exit 1
fi

echo export SCRAM_ARCH=${SCRAM_ARCH} > SCRAM_ARCH
chmod u+x SCRAM_ARCH

eval `scramv1 runtime -sh`

###### PAT #####

addpkg DataFormats/PatCandidates  V06-05-00
addpkg RecoJets/Configuration     V02-07-02
addpkg RecoTauTag/Configuration   V01-03-04
addpkg RecoTauTag/RecoTau         V01-02-03
addpkg RecoTauTag/TauTagTools     V01-02-03

###### Jet Energy Corrections #####

addpkg JetMETCorrections/Type1MET V04-06-03
echo "Fixing JetMETCorrections BuildFile"
mv JetMETCorrections/Type1MET/BuildFile.xml JetMETCorrections/Type1MET/BuildFile.xml.old
echo '<use   name="DataFormats/PatCandidates"/>' >  JetMETCorrections/Type1MET/BuildFile.xml
cat JetMETCorrections/Type1MET/BuildFile.xml.old >> JetMETCorrections/Type1MET/BuildFile.xml


###### Electron ID #####
addpkg RecoEgamma/ElectronIdentification V00-03-36
addpkg ElectroWeakAnalysis/WENu V00-04-02
cvs co -r V00-00-13 -d EGamma/EGammaAnalysisTools UserCode/EGamma/EGammaAnalysisTools
cd EGamma/EGammaAnalysisTools/data
cat download.url | xargs wget
cd ../../..

###### Lumi Reweighting #####
addpkg PhysicsTools/Utilities V08-03-17
addpkg SimDataFormats/PileupSummaryInfo V00-02-04

###### Hamburg TOP package (plus dependencies) #####

cvs co -d TopAnalysis UserCode/Bromo/TopAnalysis
cvs update -r B_5_2_X TopAnalyzer/python/ntuplewriter_cfi.py
cvs update -r B_5_2_X TopAnalyzer/python/FullLepGenAnalyzer_cfi.py
cvs update -r B_5_2_X TopFilter/python/filters/GeneratorTtDileptonFilter_cfi.py
cvs update -r B_5_2_X TopUtils/python/GenLevelBJetProducer_cfi.py
cvs update -r B_5_2_X TopUtils/python/genlevelbjetproducer_cfi.py
cvs update -r B_5_2_X TopUtils/python/HadronLevelBJetProducer_cfi.py

addpkg TopQuarkAnalysis/Configuration V06-02-00
addpkg TopQuarkAnalysis/TopEventSelection V06-07-14

#checkdeps -a

scram b -j12

