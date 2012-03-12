# include "DilepSVDFunctions.h"

////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////    Function Definitions  ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


DilepSVDFunctions::DilepSVDFunctions()
{
	unfoldingPlotsToPs = true;
    unfoldingPlotsToRoot = true; 
    regMode = 1;
    outpath = "";
}

	
// SVD Helper Function
// Return a k-Value for the particle/quantity/channel combination
double DilepSVDFunctions::SVD_GetRegPar(TString channel, TString particle, TString quantity, TString special)
{
 
	// Concatenate Strings
	TString concatenation = DilepSVDFunctions::SVD_CPQS(channel, particle, quantity, special); 
	
	// Standard Value for K 
	double regPar = -1.;
	
	
	// Regularize Via k
	if ( regMode == 1 || regMode == 3 ) { 
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
	}
    
    
	// Regularize Via tau
    if ( regMode == 2 || regMode == 4 ) {
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


    // Exit if this fails
    if ( regPar == -1. ) {
        cout << "Error in DilepSVDFunctions::SVD_GetRegPar()" << endl;
        cout << "Level of regularization could not be determined." << endl;
        cout << "    particle = "<<particle<<endl;
        cout << "    quantity = "<<quantity<<endl;
        cout << "    channel  = "<<channel<<endl;
        cout << "    special  = "<<special<<endl;
        cout << "Check the reason for this NOW." << endl;
        exit(1);
    }

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
TString DilepSVDFunctions::SVD_GetOutputFileNamePs(TString channel, TString particle, TString quantity, TString special)
{

    TString outputfilename = SVD_GetOutputPath();
    outputfilename.Append("/Unfolding_");
    outputfilename.Append(SVD_CPQS(channel, particle, quantity, special));
    outputfilename.Append(".ps");
    return outputfilename;

}


// DAVID
// SVD Unfolding Helper Function
// Get complete Output File Name for Root
TString DilepSVDFunctions::SVD_GetOutputFileNameRoot(TString channel, TString particle, TString quantity, TString special)
{
    TString outputfilename = SVD_GetOutputPath();
    outputfilename.Append("/Unfolding_");
    outputfilename.Append(SVD_CPQS(channel, particle, quantity, special));
    outputfilename.Append(".root");
    return outputfilename;

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
        TH1* dataInputHist,                     // Data Input (RAW Data including the background)
        TH1* bgrInputHist,                      // Background (will be substracted from data)
        TH1* genInputHist,                      // Generated MC
        TH1* recInputHist,                      // Reconstructed MC
        TH1* respInputHist,                     // Response Matrix 
        const double thebins[],                 // Binning for the unfolding
        const int numbins,                      // Number of bins for unfolding (not counting OF bins !!!) 
        TH1D*& unfolded,                        // Returned: Unfolded Distribution.
        TString channel,                        // Specify Name for the Channel ("mumu", "emu", "ee" ...)
        TString particle,                       // Specify Name for the Physics Object ("Top", "Jets", "Leptons")
        TString quantity,                       // Specify Name for the Quantity ("Eta", "Pt", or "Mass");
        TString special                         // Special Postfix to be used for names of files and plots
)   
{ 
	
		// Screen Output
		cout << endl;
		cout << "*******************************************************************************" << endl;
		cout << "Starting SVD Unfolding of ... " << endl;
		cout << "    Channel            " << channel << endl;
		cout << "    Particle           " << particle << endl;
		cout << "    Quantity:          " << quantity << endl;
		cout << "    Special condition: " << special << endl;
		

        // Determine the right kValue
        double regPar = -1.;
        regPar = SVD_GetRegPar(channel, particle, quantity, special);
		
		
        // FileNames for output 
        TString rootFile = "";
        if ( unfoldingPlotsToRoot == true ) rootFile.Append(SVD_GetOutputFileNameRoot(channel, particle, quantity, special));
        TString psFile = "";
        if ( unfoldingPlotsToPs == true ) psFile.Append(SVD_GetOutputFileNamePs(channel, particle, quantity, special));
        TString scanResultFile =  SVD_GetOutputPath();
        scanResultFile.Append("/optimalTau.txt");

		// Screen Output
		cout << "    RegPar:            " << regPar << endl;
		cout << "    RegMode:           " << regMode << endl;
		cout << "    Root File:         " << rootFile << endl;
		cout << "    Ps File:           " << psFile << endl;
		cout << "*******************************************************************************" << endl;
	    cout << endl;

        // TexStrings for Formatting
        TString channelTex = "";
        TString particleTex = "";
        TString quantityTex = ""; 
        TString specialTex = "";
        SVD_Tex(channel, particle, quantity, special, channelTex, particleTex, quantityTex, specialTex);


	    // Do the Unfolding 
	    double optimalTauX = TopSVDFunctions::SVD_Unfold(dataInputHist, bgrInputHist, NULL, genInputHist, recInputHist, respInputHist, 
             thebins, numbins, regPar, regMode,
             unfolded, 
             channel, particle, quantity, special,
             channelTex, particleTex, quantityTex, specialTex,
             rootFile, psFile, scanResultFile,
             1, true);
  
  		// Save best tau to file if you do a scan
  		if ( regMode == 3 || regMode == 4 ) {
  			
  			// Code for re-usage
  			TString tauTextFileCode = SVD_GetOutputPath();
  			tauTextFileCode.Append("/optimalTauCode.txt");
  			gSystem->RedirectOutput(tauTextFileCode, "a");
  			TString lineStrCode = "if ( concatenation.CompareTo(\"";
  			lineStrCode.Append(SVD_CPQS(channel, particle, quantity, special));
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
  			TString lineStrList =  SVD_CPQS(channel, particle, quantity, special);
  			lineStrList.ReplaceAll("_",""); // Remove underscores
  			lineStrList.Append(" ");
  			for ( int i = lineStrList.Length() ; i < 60 ; i++ ) lineStrList.Append(" ");   
  			lineStrList.Append(TString::Format("%.5f", optimalTauX)); 
  			cout << lineStrList << endl;
  			gSystem->RedirectOutput(NULL, "a");
  		} 
		
		
		return optimalTauX;
	
}


 
	
