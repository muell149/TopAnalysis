#include "plotterclass.h"

#include <fstream>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <cmath>

#include <TCanvas.h>
#include <TLegend.h>
#include <TSystem.h>
#include <TExec.h>
#include <TStyle.h>
#include <TMath.h>
#include <TROOT.h>
#include <TGraphErrors.h>
#include <THStack.h>
#include <TFile.h>
#include <TString.h>
#include <TH1.h>

// HIGGSING
//#include "utils.h"
#include "../diLeptonic/utils.h"
#include "TGaxis.h"
#include "TPaveText.h"
// ENDHIGGSING
  
  // DAVID
// HIGGSING
//#include "../diLeptonic/DilepSVDFunctions.h"
// ENDHIGGSING

using namespace std;

const double Plotter::topxsec = 253.849; //again changes with normalization, must be set outside of the class

void Plotter::setLumi(double newLumi)
{
    this->lumi = newLumi;
}



void Plotter::preunfolding(TString Channel, TString Systematic)
{
    write(Channel, Systematic);
}


void Plotter::DYScaleFactor(TString SpecialComment){

    DYScale = {1,1,1,1}; 

    if(!doDYScale) return; //need to make a switch for control plots that don't want DYScale

    TString nameAppendix = "";
    if ( !SpecialComment.BeginsWith("_post") &&  SpecialComment != "Standard" ){
        cout<<"\n\n*******************************************************************"<<endl;
        cout<<"ERROR: When calculating the DY Scale factor you must specify in which step you want to calculate the DY SF:"<<endl;
        cout<<" '_postZcut', '_post2jets', '_postMET', '_post1btag', '_postKinReco' or 'Standard' = _postKinReco"<<endl;
        cout<<"*******************************************************************\n\n"<<endl;
        exit(444);
    }
    if (SpecialComment.BeginsWith("_post")){
        nameAppendix = SpecialComment;
    } else if ( SpecialComment == "Standard") {
        nameAppendix = "_postKinReco";
    }

    cout<<"\n\nBegin DYSCALE FACTOR calculation at selection step "<<nameAppendix<<endl;
    
    vector<TString> Vec_Files = InputFileList("combined", "Nominal");//Read the hardcoded list of files
    if(Vec_Files.size()<1) {cout<<"WARNING(in DYScaleFactor)!!! No datasets available to calculate DY SF. EXITING!!"<<endl; return;}
    
    double NoutEEDYMC=0, NinEEDYMC=0, NoutMuMuDYMC=0, NinMuMuDYMC=0;//Number of events in/out of z-veto region for the DY MC
    double NinEE=0, NinMuMu=0, NinEMu=0;//Number of events in z-veto region for data
    double NinEEloose=0, NinMuMuloose=0;//Number of data events in Z-Veto region with MET cut
    double NinEEMC=0, NinMuMuMC=0;//All other MC events

    for(size_t i=0; i < Vec_Files.size(); i++){
        double LumiWeight = CalcLumiWeight(Vec_Files.at(i));
        double allWeights=LumiWeight;//calculate here all the flat-weights we apply: Lumi*others*...
        if(Vec_Files.at(i).Contains("ee") || Vec_Files.at(i).Contains("mumu")){
            if(Vec_Files.at(i).Contains("run")){
                TH1D *htemp = fileReader->GetClone<TH1D>(Vec_Files.at(i), TString("Zh1").Append(nameAppendix));
                TH1D *htemp1 = fileReader->GetClone<TH1D>(Vec_Files.at(i), "Looseh1");
                ApplyFlatWeights(htemp, allWeights);
                ApplyFlatWeights(htemp1, allWeights);
                if(Vec_Files.at(i).Contains("ee")){
                    NinEE+=htemp->Integral();
                    NinEEloose+=htemp1->Integral();
                }
                if(Vec_Files.at(i).Contains("mumu")){
                    NinMuMu+=htemp->Integral();
                    NinMuMuloose+=htemp1->Integral();
                }
            }
            else if(Vec_Files.at(i).Contains("dy")){
                if(Vec_Files.at(i).Contains("50inf")){
                    TH1D *htemp = fileReader->GetClone<TH1D>(Vec_Files.at(i), TString("Zh1").Append(nameAppendix));
                    TH1D *htemp1 = fileReader->GetClone<TH1D>(Vec_Files.at(i), TString("TTh1").Append(nameAppendix));
                    ApplyFlatWeights(htemp, LumiWeight);
                    ApplyFlatWeights(htemp1, LumiWeight);
                    if(Vec_Files.at(i).Contains("ee")){
                        NinEEDYMC+=htemp->Integral();
                        NoutEEDYMC+=htemp1->Integral();
                    }
                    if(Vec_Files.at(i).Contains("mumu")){
                        NinMuMuDYMC+=htemp->Integral();
                        NoutMuMuDYMC+=htemp1->Integral();
                    }
                    delete htemp; delete htemp1;
                }
                else{
                    TH1D *htemp = fileReader->GetClone<TH1D>(Vec_Files.at(i), TString("TTh1").Append(nameAppendix));
                    ApplyFlatWeights(htemp, LumiWeight);
                    if(Vec_Files.at(i).Contains("ee")){   NoutEEDYMC+=htemp->Integral();}
                    if(Vec_Files.at(i).Contains("mumu")){ NoutMuMuDYMC+=htemp->Integral();}
                    delete htemp;
                }
            }
            else{
                TH1D *htemp = fileReader->GetClone<TH1D>(Vec_Files.at(i), TString("Zh1").Append(nameAppendix));
                ApplyFlatWeights(htemp, LumiWeight);
                if(Vec_Files.at(i).Contains("ee")){   NinEEMC+=htemp->Integral();   }
                if(Vec_Files.at(i).Contains("mumu")){ NinMuMuMC+=htemp->Integral(); }
                delete htemp;
            }
        }
        
        if(Vec_Files.at(i).Contains("emu") && Vec_Files.at(i).Contains("run")){
            TH1D *htemp = fileReader->GetClone<TH1D>(Vec_Files.at(i), TString("Zh1").Append(nameAppendix));
            ApplyFlatWeights(htemp, LumiWeight);
            NinEMu+=htemp->Integral();
            delete htemp;
        }

    }
    
    double kee = sqrt(NinEEloose/NinMuMuloose);
    double kmumu = sqrt(NinMuMuloose/NinEEloose);
    
    double RoutinEE = NoutEEDYMC/NinEEDYMC;
    double RoutinMuMu = NoutMuMuDYMC/NinMuMuDYMC;
    
    double NoutMCEE = RoutinEE*(NinEE - 0.5*NinEMu*kee);
    double NoutMCMuMu = RoutinMuMu*(NinMuMu - 0.5*NinEMu*kmumu);

    double DYSFEE = NoutMCEE/NoutEEDYMC;
    double DYSFMuMu = NoutMCMuMu/NoutMuMuDYMC;

    cout << endl;
    cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << endl;
    cout << "Calculation of DY Scale Factors for '" << name << "'  at selection step "<<nameAppendix << endl;

    cout<<"DYSFEE:                 "<<DYSFEE<<endl;
    cout<<"DYSFMuMu:               "<<DYSFMuMu<<endl;

    cout<<"NinEEloose:             "<<NinEEloose<<endl;
    cout<<"NinMMloose:             "<<NinMuMuloose<<endl;

    cout<<"kee:                    "<<kee<<" +- "<<0.5*TMath::Sqrt(1./NinMuMuloose + 1./NinEEloose)<<endl;
    cout<<"kmumu:                  "<<kmumu<<" +- "<<0.5*TMath::Sqrt(1./NinMuMuloose + 1./NinEEloose)<<endl;

    cout<<"Rout/Rin ee:            "<<RoutinEE<<endl;
    cout<<"Rout/Rin Mumu:          "<<RoutinMuMu<<endl;

    cout<<"Est. From Data(ee):     "<<NoutMCEE<<endl;
    cout<<"Est. From Data(mumu):   "<<NoutMCMuMu<<endl;

    cout<<"Est. From MC(ee):       "<<NoutEEDYMC<<endl;
    cout<<"Est. From MC(mumu):     "<<NoutMuMuDYMC<<endl;

    cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << endl;
    cout << endl;

    
    DYScale.at(0)=DYSFEE;
    DYScale.at(1)=DYSFMuMu;
    DYScale.at(2)=1.;
    DYScale.at(3)=(DYSFEE+DYSFMuMu)/2;//not correct, but close, fix later

    cout<<"End DYSCALE FACTOR calculation\n"<<endl;

}




