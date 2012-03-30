# include "DilepSVDFunctions.h"

////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////    Function Definitions  ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


DilepSVDFunctions::DilepSVDFunctions()
{
    outpath = "";
}

    
// SVD Helper Function
// Return a k-Value for the particle/quantity/channel combination
double DilepSVDFunctions::SVD_GetRegPar(TString channel, TString particle, TString quantity, TString special, bool useTau)
{
 
    // Concatenate Strings
    // NOTE: We use the same regPar for ALL Systematic samples!
    //       Therefore, we leave the 'syst'-Parameter empty
    TString concatenation = DilepSVDFunctions::SVD_CPQSS(channel, particle, quantity, special, ""); 
    
    // Variable for the regPar
    double regPar = -1.;
    
    // Regularize Via k
    if ( useTau == 0) { 
        if ( concatenation.CompareTo("mumu_Leptons_Eta") == 0 ) regPar = 10.;//8.;
        if ( concatenation.CompareTo("emu_Leptons_Eta") == 0 ) regPar = 10.;//8.;
        if ( concatenation.CompareTo("ee_Leptons_Eta") == 0 ) regPar = 10.;//8.;
        if ( concatenation.CompareTo("combined_Leptons_Eta") == 0 ) regPar = 10.;//8.;
        if ( concatenation.CompareTo("mumu_Leptons_Eta_MoreBins") == 0 ) regPar = 8.;
        if ( concatenation.CompareTo("emu_Leptons_Eta_MoreBins") == 0 ) regPar = 8.;
        if ( concatenation.CompareTo("ee_Leptons_Eta_MoreBins") == 0 ) regPar = 8.;
        if ( concatenation.CompareTo("combined_Leptons_Eta_MoreBins") == 0 ) regPar = 8.; 
        if ( concatenation.CompareTo("mumu_Leptons_Pt") == 0 ) regPar = 6.;
        if ( concatenation.CompareTo("emu_Leptons_Pt") == 0 ) regPar = 6.;
        if ( concatenation.CompareTo("ee_Leptons_Pt") == 0 ) regPar = 6.;
        if ( concatenation.CompareTo("combined_Leptons_Pt") == 0 ) regPar = 6.; 
        if ( concatenation.CompareTo("mumu_LepPair_Eta") == 0 ) regPar = 8.;
        if ( concatenation.CompareTo("emu_LepPair_Eta") == 0 ) regPar = 8.;
        if ( concatenation.CompareTo("ee_LepPair_Eta") == 0 ) regPar = 8.;
        if ( concatenation.CompareTo("combined_LepPair_Eta") == 0 ) regPar = 8.; 
        if ( concatenation.CompareTo("mumu_LepPair_Pt") == 0 ) regPar = 7.; //6.;
        if ( concatenation.CompareTo("emu_LepPair_Pt") == 0 ) regPar = 7.; //6.;
        if ( concatenation.CompareTo("ee_LepPair_Pt") == 0 ) regPar = 7.; //6.;
        if ( concatenation.CompareTo("combined_LepPair_Pt") == 0 ) regPar = 7.; //6.; 
        if ( concatenation.CompareTo("mumu_LepPair_Mass") == 0 ) regPar = 6.;
        if ( concatenation.CompareTo("emu_LepPair_Mass") == 0 ) regPar = 6.;
        if ( concatenation.CompareTo("ee_LepPair_Mass") == 0 ) regPar = 6.;
        if ( concatenation.CompareTo("combined_LepPair_Mass") == 0 ) regPar = 6.; 
        if ( concatenation.CompareTo("mumu_Jets_Eta") == 0 ) regPar = 7.; //6.;
        if ( concatenation.CompareTo("emu_Jets_Eta") == 0 ) regPar = 7.; //6.;
        if ( concatenation.CompareTo("ee_Jets_Eta") == 0 ) regPar = 7.; //6.;
        if ( concatenation.CompareTo("combined_Jets_Eta") == 0 ) regPar = 7.; //6.; 
        if ( concatenation.CompareTo("mumu_Jets_Pt") == 0 ) regPar = 7.; //4.;
        if ( concatenation.CompareTo("emu_Jets_Pt") == 0 ) regPar = 7.; //4.;
        if ( concatenation.CompareTo("ee_Jets_Pt") == 0 ) regPar = 7.; //4.;
        if ( concatenation.CompareTo("combined_Jets_Pt") == 0 ) regPar = 7.; //4.; 
        if ( concatenation.CompareTo("mumu_TopQuarks_Rapidity") == 0 ) regPar = 4.;//3.;
        if ( concatenation.CompareTo("emu_TopQuarks_Rapidity") == 0 ) regPar = 4.;//3.;
        if ( concatenation.CompareTo("ee_TopQuarks_Rapidity") == 0 ) regPar = 4.;//3.;
        if ( concatenation.CompareTo("combined_TopQuarks_Rapidity") == 0 ) regPar = 4.;//3.;
        if ( concatenation.CompareTo("mumu_TopQuarks_Rapidity_MoreBins") == 0 ) regPar = 5.;
        if ( concatenation.CompareTo("emu_TopQuarks_Rapidity_MoreBins") == 0 ) regPar = 5.;
        if ( concatenation.CompareTo("ee_TopQuarks_Rapidity_MoreBins") == 0 ) regPar = 5.;
        if ( concatenation.CompareTo("combined_TopQuarks_Rapidity_MoreBins") == 0 ) regPar = 5.; 
        if ( concatenation.CompareTo("mumu_TopQuarks_Pt") == 0 ) regPar = 4.;//3.;
        if ( concatenation.CompareTo("emu_TopQuarks_Pt") == 0 ) regPar = 4.;//3.;
        if ( concatenation.CompareTo("ee_TopQuarks_Pt") == 0 ) regPar = 4.;//3.;
        if ( concatenation.CompareTo("combined_TopQuarks_Pt") == 0 ) regPar = 4.;//3.; 
        if ( concatenation.CompareTo("mumu_TtBar_Rapidity") == 0 ) regPar = 4.;//3.;
        if ( concatenation.CompareTo("emu_TtBar_Rapidity") == 0 ) regPar = 4.;//3.;
        if ( concatenation.CompareTo("ee_TtBar_Rapidity") == 0 ) regPar = 4.;//3.;
        if ( concatenation.CompareTo("combined_TtBar_Rapidity") == 0 ) regPar = 4.;//3.;
        if ( concatenation.CompareTo("mumu_TtBar_Rapidity_MoreBins") == 0 ) regPar = 5.;
        if ( concatenation.CompareTo("emu_TtBar_Rapidity_MoreBins") == 0 ) regPar = 5.;
        if ( concatenation.CompareTo("ee_TtBar_Rapidity_MoreBins") == 0 ) regPar = 5.;
        if ( concatenation.CompareTo("combined_TtBar_Rapidity_MoreBins") == 0 ) regPar = 5.; 
        if ( concatenation.CompareTo("mumu_TtBar_Pt") == 0 ) regPar = 4.;
        if ( concatenation.CompareTo("emu_TtBar_Pt") == 0 ) regPar = 4.;
        if ( concatenation.CompareTo("ee_TtBar_Pt") == 0 ) regPar = 4.;
        if ( concatenation.CompareTo("combined_TtBar_Pt") == 0 ) regPar = 4.; 
        if ( concatenation.CompareTo("mumu_TtBar_Mass") == 0 ) regPar = 4.;
        if ( concatenation.CompareTo("emu_TtBar_Mass") == 0 ) regPar = 4.;
        if ( concatenation.CompareTo("ee_TtBar_Mass") == 0 ) regPar = 4.;
        if ( concatenation.CompareTo("combined_TtBar_Mass") == 0 ) regPar = 4.;
    } else {
    	if ( concatenation.CompareTo("emu_Leptons_Eta") == 0 )                          regPar = 12.46585;
        if ( concatenation.CompareTo("mumu_Leptons_Eta") == 0 )                         regPar = 7.00469;
        if ( concatenation.CompareTo("ee_Leptons_Eta") == 0 )                           regPar = 6.38505;
        if ( concatenation.CompareTo("combined_Leptons_Eta") == 0 )                     regPar = 15.64009;
        if ( concatenation.CompareTo("emu_Leptons_Pt") == 0 )                           regPar = 10.46604;
        if ( concatenation.CompareTo("mumu_Leptons_Pt") == 0 )                          regPar = 5.73979;
        if ( concatenation.CompareTo("ee_Leptons_Pt") == 0 )                            regPar = 5.26385;
        if ( concatenation.CompareTo("combined_Leptons_Pt") == 0 )                      regPar = 12.95660;
        if ( concatenation.CompareTo("emu_LepPair_Pt") == 0 )                           regPar = 14.21435;
        if ( concatenation.CompareTo("mumu_LepPair_Pt") == 0 )                          regPar = 7.72164;
        if ( concatenation.CompareTo("ee_LepPair_Pt") == 0 )                            regPar = 7.34612;
        if ( concatenation.CompareTo("combined_LepPair_Pt") == 0 )                      regPar = 17.68402;
        if ( concatenation.CompareTo("emu_LepPair_Mass") == 0 )                         regPar = 19.03124;
        if ( concatenation.CompareTo("mumu_LepPair_Mass") == 0 )                        regPar = 111.13875;
        if ( concatenation.CompareTo("ee_LepPair_Mass") == 0 )                          regPar = 219.42386;
        if ( concatenation.CompareTo("combined_LepPair_Mass") == 0 )                    regPar = 23.50532;
        if ( concatenation.CompareTo("emu_Jets_Eta") == 0 )                             regPar = 23.07640;
        if ( concatenation.CompareTo("mumu_Jets_Eta") == 0 )                            regPar = 12.61893;
        if ( concatenation.CompareTo("ee_Jets_Eta") == 0 )                              regPar = 12.13045;
        if ( concatenation.CompareTo("combined_Jets_Eta") == 0 )                        regPar = 28.89900;
        if ( concatenation.CompareTo("emu_Jets_Pt") == 0 )                              regPar = 19.69450;
        if ( concatenation.CompareTo("mumu_Jets_Pt") == 0 )                             regPar = 10.53993;
        if ( concatenation.CompareTo("ee_Jets_Pt") == 0 )                               regPar = 10.10353;
        if ( concatenation.CompareTo("combined_Jets_Pt") == 0 )                         regPar = 24.39646;
        if ( concatenation.CompareTo("emu_TopQuarks_Rapidity") == 0 )                   regPar = 22.01909;
        if ( concatenation.CompareTo("mumu_TopQuarks_Rapidity") == 0 )                  regPar = 12.18932;
        if ( concatenation.CompareTo("ee_TopQuarks_Rapidity") == 0 )                    regPar = 11.80886;
        if ( concatenation.CompareTo("combined_TopQuarks_Rapidity") == 0 )              regPar = 27.73292;
        if ( concatenation.CompareTo("emu_TopQuarks_Rapidity_MoreBins") == 0 )          regPar = 28.86155;
        if ( concatenation.CompareTo("mumu_TopQuarks_Rapidity_MoreBins") == 0 )         regPar = 15.99503;
        if ( concatenation.CompareTo("ee_TopQuarks_Rapidity_MoreBins") == 0 )           regPar = 15.23704;
        if ( concatenation.CompareTo("combined_TopQuarks_Rapidity_MoreBins") == 0 )     regPar = 36.22604;
        if ( concatenation.CompareTo("emu_TopQuarks_Pt") == 0 )                         regPar = 30.32823;
        if ( concatenation.CompareTo("mumu_TopQuarks_Pt") == 0 )                        regPar = 18.05278;
        if ( concatenation.CompareTo("ee_TopQuarks_Pt") == 0 )                          regPar = 16.97786;
        if ( concatenation.CompareTo("combined_TopQuarks_Pt") == 0 )                    regPar = 39.06316;
        if ( concatenation.CompareTo("emu_TtBar_Rapidity") == 0 )                       regPar = 13.92207;
        if ( concatenation.CompareTo("mumu_TtBar_Rapidity") == 0 )                      regPar = 6.61194;
        if ( concatenation.CompareTo("ee_TtBar_Rapidity") == 0 )                        regPar = 6.81676;
        if ( concatenation.CompareTo("combined_TtBar_Rapidity") == 0 )                  regPar = 16.74603;
        if ( concatenation.CompareTo("emu_TtBar_Rapidity_MoreBins") == 0 )              regPar = 21.82622;
        if ( concatenation.CompareTo("mumu_TtBar_Rapidity_MoreBins") == 0 )             regPar = 11.46453;
        if ( concatenation.CompareTo("ee_TtBar_Rapidity_MoreBins") == 0 )               regPar = 11.07554;
        if ( concatenation.CompareTo("combined_TtBar_Rapidity_MoreBins") == 0 )         regPar = 26.91094;
        if ( concatenation.CompareTo("emu_TtBar_Pt") == 0 )                             regPar = 23.54894;
        if ( concatenation.CompareTo("mumu_TtBar_Pt") == 0 )                            regPar = 12.68250;
        if ( concatenation.CompareTo("ee_TtBar_Pt") == 0 )                              regPar = 12.95903;
        if ( concatenation.CompareTo("combined_TtBar_Pt") == 0 )                        regPar = 29.66756;
        if ( concatenation.CompareTo("emu_TtBar_Mass") == 0 )                           regPar = 9.94907;
        if ( concatenation.CompareTo("mumu_TtBar_Mass") == 0 )                          regPar = 6.90770;
        if ( concatenation.CompareTo("ee_TtBar_Mass") == 0 )                            regPar = 6.43150;
        if ( concatenation.CompareTo("combined_TtBar_Mass") == 0 )                      regPar = 13.71350;    
    }
	
	if( regPar > 0. ) return regPar;
    
    // Exit if this fails 
    cout << "Error in DilepSVDFunctions::SVD_GetRegPar()" << endl;
    cout << "Level of regularization could not be determined." << endl;
    cout << "    particle = "<<particle<<endl;
    cout << "    quantity = "<<quantity<<endl;
    cout << "    channel  = "<<channel<<endl;
    cout << "    special  = "<<special<<endl;
    cout << "Check the reason for this NOW." << endl;
    exit(1);
    
    return regPar;
    
}


