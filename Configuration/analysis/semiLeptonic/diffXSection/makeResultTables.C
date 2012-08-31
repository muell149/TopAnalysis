#include "basicFunctions.h"

void makeResultTables(std::string decayChannel = "combined", bool extrapolate=true, bool hadron=false, bool addCrossCheckVariables=false, int verbose=0){
  
  // ============================
  //  Set Root Style
  // ============================

  TStyle myStyle("HHStyle","HHStyle");
  setHHStyle(myStyle);
  TGaxis::SetMaxDigits(2);
  myStyle.cd();
  gROOT->SetStyle("HHStyle");

  // ============================
  //  Open file
  // ============================
  if(extrapolate==true) hadron=false; 
  TString filename="diffXSecTopSemi";
  if(decayChannel=="combined") filename+="Lep";
  else if(decayChannel=="electron") filename+="Elec2011";
  else if(decayChannel=="muon"    ) filename+="Mu2011";
  if(extrapolate) filename+="Parton";
  else{
    if(hadron) filename+="Hadron";
    else filename+="Parton";
    filename+="PhaseSpace";
  }
  filename+=".root";
  if(verbose>0) std::cout << "opening file " << filename << std::endl;
  TFile* file = TFile::Open(filename, "READ");
  if(!file){
    std::cout << "ERROR: can not open file " << filename << std::endl;
    exit(0);
  }
  // dont associate new objects with file to be able to close it in the end
  gROOT->cd();
  // ============================
  //  Get plots
  // ============================
  // variables to be processed
  std::vector<TString> xSecVariables_;
  xSecVariables_.insert( xSecVariables_.begin(), xSecVariables, xSecVariables + sizeof(xSecVariables)/sizeof(TString));
  for(unsigned int i=0; i<xSecVariables_.size(); ++i){
    TString plotName=xSecVariables[i];
    if(verbose>0) std::cout << std::endl << "variable: " << plotName << std::endl;
    // get canvas for chosen cross section
    TCanvas* canvas = (TCanvas*)(file->Get("finalXSec/"+plotName+"Norm")->Clone());
    if(!canvas){
      std::cout << "ERROR: can not load canvas finalXSec/"+plotName+"Norm" << std::endl;
      exit(0);
    }
    // GET DATA: with final errors from canvas
    TGraphAsymmErrors* dataTot  = (TGraphAsymmErrors*)canvas->GetPrimitive("dataTotalError");
    TGraphAsymmErrors* dataStat  = (TGraphAsymmErrors*)canvas->GetPrimitive("dataStatError");
    TH1F* binned = (TH1F*)canvas->GetPrimitive(plotName);
    if(!dataTot){
      std::cout << "ERROR: can not load TGraphAsymmErrors dataTotalError in canvas finalXSec/"+plotName+"Norm" << std::endl;
      exit(0);
    }
    if(!dataStat){
      std::cout << "ERROR: can not load TGraphAsymmErrors dataStatError in canvas finalXSec/"+plotName+"Norm" << std::endl;
      exit(0);
    }
    if(!binned){
      std::cout << "ERROR: can not load TH1F topPt in canvas finalXSec/"+plotName << std::endl;
      exit(0);
    }
    //  loop all bins
    for(int bin=1; bin<=binned->GetNbinsX(); ++bin){
      if(verbose>0) std::cout << "bin #" << bin << std::endl;
      // collect information
      double MCxSec=binned->GetBinContent(bin);
      double xSec=dataTot->GetY()[bin];
      double totError=dataTot->GetErrorYhigh(bin);
      double statError=dataStat->GetErrorYhigh(bin);
      double sysError=sqrt(totError*totError-statError*statError);
      double BCCxValue=dataTot->GetX()[bin];
      double xValueUp=binned->GetBinLowEdge(bin+1);
      double xValueDn=binned->GetBinLowEdge(bin);      
      // combine information in Latex line style in one TString
      int precXSec=6;
      int precErr=1;
      int precXBCC=2;
      int precX=1;
      if(plotName.Contains("Pt")){
	precXBCC=1;
	if(plotName.Contains("Lep"  )) precXBCC=2;
	if(plotName.Contains("ttbar")) precXBCC=0;
	precX=0;	
      }
      if(plotName.Contains("Eta")||plotName.Contains("Y")){
	precXBCC=3;
	precX=1;
      }
      if(plotName.Contains("Mass")){
	precXBCC=1;
	precX=0;
      }
      TString out= "";
      out+=getTStringFromDouble(BCCxValue+5./(pow(10,precXBCC+1)), precXBCC);
      out+=" &  ";			  
      out+=getTStringFromDouble(xValueDn +5./(pow(10,precX   +1)), precX   );
      out+=" to  ";			  
      out+=getTStringFromDouble(xValueUp +5./(pow(10,precX   +1)), precX   );
      out+=" & ";
      out+=getTStringFromDouble(MCxSec+5./(pow(10,precXSec+1)), precXSec);
      out+="  & ";
      out+=getTStringFromDouble(xSec  +5./(pow(10,precXSec+1)), precXSec);
      out+=" &  ";
      out+=getTStringFromDouble(100*(statError/xSec)+5./(pow(10,precErr+1)),  precErr);
      out+=" &  ";
      out+=getTStringFromDouble(100*(sysError/xSec )+5./(pow(10,precErr+1)),  precErr);
      out+=" &  ";
      out+=getTStringFromDouble(100*(totError/xSec )+5./(pow(10,precErr+1)),  precErr);
      out+=" \\\\ ";
      bool append= (bin==1 ? false : true);
      TString txtfile="./diffXSecFromSignal/"+filename;
      txtfile.ReplaceAll(".root",plotName+".txt");
      writeToFile(out, txtfile, append);
      std::cout << out << std::endl;
      //std::cout << BCCxValue << " &  " << xValueDn << " to  " << xValueUp << " & " << MCxSec << "  & " << xSec << " &  " << statError/xSec << " &  " << sysError/xSec << " &  " << totError/xSec << " \\\\ " << std::endl;
      if(verbose>0) std::cout << std::setprecision(7) << std::fixed<< xSec << "+/-" << statError << "+/-" << sysError << std::endl;
      if(verbose>0) std::cout << std::setprecision(7) << std::fixed << "xvalue: " << BCCxValue << " (" << xValueDn << ".." << xValueUp << ")" << std::endl;
    }
  }
}