Plotter::Plotter()
{
    name="defaultName";
    specialComment="Standard";
    rangemin=0;
    rangemax=3;
    YAxis="N_{events}";
    initialized=false;
    datafiles = 0;

    channelLabel.insert(channelLabel.begin(),4, "");

    
    //Ivan: Initialize list of systematics
    fileReader = RootFileReader::getInstance();
}

void Plotter::setOptions(TString name_, TString specialComment_, TString YAxis_, TString XAxis_, int rebin_, bool doDYScale_, bool logX_, bool logY_, double ymin_, double ymax_, double rangemin_, double rangemax_, int bins_, std::vector<double> XAxisbins_, std::vector<double> XAxisbinCenters_)
{
    name=name_; //Variable name you want to plot
    specialComment=specialComment_; 
    YAxis=YAxis_; //Y-axis title
    XAxis=XAxis_; //X-axis title
    rebin=rebin_; //Nr. of bins to be merged together
    doDYScale = doDYScale_; //Apply DY scale factor?
    logX = logX_; //Draw X-axis in Log scale
    logY = logY_; //Draw Y-axis in Log scale
    ymin = ymin_; //Min. value in Y-axis
    ymax = ymax_; //Max. value in Y-axis
    rangemin=rangemin_; //Min. value in X-axis
    rangemax=rangemax_; //Max. value in X-axis
    bins=bins_; //Number of bins to plot
    XAxisbins.clear(); 
    XAxisbins = XAxisbins_; // Bins edges=bins+1
    XAxisbinCenters.clear();
    XAxisbinCenters = XAxisbinCenters_; //Central point for BinCenterCorrection=bins

    //Modify the X/Y-axis labels
    if(XAxis.Contains("band#bar{b}")){//Histogram naming convention has to be smarter
        XAxis.ReplaceAll("band#bar{b}",11,"b and #bar{b}",13);
    }
    if(XAxis.Contains("tand#bar{t}")){//Histogram naming convention has to be smarter
        XAxis.ReplaceAll("tand#bar{t}",11,"t and #bar{t}",13);
    }
    if(XAxis.Contains("l^{+}andl^{-}")){//Histogram naming convention has to be smarter
        XAxis.ReplaceAll("l^{+}andl^{-}",13,"l^{+} and l^{-}",15);
    }
    if(YAxis.Contains("Toppairs")){
        YAxis.ReplaceAll("Toppairs",8,"Top-quark pairs",15);
    }
    if(YAxis.Contains("Topquarks")){
        YAxis.ReplaceAll("Topquarks",9, "Top quarks",10);
    }
    if(YAxis.Contains("Numberof")){
        YAxis.ReplaceAll("Numberof", 8, "Number of ",10);
    }

    DYScale.insert(DYScale.begin(), 4, 1.);//Initialize the DY scale-factor to (1., 1., 1., 1.)
}


void Plotter::setDataSet(std::vector<TString> dataset_, std::vector<double> scales_, std::vector<TString> legends_, std::vector<int> colors_, TString DYEntry_)
{
    dataset.clear();
    scales.clear();
    legends.clear();
    legendsSyst.clear();
    colors.clear();
    dataset=dataset_;
    scales=scales_;
    legends=legends_;
    colors=colors_;
    DYEntry=DYEntry_;
}

