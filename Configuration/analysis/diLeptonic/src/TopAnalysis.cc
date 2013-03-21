#include "TopAnalysis.h"
#include "HistoListReader.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <TMath.h>
#include <TSystem.h>
#include <Math/VectorUtil.h>
#include <TLorentzVector.h>
#include <set>
#include <cmath>
#include <TString.h>
#include <limits>
#include <iomanip>
#include "utils.h"
#include "KinReco.h"

using ROOT::Math::VectorUtil::DeltaPhi;
using ROOT::Math::VectorUtil::DeltaR;

///top production xsec in pb
constexpr double TOPXSEC = 234;
/// Luminosity in 1/fb
constexpr double LUMI = 12.21; 

///do we want to run the sync excercise?
constexpr bool RUNSYNC = false;


constexpr double JETPTCUT = 30;
constexpr double JETETACUT = 2.4;


/** Initialise all histograms used in the analysis
 * 
 * @param TTree parameter is not used!
 */
void TopAnalysis::SlaveBegin ( TTree * )
{
    AnalysisBase::SlaveBegin(0);
    
    h_step4 = store(new TH1D ( "step4", "event count at after 2lepton", 10, 0, 10 ));       h_step4->Sumw2();
    h_step5 = store(new TH1D ( "step5", "event count at after Zcut", 10, 0, 10 ));          h_step5->Sumw2();
    h_step6 = store(new TH1D ( "step6", "event count at after 2jets", 10, 0, 10 ));         h_step6->Sumw2();
    h_step7 = store(new TH1D ( "step7", "event count at after MET", 10, 0, 10 ));           h_step7->Sumw2();
    h_step8 = store(new TH1D ( "step8", "event count at after 1btag", 10, 0, 10 ));         h_step8->Sumw2();
    h_step9 = store(new TH1D ( "step9", "event count at step after KinReco", 10, 0, 10 ));  h_step9->Sumw2();

    //h_jetMultiAll = store(new TH1D ( "HypjetMultiAll", "Jet Multiplicity (AllJets)", 10, -0.5, 9.5 ));
    h_jetMultiXSec = store(new TH1D ( "HypjetMultiXSec", "Jet Multiplicity (for cross-section)", 10, -0.5, 9.5 ));
    h_jetMulti = store(new TH1D ( "HypjetMulti", "Jet Multiplicity", 10, -0.5, 9.5 ));
    h_jetMulti_diLep = store(new TH1D ( "HypjetMulti_diLep", "Jet Multiplicity (after dilepton)", 10, -0.5, 9.5 ));
    h_jetMulti_noBTag = store(new TH1D ( "HypjetMulti_noBTag", "Jet Multiplicity (after dilepton before btag)", 10, -0.5, 9.5 ));
    h_jetMultiNoPU = store(new TH1D ( "HypjetMultiNoPU", "Jet Multiplicity (No Pileup or lumi weight)", 10, -0.5, 9.5 ));
//     h_jetMultiVisTop = store(new TH1D ( "HypjetMultiVisTop", "Jet Multiplicity for Visible Top (No Pileup or lumi Weight)", 10, -0.5, 9.5 ));
    h_BjetMulti = store(new TH1D ( "HypBjetMulti", "B-Jet Multiplicity", 10, -0.5, 9.5 ));
    h_BjetMulti_noBTag = store(new TH1D ( "HypBjetMulti_noBTag", "B-Jet Multiplicity before B-Tag requirement", 10, -0.5, 9.5 ));

    h_HypTTBarRapidity = store(new TH1D ( "HypTTBarRapidity", "Rapidity of TTbar System (HYP)", 100, -5, 5 ));
    h_HypTTBarpT = store(new TH1D ( "HypTTBarpT", "pT of TTbar System (HYP)", 500, 0, 500 ));
    h_HypTTBarMass = store(new TH1D ( "HypTTBarMass", "Mass of TTbar System (HYP)", 2000, 0, 2000 ));
    h_HypLLBarMass = store(new TH1D ( "HypLLBarMass", "Mass of LLbar System (HYP)", 500, 0, 1000 ));
    h_HypLLBarpT = store(new TH1D ( "HypLLBarpT", "pT of LLbar System (HYP)", 200, 0, 1000 ));

    h_VisGenTTBarMass = store(new TH1D ( "VisGenTTBarMass", "Mass of TTbar System(VisGEN)", 2000, 0, 2000 ));
    h_VisGenTTBarRapidity = store(new TH1D ( "VisGenTTBarRapidity", "Rapidity of TTbar System(VisGEN)", 100, -5, 5 ));
    h_VisGenTTBarpT = store(new TH1D ( "VisGenTTBarpT", "pT of TTbar System(VisGEN)", 1200, 0, 1200 ));
    h_VisGenTopRapidity = store(new TH1D ( "VisGenTopRapidity", "Rapidity of Top(VisGEN)", 100, -5, 5 ));
    h_VisGenAntiTopRapidity = store(new TH1D ( "VisGenAntiTopRapidity", "Rapidity of AntiTop(VisGEN)", 100, -5, 5 ));

    h_VisGenLLBarpT = store(new TH1D ( "VisGenLLBarpT", "pT of LLbar System(VisGEN)", 200, 0, 1000 ));
    h_VisGenLLBarMass = store(new TH1D ( "VisGenLLBarMass", "Mass of LLbar System(VisGEN)", 500, 0, 1000 ));

    h_RecoTTBarMass = store(new TH1D ( "RecoTTBarMass","Mass of TTbar System (HYP)",2000,0,2000 ));
    h_RecoTTBarRapidity = store(new TH1D ( "RecoTTBarRapidity","Rapidity of TTbar System (HYP)",100,-5,5 ));
    h_RecoTTBarpT = store(new TH1D ( "RecoTTBarpT","pT of TTbar System (HYP)",1200,0,1200 ));
    h_RecoToppT = store(new TH1D ( "RecoToppT","pT of Top (HYP)",1200,0,1200 ));
    h_RecoAntiToppT = store(new TH1D ( "RecoAntiToppT","pT of AntiTop (HYP)",1200,0,1200 ));
    h_RecoTopRapidity = store(new TH1D ( "RecoTopRapidity","Rapidity of Top (HYP)",100,-5,5 ));
    h_RecoAntiTopRapidity = store(new TH1D ( "RecoAntiTopRapidity","Rapidity of AntiTop (HYP)",100,-5,5 ));

    h_RecoBJetpT = store(new TH1D ( "RecoBJetpT","pT of BJet (HYP)",80,0,400 ));
    h_RecoAntiBJetpT = store(new TH1D ( "RecoAntiBJetpT","pT of AntiBJet (HYP)",80,0,400 ));
    h_RecoBJetRapidity = store(new TH1D ( "RecoBJetRapidity","Rapidity of BJet (HYP)",100,-5,5 ));
    h_RecoAntiBJetRapidity = store(new TH1D ( "RecoAntiBJetRapidity","Rapidity of AntiBJet (HYP)",100,-5,5 ));
    h_RecoBJetEta = store(new TH1D ( "RecoBJetEta","#eta of BJet (HYP)",100,-5,5 ));
    h_RecoAntiBJetEta = store(new TH1D ( "RecoAntiBJetEta","#eta of AntiBJet (HYP)",100,-5,5 ));

    h_RecoLLBarMass = store(new TH1D ( "RecoLLBarMass","Mass of LLbar System (HYP)",500,0,1000 ));
    h_RecoLLBarpT = store(new TH1D ( "RecoLLBarpT","pT of LLbar System (HYP)",200,0,1000 ));
    h_RecoLeptonpT = store(new TH1D ( "RecoLeptonpT","pT of Lepton (HYP)",240,0,1200 ));
    h_RecoAntiLeptonpT = store(new TH1D ( "RecoAntiLeptonpT","pT of AntiLepton (HYP)",240,0,1200 ));
    h_RecoLeptonEta = store(new TH1D ( "RecoLeptonEta","Eta of Lepton (HYP)",100,-5,5 ));
    h_RecoAntiLeptonEta = store(new TH1D ( "RecoAntiLeptonEta","Eta of AntiLepton (HYP)",100,-5,5 ));

    h_VisGenAll = store(new TH1D ( "VisGenAll", "All Visible Generated particles (IM)", 40, 0, 400 ));
    h_GenAll = store(new TH1D ( "GenAll", "AllGenerated particles (IM)", 40, 0, 400 ));         h_GenAll->Sumw2();
    Allh1_postKinReco = store(new TH1D ( "Allh1_postKinReco", "DiLepton Mass", 40, 0, 400 ));
    h_diLepMassFull = store(new TH1D ( "DIMFull", "DiLepton Mass (Full Range)", 100, 0, 300 ));
    h_diLepMassFull_fullSel = store(new TH1D ( "DIMFull_fullSel", "DiLepton Mass (Full Range)", 100, 0, 300 ));
    Looseh1 = store(new TH1D ( "Looseh1", "DiLepton Mass", 40, 0, 400 ));
    Zh1_postKinReco = store(new TH1D ( "Zh1_postKinReco", "DiLepton Mass in Z Window", 40, 0, 400 ));
    TTh1_postKinReco = store(new TH1D ( "TTh1_postKinReco", "DiLepton Mass out of Z Window", 40, 0, 400 ));

    Allh1_postZcut = store(new TH1D ( "Allh1_postZcut", "DiLepton Mass", 40, 0, 400 ));
    Zh1_postZcut = store(new TH1D ( "Zh1_postZcut", "DiLepton Mass in Z Window", 40, 0, 400 ));
    TTh1_postZcut = store(new TH1D ( "TTh1_postZcut", "DiLepton Mass out of Z Window", 40, 0, 400 ));

    Allh1_post2jets = store(new TH1D ( "Allh1_post2jets", "DiLepton Mass", 40, 0, 400 ));
    Zh1_post2jets = store(new TH1D ( "Zh1_post2jets", "DiLepton Mass in Z Window", 40, 0, 400 ));
    TTh1_post2jets = store(new TH1D ( "TTh1_post2jets", "DiLepton Mass out of Z Window", 40, 0, 400 ));

    Allh1_postMET = store(new TH1D ( "Allh1_postMET", "DiLepton Mass", 40, 0, 400 ));
    Zh1_postMET = store(new TH1D ( "Zh1_postMET", "DiLepton Mass in Z Window", 40, 0, 400 ));
    TTh1_postMET = store(new TH1D ( "TTh1_postMET", "DiLepton Mass out of Z Window", 40, 0, 400 ));

    Allh1_post1btag = store(new TH1D ( "Allh1_post1btag", "DiLepton Mass", 40, 0, 400 ));
    Zh1_post1btag = store(new TH1D ( "Zh1_post1btag", "DiLepton Mass in Z Window", 40, 0, 400 ));
    TTh1_post1btag = store(new TH1D ( "TTh1_post1btag", "DiLepton Mass out of Z Window", 40, 0, 400 ));

    
    h_vertMulti = store(new TH1D ( "vertMulti", "Primary Vertex Multiplicity", 30, 0, 30 ));
    h_vertMulti_noPU = store(new TH1D ( "vertMulti_noPU", "Primary Vertex Multiplicity (no Pileup)", 30, 0, 30 ));
    h_MET = store(new TH1D ( "MET", "Missing Transverse Energy", 80, 0, 400 ));
    h_jetpT = store(new TH1D ( "jetpT", "jet pT", 80, 0, 400 ));
    h_jetHT = store(new TH1D ( "jetHT", "jet HT", 80, 0, 1000 ));

    h_MuonpT = store(new TH1D ( "MuonpT", "Muon pT", 80, 0, 400 ));
    h_MuonEta = store(new TH1D ( "MuonEta", "Muon Eta", 100, -5, 5 ));
    h_ElectronpT = store(new TH1D ( "ElectronpT", "Electron pT", 80, 0, 400 ));
    h_ElectronEta = store(new TH1D ( "ElectronEta", "Electron Eta", 100, -5, 5 ));

    h_leptonPtBeforeKinReco = store(new TH1D ( "LeptonpTbkr", "Lepton pT (before kin reco)", 80, 0, 400 ));
    h_leptonPtAfterKinReco = store(new TH1D ( "LeptonpTakr", "Lepton pT (after kin reco)", 80, 0, 400 ));
    h_leptonEtaBeforeKinReco = store(new TH1D ( "LeptonEtabkr", "Lepton #eta (before kin reco)", 80, -2.5, 2.5 ));
    h_leptonEtaAfterKinReco = store(new TH1D ( "LeptonEtaakr", "Lepton #eta (after kin reco)", 80, -2.5, 2.5 ));
    h_METBeforeKinReco = store(new TH1D ( "METbkr", "Missing Transverse Energy (before kin reco)", 80, 0, 400 ));
    h_METAfterKinReco = store(new TH1D ( "METakr", "Missing Transverse Energy (after kin reco)", 80, 0, 400 ));
    h_bjetetaBeforeKinReco = store(new TH1D ( "BjetEtabkr", "b-jet eta (before kin reco)", 80, -2.5, 2.5 ));
    h_bjetetaAfterKinReco = store(new TH1D ( "BjetEtaakr", "b-jet eta (after kin reco)", 80, -2.5, 2.5 ));
    
    
    h_LeptonpT_postMETcut = store(new TH1D ( "LeptonpT_postMETcut", "Lepton pT (post MET cut)", 80, 0, 400 ));
    h_LeptonEta_postMETcut = store(new TH1D ( "LeptonEta_postMETcut", "Lepton Eta (post MET cut)", 100, -5, 5 ));
    h_AntiLeptonpT_postMETcut = store(new TH1D ( "AntiLeptonpT_postMETcut", "AntiLepton pT (post MET cut)", 80, 0, 400 ));
    h_AntiLeptonEta_postMETcut = store(new TH1D ( "AntiLeptonEta_postMETcut", "AntiLepton Eta (post MET cut)", 100, -5, 5 ));
    h_MuonpT_postMETcut = store(new TH1D ( "MuonpT_postMETcut", "Muon pT (post MET cut)", 80, 0, 400 ));
    h_MuonEta_postMETcut = store(new TH1D ( "MuonEta_postMETcut", "Muon Eta (post MET cut)", 100, -5, 5 ));
    h_ElectronpT_postMETcut = store(new TH1D ( "ElectronpT_postMETcut", "Electron pT (post MET cut)", 80, 0, 400 ));
    h_ElectronEta_postMETcut = store(new TH1D ( "ElectronEta_postMETcut", "Electron Eta (post MET cut)", 100, -5, 5 ));
    
    h_LeptonpT = store(new TH1D ( "LeptonpT", "Lepton pT", 80, 0, 400 ));
    h_LeptonEta = store(new TH1D ( "LeptonEta", "Lepton Eta", 100, -5, 5 ));
    h_LeptonpT_diLep = store(new TH1D ( "LeptonpT_diLep", "Lepton pT (after dilepton cut)", 80, 0, 400 ));
    h_LeptonEta_diLep = store(new TH1D ( "LeptonEta_diLep", "Lepton Eta (after dilepton cut)", 100, -5, 5 ));

    h_AntiLeptonpT = store(new TH1D ( "AntiLeptonpT", "AntiLepton pT", 80, 0, 400 ));
    h_AntiLeptonEta = store(new TH1D ( "AntiLeptonEta", "AntiLepton Eta", 100, -5, 5 ));
    h_AntiLeptonpT_diLep = store(new TH1D ( "AntiLeptonpT_diLep", "Lepton pT (after dilepton cut)", 80, 0, 400 ));
    h_AntiLeptonEta_diLep = store(new TH1D ( "AntiLeptonEta_diLep", "Lepton Eta (after dilepton cut)", 100, -5, 5 ));

    h_HypToppT = store(new TH1D ( "HypToppT", "Top pT", 400, 0, 400 ));
    h_HypTopEta = store(new TH1D ( "HypTopEta", "Top #eta", 100, -5, 5 ));
    h_HypTopMass = store(new TH1D ( "HypTopMass", "Top Mass", 80, 0, 400 ));
    h_HypTopRapidity = store(new TH1D ( "HypTopRapidity", "Top Rapidity", 100, -5, 5 ));
    
    h_HypAntiToppT = store(new TH1D ( "HypAntiToppT", "AntiTop pT", 400, 0, 400 ));
    h_HypAntiTopEta = store(new TH1D ( "HypAntiTopEta", "AntiTop #eta", 100, -5, 5 ));
    h_HypAntiTopMass = store(new TH1D ( "HypAntiTopMass", "AntiTop Mass", 80, 0, 400 ));
    h_HypAntiTopRapidity = store(new TH1D ( "HypAntiTopRapidity", "Top Rapidity", 100, -5, 5 ));

    h_HypLeptonpT = store(new TH1D ( "HypLeptonpT", "Lepton Hypothesis pT", 80, 0, 400 ));
    h_HypLeptonEta = store(new TH1D ( "HypLeptonEta", "Lepton Eta", 100, -5, 5 ));

    h_HypAntiLeptonpT = store(new TH1D ( "HypAntiLeptonpT", "AntiLepton Hypothesis pT", 80, 0, 400 ));
    h_HypAntiLeptonEta = store(new TH1D ( "HypAntiLeptonEta", "AntiLepton Hypothesis Eta", 100, -5, 5 ));

    h_HypBJetpT = store(new TH1D ( "HypBJetpT", "B Hypothesis pT", 80, 0, 400 ));
    h_HypBJetEta = store(new TH1D ( "HypBJetEta", "B Hypothesis Eta", 100, -5, 5 ));
    h_HypBJetRapidity = store(new TH1D ( "HypBJetRapidity", "B Hypothesis Eta", 100, -5, 5 ));

    h_HypAntiBJetpT = store(new TH1D ( "HypAntiBJetpT", "AntiB Hypothesis pT", 80, 0, 400 ));
    h_HypAntiBJetEta = store(new TH1D ( "HypAntiBJetEta", "AntiB Hypothesis Eta", 100, -5, 5 ));
    h_HypAntiBJetRapidity = store(new TH1D ( "HypAntiBJetRapidity", "AntiB Hypothesis Eta", 100, -5, 5 ));

    h_VisGenToppT = store(new TH1D ( "VisGenToppT", "Top pT (VisGen)", 400, 0, 400 ));
    h_VisGenTopEta = store(new TH1D ( "VisGenTopEta", "Top Eta (VisGen)", 100, -5, 5 ));

    h_VisGenAntiToppT = store(new TH1D ( "VisGenAntiToppT", "AntiTop pT (VisGen)", 400, 0, 400 ));
    h_VisGenAntiTopEta = store(new TH1D ( "VisGenAntiTopEta", "AntiTop pT (VisGen)", 100, -5, 5 ));

    h_VisGenLeptonpT = store(new TH1D ( "VisGenLeptonpT", "Lepton VisGenothesis pT", 80, 0, 400 ));
    h_VisGenLeptonEta = store(new TH1D ( "VisGenLeptonEta", "Lepton Eta", 100, -5, 5 ));

    h_VisGenAntiLeptonpT = store(new TH1D ( "VisGenAntiLeptonpT", "AntiLepton VisGenothesis pT", 80, 0, 400 ));
    h_VisGenAntiLeptonEta = store(new TH1D ( "VisGenAntiLeptonEta", "AntiLepton VisGenothesis Eta", 100, -5, 5 ));

    h_VisGenBJetpT = store(new TH1D ( "VisGenBJetpT", "B VisGenothesis pT", 80, 0, 400 ));
    h_VisGenBJetEta = store(new TH1D ( "VisGenBJetEta", "B VisGenothesis Eta", 100, -5, 5 ));
    h_VisGenBJetRapidity = store(new TH1D ( "VisGenBJetRapidity", "B VisGenothesis Rapidity", 100, -5, 5 ));

    h_VisGenAntiBJetpT = store(new TH1D ( "VisGenAntiBJetpT", "AntiB VisGenothesis pT", 80, 0, 400 ));
    h_VisGenAntiBJetEta = store(new TH1D ( "VisGenAntiBJetEta", "AntiB VisGenothesis Eta", 100, -5, 5 ));
    h_VisGenAntiBJetRapidity = store(new TH1D ( "VisGenAntiBJetRapidity", "AntiB VisGenothesis Rapidity", 100, -5, 5 ));

    /*  h_VisGenBQuarkpT = store(new TH1D("VisGenBQuarkpT", "B Quark VisGenothesis pT", 80, 0, 400));
    h_VisGenBQuarkEta = store(new TH1D("VisGenBQuarkEta", "B Quark VisGenothesis Eta", 100, -5, 5));
    h_VisGenBQuarkRapidity = store(new TH1D("VisGenBQuarkRapidity", "B Quark VisGenothesis Rapidity", 100, -5, 5));

    h_VisGenAntiBQuarkpT = store(new TH1D("VisGenAntiBQuarkpT", "AntiB Quark VisGenothesis pT", 80, 0, 400));
    h_VisGenAntiBQuarkEta = store(new TH1D("VisGenAntiBQuarkEta", "AntiB Quark VisGenothesis Eta", 100, -5, 5));
    h_VisGenAntiBQuarkRapidity = store(new TH1D("VisGenAntiBQuarkRapidity", "AntiB Quark VisGenothesis Rapidity", 100, -5, 5));
    */
    /*h_GenToppT = store(new TH1D("GenToppT", "Top pT (Gen)", 80, 0, 400));
    h_GenTopEta = store(new TH1D("GenTopEta", "Top Eta (Gen)", 100, -5, 5));
    h_GenTopRapidity = store(new TH1D("GenTopRapidity", "Top Rapidity (Gen)", 100, -5, 5));

    h_GenAntiToppT = store(new TH1D("GenAntiToppT", "AntiTop pT (Gen)", 80, 0, 400));
    h_GenAntiTopEta = store(new TH1D("GenAntiTopEta", "AntiTop Eta (Gen)", 100, -5, 5));
    h_GenAntiTopRapidity = store(new TH1D("GenAntiTopRapidity", "AntiTop Rapidity (Gen)", 100, -5, 5));

    h_GenLeptonpT = store(new TH1D("GenLeptonpT", "Lepton Genothesis pT", 80, 0, 400));
    h_GenLeptonEta = store(new TH1D("GenLeptonEta", "Lepton Eta", 100, -5, 5));

    h_GenAntiLeptonpT = store(new TH1D("GenAntiLeptonpT", "AntiLepton Genothesis pT", 80, 0, 400));
    h_GenAntiLeptonEta = store(new TH1D("GenAntiLeptonEta", "AntiLepton Genothesis Eta", 100, -5, 5));

    h_GenBQuarkpT = store(new TH1D("GenBQuarkpT", "B Quark Genothesis pT", 80, 0, 400));
    h_GenBQuarkEta = store(new TH1D("GenBQuarkEta", "B Quark Genothesis Eta", 100, -5, 5));
    h_GenBQuarkRapidity = store(new TH1D("GenBQuarkRapidity", "B Quark Genothesis Rapidity", 100, -5, 5));

    h_GenAntiBQuarkpT = store(new TH1D("GenAntiBQuarkpT", "AntiB Quark Genothesis pT", 80, 0, 400));
    h_GenAntiBQuarkEta = store(new TH1D("GenAntiBQuarkEta", "AntiB Quark Genothesis Eta", 100, -5, 5));
    h_GenAntiBQuarkRapidity = store(new TH1D("GenAntiBQuarkRapidity", "AntiB Quark Genothesis Rapidity", 100, -5, 5));

    h_GenBJetpT = store(new TH1D("GenBJetpT", "B Genothesis pT", 80, 0, 400));
    h_GenBJetEta = store(new TH1D("GenBJetEta", "B Genothesis Eta", 100, -5, 5));
    h_GenBJetRapidity = store(new TH1D("GenBJetRapidity", "B Genothesis Rapidity", 100, -5, 5));

    h_GenAntiBJetpT = store(new TH1D("GenAntiBJetpT", "AntiB Genothesis pT", 80, 0, 400));
    h_GenAntiBJetEta = store(new TH1D("GenAntiBJetEta", "AntiB Genothesis Eta", 100, -5, 5));
    h_GenAntiBJetRapidity = store(new TH1D("GenAntiBJetRapidity", "Anti B Genothesis Rapidity", 100, -5, 5));
    */
    h_GenRecoBJetpT = store(new TH2D ( "GenRecoBJetpT", "Gen/Reco Matching", 80, 0, 400, 80, 0, 400 ));
    h_GenRecoBJetEta = store(new TH2D ( "GenRecoBJetEta", "Gen/Reco Matching", 100, -5, 5, 100, -5, 5 ));
    h_GenRecoBJetRapidity = store(new TH2D ( "GenRecoBJetRapidity", "Gen/Reco Matching", 100, -5, 5, 100, -5, 5 ));

    h_GenRecoAntiBJetpT = store(new TH2D ( "GenRecoAntiBJetpT", "Gen/Reco Matching", 80, 0, 400, 80, 0, 400 ));
    h_GenRecoAntiBJetEta = store(new TH2D ( "GenRecoAntiBJetEta", "Gen/Reco Matching", 100, -5, 5, 100, -5, 5 ));
    h_GenRecoAntiBJetRapidity = store(new TH2D ( "GenRecoAntiBJetRapidity", "Gen/Reco Matching", 100, -5, 5, 100, -5, 5 ));

    h_GenRecoLeptonEta = store(new TH2D ( "GenRecoLeptonEta", "Gen/Reco Matching", 100, -5, 5, 100, -5, 5 ));
    h_GenRecoAntiLeptonEta = store(new TH2D ( "GenRecoAntiLeptonEta", "Gen/Reco Matching", 100, -5, 5, 100, -5, 5 ));
    h_GenRecoLeptonpT = store(new TH2D ( "GenRecoLeptonpT", "Gen/Reco Matching", 80, 0, 400, 80, 0, 400 ));
    h_GenRecoAntiLeptonpT = store(new TH2D ( "GenRecoAntiLeptonpT", "Gen/Reco Matching", 80, 0, 400, 80, 0, 400 ));

    h_GenRecoTopRapidity = store(new TH2D ( "GenRecoTopRapidity", "Gen/Reco Matching", 100, -5, 5, 100, -5, 5 ));
    h_GenRecoAntiTopRapidity = store(new TH2D ( "GenRecoAntiTopRapidity", "Gen/Reco Matching", 100, -5, 5, 100, -5, 5 ));
    h_GenRecoToppT = store(new TH2D ( "GenRecoToppT", "Gen/Reco Matching", 400, 0, 400, 400, 0, 400 ));
    h_GenRecoAntiToppT = store(new TH2D ( "GenRecoAntiToppT", "Gen/Reco Matching", 400, 0, 400, 400, 0, 400 ));

    h_GenRecoMet = store(new TH2D("GenRecoMet", "Missing ET in the event", 500, 0, 500, 500, 0, 500));
    h_VisGenMet = store(new TH1D("VisGenMet", "MET (VisGEN)", 500, 0, 500));
    h_RecoMet = store(new TH1D("RecoMet", "Reconstructed MET", 500, 0, 500));
    h_HypMet = store(new TH1D("HypMet","MET ", 500, 0, 500));
    
    h_GenRecoHT = store(new TH2D("GenRecoHT", "HT in the event", 800, 0, 800, 800, 0, 800));
    h_VisGenHT = store(new TH1D("VisGenHT", "HT (VisGEN)", 800, 0, 800));
    h_RecoHT = store(new TH1D("RecoHT", "Reconstructed HT", 800, 0, 800));
    h_HypHT = store(new TH1D("HypHT", "HT", 800, 0, 800));
    
    h_GenRecoNeutrinopT = store(new TH2D("GenRecoNeutrinopT", "Gen/Reco nu pt", 80, 0, 400, 80, 0, 400));
    h_VisGenNeutrinopT = store(new TH1D("VisGenNeutrinopT", "Nu pT (VisGEN)", 80, 0, 400));
    h_RecoNeutrinopT = store(new TH1D("RecoNeutrinopT", "reco nu pT", 80, 0, 400));
    h_HypNeutrinopT = store(new TH1D("HypNeutrinopT", "hyp nu pT", 80, 0, 400));
    
    h_GenRecoAntiNeutrinopT = store(new TH2D("GenRecoAntiNeutrinopT", "Gen/Reco nubar pt", 80, 0, 400, 80, 0, 400));
    h_VisGenAntiNeutrinopT = store(new TH1D("VisGenAntiNeutrinopT", "Nubar pT (VisGEN)", 80, 0, 400));
    h_RecoAntiNeutrinopT = store(new TH1D("RecoAntiNeutrinopT", "reco nubar pT", 80, 0, 400));
    h_HypAntiNeutrinopT = store(new TH1D("HypAntiNeutrinopT", "hyp nubar pT", 80, 0, 400));
    
    
    h_GenRecoTTBarRapidity = store(new TH2D ( "GenRecoTTBarRapidity", "Rapidity of TTbar System (HYP)", 100, -5, 5, 100, -5, 5 ));
    h_GenRecoTTBarpT = store(new TH2D ( "GenRecoTTBarpT", "pT of TTbar System (HYP)", 500, 0, 500, 500, 0, 500 ));
    h_GenRecoTTBarMass = store(new TH2D ( "GenRecoTTBarMass", "Mass of TTbar System (HYP)", 2000, 0, 2000, 2000, 0, 2000 ));
    h_GenRecoLLBarMass = store(new TH2D ( "GenRecoLLBarMass", "Mass of LLbar System (HYP)", 500, 0, 1000, 500, 0, 1000 ));
    h_GenRecoLLBarpT = store(new TH2D ( "GenRecoLLBarpT", "pT of LLbar System (HYP)", 200, 0, 1000, 200, 0, 1000 ));
    
    h_NJetMatching = store(new TH1D ( "NJetMatching", "NJet Gen/Reco Matching", 5, 0, 5 ));

    h_GenRecoLLBarDPhi = store(new TH2D ( "GenRecoLLBarDPhi", "Gen/Reco Matching", 320, 0., 3.2, 320, 0., 3.2 ));
    h_GenRecoLeptonantiBjetMass = store(new TH2D ( "GenRecoLeptonBjetMass", "Gen/Reco Matching", 500, 0, 1000, 500, 0, 1000 ));
    h_GenRecoAntiLeptonBjetMass = store(new TH2D ( "GenRecoAntiLeptonBjetMass", "Gen/Reco Matching", 500, 0, 1000, 500, 0, 1000 ));
    h_GenRecoJetMult = store(new TH2D ( "GenRecoJetMult", "Gen/Reco Matching", 26, -0.5, 25.5, 26, -0.5, 25.5 ));

    h_HypLLBarDPhi = store(new TH1D ( "HypLLBarDPhi", "#Delta#phi(Lep, AntiLep) (HYP)",320, 0., 3.2 ));
    h_HypLeptonantiBjetMass = store(new TH1D ( "HypLeptonBjetMass", "Mass(Lep, AntiBJet) (HYP)", 500, 0, 1000 ));
    h_HypAntiLeptonBjetMass = store(new TH1D ( "HypAntiLeptonBjetMass", "Mass(AntiLep, BJet) (HYP)", 500, 0, 1000 ));
    h_HypJetMult = store(new TH1D ( "HypJetMult", "Jet Multiplicity (HYP)", 26, -0.5, 25.5 ));

    h_VisGenLLBarDPhi = store(new TH1D ( "VisGenLLBarDPhi", "#Delta #Phi (Lep, AntiLep) (VisGEN)", 320, 0., 3.2 ));
    h_VisGenLeptonantiBjetMass = store(new TH1D ( "VisGenLeptonBjetMass", "M(Lep, AntiBJet) (VisGEN)", 500, 0, 1000 ));
    h_VisGenAntiLeptonBjetMass = store(new TH1D ( "VisGenAntiLeptonBjetMass", "M(AntiLep, BJet) (VisGEN)", 500, 0, 1000 ));
    h_VisGenJetMult = store(new TH1D ( "VisGenJetMult", "Jet Multiplicty (VisGEN)", 26, -0.5, 25.5 ));

    h_RecoLLBarDPhi = store(new TH1D ( "RecoLLBarDPhi", "#Delta #Phi (Lep, AntiLep) (Reco)", 320, 0., 3.2 ));
    h_RecoLeptonantiBjetMass = store(new TH1D ( "RecoLeptonBjetMass", "M(Lep, AntiBJet) (Reco)", 500, 0, 1000 ));
    h_RecoAntiLeptonBjetMass = store(new TH1D ( "RecoAntiLeptonBjetMass", "M(AntiLep, BJet) (Reco)", 500, 0, 1000 ));
    h_RecoJetMult = store(new TH1D ( "RecoJetMult", "Jet Multiplicty (Reco)", 26, -0.5, 25.5 ));

    h_HypToppTLead = store(new TH1D ( "HypToppTLead","Leading pT Top pT",400,0,400 ));
    h_RecoToppTLead = store(new TH1D ( "RecoToppTLead","Leading pT Top pT",400,0,400 ));
    h_VisGenToppTLead = store(new TH1D ( "VisGenToppTLead","Leading pT Top pT",400,0,400 ));
    h_GenRecoToppTLead = store(new TH2D ( "GenRecoToppTLead", "Gen/Reco Matching", 400,0,400,400,0,400 ));

    h_HypToppTNLead = store(new TH1D ( "HypToppTNLead","NLeading pT Top pT",400,0,400 ));
    h_RecoToppTNLead = store(new TH1D ( "RecoToppTNLead","NLeading pT Top pT",400,0,400 ));
    h_VisGenToppTNLead = store(new TH1D ( "VisGenToppTNLead","NLeading pT Top pT",400,0,400 ));
    h_GenRecoToppTNLead = store(new TH2D ( "GenRecoToppTNLead", "Gen/Reco Matching", 400,0,400,400,0,400 ));

    h_HypTopRapidityLead = store(new TH1D ( "HypTopRapidityLead","Leading pT Top Rapidity",100,-5,5 ));
    h_RecoTopRapidityLead = store(new TH1D ( "RecoTopRapidityLead","Leading pT Top Rapidity",100,-5,5 ));
    h_VisGenTopRapidityLead = store(new TH1D ( "VisGenTopRapidityLead","Leading pT Top Rapidity",100,-5,5 ));
    h_GenRecoTopRapidityLead = store(new TH2D ( "GenRecoTopRapidityLead", "Gen/Reco Matching", 100,-5,5,100,-5,5 ));

    h_HypTopRapidityNLead = store(new TH1D ( "HypTopRapidityNLead","NLeading pT Top Rapidity",100,-5,5 ));
    h_RecoTopRapidityNLead = store(new TH1D ( "RecoTopRapidityNLead","NLeading pT Top Rapidity",100,-5,5 ));
    h_VisGenTopRapidityNLead = store(new TH1D ( "VisGenTopRapidityNLead","NLeading pT Top Rapidity",100,-5,5 ));
    h_GenRecoTopRapidityNLead = store(new TH2D ( "GenRecoTopRapidityNLead", "Gen/Reco Matching", 100,-5,5,100,-5,5 ));

    h_HypTopMassLead = store(new TH1D ( "HypTopMassLead","Leading pT Top Mass",80,0,400 ));
    h_RecoTopMassLead = store(new TH1D ( "RecoTopMassLead","Leading pT Top Mass",80,0,400 ));
    h_VisGenTopMassLead = store(new TH1D ( "VisGenTopMassLead","Leading pT Top Mass",80,0,400 ));
    h_GenRecoTopMassLead = store(new TH2D ( "GenRecoTopMassLead", "Gen/Reco Matching", 80,0,400,80,0,400 ));

    h_HypTopMassNLead = store(new TH1D ( "HypTopMassNLead","NLeading pT Top Mass",80,0,400 ));
    h_RecoTopMassNLead = store(new TH1D ( "RecoTopMassNLead","NLeading pT Top Mass",80,0,400 ));
    h_VisGenTopMassNLead = store(new TH1D ( "VisGenTopMassNLead","NLeading pT Top Mass",80,0,400 ));
    h_GenRecoTopMassNLead = store(new TH2D ( "GenRecoTopMassNLead", "Gen/Reco Matching", 80,0,400,80,0,400 ));


    h_HypLeptonpTLead = store(new TH1D ( "HypLeptonpTLead","Leading pT Lepton pT",400,0,400 ));
    h_RecoLeptonpTLead = store(new TH1D ( "RecoLeptonpTLead","Leading pT Lepton pT",400,0,400 ));
    h_VisGenLeptonpTLead = store(new TH1D ( "VisGenLeptonpTLead","Leading pT Lepton pT",400,0,400 ));
    h_GenRecoLeptonpTLead = store(new TH2D ( "GenRecoLeptonpTLead", "Gen/Reco Matching", 400,0,400,400,0,400 ));

    h_HypLeptonpTNLead = store(new TH1D ( "HypLeptonpTNLead","NLeading pT Lepton pT",400,0,400 ));
    h_RecoLeptonpTNLead = store(new TH1D ( "RecoLeptonpTNLead","NLeading pT Lepton pT",400,0,400 ));
    h_VisGenLeptonpTNLead = store(new TH1D ( "VisGenLeptonpTNLead","NLeading pT Lepton pT",400,0,400 ));
    h_GenRecoLeptonpTNLead = store(new TH2D ( "GenRecoLeptonpTNLead", "Gen/Reco Matching", 400,0,400,400,0,400 ));

    h_HypLeptonEtaLead = store(new TH1D ( "HypLeptonEtaLead","Leading pT Lepton Eta",100,-5,5 ));
    h_RecoLeptonEtaLead = store(new TH1D ( "RecoLeptonEtaLead","Leading pT Lepton Eta",100,-5,5 ));
    h_VisGenLeptonEtaLead = store(new TH1D ( "VisGenLeptonEtaLead","Leading pT Lepton Eta",100,-5,5 ));
    h_GenRecoLeptonEtaLead = store(new TH2D ( "GenRecoLeptonEtaLead", "Gen/Reco Matching", 100,-5,5,100,-5,5 ));

    h_HypLeptonEtaNLead = store(new TH1D ( "HypLeptonEtaNLead","NLeading pT Lepton Eta",100,-5,5 ));
    h_RecoLeptonEtaNLead = store(new TH1D ( "RecoLeptonEtaNLead","NLeading pT Lepton Eta",100,-5,5 ));
    h_VisGenLeptonEtaNLead = store(new TH1D ( "VisGenLeptonEtaNLead","NLeading pT Lepton Eta",100,-5,5 ));
    h_GenRecoLeptonEtaNLead = store(new TH2D ( "GenRecoLeptonEtaNLead", "Gen/Reco Matching", 100,-5,5,100,-5,5 ));

    h_HypBJetpTLead = store(new TH1D ( "HypBJetpTLead","Leading pT BJet pT",400,0,400 ));
    h_RecoBJetpTLead = store(new TH1D ( "RecoBJetpTLead","Leading pT BJet pT",400,0,400 ));
    h_VisGenBJetpTLead = store(new TH1D ( "VisGenBJetpTLead","Leading pT BJet pT",400,0,400 ));
    h_GenRecoBJetpTLead = store(new TH2D ( "GenRecoBJetpTLead", "Gen/Reco Matching", 400,0,400,400,0,400 ));

    h_HypBJetpTNLead = store(new TH1D ( "HypBJetpTNLead","NLeading pT BJet pT",400,0,400 ));
    h_RecoBJetpTNLead = store(new TH1D ( "RecoBJetpTNLead","NLeading pT BJet pT",400,0,400 ));
    h_VisGenBJetpTNLead = store(new TH1D ( "VisGenBJetpTNLead","NLeading pT BJet pT",400,0,400 ));
    h_GenRecoBJetpTNLead = store(new TH2D ( "GenRecoBJetpTNLead", "Gen/Reco Matching", 400,0,400,400,0,400 ));

    h_HypBJetEtaLead = store(new TH1D ( "HypBJetEtaLead","Leading pT BJet Eta",100,-5,5 ));
    h_RecoBJetEtaLead = store(new TH1D ( "RecoBJetEtaLead","Leading pT BJet Eta",100,-5,5 ));
    h_VisGenBJetEtaLead = store(new TH1D ( "VisGenBJetEtaLead","Leading pT BJet Eta",100,-5,5 ));
    h_GenRecoBJetEtaLead = store(new TH2D ( "GenRecoBJetEtaLead", "Gen/Reco Matching", 100,-5,5,100,-5,5 ));

    h_HypBJetEtaNLead = store(new TH1D ( "HypBJetEtaNLead","NLeading pT BJet Eta",100,-5,5 ));
    h_RecoBJetEtaNLead = store(new TH1D ( "RecoBJetEtaNLead","NLeading pT BJet Eta",100,-5,5 ));
    h_VisGenBJetEtaNLead = store(new TH1D ( "VisGenBJetEtaNLead","NLeading pT BJet Eta",100,-5,5 ));
    h_GenRecoBJetEtaNLead = store(new TH2D ( "GenRecoBJetEtaNLead", "Gen/Reco Matching", 100,-5,5,100,-5,5 ));

    /*
    //New plots from Carmen: Begin
    h_RecoLeadingJetpT   = store(new TH1D("RecoLeadingJetpT","pT of all Jets (HYP)",80,0,400));
    h_RecoLeadingJetEta  = store(new TH1D("RecoLeadingJetEta","#eta of all Jets (HYP)",100,-5,5));
    h_RecoNLeadingJetpT  = store(new TH1D("RecoNLeadingJetpT","pT of all Jets (HYP)",80,0,400));
    h_RecoNLeadingJetEta = store(new TH1D("RecoNLeadingJetEta","#eta of all Jets (HYP)",100,-5,5));

    h_GenRecoLeadingJetpT   = store(new TH2D("GenRecoLeadingJetpT","pT of all Jets (HYP)",80,0,400,80,0,400));
    h_GenRecoLeadingJetEta  = store(new TH2D("GenRecoLeadingJetEta","#eta of all Jets (HYP)",100,-5,5,100,-5,5));
    h_GenRecoNLeadingJetpT  = store(new TH2D("GenRecoNLeadingJetpT","pT of all Jets (HYP)",80,0,400,80,0,400));
    h_GenRecoNLeadingJetEta = store(new TH2D("GenRecoNLeadingJetEta","#eta of all Jets (HYP)",100,-5,5,100,-5,5));

    h_VisGenLeadingJetpT   = store(new TH1D("VisGenLeadingJetpT","pT of leading Jets (VisGEN)",80,0,400));
    h_VisGenLeadingJetEta  = store(new TH1D("VisGenLeadingJetEta","#eta of leading Jets (VisGEN)",100,-5,5));
    h_VisGenNLeadingJetpT  = store(new TH1D("VisGenNLeadingJetpT","pT of leading Jets (VisGEN)",80,0,400));
    h_VisGenNLeadingJetEta = store(new TH1D("VisGenNLeadingJetEta","#eta of leading Jets (VisGEN)",100,-5,5));

    h_HypLeadingJetpT   = store(new TH1D("HypLeadingJetpT","pT of leading Jets (HYP)",80,0,400));
    h_HypLeadingJetEta  = store(new TH1D("HypLeadingJetEta","#eta of leading Jets (HYP)",100,-5,5));
    h_HypNLeadingJetpT  = store(new TH1D("HypNLeadingJetpT","pT of leading Jets (HYP)",80,0,400));
    h_HypNLeadingJetEta = store(new TH1D("HypNLeadingJetEta","#eta of leading Jets (HYP)",100,-5,5));

    h_RecoExtraJetpT   = store(new TH1D("RecoExtraJetpT","pT of additional Jet (HYP)",80,0,400));
    h_RecoExtraJetEta  = store(new TH1D("RecoExtraJetEta","#eta of additional Jet (HYP)",100,-5,5));
    h_RecoExtraJetpT2  = store(new TH1D("RecoExtraJetpT2","pT of additional Jet (HYP)",80,0,400));
    h_RecoExtraJetEta2 = store(new TH1D("RecoExtraJetEta2","#eta of additional Jet (HYP)",100,-5,5));
    h_RecoExtraJetpT3  = store(new TH1D("RecoExtraJetpT3","pT of additional Jet (HYP)",80,0,400));
    h_RecoExtraJetEta3 = store(new TH1D("RecoExtraJetEta3","#eta of additional Jet (HYP)",100,-5,5));
    h_RecoExtraJetpT4  = store(new TH1D("RecoExtraJetpT4","pT of additional Jet (HYP)",80,0,400));
    h_RecoExtraJetEta4 = store(new TH1D("RecoExtraJetEta4","#eta of additional Jet (HYP)",100,-5,5));

    h_HypExtraJetpT   = store(new TH1D("HypExtraJetpT","pT of additional Jet",80,0,400));
    h_HypExtraJetEta  = store(new TH1D("HypExtraJetEta","#eta of additional Jet",100,-5,5));
    h_HypExtraJetpT2  = store(new TH1D("HypExtraJetpT2","pT of additional Jet",80,0,400));
    h_HypExtraJetEta2 = store(new TH1D("HypExtraJetEta2","#eta of additional Jet",100,-5,5));
    h_HypExtraJetpT3  = store(new TH1D("HypExtraJetpT3","pT of additional Jet",80,0,400));
    h_HypExtraJetEta3 = store(new TH1D("HypExtraJetEta3","#eta of additional Jet",100,-5,5));
    h_HypExtraJetpT4  = store(new TH1D("HypExtraJetpT4","pT of additional Jet",80,0,400));
    h_HypExtraJetEta4 = store(new TH1D("HypExtraJetEta4","#eta of additional Jet",100,-5,5));

    h_VisGenExtraJetpT   = store(new TH1D("VisGenExtraJetpT","pT of gen additional Jet",80,0,400));
    h_VisGenExtraJetEta  = store(new TH1D("VisGenExtraJetEta","#eta of gen additional Jet",100,-5,5));
    h_VisGenExtraJetpT2  = store(new TH1D("VisGenExtraJetpT2","pT of gen additional Jet",80,0,400));
    h_VisGenExtraJetEta2 = store(new TH1D("VisGenExtraJetEta2","#eta of gen additional Jet",100,-5,5));
    h_VisGenExtraJetpT3  = store(new TH1D("VisGenExtraJetpT3","pT of gen additional Jet",80,0,400));
    h_VisGenExtraJetEta3 = store(new TH1D("VisGenExtraJetEta3","#eta of gen additional Jet",100,-5,5));
    h_VisGenExtraJetpT4  = store(new TH1D("VisGenExtraJetpT4","pT of gen additional Jet",80,0,400));
    h_VisGenExtraJetEta4 = store(new TH1D("VisGenExtraJetEta4","#eta of gen additional Jet",100,-5,5));

    h_GenRecoExtraJetpT   = store(new TH2D("GenRecoExtraJetpT","Gen/Reco pT of additional Jet",80,0,400,80,0,400));
    h_GenRecoExtraJetEta  = store(new TH2D("GenRecoExtraJetEta","Gen/Reco #eta of additional Jet",100,-5,5,100,-5,5));
    h_GenRecoExtraJetpT2  = store(new TH2D("GenRecoExtraJetpT2","Gen/Reco pT of additional Jet",80,0,400,80,0,400));
    h_GenRecoExtraJetEta2 = store(new TH2D("GenRecoExtraJetEta2","Gen/Reco #eta of additional Jet",100,-5,5,100,-5,5));
    h_GenRecoExtraJetpT3  = store(new TH2D("GenRecoExtraJetpT3","Gen/Reco pT of additional Jet",80,0,400,80,0,400));
    h_GenRecoExtraJetEta3 = store(new TH2D("GenRecoExtraJetEta3","Gen/Reco #eta of additional Jet",100,-5,5,100,-5,5));
    h_GenRecoExtraJetpT4  = store(new TH2D("GenRecoExtraJetpT4","Gen/Reco pT of additional Jet",80,0,400,80,0,400));
    h_GenRecoExtraJetEta4 = store(new TH2D("GenRecoExtraJetEta4","Gen/Reco #eta of additional Jet",100,-5,5,100,-5,5));

    h_GenRecoJetMultpt40 = store(new TH2D("GenRecoJetMultpt40", "Gen/Reco Matching",10,-0.5,9.5,10,-0.5,9.5));
    h_RecoJetMultpt40    = store(new TH1D("RecoJetMultpt40", "Jet Multiplicity (HYP)",10,-0.5,9.5));
    h_HypJetMultpt40     = store(new TH1D("HypJetMultpt40", "Jet Multiplicity (HYP)",10,-0.5,9.5));
    h_GenJetMultpt40     = store(new TH1D("GenJetMultpt40", "Jet Multiplicty (GEN)",10,-0.5,9.5));
    h_VisGenJetMultpt40  = store(new TH1D("VisGenJetMultpt40", "Jet Multiplicty (VisGEN)",10,-0.5,9.5));

    h_GenRecoJetMultpt60 = store(new TH2D("GenRecoJetMultpt60", "Gen/Reco Matching",10,-0.5,9.5,10,-0.5,9.5));
    h_RecoJetMultpt60    = store(new TH1D("RecoJetMultpt60", "Jet Multiplicity (HYP)",10,-0.5,9.5));
    h_HypJetMultpt60     = store(new TH1D("HypJetMultpt60", "Jet Multiplicity (HYP)",10,-0.5,9.5));
    h_GenJetMultpt60     = store(new TH1D("GenJetMultpt60", "Jet Multiplicty (GEN)",10,-0.5,9.5));
    h_VisGenJetMultpt60  = store(new TH1D("VisGenJetMultpt60", "Jet Multiplicty (VisGEN)",10,-0.5,9.5));
    //New plots from Carmen: End
*/
    
    h_ClosureTotalWeight = store(new TH1D("ClosureTotalWeight", "Total Weights from closure test",1,0,2));
    h_PDFTotalWeight = store(new TH1D("PDFTotalWeight", "PDF Weights",1,0,2));

    CreateBinnedControlPlots(h_HypToppT, h_LeptonpT);
    CreateBinnedControlPlots(h_HypToppT, h_LeptonEta);
    CreateBinnedControlPlots(h_HypToppT, h_MET);
    CreateBinnedControlPlots(h_HypToppT, h_diLepMassFull);
    
    CreateBinnedControlPlots(h_HypTopRapidity, h_LeptonpT);
    CreateBinnedControlPlots(h_HypTopRapidity, h_LeptonEta);
    CreateBinnedControlPlots(h_HypTopRapidity, h_MET);
    CreateBinnedControlPlots(h_HypTopRapidity, h_diLepMassFull);
    
    
    
    h_AllLeptonpT_step0 = store(new TH1D("AllLeptonpT_step0", "p_{T} of all leptons before trigger", 80, 0, 400));
    h_AllLeptonEta_step0 = store(new TH1D("AllLeptonEta_step0", "#eta of all leptons before trigger", 20, -2.4, 2.4));
    h_LeptonpT_step0 = store(new TH1D("LeptonpT_step0", "p_{T} of  leptons before trigger", 80, 0, 400));
    h_LeptonEta_step0 = store(new TH1D("LeptonEta_step0", "#eta of  leptons before trigger", 20, -2.4, 2.4));
    h_LeptonMult_step0 = store(new TH1D("LeptonMult_step0", "Number of all leptons before trigger", 20, -0.5, 20.5));
    h_AllJetspT_step0 = store(new TH1D("AllJetpT_step0", "p_{T} of all jets before trigger", 80, 0, 400));
    h_AllJetsEta_step0 = store(new TH1D("AllJetEta_step0", "#eta of all jets before trigger", 20, -2.4, 2.4));
    h_JetsMult_step0 = store(new TH1D("JetsMult_step0", "Number of the jets before trigger", 20, -0.5, 20.5));
    h_BJetsMult_step0 = store(new TH1D("BJetsMult_step0", "Number of the jets before trigger", 20, -0.5, 20.5));
    
    h_AllLeptonpT_step1 = store(new TH1D("AllLeptonpT_step1", "p_{T} of all leptons before 2 lepton", 80, 0, 400));
    h_AllLeptonEta_step1 = store(new TH1D("AllLeptonEta_step1", "#eta of all leptons before 2 lepton", 20, -2.4, 2.4));
    h_LeptonpT_step1 = store(new TH1D("LeptonpT_step1", "p_{T} of  leptons before 2 lepton", 80, 0, 400));
    h_LeptonEta_step1 = store(new TH1D("LeptonEta_step1", "#eta of  leptons before 2 lepton", 20, -2.4, 2.4));
    h_LeptonMult_step1 = store(new TH1D("LeptonMult_step1", "Number of all leptons before 2 lepton", 20, -0.5, 20.5));
    h_AllJetspT_step1 = store(new TH1D("AllJetpT_step1", "p_{T} of all jets before 2 lepton", 80, 0, 400));
    h_AllJetsEta_step1 = store(new TH1D("AllJetEta_step1", "#eta of all jets before 2 lepton", 20, -2.4, 2.4));
    h_JetspT_step1 = store(new TH1D("JetpT_step1", "p_{T} of  jets before 2 lepton", 80, 0, 400));
    h_JetsEta_step1 = store(new TH1D("JetEta_step1", "#eta of  jets before 2 lepton", 20, -2.4, 2.4));
    h_JetsMult_step1 = store(new TH1D("JetsMult_step1", "Number of the jets before 2 lepton", 20, -0.5, 20.5));
    h_BJetsMult_step1 = store(new TH1D("BJetsMult_step1", "Number of the jets before 2 lepton", 20, -0.5, 20.5));
    
    h_AllLeptonpT_step2 = store(new TH1D("AllLeptonpT_step2", "p_{T} of all leptons before m_{ll}>20 cut", 80, 0, 400));
    h_AllLeptonEta_step2 = store(new TH1D("AllLeptonEta_step2", "#eta of all leptons before m_{ll}>20 cut", 20, -2.4, 2.4));
    h_LeptonpT_step2 = store(new TH1D("LeptonpT_step2", "p_{T} of  leptons before m_{ll}>20 cut", 80, 0, 400));
    h_LeptonEta_step2 = store(new TH1D("LeptonEta_step2", "#eta of  leptons before m_{ll}>20 cut", 20, -2.4, 2.4));
    h_LeptonMult_step2 = store(new TH1D("LeptonMult_step2", "Number of all leptons before m_{ll}>20 cut", 20, -0.5, 20.5));
    h_AllJetspT_step2 = store(new TH1D("AllJetpT_step2", "p_{T} of all jets before m_{ll}>20 cut", 80, 0, 400));
    h_AllJetsEta_step2 = store(new TH1D("AllJetEta_step2", "#eta of all jets before m_{ll}>20 cut", 20, -2.4, 2.4));
    h_JetspT_step2 = store(new TH1D("JetpT_step2", "p_{T} of  jets before m_{ll}>20 cut", 80, 0, 400));
    h_JetsEta_step2 = store(new TH1D("JetEta_step2", "#eta of  jets before m_{ll}>20 cut", 20, -2.4, 2.4));
    h_JetsMult_step2 = store(new TH1D("JetsMult_step2", "Number of the jets before m_{ll}>20 cut", 20, -0.5, 20.5));
    h_BJetsMult_step2 = store(new TH1D("BJetsMult_step2", "Number of the jets before m_{ll}>20 cut", 20, -0.5, 20.5));
    
    h_AllLeptonpT_step3 = store(new TH1D("AllLeptonpT_step3", "p_{T} of all leptons before Zpeakcut", 80, 0, 400));
    h_AllLeptonEta_step3 = store(new TH1D("AllLeptonEta_step3", "#eta of all leptons before Zpeakcut", 20, -2.4, 2.4));
    h_LeptonpT_step3 = store(new TH1D("LeptonpT_step3", "p_{T} of  leptons before Zpeakcut", 80, 0, 400));
    h_LeptonEta_step3 = store(new TH1D("LeptonEta_step3", "#eta of  leptons before Zpeakcut", 20, -2.4, 2.4));
    h_LeptonMult_step3 = store(new TH1D("LeptonMult_step3", "Number of all leptons before Zpeakcut", 20, -0.5, 20.5));
    h_AllJetspT_step3 = store(new TH1D("AllJetpT_step3", "p_{T} of all jets before Zpeakcut", 80, 0, 400));
    h_AllJetsEta_step3 = store(new TH1D("AllJetEta_step3", "#eta of all jets before Zpeakcut", 20, -2.4, 2.4));
    h_JetspT_step3 = store(new TH1D("JetpT_step3", "p_{T} of  jets before Zpeakcut", 80, 0, 400));
    h_JetsEta_step3 = store(new TH1D("JetEta_step3", "#eta of  jets before Zpeakcut", 20, -2.4, 2.4));
    h_JetsMult_step3 = store(new TH1D("JetsMult_step3", "Number of the jets before Zpeakcut", 20, -0.5, 20.5));
    h_BJetsMult_step3 = store(new TH1D("BJetsMult_step3", "Number of the jets before Zpeakcut", 20, -0.5, 20.5));
    
    h_AllLeptonpT_step4 = store(new TH1D("AllLeptonpT_step4", "p_{T} of all leptons before 2jets", 80, 0, 400));
    h_AllLeptonEta_step4 = store(new TH1D("AllLeptonEta_step4", "#eta of all leptons before 2jets", 20, -2.4, 2.4));
    h_LeptonpT_step4 = store(new TH1D("LeptonpT_step4", "p_{T} of  leptons before 2jets", 80, 0, 400));
    h_LeptonEta_step4 = store(new TH1D("LeptonEta_step4", "#eta of  leptons before 2jets", 20, -2.4, 2.4));
    h_LeptonMult_step4 = store(new TH1D("LeptonMult_step4", "Number of all leptons before 2jets", 20, -0.5, 20.5));
    h_AllJetspT_step4 = store(new TH1D("AllJetpT_step4", "p_{T} of all jets before 2jets", 80, 0, 400));
    h_AllJetsEta_step4 = store(new TH1D("AllJetEta_step4", "#eta of all jets before 2jets", 20, -2.4, 2.4));
    h_JetspT_step4 = store(new TH1D("JetpT_step4", "p_{T} of  jets before 2jets", 80, 0, 400));
    h_JetsEta_step4 = store(new TH1D("JetEta_step4", "#eta of  jets before 2jets", 20, -2.4, 2.4));
    h_JetsMult_step4 = store(new TH1D("JetsMult_step4", "Number of the jets before 2jets", 20, -0.5, 20.5));
    h_BJetsMult_step4 = store(new TH1D("BJetsMult_step4", "Number of the jets before 2jets", 20, -0.5, 20.5));
    
    h_AllLeptonpT_step5 = store(new TH1D("AllLeptonpT_step5", "p_{T} of all leptons before MET", 80, 0, 400));
    h_AllLeptonEta_step5 = store(new TH1D("AllLeptonEta_step5", "#eta of all leptons before MET", 20, -2.4, 2.4));
    h_LeptonpT_step5 = store(new TH1D("LeptonpT_step5", "p_{T} of  leptons before MET", 80, 0, 400));
    h_LeptonEta_step5 = store(new TH1D("LeptonEta_step5", "#eta of  leptons before MET", 20, -2.4, 2.4));
    h_LeptonMult_step5 = store(new TH1D("LeptonMult_step5", "Number of all leptons before MET", 20, -0.5, 20.5));
    h_AllJetspT_step5 = store(new TH1D("AllJetpT_step5", "p_{T} of all jets before MET", 80, 0, 400));
    h_AllJetsEta_step5 = store(new TH1D("AllJetEta_step5", "#eta of all jets before MET", 20, -2.4, 2.4));
    h_JetspT_step5 = store(new TH1D("JetpT_step5", "p_{T} of  jets before MET", 80, 0, 400));
    h_JetsEta_step5 = store(new TH1D("JetEta_step5", "#eta of  jets before MET", 20, -2.4, 2.4));
    h_JetsMult_step5 = store(new TH1D("JetsMult_step5", "Number of the jets before MET", 20, -0.5, 20.5));
    h_BJetsMult_step5 = store(new TH1D("BJetsMult_step5", "Number of the jets before MET", 20, -0.5, 20.5));
    
    h_AllLeptonpT_step6 = store(new TH1D("AllLeptonpT_step6", "p_{T} of all leptons before 1b-tag", 80, 0, 400));
    h_AllLeptonEta_step6 = store(new TH1D("AllLeptonEta_step6", "#eta of all leptons before 1b-tag", 20, -2.4, 2.4));
    h_LeptonpT_step6 = store(new TH1D("LeptonpT_step6", "p_{T} of  leptons before 1b-tag", 80, 0, 400));
    h_LeptonEta_step6 = store(new TH1D("LeptonEta_step6", "#eta of  leptons before 1b-tag", 20, -2.4, 2.4));
    h_LeptonMult_step6 = store(new TH1D("LeptonMult_step6", "Number of all leptons before 1b-tag", 20, -0.5, 20.5));
    h_AllJetspT_step6 = store(new TH1D("AllJetpT_step6", "p_{T} of all jets before 1b-tag", 80, 0, 400));
    h_AllJetsEta_step6 = store(new TH1D("AllJetEta_step6", "#eta of all jets before 1b-tag", 20, -2.4, 2.4));
    h_JetspT_step6 = store(new TH1D("JetpT_step6", "p_{T} of  jets before 1b-tag", 80, 0, 400));
    h_JetsEta_step6 = store(new TH1D("JetEta_step6", "#eta of  jets before 1b-tag", 20, -2.4, 2.4));
    h_JetsMult_step6 = store(new TH1D("JetsMult_step6", "Number of the jets before 1b-tag", 20, -0.5, 20.5));
    h_BJetsMult_step6 = store(new TH1D("BJetsMult_step6", "Number of the jets before 1b-tag", 20, -0.5, 20.5));
    
    h_AllLeptonpT_step7 = store(new TH1D("AllLeptonpT_step7", "p_{T} of all leptons before kinReco", 80, 0, 400));
    h_AllLeptonEta_step7 = store(new TH1D("AllLeptonEta_step7", "#eta of all leptons before kinReco", 20, -2.4, 2.4));
    h_LeptonpT_step7 = store(new TH1D("LeptonpT_step7", "p_{T} of  leptons before kinReco", 80, 0, 400));
    h_LeptonEta_step7 = store(new TH1D("LeptonEta_step7", "#eta of  leptons before kinReco", 20, -2.4, 2.4));
    h_LeptonMult_step7 = store(new TH1D("LeptonMult_step7", "Number of all leptons before kinReco", 20, -0.5, 20.5));
    h_AllJetspT_step7 = store(new TH1D("AllJetpT_step7", "p_{T} of all jets before kinReco", 80, 0, 400));
    h_AllJetsEta_step7 = store(new TH1D("AllJetEta_step7", "#eta of all jets before kinReco", 20, -2.4, 2.4));
    h_JetspT_step7 = store(new TH1D("JetpT_step7", "p_{T} of  jets before kinReco", 80, 0, 400));
    h_JetsEta_step7 = store(new TH1D("JetEta_step7", "#eta of  jets before kinReco", 20, -2.4, 2.4));
    h_JetsMult_step7 = store(new TH1D("JetsMult_step7", "Number of the jets before kinReco", 20, -0.5, 20.5));
    h_BJetsMult_step7 = store(new TH1D("BJetsMult_step7", "Number of the jets before kinReco", 20, -0.5, 20.5));
    
    h_AllLeptonpT_step8 = store(new TH1D("AllLeptonpT_step8", "p_{T} of the leptons after kinReco", 80, 0, 400));
    h_AllLeptonEta_step8 = store(new TH1D("AllLeptonEta_step8", "#eta of the leptons after kinReco", 20, -2.4, 2.4));
    h_LeptonpT_step8 = store(new TH1D("LeptonpT_step8", "p_{T} of  leptons after kinReco", 80, 0, 400));
    h_LeptonEta_step8 = store(new TH1D("LeptonEta_step8", "#eta of  leptons after kinReco", 20, -2.4, 2.4));
    h_LeptonMult_step8 = store(new TH1D("LeptonMult_step8", "Number of the leptons after kinReco", 20, -0.5, 20.5));
    h_AllJetspT_step8 = store(new TH1D("AllJetpT_step8", "p_{T} of the jets after kinReco", 80, 0, 400));
    h_AllJetsEta_step8 = store(new TH1D("AllJetEta_step8", "#eta of the jets after kinReco", 20, -2.4, 2.4));
    h_JetspT_step8 = store(new TH1D("JetpT_step8", "p_{T} of jets after kinReco", 80, 0, 400));
    h_JetsEta_step8 = store(new TH1D("JetEta_step8", "#eta of jets after kinReco", 20, -2.4, 2.4));
    h_JetsMult_step8 = store(new TH1D("JetsMult_step8", "Number of the jets after kinReco", 20, -0.5, 20.5));
    h_BJetsMult_step8 = store(new TH1D("BJetsMult_step8", "Number of the jets after kinReco", 20, -0.5, 20.5));
    
    
    //btagSF
    const int PtMax = 11;
    const int EtaMax = 5;
    Double_t ptbins[PtMax+1] = {20.,30.,40.,50.,60.,70.,80.,100.,120.,160.,210.,800.};
    Double_t etabins[EtaMax+1] = {0.0,0.5,1.0,1.5,2.0,2.4};
    
    h_bjets = store(new TH2D("bjets2D", "unTagged Bjets", PtMax, ptbins, EtaMax, etabins));              h_bjets->Sumw2();
    h_btaggedjets = store(new TH2D("bjetsTagged2D", "Tagged Bjets", PtMax, ptbins, EtaMax, etabins));    h_btaggedjets->Sumw2();
    h_cjets = store(new TH2D("cjets2D", "unTagged Cjets", PtMax, ptbins, EtaMax, etabins));              h_cjets->Sumw2();
    h_ctaggedjets = store(new TH2D("cjetsTagged2D", "Tagged Cjets", PtMax, ptbins, EtaMax, etabins));    h_ctaggedjets->Sumw2();
    h_ljets = store(new TH2D("ljets2D", "unTagged Ljets", PtMax, ptbins, EtaMax, etabins));              h_ljets->Sumw2();
    h_ltaggedjets = store(new TH2D("ljetsTagged2D", "Tagged Ljets", PtMax, ptbins, EtaMax, etabins));    h_ltaggedjets->Sumw2();
    
    h_PUSF = store(new TH1D("PUSF", "PU SF per event", 200, 0.5, 1.5));
    h_TrigSF = store(new TH1D("TrigSF", "Trigger SF per event", 200, 0.5, 1.5));
    h_LepSF = store(new TH1D("LepSF", "Lep. Id and Isol. SF per event", 200, 0.75, 1.25));
    h_BTagSF = store(new TH1D("BTagSF", "BTagging SF per event", 200 , 0.95, 1.15 ));
    h_BTagSF->Sumw2();
    h_KinRecoSF = store(new TH1D("KinRecoSF", "Kinematic Reco. SF per event", 200, 0.5, 1.5));
    h_EventWeight = store(new TH1D("EventWeight", "Event SF", 600, 0, 3));

}

