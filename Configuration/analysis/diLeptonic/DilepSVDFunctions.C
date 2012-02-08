# include "TopAnalysis/Configuration/analysis/diLeptonic/DilepSVDFunctions.h"

////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////    Function Definitions  ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


DilepSVDFunctions::DilepSVDFunctions()
{
	unfoldingPlotsToPs = true;
    unfoldingPlotsToRoot = true;
    outpath = "";
}

	
// SVD Helper Function
// Return a k-Value for the particle/quantity/channel combination
int DilepSVDFunctions::SVD_GetKValue(TString channel, TString particle, TString quantity, TString special)
{
 
	// Concatenate Strings
	TString concatenation = DilepSVDFunctions::SVD_CPQS(channel, particle, quantity, special); 
	
	// Standard Value for K 
	int kValue = 0;
	
	
	// Leptons Eta
	if ( concatenation.CompareTo("mumu_Leptons_Eta") == 0 ) kValue = 8;
	if ( concatenation.CompareTo("emu_Leptons_Eta") == 0 ) kValue = 8;
	if ( concatenation.CompareTo("ee_Leptons_Eta") == 0 ) kValue = 8;
	if ( concatenation.CompareTo("combined_Leptons_Eta") == 0 ) kValue = 8;
	if ( concatenation.CompareTo("mumu_Leptons_Eta_MoreBins") == 0 ) kValue = 8;
	if ( concatenation.CompareTo("emu_Leptons_Eta_MoreBins") == 0 ) kValue = 8;
	if ( concatenation.CompareTo("ee_Leptons_Eta_MoreBins") == 0 ) kValue = 8;
	if ( concatenation.CompareTo("combined_Leptons_Eta_MoreBins") == 0 ) kValue = 8;
	
	
	// Leptons Pt
	if ( concatenation.CompareTo("mumu_Leptons_Pt") == 0 ) kValue = 6;
	if ( concatenation.CompareTo("emu_Leptons_Pt") == 0 ) kValue = 6;
	if ( concatenation.CompareTo("ee_Leptons_Pt") == 0 ) kValue = 6;
	if ( concatenation.CompareTo("combined_Leptons_Pt") == 0 ) kValue = 6;
	 
	
	// LepPair Eta
	if ( concatenation.CompareTo("mumu_LepPair_Eta") == 0 ) kValue = 8;
	if ( concatenation.CompareTo("emu_LepPair_Eta") == 0 ) kValue = 8;
	if ( concatenation.CompareTo("ee_LepPair_Eta") == 0 ) kValue = 8;
	if ( concatenation.CompareTo("combined_LepPair_Eta") == 0 ) kValue = 8;
	
	
	// LepPair Pt
	if ( concatenation.CompareTo("mumu_LepPair_Pt") == 0 ) kValue = 6;
	if ( concatenation.CompareTo("emu_LepPair_Pt") == 0 ) kValue = 6;
	if ( concatenation.CompareTo("ee_LepPair_Pt") == 0 ) kValue = 6;
	if ( concatenation.CompareTo("combined_LepPair_Pt") == 0 ) kValue = 6;
	
	
	// LepPair Mass
	if ( concatenation.CompareTo("mumu_LepPair_Mass") == 0 ) kValue = 6;
	if ( concatenation.CompareTo("emu_LepPair_Mass") == 0 ) kValue = 6;
	if ( concatenation.CompareTo("ee_LepPair_Mass") == 0 ) kValue = 6;
	if ( concatenation.CompareTo("combined_LepPair_Mass") == 0 ) kValue = 6;
	 
	
	// Jets Eta
	if ( concatenation.CompareTo("mumu_Jets_Eta") == 0 ) kValue = 6;
	if ( concatenation.CompareTo("emu_Jets_Eta") == 0 ) kValue = 6;
	if ( concatenation.CompareTo("ee_Jets_Eta") == 0 ) kValue = 6;
	if ( concatenation.CompareTo("combined_Jets_Eta") == 0 ) kValue = 6;
	
	
	// Jets Pt
	if ( concatenation.CompareTo("mumu_Jets_Pt") == 0 ) kValue = 4;
	if ( concatenation.CompareTo("emu_Jets_Pt") == 0 ) kValue = 4;
	if ( concatenation.CompareTo("ee_Jets_Pt") == 0 ) kValue = 4;
	if ( concatenation.CompareTo("combined_Jets_Pt") == 0 ) kValue = 4;
	
	
	// TopQuarks Rapidity
	if ( concatenation.CompareTo("mumu_TopQuarks_Rapidity") == 0 ) kValue = 3;
	if ( concatenation.CompareTo("emu_TopQuarks_Rapidity") == 0 ) kValue = 3;
	if ( concatenation.CompareTo("ee_TopQuarks_Rapidity") == 0 ) kValue = 3;
	if ( concatenation.CompareTo("combined_TopQuarks_Rapidity") == 0 ) kValue = 3;
	if ( concatenation.CompareTo("mumu_TopQuarks_Rapidity_MoreBins") == 0 ) kValue = 5;
	if ( concatenation.CompareTo("emu_TopQuarks_Rapidity_MoreBins") == 0 ) kValue = 5;
	if ( concatenation.CompareTo("ee_TopQuarks_Rapidity_MoreBins") == 0 ) kValue = 5;
	if ( concatenation.CompareTo("combined_TopQuarks_Rapidity_MoreBins") == 0 ) kValue = 5;
	
	
	// TopQuarks Pt
	if ( concatenation.CompareTo("mumu_TopQuarks_Pt") == 0 ) kValue = 3;
	if ( concatenation.CompareTo("emu_TopQuarks_Pt") == 0 ) kValue = 3;
	if ( concatenation.CompareTo("ee_TopQuarks_Pt") == 0 ) kValue = 3;
	if ( concatenation.CompareTo("combined_TopQuarks_Pt") == 0 ) kValue = 3;
	
	
	// TtBar Rapidity
	if ( concatenation.CompareTo("mumu_TtBar_Rapidity") == 0 ) kValue = 3;
	if ( concatenation.CompareTo("emu_TtBar_Rapidity") == 0 ) kValue = 3;
	if ( concatenation.CompareTo("ee_TtBar_Rapidity") == 0 ) kValue = 3;
	if ( concatenation.CompareTo("combined_TtBar_Rapidity") == 0 ) kValue = 3;
	if ( concatenation.CompareTo("mumu_TtBar_Rapidity_MoreBins") == 0 ) kValue = 5;
	if ( concatenation.CompareTo("emu_TtBar_Rapidity_MoreBins") == 0 ) kValue = 5;
	if ( concatenation.CompareTo("ee_TtBar_Rapidity_MoreBins") == 0 ) kValue = 5;
	if ( concatenation.CompareTo("combined_TtBar_Rapidity_MoreBins") == 0 ) kValue = 5;
	
	
	// TtBar Pt
	if ( concatenation.CompareTo("mumu_TtBar_Pt") == 0 ) kValue = 4;
	if ( concatenation.CompareTo("emu_TtBar_Pt") == 0 ) kValue = 4;
	if ( concatenation.CompareTo("ee_TtBar_Pt") == 0 ) kValue = 4;
	if ( concatenation.CompareTo("combined_TtBar_Pt") == 0 ) kValue = 4;
	
	
	// TtBar Mass
	if ( concatenation.CompareTo("mumu_TtBar_Mass") == 0 ) kValue = 4;
	if ( concatenation.CompareTo("emu_TtBar_Mass") == 0 ) kValue = 4;
	if ( concatenation.CompareTo("ee_TtBar_Mass") == 0 ) kValue = 4;
	if ( concatenation.CompareTo("combined_TtBar_Mass") == 0 ) kValue = 4; 




    // Exit if this fails
    if ( kValue == 0 ) {
        cout << "Error in DilepSVDFunctions::SVD_GetKValue()" << endl;
        cout << "Level of regularization could not be determined." << endl;
        cout << "    particle = "<<particle<<endl;
        cout << "    quantity = "<<quantity<<endl;
        cout << "    channel  = "<<channel<<endl;
        cout << "    special  = "<<special<<endl;
        cout << "Check the reason for this NOW." << endl;
        exit(1);
    }

    return kValue;
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
int DilepSVDFunctions::SVD_DoUnfold(
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
        // Determine the right kValue
        int kValue = -1 ;
        kValue = SVD_GetKValue(channel, particle, quantity, special);
        

        // FileNames for output 
        TString rootFile = "";
        if ( unfoldingPlotsToRoot == true ) rootFile.Append(SVD_GetOutputFileNameRoot(channel, particle, quantity, special));
        TString psFile = "";
        if ( unfoldingPlotsToPs == true ) psFile.Append(SVD_GetOutputFileNamePs(channel, particle, quantity, special));
         

        // TexStrings for Formatting
        TString particleTex = "";
        TString quantityTex = "";
        TString channelTex = "";
        TString specialTex = "";
        SVD_Tex(channel, particle, quantity, special, channelTex, particleTex, quantityTex, specialTex);
        
	   
	    // Do the Unfolding 
	    return TopSVDFunctions::SVD_Unfold(dataInputHist, bgrInputHist, genInputHist, recInputHist, respInputHist, 
             thebins, numbins, kValue, 
             unfolded, 
             channel, particle, quantity, special,
             channelTex, particleTex, quantityTex, specialTex,
             rootFile, psFile);
	
}