void Plotter::setDataSet(TString mode, TString Systematic)
{
    initialized=false;
    legendsSyst.clear();

    if(channelLabel.size()<4){channelLabel.insert(channelLabel.begin(), 4, "");}

    if(mode =="ee"){channelType=0;channelLabel.at(0)="ee";}
    if(mode =="mumu"){channelType=1;channelLabel.at(1)="#mu#mu";}
    if(mode =="emu"){channelType=2;channelLabel.at(2)="e#mu";}
    if(mode =="combined"){channelType=3;channelLabel.at(3)="Dilepton Combined";}

    // Set dataset specific subfolders
    outpathPlots = "./Plots";
    subfolderChannel = mode;
    subfolderChannel.Prepend("/");
    subfolderSpecial = "";
    if ( specialComment.CompareTo("Standard") != 0 ) {
        //subfolderSpecial = specialComment.Prepend("/");
    }

    DYEntry = "Z / #gamma* #rightarrow ee/#mu#mu";

    if(Systematic.Contains("DY_") || Systematic.Contains("BG_")){Systematic = "Nominal";}//We just need to vary the nominal DY and BG systematics

    TString histoListName = "FileLists/HistoFileList_"+Systematic+"_"+mode+".txt";
    cout << "reading " << histoListName << endl;
    ifstream FileList(histoListName);
    if (FileList.fail()) {
        cerr << "Error reading " << histoListName << endl;
        exit(1);
    }
    TString filename;
    datafiles=0;

    dataset.clear();
    legends.clear();
    colors.clear();

    while(!FileList.eof()){
        FileList>>filename;
        if(filename==""){continue;}//Skip empty lines
        dataset.push_back(filename);
        if(filename.Contains("run")){legends.push_back("Data"); colors.push_back(kBlack);datafiles++;}
        else if(filename.Contains("ttbarsignal")){legends.push_back("t#bar{t} Signal"); colors.push_back(kRed+1);}
        else if(filename.Contains("ttbarbg")){legends.push_back("t#bar{t} Other"); colors.push_back(kRed-7);}
        else if(filename.Contains("single")){legends.push_back("Single Top"); colors.push_back(kMagenta);}
        else if(filename.Contains("ww") ||filename.Contains("wz")||filename.Contains("zz")){legends.push_back("Diboson"); colors.push_back(10);}
        else if(filename.Contains("dytautau")){legends.push_back("Z / #gamma* #rightarrow #tau#tau"); colors.push_back(kAzure+8);}
        else if(filename.Contains("dymumu")||filename.Contains("dyee")){legends.push_back("Z / #gamma* #rightarrow ee/#mu#mu"); colors.push_back(kAzure-2);}
        else if(filename.Contains("wtolnu")){legends.push_back("W+Jets"); colors.push_back(kGreen-3);}
        else if(filename.Contains("qcd")){legends.push_back("QCD Multijet"); colors.push_back(kYellow);}
	// HIGGSING
	else if(filename.Contains("ttbarH125inclusive")){legends.push_back("t#bar{t}H (incl.)"); colors.push_back(kSpring);}
        else if(filename.Contains("ttbarH125tobbbar")){legends.push_back("t#bar{t}H (b#bar{b})"); colors.push_back(kOrange-7);}
	// ENDHIGGSING
    }
}




std::vector<TString> Plotter::InputFileList(TString mode, TString Systematic)
{
    // Use only nominal samples and do not apply systematics
    
    std::vector<TString> FileVector;
    FileVector.clear();
    
    
    if( mode.CompareTo("combined") && mode.CompareTo("ee") && mode.CompareTo("emu") && mode.CompareTo("mumu")){
        cout<<"The decay channel you provided is not supported."<<endl;
        cout<<"Please use: ee, emu, mumu, combined"<<endl;
        return FileVector;
    }
    
    if(!mode.CompareTo("combined")){
        vector<TString> eemode   = Plotter::InputFileList(TString("ee"), Systematic);
        vector<TString> emumode  = Plotter::InputFileList(TString("emu"), Systematic);
        vector<TString> mumumode = Plotter::InputFileList(TString("mumu"), Systematic);
        FileVector.insert(FileVector.end(), eemode.begin(), eemode.end());
        FileVector.insert(FileVector.end(), emumode.begin(), emumode.end());
        FileVector.insert(FileVector.end(), mumumode.begin(), mumumode.end());
        return FileVector;
    }

    //data is only stored in the Nominal directory
    FileVector.push_back(TString("selectionRoot/Nominal/").Append(mode.Copy()).Append("/").Append(mode.Copy()).Append("_run2012A.root"));
    FileVector.push_back(TString("selectionRoot/Nominal/").Append(mode.Copy()).Append("/").Append(mode.Copy()).Append("_run2012Arecover.root"));
    FileVector.push_back(TString("selectionRoot/Nominal/").Append(mode.Copy()).Append("/").Append(mode.Copy()).Append("_run2012B.root"));
    FileVector.push_back(TString("selectionRoot/Nominal/").Append(mode.Copy()).Append("/").Append(mode.Copy()).Append("_run2012C_24Aug.root"));
    FileVector.push_back(TString("selectionRoot/Nominal/").Append(mode.Copy()).Append("/").Append(mode.Copy()).Append("_run2012C_PromptReco.root"));
    
    //MC depends on the specific Systematic: Signal systematics only use different signal samples
    TString tempName;
    tempName = TString("selectionRoot/Nominal/") + mode + "/" + mode;
    
    FileVector.push_back(tempName + "_dyee1050.root");
    FileVector.push_back(tempName + "_dyee50inf.root");
    FileVector.push_back(tempName + "_dymumu1050.root");
    FileVector.push_back(tempName + "_dymumu50inf.root");
    FileVector.push_back(tempName + "_singleantitop_tw.root");
    FileVector.push_back(tempName + "_singletop_tw.root");
    FileVector.push_back(tempName + "_wtolnu.root");
    FileVector.push_back(tempName + "_wwtoall.root");
    FileVector.push_back(tempName + "_wztoall.root");
    FileVector.push_back(tempName + "_zztoall.root");
    FileVector.push_back(tempName + "_dytautau1050.root");
    FileVector.push_back(tempName + "_dytautau50inf.root");
    FileVector.push_back(tempName + "_qcdem2030.root");
    FileVector.push_back(tempName + "_qcdem3080.root");
    FileVector.push_back(tempName + "_qcdem80170.root");
    FileVector.push_back(tempName + "_qcdmu15.root");
    
    TString ttbarsignalplustau = tempName + "_ttbarsignalplustau.root";
    TString ttbarbgviatau      = tempName + "_ttbarbgviatau.root";
    TString ttbarbg            = tempName + "_ttbarbg.root";

    FileVector.push_back(ttbarsignalplustau);
    FileVector.push_back(ttbarbg);
    FileVector.push_back(ttbarbgviatau);
    
    return FileVector;
    
}


