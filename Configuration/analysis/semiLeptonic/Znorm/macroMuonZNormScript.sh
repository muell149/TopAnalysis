#!/bin/sh

## use this file to do the whole analysis for calculation of the Z cross section with the tools
## of the semileptonic ttbar analysis, and for the calculation of the cross section ratio
## ttbar_meas / Z_meas and Z_meas / Z_theo.
## Finally also a new normalised ttbar cross section is calculated via
## ttbar_norm = ttbar_meas / Z_meas * Z_theo

## INSTRUCTIONS:
## + to be called from TopAnalysis/Configuration/analysis/semiLeptonic/ZNorm/
## + for each systematic variations three steps are performed:
##   1) call macroMuonZNorm.C for lumi-, effSF- and background variation weightings
##     -> saves histos to folderResults+whichFile+"_lumiweightedAndAddedHistos.root"
##     void macroMuonZNorm(TString sys="sysNo", bool saveHistos = true, bool drawPlots = false, bool savePlots = false)
##   2) call macroMuonZNormEfficiencies.C for efficiency and acceptance calculation
##     -> saves histos to folderResults+whichFile+"_efficiencyHistos.root"
##     void macroMuonZNormEfficiencies(TString sys="sysNo", bool save = true)
##   3) call macroMuonZNormXSec.C for calculating final cross sections and their ratios
##     -> saves output into text files _xSecResults.txt (cross sections)
##        and _effYieldResults.txt (efficiencies and yields)
##     void macroMuonZNormXSec(TString sys="sysNo", bool output=false, bool append=false)
##   4) after all systematic variations call again macroMuonZNorm.C and macroMuonZNormEfficiencies.C
##      without variations in order to create histos and stack plots for central values

## List of systematic variations:
##  /* 0:*/"sysNo"          , /* 1:*/"sysLumiUp"       , /* 2:*/"sysLumiDown"       , /* 3:*/"sysJESUp"     , 
##  /* 4:*/"sysJESDown"     , /* 5:*/"sysJERUp"        , /* 6:*/"sysJERDown"        , /* 7:*/"sysTopScaleUp", 
##  /* 8:*/"sysTopScaleDown", /* 9:*/"sysVBosonScaleUp", /*10:*/"sysVBosonScaleDown", /*11:*/"sysTopMatchUp", 
##  /*12:*/"sysTopMatchDown", /*13:*/"sysVBosonMatchUp", /*14:*/"sysVBosonMatchDown", /*15:*/"sysMuEffSFup" , 
##  /*16:*/"sysMuEffSFdown" , /*17:*/"sysISRFSRup"     , /*18:*/"sysISRFSRdown"     , /*19:*/"sysPileUp"    ,
##  /*20:*/"sysQCDup"       , /*21:*/"sysQCDdown"      , /*22:*/"sysSTopUp"         , /*23:*/"sysSTopDown"  ,
##  /*24:*/"sysDiBosUp"     , /*25:*/"sysDiBosDown"    , /*26:*/"sysTTbarUp"        , /*27:*/"sysTTbarDown",
##  /*28:*/"sysWjetsUp"     , /*29:*/"sysWjetsDown"    , /*30:*/"sysZTauTauUp"      , /*31:*/"sysZTauTauDown" 
##  /*32:*/"sysMuEffSFIsoIDup"  , /*33:*/"sysMuEffSFIsoIDdown", /*34:*/"sysMuEffSFTrigUp", /*35:*/"sysMuEffSFTrigDown",
##  /*36:*/"sysMuEffSFPreTrigUp", /*37:*/"sysMuEffSFPreTrigDown" };

# Array of systematic variations:
sysVar_=( \"sysNo\"           \"sysLumiUp\"        \"sysLumiDown\"        \"sysJESUp\"      
	  \"sysJESDown\"      \"sysJERUp\"         \"sysJERDown\"         \"sysTopScaleUp\" 
	  \"sysTopScaleDown\" \"sysVBosonScaleUp\" \"sysVBosonScaleDown\" \"sysTopMatchUp\" 
	  \"sysTopMatchDown\" \"sysVBosonMatchUp\" \"sysVBosonMatchDown\" \"sysMuEffSFup\"  
	  \"sysMuEffSFdown\"  \"sysISRFSRup\"      \"sysISRFSRdown\"      \"sysPileUp\"    
	  \"sysQCDup\"        \"sysQCDdown\"       \"sysSTopUp\"          \"sysSTopDown\"  
	  \"sysDiBosUp\"      \"sysDiBosDown\"     \"sysTTbarUp\"         \"sysTTbarDown\"
	  \"sysWjetsUp\"      \"sysWjetsDown\"     \"sysZTauTauUp\"       \"sysZTauTauDown\" 
	  \"sysMuEffSFIsoIDup\"  \"sysMuEffSFIsoIDdown\" \"sysMuEffSFTrigUp\" \"sysMuEffSFTrigDown\"
          \"sysMuEffSFPreTrigUp\" \"sysMuEffSFPreTrigDown\" ) 

echo
echo Do the Z cross section measurement and ttbar / Z normalisation.
echo
sleep 1

# loop over all systematic variations
for (( iSys=0; iSys<=37; iSys++ ))
  do
  ## if sysNo -> create new txt file, else append to existing txt file
  if [ ${sysVar_[$iSys]} = \"sysNo\" ]
    then append=false
    else append=true
  fi
  echo systematic variation: ${sysVar_[$iSys]} , text output appended to existing file: $append
  ## execute the root macros for each sysVar
  root -l -q -b './macroMuonZNorm.C+('${sysVar_[$iSys]}')'
  root -l -q -b './macroMuonZNormEfficiencies.C+('${sysVar_[$iSys]}')'
  root -l -q -b './macroMuonZNormXSec.C+('${sysVar_[$iSys]}', true, '$append')'
  echo ----------------------------------------------------------------------------------------
done
echo done

# ## loop over all systematic variations
# for sysVar in \"sysNo\" #\"sysTopScaleUp\"
#   do
# ## if sysNo -> create new txt file, else append to existing txt file
#   if [ $sysVar = \"sysNo\" ]
#     then append=false
#     else append=true
#   fi
#   echo systematic variation: $sysVar , text output appended to existing file: $append
# ## execute the root macros for each sysVar
#   root -l -q -b './macroMuonZNorm.C+('$sysVar')'
#   root -l -q -b './macroMuonZNormEfficiencies.C+('$sysVar')'
#   root -l -q -b './macroMuonZNormXSec.C+('$sysVar', true, '$append')'
# done
# echo done