void TopAnalysis::SlaveTerminate()
{
    AnalysisBase::SlaveTerminate();
}

Bool_t TopAnalysis::Process ( Long64_t entry )
{    
    if ( ++EventCounter_ % 100000 == 0 ) std::cout << "Event Counter: " << EventCounter_ << std::endl;
    
    
    //do we have a DY true level cut?
    if (checkZDecayMode_ && !checkZDecayMode_(entry)) return kTRUE;
    
    if (isTtbarPlusTauSample_ || correctMadgraphBR_) GetTopDecayModeEntry(entry); 
    //decayMode contains the decay of the top (*10) + the decay of the antitop
    //1=hadron, 2=e, 3=mu, 4=tau->hadron, 5=tau->e, 6=tau->mu
    //i.e. 23 == top decays to e, tbar decays to mu
    if (isTtbarPlusTauSample_) {
        bool isViaTau = topDecayMode_ > 40 || ( topDecayMode_ % 10 > 4 );
        bool isCorrectChannel = false;
        switch (channelPdgIdProduct_) {
            case -11*13: isCorrectChannel = topDecayMode_ == 23 || topDecayMode_ == 32 //emu prompt
                            || topDecayMode_ == 53 || topDecayMode_ == 35 //e via tau, mu prompt
                            || topDecayMode_ == 26 || topDecayMode_ == 62 //e prompt, mu via tau
                            || topDecayMode_ == 56 || topDecayMode_ == 65; //both via tau
                            break;
            case -11*11: isCorrectChannel = topDecayMode_ == 22  //ee prompt
                            || topDecayMode_ == 52 || topDecayMode_ == 25 //e prompt, e via tau
                            || topDecayMode_ == 55; break; //both via tau
            case -13*13: isCorrectChannel = topDecayMode_ == 33
                            || topDecayMode_ == 36 || topDecayMode_ == 63
                            || topDecayMode_ == 66; break;
            default: std::cerr << "Invalid channel! Product = " << channelPdgIdProduct_ << "\n";
        };
        bool isBackgroundInSignalSample = !isCorrectChannel || isViaTau;
        if (runViaTau_ != isBackgroundInSignalSample) return kTRUE;
    }

    GetRecoBranches(entry);
    //We must correct for the madGraph branching fraction being 1/9 for dileptons (PDG average is .108)
    if ( correctMadgraphBR_ ) {
        if ( topDecayMode_ == 11 ) { //all hadronic decay
            weightGenerator_ *= (0.676*1.5) * (0.676*1.5);
        } else if ( topDecayMode_< 20 || ( topDecayMode_ % 10 == 1) ) { //semileptonic Decay
            weightGenerator_ *= (0.108*9) * (0.676*1.5);
        } else {//dileptonic decay (including taus!)
            weightGenerator_ *= (0.108*9) * (0.108*9);
        }
    }
    
    if (pdf_no_ >= 0) {
        GetPDFEntry(entry);
        double pdfWeight = weightPDF_->at(pdf_no_); //vector is 0 based
//         pdfWeight = 10;
        weightGenerator_ *= pdfWeight;
        h_PDFTotalWeight->Fill(1, pdfWeight);
    }
    
    //count events here, where no more taus are available
    if (doClosureTest_) {
        static int closureTestEventCounter = 0;
        if (++closureTestEventCounter > closureMaxEvents_) return kTRUE;
        weightGenerator_ = 1;
    }
    
    //Jet Energy Resolution/Scale?
    if (doJesJer_) applyJER_JES();

    // apply all jet cuts
    cleanJetCollection(JETPTCUT, JETETACUT);

    double weightPU = 1;
    if (isMC_) { 
        //still have lumi weights for old plotterclass
        //weightGenerator *= lumiWeight;        
        if (pureweighter_) {
            weightPU = pureweighter_->getPUweight(vertMultiTrue_);
        }
    }
        
    int BHadronIndex=-1;
    int AntiBHadronIndex=-1;
    
    if (isSignal_) {
        GetSignalBranches(entry);

        std::vector<size_t> idx_leadbHadJet;
        std::vector<size_t> idx_nleadbHadJet;
        //To avoid recopying may code lines, we select HERE the BHadron JET Indices to cut on.

        //time to choose which genJet we actually want

        idx_leadbHadJet.insert ( idx_leadbHadJet.begin(), 4, -1 );
        idx_nleadbHadJet.insert ( idx_nleadbHadJet.begin(), 4, -1 );
        /*
          idx_bHadJet will have 4 jet indices
          [0] is the highest pT jet with a B-Hadron
          [1] is the highest pT jet with a B-Hadron also matched to a top quark
          [2] highest pT jet of those matched closest (in DeltaR) to the B-Hadron
          [3] highest pT jet of those matched closest (in DeltaR) to the B-Hadron also matched to a top quark
        */

        bool LeadBHadhighpTjet = false;
        bool LeadBHadhighpTjetfromtop = false;
        bool NLeadBHadhighpTjet = false;
        bool NLeadBHadhighpTjetfromtop = false;

        size_t hadron_index = std::numeric_limits<size_t>::max();
        size_t antihadron_index = std::numeric_limits<size_t>::max();
        size_t hadrontop_index = std::numeric_limits<size_t>::max();
        size_t antihadrontop_index = std::numeric_limits<size_t>::max();
        
        //Case 1: highest pT genJet matched to a BHadron
        //need to remove jets from the genJetCollection which are below the JETPTCUT
        //while (allGenJets->size() > 0 && allGenJets->back().Pt() < JETPTCUT) allGenJets->pop_back();
        //while (jet->size() > 0 && jet->back().Pt() < JETPTCUT) jet->pop_back();
        
        for ( size_t genJet = 0; 
              genJet < allGenJets_->size() && allGenJets_->at(genJet).pt() >= JETPTCUT; 
              ++genJet ) 
        {
            for ( size_t bHadron=0; bHadron < BHadrons_->size(); bHadron++ ) {
                if ( (*BHadronVsJet_)[genJet*BHadrons_->size()+bHadron]==1 
                     && (!LeadBHadhighpTjet || !LeadBHadhighpTjetfromtop || !NLeadBHadhighpTjet || !NLeadBHadhighpTjetfromtop) )
                {
                    if ( LeadBHadhighpTjet==false ) {
                        idx_leadbHadJet[0] = genJet;
                        LeadBHadhighpTjet = true;
                        hadron_index = bHadron;
                        if ( ( *BHadronFromTopB_ ) [bHadron] == true ) {
                            idx_leadbHadJet[1] = genJet;
                            LeadBHadhighpTjetfromtop = true;
                            hadrontop_index = bHadron;
                        }
                    } else if ( LeadBHadhighpTjetfromtop == false ) {
                        if ( ( *BHadronFromTopB_ ) [bHadron] == true ) {
                            idx_leadbHadJet[1] = genJet;
                            LeadBHadhighpTjetfromtop = true;
                            hadrontop_index = bHadron;
                        }
                    } else if ( NLeadBHadhighpTjet==false && bHadron!=hadron_index && idx_leadbHadJet[0] != genJet ) {
                        idx_nleadbHadJet[0] = genJet;
                        NLeadBHadhighpTjet = true;
                        if ( ( *BHadronFromTopB_ ) [bHadron] == true && bHadron!=hadrontop_index && idx_leadbHadJet[1] != genJet ) {
                            idx_nleadbHadJet[1] = genJet;
                            NLeadBHadhighpTjetfromtop = true;
                        }
                    } else if ( NLeadBHadhighpTjetfromtop == false && bHadron!=hadrontop_index && idx_leadbHadJet[1] != genJet ) {
                        if ( ( *BHadronFromTopB_ ) [bHadron] == true ) {
                            idx_nleadbHadJet[1] = genJet;
                            LeadBHadhighpTjetfromtop = true;
                        }
                    }//series of if statements to find highest pT jet
                }
            }
            for ( size_t antibHadron=0; antibHadron < AntiBHadrons_->size(); antibHadron++ ) {
                if ( (*AntiBHadronVsJet_)[genJet*AntiBHadrons_->size()+antibHadron]==1 
                    && ( LeadBHadhighpTjet ==false || LeadBHadhighpTjetfromtop == false || NLeadBHadhighpTjet ==false || NLeadBHadhighpTjetfromtop == false ) && idx_leadbHadJet[0] != genJet ) 
                {
                    if ( LeadBHadhighpTjet==false ) {
                        idx_leadbHadJet[0] = genJet;
                        LeadBHadhighpTjet = true;
                        antihadron_index = antibHadron;
                        if ( ( *AntiBHadronFromTopB_ ) [antibHadron] == true ) {
                            idx_leadbHadJet[1] = genJet;
                            LeadBHadhighpTjetfromtop = true;
                            antihadrontop_index = antibHadron;
                        }
                    } else if ( LeadBHadhighpTjetfromtop == false ) {
                        if ( ( *AntiBHadronFromTopB_ ) [antibHadron] == true ) {
                            idx_leadbHadJet[1] = genJet;
                            LeadBHadhighpTjetfromtop = true;
                            antihadrontop_index = antibHadron;
                        }
                    } else if ( NLeadBHadhighpTjet==false && antibHadron!=antihadron_index && idx_leadbHadJet[0] != genJet ) {
                        idx_nleadbHadJet[0] = genJet;
                        NLeadBHadhighpTjet = true;
                        if ( ( *AntiBHadronFromTopB_ ) [antibHadron] == true && antibHadron!=antihadrontop_index && idx_leadbHadJet[1] != genJet ) {
                            idx_nleadbHadJet[1] = genJet;
                            NLeadBHadhighpTjetfromtop = true;
                        }
                    } else if ( NLeadBHadhighpTjetfromtop == false && antibHadron!=antihadrontop_index && idx_leadbHadJet[1] != genJet ) {
                        if ( ( *AntiBHadronFromTopB_ ) [antibHadron] == true ) {
                            idx_nleadbHadJet[1] = genJet;
                            LeadBHadhighpTjetfromtop = true;
                        }
                    }
                }
            }
        }
 
        //Case 2: highest pT genJets matched closest to a BHadron
        //BHadJetIndex: vector containing the GetJet indices matched, in DeltaR, to a BHadron. Starting from the highest pT jet.
        if ( BHadJetIndex_->size() != 0 ) idx_leadbHadJet[2] = ( *BHadJetIndex_ ) [0];
        for ( size_t i=0; i < BHadJetIndex_->size(); ++i ) {
            //Only search for those jets matched in DeltaR with a BHadron
            for ( size_t j=0; j<BHadrons_->size() ; ++j ) {
                if ( ( *BHadronVsJet_ ) [ ( ( *BHadJetIndex_ ) [i] ) * BHadrons_->size()+j] == 1 && ( *BHadronFromTopB_ ) [j] == true ) {
                    idx_leadbHadJet[3] = ( *BHadJetIndex_ ) [i];
                }
            }
        }

        //AntiBHadJetIndex: vector containing the GetJet indices matched, in DeltaR, to a AntiBHadron. Starting from the highest pT jet.
        if ( AntiBHadJetIndex_->size() != 0 ) idx_nleadbHadJet[2] = ( *AntiBHadJetIndex_ ) [0];
        for ( size_t i=0; i < AntiBHadJetIndex_->size(); ++i ) {
            //Only search for those jets matched in DeltaR with a AntiBHadron
            for ( size_t j=0; j < AntiBHadrons_->size() ; ++j ) {
                //if ((*AntiBHadronVsJet)[i*AntiBHadrons_+j] == 1 && (*AntiBHadronFromTopB)[j] == true) {idx_antibHadJet[3] = (*AntiBHadJetIndex)[i];}
                if ( ( *AntiBHadronVsJet_ ) [ ( ( *AntiBHadJetIndex_ ) [i] ) * AntiBHadrons_->size()+j] == 1 && ( *AntiBHadronFromTopB_ ) [j] == true ) {
                    idx_nleadbHadJet[3] = ( *AntiBHadJetIndex_ ) [i];
                }
            }
        }


//     //To avoid recopying many code lines, we select HERE the BHadron JET Indices to cut on.
//     int BHadronIndex;
//     int AntiBHadronIndex;
        //Case 1A: highest pT genJet matched to a BHadron
        BHadronIndex = idx_leadbHadJet[0];
        AntiBHadronIndex = idx_nleadbHadJet[0];
//
        //   //Case 1B: highest pT genJet matched to a BHadron from Top
        //BHadronIndex = idx_bHadJet[1];
        //AntiBHadronIndex = idx_antibHadJet[1];

        //   //Case 2A: highest pT genJets matched closest to a BHadron
        //BHadronIndex = idx_bHadJet[2];
        //AntiBHadronIndex = idx_antibHadJet[2];
        //
        //   //Case 2B: highest pT genJets matched closest to a BHadron from Top
        //    BHadronIndex = idx_leadbHadJet[3];
        //AntiBHadronIndex = idx_nleadbHadJet[3];


    }

    
    double BtagWP = 0.244; //CSV Loose working point
    std::vector<int> BJetIndex;
    for ( auto it = jetBTagCSV_->begin(); it<jetBTagCSV_->end(); it++ ) {
        if ( *it > BtagWP) {
            //BJetIndex.push_back ( *it );
            BJetIndex.push_back((it-jetBTagCSV_->begin())); //change asked by Tyler
        }
    }
    const int NumberOfBJets = BJetIndex.size();

    LV LeadGenTop, NLeadGenTop;
    LV LeadGenLepton, NLeadGenLepton;
    LV LeadGenBJet, NLeadGenBJet;
    double genHT = -1;
    
    
    if ( isSignal_ ) {
        if (doClosureTest_) weightGenerator_ *= calculateClosureTestWeight();
        double trueLevelWeight = weightGenerator_ * weightPU;
        h_GenAll->Fill(GenTop_->M(), trueLevelWeight);
        
        //Begin: Select & Fill histograms with Leading pT and 2nd Leading pT: Lepton and BJet
        orderLVByPt(LeadGenLepton, NLeadGenLepton, *GenLepton_, *GenAntiLepton_);
        
        if (BHadronIndex != -1 && AntiBHadronIndex != -1) {
            orderLVByPt(LeadGenBJet, NLeadGenBJet, 
                        allGenJets_->at(BHadronIndex), allGenJets_->at(AntiBHadronIndex));
        }
        
        if ( GenLepton_->pt() > 20 && GenAntiLepton_->pt() > 20 
              && abs( GenLepton_->eta() ) < 2.4 && abs ( GenAntiLepton_->eta() ) < 2.4 ) {
            //if (LVGenBQuark.Pt()>JETPTCUT && LVGenAntiBQuark.Pt()>JETPTCUT && abs(LVGenBQuark.Eta())<2.4 && abs(LVGenAntiBQuark.Eta())<2.4){
            if ( BHadronIndex != -1 && AntiBHadronIndex != -1 ) {
                if ( allGenJets_->at(BHadronIndex).pt() > JETPTCUT &&
                    abs ( allGenJets_->at(BHadronIndex).eta() ) < 2.4 &&
                    allGenJets_->at(AntiBHadronIndex).pt() > JETPTCUT &&
                    abs ( allGenJets_->at(AntiBHadronIndex).Eta() ) < 2.4 )
                {

                    h_VisGenAll->Fill(GenTop_->M(), trueLevelWeight);

                    h_VisGenLLBarpT->Fill(( *GenLepton_ + *GenAntiLepton_ ).Pt(), trueLevelWeight );
                    h_VisGenLLBarMass->Fill(( *GenLepton_ + *GenAntiLepton_ ).M(), trueLevelWeight );

                    h_VisGenLeptonpT->Fill(GenLepton_->pt(), trueLevelWeight );
                    h_VisGenAntiLeptonpT->Fill(GenAntiLepton_->Pt(), trueLevelWeight );

                    h_VisGenLeptonEta->Fill(GenLepton_->Eta(), trueLevelWeight );
                    h_VisGenAntiLeptonEta->Fill(GenAntiLepton_->Eta(), trueLevelWeight );

                    h_VisGenBJetEta->Fill(allGenJets_->at(BHadronIndex).Eta(), trueLevelWeight );
                    h_VisGenAntiBJetEta->Fill(allGenJets_->at(AntiBHadronIndex).Eta(), trueLevelWeight );
                    h_VisGenBJetRapidity->Fill(allGenJets_->at(BHadronIndex).Rapidity(), trueLevelWeight );
                    h_VisGenAntiBJetRapidity->Fill(allGenJets_->at(AntiBHadronIndex).Rapidity(), trueLevelWeight );
                    h_VisGenBJetpT->Fill(allGenJets_->at(BHadronIndex).Pt(), trueLevelWeight );
                    h_VisGenAntiBJetpT->Fill(allGenJets_->at(AntiBHadronIndex).Pt(), trueLevelWeight );
                    h_VisGenMet->Fill(GenMet_->Pt(), trueLevelWeight);
                    
                    //for HT, count only >= JETPTCUT
                    genHT = getJetHT(*allGenJets_, JETPTCUT);
                    h_VisGenHT->Fill(genHT, trueLevelWeight);

                    h_VisGenLLBarDPhi->Fill(abs( DeltaPhi(*GenLepton_, *GenAntiLepton_)), trueLevelWeight );
                    h_VisGenLeptonantiBjetMass->Fill(( *GenLepton_ + allGenJets_->at(AntiBHadronIndex) ).M(), trueLevelWeight );
                    h_VisGenAntiLeptonBjetMass->Fill(( *GenAntiLepton_ + allGenJets_->at(BHadronIndex) ).M(), trueLevelWeight );
                    h_VisGenJetMult->Fill(allGenJets_->size(), trueLevelWeight );

                    //Begin: Select & Fill histograms with Leading pT and 2nd Leading pT: Lepton and BJet
                    h_VisGenLeptonpTLead->Fill(LeadGenLepton.Pt(), trueLevelWeight);
                    h_VisGenLeptonpTNLead->Fill(NLeadGenLepton.Pt(), trueLevelWeight);
                    h_VisGenLeptonEtaLead->Fill(LeadGenLepton.Eta(), trueLevelWeight);
                    h_VisGenLeptonEtaNLead->Fill(NLeadGenLepton.Eta(), trueLevelWeight);
                    
                    h_VisGenBJetpTLead->Fill(LeadGenBJet.Pt(), trueLevelWeight);
                    h_VisGenBJetpTNLead->Fill(NLeadGenBJet.Pt(), trueLevelWeight);
                    h_VisGenBJetEtaLead->Fill(LeadGenBJet.Eta(), trueLevelWeight);
                    h_VisGenBJetEtaNLead->Fill(NLeadGenBJet.Eta(), trueLevelWeight);
                    //End: Select & Fill histograms with Leading pT and 2nd Leading pT: Lepton and BJet
                    
//                     //New plots from Carmen: Begin
//                     bool firstJet = 0, secondJet = 0;
//                     for(int k=0; k<allGenJets->size(); k++){
//                         if(abs(allGenJets->at(k).Eta())>2.4 || allGenJets->at(k).Pt()< 30.0) {continue;}
//                         if(!firstJet) {
//                             h_VisGenLeadingJetpT->Fill(allGenJets->at(k).Pt(),trueLevelWeight);
//                             h_VisGenLeadingJetEta->Fill(allGenJets->at(k).Eta(),trueLevelWeight);
//                             firstJet=1;
//                             continue;
//                         }
//                         if(firstJet && !secondJet){
//                             h_VisGenNLeadingJetpT->Fill(allGenJets->at(k).Pt(),trueLevelWeight);
//                             h_VisGenNLeadingJetEta->Fill(allGenJets->at(k).Eta(),trueLevelWeight);
//                             secondJet=1;
//                             break;
//                         }
//                     }
//                     
//                     for(int genJet=0; genJet<allGenJets->size(); genJet++){
//                         if(abs(allGenJets->at(genJet).Eta() ) > 2.4 || TMath::Abs(DeltaR(*GenLepton, allGenJets->at(genJet))) < 0.4 
//                             || TMath::Abs(DeltaR(*GenAntiLepton, allGenJets->at(genJet))) < 0.4 ) {
//                             continue;
//                         }
//                         if(allGenJets->at(genJet).Pt()> 30) {
//                             GetJets_cut++; 
//                             if(allGenJets->at(BHadronIndex) != allGenJets->at(genJet) && allGenJets->at(AntiBHadronIndex) != allGenJets->at(genJet)) { 
//                                 jetHTGen+=allGenJets->at(genJet).Pt(); 
//                                 if(jetnum < 3) {
//                                     jetnum++;
//                                     extragenjet[jetnum] = genJet;
//                                 }
//                             }
//                             if(allGenJets->at(genJet).Pt()> 40) GetJets_cut40++;
//                             if(allGenJets->at(genJet).Pt()> 60) GetJets_cut60++;
//                         }
//                     }//for
// 
//                     h_VisGenJetMult->Fill(GetJets_cut,trueLevelWeight);
//                     h_VisGenJetMultpt40->Fill(GetJets_cut40,trueLevelWeight);
//                     h_VisGenJetMultpt60->Fill(GetJets_cut60,trueLevelWeight);
//                     if(jetnum>2){
//                         h_VisGenExtraJetpT4->Fill(allGenJets->at(extragenjet[3]).Pt(),trueLevelWeight);
//                         h_VisGenExtraJetEta4->Fill(allGenJets->at(extragenjet[3]).Eta(),trueLevelWeight);
//                     }
//                     else if(jetnum>1){
//                         h_VisGenExtraJetpT3->Fill(allGenJets->at(extragenjet[2]).Pt(),trueLevelWeight);
//                         h_VisGenExtraJetEta3->Fill(allGenJets->at(extragenjet[2]).Eta(),trueLevelWeight);
//                     }
//                     else if(jetnum>0){
//                         h_VisGenExtraJetpT2->Fill(allGenJets->at(extragenjet[1]).Pt(),trueLevelWeight);
//                         h_VisGenExtraJetEta2->Fill(allGenJets->at(extragenjet[1]).Eta(),trueLevelWeight);
//                     }
//                     else if(jetnum == 0){
//                         h_VisGenExtraJetpT->Fill(allGenJets->at(extragenjet[0]).Pt(),trueLevelWeight);
//                         h_VisGenExtraJetEta->Fill(allGenJets->at(extragenjet[0]).Eta(),trueLevelWeight);
//                     }
//                     //New plots from Carmen: End
                }
            }
        }
        
        LV genttbar(*GenTop_ + *GenAntiTop_);
        h_VisGenTTBarMass->Fill(genttbar.M(), trueLevelWeight );
        h_VisGenTTBarRapidity->Fill(genttbar.Rapidity(), trueLevelWeight );
        h_VisGenTTBarpT->Fill(genttbar.Pt(), trueLevelWeight );

        h_VisGenToppT->Fill(GenTop_->Pt(), trueLevelWeight );
        h_VisGenAntiToppT->Fill(GenAntiTop_->Pt(), trueLevelWeight );
        h_VisGenTopRapidity->Fill(GenTop_->Rapidity(), trueLevelWeight );
        h_VisGenAntiTopRapidity->Fill(GenAntiTop_->Rapidity(), trueLevelWeight );
        h_VisGenTopEta->Fill(GenTop_->Eta(), trueLevelWeight );
        h_VisGenAntiTopEta->Fill(GenAntiTop_->Eta(), trueLevelWeight );
        
        h_VisGenNeutrinopT->Fill(GenNeutrino_->Pt(), trueLevelWeight);
        h_VisGenAntiNeutrinopT->Fill(GenAntiNeutrino_->Pt(), trueLevelWeight);
        
        //Begin: Fill histograms with Leading pT and 2nd Leading pT: Top
        orderLVByPt(LeadGenTop, NLeadGenTop, *GenTop_, *GenAntiTop_);
        h_VisGenToppTLead->Fill(LeadGenTop.Pt(), trueLevelWeight);
        h_VisGenToppTNLead->Fill(NLeadGenTop.Pt(), trueLevelWeight);
        h_VisGenTopRapidityLead->Fill(LeadGenTop.Rapidity(), trueLevelWeight);
        h_VisGenTopRapidityNLead->Fill(NLeadGenTop.Rapidity(), trueLevelWeight);
        h_VisGenTopMassLead->Fill(LeadGenTop.M(), trueLevelWeight);
        h_VisGenTopMassNLead->Fill(NLeadGenTop.M(), trueLevelWeight);
        //End: Fill histograms with Leading pT and 2nd Leading pT: Top
        
    }//for visible top events

    // ++++ Control Plots ++++
    for (int i=0; i<(int) leptons_->size(); ++i){
        h_AllLeptonEta_step0->Fill(leptons_->at(i).Eta(), 1);
        h_AllLeptonpT_step0->Fill(leptons_->at(i).Pt(), 1);
    }
    
    for (int i=0; i<(int) jets_->size(); ++i){
        h_AllJetsEta_step0->Fill(jets_->at(i).Eta(), 1);
        h_AllJetspT_step0->Fill(jets_->at(i).Pt(), 1);
    }
    h_LeptonMult_step0->Fill(leptons_->size(), 1);
    h_JetsMult_step0->Fill(jets_->size(), 1);
    int nbjets_step0 = NumberOfBJets;
    h_BJetsMult_step0->Fill(nbjets_step0, 1);
    
    h_PUSF->Fill(weightPU, 1);

    
    //===CUT===
    // check if event was triggered
    //our triggers (bits: see the ntuplewriter!)    
    constexpr int mumuTriggers = 0x8 + 0x20; //17/8 + 17Tr8
    constexpr int emuTriggers = 0x2000 + 0x4000;
    constexpr int eeTriggers = 0x40000;
    
    if (!(((triggerBits_ & mumuTriggers) && channelPdgIdProduct_ == -13*13)    //mumu triggers in rightmost byte
          ||((triggerBits_ & emuTriggers) && channelPdgIdProduct_ == -11*13)     //emu in 2nd byte
          ||((triggerBits_ & eeTriggers) && channelPdgIdProduct_ == -11*11)))    //ee in 3rd byte
    {
        return kTRUE;
    }

    size_t LeadLeptonNumber = 0;
    size_t NLeadLeptonNumber = 0;
    bool hasLeptonPair = getLeptonPair(LeadLeptonNumber, NLeadLeptonNumber);

    // ++++ Control Plots ++++
    for (int i=0; i<(int) leptons_->size(); ++i){
        h_AllLeptonEta_step1->Fill(leptons_->at(i).Eta(), 1);
        h_AllLeptonpT_step1->Fill(leptons_->at(i).Pt(), 1);
    }
    if(leptons_->size()>1){
        h_LeptonEta_step1->Fill(leptons_->at(0).Eta(), 1);
        h_LeptonpT_step1->Fill(leptons_->at(0).Pt(), 1);
        h_LeptonEta_step1->Fill(leptons_->at(1).Eta(), 1);
        h_LeptonpT_step1->Fill(leptons_->at(1).Pt(), 1);
    }

    for (int i=0; i<(int) jets_->size(); ++i){
        h_AllJetsEta_step1->Fill(jets_->at(i).Eta(), 1);
        h_AllJetspT_step1->Fill(jets_->at(i).Pt(), 1);
    }
    h_LeptonMult_step1->Fill(leptons_->size(), 1);
    h_JetsMult_step1->Fill(jets_->size(), 1);
    int nbjets_step1 = NumberOfBJets;
    h_BJetsMult_step1->Fill(nbjets_step1, 1);
    
    
    //===CUT===
    // we need an OS lepton pair
    if (! hasLeptonPair) return kTRUE;
    
    LV dilepton = leptons_->at(LeadLeptonNumber) + leptons_->at(NLeadLeptonNumber);
    
    // ++++ Control Plots ++++
    for (int i=0; i<(int) leptons_->size(); ++i){
        h_AllLeptonEta_step2->Fill(leptons_->at(i).Eta(), 1);
        h_AllLeptonpT_step2->Fill(leptons_->at(i).Pt(), 1);
    }
    h_LeptonEta_step2->Fill(leptons_->at(0).Eta(), 1);
    h_LeptonpT_step2->Fill(leptons_->at(0).Pt(), 1);
    h_LeptonEta_step2->Fill(leptons_->at(1).Eta(), 1);
    h_LeptonpT_step2->Fill(leptons_->at(1).Pt(), 1);

    for (int i=0; i<(int) jets_->size(); ++i){
        h_AllJetsEta_step2->Fill(jets_->at(i).Eta(), 1);
        h_AllJetspT_step2->Fill(jets_->at(i).Pt(), 1);
    }
    if(jets_->size()>1){
        h_JetsEta_step2->Fill(jets_->at(0).Eta(), 1);
        h_JetspT_step2->Fill(jets_->at(0).Pt(), 1);
        h_JetsEta_step2->Fill(jets_->at(1).Eta(), 1);
        h_JetspT_step2->Fill(jets_->at(1).Pt(), 1);
    }
    h_LeptonMult_step2->Fill(leptons_->size(), 1);
    h_JetsMult_step2->Fill(jets_->size(), 1);
    int nbjets_step2 = NumberOfBJets;
    h_BJetsMult_step2->Fill(nbjets_step2, 1);
    

    //===CUT===
    //with at least 12 GeV invariant mass
    if (dilepton.M() < 20) return kTRUE;
    
    // find l+ and l-
    LV leptonPlus;
    LV leptonMinus;
    if (lepPdgId_->at(LeadLeptonNumber) < 0) {
        leptonPlus = leptons_->at(LeadLeptonNumber);
        leptonMinus = leptons_->at(NLeadLeptonNumber);
    } else {
        leptonMinus = leptons_->at(LeadLeptonNumber);
        leptonPlus = leptons_->at(NLeadLeptonNumber);
    }

    //This is necessary due to the ordering in the trigger 2D-plots
    LV leptonX, leptonY;
    if ( abs( lepPdgId_->at(LeadLeptonNumber) ) == abs( lepPdgId_->at(NLeadLeptonNumber) ) ){
        //in ee and mumu channel leptonX must be the highest pT lepton
        leptonX = leptons_->at(LeadLeptonNumber);
        leptonY = leptons_->at(NLeadLeptonNumber);
    } else {
        // in emu channel lepX should be electron
        if (abs(lepPdgId_->at(LeadLeptonNumber)) == 11) {
            leptonX = leptons_->at(LeadLeptonNumber);
            leptonY = leptons_->at(NLeadLeptonNumber);
        } else {
            leptonX = leptons_->at(NLeadLeptonNumber);
            leptonY = leptons_->at(LeadLeptonNumber);
        }
    }
    
    int LleptonId = lepPdgId_->at(LeadLeptonNumber);
    int NLleptonId = lepPdgId_->at(NLeadLeptonNumber);
    //Now determine the lepton trigger and ID scale factors
    double weightLepSF = isMC_ ? getLeptonIDSF(leptons_->at(LeadLeptonNumber), leptons_->at(NLeadLeptonNumber), LleptonId, NLleptonId) : 1;  
    double weightTrigSF = isMC_ ? getTriggerSF(leptonX, leptonY) : 1;
    
    //First control plots after dilepton selection (without Z cut)
    double weight = weightGenerator_*weightTrigSF*weightLepSF;

    //weight even without PU reweighting
    h_vertMulti_noPU->Fill(vertMulti_, weight);
    
    //apply PU reweighting - continue with control plots
    weight *= weightPU;
    h_vertMulti->Fill(vertMulti_, weight);
    
    h_step4->Fill(1, weight);
    h_TrigSF->Fill(weightTrigSF, 1);
    h_LepSF->Fill(weightLepSF, 1);
    
    h_jetMulti_diLep->Fill(jets_->size(), weight);
    h_diLepMassFull->Fill(dilepton.M(), weight);

    
    //****************************************
    //handle inverted Z cut
    // Fill loose dilepton mass histogram before any jet cuts
    bool isZregion = dilepton.M() > 76 && dilepton.M() < 106;
    bool hasJets = jets_->size() > 1;
    bool hasMetOrEmu = channel_ == "emu" || met_->Pt() > 40;
    bool hasBtag = BJetIndex.size() > 0;
    double weightBtagSF = -1; //trick: initialize to -1 to avoid calculation of the btagSF twice
    
    bool hasSolution = HypTop_->size() > 0;
    if (kinRecoOnTheFly_ || true) 
        hasSolution = calculateKinReco(leptonMinus, leptonPlus);
    
    if ( isZregion ) {
        double fullWeights = weightGenerator_*weightPU*weightTrigSF*weightLepSF;
//         Looseh1->Fill(dilepton.M(), fullWeights);
        Zh1_postZcut->Fill(dilepton.M(), fullWeights);
        Allh1_postZcut->Fill(dilepton.M(), fullWeights);
        
        if ( hasJets ) {
            Looseh1->Fill(dilepton.M(), fullWeights);
            Zh1_post2jets->Fill(dilepton.M(), fullWeights);
            Allh1_post2jets->Fill(dilepton.M(), fullWeights);
            
            if ( hasMetOrEmu ) {
                Zh1_postMET->Fill(dilepton.M(), fullWeights);
                Allh1_postMET->Fill(dilepton.M(), fullWeights);
                
                if ( hasBtag ) {
                    weightBtagSF = isMC_ ? calculateBtagSF() : 1;
                    fullWeights *= weightBtagSF;
                    Zh1_post1btag->Fill(dilepton.M(), fullWeights);
                    Allh1_post1btag->Fill(dilepton.M(), fullWeights);
                    
                    if ( hasSolution ) {
                        fullWeights *= weightKinFit_;
                        Zh1_postKinReco->Fill(dilepton.M(), fullWeights);
                        Allh1_postKinReco->Fill(dilepton.M(), fullWeights);
                    }
                }
            }
        }
    }
    
    // ++++ Control Plots ++++
    for (int i=0; i<(int) leptons_->size(); ++i){
        h_AllLeptonEta_step3->Fill(leptons_->at(i).Eta(), weight);
        h_AllLeptonpT_step3->Fill(leptons_->at(i).Pt(), weight);
    }
    h_LeptonEta_step3->Fill(leptons_->at(0).Eta(), weight);
    h_LeptonpT_step3->Fill(leptons_->at(0).Pt(), weight);
    h_LeptonEta_step3->Fill(leptons_->at(1).Eta(), weight);
    h_LeptonpT_step3->Fill(leptons_->at(1).Pt(), weight);

    for (int i=0; i<(int) jets_->size(); ++i){
        h_AllJetsEta_step3->Fill(jets_->at(i).Eta(), weight);
        h_AllJetspT_step3->Fill(jets_->at(i).Pt(), weight);
    }
    if(jets_->size()>1){
        h_JetsEta_step3->Fill(jets_->at(0).Eta(), weight);
        h_JetspT_step3->Fill(jets_->at(0).Pt(), weight);
        h_JetsEta_step3->Fill(jets_->at(1).Eta(), weight);
        h_JetspT_step3->Fill(jets_->at(1).Pt(), weight);
    }
    h_LeptonMult_step3->Fill(leptons_->size(), weight);
    h_JetsMult_step3->Fill(jets_->size(), weight);
    int nbjets_step3 = NumberOfBJets;
    h_BJetsMult_step3->Fill(nbjets_step3, weight);
    
    //=== CUT ===
    //Exclude the Z window
    if (channel_ != "emu" && isZregion) return kTRUE;
    
    h_step5->Fill(1, weight);
    h_LeptonpT_diLep->Fill(leptonMinus.Pt(), weight);
    h_AntiLeptonpT_diLep->Fill(leptonPlus.Pt(), weight);
    h_LeptonEta_diLep->Fill(leptonMinus.Eta(), weight);
    h_AntiLeptonEta_diLep->Fill(leptonPlus.Eta(), weight);
    
    h_MET->Fill(met_->Pt(), weight);
    //loop over both leptons
    for (auto i : {LeadLeptonNumber, NLeadLeptonNumber}) {
        if ( std::abs(lepPdgId_->at(i)) == 11 ) {
            h_ElectronpT->Fill(leptons_->at(i).Pt(), weight);
            h_ElectronEta->Fill(leptons_->at(i).Eta(), weight);
        }
        if ( std::abs(lepPdgId_->at(i)) == 13 ) {
            h_MuonpT->Fill(leptons_->at(i).Pt(), weight);
            h_MuonEta->Fill(leptons_->at(i).Eta(), weight);
        }
    }
    
    // ++++ Control Plots ++++
    for (int i=0; i<(int) leptons_->size(); ++i){
        h_AllLeptonEta_step4->Fill(leptons_->at(i).Eta(), weight);
        h_AllLeptonpT_step4->Fill(leptons_->at(i).Pt(), weight);
    }
    h_LeptonEta_step4->Fill(leptons_->at(0).Eta(), weight);
    h_LeptonpT_step4->Fill(leptons_->at(0).Pt(), weight);
    h_LeptonEta_step4->Fill(leptons_->at(1).Eta(), weight);
    h_LeptonpT_step4->Fill(leptons_->at(1).Pt(), weight);

    for (int i=0; i<(int) jets_->size(); ++i){
        h_AllJetsEta_step4->Fill(jets_->at(i).Eta(), weight);
        h_AllJetspT_step4->Fill(jets_->at(i).Pt(), weight);
    }
    if(jets_->size()>1){
        h_JetsEta_step4->Fill(jets_->at(0).Eta(), weight);
        h_JetspT_step4->Fill(jets_->at(0).Pt(), weight);
        h_JetsEta_step4->Fill(jets_->at(1).Eta(), weight);
        h_JetspT_step4->Fill(jets_->at(1).Pt(), weight);
    }
    h_LeptonMult_step4->Fill(leptons_->size(), weight);
    h_JetsMult_step4->Fill(jets_->size(), weight);
    int nbjets_step4 = NumberOfBJets;
    h_BJetsMult_step4->Fill(nbjets_step4, weight);
    
    if (!isZregion) { //also apply Z cut in emu!
        TTh1_postZcut->Fill(dilepton.M(), weight);
        Allh1_postZcut->Fill(dilepton.M(), weight);  //this is also filled in the Z region in the code above
    }
    
    //=== CUT ===
    //Require at least two jets > 30 GeV (check for > 30 needed because we might have 20 GeV jets in our NTuple)
    if (! hasJets) return kTRUE;
    h_step6->Fill(1, weight);
    
    // ++++ Control Plots ++++
    for (int i=0; i<(int) leptons_->size(); ++i){
        h_AllLeptonEta_step5->Fill(leptons_->at(i).Eta(), weight);
        h_AllLeptonpT_step5->Fill(leptons_->at(i).Pt(), weight);
    }
    h_LeptonEta_step5->Fill(leptons_->at(0).Eta(), weight);
    h_LeptonpT_step5->Fill(leptons_->at(0).Pt(), weight);
    h_LeptonEta_step5->Fill(leptons_->at(1).Eta(), weight);
    h_LeptonpT_step5->Fill(leptons_->at(1).Pt(), weight);

    for (int i=0; i<(int) jets_->size(); ++i){
        h_AllJetsEta_step5->Fill(jets_->at(i).Eta(), weight);
        h_AllJetspT_step5->Fill(jets_->at(i).Pt(), weight);
    }
    if(jets_->size()>1){
        h_JetsEta_step5->Fill(jets_->at(0).Eta(), weight);
        h_JetspT_step5->Fill(jets_->at(0).Pt(), weight);
        h_JetsEta_step5->Fill(jets_->at(1).Eta(), weight);
        h_JetspT_step5->Fill(jets_->at(1).Pt(), weight);
    }
    h_LeptonMult_step5->Fill(leptons_->size(), weight);
    h_JetsMult_step5->Fill(jets_->size(), weight);
    int nbjets_step5 = NumberOfBJets;
    h_BJetsMult_step5->Fill(nbjets_step5, weight);
    
    if (!isZregion) { //also apply Z cut in emu!
        TTh1_post2jets->Fill(dilepton.M(), weight);
        Allh1_post2jets->Fill(dilepton.M(), weight);  //this is also filled in the Z region in the code above
    }
    
    //=== CUT ===
    //Require MET > 30 GeV in non-emu channels
    if (!hasMetOrEmu) return kTRUE;
    h_step7->Fill(1, weight);
 
    h_LeptonpT_postMETcut->Fill(leptonMinus.Pt(), weight);
    h_AntiLeptonpT_postMETcut->Fill(leptonPlus.Pt(), weight);
    h_LeptonEta_postMETcut->Fill(leptonMinus.Eta(), weight);
    h_AntiLeptonEta_postMETcut->Fill(leptonPlus.Eta(), weight);

    //loop over both leptons
    for (auto i : {LeadLeptonNumber, NLeadLeptonNumber}) {
        if ( std::abs(lepPdgId_->at(i)) == 11 ) {
            h_ElectronpT_postMETcut->Fill(leptons_->at(i).Pt(), weight);
            h_ElectronEta_postMETcut->Fill(leptons_->at(i).Eta(), weight);
        }
        if ( std::abs(lepPdgId_->at(i)) == 13 ) {
            h_MuonpT_postMETcut->Fill(leptons_->at(i).Pt(), weight);
            h_MuonEta_postMETcut->Fill(leptons_->at(i).Eta(), weight);
        }
    }
    
    h_jetMulti_noBTag->Fill(jets_->size(), weight);
    h_BjetMulti_noBTag->Fill(BJetIndex.size(), weight);

    double jetHT = getJetHT(*jets_, JETPTCUT);
    h_jetHT->Fill(jetHT, weight);

    for ( size_t i = 0; i < 2; ++i ) {
        h_jetpT->Fill(jets_->at(i).Pt(), weight);
    }

    // ++++ Control Plots ++++
    for (int i=0; i<(int) leptons_->size(); ++i){
        h_AllLeptonEta_step6->Fill(leptons_->at(i).Eta(), weight);
        h_AllLeptonpT_step6->Fill(leptons_->at(i).Pt(), weight);
    }
    h_LeptonEta_step6->Fill(leptons_->at(0).Eta(), weight);  
    h_LeptonpT_step6->Fill(leptons_->at(0).Pt(), weight);    
    h_LeptonEta_step6->Fill(leptons_->at(1).Eta(), weight);
    h_LeptonpT_step6->Fill(leptons_->at(1).Pt(), weight);

    for (int i=0; i<(int) jets_->size(); ++i){
        h_AllJetsEta_step6->Fill(jets_->at(i).Eta(), weight);
        h_AllJetspT_step6->Fill(jets_->at(i).Pt(), weight);
    }
    if(jets_->size()>1){
        h_JetsEta_step6->Fill(jets_->at(0).Eta(), weight);
        h_JetspT_step6->Fill(jets_->at(0).Pt(), weight);
        h_JetsEta_step6->Fill(jets_->at(1).Eta(), weight);
        h_JetspT_step6->Fill(jets_->at(1).Pt(), weight);
    }
    h_LeptonMult_step6->Fill(leptons_->size(), weight);
    h_JetsMult_step6->Fill(jets_->size(), weight);
    int nbjets_step6 = NumberOfBJets;
    h_BJetsMult_step6->Fill(nbjets_step6, weight);
    
    if (!isZregion) { //also apply Z cut in emu!
        TTh1_postMET->Fill(dilepton.M(), weight);
        Allh1_postMET->Fill(dilepton.M(), weight);  //this is also filled in the Z region in the code above
    }
    
    //=== CUT ===
    //Require at least one b tagged jet
    if (!hasBtag) return kTRUE;

    //finally do the btag efficiency calculation stuff
    if(isSignal_){
        for (size_t i = 0; i < jets_->size(); ++i) {
            if (jets_->at(i).Pt() <= JETPTCUT) break;
            double absJetEta = abs(jets_->at(i).Eta());
            if (absJetEta<2.4) {
                int partonFlavour = abs(jetPartonFlavour_->at(i));
                if(partonFlavour == 5){//b-quark
                    h_bjets->Fill(jets_->at(i).Pt(), absJetEta);
                    if((*jetBTagCSV_)[i]>BtagWP){
                        h_btaggedjets->Fill(jets_->at(i).Pt(), absJetEta);
                    }
                }
                else if (partonFlavour == 4){//c-quark
                    h_cjets->Fill(jets_->at(i).Pt(), absJetEta);
                    if((*jetBTagCSV_)[i]>BtagWP){
                        h_ctaggedjets->Fill(jets_->at(i).Pt(), absJetEta);
                    }
                }
                else if (partonFlavour != 0){//l-quark
                    h_ljets->Fill(jets_->at(i).Pt(), absJetEta);
                    if((*jetBTagCSV_)[i]>BtagWP){
                        h_ltaggedjets->Fill(jets_->at(i).Pt(), absJetEta);
                    }
                }
            }
        }
    }
    
    if (weightBtagSF == -1) weightBtagSF = isMC_ ? calculateBtagSF() : 1; //avoid calculation of the btagSF twice
    weight *= weightBtagSF;
    h_BTagSF->Fill(weightBtagSF );
    h_step8->Fill(1, weight );
    
    if (RUNSYNC) {
        static int fullSelectionCounter = 0;
        if (fullSelectionCounter == 0)
            std::cout << "Selected#\tRun\tEvent\tlep+\tlep-\tMll\tNJets\tjet0\tjet1\tNTags\tGenJet1\tGenJet2\tMet\tGenMet\tt/tbar_decay\n"
            << std::setprecision(2) << std::fixed;
        std::cout << "Event#" << ++fullSelectionCounter << ":\t" << runNumber_ << "\t" << eventNumber_ << "\t" << leptonPlus << "\t" << leptonMinus << "\t"
            << dilepton.M() << "\t" << jets_->size() << "\t"
            << jets_->at(0) << "\t" << jets_->at(1) << "\t" << BJetIndex.size() << "\t"
            << associatedGenJet_->at(0) << "\t" << associatedGenJet_->at(1) << "\t"
            << met_->Pt() << "\t" << GenMet_->Pt() << "\t"
            << topDecayModeString()
            << "\n";
    }
    
    h_BjetMulti->Fill(BJetIndex.size(), weight);
    h_jetMulti->Fill(jets_->size(), weight);
    
    h_leptonPtBeforeKinReco->Fill(leptonMinus.Pt(), weight);
    h_leptonPtBeforeKinReco->Fill(leptonPlus.Pt(), weight);
    h_leptonEtaBeforeKinReco->Fill(leptonMinus.Eta(), weight);
    h_leptonEtaBeforeKinReco->Fill(leptonPlus.Eta(), weight);
    h_METBeforeKinReco->Fill(met_->Pt(), weight);
    for (size_t i = 0; i < BJetIndex.size(); ++i)
        h_bjetetaBeforeKinReco->Fill(jets_->at(i).Eta(), weight);

    // ++++ Control Plots ++++
    for (int i=0; i<(int) leptons_->size(); ++i){
        h_AllLeptonEta_step7->Fill(leptons_->at(i).Eta(), weight);
        h_AllLeptonpT_step7->Fill(leptons_->at(i).Pt(), weight);
    }
    h_LeptonEta_step7->Fill(leptons_->at(0).Eta(), weight);
    h_LeptonpT_step7->Fill(leptons_->at(0).Pt(), weight);
    h_LeptonEta_step7->Fill(leptons_->at(1).Eta(), weight);
    h_LeptonpT_step7->Fill(leptons_->at(1).Pt(), weight);

    for (int i=0; i<(int) jets_->size(); ++i){
        h_AllJetsEta_step7->Fill(jets_->at(i).Eta(), weight);
        h_AllJetspT_step7->Fill(jets_->at(i).Pt(), weight);
    }
    if(jets_->size()>1){
        h_JetsEta_step7->Fill(jets_->at(0).Eta(), weight);
        h_JetspT_step7->Fill(jets_->at(0).Pt(), weight);
        h_JetsEta_step7->Fill(jets_->at(1).Eta(), weight);
        h_JetspT_step7->Fill(jets_->at(1).Pt(), weight);
    }
    h_LeptonMult_step7->Fill(leptons_->size(), weight);
    h_JetsMult_step7->Fill(jets_->size(), weight);
    int nbjets_step7 = NumberOfBJets;
    h_BJetsMult_step7->Fill(nbjets_step7, weight);
    
    if (!isZregion) { //also apply Z cut in emu!
        TTh1_post1btag->Fill(dilepton.M(), weight);
        Allh1_post1btag->Fill(dilepton.M(), weight);  //this is also filled in the Z region in the code above
    }
    
    //=== CUT ===
    //Require at least one solution for the kinematic event reconstruction
    if (!hasSolution) return kTRUE;
    weight *= weightKinFit_;
    
    h_leptonPtAfterKinReco->Fill(leptonMinus.Pt(), weight);
    h_leptonPtAfterKinReco->Fill(leptonPlus.Pt(), weight);
    h_leptonEtaAfterKinReco->Fill(leptonMinus.Eta(), weight);
    h_leptonEtaAfterKinReco->Fill(leptonPlus.Eta(), weight);
    h_METAfterKinReco->Fill(met_->Pt(), weight);
    for (size_t i = 0; i < BJetIndex.size(); ++i)
        h_bjetetaAfterKinReco->Fill(jets_->at(i).Eta(), weight);
    
    h_KinRecoSF->Fill(weightKinFit_, 1);
    h_EventWeight->Fill(weight, 1);
    
     // ++++ Control Plots ++++
    for (int i=0; i<(int) leptons_->size(); ++i){
        h_AllLeptonEta_step8->Fill(leptons_->at(i).Eta(), weight);
        h_AllLeptonpT_step8->Fill(leptons_->at(i).Pt(), weight);
    }
    h_LeptonEta_step8->Fill(leptons_->at(0).Eta(), weight);
    h_LeptonpT_step8->Fill(leptons_->at(0).Pt(), weight);
    h_LeptonEta_step8->Fill(leptons_->at(1).Eta(), weight);
    h_LeptonpT_step8->Fill(leptons_->at(1).Pt(), weight);

    for (int i=0; i<(int) jets_->size(); ++i){
        h_AllJetsEta_step8->Fill(jets_->at(i).Eta(), weight);
        h_AllJetspT_step8->Fill(jets_->at(i).Pt(), weight);
    }
    if(jets_->size()>1){
        h_JetsEta_step8->Fill(jets_->at(0).Eta(), weight);
        h_JetspT_step8->Fill(jets_->at(0).Pt(), weight);
        h_JetsEta_step8->Fill(jets_->at(1).Eta(), weight);
        h_JetspT_step8->Fill(jets_->at(1).Pt(), weight);
    }
    h_LeptonMult_step8->Fill(leptons_->size(), weight);
    h_JetsMult_step8->Fill(jets_->size(), weight);
    int nbjets_step8 = NumberOfBJets;
    h_BJetsMult_step8->Fill(nbjets_step8, weight);
    
    h_step9->Fill(1, weight);
    h_jetMultiXSec->Fill(jets_->size(), weight);
    h_jetMultiNoPU->Fill(jets_->size(), weight / weightPU );
    h_diLepMassFull_fullSel->Fill(dilepton.M(), weight);
        
    //create helper variables
    
    //Begin: find 1st (and 2nd) leading pT particles: Top, Lepton, BJetIndex
    LV LeadHypTop, NLeadHypTop;
    LV LeadHypLepton, NLeadHypLepton;
    LV LeadHypBJet, NLeadHypBJet;
    
    size_t solutionIndex = 0; //always zero!
    orderLVByPt(LeadHypTop, NLeadHypTop, HypTop_->at(solutionIndex), HypAntiTop_->at(solutionIndex));
    orderLVByPt(LeadHypLepton, NLeadHypLepton, HypLepton_->at(solutionIndex), HypAntiLepton_->at(solutionIndex));
    orderLVByPt(LeadHypBJet, NLeadHypBJet, HypBJet_->at(solutionIndex), HypAntiBJet_->at(solutionIndex));
    //End: find 1st (and 2nd) leading pT particles: Top, Lepton, BJetIndex
    
    //create ll and tt system
    LV hypllbar(HypLepton_->at(solutionIndex) + HypAntiLepton_->at(solutionIndex));
    LV hypttbar(HypTop_->at(solutionIndex)+HypAntiTop_->at(solutionIndex));
    
    //First fill the reco histograms (which have no scaling factors applied)
    double recoWeight = weightGenerator_ * weightPU;
    h_RecoTTBarMass->Fill(hypttbar.M(), recoWeight);
    h_RecoTTBarRapidity->Fill(hypttbar.Rapidity(), recoWeight);
    h_RecoTTBarpT->Fill(hypttbar.Pt(), recoWeight);
    h_RecoToppT->Fill(HypTop_->at(solutionIndex).Pt(), recoWeight);
    h_RecoAntiToppT->Fill(HypAntiTop_->at(solutionIndex).Pt(), recoWeight);
    h_RecoTopRapidity->Fill(HypTop_->at(solutionIndex).Rapidity(), recoWeight);
    h_RecoAntiTopRapidity->Fill(HypAntiTop_->at(solutionIndex).Rapidity(), recoWeight);

    h_RecoLLBarMass->Fill(hypllbar.M(), recoWeight);
    h_RecoLLBarpT->Fill(hypllbar.Pt(), recoWeight);
    h_RecoLeptonpT->Fill(HypLepton_->at(solutionIndex).Pt(), recoWeight);
    h_RecoAntiLeptonpT->Fill(HypAntiLepton_->at(solutionIndex).Pt(), recoWeight);
    h_RecoLeptonEta->Fill(HypLepton_->at(solutionIndex).Eta(), recoWeight);
    h_RecoAntiLeptonEta->Fill(HypAntiLepton_->at(solutionIndex).Eta(), recoWeight);
    
    h_RecoMet->Fill(met_->Pt(), recoWeight);
    h_RecoHT->Fill(jetHT, recoWeight);
    
    h_RecoNeutrinopT->Fill(HypNeutrino_->at(solutionIndex).Pt(), recoWeight);
    h_RecoAntiNeutrinopT->Fill(HypAntiNeutrino_->at(solutionIndex).Pt(), recoWeight);

    h_RecoBJetpT->Fill(HypBJet_->at(solutionIndex).Pt(), recoWeight);
    h_RecoAntiBJetpT->Fill(HypAntiBJet_->at(solutionIndex).Pt(), recoWeight);
    h_RecoBJetRapidity->Fill(HypBJet_->at(solutionIndex).Rapidity(), recoWeight);
    h_RecoAntiBJetRapidity->Fill(HypAntiBJet_->at(solutionIndex).Rapidity(), recoWeight);
    h_RecoBJetEta->Fill(HypBJet_->at(solutionIndex).Eta(), recoWeight);
    h_RecoAntiBJetEta->Fill(HypAntiBJet_->at(solutionIndex).Eta(), recoWeight);

    h_RecoLLBarDPhi->Fill(abs ( DeltaPhi ( HypLepton_->at(solutionIndex), HypAntiLepton_->at(solutionIndex) ) ), recoWeight);
    h_RecoLeptonantiBjetMass->Fill(( HypLepton_->at(solutionIndex)+HypAntiBJet_->at(solutionIndex) ).M(), recoWeight);
    h_RecoAntiLeptonBjetMass->Fill(( HypAntiLepton_->at(solutionIndex)+HypBJet_->at(solutionIndex) ).M(), recoWeight);

//     //New plots from Carmen: Begin
//     h_RecoJetMult->Fill ( jet->size(),recoWeight);
//     h_RecoJetMultpt40->Fill(RecoJets_cut40,recoWeight);
//     h_RecoJetMultpt60->Fill(RecoJets_cut60,recoWeight);
//     h_HypJetMult->Fill ( jet->size(),weight);
//     h_HypJetMultpt40->Fill(RecoJets_cut40,weight);
//     h_HypJetMultpt60->Fill(RecoJets_cut60,weight);
// 
//     bool firstJet = 0, secondJet = 0;
//     for(int k=0; k<(int)jet->size(); k++){
//         if(abs(jet->at(k).Eta())>2.4 && jet->at(k).Pt()< 30.0) {continue;}
//         if(!firstJet) {
//             h_RecoLeadingJetpT->Fill(jet->at(k).Pt(),recoWeight);
//             h_RecoLeadingJetEta->Fill(jet->at(k).Eta(),recoWeight);
//             h_HypLeadingJetpT->Fill(jet->at(k).Pt(),weight);
//             h_HypLeadingJetEta->Fill(jet->at(k).Eta(),weight);
//             firstJet=1;
//             continue;
//         }
//         if(firstJet && !secondJet){
//             h_RecoNLeadingJetpT->Fill(jet->at(k).Pt(),recoWeight);
//             h_RecoNLeadingJetEta->Fill(jet->at(k).Eta(),recoWeight);
//             h_HypNLeadingJetpT->Fill(jet->at(k).Pt(),weight);
//             h_HypNLeadingJetEta->Fill(jet->at(k).Eta(),weight);
//             secondJet=1;
//             break;
//         }
//     }
//     
//     if(jetnumReco>2){
//         h_RecoExtraJetpT4->Fill(jet->at(extrarecojet[3]).Pt(),recoWeight);
//         h_RecoExtraJetEta4->Fill(jet->at(extrarecojet[3]).Eta(),recoWeight);
//         h_HypExtraJetpT4->Fill(jet->at(extrarecojet[3]).Pt(),weight);
//         h_HypExtraJetEta4->Fill(jet->at(extrarecojet[3]).Eta(),weight);
//     }
//     else if (jetnumReco>1){
//         h_RecoExtraJetpT3->Fill(jet->at(extrarecojet[2]).Pt(),recoWeight);
//         h_RecoExtraJetEta3->Fill(jet->at(extrarecojet[2]).Eta(),recoWeight);
//         h_HypExtraJetpT3->Fill(jet->at(extrarecojet[2]).Pt(),weight);
//         h_HypExtraJetEta3->Fill(jet->at(extrarecojet[2]).Eta(),weight);
//     }
//     else if (jetnumReco>0){
//         h_RecoExtraJetpT2->Fill(jet->at(extrarecojet[1]).Pt(),recoWeight);
//         h_RecoExtraJetEta2->Fill(jet->at(extrarecojet[1]).Eta(),recoWeight);
//         h_HypExtraJetpT2->Fill(jet->at(extrarecojet[1]).Pt(),weight);
//         h_HypExtraJetEta2->Fill(jet->at(extrarecojet[1]).Eta(),weight);
//     }
//     else if (jetnumReco >-1){
//         h_RecoExtraJetpT->Fill(jet->at(extrarecojet[0]).Pt(),recoWeight);
//         h_RecoExtraJetEta->Fill(jet->at(extrarecojet[0]).Eta(),recoWeight);
//         h_HypExtraJetpT->Fill(jet->at(extrarecojet[0]).Pt(),weight);
//         h_HypExtraJetEta->Fill(jet->at(extrarecojet[0]).Eta(),weight);
//     }
//     //New plots from Carmen: End
    
    h_RecoToppTLead->Fill(LeadHypTop.Pt(), recoWeight);
    h_RecoToppTNLead->Fill(NLeadHypTop.Pt(), recoWeight);
    h_RecoTopRapidityLead->Fill(LeadHypTop.Rapidity(), recoWeight);
    h_RecoTopRapidityNLead->Fill(NLeadHypTop.Rapidity(), recoWeight);
    h_RecoTopMassLead->Fill(LeadHypTop.M(), recoWeight);
    h_RecoTopMassNLead->Fill(NLeadHypTop.M(), recoWeight);
    
    h_RecoLeptonpTLead->Fill(LeadHypLepton.Pt(), recoWeight);
    h_RecoLeptonpTNLead->Fill(NLeadHypLepton.Pt(), recoWeight);
    h_RecoLeptonEtaLead->Fill(LeadHypLepton.Eta(), recoWeight);
    h_RecoLeptonEtaNLead->Fill(NLeadHypLepton.Eta(), recoWeight);
    
    h_RecoBJetpTLead->Fill(LeadHypBJet.Pt(), recoWeight);
    h_RecoBJetpTNLead->Fill(NLeadHypBJet.Pt(), recoWeight);
    h_RecoBJetEtaLead->Fill(LeadHypBJet.Eta(), recoWeight);
    h_RecoBJetEtaNLead->Fill(NLeadHypBJet.Eta(), recoWeight);
    
    //now go to the plots 
    h_HypTTBarMass->Fill(hypttbar.M(), weight);
    h_HypTTBarRapidity->Fill(hypttbar.Rapidity(), weight);
    h_HypTTBarpT->Fill(hypttbar.Pt(), weight);

    h_HypLLBarMass->Fill(hypllbar.M(), weight);
    h_HypLLBarpT->Fill(hypllbar.Pt(), weight);
    
    h_HypMet->Fill(met_->Pt(), weight);
    h_HypHT->Fill(jetHT, weight);

    h_HypTopMass->Fill(HypTop_->at(solutionIndex).M(), weight);
    h_HypAntiTopMass->Fill(HypAntiTop_->at(solutionIndex).M(), weight);
    h_HypToppT->Fill(HypTop_->at(solutionIndex).Pt(), weight);
    h_HypAntiToppT->Fill(HypAntiTop_->at(solutionIndex).Pt(), weight);
        
    h_HypLeptonpT->Fill(HypLepton_->at(solutionIndex).Pt(), weight);
    h_HypAntiLeptonpT->Fill(HypAntiLepton_->at(solutionIndex).Pt(), weight);

    h_HypBJetpT->Fill(HypBJet_->at(solutionIndex).Pt(), weight);
    h_HypAntiBJetpT->Fill(HypAntiBJet_->at(solutionIndex).Pt(), weight);
    h_HypBJetRapidity->Fill(HypBJet_->at(solutionIndex).Rapidity(), weight);
    h_HypAntiBJetRapidity->Fill(HypAntiBJet_->at(solutionIndex).Rapidity(), weight);

    h_HypTopRapidity->Fill(HypTop_->at(solutionIndex).Rapidity(), weight);
    h_HypAntiTopRapidity->Fill(HypAntiTop_->at(solutionIndex).Rapidity(), weight);
    
    h_HypNeutrinopT->Fill(HypNeutrino_->at(solutionIndex).Pt(), weight);
    h_HypAntiNeutrinopT->Fill(HypAntiNeutrino_->at(solutionIndex).Pt(), weight);
    
    h_HypTopEta->Fill(HypTop_->at(solutionIndex).Eta(), weight);
    h_HypAntiTopEta->Fill(HypAntiTop_->at(solutionIndex).Eta(), weight);
    h_HypBJetEta->Fill(HypBJet_->at(solutionIndex).Eta(), weight);
    h_HypAntiBJetEta->Fill(HypAntiBJet_->at(solutionIndex).Eta(), weight);
    h_HypLeptonEta->Fill(HypLepton_->at(solutionIndex).Eta(), weight);

    h_HypAntiLeptonEta->Fill(HypAntiLepton_->at(solutionIndex).Eta(), weight);

    h_HypLLBarDPhi->Fill(abs ( DeltaPhi ( HypLepton_->at(solutionIndex), HypAntiLepton_->at(solutionIndex) ) ), weight);
    h_HypLeptonantiBjetMass->Fill(( HypLepton_->at(solutionIndex) + HypAntiBJet_->at(solutionIndex) ).M(), weight);
    h_HypAntiLeptonBjetMass->Fill(( HypAntiLepton_->at(solutionIndex) + HypBJet_->at(solutionIndex) ).M(), weight);

    h_HypToppTLead->Fill(LeadHypTop.Pt(), weight);
    h_HypToppTNLead->Fill(NLeadHypTop.Pt(), weight);
    h_HypTopRapidityLead->Fill(LeadHypTop.Rapidity(), weight);
    h_HypTopRapidityNLead->Fill(NLeadHypTop.Rapidity(), weight);
    h_HypTopMassLead->Fill(LeadHypTop.M(), weight);
    h_HypTopMassNLead->Fill(NLeadHypTop.M(), weight);

    h_HypLeptonpTLead->Fill(LeadHypLepton.Pt(), weight);
    h_HypLeptonpTNLead->Fill(NLeadHypLepton.Pt(), weight);
    h_HypLeptonEtaLead->Fill(LeadHypLepton.Eta(), weight);
    h_HypLeptonEtaNLead->Fill(NLeadHypLepton.Eta(), weight);
    
    h_HypBJetpTLead->Fill(LeadHypBJet.Pt(), weight);
    h_HypBJetpTNLead->Fill(NLeadHypBJet.Pt(), weight);
    h_HypBJetEtaLead->Fill(LeadHypBJet.Eta(), weight);
    h_HypBJetEtaNLead->Fill(NLeadHypBJet.Eta(), weight);

    //make sure you have called CreateBinnedControlPlots in the SlaveBegin first
    for (const auto& i : { HypTop_->at(solutionIndex), HypAntiTop_->at(solutionIndex) } ) {
        FillBinnedControlPlot(h_HypToppT, i.Pt(), h_LeptonpT, leptonMinus.Pt(), weight);
        FillBinnedControlPlot(h_HypToppT, i.Pt(), h_LeptonpT, leptonPlus.Pt(), weight);
        FillBinnedControlPlot(h_HypToppT, i.Pt(), h_diLepMassFull, dilepton.M(), weight);
        FillBinnedControlPlot(h_HypToppT, i.Pt(), h_LeptonEta, leptonMinus.Eta(), weight);
        FillBinnedControlPlot(h_HypToppT, i.Pt(), h_LeptonEta, leptonPlus.Eta(), weight);
        FillBinnedControlPlot(h_HypToppT, i.Pt(), h_MET, met_->Pt(), weight);
        
        FillBinnedControlPlot(h_HypTopRapidity, i.Rapidity(), h_LeptonpT, leptonMinus.Pt(), weight);
        FillBinnedControlPlot(h_HypTopRapidity, i.Rapidity(), h_LeptonpT, leptonPlus.Pt(), weight);
        FillBinnedControlPlot(h_HypTopRapidity, i.Rapidity(), h_diLepMassFull, dilepton.M(), weight);
        FillBinnedControlPlot(h_HypTopRapidity, i.Rapidity(), h_LeptonEta, leptonMinus.Eta(), weight);
        FillBinnedControlPlot(h_HypTopRapidity, i.Rapidity(), h_LeptonEta, leptonPlus.Eta(), weight);
        FillBinnedControlPlot(h_HypTopRapidity, i.Rapidity(), h_MET, met_->Pt(), weight);
    }

    if (!isZregion) { //also apply Z cut in emu!
        TTh1_postKinReco->Fill(dilepton.M(), weight);
        Allh1_postKinReco->Fill(dilepton.M(), weight);  //this is also filled in the Z region in the code above
    }

    //=== CUT ===
    //Following histograms only filled for the signal sample
    if (! isSignal_) return kTRUE;

//     if ( GenLepton->Pt() > 20 && GenAntiLepton->Pt() > 20 
//          && abs(GenLepton->Eta()) < 2.4 && abs(GenAntiLepton->Eta()) < 2.4 ) 
//     {
//         //Comment the next 2 lines and uncomment the 3rd one for gen-level Vis PS cuts
//         //if (LVGenBQuark.Pt()>30 && LVGenAntiBQuark.Pt()>30 && abs(LVGenBQuark.Eta())<2.4 && abs(LVGenAntiBQuark.Eta())<2.4){
//         if ( BHadronIndex != -1 && allGenJets->at(BHadronIndex).Pt() > 30 
//             && abs( allGenJets->at(BHadronIndex).Eta() ) < 2.4 
//             && AntiBHadronIndex != -1 && allGenJets->at(AntiBHadronIndex).Pt() > 30 
//             && abs( allGenJets->at(AntiBHadronIndex).Eta() ) < 2.4 ) 
//         {
//             //            if(LVBHadronGenJet.Pt()>30 && abs(LVBHadronGenJet.Eta())<2.4 &&
//             //          LVAntiBHadronGenJet.Pt()>30 && abs(LVAntiBHadronGenJet.Eta())<2.4){
// 
//             h_jetMultiVisTop->Fill(jet->size(), weightLepSF*btagSF*trigEFF*weightKinFit );
//             //!! why these weights? , ah because label of the plot
//         }
//     }
    
    h_GenRecoLeptonEta->Fill(HypLepton_->at(solutionIndex).Eta(), GenLepton_->Eta(), weight );

    h_GenRecoAntiLeptonEta->Fill(HypAntiLepton_->at(solutionIndex).Eta(), GenAntiLepton_->Eta(), weight );
    h_GenRecoLeptonpT->Fill(HypLepton_->at(solutionIndex).Pt(), GenLepton_->Pt(), weight );
    h_GenRecoAntiLeptonpT->Fill(HypAntiLepton_->at(solutionIndex).Pt(), GenAntiLepton_->Pt(), weight );

    h_GenRecoTopRapidity->Fill(HypTop_->at(solutionIndex).Rapidity(), GenTop_->Rapidity(), weight );
    h_GenRecoAntiTopRapidity->Fill(HypAntiTop_->at(solutionIndex).Rapidity(), GenAntiTop_->Rapidity(), weight );
    h_GenRecoToppT->Fill(HypTop_->at(solutionIndex).Pt(), GenTop_->Pt(), weight );
    h_GenRecoAntiToppT->Fill(HypAntiTop_->at(solutionIndex).Pt(), GenAntiTop_->Pt(), weight );
    h_GenRecoMet->Fill(met_->Pt(), GenMet_->Pt(), weight);
    h_GenRecoHT->Fill(jetHT, genHT, weight);
    h_GenRecoNeutrinopT->Fill(HypNeutrino_->at(solutionIndex).Pt(), GenNeutrino_->Pt(), weight);
    h_GenRecoAntiNeutrinopT->Fill(HypAntiNeutrino_->at(solutionIndex).Pt(), GenAntiNeutrino_->Pt(), weight);

    h_GenRecoLLBarDPhi->Fill(
        abs( DeltaPhi( HypLepton_->at(solutionIndex), HypAntiLepton_->at(solutionIndex) ) ), 
        abs( DeltaPhi( *GenLepton_, *GenAntiLepton_ ) ), 
        weight );

    //Begin: find (and fill) the GenReco plots for Leading and NLeading Top, Lepton, BJet
    h_GenRecoToppTLead->Fill(LeadHypTop.Pt(), LeadGenTop.Pt(), weight);
    h_GenRecoToppTNLead->Fill(NLeadHypTop.Pt(), NLeadGenTop.Pt(), weight);
    h_GenRecoTopRapidityLead->Fill(LeadHypTop.Rapidity(), LeadGenTop.Rapidity(), weight);
    h_GenRecoTopRapidityNLead->Fill(NLeadHypTop.Rapidity(), NLeadGenTop.Rapidity(), weight);
    h_GenRecoTopMassLead->Fill(LeadHypTop.M(), LeadGenTop.M(), weight);
    h_GenRecoTopMassNLead->Fill(NLeadHypTop.M(), NLeadGenTop.M(), weight);

    h_GenRecoLeptonpTLead->Fill(LeadHypLepton.Pt(), LeadGenLepton.Pt(), weight);
    h_GenRecoLeptonpTNLead->Fill(NLeadHypLepton.Pt(), NLeadGenLepton.Pt(), weight);
    h_GenRecoLeptonEtaLead->Fill(LeadHypLepton.Eta(), LeadGenLepton.Eta(), weight);
    h_GenRecoLeptonEtaNLead->Fill(NLeadHypLepton.Eta(), NLeadGenLepton.Eta(), weight);
    
    if(BHadronIndex >= 0 && AntiBHadronIndex >= 0){
        h_GenRecoBJetpTLead->Fill(LeadHypBJet.Pt(), LeadGenBJet.Pt(), weight);
        h_GenRecoBJetpTNLead->Fill(NLeadHypBJet.Pt(), NLeadGenBJet.Pt(), weight);
        h_GenRecoBJetEtaLead->Fill(LeadHypBJet.Eta(), LeadGenBJet.Eta(), weight);
        h_GenRecoBJetEtaNLead->Fill(NLeadHypBJet.Eta(), NLeadGenBJet.Eta(), weight);
    }
    else{
        h_GenRecoBJetpTLead->Fill(LeadHypBJet.Pt(), -1000, weight);
        h_GenRecoBJetpTNLead->Fill(NLeadHypBJet.Pt(), -1000, weight);
        h_GenRecoBJetEtaLead->Fill(LeadHypBJet.Eta(), -1000, weight);
        h_GenRecoBJetEtaNLead->Fill(NLeadHypBJet.Eta(), -1000, weight);
    }
    //End: find (and fill) the GenReco plots for Leading and NLeading Leptons

    if ( BHadronIndex>=0 ) {
        h_GenRecoBJetpT->Fill(HypBJet_->at(solutionIndex).Pt(), allGenJets_->at(BHadronIndex).Pt(), weight );
        h_GenRecoBJetRapidity->Fill(HypBJet_->at(solutionIndex).Rapidity(), allGenJets_->at(BHadronIndex).Rapidity(), weight );
        h_GenRecoBJetEta->Fill(HypBJet_->at(solutionIndex).Eta(), allGenJets_->at(BHadronIndex).Eta(), weight );
        h_GenRecoAntiLeptonBjetMass->Fill(( HypAntiLepton_->at(solutionIndex)+HypBJet_->at(solutionIndex) ).M(), ( *GenAntiLepton_+allGenJets_->at(BHadronIndex) ).M(), weight );
    } else {
        h_GenRecoBJetpT->Fill(HypBJet_->at(solutionIndex).Pt(), -1000., weight );
        h_GenRecoBJetRapidity->Fill(HypBJet_->at(solutionIndex).Rapidity(), -1000., weight );
        h_GenRecoBJetEta->Fill(HypBJet_->at(solutionIndex).Eta(), -1000., weight );
        h_GenRecoAntiLeptonBjetMass->Fill(( HypAntiLepton_->at(solutionIndex) + HypBJet_->at(solutionIndex) ).M(), -1000., weight );
    }
    if ( AntiBHadronIndex>=0 ) {
        h_GenRecoAntiBJetpT->Fill(HypAntiBJet_->at(solutionIndex).Pt(), allGenJets_->at(AntiBHadronIndex).Pt(), weight );
        h_GenRecoAntiBJetRapidity->Fill(HypAntiBJet_->at(solutionIndex).Rapidity(), allGenJets_->at(AntiBHadronIndex).Rapidity(), weight );
        h_GenRecoAntiBJetEta->Fill(HypAntiBJet_->at(solutionIndex).Eta(), allGenJets_->at(AntiBHadronIndex).Eta(), weight );
        h_GenRecoLeptonantiBjetMass->Fill(( HypLepton_->at(solutionIndex) + HypAntiBJet_->at(solutionIndex) ).M(), ( *GenLepton_+allGenJets_->at(AntiBHadronIndex) ).M(), weight );
    } else {
        h_GenRecoAntiBJetpT->Fill(HypAntiBJet_->at(solutionIndex).Pt(), -1000., weight );
        h_GenRecoAntiBJetRapidity->Fill(HypAntiBJet_->at(solutionIndex).Rapidity(), -1000., weight );
        h_GenRecoAntiBJetEta->Fill(HypAntiBJet_->at(solutionIndex).Eta(), -1000., weight );
        h_GenRecoLeptonantiBjetMass->Fill(( HypLepton_->at(solutionIndex) + HypAntiBJet_->at(solutionIndex) ).M(), -1000., weight );
    }
    
//     int firstGenJet = -1, secondGenJet = -1;
//     int firstHypJet = -1, secondHypJet = -1;
//     for(int k=0; k<allGenJets->size(); k++){
//         if(abs(allGenJets->at(k).Eta())>2.4 || allGenJets->at(k).Pt()< 30.0) {continue;}
//         if(firstGenJet<0) {
//             firstGenJet=k;
//             continue;//jump to next iteration k -> k+1
//         }
//         if(firstGenJet>=0 && secondGenJet<0){
//             secondGenJet=k;
//             break; //exit 'for' loop, found interesting 1st and 2nd jets
//         }
//     }
//     for(int k=0; k<jet.size(); k++){
//         if(abs(jet->at(k).Eta())>2.4 || jet->at(k).Pt()< 30.0) {continue;}
//         if(firstHypJet<0) {
//             firstHypJet=k;
//             continue;//jump to next iteration k -> k+1
//         }
//         if(firstHypJet>=0 && secondHypJet<0){
//             secondHypJet=k;
//             break; //exit 'for' loop, found interesting 1st and 2nd jets
//         }
//     }
//     if(firstGenJet >=0 && secondGenJet>=0 && firstHypJet >=0 && secondHypJet >=0 ){
//         h_GenRecoLeadingJetpT->Fill(jet->at(firstHypJet).Pt(), allGenJets->at(firstGenJet).Pt(),weight);
//         h_GenRecoLeadingJetEta->Fill(jet->at(firstHypJet).Eta(), allGenJets->at(firstGenJet).Eta(),weight);
//         h_GenRecoNLeadingJetpT->Fill(jet->at(secondHypJet).Pt(), allGenJets->at(secondGenJet).Pt(),weight);
//         h_GenRecoNLeadingJetEta->Fill(jet->at(secondHypJet).Eta(), allGenJets->at(secondGenJet).Eta(),weight);
//     }
    
    if ( BHadronIndex>=0 && AntiBHadronIndex>=0 ) {
        h_GenRecoJetMult->Fill(jets_->size(), allGenJets_->size(), weight );
    } else {
        h_GenRecoJetMult->Fill(jets_->size(), -1000., weight );
    }

    LV genllbar(*GenLepton_ + *GenAntiLepton_);
    h_GenRecoLLBarMass->Fill(hypllbar.M(), genllbar.M(), weight );
    h_GenRecoLLBarpT->Fill(hypllbar.Pt(), genllbar.Pt(), weight );

    LV genttbar(*GenTop_ + *GenAntiTop_);
    h_GenRecoTTBarMass->Fill(hypttbar.M(), genttbar.M(), weight );
    h_GenRecoTTBarpT->Fill(hypttbar.Pt(), genttbar.Pt(), weight );
    h_GenRecoTTBarRapidity->Fill(hypttbar.Rapidity(), genttbar.Rapidity(), weight );

    return kTRUE;
}