bool Plotter::fillHisto()
{   
    if (initialized) { return true; }
    TH1::AddDirectory(kFALSE);
    hists.clear();
    for(unsigned int i=0; i<dataset.size(); i++){
        TH1D *hist = fileReader->GetClone<TH1D>(dataset.at(i), name, true);
        if (!hist) return false;

        //Rescaling to the data luminosity
        double LumiWeight = CalcLumiWeight(dataset.at(i));
        ApplyFlatWeights(hist, LumiWeight);

        setHHStyle(*gStyle);

        hists.push_back(*hist);
    }
    initialized=true;
    return true;
}

void Plotter::write(TString Channel, TString Systematic) // do scaling, stacking, legending, and write in file 
{
    setDataSet(Channel,Systematic);
    if (!fillHisto()) return;

    if (hists.size() == 0) { 
        cerr << "***ERROR! No histograms available! " << Channel << "/" << Systematic << endl; 
        exit(11); 
    }
        
    TCanvas * c = new TCanvas("","");

    THStack * stack=  new THStack("def", "def");
    TLegend * leg =  new TLegend(0.70,0.55,0.98,0.85);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetX1NDC(1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength() - 0.25);
    leg->SetY1NDC(1.0 - gStyle->GetPadTopMargin()  - gStyle->GetTickLength() - 0.05 - leg->GetNRows()*0.04);
    leg->SetX2NDC(1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength());
    leg->SetY2NDC(1.0 - gStyle->GetPadTopMargin()  - gStyle->GetTickLength());

    TH1 *drawhists[hists.size()];
    std::stringstream ss;
    ss << DYScale[channelType];
    TString scale;
    scale=(TString)ss.str();
    int legchange=0;
    leg->Clear();
    c->Clear();
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    c->SetName("");

    c->SetTitle("");


    TString newname = name;




    for(unsigned int i=0; i<hists.size() ; i++){ // prepare histos and leg
        drawhists[i]=(TH1D*) hists[i].Clone();//rebin and scale the histograms
        if(rebin>1) drawhists[i]->Rebin(rebin);
        setStyle(drawhists[i], i, true);
    }


    for(unsigned int i=0; i<hists.size() ; ++i){ // prepare histos and leg
    if(legends.at(i) != "Data"){
        if(i > 1){
            if(legends.at(i) != legends.at(i-1)){
                legchange = i; 
                if((legends.at(i) == DYEntry)&& DYScale[channelType] != 1) leg->AddEntry(drawhists[i], legends.at(i),"f");
                else leg->AddEntry(drawhists[i], legends.at(i) ,"f");
            }else{
                drawhists[legchange]->Add(drawhists[i]);
            }
        }

        if(i!=(hists.size()-1)){
            if(legends.at(i)!=legends.at(i+1)){
                drawhists[i]->SetLineColor(1);
            }
        }else{
            drawhists[i]->SetLineColor(1);
        }
        if(legends.at(i) != legends.at(i-1)){
            drawhists[i]->SetLineColor(1);
            stack->Add(drawhists[i]); 
        }
    }
    else{
        if(i==0) leg->AddEntry(drawhists[i], legends.at(i) ,"pe");
        if(i>0){
            if(legends.at(i) != legends.at(i-1)){
                leg->AddEntry(drawhists[i], legends.at(i) ,"pe");
            }
            if(legends.at(i) == legends.at(0)){
                drawhists[0]->Add(drawhists[i]);
            }
        }
    }
    }



    leg = ControlLegend(hists.size(), drawhists, legends, leg);
    
    // Needed for event yield tables
    MakeTable();


    TList* l = stack->GetHists(); 
    TH1D* stacksum = (TH1D*) l->At(0)->Clone();

    for (int i = 1; i < l->GetEntries(); ++i) { stacksum->Add((TH1D*)l->At(i));}

    TH1D* syshist =0;
    syshist = (TH1D*)stacksum->Clone();
    for(Int_t i=0; i<=syshist->GetNbinsX(); ++i){
        Double_t binc = 0;
        binc += stacksum->GetBinContent(i);
        syshist->SetBinContent(i, binc);
    }

    if(logY)c->SetLogy();
    syshist->SetFillStyle(3004);
    syshist->SetFillColor(kBlack);

    drawhists[0]->SetMinimum(ymin);

    if(rangemin!=0 || rangemax!=0) {drawhists[0]->SetAxisRange(rangemin, rangemax, "X");}

    if(ymax==0){
        if(logY){drawhists[0]->SetMaximum(18  * drawhists[0]->GetBinContent(drawhists[0]->GetMaximumBin()));}
        else    {drawhists[0]->SetMaximum(1.5 * drawhists[0]->GetBinContent(drawhists[0]->GetMaximumBin()));}
    }
    else{drawhists[0]->SetMaximum(ymax);}

    drawhists[0]->GetXaxis()->SetNoExponent(kTRUE);

    TGaxis::SetMaxDigits(2);


    //Add the binwidth to the yaxis in yield plots

    TString ytitle = TString(drawhists[0]->GetYaxis()->GetTitle()).Copy();
    double binwidth = drawhists[0]->GetXaxis()->GetBinWidth(1);
    std::ostringstream width;
    width<<binwidth;

    if(name.Contains("Rapidity") || name.Contains("Eta")){ytitle.Append(" / ").Append(width.str());}
    else if(name.Contains("pT") || name.Contains("Mass") || name.Contains("mass") || name.Contains("MET") || name.Contains("HT")){ytitle.Append(" / ").Append(width.str()).Append(" GeV");};
    drawhists[0]->GetYaxis()->SetTitle(ytitle);
    drawhists[0]->Draw("e1");

    stack->Draw("same HIST");
    gPad->RedrawAxis();
    TExec *setex1 = new TExec("setex1","gStyle->SetErrorX(0.5)");//this is frustrating and stupid but apparently necessary...
    setex1->Draw();
    syshist->SetMarkerStyle(0);
    //syshist->Draw("same,E2");
    TExec *setex2 = new TExec("setex2","gStyle->SetErrorX(0.)");
    setex2->Draw();
    drawhists[0]->Draw("same,e1");

    DrawCMSLabels(1, 8);
    DrawDecayChLabel(channelLabel[channelType]);
    leg->Draw("SAME");
    drawRatio(drawhists[0], stacksum, 0.5, 1.7);

    // Create Directory for Output Plots 
    gSystem->mkdir(outpathPlots+"/"+subfolderChannel+"/"+Systematic, true);
    c->Print(outpathPlots+subfolderChannel+"/"+Systematic+"/"+name+".eps");
    
    TH1 *sumMC = 0; 
    TH1 *sumttbar = 0;
    for (size_t i = 0; i < hists.size(); ++i) {
        if (legends.at(i) != "Data") {
            if (sumMC) sumMC->Add(drawhists[i]);
            else sumMC = static_cast<TH1*>(drawhists[i]->Clone());
        }
        if (legends.at(i) == "t#bar{t} Signal") {
            if (sumttbar) sumttbar->Add(drawhists[i]);
            else sumttbar = static_cast<TH1*>(drawhists[i]->Clone());
        }
    }
    sumMC->SetName(name);
    
    //save Canvas AND sources in a root file
    TFile out_root(outpathPlots+subfolderChannel+"/"+Systematic+"/"+name+"_source.root", "RECREATE");
    drawhists[0]->Write(name+"_data");
    sumttbar->Write(name+"_signalmc");
    sumMC->Write(name+"_allmc");
    c->Write(name + "_canvas");
    out_root.Close();
    
    c->Clear();
    leg->Clear();
    delete c;
    delete leg;
}

