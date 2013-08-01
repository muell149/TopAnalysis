#include "basicFunctions.h"

void btagEfficiencyComparison()
{
  /// set style
  gStyle->SetOptStat(0);
  gStyle->SetPadLeftMargin(0.15);

  /// list of generators
  std::vector<std::string> generator_;
  generator_.push_back("MadGraph");
  generator_.push_back("MCatNLO");
  generator_.push_back("Powheg");

  /// input files
  TString folderName = "/afs/naf.desy.de/user/h/henderle/myscratch/testRun/CMSSW_5_3_5/src/TopAnalysis/Configuration/";
  std::vector<TFile*> inputFile_;
  inputFile_.push_back(new TFile(folderName+"data/analyzeBTagEfficiency2012.root", "READ"));
  for(unsigned int i=1; i<generator_.size(); i++){
    inputFile_.push_back(new TFile(folderName+"analysis/semiLeptonic/diffXSection/naf_bTagEff"+generator_[i]+"/analyzeBTagEfficiency.root", "READ"));
  }

  /// jet types
  std::vector<std::string> jetType_;
  jetType_.push_back("BJets");
  jetType_.push_back("CJets");
  jetType_.push_back("LJets");
  std::vector<TString> jetName_;
  jetName_.push_back("b jets");
  jetName_.push_back("c jets");
  jetName_.push_back("light jets");

  /// getting efficiency histos from input files
  std::map<std::string, TH1F*> effHists_;
  for(unsigned int iJet=0; iJet<jetType_.size(); iJet++){
    for(unsigned int i=0; i<generator_.size(); i++){
    effHists_["Num"+jetType_[iJet]+"Pt"+generator_[i]]       = (TH1F*) inputFile_[i]->Get("bTagEff/Num"+(TString)jetType_[iJet]+"Pt")->Clone();
    effHists_["Num"+jetType_[iJet]+"TaggedPt"+generator_[i]] = (TH1F*) inputFile_[i]->Get("bTagEff/Num"+(TString)jetType_[iJet]+"TaggedPt")->Clone();
    effHists_["Eff"+jetType_[iJet]+"TaggedPt"+generator_[i]] = (TH1F*) inputFile_[i]->Get("bTagEff/Eff"+(TString)jetType_[iJet]+"TaggedPt")->Clone();

    effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[i])->second->Reset();
    effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[i])->second->Divide(effHists_.find("Num"+jetType_[iJet]+"TaggedPt"+generator_[i])->second, 
										      effHists_.find("Num"+jetType_[iJet]+"Pt"+generator_[i])->second,1,1,"B");
    }// end generator loop
  }// end jet-type loop

  /// canvases
  std::vector<TCanvas*> canv_;
  addCanvas(canv_);addCanvas(canv_);addCanvas(canv_);
    
  /// create legend
  TLegend *leg = new TLegend(0.18, 0.37, 0.53, 0.57);
  leg->SetTextFont(42);
  legendStyle(*leg,"Generator",0.04);
  for(unsigned int i=0; i<generator_.size(); i++){
    if(generator_[i]=="MadGraph"||generator_[i]=="Powheg")leg ->AddEntry(effHists_.find("EffBJetsTaggedPt"+generator_[i])->second, (TString)generator_[i]+"(+Pythia)","L");
    if(generator_[i]=="MCatNLO")leg ->AddEntry(effHists_.find("EffBJetsTaggedPt"+generator_[i])->second, "MC@NLO(+Herwig)","L");
  }

  /// plot efficiencies
  for(unsigned int iJet=0; iJet<jetType_.size(); iJet++){
    canv_[iJet]->cd();
    
    /// take care of maximum
    double max=0.; double maximum=0.;
    for(unsigned int i=0; i<generator_.size(); i++){
      effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[i])->second->GetXaxis()->SetRangeUser(0,999);
      max = effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[i])->second->GetMaximum();
      if(max>maximum)maximum=max;
    }

    axesStyle(*effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[0])->second,"p_{T} [GeV]","efficiency",0,1.1*maximum);
    effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[0])->second->SetTitle("tag efficiency CSVM ("+jetName_[iJet]+")");
    effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[0])->second->GetXaxis()->SetTitleSize(0.045);
    effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[0])->second->GetXaxis()->SetLabelSize(0.045);
    effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[0])->second->GetXaxis()->SetTitleOffset(1.1);
    effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[0])->second->GetYaxis()->SetTitleSize(0.045);
    effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[0])->second->GetYaxis()->SetLabelSize(0.045);
    effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[0])->second->GetYaxis()->SetTitleOffset(1.5);
    effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[0])->second->GetXaxis()->SetNdivisions(505);
    for(unsigned int i=0; i<generator_.size(); i++){
      effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[i])->second->SetLineColor(TMath::Power(2.,(int)i));
      effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[i])->second->SetLineStyle(i);
      effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[i])->second->SetLineWidth(2);

      if(i==0)effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[i])->second->Draw("");
      else effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[i])->second->Draw("same");
    }
    leg->Draw("same");
    std::vector<double> err1_;
    std::vector<double> err2_;
    for(int bin=1; bin<=effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[0])->second->GetNbinsX(); bin++){
      err1_.push_back((effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[1])->second->GetBinContent(bin)/effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[0])->second->GetBinContent(bin))*sqrt(TMath::Power(effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[1])->second->GetBinError(bin)/effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[1])->second->GetBinContent(bin),2)+TMath::Power(effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[0])->second->GetBinError(bin)/effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[0])->second->GetBinContent(bin),2)));
      err2_.push_back((effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[2])->second->GetBinContent(bin)/effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[0])->second->GetBinContent(bin))*sqrt(TMath::Power(effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[2])->second->GetBinError(bin)/effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[2])->second->GetBinContent(bin),2)+TMath::Power(effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[0])->second->GetBinError(bin)/effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[0])->second->GetBinContent(bin),2)));
    }
    drawRatio(effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[1])->second,effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[0])->second,0.7,1.3,*gStyle,0,err1_,"#varepsilon(Generator)","#varepsilon(MadGraph)","e",2);
    drawRatio(effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[2])->second,effHists_.find("Eff"+jetType_[iJet]+"TaggedPt"+generator_[0])->second,0.4,1.6,*gStyle,0,err2_,"","","esame",4);
  }

}