// DAVID
// SVD Unfolding Helper Function
// Create Tex Snippets for the histograms
void DilepSVDFunctions::SVD_Tex(TString channel, TString particle, TString quantity, TString special, TString& channelTex, TString& particleTex, TString& quantityTex, TString& specialTex)
{

    channelTex = "";
    if ( strcmp(channel, "mumu") == 0 ) {
        channelTex.Append("#mu^{+}#mu^{-}");
    } else if ( strcmp(channel, "emu") == 0 ) {
        channelTex.Append("e^{+}#mu^{-}");
    } else if ( strcmp(channel, "ee") == 0 ) {
        channelTex.Append("e^{+}e^{-}");
    } else if ( strcmp(channel, "combined") == 0 ) {
        channelTex.Append("cb.");
    } else {
        channelTex.Append(channel);
    }
    
    particleTex = "";
    if ( strcmp(particle, "Leptons") == 0 ) {
        particleTex.Append("l^{+} / l^{-}");
    } else if ( strcmp(particle, "LepPair") == 0 ) {
        particleTex.Append("(l^{+}l^{-})");
    } else if ( strcmp(particle, "Jets") == 0 ){
        particleTex.Append("Jets");
    } else if ( strcmp(particle, "TopQuarks") == 0 ) {
        particleTex.Append("t / #bar{t}");
    } else if ( strcmp(particle, "TtBar") == 0 ) {
        particleTex.Append("(t#bar{t})");
    } else {
        particleTex.Append(particle);
    } 
    
    quantityTex = "";
    if ( strcmp(quantity, "Pt") == 0 ) {
        quantityTex.Append("p_{T}");
    } else if ( strcmp(quantity, "Eta") == 0 ) {
        quantityTex.Append("#eta");
    } else if ( strcmp(quantity, "Rapidity") == 0 ) {
        quantityTex.Append("y");
    } else if ( strcmp(quantity, "Mass") == 0 ) {
        quantityTex.Append("M_{t #bar{t}}");
    } else {
        quantityTex.Append(quantity);
    } 
    
    specialTex = "";
    if ( strcmp(special, "MoreBins") == 0 ) {
        specialTex.Append("(MB)"); 
    } else {
        specialTex.Append(particle);
    }

} 