void Plotter::setStyle(TH1 *hist, unsigned int i, bool isControlPlot)
{
    hist->SetFillColor(colors[i]);
    hist->SetLineColor(colors[i]);
    hist->SetLineWidth(1);

    if(legends.at(i) == "Data"){
        hist->SetFillColor(0);
        hist->SetMarkerStyle(20);
        hist->SetMarkerSize(1.);
        hist->SetLineWidth(1);
        hist->GetXaxis()->SetLabelFont(42);
        hist->GetYaxis()->SetLabelFont(42);
        hist->GetXaxis()->SetTitleFont(42);
        hist->GetYaxis()->SetTitleFont(42);
        hist->GetYaxis()->SetTitleOffset(1.7);
        hist->GetXaxis()->SetTitleOffset(1.25);
        if ((name.Contains("pT") || name.Contains("Mass")) && !name.Contains("Rapidity")) {
            hist->GetXaxis()->SetTitle(XAxis+" #left[GeV#right]");
            hist->GetYaxis()->SetTitle("#frac{1}{#sigma} #frac{d#sigma}{d"+XAxis+"}"+" #left[GeV^{-1}#right]"); 
        } else {
            hist->GetXaxis()->SetTitle(XAxis);
            hist->GetYaxis()->SetTitle("#frac{1}{#sigma} #frac{d#sigma}{d"+XAxis+"}");     
        }
        if (isControlPlot) hist->GetYaxis()->SetTitle(YAxis);
    }
}