double TopAnalysis::calculateClosureTestWeight()
{
    double weight = closureFunction_();
    h_ClosureTotalWeight->Fill(1, weight);
    return weight;
}

void TopAnalysis::SetClosureTest(TString closure, double slope)
{
    if (closure == "") {
        doClosureTest_ = false;
    } else {
        doClosureTest_ = true;
        if (closure == "pttop") {
            closureFunction_ = [&,slope](){
                return std::max((1+(GenTop_->Pt()-100)*slope)
                               *(1+(GenAntiTop_->Pt()-100)*slope) , 0.1);
            };
        } else if (closure == "ytop") {
            closureFunction_ = [&,slope](){
                return std::max((1+(abs(GenTop_->Rapidity())-1)*slope)
                               *(1+(abs(GenAntiTop_->Rapidity()-1))*slope) , 0.1);
            };
        } if (closure == "nominal") {
            closureFunction_ = [](){return 1.;};
        } else {
            std::cerr << "invalid closure test function\n";
            exit(1);
        }            
        if (closure != "nominal") {
            outputfilename_.ReplaceAll(".root", TString::Format("_fakerun_%s%.3f.root", closure.Data(), slope));
        } else {
            outputfilename_.ReplaceAll(".root", TString::Format("_fakerun_%s.root", closure.Data()));
        }
        std::cout << "<<< Closure test. Writing to: " << outputfilename_ << "\n";
        //BRANCHING FRACTION
        double br = 0;
        if (channelPdgIdProduct_ == -11*11 || channelPdgIdProduct_ == -13*13) br = 0.01166;
        else if (channelPdgIdProduct_ == -11*13) br = 0.02332;
        else {
            std::cerr << "closure test channel invalid\n"; exit(1);
        }            
        closureMaxEvents_ = TOPXSEC * 1000 * LUMI * br;
        samplename_.Append("_fakedata");
    }
}