// DAVID
// SVD Unfolding Helper Function
TString DilepSVDFunctions::SVD_GetOutputPath()
{

    TString outputfilename = "";
    outputfilename.Append(outpath);
    outputfilename.Append("SVD");

    return outputfilename;

}

// DAVID
// SVD Unfolding Helper Function
// Get complete Output File Name for Ps
TString DilepSVDFunctions::SVD_GetOutputFileNamePs(TString channel, TString particle, TString quantity, TString syst, TString special)
{

    TString outputfilename = SVD_GetOutputPath();
    outputfilename.Append("/Unfolding_");
    outputfilename.Append(SVD_CPQSS(channel, particle, quantity, special, syst)); 
    outputfilename.Append(".ps");
    return outputfilename;

}


// DAVID
// SVD Unfolding Helper Function
// Get complete Output File Name for Root
TString DilepSVDFunctions::SVD_GetOutputFileNameRoot(TString channel, TString particle, TString quantity, TString syst, TString special)
{
    TString outputfilename = SVD_GetOutputPath();
    outputfilename.Append("/Unfolding_");
    outputfilename.Append(SVD_CPQSS(channel, particle, quantity, special, syst));
    outputfilename.Append(".root");
    return outputfilename;

}
 
 

 
// Unfolding with systematics.
// This takes "3 of each kind": Nominal, Up and Down
// The return value will contain relative shifts !!!
// For more information see function SVD_DoUnfold() 
double DilepSVDFunctions::SVD_DoUnfoldSys(
        TH1D* dataInputHist,                            // DATA.
        TH1D* bgrNom, TH1D* bgrUp, TH1D* bgrDown,      // Background.
        TH1D* genNom, TH1D* genUp, TH1D* genDown,        // Gen. Note: if genUp==NULL then genUp=genNom, etc. 
        TH1D* recNom, TH1D* recUp, TH1D* recDown,      // Rec
        TH2D* respNom, TH2D* respUp, TH2D* respDown,  // Response Matrices
        const double thebins[],                 
        const int numbins,                       
        TH1D*& unfolded,                        
        TString channel,                       
        TString particle,                      
        TString quantity,                      
        TString special,    
        TString syst                           // Specify Name for the Down-Systematic
)
{		   
    // Align Data
    TH1D* arrData = new TH1D[1];
    *(arrData+0) = *dataInputHist; 
     
    
    // Align Background
    TH1D* arrBgr = new TH1D[3];
    *(arrBgr+0) = *bgrNom;
    *(arrBgr+1) = *bgrUp;
    *(arrBgr+2) = *bgrDown;
    
    
    // Align Gen Dists
    TH1D* arrGen = NULL;
    if ( genUp == NULL || genDown == NULL ) { 
        arrGen = new TH1D[1];
        *(arrGen+0) = *genNom;
    } else { 
        arrGen = new TH1D[3];
        *(arrGen+0) = *genNom;
        *(arrGen+1) = *genUp;
        *(arrGen+2) = *genDown;
    }
         
    
    // Align Rec Dists
    TH1D* arrRec = new TH1D[3];
    *(arrRec+0) = *recNom;
    *(arrRec+1) = *recUp;
    *(arrRec+2) = *recDown;
    
    
    // Align Response Matrices
    TH2D* arrResp = new TH2D[3];
    *(arrResp+0) = *respNom;
    *(arrResp+1) = *respUp;
    *(arrResp+2) = *respDown;
    
         
    // Create Pointer for Output 
    TH1D* arrUnfolded = NULL;
    
    
    // Call the unfolding function
    int numSys = 2;
    double bestTau = SVD_DoUnfold(
        arrData,               
        arrBgr,                       
        arrGen,                      
        arrRec,                    
        arrResp,                     
        thebins,                 
        numbins,                       
        arrUnfolded,    // Return value   
        numSys,          
        channel,                     
        particle,                      
        quantity,                      
        special,
        syst);                    
     
     
    // Get the unfolded histograms 
    TH1D* unfNom = arrUnfolded;  
    TH1D* unfUp = arrUnfolded + 1; 
    TH1D* unfDown = arrUnfolded + 2; 
     
     
    // Create the output histogram for this function
    if ( unfolded == NULL ) {
        unfolded =  (TH1D*) unfNom->Clone("unfolded");
    }
     
    
    // Calculate the bin wise differences
    for ( int i = 1 ; i <= numbins+2 ; i++ ) {
        double valunfNom = unfNom->GetBinContent(i);
        double valunfUp = unfUp->GetBinContent(i);
        double valunfDown = unfDown->GetBinContent(i);
        double Sys_Error = 0.;
        if ( valunfNom > 0. ) { 
            double Sys_Error_Up   = TMath::Abs(valunfUp - valunfNom ) / valunfNom ;
            double Sys_Error_Down   = TMath::Abs(valunfDown - valunfNom ) / valunfNom ; 
            Sys_Error  = (Sys_Error_Up+Sys_Error_Down)/2.;
        } 
        unfolded->SetBinContent(i, Sys_Error);
        unfolded->SetBinError(i, 0.);
    }
      
    
    // return best tau value
    return bestTau;
        
}    
 
 
// PERFORM UNFOLDING 
// Note: This function can do both, BBB and SVD Unfolding.
// If kreg > 0:
//       SVD Unfolding is done with 'kreg'
//       and the result of SVD Unfolding is returned in 'unfolded'
// If kreg <= 0:
//       BBB Unfolding is returned in 'unfolded' 
// If you specify filenames, plots will be drawn and saved.
// Return value: Best tau, if found, -1. otherwise
double DilepSVDFunctions::SVD_DoUnfold(
        TH1D* dataInputHist,                     // Data Input (RAW Data including the background)
        TH1D* bgrInputHist,                      // Background (will be substracted from data)
        TH1D* genInputHist,                      // Generated MC
        TH1D* recInputHist,                      // Reconstructed MC
        TH2D* respInputHist,                     // Response Matrix 
        const double thebins[],                  // Binning for the unfolding
        const int numbins,                       // Number of bins for unfolding (not counting OF bins !!!) 
        TH1D*& unfolded,                         // Returned: Unfolded Distribution.
        const int numSys,                        // Number of used systematics (standard = 0 )
        TString channel,                         // Specify Name for the Channel ("mumu", "emu", "ee" ...)
        TString particle,                        // Specify Name for the Physics Object ("Top", "Jets", "Leptons")
        TString quantity,                        // Specify Name for the Quantity ("Eta", "Pt", or "Mass");
        TString special,                         // Special Postfix to be used for names of files and plots
        TString syst                             // Specify Name for the Up-Systematic
)   
{ 

    
    
    // Determine the Steering
    int regMode = 2;
    int useTau = 0;
    int doScan = 1;
    int doPsFile = 1;
    int doKScanPlots = 1;
    int doTauScanPlots = 1;
    int doRootFile = 0;
    int doTextFile = 1;
    int verbosity = 1;
    
    // Calculate Steering Parameter
    int steering = 0;
    steering +=       1*regMode;
    steering +=      10*useTau;
    steering +=     100*doScan;
    steering +=    1000*doPsFile;
    steering +=    1000*doKScanPlots;
    steering +=    1000*doTauScanPlots;
    steering +=   10000*doRootFile;
    steering +=  100000*doTextFile;
    steering += 1000000*verbosity;
        

    // Determine the right kValue
    double regPar = -1.;
    regPar = SVD_GetRegPar(channel, particle, quantity, special, useTau);    
    
    // FileNames for output 
    TString rootFile = "";
    rootFile.Append(SVD_GetOutputFileNameRoot(channel, particle, quantity, syst, special));
    TString psFile = "";
    psFile.Append(SVD_GetOutputFileNamePs(channel, particle, quantity, syst, special));
    TString scanResultFile =  SVD_GetOutputPath();
    scanResultFile.Append("/optimalTau.txt");

  
    // TexStrings for Formatting
    TString channelTex = "";
    TString particleTex = "";
    TString quantityTex = ""; 
    TString specialTex = "";
    SVD_Tex(channel, particle, quantity, special, channelTex, particleTex, quantityTex, specialTex);


    // Tex for Systematics
    TString systTex = syst; 
    

    // Do the Unfolding 
    double optimalTauX = TopSVDFunctions::SVD_Unfold(dataInputHist, bgrInputHist, NULL, genInputHist, recInputHist, respInputHist,
        unfolded, 
        thebins, numbins, regPar, steering, numSys,
        channel, particle, quantity, special, syst,
        channelTex, particleTex, quantityTex, specialTex, systTex,
        rootFile, psFile, scanResultFile);
  
    // Save best tau to file if you do a scan
    if ( doScan == true  ) {
          
        // Code for re-usage
        TString tauTextFileCode = SVD_GetOutputPath();
        tauTextFileCode.Append("/optimalTauCode.txt");
        gSystem->RedirectOutput(tauTextFileCode, "a");
        TString lineStrCode = "if ( concatenation.CompareTo(\"";
        lineStrCode.Append(SVD_CPQSS(channel, particle, quantity, special, syst));
        lineStrCode.Append("\") == 0 ) ");
        for ( int i = lineStrCode.Length() ; i < 80 ; i++ ) lineStrCode.Append(" ");  
        lineStrCode.Append("regPar = ");
        lineStrCode.Append(TString::Format("%.5f", optimalTauX));
        lineStrCode.Append(";");
        cout << lineStrCode << endl;
        gSystem->RedirectOutput(NULL, "a");
         
        // Plain list with Tau Parameters
        TString tauTextFileList = SVD_GetOutputPath();
        tauTextFileList.Append("/optimalTauDocu.txt");
        gSystem->RedirectOutput(tauTextFileList, "a");
        TString lineStrList =  SVD_CPQSS(channel, particle, quantity, special, syst);
        lineStrList.ReplaceAll("_",""); // Remove underscores
        lineStrList.Append(" ");
        for ( int i = lineStrList.Length() ; i < 60 ; i++ ) lineStrList.Append(" ");   
        lineStrList.Append(TString::Format("%.5f", optimalTauX)); 
        cout << lineStrList << endl;
        gSystem->RedirectOutput(NULL, "a");
    } 
    
    
    return optimalTauX;
    
}


 
    