void Plotter::MakeTable(){

    TH1D *numhists5[hists.size()];
    TH1D *numhists6[hists.size()];
    TH1D *numhists7[hists.size()];
    TH1D *numhists8[hists.size()];
    TH1D *numhists9[hists.size()];

    for(unsigned int i=0; i<dataset.size(); i++){

        TH1D *temp_hist5 = fileReader->GetClone<TH1D>(dataset[i], "step5");
        TH1D *temp_hist6 = fileReader->GetClone<TH1D>(dataset[i], "step6");
        TH1D *temp_hist7 = fileReader->GetClone<TH1D>(dataset[i], "step7");
        TH1D *temp_hist8 = fileReader->GetClone<TH1D>(dataset[i], "step8");
        TH1D *temp_hist9 = fileReader->GetClone<TH1D>(dataset[i], "step9");
        
        double LumiWeight = CalcLumiWeight(dataset.at(i));
        ApplyFlatWeights(temp_hist5, LumiWeight);
        ApplyFlatWeights(temp_hist6, LumiWeight);
        ApplyFlatWeights(temp_hist7, LumiWeight);
        ApplyFlatWeights(temp_hist8, LumiWeight);
        ApplyFlatWeights(temp_hist9, LumiWeight);

        numhists5[i]=temp_hist5;
        numhists6[i]=temp_hist6;
        numhists7[i]=temp_hist7;
        numhists8[i]=temp_hist8;
        numhists9[i]=temp_hist9;

    }

    for(unsigned int i=0; i<hists.size() ; i++){ // prepare histos and leg
        if((legends.at(i) == DYEntry) && channelType!=2){
            //numhists5[i]->Scale(DYScale[channelType]);//DYscale not applied in step5 and 6?
            //numhists6[i]->Scale(DYScale[channelType]);
            numhists7[i]->Scale(DYScale.at(channelType));
            numhists8[i]->Scale(DYScale.at(channelType));
            numhists9[i]->Scale(DYScale.at(channelType));
        }
    }

    ////////////////////////////Make output for tables
    double tmp_num5 = 0;
    double tmp_num6 = 0;
    double tmp_num7 = 0;
    double tmp_num8 = 0;
    double tmp_num9 = 0;

    ofstream EventFile5;
    ofstream EventFile6;
    ofstream EventFile7;
    ofstream EventFile8;
    ofstream EventFile9;
    string EventFilestring = outpathPlots.Data();
    EventFilestring.append(subfolderChannel.Data());
    EventFilestring.append(subfolderSpecial.Data());
    gSystem->mkdir(outpathPlots+"/"+subfolderChannel+"/"+subfolderSpecial, true);  
    string EventFilestring5;
    string EventFilestring6;
    string EventFilestring7;
    string EventFilestring8;
    string EventFilestring9;
    EventFilestring5 =EventFilestring;EventFilestring5.append("/Events5.txt");
    EventFilestring6 =EventFilestring;EventFilestring6.append("/Events6.txt");
    EventFilestring7 =EventFilestring;EventFilestring7.append("/Events7.txt");
    EventFilestring8 =EventFilestring;EventFilestring8.append("/Events8.txt");
    EventFilestring9 =EventFilestring;EventFilestring9.append("/Events9.txt");
    EventFile5.open(EventFilestring5.c_str());
    EventFile6.open(EventFilestring6.c_str());
    EventFile7.open(EventFilestring7.c_str());
    EventFile8.open(EventFilestring8.c_str());
    EventFile9.open(EventFilestring9.c_str());
    double bg_num5 = 0;
    double bg_num6 = 0;
    double bg_num7 = 0;
    double bg_num8 = 0;
    double bg_num9 = 0;

    for(unsigned int i=0; i<hists.size() ; i++){
        tmp_num5+=numhists5[i]->Integral();
        tmp_num6+=numhists6[i]->Integral();
        tmp_num7+=numhists7[i]->Integral();
        tmp_num8+=numhists8[i]->Integral();
        tmp_num9+=numhists9[i]->Integral();

        if(i==(hists.size()-1)){
            EventFile5<<legends.at(i)<<": "<<tmp_num5<<endl;
            EventFile6<<legends.at(i)<<": "<<tmp_num6<<endl;
            EventFile7<<legends.at(i)<<": "<<tmp_num7<<endl;
            EventFile8<<legends.at(i)<<": "<<tmp_num8<<endl;
            EventFile9<<legends.at(i)<<": "<<tmp_num9<<endl;
            bg_num5+=tmp_num5;
            bg_num6+=tmp_num6;
            bg_num7+=tmp_num7;
            bg_num8+=tmp_num8;
            bg_num9+=tmp_num9;
            tmp_num5=0;
            tmp_num6=0;
            tmp_num7=0;
            tmp_num8=0;
            tmp_num9=0;
        }
        else if(legends.at(i)!=legends.at(i+1)){
            EventFile5<<legends.at(i)<<": "<<tmp_num5<<endl;
            EventFile6<<legends.at(i)<<": "<<tmp_num6<<endl;
            EventFile7<<legends.at(i)<<": "<<tmp_num7<<endl;
            EventFile8<<legends.at(i)<<": "<<tmp_num8<<endl;
            EventFile9<<legends.at(i)<<": "<<tmp_num9<<endl;
            if(legends.at(i)!="Data"){
                bg_num5+=tmp_num5;
                bg_num6+=tmp_num6;
                bg_num7+=tmp_num7;
                bg_num8+=tmp_num8;
                bg_num9+=tmp_num9;
            }
            tmp_num5=0;
            tmp_num6=0;
            tmp_num7=0;
            tmp_num8=0;
            tmp_num9=0;
        }
    }
    EventFile5<<"Total background: "<<bg_num5<<endl;
    EventFile5.close();
    EventFile6<<"Total background: "<<bg_num6<<endl;
    EventFile6.close();
    EventFile7<<"Total background: "<<bg_num7<<endl;
    EventFile7.close();
    EventFile8<<"Total background: "<<bg_num8<<endl;
    EventFile8.close();
    EventFile9<<"Total background: "<<bg_num9<<endl;
    EventFile9.close();
    cout<<"\nEvent yields saved in "<<EventFilestring5.c_str()<<"\n"<<endl;
}







// get new legend
TLegend* Plotter::getNewLegend() {
  TLegend *leg = new TLegend();
  leg->SetX1NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength()-0.25);
  leg->SetY1NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength()-0.20);
  leg->SetX2NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength());
  leg->SetY2NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength());
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextAlign(12);
  return leg;
}

// get new legend
TLegend* Plotter::getNewLegendpre() {
  TLegend *leg = new TLegend();
  leg->SetX1NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength()-0.25);
  leg->SetY1NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength()-0.30);
  leg->SetX2NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength());
  leg->SetY2NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength());
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextAlign(12);
  return leg;
}

