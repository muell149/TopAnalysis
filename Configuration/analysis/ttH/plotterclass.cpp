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

#include "TGaxis.h"
#include "TPaveText.h"

#include "../diLeptonic/utils.h"
#include <iomanip>



const double Plotter::topxsec_ = 253.849; //again changes with normalization, must be set outside of the class



void Plotter::setLumi(double newLumi)
{
    this->lumi_ = newLumi;
}



void Plotter::DYScaleFactor(TString SpecialComment){

    DYScale_ = {1,1,1,1}; 

    if(!doDYScale_) return; //need to make a switch for control plots that don't want DYScale

    TString nameAppendix = "";
    if ( !SpecialComment.BeginsWith("_post") &&  SpecialComment != "Standard" ){
        std::cout<<"\n\n*******************************************************************"<<std::endl;
        std::cout<<"ERROR: When calculating the DY Scale factor you must specify in which step you want to calculate the DY SF:"<<std::endl;
        std::cout<<" '_postZcut', '_post2jets', '_postMET', '_post1btag', '_postKinReco' or 'Standard' = _postKinReco"<<std::endl;
        std::cout<<"*******************************************************************\n\n"<<std::endl;
        exit(444);
    }
    if (SpecialComment.BeginsWith("_post")){
        nameAppendix = SpecialComment;
    } else if ( SpecialComment == "Standard") {
        nameAppendix = "_postKinReco";
    }

    std::cout<<"\n\nBegin DYSCALE FACTOR calculation at selection step "<<nameAppendix<<std::endl;
    
    std::vector<TString> Vec_Files = InputFileList("combined", "Nominal");//Read the hardcoded list of files
    if(Vec_Files.size()<1) {std::cout<<"WARNING(in DYScaleFactor)!!! No datasets available to calculate DY SF. EXITING!!"<<std::endl; return;}
    
    double NoutEEDYMC=0, NinEEDYMC=0, NoutMuMuDYMC=0, NinMuMuDYMC=0;//Number of events in/out of z-veto region for the DY MC
    double NinEE=0, NinMuMu=0, NinEMu=0;//Number of events in z-veto region for data
    double NinEEloose=0, NinMuMuloose=0;//Number of data events in Z-Veto region with MET cut
    double NinEEMC=0, NinMuMuMC=0;//All other MC events

    for(size_t i=0; i < Vec_Files.size(); i++){
        double LumiWeight = CalcLumiWeight(Vec_Files.at(i));
        double allWeights=LumiWeight;//calculate here all the flat-weights we apply: Lumi*others*...
        if(Vec_Files.at(i).Contains("ee") || Vec_Files.at(i).Contains("mumu")){
            if(Vec_Files.at(i).Contains("run")){
                TH1D *htemp = fileReader_->GetClone<TH1D>(Vec_Files.at(i), TString("Zh1").Append(nameAppendix));
                TH1D *htemp1 = fileReader_->GetClone<TH1D>(Vec_Files.at(i), "Looseh1");
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
                    TH1D *htemp = fileReader_->GetClone<TH1D>(Vec_Files.at(i), TString("Zh1").Append(nameAppendix));
                    TH1D *htemp1 = fileReader_->GetClone<TH1D>(Vec_Files.at(i), TString("TTh1").Append(nameAppendix));
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
                    TH1D *htemp = fileReader_->GetClone<TH1D>(Vec_Files.at(i), TString("TTh1").Append(nameAppendix));
                    ApplyFlatWeights(htemp, LumiWeight);
                    if(Vec_Files.at(i).Contains("ee")){   NoutEEDYMC+=htemp->Integral();}
                    if(Vec_Files.at(i).Contains("mumu")){ NoutMuMuDYMC+=htemp->Integral();}
                    delete htemp;
                }
            }
            else{
                TH1D *htemp = fileReader_->GetClone<TH1D>(Vec_Files.at(i), TString("Zh1").Append(nameAppendix));
                ApplyFlatWeights(htemp, LumiWeight);
                if(Vec_Files.at(i).Contains("ee")){   NinEEMC+=htemp->Integral();   }
                if(Vec_Files.at(i).Contains("mumu")){ NinMuMuMC+=htemp->Integral(); }
                delete htemp;
            }
        }
        
        if(Vec_Files.at(i).Contains("emu") && Vec_Files.at(i).Contains("run")){
            TH1D *htemp = fileReader_->GetClone<TH1D>(Vec_Files.at(i), TString("Zh1").Append(nameAppendix));
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

    std::cout << std::endl;
    std::cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << std::endl;
    std::cout << "Calculation of DY Scale Factors for '" << name_ << "'  at selection step "<<nameAppendix << std::endl;

    std::cout<<"DYSFEE:                 "<<DYSFEE<<std::endl;
    std::cout<<"DYSFMuMu:               "<<DYSFMuMu<<std::endl;

    std::cout<<"NinEEloose:             "<<NinEEloose<<std::endl;
    std::cout<<"NinMMloose:             "<<NinMuMuloose<<std::endl;

    std::cout<<"kee:                    "<<kee<<" +- "<<0.5*TMath::Sqrt(1./NinMuMuloose + 1./NinEEloose)<<std::endl;
    std::cout<<"kmumu:                  "<<kmumu<<" +- "<<0.5*TMath::Sqrt(1./NinMuMuloose + 1./NinEEloose)<<std::endl;

    std::cout<<"Rout/Rin ee:            "<<RoutinEE<<std::endl;
    std::cout<<"Rout/Rin Mumu:          "<<RoutinMuMu<<std::endl;

    std::cout<<"Est. From Data(ee):     "<<NoutMCEE<<std::endl;
    std::cout<<"Est. From Data(mumu):   "<<NoutMCMuMu<<std::endl;

    std::cout<<"Est. From MC(ee):       "<<NoutEEDYMC<<std::endl;
    std::cout<<"Est. From MC(mumu):     "<<NoutMuMuDYMC<<std::endl;

    std::cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << std::endl;
    std::cout << std::endl;

    
    DYScale_.at(0)=DYSFEE;
    DYScale_.at(1)=DYSFMuMu;
    DYScale_.at(2)=1.;
    DYScale_.at(3)=(DYSFEE+DYSFMuMu)/2;//not correct, but close, fix later

    std::cout<<"End DYSCALE FACTOR calculation\n"<<std::endl;

}



Plotter::Plotter()
{
    name_ = "defaultName";
    specialComment_ = "Standard";
    rangemin_ = 0;
    rangemax_ = 3;
    YAxis_ = "N_{events}";
    initialized_ = false;
    datafiles_ = 0;

    channelLabel_.insert(channelLabel_.begin(),4, "");

    
    //Ivan: Initialize list of systematics
    fileReader_ = RootFileReader::getInstance();
}



void Plotter::setOptions(TString name, TString specialComment, TString YAxis, TString XAxis, int rebin, bool doDYScale, bool logX, bool logY, double ymin, double ymax, double rangemin, double rangemax, int bins, std::vector<double> XAxisbins, std::vector<double> XAxisbinCenters)
{
    name_ = name; //Variable name you want to plot
    specialComment_ = specialComment; 
    YAxis_ = YAxis; //Y-axis title
    XAxis_ = XAxis; //X-axis title
    rebin_ = rebin; //Nr. of bins to be merged together
    doDYScale_ = doDYScale; //Apply DY scale factor?
    logX_ = logX; //Draw X-axis in Log scale
    logY_ = logY; //Draw Y-axis in Log scale
    ymin_ = ymin; //Min. value in Y-axis
    ymax_ = ymax; //Max. value in Y-axis
    rangemin_ = rangemin; //Min. value in X-axis
    rangemax_ = rangemax; //Max. value in X-axis
    bins_ = bins; //Number of bins to plot
    XAxisbins_.clear(); 
    XAxisbins_ = XAxisbins; // Bins edges=bins+1
    XAxisbinCenters_.clear();
    XAxisbinCenters_ = XAxisbinCenters; //Central point for BinCenterCorrection=bins

    //Modify the X/Y-axis labels
    if(XAxis_.Contains("band#bar{b}")){//Histogram naming convention has to be smarter
        XAxis_.ReplaceAll("band#bar{b}",11,"b and #bar{b}",13);
    }
    if(XAxis_.Contains("tand#bar{t}")){//Histogram naming convention has to be smarter
        XAxis_.ReplaceAll("tand#bar{t}",11,"t and #bar{t}",13);
    }
    if(XAxis_.Contains("l^{+}andl^{-}")){//Histogram naming convention has to be smarter
        XAxis_.ReplaceAll("l^{+}andl^{-}",13,"l^{+} and l^{-}",15);
    }
    if(YAxis_.Contains("Toppairs")){
        YAxis_.ReplaceAll("Toppairs",8,"Top-quark pairs",15);
    }
    if(YAxis_.Contains("Topquarks")){
        YAxis_.ReplaceAll("Topquarks",9, "Top quarks",10);
    }
    if(YAxis_.Contains("Numberof")){
        YAxis_.ReplaceAll("Numberof", 8, "Number of ",10);
    }

    DYScale_.insert(DYScale_.begin(), 4, 1.);//Initialize the DY scale-factor to (1., 1., 1., 1.)
}



void Plotter::setDataSet(std::vector<TString> dataset, std::vector<double> scales, std::vector<TString> legends, std::vector<int> colors, TString DYEntry)
{
    dataset_.clear();
    scales_.clear();
    legends_.clear();
    colors_.clear();
    dataset_ = dataset;
    scales_ = scales;
    legends_ = legends;
    colors_ = colors;
    DYEntry_ = DYEntry;
}



void Plotter::setDataSet(TString mode, TString Systematic)
{
    initialized_ = false;

    if(channelLabel_.size()<4){channelLabel_.insert(channelLabel_.begin(), 4, "");}

    if(mode =="ee"){channelType_=0; channelLabel_.at(0)="ee";}
    if(mode =="mumu"){channelType_=1; channelLabel_.at(1)="#mu#mu";}
    if(mode =="emu"){channelType_=2; channelLabel_.at(2)="e#mu";}
    if(mode =="combined"){channelType_=3; channelLabel_.at(3)="Dilepton Combined";}

    // Set dataset specific subfolders
    outpathPlots_ = "./Plots";
    subfolderChannel_ = mode;
    subfolderChannel_.Prepend("/");
    subfolderSpecial_ = "";
    if ( specialComment_.CompareTo("Standard") != 0 ) {
        //subfolderSpecial_ = specialComment_.Prepend("/");
    }

    DYEntry_ = "Z / #gamma* #rightarrow ee/#mu#mu";

    if(Systematic.Contains("DY_") || Systematic.Contains("BG_")){Systematic = "Nominal";}//We just need to vary the nominal DY and BG systematics

    TString histoListName = "FileLists/HistoFileList_"+Systematic+"_"+mode+".txt";
    std::cout << "reading " << histoListName << std::endl;
    ifstream FileList(histoListName);
    if (FileList.fail()) {
        std::cerr << "Error reading " << histoListName << std::endl;
        exit(1);
    }
    TString filename;
    datafiles_ = 0;

    dataset_.clear();
    legends_.clear();
    colors_.clear();

    while(!FileList.eof()){
        FileList>>filename;
        if(filename==""){continue;}//Skip empty lines
        dataset_.push_back(filename);
        if(filename.Contains("run")){legends_.push_back("Data"); colors_.push_back(kBlack);datafiles_++;}
        else if(filename.Contains("ttbarsignal")){legends_.push_back("t#bar{t} Signal"); colors_.push_back(kRed+1);}
        else if(filename.Contains("ttbarbg")){legends_.push_back("t#bar{t} Other"); colors_.push_back(kRed-7);}
        else if(filename.Contains("single")){legends_.push_back("Single Top"); colors_.push_back(kMagenta);}
        else if(filename.Contains("ww") ||filename.Contains("wz")||filename.Contains("zz")){legends_.push_back("Diboson"); colors_.push_back(10);}
        else if(filename.Contains("dytautau")){legends_.push_back("Z / #gamma* #rightarrow #tau#tau"); colors_.push_back(kAzure+8);}
        else if(filename.Contains("dymumu")||filename.Contains("dyee")){legends_.push_back("Z / #gamma* #rightarrow ee/#mu#mu"); colors_.push_back(kAzure-2);}
        else if(filename.Contains("wtolnu")){legends_.push_back("W+Jets"); colors_.push_back(kGreen-3);}
        else if(filename.Contains("qcd")){legends_.push_back("QCD Multijet"); colors_.push_back(kYellow);}
    // HIGGSING
        else if(filename.Contains("ttbarH125inclusive")){legends_.push_back("t#bar{t}H (incl.)"); colors_.push_back(kSpring);}
        else if(filename.Contains("ttbarH125tobbbar")){legends_.push_back("t#bar{t}H (b#bar{b})"); colors_.push_back(kOrange-7);}
    // ENDHIGGSING
    }
}



// This method is only used for DY rescaling
std::vector<TString> Plotter::InputFileList(TString mode, TString Systematic)
{
    // Use only nominal samples and do not apply systematics
    
    std::vector<TString> FileVector;
    FileVector.clear();
    
    
    if( mode.CompareTo("combined") && mode.CompareTo("ee") && mode.CompareTo("emu") && mode.CompareTo("mumu")){
        std::cout<<"The decay channel you provided is not supported."<<std::endl;
        std::cout<<"Please use: ee, emu, mumu, combined"<<std::endl;
        return FileVector;
    }
    
    if(!mode.CompareTo("combined")){
        std::vector<TString> eemode   = Plotter::InputFileList(TString("ee"), Systematic);
        std::vector<TString> emumode  = Plotter::InputFileList(TString("emu"), Systematic);
        std::vector<TString> mumumode = Plotter::InputFileList(TString("mumu"), Systematic);
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
    if (initialized_) { return true; }
    TH1::AddDirectory(kFALSE);
    hists_.clear();
    for(unsigned int i=0; i<dataset_.size(); i++){
        TH1D *hist = fileReader_->GetClone<TH1D>(dataset_.at(i), name_, true);
        if (!hist) return false;

        //Rescaling to the data luminosity
        double LumiWeight = CalcLumiWeight(dataset_.at(i));
        ApplyFlatWeights(hist, LumiWeight);

        setHHStyle(*gStyle);

        hists_.push_back(*hist);
    }
    initialized_ = true;
    return true;
}



void Plotter::write(TString Channel, TString Systematic, DrawMode drawMode) // do scaling, stacking, legending, and write in file 
{
    
    setDataSet(Channel,Systematic);
    if (!fillHisto()) return;

    if (hists_.size() == 0) { 
        std::cerr << "***ERROR! No histograms available! " << Channel << "/" << Systematic << std::endl; 
        exit(11); 
    }
    
    // FIXME: Needed for event yield tables, but should be run only once, and not for each histogram
    if(name_=="JetCategories_step0")MakeTable();
    
    TCanvas * canvas = new TCanvas("","");

    THStack * stack = new THStack("def", "def");
    TLegend * legend = new TLegend(0.70,0.55,0.98,0.85);
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    legend->SetX1NDC(1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength() - 0.25);
    legend->SetY1NDC(1.0 - gStyle->GetPadTopMargin()  - gStyle->GetTickLength() - 0.05 - legend->GetNRows()*0.04);
    legend->SetX2NDC(1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength());
    legend->SetY2NDC(1.0 - gStyle->GetPadTopMargin()  - gStyle->GetTickLength());

    TH1 *drawhists[hists_.size()];
    std::stringstream ss;
    ss << DYScale_[channelType_];
    TString scale;
    scale=(TString)ss.str();
    int legchange=0;
    legend->Clear();
    canvas->Clear();
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    canvas->SetName("");
    canvas->SetTitle("");
    
    TString newname = name_;
    
    // Error messages in case of undefined legends or colors
    if(legends_.size()!=colors_.size()){
        std::cerr<<"Incorrect number of legend entries ("<<legends_.size()<<"), ie. not equal to defined colors ("<<colors_.size()<<"). CANNOT continue!!!\n";
        exit(77);
    }
    if(hists_.size()>legends_.size()){
        std::cerr<<"Incorrect number of legend entries ("<<legends_.size()<<"), ie. less than sample files ("<<hists_.size()<<"). CANNOT continue!!!\n";
        exit(77);
    }
    
    // Here fill colors and line width are adjusted
    for(unsigned int i=0; i<hists_.size() ; i++){ // prepare histos and legend
        drawhists[i]=(TH1D*) hists_[i].Clone();//rebin the histograms
        if(rebin_>1) drawhists[i]->Rebin(rebin_);
        setStyle(drawhists[i], i, true);
    }
    
    
    // Check whether Higgs sample should be drawn overlaid and/or scaled
    TH1D* overlayHist(0);
    std::vector<bool> v_isHiggsSignal;
    bool drawHiggsOverlaid(false);
    bool drawHiggsScaled(false);
    if(drawMode==overlaid){drawHiggsOverlaid = true;}
    else if(drawMode==scaledoverlaid){drawHiggsOverlaid = true; drawHiggsScaled = true;}
    for(unsigned int i=0; i<hists_.size(); ++i){
        bool isHiggsSignal(false);
        if(legends_.at(i) == "t#bar{t}H (b#bar{b})")isHiggsSignal = true;
        v_isHiggsSignal.push_back(isHiggsSignal);
    }
    
    
    // Here the shape in the legend is adjusted, and black lines are drawn between samples with different legends,
    // and the stack is created
    unsigned int legendEntryHiggs(0);
    for(unsigned int i=0; i<hists_.size() ; ++i){ // prepare histos and legend
        //std::cout<<"IsHiggs: "<<v_isHiggsSignal.at(i)<<" , "<<drawHiggsOverlaid<<"\n";
        if(legends_.at(i) != "Data" && !(v_isHiggsSignal.at(i) && drawHiggsOverlaid)){
            //std::cout<<"legend in mc stack: "<<legends_.at(i)<<"\n";
            if(i > 1){
                if(legends_.at(i) != legends_.at(i-1)){
                    legchange = i; 
                    legend->AddEntry(drawhists[i], legends_.at(i),"f");
                    ++legendEntryHiggs;
                }else{
                    drawhists[legchange]->Add(drawhists[i]);
                }
            }
            
            if(i!=(hists_.size()-1)){
                if(legends_.at(i)!=legends_.at(i+1)){
                    drawhists[i]->SetLineColor(1);
                }
            }else{
                drawhists[i]->SetLineColor(1);
            }
            
            if(legends_.at(i) != legends_.at(i-1)){
                drawhists[i]->SetLineColor(1);
                stack->Add(drawhists[i]); 
            }
        }
        else if(legends_.at(i) != "Data"){
            //std::cout<<"legend in higgs overlaid: "<<legends_.at(i)<<"\n";
            if(!overlayHist)overlayHist = (TH1D*) drawhists[i]->Clone();
            else overlayHist->Add(drawhists[i]);
            overlayHist->SetFillStyle(0);
            overlayHist->SetLineWidth(2);
        }
        else{
            if(i==0) legend->AddEntry(drawhists[i], legends_.at(i) ,"pe");
            if(i>0){
                if(legends_.at(i) != legends_.at(i-1)){
                    ++legendEntryHiggs;
                    legend->AddEntry(drawhists[i], legends_.at(i) ,"pe");
                }
                if(legends_.at(i) == legends_.at(0)){
                    drawhists[0]->Add(drawhists[i]);
                }
            }
        }
    }
    
    
    TList* list = stack->GetHists(); 
    // Create a histogram with the sum of all stacked hists
    TH1D* stacksum = (TH1D*) list->At(0)->Clone();
    for (int i = 1; i < list->GetEntries(); ++i) { stacksum->Add((TH1D*)list->At(i));}
    // If Higgs signal overlaid: add legend entry
    // If Higgs signal scaled: scale sample and add modified legend entry
    double signalScaleFactor(1);
    std::vector<TString> v_higgsLabel;
    if(drawHiggsScaled){
        std::stringstream ss_scaleFactor;
        signalScaleFactor = stacksum->Integral()/overlayHist->Integral();
        const int precision(signalScaleFactor>=100 ? 0 : 1);
        ss_scaleFactor<<" x"<<std::fixed<<std::setprecision(precision)<<signalScaleFactor;
        overlayHist->Scale(signalScaleFactor);
        int iSample=0;
        for(std::vector<bool>::const_iterator i_isHiggsSignal = v_isHiggsSignal.begin(); i_isHiggsSignal != v_isHiggsSignal.end();++iSample, ++i_isHiggsSignal){
            if(*i_isHiggsSignal){
                ++legendEntryHiggs;
                TString label(legends_.at(iSample));
                label.Append(ss_scaleFactor.str());
                v_higgsLabel.push_back(label);
                //std::cout<<"Label: "<<label<<" , "<<iSample<<" , "<<legendEntryHiggs<<"\n";
                
                if(iSample==0){
                    legend->AddEntry(overlayHist, label, "l");
                }
                else if(legends_.at(iSample) != legends_.at(iSample-1)){
                    legend->AddEntry(overlayHist, label, "l");
                }
            }
            //if(*i_isHiggsSignal)std::cout<<"\n\t\tHiggsLegend "<<legend->GetListOfPrimitives()->Print()<<"\n";
        }
    }
    
    // FIXME: why using this at all (legends are ordered but stack stays the same), isn't it better to have input correctly ?
    // in fact the legend is filled oppositely than the stack, so it is used for turning the order (but not completely, sth. is messed up !?)
    legend = ControlLegend(hists_.size(), drawhists, legends_, legend, drawHiggsOverlaid, v_higgsLabel);
    
    
    // FIXME: is this histo for error band on stack? but it is commented out ?!
    TH1D* syshist =0;
    syshist = (TH1D*)stacksum->Clone();
    for(Int_t i=0; i<=syshist->GetNbinsX(); ++i){
        Double_t binc = 0;
        binc += stacksum->GetBinContent(i);
        syshist->SetBinContent(i, binc);
    }
    syshist->SetFillStyle(3004);
    syshist->SetFillColor(kBlack);
    
    // Set x and y axis
    if(logY_)canvas->SetLogy();

    drawhists[0]->SetMinimum(ymin_);

    if(rangemin_!=0 || rangemax_!=0) {drawhists[0]->SetAxisRange(rangemin_, rangemax_, "X");}

    if(ymax_==0){
        if(logY_){drawhists[0]->SetMaximum(18  * drawhists[0]->GetBinContent(drawhists[0]->GetMaximumBin()));}
        else{drawhists[0]->SetMaximum(1.5 * drawhists[0]->GetBinContent(drawhists[0]->GetMaximumBin()));}
    }
    else{drawhists[0]->SetMaximum(ymax_);}

    drawhists[0]->GetXaxis()->SetNoExponent(kTRUE);

    TGaxis::SetMaxDigits(2);


    //Add the binwidth to the yaxis in yield plots (works only correctly for equidistant bins)
    TString ytitle = TString(drawhists[0]->GetYaxis()->GetTitle()).Copy();
    double binwidth = drawhists[0]->GetXaxis()->GetBinWidth(1);
    std::ostringstream width;
    width<<binwidth;
    if(name_.Contains("Rapidity") || name_.Contains("Eta")){ytitle.Append(" / ").Append(width.str());}
    else if(name_.Contains("pT") || name_.Contains("Mass") || name_.Contains("mass") || name_.Contains("MET") || name_.Contains("HT")){ytitle.Append(" / ").Append(width.str()).Append(" GeV");};
    drawhists[0]->GetYaxis()->SetTitle(ytitle);
    
    // Draw data histogram and stack and error bars
    drawhists[0]->Draw("e1");
    stack->Draw("same HIST");
    gPad->RedrawAxis();
    TExec *setex1 = new TExec("setex1","gStyle->SetErrorX(0.5)");//this is frustrating and stupid but apparently necessary...
    setex1->Draw();  // error bars for data
    syshist->SetMarkerStyle(0);
    //syshist->Draw("same,E2");  // error bars for stack (which, stat or combined with syst ?)
    TExec *setex2 = new TExec("setex2","gStyle->SetErrorX(0.)");
    setex2->Draw();  // remove error bars for data in x-direction
    drawhists[0]->Draw("same,e1");
    if(overlayHist)overlayHist->Draw("same");
    
    // Put additional stuff to histogram
    DrawCMSLabels(1, 8);
    DrawDecayChLabel(channelLabel_[channelType_]);
    legend->Draw("SAME");
    drawRatio(drawhists[0], stacksum, 0.5, 1.7);

    // Create Directory for Output Plots 
    gSystem->mkdir(outpathPlots_+"/"+subfolderChannel_+"/"+Systematic, true);
    canvas->Print(outpathPlots_+subfolderChannel_+"/"+Systematic+"/"+name_+".eps");
    
    // Prepare additional histograms for root-file
    TH1 *sumMC = 0; 
    TH1 *sumttbar = 0;
    for (size_t i = 0; i < hists_.size(); ++i) {
        if (legends_.at(i) != "Data") {
            if (sumMC) sumMC->Add(drawhists[i]);
            else sumMC = static_cast<TH1*>(drawhists[i]->Clone());
        }
        if (legends_.at(i) == "t#bar{t} Signal") {
            if (sumttbar) sumttbar->Add(drawhists[i]);
            else sumttbar = static_cast<TH1*>(drawhists[i]->Clone());
        }
    }
    sumMC->SetName(name_);
    
    //save Canvas AND sources in a root file
    TFile out_root(outpathPlots_+subfolderChannel_+"/"+Systematic+"/"+name_+"_source.root", "RECREATE");
    drawhists[0]->Write(name_+"_data");
    sumttbar->Write(name_+"_signalmc");
    sumMC->Write(name_+"_allmc");
    canvas->Write(name_ + "_canvas");
    out_root.Close();
    
    canvas->Clear();
    legend->Clear();
    delete canvas;
    delete legend;
}



void Plotter::setStyle(TH1 *hist, unsigned int i, bool isControlPlot)
{
    hist->SetFillColor(colors_[i]);
    hist->SetLineColor(colors_[i]);
    hist->SetLineWidth(1);

    if(legends_.at(i) == "Data"){
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
        if ((name_.Contains("pT") || name_.Contains("Mass")) && !name_.Contains("Rapidity")) {
            hist->GetXaxis()->SetTitle(XAxis_+" #left[GeV#right]");
            hist->GetYaxis()->SetTitle("#frac{1}{#sigma} #frac{d#sigma}{d"+XAxis_+"}"+" #left[GeV^{-1}#right]"); 
        } else {
            hist->GetXaxis()->SetTitle(XAxis_);
            hist->GetYaxis()->SetTitle("#frac{1}{#sigma} #frac{d#sigma}{d"+XAxis_+"}");     
        }
        if (isControlPlot) hist->GetYaxis()->SetTitle(YAxis_);
    }
}



void Plotter::MakeTable(){
    
    // Find and loop over all histograms containing information for cutflow table
    std::vector<TString> v_eventHistoName;
    v_eventHistoName = fileReader_->findHistos(dataset_[0], "step");
    for(std::vector<TString>::const_iterator i_eventHistoName = v_eventHistoName.begin(); i_eventHistoName != v_eventHistoName.end(); ++i_eventHistoName){
        
        // loop over samples and get lumi-weighted histogram
        std::vector<TH1D*> v_numhist;
        for(unsigned int i=0; i<dataset_.size(); i++){
             TH1D *temp_hist = fileReader_->GetClone<TH1D>(dataset_[i], *i_eventHistoName);
             
             double LumiWeight = CalcLumiWeight(dataset_.at(i));
             ApplyFlatWeights(temp_hist, LumiWeight);
             v_numhist.push_back(temp_hist);
        }
        
        // Scale Drell-Yan contribution
        for(unsigned int i=0; i<dataset_.size() ; i++){ // prepare histos and leg
            if((legends_.at(i) == DYEntry_) && channelType_!=2){
                // FIXME: which DY scale factor is here applied, isn't it always the same instead of the step dependent one ?
                v_numhist[i]->Scale(DYScale_.at(channelType_));
            }
        }
        
        // Prepare output folder and text file
        ofstream EventFile;
        std::string EventFilestring = outpathPlots_.Data();
        EventFilestring.append(subfolderChannel_.Data());
        EventFilestring.append(subfolderSpecial_.Data());
        gSystem->mkdir(outpathPlots_+"/"+subfolderChannel_+"/"+subfolderSpecial_, true);
        EventFilestring.append("/"+*i_eventHistoName+".txt");
        EventFile.open(EventFilestring.c_str());
        
        // Make output for tables
        double tmp_num = 0;
        double bg_num = 0;
        for(unsigned int i=0; i<dataset_.size() ; i++){
            tmp_num += v_numhist[i]->Integral();
            if(i==(hists_.size()-1)){
                EventFile<<legends_.at(i)<<": "<<tmp_num<<std::endl;
                bg_num += tmp_num;
                tmp_num = 0;
            }
            else if(legends_.at(i)!=legends_.at(i+1)){
                EventFile<<legends_.at(i)<<": "<<tmp_num<<std::endl;
                if(legends_.at(i)!="Data"){
                    bg_num+=tmp_num;
                }
                tmp_num = 0;
            }
        }
        EventFile<<"Total background: "<<bg_num<<std::endl;
        
        // Close text file
        EventFile.close();
        std::cout<<"\nEvent yields saved in "<<EventFilestring.c_str()<<"\n"<<std::endl;
    }
}



TLegend* Plotter::ControlLegend(int HistsSize, TH1* drawhists[], std::vector<TString> Legends, TLegend *leg, bool drawHiggsOverlaid, std::vector<TString> v_higgsLabel){
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
                else if(OrderedLegends[i].Contains("t#bar{t}H (b#bar{b})")){
                    TString legendTitle(OrderedLegends[i]);
                    TString legendOptions("f");
                    if(drawHiggsOverlaid)legendOptions = "l";
                    for(std::vector<TString>::const_iterator i_higgsLabel = v_higgsLabel.begin(); i_higgsLabel != v_higgsLabel.end(); ++i_higgsLabel){
                        if(i_higgsLabel->Contains(legendTitle))legendTitle = *i_higgsLabel;
                    }
                    leg->AddEntry(drawhists[j], legendTitle, legendOptions);
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

    if(weight == 0) {std::cout<<"Warning: the weight your applying is 0. This will remove your distribution."<<std::endl;}
    //if(weight >=1e3){std::cout<<"Warning: the weight your applying is >= 1e3. This will enlarge too much your distribution."<<std::endl;}
    varhists->Scale(weight);
}



double Plotter::CalcLumiWeight(const TString& WhichSample){
    if (WhichSample.Contains("run")) return 1;
    double lumiWeight=0;
    if(WhichSample!=""){
        double XSection = SampleXSection(WhichSample);
        if(XSection <= 0.){
            std::cout<<"Sample XSection is <0. Can't calculate luminosity weight!! returning"<<std::endl;
            return 0;
        }
        
        //From 'filename' get the number of weighted (MC weights) event processed.
        const TH1 *h_NrOfEvts = fileReader_->Get<TH1>(WhichSample, "weightedEvents");
        double NrOfEvts = h_NrOfEvts->GetBinContent(1);
        lumiWeight = lumi_*XSection/NrOfEvts;
    }
    
    if (lumiWeight == 0) {
        std::cout << WhichSample << " has lumi weight 0\n";
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
    else if(filename.Contains("ttbar") && !filename.Contains("ttbarH") && !filename.Contains("ttbarW") && !filename.Contains("ttbarZ")){return topxsec_;}
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
    label->AddText(Form(text, lumi_/1000, energy));
    label->SetFillStyle(0);
    label->SetBorderSize(0);
    if (textSize!=0) label->SetTextSize(textSize);
    label->SetTextAlign(32);
    label->Draw("same");
}






