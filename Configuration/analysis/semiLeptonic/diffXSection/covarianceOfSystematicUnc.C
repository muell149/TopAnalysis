#include "basicFunctions.h"

void covarianceOfSystematicUnc(bool save=false, unsigned int verbose=1, TString decayChannel="combined", bool extrapolate=true, bool hadron=false, TString closureTestSpecifier=""){
  
  // print info if up/down errors are asymmetric or very different in size
  bool check=false;
  // verbose = 0: no output, 
  //           1: + print basic options, final covariance matrices, initial and final uncertainties and number of bins with up/down in same direction
  //           2: + single systematic uncertainties, some save information
  //           3/4+ debufg and detail output
  // ======================================
  //  Nomenclature- Systematic Variations:
  // ======================================
  //         0: sysNo                                                       
  //         1: sysLumiUp                   2: sysLumiDown                 
  //         3: sysPUUp                     4: sysPUDown                   
  //         5: sysJESUp                    6: sysJESDown                  
  //         7: sysJERUp                    8: sysJERDown                  
  //         9: sysLepEffSFNormUp          10: sysLepEffSFNormDown         
  //        11: sysLepEffSFShapeUpEta      12: sysLepEffSFShapeDownEta     
  //        13: sysLepEffSFShapeUpPt       14: sysLepEffSFShapeDownPt      
  //        15: sysBtagSFUp                16: sysBtagSFDown               
  //        17: sysBtagSFShapeUpPt65       18: sysBtagSFShapeDownPt65      
  //        19: sysBtagSFShapeUpEta0p7     20: sysBtagSFShapeDownEta0p7    
  //        21: sysMisTagSFUp              22: sysMisTagSFDown             
  //        23: sysTopScaleUp              24: sysTopScaleDown             
  //        25: sysVBosonScaleUp           26: sysVBosonScaleDown          
  //        27: sysSingleTopScaleUp        28: sysSingleTopScaleDown       
  //        29: sysTopMatchUp              30: sysTopMatchDown             
  //        31: sysVBosonMatchUp           32: sysVBosonMatchDown  
  //        33: sysTopMassUp               34: sysTopMassDown  
  //        35: sysTopMassUp2              36: sysTopMassDown2
  //        37: sysTopMassUp3              38: sysTopMassDown3
  //        39: sysTopMassUp4              40: sysTopMassDown4
  //        41: sysQCDUp                   42: sysQCDDown                  
  //        43: sysSTopUp                  44: sysSTopDown                 
  //        45: sysDiBosUp                 46: sysDiBosDown 
  //        47: sysVjetsUp                 48: sysVjetsDown
  //        49: sysBRUp                    50: sysBRDown              
  //        51: sysPDFUp                   52: sysPDFDown                  
  //        53: sysHadUp                   54: sysHadDown                  
  //        55: sysGenMCatNLO              56: sysGenPowheg  
  //        57: sysGenPowhegHerwig         58: ENDOFSYSENUM
 
  // ============================
  //  Set Root Style
  // ============================

  TStyle myStyle("HHStyle","HHStyle");
  setHHStyle(myStyle);
  TGaxis::SetMaxDigits(2);
  myStyle.cd();
  gROOT->SetStyle("HHStyle");
  gStyle->SetErrorX(0.5); // needed to keep the functions alive drawn with DrawSteps
  gROOT->SetBatch(); // you dont want to see all canvas
  gStyle->SetPaintTextFormat("1.3e");
  gStyle->SetOptTitle(1);

  // ============================
  // Input=Output File
  // ============================
  // choose phase space
  TString PS="";
  // a) for full PS use extrapolate=true;
  if(!extrapolate) PS="PhaseSpace";
  // b) for restricted phase space:
  // b1) parton PS: hadron=false
  // b2) hadron PS: hadron=true
  TString LV="Parton";
  if(!extrapolate&&hadron) LV="Hadron";
  if(verbose>1){
    if(extrapolate) std::cout << "full Phase Space will be used!" << std::endl; 
    else std::cout << LV << " level Phase Space will be used!" << std::endl; 
  } 
  TString universalplotLabel = extrapolate ? "FullPS" : LV+"LvPS";  
  // dataSample: see if its "2010" or "2011" data
  TString dataSample="2012";
  // for closure test if desired
  TString closureLabel = "";
  if      (closureTestSpecifier.Contains("Up") || closureTestSpecifier.Contains("Down") || closureTestSpecifier.Contains("NoDistort")) closureLabel = "SysDistort"+closureTestSpecifier;
  else if (closureTestSpecifier.Contains("500") || closureTestSpecifier.Contains("750")) closureLabel = "Zprime"+closureTestSpecifier;
  // outputFile: target rootfile
  // NOTE: this must be identical with TString outputFileName 
  // in analyzeHypothesisKinFit.C
  TString outputFile="diffXSecTopSemi";
  if(decayChannel=="muon"    ) outputFile+="Mu"+closureLabel;
  if(decayChannel=="electron") outputFile+="Elec"+closureLabel;
  if(decayChannel=="combined") outputFile+="Lep"+closureLabel;
  outputFile+=LV+PS+".root";
  // specify folder (within Input rootfile) where XSec plots are stored
  TString xSecFolder = "xSec";

  // ============================
  // Output Folder
  // ============================
  // save all plots into the following folder
  TString outputFolder = "./diffXSecFromSignal/plots/"+decayChannel+"/";
  if(dataSample!="") outputFolder+=dataSample;
  outputFolder+="/cov/";

  // =============================
  // Define Variables of Interest
  // =============================
  
  // ( xSecVariables... are centrally defined in basicFunctions.h)
  // NOTE: these must be identical to those defined in xSecVariables_ in analyzeHypothesisKinFit.C

  std::vector<TString> xSecVariables_;
  // a) top and ttbar quantities
  if(!hadron){
    //xSecVariables_.insert(xSecVariables_.end(), xSecVariablesKinFit    , xSecVariablesKinFit     + sizeof(xSecVariablesKinFit    )/sizeof(TString));
    xSecVariables_.insert(xSecVariables_.end(), xSecVariablesKinFitNorm, xSecVariablesKinFitNorm + sizeof(xSecVariablesKinFitNorm)/sizeof(TString));
  }
  // b) lepton and b-jet quantities
  if(hadron||!extrapolate){
    //xSecVariables_.insert(xSecVariables_.end(), xSecVariablesFinalState    , xSecVariablesFinalState     + sizeof(xSecVariablesFinalState    )/sizeof(TString));
    xSecVariables_.insert(xSecVariables_.end(), xSecVariablesFinalStateNorm, xSecVariablesFinalStateNorm + sizeof(xSecVariablesFinalStateNorm)/sizeof(TString));
  }

  // ==========
  // Container
  // ==========
  // for data result plots 
  std::map< TString, std::map <unsigned int, TH1F*> > histo_;
  // for covariance result plots 
  std::map< TString, std::map <unsigned int, TH2F*> > sysCov_;
  // for uncertainties that will be excluded
  std::map< TString, std::map<unsigned int, bool> > considerSys_;
  // for absolute uncertainty values
  std::map< TString, std::map < TString, std::vector <double > > > unc_;
  std::map< TString, std::map < TString, std::vector <double > > > uncIter_;
  // for data result plots 
  std::map< TString, std::map <TString, TH1F*> > histoSysShift_;
  // for canvas
  std::vector<TCanvas*> plotCanvas_;
  std::vector<TCanvas*> plotCanvasTot_;

  // ==================
  // Control printout
  // ==================
  if(verbose>1){
    std::cout << std::endl;
    std::cout << " Executing covarianceOfSystematicUnc with " << dataSample << " data" << std::endl;
    std::cout << std::endl;
    std::cout << " Target file: " << outputFile << std::endl;
    std::cout << " Target variables for covariance calculation:" << std::endl;

    // loop variables
    for(unsigned int i=0; i<xSecVariables_.size(); ++i){
      std::cout << xSecVariables_[i]; 
      if(i<xSecVariables_.size()-1) std::cout << ", ";
      else std::cout << std::endl;
    }
    std::cout << " Target folder containing covariance plots: " << outputFolder << std::endl;
    if(save) std::cout << " Final plots will be saved in " << outputFile << " and as .eps in " << outputFolder << std::endl;
  }

  // ============================
  //  Open Input File
  // ============================
  TFile* file = TFile::Open(outputFile, "UPDATE");
  if(verbose>3) std::cout << " Opened file "+outputFile << std::endl;

  // Proceed only if file exists and is not broken    
  if(!file || file->IsZombie()){
    std::cout << "ERROR: Target file does not exist or is broken!" << std::endl;
    exit(0);
  }
  else if(verbose>3) std::cout << " Target file found!" << std::endl;
  
  // ===============================================================
  //  Get all data xSecs for all systematic variations
  // ===============================================================
  // printout
  if(verbose>1) std::cout << std::endl << "Loading Plots" << std::endl;
  // loop all systematic variations
  for(unsigned int sys=sysNo; sys<ENDOFSYSENUM; ++sys){
    TString subfolder=sysLabel(sys);      
    // loop all variables
    for(unsigned int i=0; i<xSecVariables_.size(); ++i){
      // get canvas       
      TCanvas* canvas = (TCanvas*)file->Get(xSecFolder+"/"+subfolder+"/"+xSecVariables_[i]);	
      if(canvas){
	// get data plot for all systematics
	TString plotName = xSecVariables_[i];
	plotName.ReplaceAll("Norm","");
	TH1F* plot= (TH1F*)canvas->GetPrimitive(plotName+"kData");
	if(plot){ 
	  if(verbose>2) std::cout << " Plot "+plotName+"kData found in "+xSecFolder+"/"+subfolder+"/"+xSecVariables_[i] << std::endl;
	  // go to root directory, keep plot when closing rootfile
	  gROOT->cd();	    
	  histo_[xSecVariables_[i]][sys]=(TH1F*)(plot->Clone());
	  considerSys_[xSecVariables_[i]][sys]=considerInTotalError(sys);
	  // FIXME: no generator uncertainties considered for final errors
	  if(sys==sysGenPowheg||sys==sysGenPowhegHerwig||sys==sysGenMCatNLO) considerSys_[xSecVariables_[i]][sys]=false;
	  // sysHadUp   -> Hadronization: POWHEG+PYTHIA cs. POWHEG+HERWIG
	  // sysHadDown -> Generator: MC@NLO+HERWIG vs. POWHEG+HERWIG
	  if(sys==sysHadDown) considerSys_[xSecVariables_[i]][sys]=false;
	  if(sys==sysHadUp  ) considerSys_[xSecVariables_[i]][sys]=false;
	  // sysHadronizationOld=MC@NLO+HERWIG vs. POWHEG+PYTHIA
	  if(sys==ENDOFSYSENUM-1){ considerSys_[xSecVariables_[i]][ENDOFSYSENUM]=true; }
	} // end if(plot)
	else if(verbose>2) std::cout << "ERROR: Plot " << plotName +"kData not found in "+ xSecFolder+"/"+subfolder+"/"+xSecVariables_[i] << std::endl;
      } // end if(canvas)
    } // end for xSecVariables_ loop
  } // end for sys loop

  // INFO printout
  if(verbose>2){
    std::cout << std::endl << "considered uncertainties: " << std::endl;
    // loop all variables
    for(unsigned int i=0; i<xSecVariables_.size(); ++i){
      std::cout << "- for " << xSecVariables_[i] << ": " << std::endl;
      // loop all systematics
      for(unsigned int sys=sysNo+1; sys<=ENDOFSYSENUM; ++sys){
	if(considerSys_[xSecVariables_[i]].count(sys)>0&&considerSys_[xSecVariables_[i]][sys]==true){
	  std::cout << "  "<< std::endl;
	  if(sys>sysNo+1) std::cout << ", "<< std::endl;
	  if(sys==ENDOFSYSENUM) std::cout << "sysHadronizationOld=MC@NLO+HERWIG vs. POWHEG+PYTHIA";
	  else if(sys==sysHadUp  ) std::cout << "Hadronization: POWHEG+PYTHIA cs. POWHEG+HERWIG";
	  else if(sys==sysHadDown) std::cout << "Generator: MC@NLO+HERWIG vs. POWHEG+HERWIG";
	  else std::cout << sysLabel(sys);
	} // end if consider
      } // end for sys loop
      std::cout << std::endl << std::endl;
    } // end for xSecVariables_ loop
  } // end if verbose

  // ==================================
  //  Calculate Relative Uncertainties
  // ==================================
  std::vector<TString> symmUncLabel_;
  // printout
  if(verbose>1) std::cout << std::endl << "Calculate Initial Uncertainty Shift" << std::endl;
  // loop all variables
  for(unsigned int i=0; i<xSecVariables_.size(); ++i){
    // printout
    if(verbose>1) std::cout << std::endl << xSecVariables_[i] << std::endl;
    int numTot=0;
    int numAsymm=0;
    // loop all systematic variations
    for(unsigned int sys=sysNo+1; sys<=ENDOFSYSENUM; ++sys){
      // check if uncertainty should be considered
      if(considerSys_[xSecVariables_[i]].count(sys)>0&&considerSys_[xSecVariables_[i]][sys]==true){ 
	// process down and up (symmetrization) for up variation
	TString systLabel = (sys<ENDOFSYSENUM ? sysLabel(sys) : "sysHadronizationOld");
	if(systLabel.Contains("Hadronization")||(!systLabel.Contains("down")&&!systLabel.Contains("Down"))){
	  // check if up/down systematics
	  bool symm=false;
	  if(!systLabel.Contains("Hadronization")&&(systLabel.Contains("up")||systLabel.Contains("Up"))) symm=true;
	  // save name of considered uncertainty
	  systLabel.ReplaceAll("up", "");
	  systLabel.ReplaceAll("Up", "");
	  systLabel.ReplaceAll("Down", "");
	  systLabel.ReplaceAll("down", "");
	  if(sys==sysHadUp         ) systLabel="sysHadronizationNew";
	  else if(sys==sysHadDown  ) systLabel="sysGenerator";
	  else if(sys==ENDOFSYSENUM) systLabel="sysHadronizationOld";
	  if(i==0) symmUncLabel_.push_back(systLabel);
	  // printout
	  if(verbose>1) std::cout << "  - " << systLabel << std::endl;
	  // loop all bins
	  for(int bin=1; bin<=histo_[xSecVariables_[i]][sysNo]->GetNbinsX(); ++bin){
	    double xSecStd    = histo_[xSecVariables_[i]][sysNo]->GetBinContent(bin);
	    double binEdgeDown= histo_[xSecVariables_[i]][sysNo]->GetBinLowEdge(bin);
	    double binEdgeUp  = histo_[xSecVariables_[i]][sysNo]->GetBinLowEdge(bin+1);
	    double dBin=0;
	    // up/down uncertainties -> symmetrization
	    if(symm){ 
	      double xSecUp=histo_[xSecVariables_[i]][sys  ]->GetBinContent(bin);
	      double xSecDn=histo_[xSecVariables_[i]][sys+1]->GetBinContent(bin);
	      double dUp=xSecUp-xSecStd;
	      double dDn=xSecDn-xSecStd;
	      // linear rescaling of top mass uncertainty
	      if(sys==sysTopMassUp||sys==sysTopMassDown){
		dUp*=SF_TopMassUpUncertainty;
		dDn*=SF_TopMassDownUncertainty;
	      }
	      dBin=0.5*(std::abs(dUp)+std::abs(dDn));
	      bool show=false;
	      numTot++;
	      if((dUp/std::abs(dUp))==(dDn/std::abs(dDn))){ numAsymm++; if(check){std::cout << "NOTE: UP/DN IN SAME DIRECTION!"<< std::endl; show=true;} }
	      double updndiff=(std::abs(100*dUp/xSecStd)-std::abs(100*dDn/xSecStd))/(std::abs(100*dUp/xSecStd));
	      if(updndiff>0.3&&std::abs(100*dUp/xSecStd)>0.5){ if(check){std::cout << ">30% DIFF between UP/DN! "<< std::endl; show=true;} }
	      if(show){
		std::cout << xSecVariables_[i] << ", " << systLabel << ", bin #" << bin << ":" << std::endl;
		std::cout << "up: " << dUp << std::endl;
		std::cout << "dn: " << dDn << std::endl;
	      }
	      // store sign of upwards variation
	      double sign= ( dUp==0. ? 1. : (dUp/std::abs(dUp)) );
	      dBin*=sign;
	      // in case up and down go in the same direction...
	      if((dUp/std::abs(dUp))==(dDn/std::abs(dDn))){
		// ... the variation with the larger shift keeps this sign
		// (which means flipping the sign for the up variation if the down is larger)
		if(std::abs(dUp)<std::abs(dDn)) dBin*=(-1.);
	      } // end if abs
	    } // end if symm
	    else{
	      // special (by hand filled) uncertainties
	      // (use sign of the variation as sign of the up variation)
	      if     (sys==sysHadUp    ) dBin=histo_[xSecVariables_[i]][sysGenPowhegHerwig]->GetBinContent(bin)-histo_[xSecVariables_[i]][sysGenPowheg ]->GetBinContent(bin);
	      else if(sys==sysHadDown  ) dBin=histo_[xSecVariables_[i]][sysGenPowhegHerwig]->GetBinContent(bin)-histo_[xSecVariables_[i]][sysGenMCatNLO]->GetBinContent(bin);
	      else if(sys==ENDOFSYSENUM) dBin=histo_[xSecVariables_[i]][sysGenMCatNLO     ]->GetBinContent(bin)-histo_[xSecVariables_[i]][sysGenPowheg ]->GetBinContent(bin);
	      // uncertainties without symmetrization
	      else dBin=histo_[xSecVariables_[i]][sys]->GetBinContent(bin)-xSecStd;
	    }
	    // save absolute uncertainties for variable and uncertainty
	    unc_[xSecVariables_[i]][systLabel].push_back(dBin);
	    // add unc. for total syst. unc.
	    double relUncPercBin=100*(dBin/xSecStd);
	    if(sys==sysNo+1) unc_[xSecVariables_[i]]["all"].push_back(relUncPercBin*relUncPercBin);
	    else unc_[xSecVariables_[i]]["all"][bin-1]+=relUncPercBin*relUncPercBin;
	    // printout
	    if(verbose>1){
	      std::cout << "    bin #" << bin;
	      if(systLabel==symmUncLabel_[0]) std::cout << "(" << binEdgeDown << ".." << binEdgeUp << ")";
	      std::cout << ": " << 100*(dBin/xSecStd) << "%" << std::endl;
	    } // end if verbose
	    // last bin and systematic: total systematic uncertainty
	    if(verbose>1&&sys==ENDOFSYSENUM&&bin==histo_[xSecVariables_[i]][sysNo]->GetNbinsX()){
	      std::cout << "-----------------------------" << std::endl;
	      std::cout << "total syst. uncertainty " << std::endl;
	      // loop all bins
	      for(int bin2=1; bin2<=histo_[xSecVariables_[i]][sysNo]->GetNbinsX(); ++bin2){  
		std::cout << "bin #" << bin2 << ": " << sqrt(unc_[xSecVariables_[i]]["all"][bin2-1]) << "%" << std::endl;
	      } //end for bin2 loop
	    } // end if last systematic, bin and if verbose	    
	  } // end for bin loop
	} // end if !label
      } // end if consider  
    } // end for sys loop
    if(verbose>0) std::cout << "fraction of bins with up/down in same direction (" << xSecVariables_[i] << "): " << 100*numAsymm/numTot << "%" << std::endl;
  } // end for xSecVariables_ loop
  
  
  // ============================================
  // Redetermine symmetrized cross Section values
  // ============================================
  // printout
  if(verbose>1) std::cout << std::endl << "Normalize symmetrized up/down cross sections again" << std::endl;
  double Nconsider=0;
  double totdev=0;
  double totdevsign=0;
  // loop all variables
  for(unsigned int i=0; i<xSecVariables_.size(); ++i){
    // printout
    if(verbose>2) std::cout << std::endl << xSecVariables_[i] << std::endl;
    // loop all systematic variations
    for(unsigned int sys=sysNo+1; sys<=ENDOFSYSENUM; ++sys){
      // check if uncertainty that should be considered
      if(considerSys_[xSecVariables_[i]].count(sys)>0&&considerSys_[xSecVariables_[i]][sys]==true){
	// clone default plot
	histoSysShift_[xSecVariables_[i]][sys]=(TH1F*)histo_[xSecVariables_[i]][sysNo]->Clone(TString(histo_[xSecVariables_[i]][sysNo]->GetName())+"iter");
	// get label
	TString systLabel = (sys<ENDOFSYSENUM ? sysLabel(sys) : "sysHadronizationOld");
	if(sys==sysHadUp         ) systLabel="sysHadronizationNew";
	else if(sys==sysHadDown  ) systLabel="sysGenerator";
	else if(sys==ENDOFSYSENUM) systLabel="sysHadronizationOld";
	TString systStripLabel=systLabel;
	systStripLabel.ReplaceAll("up", "");
	systStripLabel.ReplaceAll("Up", "");
	systStripLabel.ReplaceAll("Down", "");
	systStripLabel.ReplaceAll("down", "");	
	// clone uncertainty values values (will be adapted for up/down variation iterions)
	uncIter_[xSecVariables_[i]][systStripLabel]=unc_[xSecVariables_[i]][systStripLabel];
	// reprocess only up/down systematics
	if(systLabel.Contains("up")||systLabel.Contains("Up")||systLabel.Contains("Down")||systLabel.Contains("down")){
	  if(verbose>3) std::cout << systLabel << std::endl;
	  // loop bins
	  for(unsigned int bin=1; bin<=(unsigned int)histoSysShift_[xSecVariables_[i]][sys]->GetNbinsX(); ++bin){
	    if(verbose>3) std::cout << "bin" << bin << std::endl;
	    // get symmetrized uncertainties
	    double xSecStd     =histo_[xSecVariables_[i]][sysNo         ]->GetBinContent(bin);
	    double symmSysShift=unc_  [xSecVariables_[i]][systStripLabel].at(bin-1);
	    // inverse sign for down variation	    
	    if(systLabel.Contains("down")||systLabel.Contains("Down")) symmSysShift*=-1;
	    // create symmetrized uncertainty histo
	    if(verbose>3) std::cout << xSecStd << " + " << symmSysShift << std::endl;
	    histoSysShift_[xSecVariables_[i]][sys]->SetBinContent(bin, xSecStd+symmSysShift);
	  } // end for loop bins
	  // do normalization
	  double area=getInclusiveXSec(histoSysShift_[xSecVariables_[i]][sys],verbose-2);
	  if(verbose>3) std::cout << "area is: " << area << std::endl;
	  histoSysShift_[xSecVariables_[i]][sys]->Scale(1./area);
	  // for down variations... 
	  if(systLabel.Contains("Down")||systLabel.Contains("down")){
	    // ... redetermine uncertainty
	    if(verbose>3) std::cout << "variation " << systStripLabel << std::endl;
	    // loop bins
	    for(unsigned int bin=1; bin<=(unsigned int)histoSysShift_[xSecVariables_[i]][sys]->GetNbinsX(); ++bin){
	      double xSecStd=histo_        [xSecVariables_[i]][sysNo]->GetBinContent(bin);
	      // symmetrized and newly normalized uncertainty value
	      double xSecUp =histoSysShift_[xSecVariables_[i]][sys-1]->GetBinContent(bin);
	      double xSecDn =histoSysShift_[xSecVariables_[i]][sys  ]->GetBinContent(bin);
	      double dUp=xSecUp-xSecStd;
	      double dDn=xSecDn-xSecStd;	      
	      // old uncertainty value
	      double xSecOldUp =histo_[xSecVariables_[i]][sys-1]->GetBinContent(bin);
	      double xSecOldDn =histo_[xSecVariables_[i]][sys  ]->GetBinContent(bin);
	      double dOldUp=xSecOldUp-xSecStd;
	      double dOldDn=xSecOldDn-xSecStd;	   
	      if(verbose>3){
		std::cout << "  bin #" << bin << std::endl;
		std::cout << "  up: " << 100*dOldUp/xSecStd << "% -> " << 100*dUp/xSecStd << "%" << std::endl;
		std::cout << "  dn: " << 100*dOldDn/xSecStd << "% -> " << 100*dDn/xSecStd << "%" << std::endl;
	      }
	      // store new symmetrized value
	      double dBin=0.5*(std::abs(xSecUp-xSecStd)+std::abs(xSecDn-xSecStd));
	      // store sign of upwards variation
	      double sign= ( dUp==0. ? 1. : (dUp/std::abs(dUp)) );
	      dBin*=sign;
	      if(verbose>3) std::cout << "  symmetrized: " << 100*unc_  [xSecVariables_[i]][systStripLabel].at(bin-1)/xSecStd << " -> " << 100*dBin/xSecStd << std::endl;
	      uncIter_  [xSecVariables_[i]][systStripLabel].at(bin-1)=dBin;
	    } // end for loop bins
	  } // end if down
	} // end if up/down
      } // end if consider  
    } // end for sys loop
    // printout change in total uncertainty
    if(verbose>0){
      std::cout << "=> final total uncertainty (" << xSecVariables_[i] << "): " << std::endl;
      // loop bins
      for(unsigned int bin=1; bin<=(unsigned int)histo_[xSecVariables_[i]][sysNo]->GetNbinsX(); ++bin){	
	double binEdgeDown= histo_[xSecVariables_[i]][sysNo]->GetBinLowEdge(bin);
	double binEdgeUp  = histo_[xSecVariables_[i]][sysNo]->GetBinLowEdge(bin+1);
	if(verbose>0) std::cout << "     bin #" << bin << "(" << binEdgeDown << ".." << binEdgeUp << ")" << std::endl;
	double totErr    =0.;
	double totErrIter=0.;
	// add all different uncertainties
	for(unsigned int lab=0; lab<symmUncLabel_.size(); ++lab){
	  TString uncLab=symmUncLabel_[lab];
	  totErr    +=(unc_    [xSecVariables_[i]][symmUncLabel_[lab]].at(bin-1)*unc_    [xSecVariables_[i]][symmUncLabel_[lab]].at(bin-1));
	  totErrIter+=(uncIter_[xSecVariables_[i]][symmUncLabel_[lab]].at(bin-1)*uncIter_[xSecVariables_[i]][symmUncLabel_[lab]].at(bin-1));
	}
	// printout of relative uncertainty
	double xSecStd=histo_[xSecVariables_[i]][sysNo]->GetBinContent(bin);
	double old   =100*sqrt(totErr)    /xSecStd;
	double latest=100*sqrt(totErrIter)/xSecStd;
	double relChange=100*std::abs(old-latest)/old;
	double changeSign=(latest-old)/std::abs(old-latest);
	if(relChange<100.&&old<50.){
	  ++Nconsider;
	  totdev+=relChange;
	  totdevsign+=(changeSign*relChange);
	}
	if(verbose>0){
	  std::cout << "      " << old << "% -> " << latest << "% (=";
	  if     (relChange<=5. ) std::cout << "\033[42m\033[1m";
	  else if(relChange<=10.) std::cout << "\033[33m\033[43m\033[1m";
	  else                    std::cout << "\033[33m\033[41m\033[1m";
	  std::cout << changeSign*relChange << "% \033[0m relative change)";
	  std::cout << std::endl;
	  if(bin==(unsigned int)histo_[xSecVariables_[i]][sysNo]->GetNbinsX()&&i==xSecVariables_.size()-1){
	    std::cout << "average abs change: " << totdev/Nconsider << std::endl;
	    std::cout << "average change: " << totdevsign/Nconsider << std::endl;
	  }
	} // end if verbose
      } // for loop bins
    } // end if verbose
  } // end for xSecVariables_ loop

  // ============================
  // Determine covariance Matrix
  // ============================
  // printout
  if(verbose>0) std::cout << std::endl << "Determine Covariance Matrices" << std::endl;
  // loop all variables
  for(unsigned int i=0; i<xSecVariables_.size(); ++i){
    // printout
    if(verbose>1) std::cout << std::endl << "- for " << xSecVariables_[i] << std::endl;
    // loop relevant symmetrized systematic variations
    for(unsigned int sys=0; sys<(unsigned int)symmUncLabel_.size(); ++sys){
      if(verbose>2){
	std::cout <<  symmUncLabel_[sys];
	if(sys<(unsigned int)symmUncLabel_.size()-1) std::cout << ", ";
      }
      else std::cout << ".";
      if(sys==(unsigned int)symmUncLabel_.size()-1) std::cout << std::endl;
      // create 2D covariance matrix for current systematic
      int Nbins=uncIter_[xSecVariables_[i]][symmUncLabel_[sys]].size();
      TH2F* tempCovSys= new TH2F("tempCovSys","tempCovSys", Nbins, 0., Nbins, Nbins, 0., Nbins);
      tempCovSys->GetXaxis()->SetNoExponent(true);
      tempCovSys->GetYaxis()->SetNoExponent(true);
      // adjust bin label
      for(unsigned int bin=1; bin<=(unsigned int)histo_[xSecVariables_[i]][sysNo]->GetNbinsX(); ++bin){
	double edgeDown=histo_[xSecVariables_[i]][sysNo]->GetBinLowEdge(bin);
	double edgeUp=histo_[xSecVariables_[i]][sysNo]->GetBinLowEdge(bin+1);
	TString binlabelX="#splitline{"+getTStringFromDouble(edgeDown,getRelevantDigits(edgeDown))+"}{#splitline{  -}{"+getTStringFromDouble(edgeUp,getRelevantDigits(edgeUp))+"}}";
	TString binlabelY=getTStringFromDouble(edgeDown,getRelevantDigits(edgeDown))+" - "+getTStringFromDouble(edgeUp,getRelevantDigits(edgeUp));
	tempCovSys->GetXaxis()->SetBinLabel(bin, binlabelX);
	tempCovSys->GetYaxis()->SetBinLabel(bin, binlabelY);
      }
      // double bin loop for filling the covariance matrix
      for(unsigned int bini=1; bini<=(unsigned int)Nbins; ++bini){
	for(unsigned int binj=1; binj<=(unsigned int)Nbins; ++binj){
	  // fill value: cov(i,j)=unc_bini * unc_binj
	  // (use sign from up variation after one iteration and the symmetrization, see definition above)
	  double covij=uncIter_[xSecVariables_[i]][symmUncLabel_[sys]].at(bini-1)* uncIter_[xSecVariables_[i]][symmUncLabel_[sys]].at(binj-1);
	  tempCovSys->SetBinContent(bini, binj, covij);
	} // end for loop binj
      } // end for loop bini
      // add covariance matrix of current systematic to total covariance matrix
      sysCov_[xSecVariables_[i]][sys]=(TH2F*)tempCovSys->Clone(symmUncLabel_[sys]);
      if(sys==0) sysCov_[xSecVariables_[i]][42]=(TH2F*)tempCovSys->Clone("covSysTot");
      else sysCov_[xSecVariables_[i]][42]->Add((TH2F*)tempCovSys->Clone(symmUncLabel_[sys]));
      // histo style of covariance matrices
      TString nameSys=TString("covSys")+xSecVariables_[i]+symmUncLabel_[sys];      
      histStyle2D(*sysCov_[xSecVariables_[i]][sys], nameSys+"plot", "", "");
      sysCov_[xSecVariables_[i]][sys]->SetTitle("covariance matrix of "+xSecVariables_[i]+"("+symmUncLabel_[sys]+")");
      // save plot for current systematic
      // create new canvas
      addCanvas(plotCanvas_);
      // go to canvas 
      plotCanvas_[plotCanvas_.size()-1]->cd();
      //plotCanvas_[plotCanvas_.size()-1]->SetRightMargin(0.10);
      plotCanvas_[plotCanvas_.size()-1]->SetGrid(1,1);
      plotCanvas_[plotCanvas_.size()-1]->SetName( nameSys+"canv");
      plotCanvas_[plotCanvas_.size()-1]->SetTitle(nameSys+"canv");
      // print plot 
      //sysCov_[xSecVariables_[i]][sys]->Draw("colz");
      sysCov_[xSecVariables_[i]][sys]->Draw("text");
      // last systematic:
      if(sys==(unsigned int)symmUncLabel_.size()-1){
	// style of total systematic covariance matrix
	TString nameTot=TString("SysCovMatrix")+xSecVariables_[i]+"Tot";
	histStyle2D(*sysCov_[xSecVariables_[i]][42], nameTot+"plot", "", "");
	TString sysHistLabel="covariance matrix of "+xSecVariables_[i];
	if(xSecVariables_[i].Contains("Pt")||xSecVariables_[i].Contains("Mass")) sysHistLabel+="[GeV]";
	sysHistLabel+=" (total systematic)";
	sysCov_[xSecVariables_[i]][42]->SetTitle(sysHistLabel);
	// print total systematic covariance matrix
	// create new canvas
	addCanvas(plotCanvasTot_);
	// go to canvas 
	plotCanvasTot_[plotCanvasTot_.size()-1]->cd();
	//plotCanvasTot_[plotCanvasTot_.size()-1]->SetRightMargin(0.10);
	//plotCanvasTot_[plotCanvasTot_.size()-1]->SetLeftMargin(0.10);
	plotCanvasTot_[plotCanvasTot_.size()-1]->SetGrid(1,1);
	plotCanvasTot_[plotCanvasTot_.size()-1]->SetName( nameTot+"canv");
	plotCanvasTot_[plotCanvasTot_.size()-1]->SetTitle(nameTot+"canv");
	// print plot 
	//sysCov_[xSecVariables_[i]][42]->DrawClone("axis");
	sysCov_[xSecVariables_[i]][42]->Draw("text");
      }// end if last sys
      delete tempCovSys;
    } // end for loop symmetrized systematic variations
    // printout
    if(verbose>0){
      // double bin loop for filling the covariance matrix
      int Nbins=uncIter_[xSecVariables_[i]][symmUncLabel_[0]].size();
      std::cout << "cov(i,j) [" << xSecVariables_[i] << "]=" << std::endl;
      for(unsigned int bini=1; bini<=(unsigned int)Nbins; ++bini){
	for(unsigned int binj=1; binj<=(unsigned int)Nbins; ++binj){
	  double value=sysCov_[xSecVariables_[i]][42]->GetBinContent(bini, binj);
	  if(value>0) std::cout << " ";
	  std::cout << std::setprecision(3) << std::scientific << sysCov_[xSecVariables_[i]][42]->GetBinContent(bini, binj) << "  ";
	  if(binj==(unsigned int)Nbins) std::cout << std::endl;
	} // end for loop binj
      } // end for loop bini
      std::cout << "tot. syst. uncertainty[%]: " << std::endl;
      for(unsigned int bink=1; bink<=(unsigned int)Nbins; ++bink){
	double value=sqrt(sysCov_[xSecVariables_[i]][42]->GetBinContent(bink, bink))/histo_[xSecVariables_[i]][sysNo]->GetBinContent(bink);
	std::cout << std::setprecision(2) << std::fixed << 100*value;
	if(bink<(unsigned int)Nbins) std::cout << ", ";
	else std::cout << std::endl;
      } // end for loop bink
    } // end if verbose 
  } // end for loop xSecVariables
  
  // close file
  file->Close();

  // ==========
  // Do Saving
  // ==========
  if(save){
    // printout
    if(verbose>0) std::cout << std::endl << "Do Saving" << std::endl;
    if(verbose==0) gErrorIgnoreLevel=kWarning;
    // a)  Save as pictures
    if(verbose>0) std::cout << "a) as pictures" << std::endl;
    saveCanvas(plotCanvasTot_, outputFolder, "covarianceMatricesTot"      , true, true , true );
    saveCanvas(plotCanvas_   , outputFolder, "covarianceMatricesSingleSys", true, false, false);
    // b) Save in rootfile
    if(verbose>0) std::cout << "b) in rootfile" << std::endl;
    // loop all variables
    for(unsigned int i=0; i<xSecVariables_.size(); ++i){
      // i)  total systematic covariance matrix
      saveToRootFile(outputFile, sysCov_[xSecVariables_[i]][42], true, verbose-1, "covMatrixSys/"+xSecVariables_[i]);
      // ii) single systematic covariance matrices
      // loop relevant symmetrized systematic variations
      for(unsigned int sys=0; sys<(unsigned int)symmUncLabel_.size(); ++sys){
	//saveToRootFile(outputFile, sysCov_[xSecVariables_[i]][sys], true, verbose, "covarianceMatrixSys");	
      } // end for loop relevant symmetrized systematic variations
    } // end for loop variables   
  } // end if save  
}
