#include "basicFunctionsEff.h"

void analyzeCutflowWithAnalyzers(bool save=false)
{
  gStyle->SetOptStat(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetPadBottomMargin(0.11);
  gStyle->SetLabelSize(0.05,"XY");
  gStyle->SetTitleSize(0.05,"XY");
  gStyle->SetFillColor(0);
  
  
  /// path where input files are stored
  TString inputPathScratch  ="/scratch/hh/current/cms/user/jlange/output_4_2_4/fullLeptonic";
  TString inputPath42       ="/afs/naf.desy.de/user/j/jlange/nafscratch/top/CMSSW_4_2_4/src/TopAnalysis/Configuration/analysis/fullLeptonic";
  
  TString outputFolder   = "/afs/desy.de/user/j/jlange/analysis/tagAndProbe/plots/CutStudiesForTrigger";
  TString outputFileName = "/cutStudiesDifferentPU_";
  
  TString fileFormat = "png";
  
  
  TFile* file= new TFile(inputPath42+"/naf_analyzeCutflowWithAnalyzers_cfg/analyzeCutflowWithAnalyzers_MinJet4_pt30_MuPt20.root");
  file->cd();
  
  TTree *tJet = (TTree*) file->Get("analyzeJetAllTrig2AfterCut/tree")->Clone();
  tJet->AddFriend("tMu = analyzeMuonKinematicsTrig2/tree");
  
  TCut cutPtMu  = "tMu.pt>30";
  TCut cutPtJet = "pt1>35 && pt2>35 && pt3>35 && pt4>35";
  TCut cutPtMuJet = cutPtMu && cutPtJet;
  
  /// calculate efficiencies
  // no PUrew
  double NeventIni = 1000000.;
  double NmuPt20_minJet4pt30 = (double)tJet->GetEntries();
  double NmuPt23_minJet4pt30 = (double)tJet->GetEntries("tMu.pt>23");
  double NmuPt30_minJet4pt30 = (double)tJet->GetEntries("tMu.pt>30");
//   double NmuPt20_minJet4pt35 = (double)tJet->GetEntries("pt1>35 && pt2>35 && pt3>35 && pt4>35");
//   double NmuPt23_minJet4pt35 = (double)tJet->GetEntries("pt1>35 && pt2>35 && pt3>35 && pt4>35 && tMu.pt>23");
//   double NmuPt23_minJet4pt1_65 = (double)tJet->GetEntries("pt1>65 && pt2>50 && pt3>35 && pt4>20 && tMu.pt>23");
//   double NmuPt30_minJet4pt1_65 = (double)tJet->GetEntries("pt1>65 && pt2>50 && pt3>35 && pt4>20 && tMu.pt>30");
  double NmuPt20_minJet4pt35 = (double)tJet->GetEntries("pt1>35 && pt2>35 && pt3>35 && pt4>35");
  double NmuPt23_minJet4pt35 = (double)tJet->GetEntries("pt1>35 && pt2>35 && pt3>35 && pt4>35 && tMu.pt>23");
  double NmuPt23_minJet4pt1_65 = (double)tJet->GetEntries("pt1>65 && pt2>50 && pt3>35 && pt4>30 && tMu.pt>23");
  double NmuPt30_minJet4pt1_65 = (double)tJet->GetEntries("pt1>65 && pt2>50 && pt3>35 && pt4>30 && tMu.pt>30");
  double NmuPt30_minJet4pt1_50 = (double)tJet->GetEntries("pt1>50 && pt2>40 && pt3>35 && pt4>30 && tMu.pt>30");
  
  double NmuPt20_minJet4pt30_PUlo = (double)tJet->GetEntries("pv<10");
  double NmuPt20_minJet4pt30_PUhi = (double)tJet->GetEntries("pv>10");
  
  std::cout<<"NeventIni= "<<NeventIni<<std::endl;
  std::cout<<"NmuPt20_minJet4pt30= "<<NmuPt20_minJet4pt30<<std::endl;
  std::cout<<"NmuPt23_minJet4pt30= "<<NmuPt23_minJet4pt30<<std::endl;
  std::cout<<"NmuPt30_minJet4pt30= "<<NmuPt30_minJet4pt30<<std::endl;
  std::cout<<"NmuPt20_minJet4pt35= "<<NmuPt20_minJet4pt35<<std::endl;
  std::cout<<"NmuPt23_minJet4pt35= "<<NmuPt23_minJet4pt35<<std::endl;
  std::cout<<"NmuPt23_minJet4pt1_65= "<<NmuPt23_minJet4pt1_65<<std::endl;
  std::cout<<"NmuPt30_minJet4pt1_65= "<<NmuPt30_minJet4pt1_65<<std::endl;
  std::cout<<"NmuPt30_minJet4pt1_50= "<<NmuPt30_minJet4pt1_50<<std::endl;
  
  std::cout<<"eff muPt>20 minJet4pt>30 wrt NeventIni "<< NmuPt20_minJet4pt30/NeventIni <<std::endl;
  std::cout<<"eff muPt>23 minJet4pt>30 wrt NeventIni "<< NmuPt23_minJet4pt30/NeventIni <<std::endl;
  std::cout<<"eff muPt>30 minJet4pt>30 wrt NeventIni "<< NmuPt30_minJet4pt30/NeventIni <<std::endl;
  std::cout<<"eff muPt>20 minJet4pt>35 wrt NeventIni "<< NmuPt20_minJet4pt35/NeventIni <<std::endl;
  std::cout<<"eff muPt>23 minJet4pt>35 wrt NeventIni "<< NmuPt23_minJet4pt35/NeventIni <<std::endl;
  std::cout<<"eff muPt>23 minJet4pt1_65 wrt NeventIni "<< NmuPt23_minJet4pt1_65/NeventIni <<std::endl;
  std::cout<<std::endl;
  std::cout<<"eff muPt>30 minJet4pt1_65 wrt NeventIni "<< NmuPt30_minJet4pt1_65/NeventIni <<std::endl;
  std::cout<<std::endl;
  std::cout<<"eff muPt>30 minJet4pt1_50 wrt NeventIni "<< NmuPt30_minJet4pt1_50/NeventIni <<std::endl;
  std::cout<<std::endl;
  
  std::cout<<"eff muPt>23 minJet4pt>30 wrt muPt>20 minJet4pt>30 "<< NmuPt23_minJet4pt30/NmuPt20_minJet4pt30 <<std::endl;
  std::cout<<"eff muPt>30 minJet4pt>30 wrt muPt>20 minJet4pt>30 "<< NmuPt30_minJet4pt30/NmuPt20_minJet4pt30 <<std::endl;
  std::cout<<"eff muPt>20 minJet4pt>35 wrt muPt>20 minJet4pt>30 "<< NmuPt20_minJet4pt35/NmuPt20_minJet4pt30 <<std::endl;
  std::cout<<"eff muPt>23 minJet4pt>35 wrt muPt>20 minJet4pt>30 "<< NmuPt23_minJet4pt35/NmuPt20_minJet4pt30 <<std::endl;
  std::cout<<"eff muPt>23 minJet4pt1_65 wrt muPt>20 minJet4pt>30 "<< NmuPt23_minJet4pt1_65/NmuPt20_minJet4pt30 <<std::endl;
  std::cout<<"eff muPt>30 minJet4pt1_65 wrt muPt>20 minJet4pt>30 "<< NmuPt30_minJet4pt1_65/NmuPt20_minJet4pt30 <<std::endl;
  std::cout<<"eff muPt>30 minJet4pt1_50 wrt muPt>20 minJet4pt>30 "<< NmuPt30_minJet4pt1_50/NmuPt20_minJet4pt30 <<std::endl;
  
  // with PUrew
//   std::cout<<"--------------------------------------------"<<std::endl;
//   std::cout<<"!!! PU rew !!! "<<NeventIni<<std::endl;
//   NeventIni = 1000000.;
//   NmuPt20_minJet4pt30 = (double)tJet->GetEntries("weight");
//   NmuPt23_minJet4pt30 = (double)tJet->GetEntries("weight*(tMu.pt>23)");
//   NmuPt20_minJet4pt35 = (double)tJet->GetEntries("weight*(pt1>35 && pt2>35 && pt3>35 && pt4>35)");
//   NmuPt23_minJet4pt35 = (double)tJet->GetEntries("weight*(pt1>35 && pt2>35 && pt3>35 && pt4>35 && tMu.pt>23)");
//   
//   std::cout<<"NeventIni= "<<NeventIni<<std::endl;
//   std::cout<<"NmuPt20_minJet4pt30= "<<NmuPt20_minJet4pt30<<std::endl;
//   std::cout<<"NmuPt23_minJet4pt30= "<<NmuPt23_minJet4pt30<<std::endl;
//   std::cout<<"NmuPt20_minJet4pt35= "<<NmuPt20_minJet4pt35<<std::endl;
//   std::cout<<"NmuPt23_minJet4pt35= "<<NmuPt23_minJet4pt35<<std::endl;
//   
//   std::cout<<"eff muPt>20 minJet4pt>30 wrt NeventIni "<< NmuPt20_minJet4pt30/NeventIni <<std::endl;
//   std::cout<<"eff muPt>23 minJet4pt>30 wrt NeventIni "<< NmuPt23_minJet4pt30/NeventIni <<std::endl;
//   std::cout<<"eff muPt>20 minJet4pt>35 wrt NeventIni "<< NmuPt20_minJet4pt35/NeventIni <<std::endl;
//   std::cout<<"eff muPt>23 minJet4pt>35 wrt NeventIni "<< NmuPt23_minJet4pt35/NeventIni <<std::endl;
//   std::cout<<std::endl;
//   
//   std::cout<<"eff muPt>23 minJet4pt>30 wrt muPt>20 minJet4pt>30 "<< NmuPt23_minJet4pt30/NmuPt20_minJet4pt30 <<std::endl;
//   std::cout<<"eff muPt>20 minJet4pt>35 wrt muPt>20 minJet4pt>30 "<< NmuPt20_minJet4pt35/NmuPt20_minJet4pt30 <<std::endl;
//   std::cout<<"eff muPt>23 minJet4pt>35 wrt muPt>20 minJet4pt>30 "<< NmuPt23_minJet4pt35/NmuPt20_minJet4pt30 <<std::endl;
  
      
//   tJet->Scan("*", "","",10,10);
//   tJet->Scan("*", cutPtMu,"",10,10);
//   tJet->Scan("*", cutPtJet,"",10,10);
  
  TCanvas* canv1=new TCanvas("c","c",1);
  canv1->cd();
  //tree -> Draw("probePt>>hnew(30,0,150)", "", "", 100);
  tJet -> Draw("tMu.pt>>hnew1(30,0,150)", cutPtJet);
  TCanvas* canv2=new TCanvas("c2","c2",1);
  canv2->cd();
  tJet -> Draw("pt1>>hnew2(30,0,150)",cutPtJet);
  
  /// ------------------------------------------------------------------------------  
  /// map with structure that keeps features of methods, ignore file, filename=""
  /// use source for cuts
  std::map<TString, method*> method_;
  
  TString mIDarr []= {"m1", "m2", "m3", "m4"};
  //TString mIDarr []= {"m1", "m2", "m3", "m4","m5","m6","m7","m8"};
  std::vector<TString> mID(mIDarr, mIDarr + sizeof(mIDarr)/sizeof(TString));
  int mIDNum = mID.size();
  std::cout<< "Number of considered methods (i.e. cuts): " <<  mIDNum << std::endl;
  
  /// Constructor for struct method(TString iniFileName, TString iniLegName, int iniLineStyle, int iniLineColor, int iniMarkerStyle, int iniMarkerColor, TString iniDrawOpt, TString iniLepOpt, TString source)
  
  // no PUrew
  method_["m1"] = new method("", "p_{T}(mu)>20, p_{T}(jet)>30", 1, 1, 1, 2, "", "L","tree");
  method_["m2"] = new method("", "p_{T}(mu)>30, p_{T}(jet)>30", 1, 2, 1, 2, "same", "L", "tree",cutPtMu);
  method_["m3"] = new method("", "p_{T}(mu)>20, p_{T}(jet)>35", 1, 3, 1, 2, "same", "L","tree",cutPtJet);
  method_["m4"] = new method("", "p_{T}(mu)>30, p_{T}(jet)>35", 1, 4, 1, 2, "same", "L","tree",cutPtMuJet);
  // with PUrew
  method_["m5"] = new method("", "", 2, 1, 1, 2, "same", "","treeWeight");
  method_["m6"] = new method("", "", 2, 2, 1, 2, "same", "", "treeWeight",cutPtMu);
  method_["m7"] = new method("", "", 2, 3, 1, 2, "same", "","treeWeight",cutPtJet);
  method_["m8"] = new method("", "", 2, 4, 1, 2, "same", "","treeWeight",cutPtMuJet);
  
//    // no PUrew
//   method_["m1"] = new method("", "no PU reweighting", 1, 1, 1, 2, "", "L","tree");
//   method_["m2"] = new method("", "", 1, 2, 1, 2, "same", "", "tree",cutPtMu);
//   method_["m3"] = new method("", "", 1, 3, 1, 2, "same", "","tree",cutPtJet);
//   method_["m4"] = new method("", "", 1, 4, 1, 2, "same", "","tree",cutPtMuJet);
//   // with PUrew
//   method_["m5"] = new method("", "PU reweighting (first 1 fb^{-1})", 2, 1, 1, 2, "same", "L","treeWeight");
//   method_["m6"] = new method("", "", 2, 2, 1, 2, "same", "", "treeWeight",cutPtMu);
//   method_["m7"] = new method("", "", 2, 3, 1, 2, "same", "","treeWeight",cutPtJet);
//   method_["m8"] = new method("", "", 2, 4, 1, 2, "same", "","treeWeight",cutPtMuJet);
  
//   method_["m1"] = new method("", "no PU reweighting", 1, 1, 1, 2, "", "L","tree","1/NmuPt20_minJet4pt30");
//   method_["m2"] = new method("", "PU reweighting (first 1 fb^{-1}", 1, 2, 1, 2, "same", "L", "treeWeight");
//   method_["m3"] = new method("", "low PU N_{PV}<10", 1, 3, 1, 2, "same", "L","tree","pv<10");
//   method_["m4"] = new method("", "high PU N_{PV}>10", 1, 4, 1, 2, "same", "L","tree","pv>10");
  
  /// draw with the help of efficiency structure
  // variables to be plotted
  TString effIDarr[]      = {"muPt", "muEta", "jet1Pt", "jet2Pt", "jet3Pt", "jet4Pt", "jet1Eta", "jet2Eta", "jet3Eta", "jet4Eta"};
  std::vector<TString> effID(effIDarr, effIDarr + sizeof(effIDarr)/sizeof(TString));
  int effIDNum = effID.size();
  std::cout<< "Number of considered plots: " <<  effIDNum << std::endl;
  
  /// map with structure that keeps features of histograms
  std::map<TString, eff*> eff_;
  
  /// title for histo, x and y axis (separated by "/")
  TString title ="";
  TString title0 ="t#bar{t} Summer11 sample, 10^{6} events";
  
  double yLoEta=0; 
  double yHiEta=12000;
  
//   int mBinsPt0     = 60;
//   int mBinsEta0    = -1;
//   
//   double binsPt0[]     = {  0., 300. };
//   std::vector<double> binsPt0_(binsPt0, binsPt0 + sizeof(binsPt0)/sizeof(double));
//   double binsEta0[]    = { -2.4,-2.1,-1.65,-1.2,-0.9,-0.45,0.,0.45,0.9,1.2,1.65,2.1,2.4 };
//   std::vector<double> binsEta0_(binsEta0, binsEta0 + sizeof(binsEta0)/sizeof(double));
  
  int mBinsPt0     = 240;
  int mBinsEta0    = 120;
  
  double binsPt0[]     = {  0., 300. };
  std::vector<double> binsPt0_(binsPt0, binsPt0 + sizeof(binsPt0)/sizeof(double));
  double binsEta0[]    = { -2.4,2.4 };
  std::vector<double> binsEta0_(binsEta0, binsEta0 + sizeof(binsEta0)/sizeof(double));
  
  /// Constructor for struct eff(TString iniVar, TCut iniCuts, TString iniBins, TString iniTitles, double iniYLo=-9999., double iniYHi=-9999., double iniXLo=-9999., double iniXHi=-9999.)
  title = title0+"/ p_{T}(mu) / ";
  eff_["muPt"] =new eff("tMu.pt", "", mBinsPt0, binsPt0_, title,0,5000);
  title = title0+"/ #eta(mu) / ";
  eff_["muEta"] =new eff("tMu.eta", "", mBinsEta0, binsEta0_, title,yLoEta,yHiEta);
  title = title0+"/ p_{T}(jet 1) / ";
  eff_["jet1Pt"] =new eff("pt1", "", mBinsPt0, binsPt0_, title,0,3000);
  title = title0+"/ p_{T}(jet 2) / ";
  eff_["jet2Pt"] =new eff("pt2", "", mBinsPt0, binsPt0_, title,0,5000);
  title = title0+"/ p_{T}(jet 3) / ";
  eff_["jet3Pt"] =new eff("pt3", "", mBinsPt0, binsPt0_, title,0,7000);
  title = title0+"/ p_{T}(jet 4) / ";
  eff_["jet4Pt"] =new eff("pt4", "", mBinsPt0, binsPt0_, title,0,13000);
  title = title0+"/ #eta(jet 1) / ";
  eff_["jet1Eta"] =new eff("eta1", "", mBinsEta0, binsEta0_, title,yLoEta,yHiEta);
  title = title0+"/ #eta(jet 2) / ";
  eff_["jet2Eta"] =new eff("eta2", "", mBinsEta0, binsEta0_, title,yLoEta,yHiEta);
  title = title0+"/ #eta(jet 3) / ";
  eff_["jet3Eta"] =new eff("eta3", "", mBinsEta0, binsEta0_, title,yLoEta,yHiEta);
  title = title0+"/ #eta(jet 4) / ";
  eff_["jet4Eta"] =new eff("eta4", "", mBinsEta0, binsEta0_, title,yLoEta,yHiEta);
  
  /// PU reweightung
  TString PU;
  
  /// ---
  /// get histos from tree
  ///  ---
  for(int iMethod=0; iMethod<mIDNum; iMethod++){
    for(int iEff=0; iEff<effIDNum; iEff++){
      getHisto(eff_[effID[iEff]]->his[mID[iMethod]], eff_[effID[iEff]]->var, tJet, eff_[effID[iEff]]->binMode, eff_[effID[iEff]]->bins, method_[mID[iMethod]]->cuts, method_[mID[iMethod]]->source);
      
      setHistoStyle(eff_[effID[iEff]]->his[mID[iMethod]], eff_[effID[iEff]]->titles, method_[mID[iMethod]]->lineStyle, method_[mID[iMethod]]->lineColor, method_[mID[iMethod]]->markerStyle, method_[mID[iMethod]]->markerColor, eff_[effID[iEff]]->yLo, eff_[effID[iEff]]->yHi);
    }
  }
  
  /// Draw Canvas 
  TCanvas* CanvMu= new TCanvas("CanvMu", "CanvMu", 1280,900);
  TCanvas* CanvJetPt= new TCanvas("CanvJetPt", "CanvJetPt", 1280,900);
  TCanvas* CanvJetEta= new TCanvas("CanvJetEta", "CanvJetEta", 1280,900);

  CanvMu->Divide(2,2);
  CanvJetPt->Divide(2,2);
  CanvJetEta->Divide(2,2);
  
  CanvMu->cd(1);
  drawEfficiencies(eff_["muPt"], method_, mID, 0.45,0.6,0.85,0.85);
  CanvMu->cd(2);
  drawEfficiencies(eff_["muEta"], method_, mID, 0.45,0.6,0.85,0.85);
  
  CanvJetPt->cd(1);
  drawEfficiencies(eff_["jet1Pt"], method_, mID, 0.45,0.6,0.85,0.85);
  CanvJetPt->cd(2);
  drawEfficiencies(eff_["jet2Pt"], method_, mID, 0.45,0.6,0.85,0.85);
  CanvJetPt->cd(3);
  drawEfficiencies(eff_["jet3Pt"], method_, mID, 0.45,0.6,0.85,0.85);
  CanvJetPt->cd(4);
  drawEfficiencies(eff_["jet4Pt"], method_, mID, 0.45,0.6,0.85,0.85);
  
  CanvJetEta->cd(1);
  drawEfficiencies(eff_["jet1Eta"], method_, mID, 0.45,0.6,0.85,0.85);
  CanvJetEta->cd(2);
  drawEfficiencies(eff_["jet2Eta"], method_, mID, 0.45,0.6,0.85,0.85);
  CanvJetEta->cd(3);
  drawEfficiencies(eff_["jet3Eta"], method_, mID, 0.45,0.6,0.85,0.85);
  CanvJetEta->cd(4);
  drawEfficiencies(eff_["jet4Eta"], method_, mID, 0.45,0.6,0.85,0.85);
  
  // make studies of integral for shape uncertainties
  // load b-jets
//   TFile* fileBjet= new TFile(inputPath42+"/../semiLeptonic/diffXSection/naf_analyzeBTagEfficiency_cfg_new/analyzeBTagEfficiency.root");
//   fileBjet->cd();
//   TH1F* hisBjet= (TH1F*) fileBjet->Get("bTagEff/NumBJetsEta")->Clone();
//   
//   double* integral = hisBjet->GetIntegral();
//   int binsNum = hisBjet->GetNbinsX();
//   
//   for(int iBin = 0; iBin < binsNum+1; iBin++){
//     std::cout<<"Bin=" << iBin << "; binCenter=" << hisBjet->GetBinCenter(iBin) << "; cum. int.=" << integral[iBin] << std::endl;
//   }
  
  TString methodChoice="m2";
  TString effChoice="muEta";
  double* muIntegral = eff_[effChoice]->his[methodChoice]->GetIntegral();
  int muBinsNum = eff_[effChoice]->his[methodChoice]->GetNbinsX();
  
  for(int iBin = 0; iBin < muBinsNum+1; iBin++){
    std::cout<<"Bin=" << iBin << "; binCenter=" << eff_[effChoice]->his[methodChoice]->GetBinCenter(iBin) << "; cum. int.=" << muIntegral[iBin] << std::endl;
  }
  
  
  
  if(save){
    CanvMu->cd(1)->Print(outputFolder+outputFileName+"muPt."+fileFormat);
    CanvMu->cd(2)->Print(outputFolder+outputFileName+"muEta."+fileFormat);
    
    CanvJetPt->Print(outputFolder+outputFileName+"jetPt_overview."+fileFormat);
    CanvJetEta->Print(outputFolder+outputFileName+"jetEta_overview."+fileFormat);
    std::cout<<"Canvas with plots is saved in "<<outputFolder<<std::endl;
  }
  
}