TH1F* Plotter::ConvertGraphToHisto(TGraphErrors *pGraph){
  // takes data from a graph, determines binning and fills data into histogram
  Int_t NPoints = pGraph->GetN();
  Double_t BinLimits[NPoints+1];
  // sort graph
  pGraph->Sort();
  // determine lower limit of histogram: half the distance to next point
  Double_t x0,x1,y;
  pGraph->GetPoint(0,x0,y);
  pGraph->GetPoint(1,x1,y);
  Double_t Distance = TMath::Abs(x0-x1);
  BinLimits[0] = x0 - Distance/2.;
  // now set upper limits for all the other points
  for (Int_t k = 0 ; k<NPoints-1;k++){
    pGraph->GetPoint(k,x0,y);
    pGraph->GetPoint(k+1,x1,y);
    Distance = TMath::Abs(x0-x1);
    BinLimits[k+1] = x0 + Distance/2.;}
  // for the last point set upper limit similar to first point:
  pGraph->GetPoint(NPoints-2,x0,y);
  pGraph->GetPoint(NPoints-1,x1,y);
  Distance = TMath::Abs(x0-x1);
  BinLimits[NPoints] = x1 + Distance/2.;
  // now we know the binning and can create the histogram:
  TString Name = "ConvertedHisto"; 
  // make name unique 
  Name+= rand();
  TH1F *ThisHist = new TH1F(Name,"Converted Histogram",NPoints,BinLimits);
  // now fill the histogram
  for (Int_t i = 0; i<pGraph->GetN();i++){
    Double_t x2,y2;
    pGraph->GetPoint(i,x2,y2);
    ThisHist->SetBinContent(i+1,y2);
  }
  return ThisHist;
}

//TH1F* Plotter::reBinTH1FIrregularNewBinning(TH1F *histoOldBinning, const std::vector<double> &vecBinning, TString plotname, bool rescale=1){
TH1F* Plotter::reBinTH1FIrregularNewBinning(TH1F *histoOldBinning, TString plotname, bool rescale){
  //  This function rebins a histogram using a variable binning
  // 
  //  (1) It is not required to have an equidistant binning.
  //  (2) Any type of ROOT-histgramme can be used, so the template 
  //      arguments should be 
  //      (a) histoT = TH1D,   TH1F,  ....
  //      (b) varT   = double, float, ....
  //  
  //  modified quantities: none
  //  used functions:      none
  //  used enumerators:    none
  //  
  //  "histoOldBinning":   plot to be re-binned
  //  "vecBinning":        vector containing all bin edges 
  //                       from xaxis.min to xaxis.max
  //  "rescale":           rescale the rebinned histogramme
  //                       (applicable for cross-section e.g.) 
  cout << endl;
  cout << endl;
  cout << "asdfasdfasdfasdfasdf hallo david " << plotname << " " << rescale << endl;
  cout << "histoOldBinning = ";
  for ( int i = 0 ; i < histoOldBinning->GetXaxis()->GetNbins() + 1; i++ ) cout << " " << histoOldBinning->GetXaxis()->GetBinLowEdge(i+1);
  cout << endl;
  cout << endl;
  cout << endl;
  
   
  unsigned int vecIndex=0;

  // fill vector into array to use appropriate constructor of TH1-classes
  const double *binArray = XAxisbins.data();
	
  // create histo with new binning
  TH1F *histoNewBinning = new TH1F("histoNewBinning"+plotname,"histoNewBinning"+plotname,XAxisbins.size()-1,binArray);
	
  // fill contents of histoOldBinning into histoNewBinning and rescale if applicable
  for (vecIndex = 0; vecIndex < XAxisbins.size()-1; vecIndex++){
	    
    double lowEdge      = XAxisbins[vecIndex]; 
    if (plotname=="topPt"&&vecIndex==0&&lowEdge==0.0) lowEdge+=10;  // adhoc fix to compensate for minimum top-Pt cut in NNLO curve
    double highEdge     = XAxisbins[vecIndex+1];
    double newBinWidth  = highEdge - lowEdge;
    double newBinCenter = 0.5*(highEdge+lowEdge);
    double binSum       = 0.0;	    	  
	    
    for (int j=1; j<histoOldBinning->GetNbinsX(); j++){
		
      double oldBin = histoOldBinning->GetBinCenter(j);
		
      if( (oldBin>=lowEdge) && (oldBin<highEdge) ){		   
	if (rescale) binSum+=histoOldBinning->GetBinContent(j) * histoOldBinning->GetBinWidth(j);
	else         binSum+=histoOldBinning->GetBinContent(j);
      }
    }

    if (rescale) histoNewBinning->Fill(newBinCenter,binSum/newBinWidth);
    else histoNewBinning->Fill(newBinCenter,binSum);
  }

  return (TH1F*)histoNewBinning->Clone();
}

TLegend* Plotter::ControlLegend(int HistsSize, TH1* drawhists[], std::vector<TString> Legends, TLegend *leg){
    //hardcoded ControlPlot legend
    std::vector<TString> OrderedLegends;    
    OrderedLegends.push_back("Data");
    OrderedLegends.push_back("t#bar{t} Signal");
    OrderedLegends.push_back("t#bar{t} Other");
    OrderedLegends.push_back("Single Top");
    OrderedLegends.push_back("W+Jets");
    OrderedLegends.push_back("Z / #gamma* #rightarrow ee/#mu#mu");
    OrderedLegends.push_back("Z / #gamma* #rightarrow #tau#tau");
    OrderedLegends.push_back("Diboson");
    OrderedLegends.push_back("QCD Multijet");
    // HIGGSING
    OrderedLegends.push_back("t#bar{t}H (incl.)");
    OrderedLegends.push_back("t#bar{t}H (b#bar{b})");
    // ENDHIGGSING
    
    leg->Clear();
    leg->SetX1NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength()-0.25);
    leg->SetY1NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength()-0.30);
    leg->SetX2NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength());
    leg->SetY2NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength());
    leg->SetTextFont(42);
    leg->SetTextSize(0.03);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextAlign(12);
    for(int i=0; i<(int)OrderedLegends.size(); ++i){
        for(int j=0; j<HistsSize; ++j){
            if (OrderedLegends[i] == Legends[j]){
                if( OrderedLegends[i] == "Data"){
                    leg->AddEntry(drawhists[j], OrderedLegends[i], "pe");
                    break;
                }
                else{
                    leg->AddEntry(drawhists[j], OrderedLegends[i], "f");
                    break;
                }
            }
        }
    }
    return leg;
}



