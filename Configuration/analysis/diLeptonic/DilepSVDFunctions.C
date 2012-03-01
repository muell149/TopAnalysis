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
		if ( concatenation.CompareTo("emu_Leptons_Eta") == 0 )                          regPar = 11.60651;
		if ( concatenation.CompareTo("mumu_Leptons_Eta") == 0 )                         regPar = 6.65463;
		if ( concatenation.CompareTo("ee_Leptons_Eta") == 0 )                           regPar = 5.72994;
		if ( concatenation.CompareTo("combined_Leptons_Eta") == 0 )                     regPar = 14.25360;
		if ( concatenation.CompareTo("emu_Leptons_Pt") == 0 )                           regPar = 10.39686;
		if ( concatenation.CompareTo("mumu_Leptons_Pt") == 0 )                          regPar = 5.18436;
		if ( concatenation.CompareTo("ee_Leptons_Pt") == 0 )                            regPar = 4.82904;
		if ( concatenation.CompareTo("combined_Leptons_Pt") == 0 )                      regPar = 12.47045;
		if ( concatenation.CompareTo("emu_LepPair_Pt") == 0 )                           regPar = 14.17671;
		if ( concatenation.CompareTo("mumu_LepPair_Pt") == 0 )                          regPar = 6.87167;
		if ( concatenation.CompareTo("ee_LepPair_Pt") == 0 )                            regPar = 6.92577;
		if ( concatenation.CompareTo("combined_LepPair_Pt") == 0 )                      regPar = 15.95395;
		if ( concatenation.CompareTo("emu_LepPair_Mass") == 0 )                         regPar = 17.76963;
		if ( concatenation.CompareTo("mumu_LepPair_Mass") == 0 )                        regPar = 0.34067;
		if ( concatenation.CompareTo("ee_LepPair_Mass") == 0 )                          regPar = 0.43183;
		if ( concatenation.CompareTo("combined_LepPair_Mass") == 0 )                    regPar = 22.57879;
		if ( concatenation.CompareTo("emu_Jets_Eta") == 0 )                             regPar = 23.17710;
		if ( concatenation.CompareTo("mumu_Jets_Eta") == 0 )                            regPar = 12.41859;
		if ( concatenation.CompareTo("ee_Jets_Eta") == 0 )                              regPar = 11.08602;
		if ( concatenation.CompareTo("combined_Jets_Eta") == 0 )                        regPar = 26.40473;
		if ( concatenation.CompareTo("emu_Jets_Pt") == 0 )                              regPar = 18.19060;
		if ( concatenation.CompareTo("mumu_Jets_Pt") == 0 )                             regPar = 9.82304;
		if ( concatenation.CompareTo("ee_Jets_Pt") == 0 )                               regPar = 9.45277;
		if ( concatenation.CompareTo("combined_Jets_Pt") == 0 )                         regPar = 23.22770;
		if ( concatenation.CompareTo("emu_TopQuarks_Rapidity") == 0 )                   regPar = 21.31468;
		if ( concatenation.CompareTo("mumu_TopQuarks_Rapidity") == 0 )                  regPar = 11.63043;
		if ( concatenation.CompareTo("ee_TopQuarks_Rapidity") == 0 )                    regPar = 11.58946;
		if ( concatenation.CompareTo("combined_TopQuarks_Rapidity") == 0 )              regPar = 26.76945;
		if ( concatenation.CompareTo("emu_TopQuarks_Rapidity_MoreBins") == 0 )          regPar = 27.27020;
		if ( concatenation.CompareTo("mumu_TopQuarks_Rapidity_MoreBins") == 0 )         regPar = 14.98169;
		if ( concatenation.CompareTo("ee_TopQuarks_Rapidity_MoreBins") == 0 )           regPar = 14.55621;
		if ( concatenation.CompareTo("combined_TopQuarks_Rapidity_MoreBins") == 0 )     regPar = 34.25092;
		if ( concatenation.CompareTo("emu_TopQuarks_Pt") == 0 )                         regPar = 30.24627;
		if ( concatenation.CompareTo("mumu_TopQuarks_Pt") == 0 )                        regPar = 17.72126;
		if ( concatenation.CompareTo("ee_TopQuarks_Pt") == 0 )                          regPar = 16.59263;
		if ( concatenation.CompareTo("combined_TopQuarks_Pt") == 0 )                    regPar = 38.74808;
		if ( concatenation.CompareTo("emu_TtBar_Rapidity") == 0 )                       regPar = 13.09755;
		if ( concatenation.CompareTo("mumu_TtBar_Rapidity") == 0 )                      regPar = 5.72065;
		if ( concatenation.CompareTo("ee_TtBar_Rapidity") == 0 )                        regPar = 6.20367;
		if ( concatenation.CompareTo("combined_TtBar_Rapidity") == 0 )                  regPar = 15.25706;
		if ( concatenation.CompareTo("emu_TtBar_Rapidity_MoreBins") == 0 )              regPar = 19.52446;
		if ( concatenation.CompareTo("mumu_TtBar_Rapidity_MoreBins") == 0 )             regPar = 10.47879;
		if ( concatenation.CompareTo("ee_TtBar_Rapidity_MoreBins") == 0 )               regPar = 9.91619;
		if ( concatenation.CompareTo("combined_TtBar_Rapidity_MoreBins") == 0 )         regPar = 23.85867;
		if ( concatenation.CompareTo("emu_TtBar_Pt") == 0 )                             regPar = 23.84918;
		if ( concatenation.CompareTo("mumu_TtBar_Pt") == 0 )                            regPar = 12.55188;
		if ( concatenation.CompareTo("ee_TtBar_Pt") == 0 )                              regPar = 11.94456;
		if ( concatenation.CompareTo("combined_TtBar_Pt") == 0 )                        regPar = 27.23497;
		if ( concatenation.CompareTo("emu_TtBar_Mass") == 0 )                           regPar = 9.18666;
		if ( concatenation.CompareTo("mumu_TtBar_Mass") == 0 )                          regPar = 6.42640;
		if ( concatenation.CompareTo("ee_TtBar_Mass") == 0 )                            regPar = 6.16216; 
		if ( concatenation.CompareTo("combined_TtBar_Mass") == 0 )                      regPar = 13.28851;
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
	    double optimalTauX = TopSVDFunctions::SVD_Unfold(dataInputHist, bgrInputHist, genInputHist, recInputHist, respInputHist, 
             thebins, numbins, regPar, regMode,
             unfolded, 
             channel, particle, quantity, special,
             channelTex, particleTex, quantityTex, specialTex,
             rootFile, psFile);
  
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
  			
  			// Plain list
  			TString tauTextFileList = SVD_GetOutputPath();
  			tauTextFileList.Append("/optimalTau.txt");
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


 
	