void Plotter::ApplyFlatWeights(TH1* varhists, const double weight){

    if(weight == 0) {cout<<"Warning: the weight your applying is 0. This will remove your distribution."<<endl;}
    //if(weight >=1e3){cout<<"Warning: the weight your applying is >= 1e3. This will enlarge too much your distribution."<<endl;}
    varhists->Scale(weight);
}


double Plotter::CalcLumiWeight(const TString& WhichSample){
    if (WhichSample.Contains("run")) return 1;
    double lumiWeight=0;
    if(WhichSample!=""){
        double XSection = SampleXSection(WhichSample);
        if(XSection <= 0.){
            cout<<"Sample XSection is <0. Can't calculate luminosity weight!! returning"<<endl;
            return 0;
        }
        
        //From 'filename' get the number of weighted (MC weights) event processed.
        const TH1 *h_NrOfEvts = fileReader->Get<TH1>(WhichSample, "weightedEvents");
        double NrOfEvts = h_NrOfEvts->GetBinContent(1);
        lumiWeight = lumi*XSection/NrOfEvts;
    }
    
    if (lumiWeight == 0) {
        cout << WhichSample << " has lumi weight 0\n";
    }

    return lumiWeight;
}


double Plotter::SampleXSection(const TString& filename){
    
    //MC cross sections taken from:
    //  https://twiki.cern.ch/twiki/bin/view/CMS/StandardModelCrossSectionsat8TeV
    //  AN-12/194    AN-12/228
    
    if(filename.Contains("run"))              {return 1;}
    // HIGGSING
    //else if(filename.Contains("ttbar"))       {return topxsec;}
    else if(filename.Contains("ttbar") && !filename.Contains("ttbarH") && !filename.Contains("ttbarW") && !filename.Contains("ttbarZ")){return topxsec;}
    // ENDHIGGSING
    else if(filename.Contains("single"))      {return 11.1;}
    else if(filename.Contains("ww"))          {return 54.838;}
    else if(filename.Contains("wz"))          {return 33.21;}
    else if(filename.Contains("zz"))          {return 17.654;}
    else if(filename.Contains("1050"))        {return 860.5;}
    else if(filename.Contains("50inf"))       {return 3532.8;}
    else if(filename.Contains("wtolnu"))      {return 36257.2;}
    else if(filename.Contains("qcdmu15"))     {return 3.640E8*3.7E-4;}
    else if(filename.Contains("qcdmu2030"))   {return 2.870E8*6.500E-3;}
    else if(filename.Contains("qcdmu3050"))   {return 6.609E7*12.20E-3;}
    else if(filename.Contains("qcdmu5080"))   {return 8.802E6*21.80E-3;}
    else if(filename.Contains("qcdmu80120"))  {return 1.024E6*39.50E-3;}
    else if(filename.Contains("qcdmu120170")) {return 1.578E5*47.30E-3;}
    else if(filename.Contains("qcdem2030"))   {return 2.886E8*10.10E-3;}
    else if(filename.Contains("qcdem3080"))   {return 7.433E7*62.10E-3;}
    else if(filename.Contains("qcdem80170"))  {return 1.191E6*153.9E-3;}
    else if(filename.Contains("qcdbcem2030")) {return 2.886E8*5.800E-4;}
    else if(filename.Contains("qcdbcem3080")) {return 7.424E7*2.250E-3;}
    else if(filename.Contains("qcdbcem80170")){return 1.191E6*10.90E-3;}
    // HIGGSING
    else if(filename.Contains("ttbarH125inclusive")){return 0.1302;}
    else if(filename.Contains("ttbarH125tobbbar")){return 0.1302*0.577;}
    // ENDHIGGSING
    
    return -1;
}


// Draw label for Decay Channel in upper left corner of plot
void Plotter::DrawDecayChLabel(TString decaychannel, double textSize) {

    TPaveText *decch = new TPaveText();

    decch->AddText(decaychannel);

    decch->SetX1NDC(      gStyle->GetPadLeftMargin() + gStyle->GetTickLength()        );
    decch->SetY1NDC(1.0 - gStyle->GetPadTopMargin()  - gStyle->GetTickLength() - 0.05 );
    decch->SetX2NDC(      gStyle->GetPadLeftMargin() + gStyle->GetTickLength() + 0.15 );
    decch->SetY2NDC(1.0 - gStyle->GetPadTopMargin()  - gStyle->GetTickLength()        );

    decch->SetFillStyle(0);
    decch->SetBorderSize(0);
    if (textSize!=0) decch->SetTextSize(textSize);
    decch->SetTextAlign(12);
    decch->Draw("same");
}

// Draw official labels (CMS Preliminary, luminosity and CM energy) above plot
void Plotter::DrawCMSLabels(int cmsprelim, double energy, double textSize) {

    const char *text;
    if(cmsprelim ==2 ) {//Private work for PhDs students
        text = "Private Work, %2.1f fb^{-1} at #sqrt{s} = %2.f TeV";
    } else if (cmsprelim==1) {//CMS preliminary label
        text = "CMS Preliminary, %2.1f fb^{-1} at #sqrt{s} = %2.f TeV";
    } else {//CMS label
        text = "CMS, %2.1f fb^{-1} at #sqrt{s} = %2.f TeV";
    }
    
    TPaveText *label = new TPaveText();
    label->SetX1NDC(gStyle->GetPadLeftMargin());
    label->SetY1NDC(1.0-gStyle->GetPadTopMargin());
    label->SetX2NDC(1.0-gStyle->GetPadRightMargin());
    label->SetY2NDC(1.0);
    label->SetTextFont(42);
    label->AddText(Form(text, lumi/1000, energy));
    label->SetFillStyle(0);
    label->SetBorderSize(0);
    if (textSize!=0) label->SetTextSize(textSize);
    label->SetTextAlign(32);
    label->Draw("same");
}






