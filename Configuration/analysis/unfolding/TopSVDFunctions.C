# include "TopSVDFunctions.h"

////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////    Function Definitions  ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////



// SVD Unfolding Helper Function
TString TopSVDFunctions::SVD_CPQSS(TString channel, TString particle, TString quantity, TString special, TString syst)
{
    TString cpq = ""; 
    cpq.Append(channel);
    cpq.Append("_");
    cpq.Append(particle);
    cpq.Append("_");
    cpq.Append(quantity);
    if ( special.CompareTo("") != 0 ) {
        if ( special.BeginsWith("_") == true ) special.Remove(0,1); 
        cpq.Append("_");
        cpq.Append(special);
    }
    if ( syst.CompareTo("") != 0 ) {
        if ( syst.BeginsWith("_") == true ) syst.Remove(0,1); 
        cpq.Append("_");
        cpq.Append(syst);
    }
    return cpq;
}


// Create a name for a plot according to a certain scheme
// This name will be used for saving the histogram in a root file
TString TopSVDFunctions::SVD_PlotName(TString channel, TString particle, TString quantity, TString special, TString syst, TString plotName)
{
    TString rawStr("SVD_");
    rawStr.Append(SVD_CPQSS(channel, particle, quantity, special, syst));
    rawStr.Append("_");
    rawStr.Append(plotName); 

    return rawStr;
}

 
// Division of positive doubles
// If an argument is smaller or equal to zero,
// the result is zero.
double TopSVDFunctions::SVD_Divide(double numerator, double denominator)
{
    double result = 0.;
    if ( numerator > 0. && denominator > 0. ) {
        result = numerator / denominator;
    }
    return result;
}


// Calculates binomial errors                  
double TopSVDFunctions::SVD_BinomialError(double numerator, double denominator)
{
    if (numerator>denominator) {
        return 0.;
        cout << "WARNING in BinomialError: efficiency is larger than one!" << endl;
    }

    double  error;
    error=TMath::Sqrt((1-numerator/denominator)
                      *numerator/denominator/denominator);

    return error;
}



// Sqrt of positive doubles
// If an argument is smaller or equal to zero,
// the result is zero.
double TopSVDFunctions::SVD_Sqrt(double square)
{
    double result = 0.;
    if ( square > 0. ) {
        result = TMath::Sqrt(square);
    }

    return result;
}


// Helper Function to create a nicely formatted legend.
// if mode = 0, header and k will be shown
// if mode = 1, header and tau will be shown
// if mode < 0 or it mode > 1, nothing will be shown 
TLegend* TopSVDFunctions::SVD_NewLegend(TString header1, TString header2, double regPar, int mode) {

    // Style
    TLegend *leg = new TLegend();
    leg->SetX1NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength()-0.25);
    leg->SetY1NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength()-0.15);
    leg->SetX2NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength());
    leg->SetY2NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength());
    leg->SetTextFont(42);
    leg->SetTextSize(0.03); // 0.03
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextAlign(12);
    
    
    // Header, first line
    TString theHeader1 = header1;
    if ( theHeader1.CompareTo("") != 0 ) {
        leg->AddEntry((TObject*) NULL, theHeader1, "");
    }
    //leg->SetHeader(theHeader1);
    
    
    // Header, second line
    TString theHeader2 = header2;
    if ( theHeader2.CompareTo("") != 0 ) {
        leg->AddEntry((TObject*) NULL, theHeader2, "");
    }
    
    
    // Header, third line
    if ( mode == 1 ) {
        TString theHeader3 = ""; 
        theHeader3.Append("#tau = ");
        theHeader3.Append(TString::Format("%.3f", regPar)); 
        leg->AddEntry((TObject*) NULL, theHeader3, "");
    } else if ( mode == 0 ) {
        TString theHeader3 = ""; 
        theHeader3.Append("k = ");
        theHeader3.Append(TString::Format("%.0f", regPar));
        leg->AddEntry((TObject*) NULL, theHeader3, "");
    } 
         
    

    return leg;

} 


// Helper Function to create a nicely formatted
// legend for the k scan plots
TLegend* TopSVDFunctions::SVD_NewLegendK() {

    TLegend *leg = new TLegend();
//    leg->SetX1NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength()-0.15);
//    leg->SetY1NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength()-0.5);
//    leg->SetX2NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength());
//    leg->SetY2NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength());
    leg->SetX1NDC(1.0-gStyle->GetPadRightMargin());
    leg->SetY1NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength()-0.5);
    leg->SetX2NDC(1.0);
    leg->SetY2NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength());
    leg->SetTextFont(42);
    leg->SetTextSize(0.03); // 0.04
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextAlign(12);

    return leg;

} 

// Clone Array of 1D Hists
// Attention: New objects will be created on the heap.
// Do not fortget to delete them somewhere
TH1D* TopSVDFunctions::SVD_CloneHists1D(TH1D* hist, int numHist){
    
    if ( hist == NULL ) return NULL;  
    
    // Create new objects
    TH1D* outputhists = new TH1D[numHist];
    for ( int h = 0 ; h < numHist ; h++ ) {  
        *(outputhists+h) = *(hist+h); 
        TString tmpName = (hist+h)->GetName(); 
        tmpName.Append("Clone"); 
        (outputhists+h)->SetName(tmpName); 
    }
    
    // return new array
    return outputhists;
}

// Clone Array of 2D Hists
// Attention: New objects will be created on the heap.
// Do not fortget to delete them somewhere
TH2D* TopSVDFunctions::SVD_CloneHists2D(TH1D* hist, int numHist){
    
    if ( hist == NULL ) return NULL;  
    
    // Create new objects
    TH2D* outputhists = new TH2D[numHist];
    for ( int h = 0 ; h < numHist ; h++ ) {
        (hist+h)->Copy(*(outputhists+h));
        TString tmpName = (hist+h)->GetName();
        tmpName.Append("Clone");
        (outputhists+h)->SetName(tmpName); 
    }
    
    // return new array
    return outputhists;
}

// Move Events in OF/UF bins in dedicated side bins.
// Attention: Sidebins need to be created first
// Error recalculated in Poisson manner.
// Can handle arrays of histograms
void TopSVDFunctions::SVD_MoveOFBins1D(TH1D* hist, int numHist){
    
    if ( hist == NULL ) return; 
    int nBins = hist->GetNbinsX();
    
    // Loop over all histograms in the array
    for ( int h = 0 ; h < numHist ; h++ ) {

        // Count OF Events 
        double ufBin = (hist+h)->GetBinContent(0);
        ufBin += (hist+h)->GetBinContent(1);
        double ofBin = (hist+h)->GetBinContent(nBins+1);
        ofBin += (hist+h)->GetBinContent(nBins);
    
        // Set Side Bins
        (hist+h)->SetBinContent(0, 0.);
        (hist+h)->SetBinContent(1, ufBin);
        (hist+h)->SetBinContent(nBins, ofBin);
        (hist+h)->SetBinContent(nBins+1, 0.);
    
        // Set Side Bins / Error
        (hist+h)->SetBinError(0, 0.);
        (hist+h)->SetBinError(1, 0.);
        (hist+h)->SetBinError(nBins, 0.);
        (hist+h)->SetBinError(nBins+1, 0.);
        if ( ufBin > 0. ) {
            (hist+h)->SetBinError(1, TMath::Sqrt(ufBin));
        }
        if ( ofBin > 0. ) {
            (hist+h)->SetBinError(nBins, TMath::Sqrt(ofBin));
        }
    }
}




// Move Events in OF/UF bins in dedicated side bins
// Attention: Sidebins need to be created first
// Error recalculated in Possion manner
// Can handle arrays of histograms
void TopSVDFunctions::SVD_MoveOFBins2D(TH2D* hist, int numHist){
    
    if ( hist == NULL ) return; 
    int nBinsx = hist->GetNbinsX();
    int nBinsy = hist->GetNbinsY();
    
    // Loop over all histograms in the array 
    for ( int h = 0 ; h < numHist ; h++ ) {
    
    
        // Loop over bins in X direction
        for ( int i = 0 ; i < nBinsx+2 ; i++ ) {
    
             // Count OF Events
            double ufBin = (hist+h)->GetBinContent(i,0);
            ufBin += (hist+h)->GetBinContent(i,1);
            double ofBin = (hist+h)->GetBinContent(i,nBinsy+1);
            ofBin += (hist+h)->GetBinContent(i,nBinsy);
        
            // Set Side Bins
            (hist+h)->SetBinContent(i, 0, 0.);
            (hist+h)->SetBinContent(i, 1, ufBin);
            (hist+h)->SetBinContent(i, nBinsy, ofBin);
            (hist+h)->SetBinContent(i, nBinsy+1, 0.);
        
            // Set Side Bins / Error
            (hist+h)->SetBinError(i, 0, 0.);
            (hist+h)->SetBinError(i, 1, 0.);
            (hist+h)->SetBinError(i, nBinsy, 0.);
            (hist+h)->SetBinError(i, nBinsy+1, 0.);
            if ( ufBin > 0. ) {
                (hist+h)->SetBinError(i, 1, TMath::Sqrt(ufBin));
            }
            if ( ofBin > 0. ) {
                (hist+h)->SetBinError(i, nBinsy, TMath::Sqrt(ofBin));
            }
        }
    
        // Now, loop over bins in Y direction
        // The first and last row should be empty already
        // But this does not hurt
        for ( int i = 0 ; i < nBinsy+2 ; i++ ) {
    
             // Count OF Events
            double ufBin = (hist+h)->GetBinContent(0,i);
            ufBin += (hist+h)->GetBinContent(1,i);
            double ofBin = (hist+h)->GetBinContent(nBinsx+1,i);
            ofBin += (hist+h)->GetBinContent(nBinsx,i);
    
            // Set Side Bins
            (hist+h)->SetBinContent(0, i, 0.);
            (hist+h)->SetBinContent(1, i, ufBin);
            (hist+h)->SetBinContent(nBinsx,   i, ofBin);
            (hist+h)->SetBinContent(nBinsx+1, i, 0.);
    
            // Set Side Bins / Error
            (hist+h)->SetBinError(0, i, 0.);
            (hist+h)->SetBinError(1, i, 0.);
            (hist+h)->SetBinError(nBinsx, i, 0.);
            (hist+h)->SetBinError(nBinsx+1, i, 0.);
            if ( ufBin > 0. ) {
                (hist+h)->SetBinError(1, i, TMath::Sqrt(ufBin));
            }
            if ( ofBin > 0. ) {
                (hist+h)->SetBinError(nBinsx, i, TMath::Sqrt(ofBin));
            }
        }
    }
    
}





// This empties the dedicated side bins.
// Should be called for reconstructed quantities.
// Histogram side bins are also emptied.
// Can handle arrays of histograms
void TopSVDFunctions::SVD_EmptySideBins1D(TH1D* histo, int numHist) 
{
    if ( histo == NULL ) return;
    int bins = histo->GetNbinsX();
    
    // Loop over all histograms in the array 
    for ( int h = 0 ; h < numHist ; h++ ) {
        (histo+h)->SetBinContent(0, 0.);
        (histo+h)->SetBinContent(1, 0.);
        (histo+h)->SetBinContent(bins, 0.);    
        (histo+h)->SetBinContent(bins+1, 0.);
        (histo+h)->SetBinError(0, 0.);
        (histo+h)->SetBinError(1, 0.);
        (histo+h)->SetBinError(bins, 0.);
        (histo+h)->SetBinError(bins+1, 0.);
    }
    
}



// Empties all bins and all errors in a histogram
// Can handle arrays of histograms
void TopSVDFunctions::SVD_EmptyHistogram1D(TH1D* histo, int numHist)
{
    if ( histo == NULL ) return;
    int nbins = histo->GetNbinsX();
    
    // Loop over all histograms in the array 
    for ( int h = 0 ; h < numHist ; h++ ) {
        for ( int i = 0 ; i < nbins ; i++ ) {
            (histo+h)->SetBinContent(i, 0.);
            (histo+h)->SetBinError(i, 0.);
        }
    }
}



// Empties all bins and all errors in a histogram
// Can handle arrays of histograms
void TopSVDFunctions::SVD_EmptyHistogram2D(TH2D* histo, int numHist)
{
    if ( histo == NULL ) return;
    int nbinsx = histo->GetNbinsX();
    int nbinsy = histo->GetNbinsY();
    int nbins = (nbinsx+2) * (nbinsy+2);
    
    for ( int h = 0 ; h < numHist ; h++ ) {
        for ( int i = 0 ; i < nbins ; i++ ) {
            (histo+h)->SetBinContent(i, 0.);
            (histo+h)->SetBinError(i, 0.);
        }
    }
}



// Empties all errors in a histogram
// Can handle arrays of histograms
void TopSVDFunctions::SVD_EmptyHistoErrors1D(TH1D* histo, int numHist)
{
    if ( histo == NULL ) return;
    int nbins = histo->GetNbinsX();
    
    // Loop over all histograms in the array 
    for ( int h = 0 ; h < numHist ; h++ ) {
        for ( int i = 0 ; i < nbins ; i++ ) { 
            (histo+h)->SetBinError(i, 0.);
        }
    }
}



// Empties all errors in a histogram
// Can handle arrays of histograms
void TopSVDFunctions::SVD_EmptyHistoErrors2D(TH2D* histo, int numHist)
{
    if ( histo == NULL ) return;
    int nbinsx = histo->GetNbinsX();
    int nbinsy = histo->GetNbinsY();
    int nbins = (nbinsx+2) * (nbinsy+2);
    
    // Loop over all histograms in the array 
    for ( int h = 0 ; h < numHist ; h++ ) {
        for ( int i = 0 ; i < nbins ; i++ ) { 
            (histo+h)->SetBinError(i, 0.);
        }
    }
}


// This empties the dedicated side bins.
// Should be called for reconstructed quantities,
// which are assumed to be on X axis.
// Histogram side bins are also emptied.
// Can handle arrays of histograms
void TopSVDFunctions::SVD_EmptySideBins2D(TH2D* histo, int numHist)
{
    if ( histo == NULL ) return; 
    int binsx = histo->GetNbinsX();
    int binsy = histo->GetNbinsY();
    
    // Loop over all histograms in the array 
    for ( int h = 0 ; h < numHist ; h++ ) {

        // Loop over generated bins (on Y axis)
        for ( int j = 0 ; j < binsy+2 ; j++ ) { 
            (histo+h)->SetBinContent(0, j, 0.);
            (histo+h)->SetBinContent(1, j, 0.);
            (histo+h)->SetBinContent(binsx, j, 0.);
            (histo+h)->SetBinContent(binsx+1, j, 0.);
            (histo+h)->SetBinError(0, j, 0.);
            (histo+h)->SetBinError(1, j, 0.);
            (histo+h)->SetBinError(binsx, j, 0.);
            (histo+h)->SetBinError(binsx+1, j, 0.);
        }
    
    }

}

 


// Rebinning of 1D Histograms. 
// ATTENTION! ATTENTION! ATTENTION! ATTENTION! ATTENTION!
// (1) Creates new histograms on the heap. 
//     So dont forget to delete them sometimes. 
// (2) In 'binsx' the bin boundaries are specified!
//     'nbinsx' gives the number of specified bins!
// (3) The first and last bin in 'binsx' are considered
//     as overflow bins, all other bins as center bins!
//     The overflow bins will get all events that cannot be
//     assigned a center bin. The TH2D-side-bins will not be used
//     for the output-histogram.
// (5) Each (but the first and last) bin boundary in 'binsx'  
//     MUST match one in the input-histograms, otherwise double counting 
//     will occur.
// (6) Can also handle Arrays of histograms, if numHist > 1.
//     All input histograms must have the same binning!
TH1D* TopSVDFunctions::SVD_Rebin1D(TH1D* input, int nbinsx, double* binsx, int numHist)
{ 
    
    if ( input == NULL ) return NULL;
    if ( numHist <= 1 ) numHist = 1;
     
    // Binning of old histogram
    int nbinsGenRecX =input->GetNbinsX();
    
    // Create new objects
    TH1D* outputhists = new TH1D[numHist];
    for ( int h = 0 ; h < numHist ; h++ ) {
        
        // Clean fresh histogram
        TString nameNewHist = (input+h)->GetName();
        nameNewHist.Append("Rebinned");
        (outputhists+h)->SetNameTitle(nameNewHist, nameNewHist);
        (outputhists+h)->SetBins(nbinsx, binsx);
        SVD_EmptyHistogram1D(outputhists+h, 1); 
    
    
    
        // Do NOT use the side bins of th TH2D-Class! 
        for(int i=1; i<=nbinsx; ++i){ 
        
            // Variables for the bin boundaries
            double xlow  = 0.;
            double xhigh = 0.;
            double newxlow = 0.;
            double newxhigh = 0.;
            double binwidth = 0.; 
            bool alarm = false;
            double alarmTresh = 0.0001;
            
            // Find bin boundaries in X
            int nxlow = -1;
            int nxhigh = -1;
            if ( i == 1 ) {   // UF bin in X 
                xlow = binsx[0]; 
                xhigh = binsx[1];  
                nxlow = 0;
                nxhigh = SVD_FindBin((input+h)->GetXaxis(), xhigh) - 1;   
                newxlow = xlow;
                newxhigh = (input+h)->GetXaxis()->GetBinLowEdge(nxhigh+1);
                binwidth = xhigh - xlow; 
                if ( TMath::Abs(newxhigh-xhigh)/binwidth >  alarmTresh ) alarm = true;
            }
            if ( i == nbinsx ) {  // OF bin in X
                xlow = binsx[nbinsx-1]; 
                xhigh = binsx[nbinsx]; 
                nxlow = SVD_FindBin((input+h)->GetXaxis(), xlow);
                nxhigh = nbinsGenRecX+1;
                newxlow = (input+h)->GetXaxis()->GetBinLowEdge(nxlow);
                newxhigh = xhigh;
                binwidth = xhigh - xlow;
                if ( TMath::Abs(newxlow-xlow)/binwidth >  alarmTresh ) alarm = true;
            }
            if ( i > 1 && i < nbinsx) { // Center bin in X
                xlow = binsx[i-1];
                xhigh = binsx[i];
                nxlow = SVD_FindBin((input+h)->GetXaxis(), xlow);
                nxhigh = SVD_FindBin((input+h)->GetXaxis(), xhigh) - 1;  
                newxlow = (input+h)->GetXaxis()->GetBinLowEdge(nxlow);
                newxhigh = (input+h)->GetXaxis()->GetBinLowEdge(nxhigh+1);
                binwidth = xhigh - xlow;
                if ( TMath::Abs(newxhigh-xhigh)/binwidth >  alarmTresh ) alarm = true;
                if ( TMath::Abs(newxlow-xlow)/binwidth >  alarmTresh ) alarm = true;
            }

    
            // Alarm, if the bin boundaries do not match
            if ( alarm == true ) {
                cout << "*****************************************************************" << endl;
                cout << "Error in TopSVDFunctions::SVD_Rebin1D" << endl;
                cout << "The new bin boundaries cannot be matched to the ones in the" << endl;
                cout << "input histogram." << endl;
                cout << "Old bins in X: " << endl;
                for ( int k = 1; k <= nbinsGenRecX+1 ; k++ ) {
                    cout << " " <<  (input+h)->GetXaxis()->GetBinLowEdge(k);
                } 
                cout << endl;
                cout << "New bins in X: " << endl;
                for ( int k = 0; k < nbinsx+1 ; k++ ) {
                    cout << " " << binsx[k];
                }
                cout << endl;
                cout << "Exiting ... " << endl;
                cout << "*****************************************************************" << endl;
                exit(1);
            }
                 
     
            // Integrate over all the original bins
            double sum = 0.;
            double sumErrSq = 0.;
            if ( nxlow <= nxhigh ) {
                for ( int b = nxlow ; b <= nxhigh ; b++ ) {
                    double binContent = ((TH1D*) (input+h))->GetBinContent(b);
                    double binError = ((TH1D*) (input+h))->GetBinError(b);
                    sum += binContent;
                    sumErrSq += binError*binError;
                }
            } else {
                sum = 0.;
                sumErrSq = 0.;
            }
     

            // Save it
            (outputhists+h)->SetBinContent(i, sum);
            (outputhists+h)->SetBinError(i, TMath::Sqrt(sumErrSq));
        }
        
    }

    // Return the array
    return outputhists;
}

    


// Rebinning of a 2D Histogram. 
// ATTENTION! ATTENTION! ATTENTION! ATTENTION! ATTENTION!
// (1) Creates a new histogram on the heap. 
//     So dont forget to delete it sometimes.
// (2) If needed, you can transpose the matrix, too. 
// (3) In 'binsx' and 'binsy' the bin boundaries are specified!
//     'nbinsx' and 'nbinsy' the number of specified bins!
// (4) The first and last bin in 'binsx' and 'binsy' are considered
//     as overflow bins, all other bins as center bins!
//     The overflow bins will get all events that cannot be
//     assigned a center bin. The TH2D-side-bins will not be used
//     for the output-histogram.
// (5) Each (but the first and last) bin boundary in 'binsx' and 'binsy' 
//     MUST match one in the input-histogram, otherwise double counting 
//     will occur.
TH2D* TopSVDFunctions::SVD_Rebin2D(TH2D* input, int nbinsx, double* binsx, int nbinsy, double* binsy, int numHist, bool transpose)
{ 
    if ( input == NULL ) return NULL;
    if ( numHist <= 1 ) numHist = 1;
    
    // Binning of old histogram
    int nbinsGenRecX =input->GetNbinsX();
    int nbinsGenRecY =input->GetNbinsY();
    
    // Create new objects
    TH2D* outputhists = new TH2D[numHist];
    for ( int h = 0 ; h < numHist ; h++ ) {
        
        // Clean fresh histogram
        TString nameNewHist = (input+h)->GetName();
        nameNewHist.Append("Rebinned");
        (outputhists+h)->SetNameTitle(nameNewHist, nameNewHist);
        (outputhists+h)->SetBins(nbinsx, binsx, nbinsy, binsy);
        SVD_EmptyHistogram2D(outputhists+h, 1);  
    
        // Do NOT use the side bins of th TH2D-Class! 
        for(int i=1; i<=nbinsx; ++i){ 
            for(int j=1; j<=nbinsy; ++j){ 
    
        
                // Variables for the bin boundaries
                double xlow  = 0.;
                double xhigh = 0.;
                double ylow  = 0.;
                double yhigh = 0.;
                double newxlow = 0.;
                double newxhigh = 0.;
                double newylow = 0.;
                double newyhigh = 0.;
                double binwidthx = 0.; 
                double binwidthy = 0.; 
                bool alarm = false;
                double alarmTresh = 0.0001;
            
            
                // Find bin boundaries in X
                int nxlow = -1;
                int nxhigh = -1;
                if ( i == 1 ) {   // UF bin in X
                    xlow = binsx[0]; 
                    xhigh = binsx[1];  
                    nxlow = 0;
                    nxhigh = SVD_FindBin((input+h)->GetXaxis(), xhigh) - 1;   
                    newxlow = xlow;
                    newxhigh = (input+h)->GetXaxis()->GetBinLowEdge(nxhigh+1);
                    binwidthx = xhigh - xlow; 
                    if ( TMath::Abs(newxhigh-xhigh)/binwidthx >  alarmTresh ) alarm = true; 
                }
                if ( i == nbinsx ) {  // OF bin in X
                    xlow = binsx[nbinsx-1]; 
                    xhigh = binsx[nbinsx]; 
                    nxlow = SVD_FindBin((input+h)->GetXaxis(), xlow);
                    nxhigh = nbinsGenRecX+1;
                    newxlow = (input+h)->GetXaxis()->GetBinLowEdge(nxlow);
                    newxhigh = xhigh;
                    binwidthx = xhigh - xlow;
                    if ( TMath::Abs(newxlow-xlow)/binwidthx >  alarmTresh ) alarm = true; 
                }
                if ( i > 1 && i < nbinsx) { // Center bin in X
                    xlow = binsx[i-1];
                    xhigh = binsx[i];
                    nxlow = SVD_FindBin((input+h)->GetXaxis(), xlow);
                    nxhigh = SVD_FindBin((input+h)->GetXaxis(), xhigh) - 1;  
                    newxlow = (input+h)->GetXaxis()->GetBinLowEdge(nxlow);
                    newxhigh = (input+h)->GetXaxis()->GetBinLowEdge(nxhigh+1);
                    binwidthx = xhigh - xlow;
                    if ( TMath::Abs(newxhigh-xhigh)/binwidthx >  alarmTresh ) alarm = true;
                    if ( TMath::Abs(newxlow-xlow)/binwidthx >  alarmTresh ) alarm = true; 
                }
    
                // Find bin boundaries in Y
                int nylow = -1;
                int nyhigh = -1;
                if ( j == 1 ) {  // UF bin in Y
                    ylow = binsy[0]; 
                    yhigh = binsy[1];  
                    nylow = 0;
                    nyhigh = SVD_FindBin((input+h)->GetYaxis(), yhigh) - 1;   
                    newylow = ylow;
                    newyhigh = (input+h)->GetYaxis()->GetBinLowEdge(nyhigh+1);
                    binwidthy = yhigh - ylow; 
                    if ( TMath::Abs(newyhigh-yhigh)/binwidthy >  alarmTresh ) alarm = true;   
                }
                if ( j == nbinsy) {   // UF bin in Y
                    ylow = binsy[nbinsy-1]; 
                    yhigh = binsy[nbinsy]; 
                    nylow = SVD_FindBin((input+h)->GetYaxis(), ylow);
                    nyhigh = nbinsGenRecY+1;
                    newylow = (input+h)->GetYaxis()->GetBinLowEdge(nylow);
                    newyhigh = yhigh;
                    binwidthy = yhigh - ylow;
                    if ( TMath::Abs(newylow-ylow)/binwidthy >  alarmTresh ) alarm = true;  
                }
                if ( j > 1 && j < nbinsy ) { // Center bin in Y
                    ylow = binsy[j-1];
                    yhigh = binsy[j];
                    nylow = SVD_FindBin((input+h)->GetYaxis(), ylow);
                    nyhigh = SVD_FindBin((input+h)->GetYaxis(), yhigh) - 1;  
                    newylow = (input+h)->GetYaxis()->GetBinLowEdge(nylow);
                    newyhigh = (input+h)->GetYaxis()->GetBinLowEdge(nyhigh+1);
                    binwidthy = yhigh - ylow;
                    if ( TMath::Abs(newyhigh-yhigh)/binwidthy >  alarmTresh ) alarm = true;
                    if ( TMath::Abs(newylow-ylow)/binwidthy >  alarmTresh ) alarm = true;  
                } 
                
                
                
        
                // Alarm, if the bin boundaries do not match
                if ( alarm == true ) {
                    cout << "*****************************************************************" << endl;
                    cout << "Error in TopSVDFunctions::SVD_Rebin2D" << endl;
                    cout << "The new bin boundaries cannot be matched to the ones in the" << endl;
                    cout << "input histogram." << endl;
                    cout << "Old bins in X: " << endl;
                    for ( int k = 1; k <= nbinsGenRecX+1 ; k++ ) {
                        cout << " " <<  (input+h)->GetXaxis()->GetBinLowEdge(k);
                    } 
                    cout << endl;
                    cout << "New bins in X: " << endl;
                    for ( int k = 0; k < nbinsx+1 ; k++ ) {
                        cout << " " << binsx[k];
                    }
                    cout << endl;
                    cout << "Old bins in Y: " << endl;
                    for ( int k = 1; k <= nbinsGenRecY+1 ; k++ ) {
                        cout << " " <<  (input+h)->GetYaxis()->GetBinLowEdge(k);
                    } 
                    cout << endl;
                    cout << "New bins in Y: " << endl;
                    for ( int k = 0; k < nbinsy+1 ; k++ ) {
                        cout << " " << binsy[k];
                    }
                    cout << endl;
                    cout << "Exiting ... " << endl;
                    cout << "*****************************************************************" << endl;
                    exit(1);
                }
                
                
                // Integrate over all the original bins        
                double sum = 0.;
                  double sumErrSq = 0.;
                if ( nxlow <= nxhigh && nylow <= nyhigh ) {
                    for ( int bx = nxlow ; bx <= nxhigh ; bx++ ) {
                        for ( int by = nylow ; by <= nyhigh ; by++ ) { 
                            double binContent = ((TH1D*) (input+h))->GetBinContent(bx, by);
                            double binError = ((TH1D*) (input+h))->GetBinError(bx, by);
                            sum += binContent;
                            sumErrSq += binError*binError;
                        }
                    }
                } else { 
                       sum = 0.;
                       sumErrSq = 0.;
                }
    
                // Save it, thereby transpose if needed
                if ( transpose == true ) {
                    (outputhists+h)->SetBinContent(j, i, sum);
                    (outputhists+h)->SetBinError(j, i, TMath::Sqrt(sumErrSq)); 
                } else { 
                    (outputhists+h)->SetBinContent(i, j, sum);
                    (outputhists+h)->SetBinError(i, j, TMath::Sqrt(sumErrSq)); 
                }
            }
        }
    }
    
    
    // return it
    return outputhists;
                    
}




// Create Correlation Matrix from Covariance Matrix
// Creates a TH2D on the heap, so delete it eventually
// Attention: There are some cases, where one of the errors for the denominator
// is zero. This is okay, if the covariance is zero itself. In this case, the
// correlation should be zero. In all other cases, a warning message is thrown.   
TH2D* TopSVDFunctions::SVD_Cov2Corr(TH2D* input, TString name, TString axisName, TString type)
{
    int nbins = input->GetNbinsX(); // Same for X and Y

    // Clone input histogram
    TH2D* output = (TH2D*) input->Clone(name);
    output->SetName(name);
    output->SetTitle(name);
    TString corrStrZ(type + " Correlations in \%");
    output->GetXaxis()->SetTitle(axisName);
    output->GetYaxis()->SetTitle(axisName);
    output->GetZaxis()->SetTitle(corrStrZ);
    for ( int i = 1; i <= nbins ; i++ ) {
        for ( int j = 1; j <= nbins ; j++ ) {
            double cov = input->GetBinContent(i,j);
            double errsq1 = input->GetBinContent(i,i);
            double errsq2 = input->GetBinContent(j,j);
            double entry = 0.;
            if ( i != j ) {
                if ( errsq1 > 0. && errsq2 > 0. ) {
                    entry = 100*cov/(TMath::Sqrt(errsq1*errsq2));
                } else {
                    if ( cov == 0. &&  errsq1 >= 0. && errsq2 >= 0. && (errsq1 == 0. || errsq2 == 0.)) {
                        entry = 0.;
                    } else {
                        cout << "*********************************************************" << endl;
                        cout << "WARNING! TopSVDFunctions::SVD_Cov2Corr()" << endl;
                        cout << "Couldn't calculate correlation for i=" << i << ", j=" << j << endl;
                        cout << "    in Histogram: " << name << endl;
                        cout << "Reason: Funny numbers.  " << endl;
                        cout << "    Covariance(" << i << "," << j << ") = " << cov << endl;
                        cout << "    ErrorSquared(" << i << ") = " << errsq1 << endl;
                        cout << "    ErrorSquared(" << j << ") = " << errsq2 << endl; 
                        cout << "Setting Correlation to Zero for now. Please fix this." << endl;
                        cout << "*********************************************************" << endl;
                    } 
               }
           }
           output->SetBinContent(i,j, entry);
       }
    }

    // Return pointer
    return output;

}




// Create Error Plot from Covariance Matrix
// Creates a TH1D on the heap, so delete it eventually
TH1D* TopSVDFunctions::SVD_Cov2Err(TH2D* input, TH1D* means, TString name, TString axisName, TString type)
{
    int nbins = input->GetNbinsX(); 

    // Clone input histogram
    TH1D* output = (TH1D*) means->Clone(name);
    output->SetName(name);
    output->SetTitle(name);
    TString corrStrY(type + " Error in \%");
    output->GetXaxis()->SetTitle(axisName);
    output->GetYaxis()->SetTitle(corrStrY);
    for ( int i = 1 ; i <= nbins ; i++ ) {
        double variance = input->GetBinContent(i,i);
        double value = means->GetBinContent(i);
        double error = 0.;
        if ( value > 0. ) error = 100*TMath::Sqrt(variance) / value;
        output->SetBinContent(i, error);
        output->SetBinError(i, 0.);
    }

    // Return pointer
    return output;
}






// Formats a 2D histogram according to current style
// Corrects formatting in a manner specific to 2D histos  
void TopSVDFunctions::SVD_Draw2D(TH2D* hist, TString options)
{
    // Set the Style    
    hist->UseCurrentStyle();

    // Z axis title offset
    double zTitleOffset = 1.6;
    hist->GetZaxis()->SetTitleOffset(zTitleOffset);

    // Draw it, thereby create pad primitives
    hist->Draw(options);

    // Change the position of the palette
    gPad->Update();
    TPaletteAxis* palette = NULL;
    palette = (TPaletteAxis*) hist->GetListOfFunctions()->FindObject("palette");
    if ( palette != NULL ) {
        palette->SetY1NDC(gStyle->GetPadBottomMargin()+0.05);
    }
}


// Formats a 1D histogram according to current style
// Corrects formatting in a manner specific to 1D histos
// If color < 1, then color will be set autmatically 
void TopSVDFunctions::SVD_Draw1D(TH1D* hist, TString options,  int color)
{
    // Use current style
    hist->UseCurrentStyle();
    if (color > 0) hist->SetLineColor(color);
    if (color > 0) hist->SetMarkerColor(color);

    // Draw it
    hist->Draw(options);

    // Correct Y Range
    double ymin = hist->GetMinimum();
    double ymax = hist->GetMaximum();
    double newYRange = 1.3 * (ymax -ymin);
    hist->SetMaximum(ymin+newYRange);

}

// Get Range of a Graph
void TopSVDFunctions::SVD_RangeGraph(TGraph* graph, double& xmin, double& xmax, double& ymin, double& ymax)
{
    
    int nPoints = graph->GetN();
     
    // Get Range
    xmax = -FLT_MAX;
    ymax = -FLT_MAX;
    xmin = +FLT_MAX;
    ymin = +FLT_MAX;
    for ( int i = 0; i < nPoints ; i++ ) {
         double theX = 0.;
         double theY = 0.;
         graph->GetPoint(i, theX, theY);
         if ( theX > xmax ) xmax = theX;
         if ( theY > ymax ) ymax = theY;
         if ( theX < xmin ) xmin = theX;
         if ( theY < ymin ) ymin = theY;
    }
     
}

// Makes a graph from two vectors and formats it
// Corrects formatting in a manner specific to 1D histos
// If color < 1, then color will be set autmatically 
// Note: This function draws an empty histogram first,
// then draws the graph on top of it. The histo is returned.
// If you already have a background histo, provide it in the last argument.
void TopSVDFunctions::SVD_DrawGraph(TGraph* graph, TH1D*& bgrHisto, TString options,  int color)
{
     
    // Get Range
    double xmax = 0.;
    double xmin = 0.;
    double ymax = 0.;
    double ymin = 0.;
    SVD_RangeGraph(graph, xmin, xmax, ymin, ymax);
    
    // New Ranges
    double newXmin = 0.;
    double newXmax = 0.; 
    double newYmin = 0.; // Leave this
    double newYmax = 0.; 
    SVD_NewRange(xmin, xmax, newXmin, newXmax, gPad->GetLogx()); 
    SVD_NewUpperRange(ymax, newYmax);
    
    
    // Make new Histo
    if ( bgrHisto == NULL) { 
        
        // Create the object
        bgrHisto = new TH1D("bgrHist", "bgrHist", 10, newXmin, newXmax);
        bgrHisto->UseCurrentStyle();
        
        // Draw it
        bgrHisto->Draw();
        
        // Correct Y Range
        bgrHisto->SetMinimum(newYmin);
        bgrHisto->SetMaximum(newYmax);
    }
    
    // Draw options
    TString drawOptions = options;
    drawOptions.Append(" SAME");
    
    // Use current style
    graph->UseCurrentStyle();
    if (color > 0) graph->SetLineColor(color);
    if (color > 0) graph->SetMarkerColor(color);

    // Draw it
    graph->Draw(drawOptions);
      

}
 

// A little shift on the position of a text string in X
double TopSVDFunctions::SVD_TextPosX(TH1D* hist, double xpos, bool log, int orientation)
{ 
    // Get Axis Range
    double min = hist->GetXaxis()->GetXmin();
    double max = hist->GetXaxis()->GetXmax(); 
    if ( min >= max ) return 0.;
     
     
    // Position
    double thePos = xpos; 
    if ( thePos < min ) thePos = min;
    if ( thePos > max ) thePos = max; 
    
    
    // Log
    if ( log == true ) {
        if ( min > 0. ) { 
            min = TMath::Log10(min);     

        } else {
            return 0.;
        }
        if ( max > 0. ) { 
            max = TMath::Log10(max); 
        } else {
            return 0.;
        }
        if ( thePos > 0. ) {
            thePos = TMath::Log10(thePos); 
        } else {
            return 0.;
        }
    } 
    
    // Orientation ... take first digit
    int theOrientation = orientation / 10;
    
    
    // Shift
    double shift = 0.05*(max - min); 
    if ( theOrientation == 3 ) thePos = thePos - shift; 
    if ( theOrientation == 2 ) thePos = thePos; 
    if ( theOrientation == 1 ) thePos = thePos + shift; 
    
     
    // Log
    if ( log == true ) {
        thePos = TMath::Power(10., thePos);
    }
     
    // Return
    return thePos; 
}
 

// A little shift on the position of a text string in Y
double TopSVDFunctions::SVD_TextPosY(TH1D* hist, double ypos, bool log, int orientation)
{ 
    // Get Axis Range
    double min = hist->GetMinimum();
    double max = hist->GetMaximum(); 
    if ( min >= max ) return 0.;
     
      
    // Position
    double thePos = ypos; 
    if ( thePos < min ) thePos = min;
    if ( thePos > max ) thePos = max; 
    
    // Log
    if ( log == true ) {
        if ( min > 0. ) {
            min = TMath::Log10(min);
        } else {
            return 0.;
        }
        if ( max > 0. ) {
            max = TMath::Log10(max);
        } else {
            return 0.;
        }
        if ( thePos > 0. ) {
            thePos = TMath::Log10(thePos);
        } else {
            return 0.;
        }
    } 
    
    // Orientation ... take second digit
    int theOrientation = orientation % 10;
    
    
    // Shift
    double shift = 0.05*(max - min);
    if ( theOrientation == 3 ) thePos = thePos - shift; 
    if ( theOrientation == 2 ) thePos = thePos; 
    if ( theOrientation == 1 ) thePos = thePos + shift; 
    
    
    // Log
    if ( log == true ) {
        thePos = TMath::Power(10., thePos);
    }
    
    // Return
    return thePos; 
    
} 
 

// Draws a String somewhere in your pad
// If a TLatex object is given, then it will be used. Otherwise, it will be created.
TLatex* TopSVDFunctions::SVD_DrawText(TString theText, double xpos, double ypos, int orientation, TLatex*& mylatex)
{
    // Create Latex Object
    if ( mylatex == NULL ) {
        mylatex = new  TLatex();
        mylatex->SetTextSize(0.05);  
    }
     
    // Set Orientation
    mylatex->SetTextAlign(orientation);
    
    
    // Draw it
    mylatex->DrawLatex(xpos, ypos, theText);
    
    
    // Make TPaveText
    //TPaveText* pt = new TPaveText();
    
    
    // Return it;
    return mylatex;
        
}


// Draws a vertical line from top to bottom of bgrHisto.
// If color < 1, then color will be set autmatically 
TLine* TopSVDFunctions::SVD_DrawVertLine(TH1D*& bgrHisto, double xpos, int color)
{
    // Get Range of Histogram
    double Ymin = bgrHisto->GetMinimum();
    double Ymax = bgrHisto->GetMaximum();
    
    // New Line
    TLine* line = new TLine(xpos, Ymin, xpos, Ymax);
    line->SetLineColor(color);
    line->SetLineWidth(1);
    line->SetLineStyle(1);
    
    // Test it, whether it is in the range of the histogram
    bool draw = true;
    int nbins = bgrHisto->GetNbinsX();
    double xmin = bgrHisto->GetXaxis()->GetBinLowEdge(1);
    double xmax = bgrHisto->GetXaxis()->GetBinLowEdge(nbins+1);
    if ( xpos < xmin ) draw = false;
    if ( xpos > xmax ) draw = false;
    
    // Draw it
    if ( draw == true ) {
        line->Draw("SAME");
    }
    
    // REturn it
    return line;
    
}

// Draws a horizontal line from top to bottom of bgrHisto.
// If color < 1, then color will be set autmatically 
TLine* TopSVDFunctions::SVD_DrawHorizLine(TH1D*& bgrHisto, double ypos, int color)
{
    // Get Range of Histogram
    int nbins = bgrHisto->GetNbinsX();
    double Xmin = bgrHisto->GetXaxis()->GetBinLowEdge(1);
    double Xmax = bgrHisto->GetXaxis()->GetBinLowEdge(nbins+1);
    
    // New Line
    TLine* line = new TLine(Xmin,  ypos, Xmax, ypos);
    line->SetLineColor(color);
    line->SetLineWidth(1);
    line->SetLineStyle(1);
    
    // Test it, whether it is in the range of the histogram
    bool draw = true; 
    double ymin = bgrHisto->GetMinimum();
    double ymax = bgrHisto->GetMaximum();
    if ( ypos < ymin ) draw = false;
    if ( ypos > ymax ) draw = false;
    
    // Draw it
    if ( draw == true ) {
        line->Draw("SAME");
    }
    
    // REturn it
    return line;
    
}


// Draws a vertical lines from top to bottom of bgrHisto. 
// If color < 1, then color will be set autmatically 
void TopSVDFunctions::SVD_DrawVertLines(TH1D*& bgrHisto, TVectorD* xpositions, int color)
{
    
    // Make Array of Pointers
    int nPoints = xpositions->GetNoElements();   
    
    
    // Loop
    for ( int i = 0 ; i < nPoints ; i++ ) {
        
        // Get Position
        double xpos = (*xpositions)[i];
        
        // Draw Line
        SVD_DrawVertLine(bgrHisto, xpos, color);
          
    }  
    
} 


// Makes a graph from two vectors and formats it 
// Attention: Creates a Graph on the heap. Dont forget to delete it!
TGraph* TopSVDFunctions::SVD_Vect2Graph(TVectorD* vectorX, TVectorD* vectorY)
{
    //Test, if vectorX and vectorY have same number of entries
    int nelements = vectorX->GetNoElements();
    int nelementsY = vectorY->GetNoElements();
    if ( nelements <= 0 || nelementsY <= 0 || nelements != nelementsY ) {
        cout << "Error in TopSVDFunctions::SVD_Vect2Graph()" << endl;
        cout << "   The two vectors have strange sizes." << endl;
        cout << "   vectorX has " << nelements  << " entries." << endl;
        cout << "   vectorY has " << nelementsY << " entries." << endl;
        cout << "Exiting ... " << endl;
        exit(1);
    }
    
    
    // New Graph
    TGraph* graph = new TGraph(*vectorX, *vectorY);
    
    // Return
    return graph;
    
}


// Makes a graph from a the coordinates of a point
// Attention: Creates a Graph on the heap. Dont forget to delete it!
TGraph* TopSVDFunctions::SVD_Point2Graph(double x, double y)
{
    // Create new vectors
    TVectorD vectorX(1);
    TVectorD vectorY(1);
    vectorX[0] = x;
    vectorY[0] = y;
    
    // New Graph
    TGraph* graph = new TGraph(vectorX, vectorY);
    
    // Return
    return graph;
    
}

// SVD Unfolding Helper FUnction
// Format a Ratio plot according to current style
void TopSVDFunctions::SVD_DrawRange(TH1D* histo, double ymin, double ymax, TString options,  int color)
{
    // Clone Histo
    TH1D* hist = (TH1D*) histo->Clone("hist");
 
    // Hide values you dont want
    for ( int i = 0; i < hist->GetNbinsX()+2; i++) {
         double val = hist->GetBinContent(i);
         if ( val > ymax || val < ymin ) {
             hist->SetBinContent(i, 2*ymin - ymax);
             hist->SetBinError(i, 0.);
         }
    }

 
    // Use current style
    hist->UseCurrentStyle();
    hist->SetLineColor(histo->GetLineColor());
    hist->SetMarkerColor(histo->GetMarkerColor());
    if (color > 0) hist->SetLineColor(color);
    if (color > 0) hist->SetMarkerColor(color);
    
    // Draw it
    hist->Draw(options);

    // Range
    double yMin = ymin;
    double yMax = ymax;
    double newYRange = yMax - yMin;
    hist->SetMaximum(ymin+newYRange);
    hist->SetMinimum(ymin);
   
}



// SVD Unfolding Helper FUnction
// Creates a Ratio plot of two histograms
// Errors: relative errors from the NUMERATOR are taken
// Boundaries: If ymax < ymin, then range will be set automatically
TH1D* TopSVDFunctions::SVD_MakeRatioNum(TH1D* numerator, TH1D* denominator, int numHist)
{
     
     if ( numerator == NULL ) return NULL;
     if ( denominator == NULL ) return NULL;
      

    // Create new Histograms
    TH1D* hist = SVD_CloneHists1D(numerator, numHist);

    
    // Loop over all histograms in the array 
    for ( int h = 0 ; h < numHist ; h++ ) {

        // Fill Histogram
        int numbins = hist->GetNbinsX();
        for ( int i = 0 ; i < numbins ; i++) {
            double num = (numerator+h)->GetBinContent(i);
            double denom = (denominator+h)->GetBinContent(i);
            double abs = (numerator+h)->GetBinError(i);
            double val = 0.;
            double err = 0.;
            if ( denom != 0. && num != 0.) {
                val = num / denom;
                err = abs / num;
            }
            (hist+h)->SetBinContent(i, val);
            (hist+h)->SetBinError(i, err);
        }
    }
    
    // Return
    return hist;

}        


// SVD Unfolding Helper FUnction
// Creates a Ratio plot of two histograms
// Errors: relative errors from the DENOMINATOR are taken
// Boundaries: If ymax < ymin, then range will be set automatically
TH1D* TopSVDFunctions::SVD_MakeRatioDenom(TH1D* numerator, TH1D* denominator, int numHist)
{
  
     if ( numerator == NULL ) return NULL;
     if ( denominator == NULL ) return NULL;
     
     
    // Create new Histograms
    TH1D* hist = SVD_CloneHists1D(numerator, numHist);
 
    // Loop over all histograms in the array 
    for ( int h = 0 ; h < numHist ; h++ ) { 
 
        // Fill Histogram
        int numbins = hist->GetNbinsX();
        for ( int i = 0 ; i < numbins ; i++) {
            double num = (numerator+h)->GetBinContent(i);
            double denom = (denominator+h)->GetBinContent(i);
            double abs = (denominator+h)->GetBinError(i);
            double val = 0.;
            double err = 0.;
            if ( denom != 0. ) {
                val = num / denom;
                err = abs / denom;
            }
            (hist+h)->SetBinContent(i, val);
            (hist+h)->SetBinError(i, err);
        }
 
    }
    // Return
    return hist;

}
             

// SVD Unfolding Helper Function
// Creates a Ratio plot of two histograms
// Errors of ratio plot are all set to zero
// Boundaries: If ymax < ymin, then range will be set automatically
TH1D* TopSVDFunctions::SVD_MakeRatioZero(TH1D* numerator, TH1D* denominator, int numHist)
{
 
     if ( numerator == NULL ) return NULL;
     if ( denominator == NULL ) return NULL;
 
    // Create new Histograms
    TH1D* hist = SVD_CloneHists1D(numerator, numHist);
 
    // Loop over all histograms in the array 
    for ( int h = 0 ; h < numHist ; h++ ) { 
   
        // Fill Histogram
        int numbins = hist->GetNbinsX();
        for ( int i = 0 ; i < numbins ; i++) {
            double num = (numerator+h)->GetBinContent(i);
            double denom = (denominator+h)->GetBinContent(i);
            double val = 0.;
            double err = 0.;
            if ( denom != 0. && num != 0.) {
                val = num / denom; 
            }
            (hist+h)->SetBinContent(i, val);
            (hist+h)->SetBinError(i, err);
        }
    }
    
    return hist;

}  

// Formats a Stack of Histos to the current style
// The last argument takes integers between 1 and 9 for the colors, i.e.
// cols=0   means: Do not touch the colors!
// cols=243 means: First Histogram red, second blue, and third and all following ones green 
// cols<0   means: Standard palette.
void TopSVDFunctions::SVD_DrawStack(THStack* stack, TString xTitle, TString yTitle, TString options, int col)
{
     SVD_DrawStackRange(stack, xTitle, yTitle, 1., -1., options, col);
}


// Formats a Stack of Histos to the current style
// The last argument takes integers between 1 and 9 for the colors, i.e.
// cols=0   means: Do not touch the colors!
// cols=243 means: First Histogram red, second blue, and third and all following ones green 
// cols<0   means: Standard palette.
// If ymax < ymin, the range will be calculated automatically  
void TopSVDFunctions::SVD_DrawStackRange(THStack* stack, TString xTitle, TString yTitle, double ymin, double ymax, TString options, int col)
{ 
    // Colors 
    bool useStandardPalette = false;
    bool useUserPalette = false;
    bool useOldColors = false;
    int* theColors = NULL; 
    int numdigits = 1;
    if ( col > 0 ) { 
        useUserPalette = true;
         
        // Create an array of colors 
        int colstmp1 = col;
        while ( (colstmp1=colstmp1/10)>0 ) { numdigits++; }
        theColors = new int[numdigits];
        
         
        // Save colors in that array
        int colstmp2 = col;
        for ( int i = 0 ; i < numdigits ; i++ ) { 
            int position = numdigits-1-i;
            int lastdigit = colstmp2 % 10;
            theColors[position] = lastdigit;
            colstmp2=colstmp2/10; 
        }
    } else if ( col < 0 ) { 
        useStandardPalette = true;
    } else {
        useOldColors = true;
    }
  
 
    // Range Issues
    bool doSetRange = false;
    if ( ymax > ymin ) doSetRange = true;
  
  
    // Loop over all histos
    // Set Colors and make cosmetic changes 
    TH1D* histo = NULL;
    int cnt = 0;
    TList* listHistos = stack->GetHists();
    TListIter iter(listHistos);
    while ( (histo = (TH1D*) iter.Next()) != NULL ) {
        
        // Hide Unwanted Values 
        if ( doSetRange == true ) {
            for ( int i = 0; i < histo->GetNbinsX()+2; i++) {
                 double val = histo->GetBinContent(i);
                 if ( val > ymax || val < ymin ) {
                    histo->SetBinContent(i, 2*ymin - ymax);
                    histo->SetBinError(i, 0.);
                }
            }
        }
        
        // Set Color
        int currentcolor = 0;
        if ( useStandardPalette == true ) currentcolor = cnt+1;
        if ( useUserPalette == true ) currentcolor = theColors[cnt];
        if ( useOldColors == true ) currentcolor = histo->GetMarkerColor(); 
        histo->UseCurrentStyle();  
         histo->SetLineColor(currentcolor);
         histo->SetMarkerColor(currentcolor); 
        cnt++;
    } 
  

    // Draw it
    options.Append("nostack");
    stack->Draw(options);

    // Style
    stack->GetHistogram()->UseCurrentStyle();

    // Titles
    stack->GetHistogram()->GetXaxis()->SetTitle(xTitle);
    stack->GetHistogram()->GetYaxis()->SetTitle(yTitle);

    // Y Range
    if ( doSetRange == false ) {
        double yMin = stack->GetHistogram()->GetMinimum();
        double yMax = stack->GetHistogram()->GetMaximum();
        double yRange = yMax-yMin;
        double yUpperMargin = 0.3*yRange;
        double yLowerMargin = 0.;
        if ( yMin < 0. ) {
            yLowerMargin = 0.05*yRange;
        } 
        stack->SetMaximum(yMax+yUpperMargin);
        stack->SetMinimum(yMin-yLowerMargin);
    } else { 
        double yMin = ymin;
        double yMax = ymax;
        //double yRange = yMax - yMin;
        double yUpperMargin = 0.;
        double yLowerMargin = 0.; 
        stack->SetMaximum(yMax+yUpperMargin);
        stack->SetMinimum(yMin-yLowerMargin); 
    } 

}



// Set Name, Title and Axis Titles
// note: The Title is set to the value of name
void TopSVDFunctions::SVD_SetTitles1D(TH1D* histo, TString name, TString xTitle, TString yTitle, int numHist)
{
    if ( histo == NULL ) return; 
    
    // Loop over all histograms in the array
    for ( int h = 0 ; h < numHist ; h++ ) {  
        (histo+h)->SetName(name);
        (histo+h)->SetTitle(name); 
        (histo+h)->GetXaxis()->SetTitle(xTitle);
        (histo+h)->GetYaxis()->SetTitle(yTitle);
    }
}




// Set Name, Title and Axis Titles
// note: The Title is set to the value of name
void TopSVDFunctions::SVD_SetTitles2D(TH2D* histo, TString name, TString xTitle, TString yTitle, TString zTitle, int numHist)
{
    if ( histo == NULL ) return;
    
    // Loop over all histograms in the array
    for ( int h = 0 ; h < numHist ; h++ ) { 
        (histo+h)->SetName(name);
        (histo+h)->SetTitle(name);
        (histo+h)->GetXaxis()->SetTitle(xTitle);
        (histo+h)->GetYaxis()->SetTitle(yTitle);
        (histo+h)->GetZaxis()->SetTitle(zTitle);
    }
}
 


// Calculate ChiSquare between Data and Refolded Distribution
// Note: The side bins on rec level will NOT be considered!
// Empty bins will also NOT be considered!
double TopSVDFunctions::SVD_Chi2A(TH1D* dataHist, TH1D* refoldHist)
{
    double chi2a = 0.;
    for ( int i = 1 ; i <= dataHist->GetNbinsX(); i++) {
        double dataValue = dataHist->GetBinContent(i);
        double refoldedValue = refoldHist->GetBinContent(i);
        double dataErrorSquared = dataHist->GetBinContent(i);
        if ( dataValue <= 0. ) continue;
        double current = (dataValue - refoldedValue) * (dataValue - refoldedValue) / dataErrorSquared;
        chi2a += current;
    }
    return chi2a;
}

 


// Calculate the non-empty and non-side rec level bins
int TopSVDFunctions::SVD_GoodRecBins(TH1D* dataHist)
{
    int numbins = 0;
    for ( int i = 1 ; i <= dataHist->GetNbinsX(); i++) {
        double dataValue = dataHist->GetBinContent(i);
        if ( dataValue <= 0. ) continue;
        numbins++;
    }
    
    return numbins;
}




// Calculate the non-empty and gen level bins
int TopSVDFunctions::SVD_GoodGenBins(TH1D* xiniHist)
{
    int numbins = 0;
    for ( int i = 1 ; i <= xiniHist->GetNbinsX(); i++) {
        double xiniValue = xiniHist->GetBinContent(i);
        if ( xiniValue <= 0. ) continue;
        numbins++;
    }

    return numbins;
}



// Calculate NDOF
int TopSVDFunctions::SVD_Ndof(TH1D* dataHist, TH1D* xiniHist)
{
    int ndof = SVD_GoodRecBins(dataHist) - SVD_GoodGenBins(xiniHist);
    return ndof;
}



// Tau Scan
// Calculate Scan Points
TVectorD* TopSVDFunctions::SVD_CalcScanPoints(double firstTau, double lastTau, int nScanPoints)
{
    
    // Use 3 scan points minimum
    if ( nScanPoints < 3 ) nScanPoints = 3;
    
    // Setup Vector 
    TVectorD* vScanPoints = new TVectorD(nScanPoints);
    
    // Find the scan points
    // Use equidistant steps on a logarithmic scale
    double steplog = (TMath::Log10(lastTau) - TMath::Log10(firstTau)) / ((double) (nScanPoints-1));
    for ( int i = 0 ; i < nScanPoints ; i++ ) {
        double posScanPoint = TMath::Power(10., (TMath::Log10(firstTau) + ((double) i) * steplog));
        (*vScanPoints)[i] = posScanPoint;
    }
    
    return vScanPoints;
}

// Tau Scan
// Scan Global Correlation    
double TopSVDFunctions::SVD_ScanGlobalCorrelation(TH2D* statCovHist)
{  
  
    // Calculate Global Correlation in all bins
    TH1D* globCorrHist = SVD_CalcGlobCorr(statCovHist);
    
    // Averaged Global Correlation
    double globcorr = SVD_AvgGlobCorr(globCorrHist); 
     
    // Delete old objects 
    delete globCorrHist; 
    
    // return value 
    return globcorr;
    
}

// Tau Scan
// Scan Chi Squared
double TopSVDFunctions::SVD_ScanChiSquared(TH1D* weightHist, TH1D* dataHist, TH2D* mcHist)
{ 
 
    // Refold it 
    TH1D* refoldHist = SVD_Refold(weightHist, NULL, mcHist, true);  
    
    // Calculate Chi2A
    double chisq = SVD_Chi2A(dataHist, refoldHist);
    
    // Delete old objects
    delete refoldHist; 
     
    // Return
    return chisq;
    
}


// Tau Scan
// Scan Curvature
double TopSVDFunctions::SVD_ScanCurvature(double curv)
{  
 
    // return vector
    return curv;
     
}

// This is a crude thing.
// It calculates the statistical uncertainty of the
// unfolding result, averaged over all bins except
// empty bins and side bins 
double TopSVDFunctions::SVD_ScanAvgSqErr(TH2D* covMatrix)
{
    // nbins
    int nbins = covMatrix->GetNbinsX(); 
    
    // Loop
    double sumSquaredErrors = 0.;
    int numRealBins = 0;
    
    // Recall: You have two sets of OF bins!
    for ( int i = 2 ; i < nbins ; i++ ) {
        
        // Get trace element of covariance Matrix
        double binContent = covMatrix->GetBinContent(i,i);
        
        // Do not count this bin if it is empty
        if ( binContent == 0. ) continue;
        
        sumSquaredErrors += binContent;
        numRealBins++;
    }
    
    // Average
    double avgSqErr = sumSquaredErrors / ((double) numRealBins );
    
    // Take Square Root
    avgSqErr = TMath::Sqrt(avgSqErr);
    
    // Return
    return avgSqErr;
} 


// This is a crude thing.
// It calculates the mean value of the
// unfolding result, averaged over all bins except
// empty bins and side bins
double TopSVDFunctions::SVD_ScanAvgMean(TH1D* unfHist)
{
    
    // nbins
    int nbins = unfHist->GetNbinsX(); 
    
    // Loop
    double sumElements = 0.;
    int numRealBins = 0;
    
    // Recall: You have two sets of OF bins!
    for ( int i = 2 ; i < nbins ; i++ ) {
        
        // Get trace element of covariance Matrix
        double binContent = unfHist->GetBinContent(i);
        
        // Do not count this bin if it is empty
        if ( binContent == 0. ) continue;
        
        sumElements += binContent;
        numRealBins++;
    }
    
    // Average
    double avgMean =  sumElements / ((double) numRealBins );
    return avgMean; 
    
}

// Helper Function
// If you have a range you want to depict in a histogram,
// than this function gives you a good range 
void TopSVDFunctions::SVD_NewRange(double min, double max, double& newmin, double& newmax, bool log)
{
    // Set Min and Max Values
    double theMin = min;
    double theMax = max;
    if ( log == true ) {
        if ( min > 0 ) theMin = TMath::Log10(min);
        if ( max > 0 ) theMax = TMath::Log10(max);
    }
    
    // Get margin
    double margin = 0.15*(theMax - theMin);
    
    // New Min and Max
    double theNewMin = theMin - margin;
    double theNewMax = theMax + margin;
    
    
    // Return
    newmin = theNewMin;
    newmax = theNewMax;
    if ( log == true ) {
        newmin = TMath::Power(10., theNewMin);
        newmax = TMath::Power(10., theNewMax);
    }
    
    
}
    
// Helper Function
// If you have a range you want to depict in a histogram,
// than this function gives you a good range 
void TopSVDFunctions::SVD_NewUpperRange(double max, double& newmax)
{
    // Set Min and Max Values
    double theMin = 0.;
    double theMax = max; 
    
    // Get margin
    double margin = 0.3*(theMax - theMin);
    
    // New Min and Max 
    double theNewMax = theMax + margin;
    
     
    // Return 
    newmax = theNewMax;  
    
}
    
    

// GLOBAL CORRELATION
// Attention: 
// (1) We do not use the side bins for the computation
//     of the global correlation !!!
// (2) We also exclude all bins that ...
// (3) For excluded bins, the global correlation
//     will be set to zero.
TH1D* TopSVDFunctions::SVD_CalcGlobCorr(TH2D* statCovHist)
{
    // Number of bins
    int nbins = statCovHist->GetNbinsX();
    
    // New Matrix
    // Beware the side bins of the problem
    // AND the side bins of the TH2D object
    TMatrixDSym statCovMat(nbins-2);
    for ( int i = 1; i <= nbins ; i++ ) {
        for ( int j = 1; j <= nbins ; j++ ) {
            double value = statCovHist->GetBinContent(i,j);
            // Skip Side bins
            bool skipThis = false;
            if ( i == 1 || i == nbins ) skipThis = true;
            if ( j == 1 || j == nbins ) skipThis = true;
            // Set Element
            if ( skipThis == false ) statCovMat[i-2][j-2] = value;
        }
    }
    
    // Determinant
    double detStatCovMat[1]; 
    
    // Invert the whole thing
    TMatrixDSym statCovMatInv = statCovMat;
    statCovMatInv.Invert(detStatCovMat);
    
    // Histo for global correlation
    const TArrayD* xbins = statCovHist->GetXaxis()->GetXbins();
    TH1D* glcHist = new TH1D("glcHist", "glcHist", nbins, xbins->GetArray());
    for ( int i = 1 ; i <= nbins ; i++ ) { 
        double glc = 0.; 
        // Skip Side bins
        bool skipThis = false;
        if ( i == 1 || i == nbins ) skipThis = true;
        if (  (*detStatCovMat) != 0. )  {
            if ( skipThis == false ) {
                double cov = statCovMat[i-2][i-2]; 
                double covinv = statCovMatInv[i-2][i-2]; 
                // The product cov*covinv should be greater than zero            
                double hhh = SVD_Divide(1., cov * covinv);
                double glcsq = 0.;
                if ( hhh > 0.) glcsq = 1. - hhh;
                glc = 100.*SVD_Sqrt(glcsq); 
            } else {
                glc = 0.;
            }
        } else {
            cout << "WARNING!" << endl;
            cout << "Could not calculate global correlation" << endl;
            cout << "in Bin: " << i << endl;
            cout << "Reason: Statistical Covariance Matrix is singular." << endl;
        }
        glcHist->SetBinContent(i, glc); 
        glcHist->SetBinError(i, 0.); 
    }
    
    // return histo
    return glcHist;
}
 
// Calculate Averaged Global Correlation
double TopSVDFunctions::SVD_AvgGlobCorr(TH1D* globCorrHist)
{
    // Number of binsTLine* line = 
    int nbins = globCorrHist->GetNbinsX();
    
    double sumSquared = 0.;
    double avgSquared = 0.;
    int bincounter = 0;
    
    // Do not use the side bins!
    for ( int i = 1; i <= nbins; i++ ) {
        if ( i == 1 ) continue;
        if ( i == nbins ) continue;
        sumSquared += globCorrHist->GetBinContent(i+1);
        bincounter++;
    }
    
    // Averaging
    if ( bincounter > 0 ) {
        avgSquared = sumSquared / ((double) bincounter);
    }
    
    return avgSquared;
    
}


// Find minimum of a graph, given as two vectors.
// The coordinates of the minimum are returned in xBest and yBest
// The position in the vectors is returned as an integer.
int TopSVDFunctions::SVD_FindMinimum(TVectorD* xVec, TVectorD* yVec, double& xBest, double& yBest)
{
    //Test, if vectorX and vectorY have same number of entries
    int nelements = xVec->GetNoElements();
    int nelementsY = yVec->GetNoElements();
    if ( nelements <= 0 || nelementsY <= 0 || nelements != nelementsY ) {
        cout << "Error in TopSVDFunctions::SVD_FindMinimum()" << endl;
        cout << "   The two vectors have strange sizes." << endl;
        cout << "   xVec has " << nelements  << " entries." << endl;
        cout << "   yVec has " << nelementsY << " entries." << endl;
        cout << "Exiting ... " << endl;
        exit(1);
    }
    
     
    // Find smallest value
    double minYValue = FLT_MAX;
    double minXValue = 0.;
    int minPosition = -1; 
    for ( int i = 0 ; i < nelements ; i++ ) {
        double yvalue = (*yVec)[i];
        double xvalue = (*xVec)[i];
        if ( yvalue < minYValue ) {
            minYValue = yvalue;
            minXValue = xvalue;
            minPosition = i;
        }
    }
    
    
    // Return it all
    xBest = minXValue;
    yBest = minYValue;
    return minPosition;
    
}


// Helper Function
// Adds histos from an array to a legend
void TopSVDFunctions::SVD_Array2Legend(TLegend* leg, TH1D* histo, TString string, TString option, int numHist)
{  
	// Important
	if ( histo == NULL ) return;
    if ( numHist <= 0 ) return; 
	
	
    // String
    TString theString = string;
    
    // Add the Entry to the legend, use first histo
    TString theOption = option;
    if ( theOption.CompareTo("") == 0 ) theOption = "lpf";
    leg->AddEntry(histo, theString, theOption);
    
}


// Helper Function
// Adds histos from an array to a stack
// Color Handling:
//      col=0   means: The colors will not be touched
//         col=2   means: All histos get the color 2
//      col=243 means: First Histogram red, second blue, third and all following ones green 
void TopSVDFunctions::SVD_Array2Stack(THStack* stack, TH1D* histo, TString options, int col, int numHist)
{ 
	// Important
	if ( histo == NULL ) return;
    if ( numHist <= 0 ) return; 
	
    // Colors
    bool doColors = false;
    int* theColors = NULL; 
    int numdigits = 1;
    if ( col > 0 ) {
        doColors = true;
         
        // Create an array of colors 
        int colstmp1 = col;
        while ( (colstmp1=colstmp1/10)>0 ) { numdigits++; }
        theColors = new int[numdigits];
        
         
        // Save colors in that array
        int colstmp2 = col;
        for ( int i = 0 ; i < numdigits ; i++ ) { 
            int position = numdigits-1-i;
            int lastdigit = colstmp2 % 10;
            theColors[position] = lastdigit;
            colstmp2=colstmp2/10; 
        }
    }
    
    
    
    // Loop over all histograms in the array 
    for ( int h = 0 ; h < numHist ; h++ ) {
        
        // Set Colors
        if ( doColors == true ) {
            int position = h;
            if ( position > numdigits-1 ) position = numdigits-1;
            int currentcolor = theColors[position];
            
            (histo+h)->SetLineColor(currentcolor);
            (histo+h)->SetMarkerColor(currentcolor); 
            
        }
         
        // Draw Options
        TString theOptions = options;
        if ( numHist > 1 ) {
            theOptions.Append(" HIST");
        }
        
        // Append it to stack
        if ( h == 0 ) { 
            stack->Add(histo+h, theOptions);
        } else {
            stack->Add(histo+h, "HIST");
        }
        
         
    } 
    
}


// Helper Function
// Adds histos from an array to a stack
void TopSVDFunctions::SVD_ArrayScale(TH1D* histo, double scale, int numHist)
{ 
    // Loop over all histograms in the array 
    for ( int h = 0 ; h < numHist ; h++ ) { 
        (histo+h)->Scale(scale);
    } 
    
}
 


// REFOLDING - without Background
// Two possibilities:
// If useWeights==false (Standard)
//     Divide "unfHist" by "xiniHist", then refold with event matrix "mcHist". 
//     ATTENTION: If there are no generated events in a generator bin, then
//     the division by "xini" doesnt work. But there is a way out:
//     In such a case, the whole column of the event matrix will be empty! 
//     Multiplication of x/xini with the event matrix will give zero.
//     This justifies, that those bins can just be skipped in the sum!
//     However: If the column of the event matrix is not empty for some
//     reason, than something is odd and you have to check this.
//     Overflow bins: Remember, all side bins are in regular binning.
//     Indexing: i=Rec=(xAxis in mcHist), j=Gen=(yAxis in mcHist)
// If useWeights==true
//     "unfHist" is taken to be the ratio between unfolded data and generated distribution,
//     which means "unfHist" is directly refolded with event matrix "mcHist". 
//     "xiniHist" will not be used, can be set to NULL if you wish.
// Attention: A new histogram ist created on the heap
TH1D* TopSVDFunctions::SVD_Refold(TH1D* unfHist, TH1D* xiniHist, TH2D* mcHist, bool useWeights, int numHist) 
{
 
    // Create new Histograms
    TH1D* refoldHist = SVD_CloneHists1D(unfHist, numHist);
    int nbins = unfHist->GetNbinsX(); 
 
    // Loop over all histograms in the array 
    for ( int h = 0 ; h < numHist ; h++ ) {  
        
        // Important Check:
        // Make sure that generator level bins
        // with empty xiniHist-bins
        // have also empty mcHist-rows
        // GenLevelIndex=j, DetLevelIndex=i
        if ( useWeights == false ) {
            for ( int j = 1 ; j <= nbins ; j++ ) {
                double numerator = (xiniHist+h)->GetBinContent(j);
                if ( numerator > 0. ) continue; 
                bool doWarning = true;
                for ( int i = 1 ; i <= nbins ; i++ ) {  
                    double matrixelement = (mcHist+h)->GetBinContent(i,j); 
                    if ( matrixelement == 0. ) continue; 
                    if ( doWarning == true ) {
                        cout << endl;
                        cout << "******************************************************************" << endl;
                        cout << "WARNING! WARNING! WARNING! " << endl;
                        cout << "Severe problem in TopSVDFunctions::SVD_Refold() !!!" << endl;
                        cout << "For the generator level bin " << j << " ... " << endl;
                        cout << "    ... xiniHist is empty ... " << endl;
                        cout << "    ... but in the response matrix there are non-empty elements." << endl;
                        cout << "Unfolding might work, but refolding won't !!!" << endl;
                        cout << "This means, your chi square will be busted and no one will believe " <<  endl;
                        cout << "your results !!!" << endl;
                        cout << "******************************************************************" << endl;
                        cout << endl; 
                        doWarning = false;
                    }
                }
            }
        }      
        
        // Run over all bins
        // GenLevelIndex=j, DetLevelIndex=i 
        for ( int i = 1 ; i <= nbins ; i++ ) { 
            double refoldedvalue = 0.; 
            for ( int j = 1 ; j <= nbins ; j++ ) { 
                double xini = 1.;
                if ( useWeights == false ) {
                    xini = (xiniHist+h)->GetBinContent(j);
                }
                double unf = (unfHist+h)->GetBinContent(j); 
                double matrixelement = (mcHist+h)->GetBinContent(i,j); 
                double current = 0.; 
                if ( xini > 0. ) {  
                    current = matrixelement * ( unf / xini );
                } else {
                    current = 0.;
                }
                refoldedvalue += current;
            }
            (refoldHist+h)->SetBinContent(i, refoldedvalue);
            (refoldHist+h)->SetBinError(i, 0.);
        }
    }
     
    // Return the histogram
    return refoldHist;

}

// Calculate global lumi scale factor from reconstructed
// distributions. Exclude overflow bins! Use background free
// data distribution!
double TopSVDFunctions::SVD_LumiScaleFactor(TH1D* dataHist, TH1D* recHist)
{
    int nbins = dataHist->GetNbinsX();
    double sumData = 0.;
    double sumMC = 0.;
    
    for ( int i = 1 ; i <= nbins ; i++ ) {
        sumData = sumData + dataHist->GetBinContent(i);
        sumMC = sumMC + recHist->GetBinContent(i);
    }
    
    if ( sumMC <= 0. ) return 1.;
    if ( sumData <= 0. ) return 1.;
    
    double scalefactor = sumData / sumMC ;
    return scalefactor;
    
}

// Find bin number on an axis
// You give a bin boundary 'bnd' and this function gives
// you the number of the bin that STARTS at 'bnd'
int TopSVDFunctions::SVD_FindBin(TAxis* axis, double bnd)
{
    // First attempt to find bin number
    int binnr = axis->FindBin(bnd);
    
    // Possibly, the binnr is by 1 too low.
    // This can happen due to rounding errors
    // busting the comparison between 'bnd' and the
    // bin boundaries of the axis.
    // To make sure that we found the right bin,
    // we check which bin boundary is actually closer.
    double lowxFirstTry  = axis->GetBinLowEdge(binnr);
    double lowxStepUp    = axis->GetBinLowEdge(binnr+1);
    double distanceFirstTry = TMath::Abs(bnd - lowxFirstTry);
    double distanceStepUp = TMath::Abs(bnd - lowxStepUp);
    if ( distanceStepUp < distanceFirstTry ) binnr++;
    
    // Return
    return binnr;
     
    
}


// Setup Unfolding Tool
// This creates an array of TopSVDUnfold objects on the heap.
// Each of them is set up with a different systematic
// All other settings will be the same.
TopSVDUnfold* TopSVDFunctions::SVD_SetupTool(TH1D* dataHist, TH1D* biniHist, TH1D* xiniHist, TH2D* mcHist, double theTau, int numHist)
{
    TopSVDUnfold* mySVDUnfold = new TopSVDUnfold[numHist];
    
    // Loop over all histograms
    for ( int h = 0 ; h < numHist ; h++ ) { 
        
        // Create Unfolding Tool
        TopSVDUnfold tmpTool(dataHist+h, biniHist+h, xiniHist+h, mcHist+h); 
        *(mySVDUnfold+h) = tmpTool; 
        
        // Setup
        (mySVDUnfold+h)->SetNormalize(false); 
        (mySVDUnfold+h)->SetTau(theTau);
        
    }
    
    // Return
    return mySVDUnfold;
}


// Call TopSVDUnfold sequentially
// Creates new objects on the heap!
TH1D* TopSVDFunctions::SVD_CallSVDUnfolding(TopSVDUnfold* mySVDUnfold, int theKReg, int numHist)
{ 
    // Create new histograms
    TH1D* unfHist = new TH1D[numHist]; 
    // Loop over all histograms
    for ( int h = 0 ; h < numHist ; h++ ) { 
        TH1D* tmpHist = (mySVDUnfold+h)->Unfold(theKReg); 
        tmpHist->Copy(*(unfHist+h)); 
        (unfHist+h)->SetName("unfHist"); 
    } 
    
    return unfHist;
}


// Retrieve Weights
// Creates new objects on the heap! 
TH1D* TopSVDFunctions::SVD_RetrieveWeights(TopSVDUnfold* mySVDUnfold, int numHist)
{ 
    // Create new histograms
    TH1D* weightHist = new TH1D[numHist];
    
    // Loop over all histograms
    for ( int h = 0 ; h < numHist ; h++ ) { 
        TH1D* tmpHist = (mySVDUnfold+h)->GetWeights();
        tmpHist->Copy(*(weightHist+h));
        (weightHist+h)->SetName("weightHist");
    } 
    
    return weightHist;
}


// Retrieve D Value Plot
// Creates new objects on the heap! 
TH1D* TopSVDFunctions::SVD_RetrieveDD(TopSVDUnfold* mySVDUnfold, int numHist)
{ 
    // Create new histograms
    TH1D* ddHist = new TH1D[numHist];
    
    // Loop over all histograms
    for ( int h = 0 ; h < numHist ; h++ ) { 
        TH1D* tmpHist = (mySVDUnfold+h)->GetD();
        tmpHist->Copy(*(ddHist+h));
        (ddHist+h)->SetName("ddHist");
    } 
    
    return ddHist;
}


// Retrieve Singular Values
// Creates new objects on the heap! 
TH1D* TopSVDFunctions::SVD_RetrieveSV(TopSVDUnfold* mySVDUnfold, int numHist)
{ 
    // Create new histograms
    TH1D* svHist = new TH1D[numHist];
    
    // Loop over all histograms
    for ( int h = 0 ; h < numHist ; h++ ) { 
        TH1D* tmpHist = (mySVDUnfold+h)->GetSV();
        tmpHist->Copy(*(svHist+h));
        (svHist+h)->SetName("svHist");
    } 
    
    return svHist;
}


// Take an array of systematics
// and make relative shifts in % out of it
// NOTE: The output array will have one histogram LESS!
TH1D* TopSVDFunctions::SVD_ArrayToShifts(TH1D* array, int numHist)
{
    if ( numHist <= 1 ) return NULL;
    
    // Create new histograms
    // ... one less 
    TH1D* output = new TH1D[numHist-1];
    
    // Loop over all histograms
    // ... exclude the first
    for ( int h = 1 ; h < numHist ; h++ ) { 
        
        // Substract the nominal values
        TH1D* absDiv = (TH1D*) (array+h)->Clone("tmp");
        absDiv->Add(array, -1.);
        
        
        // Division by nominal values
        TH1D* relDiv = SVD_MakeRatioZero(absDiv, array, 1);
        
        // Scale to percent values
        relDiv->Scale(100.);
        
        // Save it in new array
        *(output-1+h) = *relDiv;
        
        
        
    }
    
    return output;
    
}

// BACKGROUND HANDLING
// The raw data are given plus the simulated
// backgrounds from MC. The result is returned in
// the placeholder parameter 'dataHist'.
// Notice:
// (1) Errors from background will be neglected! 
// (2) If 'ttbgrInputHist' is given, it will be removed by
//     a multiplicative approach that is xSec independent!   
// (3) If 'bgrInputHist' is given, it will be removed from the
//     data by substraction.
// (4) If both 'bgrInputHist' and 'ttbgrInputHist' are given,
//     the difference between 'bgrInputHist' and 'ttbgrInputHist'
//     will be substracted from the data and the background given
//     int 'ttbgrInputHist' will be treated as described in (2).
// (5) If neither 'bgrInputHist' nor 'ttbgrInputHist' are given,
//     no background will be considered.
void TopSVDFunctions::SVD_BackgrHandling(TH1D*& dataHist, TH1D* bgrHist, TH1D* ttbgrHist, TH1D* biniHist, TH1D* rawHist, int numHist)
{
    int verbose = 0; 
    

    // Steer background handling
    bool doBgr = false;
    if ( bgrHist != NULL ) doBgr = true;
    bool doTtBgr = false;
    if ( ttbgrHist != NULL ) doTtBgr = true;
    
    // Nbins
    int nbins = dataHist->GetNbinsX();
    
    // Loop over all histograms
    for ( int h = 0 ; h < numHist ; h++ ) {
         
        // loop bins
        for ( int i = 0 ; i < nbins + 1 ; i++) { 

            // get bin and errors for data
            // Notice: Only ONE histogram will be used here!
            double value_data = rawHist->GetBinContent(i);
            double err_data = rawHist->GetBinError(i);  
            // Get background value to be substracted! 
            double value_bgr = 0.; 
            if ( doBgr == true )  value_bgr = (bgrHist+h)->GetBinContent(i);  
            if(value_data<value_bgr){
                std::cout << "ERROR in TopSVDFunctions::SVD_BackgrHandling: " << std::endl;
                std::cout << "N_MC BG > N_data for plot " << rawHist->GetName() << std::endl;
		std::cout << "in bin " << i << " (range " << rawHist->GetBinLowEdge(i) << "," << rawHist->GetBinLowEdge(i+1) << " )" << std::endl;
                std::cout << "(" << value_bgr << ">" << value_data << ")" << std::endl;
                exit(0);
            }
                 
            // Debug output
            if(verbose>=2){
                std::cout << std::endl << "bin " << i << std::endl;
                std::cout << "value_data: " << value_data << std::endl;
                std::cout << "value_bgr: "  << value_bgr << std::endl;
                std::cout << "err_data: "   << err_data << std::endl;
            }
                 
            
            // Get background scale factor!
            double sigFrac = 1.;
            if ( doTtBgr == true ) {
                double value_ttSig=(biniHist+h)->GetBinContent(i);
                double value_ttBgr=(ttbgrHist+h)->GetBinContent(i); 
                if(value_ttBgr>value_bgr){
                    std::cout << "ERROR in TopSVDFunctions::SVD_BackgrHandling: " << std::endl;
                    std::cout << "N_{MC ttbar BG} > N_{MC all BG} in bin " << i << std::endl;
                    std::cout << "(" << value_ttBgr << ">" << value_bgr << ")" << std::endl;
                    exit(0);
                }  
                
                // don't subtract ttbar BG !!!!!!!
                value_bgr-=value_ttBgr;
                
                // calculate signal fraction
                sigFrac=value_ttSig/(value_ttSig+value_ttBgr);
                  
                // debug output
                if(verbose>=2){
                    std::cout << "value_ttBgr: " << value_ttBgr << std::endl;
                    std::cout << "value_bgr(no ttbar): " << value_bgr << std::endl;
                    std::cout << "value_ttSig: " << value_ttSig << std::endl;
                    std::cout << "sigFrac: " << sigFrac << std::endl;
                } 
            
            }
                
            // New Values
            double value_new = (value_data - value_bgr)*sigFrac;
            double err_new = err_data*sigFrac; 
             
              
            // debug output
            if(verbose>=2){
                std::cout << "data_value_new: " << value_new << std::endl;
                std::cout << "data_err_new: "   << err_new   << std::endl;
            }
              
            // Save new values
            (dataHist+h)->SetBinContent(i, value_new);
            (dataHist+h)->SetBinError(i, err_new); 
              
        }
    }   
}   
    
    
// Calculate Purity
// Will be stored in 'purHist'
// Note:
// (1) Purity is set to zero, if number of reconstructed
//     events in a bin is zero
void TopSVDFunctions::SVD_Pur(TH1D*& purHist, TH2D* mcHist,int numHist)
{ 
    // Nbins
    int nbins = mcHist->GetNbinsX();
    
    // Loop over all histograms
    for ( int h = 0 ; h < numHist ; h++ ) {
        
        // Loop over all bins
        for ( int i = 1 ; i <= nbins ; i++ ) {
            double numerator = (mcHist+h)->GetBinContent(i, i);
    
            // Sum over all Gen Level bins INCLUDING OF bins
            double denominator = 0.;
            for ( int j = 1 ; j < nbins+1 ; j++ ) {
                denominator += (mcHist+h)->GetBinContent(i, j);
            }
    
            //double denominator = biniHist->GetBinContent(i);
            double purity = SVD_Divide(numerator, denominator);
            (purHist+h)->SetBinContent(i,purity);
            (purHist+h)->SetBinError(i, 0.); 
        }
    }
}
    
    
    
    
// Calculate Stability
// Will be stored in 'stabHist'
// Note: 
// (1) Stability is set to zero, if there are no
//     gerenated events in a bin
// (2) If there is no reconstructed event in this bin,
//     then the stability is naturally zero, too
void TopSVDFunctions::SVD_Stab(TH1D*& stabHist, TH2D* mcHist, int numHist)
{
    // Nbins
    int nbins = mcHist->GetNbinsX();
    
    // Loop over all histograms
    for ( int h = 0 ; h < numHist ; h++ ) {
        
        // Loop over all bins
        for ( int i = 1 ; i <= nbins ; i++ ) {
            double numerator = (mcHist+h)->GetBinContent(i, i);
    
            // Sum over all Rec Level bins EXCEPT OF bins
            double denominator = 0.;
            for ( int j = 1 ; j < nbins+1 ; j++ ) {
                if ( j == 1 ) continue;
                if ( j == nbins ) continue;
                denominator += (mcHist+h)->GetBinContent(j, i);
            }
    
            //double denominator = xiniHist->GetBinContent(i);
            double stability = SVD_Divide(numerator, denominator);
            (stabHist+h)->SetBinContent(i,stability);
            (stabHist+h)->SetBinError(i, 0.);
        }
    }
}


// Calculate Real Efficiency    
// Will be stored in 'effHist'
// Attention:
// (1) If no generated events are available in a bin,
//     then the efficiency is set to zero.
// (2) Statistical Errors are calculated in a binomial manner.
//     This is different from bbb Efficiency.
void TopSVDFunctions::SVD_Eff(TH1D*& effHist, TH2D* mcHist, TH1D* xiniHist, int numHist)
{
    // Nbins
    int nbins = mcHist->GetNbinsX(); 
    
    // Loop over all histograms
    for ( int h = 0 ; h < numHist ; h++ ) {
        
        // Loop over all bins
        for ( int i = 1 ; i <= nbins ; i++ ) {
            
            double denominator = (xiniHist+h)->GetBinContent(i);
            double numerator = 0.;
            for ( int j = 1; j <= nbins ; j++ ) {
                // Sum over all Rec Level Bins EXEPT OF bins!
                // So Please, please, please do not forget to exclude
                // the side bins
                // Note: Rec Level bins are on x axis of mcHist
                double elem = (mcHist+h)->GetBinContent(j, i);
                if ( j == 1 ) elem = 0.;
                if ( j == nbins ) elem = 0.;
                numerator += elem;
            }
            double efficiency = SVD_Divide(numerator,denominator);
            double effErr = SVD_BinomialError(numerator, denominator);
            (effHist+h)->SetBinContent(i,efficiency);
            (effHist+h)->SetBinError(i, effErr);
        } 
    }
}


// Calculate BBB Efficiency    
// Will be stored in 'beffHist'
// Attention:
//     For the statistical uncertainty, relative errors from 
//     reconstructed and generated events counts are added in quadrature.
//     This is different from the errors on the real efficiency,
void TopSVDFunctions::SVD_BBBEff(TH1D*& beffHist, TH1D* biniHist, TH1D* xiniHist, int numHist)
{
    
    // Nbins
    int nbins = biniHist->GetNbinsX(); 
    
    // Loop over all histograms
    for ( int h = 0 ; h < numHist ; h++ ) {
        
        // Loop over all bins
        for ( int i = 1 ; i < nbins+1 ; i++ ) {
              
            // Sum over all Gen Level bins Including OF bins
            double numerator = (biniHist+h)->GetBinContent(i);  
            double numeratorErr = (biniHist+h)->GetBinError(i);
            double denominator = (xiniHist+h)->GetBinContent(i); 
            double denominatorErr = (xiniHist+h)->GetBinError(i);
            double bbbeff = 0.;
            double bbbeffErr = 0.;
            if ( denominator > 0. && numerator > 0.) {
                bbbeff = numerator / denominator;
                double bbbeffErrRelSq = 0.;
                bbbeffErrRelSq += TMath::Power(numeratorErr/numerator, 2.);
                bbbeffErrRelSq += TMath::Power(denominatorErr/denominator, 2.);
                bbbeffErr = bbbeff * TMath::Sqrt(bbbeffErrRelSq);
            }
            (beffHist+h)->SetBinContent(i,bbbeff);
            (beffHist+h)->SetBinError(i,bbbeffErr);
             
        }
    }
}


// Do BBB Unfolding 
// Output stored in 'bbbHist'
// ATTENTION:
// (1) Use BBB Efficiency.
// (2) Although this might be tempting,
//     do not include the error from the efficiency.
//     This would bust your BBB / SVD comparison.
//     Instead, add the error on the efficiency
//     later on as a systematic MC uncertainty! 
void TopSVDFunctions::SVD_BBBUnf(TH1D*& bbbHist, TH1D* dataHist, TH1D* beffHist, int numHist)
{
    
    // Nbins
    int nbins = beffHist->GetNbinsX(); 
    
    // Loop over all histograms
    for ( int h = 0 ; h < numHist ; h++ ) {
        
        // Loop over all bins  
        for ( int i = 1 ; i <= nbins ; i++ ) {
            double data = (dataHist+h)->GetBinContent(i);
            double bbbeff  = (beffHist+h)->GetBinContent(i);
            double dataErr = (dataHist+h)->GetBinError(i);
            double bbbunf = 0.;
            double bbbunfErr = 0.;
            if ( data > 0. && bbbeff > 0.) {
                bbbunf = data / bbbeff;
                bbbunfErr = dataErr / bbbeff;
            }
            (bbbHist+h)->SetBinContent(i,bbbunf);
            (bbbHist+h)->SetBinError(i,bbbunfErr);
        } 
    }
}




// PERFORM UNFOLDING 
// Note the different regularization modes:
// (1) regMode=0 is standard BBB unfolding, no regularization
// (2) regMode=1 is SVD Unfolding, regularization by means of 
//        the k Parameter. Specify the k Parameter in 'regPar'
// (3) regMode=2 is SVD Unfolding, regularization by means of
//        the tau Parameter. Specify the tau Parameter 
//        in 'regpar'
// (4) regMode=3 is SVD Unfolding. A scan for the optimal tau
//        parameter is performed. The scan is performed around
//        a "center value" for k, to be specified in 'regpar' .
//        Note: The scan may take a while!     
// (5) regMode=4 is SVD Unfolding. A scan for the optimal tau
//        parameter is performed. The scan is performed around
//        a "center value" for tau, to be specified in 'regpar'    
//        Note: The scan may take a while!     
// (6) regMode=5 is SVD Unfolding. k is automatically set to
//        the number of bins (not counting OF). The parameter
//        'regPar' will be ignored. 
// (7) regMode=6 is SVD Unfolding. A scan for the optimal tau
//        parameter is performed. The scan is performed around
//        a "center value" for k, which will be set to 
//        the number of bins (not counting OF). The parameter
//        'regPar' will be ignored.
// Modes for Plotting:
//        If you specify filenames, plots will be drawn and saved.
//        Scan Plots will only be produced if scanPlots=true
// Return value: 
//        Best value of tau if scan is performed, -1. otherwise
// Systematics Handling: 
//        If numSys > 0, the TH1-parameters 
//        'respInputHist', 'recInputHist', 'bgrInputHist',  
//        'ttbgrInputHist' and 'genInputHist' will be interpreted as 
//        arrays with numSys+1 entries, with nominal sample at position
//        0 followed by the shifted samples.
//        Exception: Since you do not want to shift the data distribution,
//        this one will NOT be considered as an array!
//        The placeholder parameter 'unfolded' must also be an
//        array with numSys+1 elements.
double TopSVDFunctions::SVD_Unfold(
        // Data Input (RAW Data including the background)
        TH1D* dataInputHist,   
        // Background (reco level, all BG, will be substracted from data)
        TH1D* bgrInputHist,
        // ttbar background only (used to calculate a ttbar signal 
        // fraction instead of subtracting the yield which depends 
        // on the inclusive ttbar cross section.) 
        // Note: if 0 pointer is handed over 
        TH1D* ttbgrInputHist, 
        // Generated signal MC
        TH1D* genInputHist,
        // Reconstructed signal MC
        TH1D* recInputHist,        
        // Response Matrix 
        TH2D* respInputHist,   
        // Binning for the unfolding (bin sizes !!!)
        const double thebins[],     
        // Number of bins for unfolding (not counting OF bins !!!)
        const int numbins,  
        // Regularization parameter
        double regPar,                          
        // Regularization Modus
        int regMode,    
        // Returned: Unfolded Distribution.    
        TH1D*& unfolded,   
        // Specify the number of systematic samples to unfold 
        int numSys, 
        // Specify Name for the Channel ("mumu", "emu", "ee" ...)
        TString channel,  
        // Specify Name for the Physics Object ("Top", "Jets", "Leptons")
        TString particle, 
        // Specify Name for the Quantity ("Eta", "Pt", or "Mass");
        TString quantity,
        // Specify Name for special run of unfolding
        TString special,
        // Array of Names for the different systematics
        // if you run only over the nominal sample, provide NULL
        TString syst,
        // Nicely formatted name for the channel
        TString channelTex,
        // Nicely formatted name for the physics object
        TString particleTex,
        // Nicely formatted name for ithe quantity
        TString quantityTex,
        // Nicely formatted name indicating some special condition 
        TString specialTex,
        // Array of Names for the different systematics
        // if you run only over the nominal sample, provide NULL
        TString systTex,
        // If specified, plots will be saved in ROOT File
        TString rootFile,
        // If specified, plots will be saved in PS File 
        TString psFile,  
        // If specified, optimal Reg Parameters will be written to this file.
        // The file will NOT be overwritten, rather the result will be appended.
        // The following data will be saved in this order: 
        // (1) the optimal tau, (2) the two nearest k values,
        // (3) the k value from the d value method
        // (4) the number of bins including side bins
        TString scanResultFile,
        // parameter to control amount of output
        // verbose=0: no output at all
        // verbose=1: standard output
        // verbose=2: debug output    
        int verbose,
        // produce scan plots
        bool scanPlots 
)
{ 
    

    // Number of Pseudo Experiments for the error calculation    
    int nExperiments = 1000;

    // Automatically create structure for errors
    // in every histogram.
    TH1::SetDefaultSumw2(true);
      
    ///////////////////////////////////////////////////////////////////  
    /////////  S E T   F L A G S   //////////////////////////////////// 
    /////////////////////////////////////////////////////////////////// 
    
    
    
    // Adapt gErrorIgnoreLevel to reduce output
    int initialgErrorLv=gErrorIgnoreLevel;
    if (verbose==1) gErrorIgnoreLevel=kWarning;
    if (verbose==0) gErrorIgnoreLevel=kFatal; 

 
    // SVD Flag
    bool doSVD = true;
    if ( regMode == 0 ) doSVD = false;

    // Regularization Flags
    bool doUseTau = false;
    if ( regMode == 2 ) doUseTau = true;
    if ( regMode == 4 ) doUseTau = true; 

    // Scan Flags
    bool doScan = false;
    if ( regMode == 3 ) doScan = true;
    if ( regMode == 4 ) doScan = true;
    if ( regMode == 6 ) doScan = true;


    // Plotting flags
    bool plotsToRoot = false;
    if ( !rootFile.CompareTo("")==0 ) plotsToRoot = true;
    bool plotsToPs = false;
    if ( !psFile.CompareTo("")==0 ) plotsToPs = true;
    bool doAllPlots = false;
    if ( plotsToRoot == true || plotsToPs == true ) doAllPlots = true;
    bool doTextFile = false;
    if ( !scanResultFile.CompareTo("")==0 ) doTextFile = true;


    // Systematics Flags
    if ( numSys < 0 ) numSys = 0;
    bool doSystematics = false;
    if ( numSys > 0 ) doSystematics = true;

    // Set regPar to number of bins
    if ( regMode == 5 || regMode == 6 ) {
        regPar = (double) numbins;
    } 
     
      
    /////////////////////////////////////////////////////////////////// 
    /////////  R E B I N N I N G   //////////////////////////////////// 
    ///////////////////////////////////////////////////////////////////
    
    // This is done for all systematics!
    
    // Prepare the binning 
    int nbins = numbins + 2;
    double bins[nbins+1];
    double binwidthup = thebins[numbins] - thebins[numbins-1];
    double binwidthdown = thebins[1] - thebins[0];
    bins[0] = thebins[0] - binwidthdown;
    bins[nbins]  = thebins[numbins] + binwidthup;
    for ( int i = 1 ; i < nbins ; i++ ) {
        bins[i] = thebins[i-1];
    } 

 

    // data (including background)
    // ATTENTION: Hier we assume to have only ONE histo in the array1
    TH1D* rawHist = SVD_Rebin1D(dataInputHist, nbins, bins, 1);
    SVD_EmptySideBins1D(rawHist);
 
 
    // All Background
    // Set errors to zero!
    TH1D* bgrHist = NULL;
    if ( bgrInputHist != NULL ) {
        bgrHist = SVD_Rebin1D((TH1D*) bgrInputHist, nbins, bins, numSys+1); 
        SVD_EmptyHistoErrors1D(bgrHist, numSys+1);
        SVD_EmptySideBins1D    (bgrHist, numSys+1);
    } 
     
    // ttbar background only
    TH1D* ttbgrHist = NULL;
    if ( ttbgrInputHist != NULL ) {
        ttbgrHist= SVD_Rebin1D((TH1D*) ttbgrInputHist, nbins, bins, numSys+1); 
        SVD_EmptyHistoErrors1D(ttbgrHist, numSys+1);
        SVD_EmptySideBins1D   (ttbgrHist, numSys+1);
    } 
     
    // Response Matrix
    // ... thereby transposing it
    TH2D* mcHist = SVD_Rebin2D((TH2D*) respInputHist, nbins, bins, nbins, bins, numSys+1, true);
    SVD_EmptySideBins2D(mcHist, numSys+1); 

 
    // ttbar (MC truth signal)
    // ATTENTION: Do not empty the side bins here!
    TH1D* xiniHist = SVD_Rebin1D((TH1D*) genInputHist, nbins, bins, numSys+1);  
 
     
    // ttbar (reconstructed MC signal)
    TH1D* biniHist = SVD_Rebin1D((TH1D*) recInputHist, nbins, bins, numSys+1);
    SVD_EmptySideBins1D(biniHist, numSys+1);  

     
    /////////////////////////////////////////////////////////////////// 
    /////////  B A C K G R O U N D   H A N D L I N G  /////////////////
    ///////////////////////////////////////////////////////////////////
    
    // This is done for all systematics!
     
    // ATTENTION! 
    // (1) Errors from background will be neglected! 
    // (2) If 'ttbgrInputHist' is given, it will be removed by
    //     a multiplicative approach that is xSec independent!   
    // (3) If 'bgrInputHist' is given, it will be removed from the
    //     data by substraction.
    // (4) If both 'bgrInputHist' and 'ttbgrInputHist' are given,
    //     the difference between 'bgrInputHist' and 'ttbgrInputHist'
    //     will be substracted from the data and the background given
    //     int 'ttbgrInputHist' will be treated as described in (2).
    // (5) If neither 'bgrInputHist' nor 'ttbgrInputHist' are given,
    //     no background will be considered.
    
    // Placeholder for background free data
    TH1D* dataHist = SVD_CloneHists1D(biniHist,numSys+1);
    
    // Background reduction
    SVD_BackgrHandling(dataHist, bgrHist, ttbgrHist, biniHist, rawHist, numSys+1);
    SVD_EmptySideBins1D(dataHist, numSys+1);


 
    ///////////////////////////////////////////////////////////////////
    ////////////   B I N   B Y   B I N   U N F O L D I N G   //////////
    ///////////////////////////////////////////////////////////////////
 

    // This is done for all systematics!
 
    // BBB-Efficiency
    TH1D* beffHist = SVD_CloneHists1D(xiniHist,numSys+1);
    SVD_BBBEff(beffHist, biniHist, xiniHist, numSys+1); 
  
  
    // Do BBB Unfolding 
    // Output stored in 'bbbHist'
    // ATTENTION:
    // (1) Use BBB Efficiency.
    // (2) Although this might be tempting,
    //     do not include the error from the efficiency.
    //     This would bust your BBB / SVD comparison.
    //     Instead, add the error on the efficiency
    //     later on as a systematic MC uncertainty! 
    TH1D* bbbHist = SVD_CloneHists1D(xiniHist,numSys+1);
    SVD_BBBUnf(bbbHist, dataHist, beffHist, numSys+1); 
    
 
    ///////////////////////////////////////////////////////////////////
    ////////////   U N F O L D I N G //////////////////////////////////
    ///////////////////////////////////////////////////////////////////
    
    
    // This is done for all systematics!
    
    // Get Lumi Scale Factor
    // This is done only for the nominal sample
    double lumiScaleFactor =  SVD_LumiScaleFactor(dataHist, biniHist);  



    // DATA COVARIANCE
    // ATTENTION! This established the statistical uncertainty!
    // I think ...
    // ... it should be not be shifted for systematics!
    TH2D* dataCovHist = (TH2D*) mcHist->Clone("dataCovHist");
    for ( int i=1; i<=nbins; i++ ) {
        for ( int j = 1; j <= nbins ; j++ ) {
            dataCovHist->SetBinContent(i,j,0.);
            dataCovHist->SetBinError(i,j,0.);
        } 
    } 
    for (int i=1; i<=nbins; i++ ) {
       double variance = TMath::Power(dataHist->GetBinError(i), 2.);
       dataCovHist->SetBinContent(i,i,variance);
    } 
 

    // Regularization
    int theKReg = -1;
    double theTau = -1.;
    if ( doUseTau == true ) {
        theKReg = -1;
        theTau = regPar;
    } 
    else {
        theKReg = (int) regPar; 
        theTau = 0.;
    }  
    
      
    // Output
    if(verbose>0){
        cout << "Unfolding " << channel << "/" << quantity << "/" << particle;
        if ( ! special.CompareTo("") == 0 ) cout << "/" << special;
        if ( ! syst.CompareTo("") == 0 ) cout << "/" << syst;
        if ( doUseTau == true ) cout << " with tau=" << theTau;
        if ( doUseTau == false ) cout << " with k=" << theKReg;
        cout << endl;
    }
    
     
    // Setup Unfolding Tools
    // One for each Systematic Sample
    // This way, they are all independent from each other
    TopSVDUnfold*  mySVDUnfold = SVD_SetupTool(dataHist, biniHist, xiniHist, mcHist, theTau, numSys+1); 
  
    
    // Unfolding 
    TH1D* unfHist = SVD_CallSVDUnfolding(mySVDUnfold, theKReg, numSys+1);
    
     
    // Get more output
    TH1D* weightHist = SVD_RetrieveWeights(mySVDUnfold, numSys+1);
    TH1D* ddHist = SVD_RetrieveDD(mySVDUnfold, numSys+1);
    TH1D* svHist = SVD_RetrieveSV(mySVDUnfold, numSys+1);
    
        
    // Output
    if(verbose>0) cout << "Unfolding done!" << endl;
 
     
    ///////////////////////////////////////////////////////////////////
    ////////////   C O V A R I A N C E    /////////////////////////////
    ///////////////////////////////////////////////////////////////////
    
    // This is done for the nominal sample only!
    
    
    // Calculate TOTAL COVARIANCE
    TH2D* statCovHist = mySVDUnfold->GetUnfoldCovMatrix(dataCovHist , nExperiments);
    TH2D* mcCovHist = mySVDUnfold->GetAdetCovMatrix(nExperiments);
    TH2D* totCovHist = (TH2D*) statCovHist->Clone("totCovHist");
    totCovHist->Add(mcCovHist);
 
    // STAT ERROR ON RESULT
    // ATTENTION:
    // Use only the statistical uncertainty!
    // Not the MC uncertainty or anything else!
    // Otherwise, comparisons to standard BBB unfolding
    // will be very difficut. 
    for ( int i = 1 ; i <= nbins ; i++ ) {
        double errorsq = statCovHist->GetBinContent(i,i);
        double error = 0.;
        if ( errorsq > 0. ) {
            error = TMath::Sqrt(errorsq);
        } 
        unfHist->SetBinError(i, error); 
    }
     
    ///////////////////////////////////////////////////////////////////
    ////////////   K   S C A N     ////////////////////////////////////
    /////////////////////////////////////////////////////////////////// 
    
    // This is done for the nominal sample only!
    
    
    // Count the Singular Values
    int nSingularValues = 0;
    int nSignSingularValues = 0;
    int nScanSingularValues = 0;  
    for ( int i = 0 ; i < nbins ; i++ ) {
        double sv = svHist->GetBinContent(i+1);
        double dd = ddHist->GetBinContent(i+1);
        if ( sv > 0. ) {
            nSingularValues++ ;
            if ( dd > 1. ) nSignSingularValues++ ;
            if ( dd > 0.01 ) nScanSingularValues++ ; 
        }
    }  
     
     
    // Save Singular Values in TVector  
    TVectorD vSingularValues(nSingularValues);
    for ( int i = 0 ; i < svHist->GetNbinsX() ; i++ ) {
        double sv = svHist->GetBinContent(i+1);  
        if ( sv > 0. ) vSingularValues[i] = sv; 
    }  
    
    
    // Setup Arrays to hold the histograms
    TH1D* arrK_StatError = NULL;
    TH1D* arrK_Weight = NULL;
    TH1D* arrK_Mean = NULL;
    TH1D* arrK_GlC = NULL;
     
     
    
    bool doKScan = true;
    if ( doKScan == true ) {
        
        // Create new Objects
        arrK_StatError = new TH1D[nScanSingularValues-1];
        arrK_Weight = new TH1D[nScanSingularValues-1];
        arrK_GlC = new TH1D[nScanSingularValues-1];
        arrK_Mean = new TH1D[nScanSingularValues-1];
        
        // Do Scan
        int kscancounter = 0;
        for ( int tmpK = 2 ; tmpK <= nScanSingularValues ; tmpK++ ) { 
            
            // Unfold with temporary k
            TH1D* tmpUnfResult = (TH1D*) mySVDUnfold->Unfold(tmpK)->Clone(TString::Format("arrK_Mean_%i", tmpK)); 
            TString unfStr = SVD_PlotName(channel, particle, quantity, special, syst, "UNF");
            SVD_SetTitles1D(tmpUnfResult, unfStr, quantityTex, "Events");
             
            // Get Weights
            TH1D* tmpWeights = (TH1D*) mySVDUnfold->GetWeights()->Clone(TString::Format("arrK_Weight_%i", tmpK)); 
            tmpWeights->Scale(1./lumiScaleFactor);
            TString weightStr = SVD_PlotName(channel, particle, quantity, special, syst, "WGT");
            SVD_SetTitles1D(tmpWeights, weightStr, quantityTex, "Weights");  
             

            // Calculate the Error matrix (internally, more unfoldings ... )
            TH2D* tmpCovHist = (TH2D*) mySVDUnfold->GetUnfoldCovMatrix(dataCovHist, nExperiments)->Clone("tmpCovHist"); 
            TH1D* tmpErr = SVD_Cov2Err(tmpCovHist, tmpUnfResult, TString::Format("arrK_Mean_%i", tmpK), quantityTex, "Stat.");
            TString statErrStr = SVD_PlotName(channel, particle, quantity, special, syst, "STATERR"); 
            SVD_SetTitles1D(tmpErr, statErrStr, quantityTex, "Stat. Err. in \%");  
             
            
    		
            // Global Correlation
            TH1D* tmpGlC = SVD_CalcGlobCorr(tmpCovHist); 
            TString glcStr = SVD_PlotName(channel, particle, quantity, special, syst, "GLOBC");
            SVD_SetTitles1D(tmpGlC, glcStr, quantityTex, "Glob. Corr. in \%");
             
            
 
            // Save Objects in Array
            arrK_StatError[kscancounter] = *tmpErr;
            arrK_Weight[kscancounter] = *tmpWeights;
            arrK_GlC[kscancounter] = *tmpGlC;
            arrK_Mean[kscancounter] = *tmpUnfResult;
 
            // Delete obsolete objects
            //delete tmpCovHist;

            // Increment Counter
            kscancounter++;
        } 
    }
        
 
     
    ///////////////////////////////////////////////////////////////////
    ////////////   T A U    S C A N     ///////////////////////////////
    ///////////////////////////////////////////////////////////////////  


    // This is done for the nominal sample only!
 
    // Create Scan Vectors
    TVectorD* vScanPoints = NULL; 
    TVectorD* vGlobCorr = NULL; 
    TVectorD* vChiSq = NULL; 
    TVectorD* vCurv = NULL;    
    TVectorD* vAvgSqErr = NULL;
    TVectorD* vAvgMean = NULL;    
    double optimalTauX     = -1.;
    double optimalTauY     = -1.;
    double optimalChiSq    = -1.;
    double optimalCurv     = -1.;
    double optimalAvgSqErr = -1.;
    double optimalAvgMean  = -1.;
    int optimalTauLowK = -1;
    int optimalTauHighK = -1;

    // Doubles for BBB values
    double bbbAvgSqErr = 0.;
    double bbbAvgMean = 0.;  
 
  
    if ( doScan == true ) {
            
            
        // Steer Scan
        double rangefactor = 100.;
        int nScanPoints = 100;
          
          
        // Range for Scan
        double lowTau = 0.;
        double highTau = 0.;
        if ( doUseTau == false ) {
	  // Find interesting singular value 
	  // Limit the kReg to the Modes which are actually there! 
	  int effectiveKReg = theKReg;
	  if ( effectiveKReg >= nSingularValues ) effectiveKReg = nSingularValues-1;
	  double singularValueK =  vSingularValues[effectiveKReg];

	  lowTau = (1./rangefactor) * singularValueK;
	  highTau = rangefactor * singularValueK;
        } else {
            lowTau = (1./rangefactor) * theTau;
            highTau = rangefactor * theTau;
        }

        // Slow scan for plots
        if ( scanPlots == true ) {       
              
            // Get the Scan Points
            vScanPoints = SVD_CalcScanPoints(lowTau, highTau, nScanPoints);
    
            // Create the vectors
            vGlobCorr = new TVectorD(nScanPoints);
            vChiSq = new TVectorD(nScanPoints);
            vCurv = new TVectorD(nScanPoints);
            vAvgSqErr = new TVectorD(nScanPoints);
            vAvgMean = new TVectorD(nScanPoints);
    
            // Perform the Scan
            if (verbose>0) cout << "Perform Tau Scan from " << lowTau << " to " << highTau << " for plotting purpose" << endl;  
            for ( int i = 0 ; i < nScanPoints ; i++ ) {
      
                // Do the unfolding with k = -1
                double tau = (*vScanPoints)[i];
                mySVDUnfold->SetTau(tau); 
                TH1D* tmpUnfResult = (TH1D*) mySVDUnfold->Unfold(-1)->Clone("tmpUnfResult"); 
                TH1D* tmpWeights = (TH1D*) mySVDUnfold->GetWeights()->Clone("tmpWeightResult"); 
                double tmpCurv = mySVDUnfold->GetCurv();
                  
                // Calculate the Error matrix (internally, more unfoldings ... )
                TH2D* tmpCovHist = (TH2D*) mySVDUnfold->GetUnfoldCovMatrix(dataCovHist, nExperiments)->Clone("tmpCovHist");
                  
                // Global Correlation 
                (*vGlobCorr)[i] = SVD_ScanGlobalCorrelation(tmpCovHist);
                  
                // Chi Squared
                (*vChiSq)[i] = SVD_ScanChiSquared(tmpWeights, dataHist, mcHist);
                  
                // Curvature
                (*vCurv)[i] = SVD_ScanCurvature(tmpCurv);
                  
                // Avg Err
                (*vAvgSqErr)[i] = SVD_ScanAvgSqErr(tmpCovHist);
                  
                // Avg Mean
                (*vAvgMean)[i] = SVD_ScanAvgMean(tmpUnfResult);
                  
                // Output
                if(verbose>0)cout << "    done for Tau = " << tau << " -> GlobCorr: " << (*vGlobCorr)[i] <<endl;
                  
                // delete things
                delete tmpUnfResult;
                delete tmpWeights;
                delete tmpCovHist;
            }
        }

        // Before starting the golden section search, we have to reset the unfolding class
        mySVDUnfold->Unfold(-1);

        // Determine optimal tau value with golden section     
        double goldSec = (3.-sqrt(5.))/2.;
        double globCorrLowTau = 1000.;
        double globCorrHighTau = 1000.;
        double newLowTau  = TMath::Power(10.,TMath::Log10(lowTau) + goldSec*(TMath::Log10(highTau)-TMath::Log10(lowTau)));
        double newHighTau = TMath::Power(10.,TMath::Log10(highTau) - goldSec*(TMath::Log10(highTau)-TMath::Log10(lowTau)));
    
        for ( int i = 0 ; i < nScanPoints ; i++ ) {
            if( optimalTauX!=newLowTau ){
                // Do the unfolding for lowTau
                mySVDUnfold->SetTau(newLowTau);
                // Calculate the Error matrix (internally, more unfoldings ... )
                TH2D* tmpCovHist = (TH2D*) mySVDUnfold->GetUnfoldCovMatrix(dataCovHist, nExperiments)->Clone("tmpCovHist");
                // Global Correlation 
                globCorrLowTau = SVD_ScanGlobalCorrelation(tmpCovHist);
                // delete Error matrix
                delete tmpCovHist;
                // print global correlation for new tau
                if(verbose>0)cout << "newLowTau: " << newLowTau << " -> globCorr: " << globCorrLowTau << endl;
            }
            if(optimalTauX!=newHighTau){
                // Do the unfolding for highTau
                mySVDUnfold->SetTau(newHighTau);
                // Calculate the Error matrix (internally, more unfoldings ... )
                TH2D* tmpCovHist = (TH2D*) mySVDUnfold->GetUnfoldCovMatrix(dataCovHist, nExperiments)->Clone("tmpCovHist");
                // Global Correlation 
                globCorrHighTau = SVD_ScanGlobalCorrelation(tmpCovHist);
                // delete Error matrix
                delete tmpCovHist;
                // print global correlation for new tau
                if(verbose>0)cout << "newHighTau: " << newHighTau << " -> globCorr: " << globCorrHighTau << endl;
            }
            if(globCorrLowTau<globCorrHighTau){
                highTau=newHighTau;
                optimalTauX=newLowTau;
                optimalTauY=globCorrLowTau;
                newHighTau=newLowTau;
                if(TMath::Abs(globCorrLowTau-globCorrHighTau)/(globCorrLowTau+globCorrHighTau)<0.000001)break;
                globCorrHighTau=globCorrLowTau;
                newLowTau=TMath::Power(10.,TMath::Log10(lowTau) + goldSec*(TMath::Log10(highTau)-TMath::Log10(lowTau)));
            } else {
                lowTau=newLowTau;
                optimalTauX=newHighTau;
                optimalTauY=globCorrHighTau;
                newLowTau=newHighTau;
                if(TMath::Abs(globCorrLowTau-globCorrHighTau)/(globCorrLowTau+globCorrHighTau)<0.000001)break;
                globCorrLowTau=globCorrHighTau;
                newHighTau=TMath::Power(10.,TMath::Log10(highTau) - goldSec*(TMath::Log10(highTau)-TMath::Log10(lowTau)));
            }
        }
        if(verbose>0)cout << "Optimal Tau = " << optimalTauX << endl;
     
     
        // Find closest K values
        optimalTauLowK = 0;
        for ( int i = 0 ; i < nSingularValues ; i++ ) {
            double sv = vSingularValues[i];
            if ( sv > optimalTauX ) optimalTauLowK++;
        }
        optimalTauHighK=optimalTauLowK+1;
     
        // Evaluation at optimal tau
        mySVDUnfold->SetTau(optimalTauX); 
        TH1D* tmpUnfResult = (TH1D*) mySVDUnfold->Unfold(-1)->Clone("tmpUnfResult"); 
        TH1D* tmpWeights = (TH1D*) mySVDUnfold->GetWeights()->Clone("tmpWeightResult"); 
        double tmpCurv = mySVDUnfold->GetCurv();
        
        // Calculate the Error matrix (internally, more unfoldings ... )
        TH2D* tmpCovHist = (TH2D*) mySVDUnfold->GetUnfoldCovMatrix(dataCovHist, nExperiments)->Clone("tmpCovHist");
        
        // Chi Squared
        optimalChiSq = SVD_ScanChiSquared(tmpWeights, dataHist, mcHist);
        
        // Curvature
        optimalCurv = SVD_ScanCurvature(tmpCurv);
        
        // Avg Err
        optimalAvgSqErr = SVD_ScanAvgSqErr(tmpCovHist);
        
        // Avg Mean
        optimalAvgMean = SVD_ScanAvgMean(tmpUnfResult);
    
        // delete things
        delete tmpUnfResult;
        delete tmpWeights;
        delete tmpCovHist;
    
        // Calculations for BBB
        // Do not count the OF bins!
        // Recall: You have 2 sets of OF bins
        bbbAvgSqErr = 0.;
        bbbAvgMean = 0.;
        int bincounter = 0;
        for ( int i = 2 ; i < nbins ; i++ ) {
            double bbb_mean = bbbHist->GetBinContent(i);
            double bbb_err = bbbHist->GetBinError(i);
            if ( bbb_mean <= 0.) continue;
                  
            bincounter++;
            bbbAvgSqErr += bbb_err*bbb_err;
            bbbAvgMean += bbb_mean;
        }
        bbbAvgSqErr = bbbAvgSqErr / ((double) bincounter );
        bbbAvgSqErr = bbbAvgMean / ((double) bincounter );
        bbbAvgSqErr = TMath::Sqrt(bbbAvgSqErr); 
        
    }
 
 
     
    ///////////////////////////////////////////////////////////////////
    ////////////   S A V E   B E S T   V A L U E S   //////////////////
    ///////////////////////////////////////////////////////////////////   

 
    if ( doScan == true && doTextFile == true) {
        
         
        // Make Output Path
        TString outputpath = "";
        bool makeFolder = false;
        if ( outputpath.CompareTo("") == 0 ) outputpath.Append(psFile);
        if ( outputpath.CompareTo("") == 0 ) outputpath.Append(rootFile);
        bool foundSlash = false;
        while ( foundSlash == false ) {
            if ( outputpath.EndsWith("/") == true ) {
                foundSlash = true;
                makeFolder = true;
            }
            if ( foundSlash == false ) outputpath.Chop();
        }
        if ( makeFolder == true) { 
            TString mkdirCommand = "mkdir -p ";
            mkdirCommand.Append(outputpath);
            mkdirCommand.Append(" 2> /dev/null");
            gSystem->Exec(mkdirCommand);
        } 
        
        
        // Touch the Text File
        TString touchCommand = "cd ";
        touchCommand.Append(outputpath);
        touchCommand.Append(" ; touch ");
        touchCommand.Append(scanResultFile);
        gSystem->Exec(touchCommand);
        
        // Set Redirection
        gSystem->RedirectOutput(scanResultFile, "a");
        
        // Write to File
        TString lineStrList =  SVD_CPQSS(channel, particle, quantity, special, syst); 
        lineStrList.Append(" ");
        for ( int i = lineStrList.Length() ; i < 60 ; i++ ) lineStrList.Append(" ");   
        lineStrList.Append(TString::Format("%.5f", optimalTauX)); 
        for ( int i = lineStrList.Length() ; i < 72 ; i++ ) lineStrList.Append(" ");    
        lineStrList.Append(TString::Format("%i", optimalTauLowK)); 
        for ( int i = lineStrList.Length() ; i < 76 ; i++ ) lineStrList.Append(" ");  
        lineStrList.Append(TString::Format("%i", optimalTauHighK)); 
        for ( int i = lineStrList.Length() ; i < 80 ; i++ ) lineStrList.Append(" ");  
        lineStrList.Append(TString::Format("%i", nSignSingularValues)); 
        for ( int i = lineStrList.Length() ; i < 84 ; i++ ) lineStrList.Append(" ");  
        lineStrList.Append(TString::Format("%i", nbins)); 
        cout << lineStrList << endl;  
        
        // Reset Redirection
        gSystem->RedirectOutput(NULL, "a");
        
    }
 
  
    ///////////////////////////////////////////////////////////////////
    ////////////   R E T U R N   O B J E C T S  ///////////////////////
    ///////////////////////////////////////////////////////////////////    
 
    // Format everything that will be returned in all cases 
 
    // Strings
    if ( channel.CompareTo("") == 0 ) channel.Append("channel");
    if ( particle.CompareTo("") == 0 ) particle.Append("particle");
    if ( quantity.CompareTo("") == 0 ) quantity.Append("quantity");
    if ( special.CompareTo("") == 0 ) special.Append("");
    if ( syst.CompareTo("") == 0 ) syst.Append("");
    if ( channelTex.CompareTo("") == 0 ) channelTex.Append("channelTex");
    if ( particleTex.CompareTo("") == 0 ) particleTex.Append("particleTex");
    if ( quantityTex.CompareTo("") == 0 ) quantityTex.Append("quantityTex");
    if ( specialTex.CompareTo("") == 0 ) specialTex.Append("");
    if ( systTex.CompareTo("") == 0 ) systTex.Append("");
 
     
    // Format BBB Plot
    TString bbbStr = SVD_PlotName(channel, particle, quantity, special, syst, "BBB");
    SVD_SetTitles1D(bbbHist, bbbStr, quantityTex, "Events", numSys+1);

        
    // Format SVD Plot (Weights)
    TString weightStr = SVD_PlotName(channel, particle, quantity, special, syst, "WGT");
    SVD_SetTitles1D(weightHist, weightStr, quantityTex, "Weights", numSys+1);
        
        
    // Format SVD Plot
    TString unfStr = SVD_PlotName(channel, particle, quantity, special, syst, "UNF");
    SVD_SetTitles1D(unfHist, unfStr, quantityTex, "Events", numSys+1);
 

    // Set Pointer
    if ( doSVD == true ) unfolded = SVD_CloneHists1D(unfHist, numSys+1);
    if ( doSVD == false ) unfolded =  SVD_CloneHists1D(bbbHist, numSys+1);
 


    // RETURN 
    // If no more plots are needed, return now 
    if ( doAllPlots == false ) return optimalTauX; 
 
 
 
    ///////////////////////////////////////////////////////////////////
    ////////////   F O R M A T   H I S T O G R A M S   ////////////////
    ///////////////////////////////////////////////////////////////////  
    
    // Format all histos we have already created!
    
    // Format Covariance Matrix
    TString dataCovStr = SVD_PlotName(channel, particle, quantity, special, syst, "DATACOV");
    SVD_SetTitles2D(dataCovHist, dataCovStr, quantityTex, quantityTex, "Covariance on Measurements", 1); 
        

    // Format Raw Data
    // Note: Here we have only 1 histogram in the array!
    TString rawStr = SVD_PlotName(channel, particle, quantity, special, syst, "YRAW");
    SVD_SetTitles1D(rawHist, rawStr, quantityTex, "Events", 1);

    // Format Bgr    
    TString bgrStr = SVD_PlotName(channel, particle, quantity, special, syst, "YBGR");
    SVD_SetTitles1D(bgrHist, bgrStr, quantityTex, "Events", numSys+1);


    // Format Data
    TString dataStr = SVD_PlotName(channel, particle, quantity, special, syst, "YDAT");
    SVD_SetTitles1D(dataHist, dataStr, quantityTex, "Events", numSys+1);


    // Format Response Matrix
    TString mcStr = SVD_PlotName(channel, particle, quantity, special, syst, "AA");
    TString mcStrX = quantityTex;
    mcStrX.Append(" (Reconstructed)");
    TString mcStrY = quantityTex;
    mcStrY.Append(" (Generated)");
    TString mcStrZ("Entries");
    SVD_SetTitles2D(mcHist, mcStr, mcStrX, mcStrY, mcStrZ, numSys+1);

 
    // Format Gen MC
    TString xiniStr = SVD_PlotName(channel, particle, quantity, special, syst, "XGEN");
    SVD_SetTitles1D(xiniHist, xiniStr, quantityTex, "Events", numSys+1);
 

    // Format Rec MC
    TString biniStr = SVD_PlotName(channel, particle, quantity, special, syst, "XREC");
    SVD_SetTitles1D(biniHist, biniStr, quantityTex, "Events", numSys+1);


    // Format BBB Eff
    TString beffStr = SVD_PlotName(channel, particle, quantity, special, syst, "BBBEFF");        
    SVD_SetTitles1D(beffHist, beffStr, quantityTex, "Bin by Bin Efficiency", numSys+1);

        
    // Format Stat COV
    // Note: Here we have only 1 histogram in the array!
    TString statCovStr = SVD_PlotName(channel, particle, quantity, special, syst, "STATCOV");
    SVD_SetTitles2D(statCovHist, statCovStr, quantityTex, quantityTex, "Statistical Covariance", 1);


    // Format MC COV 
    // Note: Here we have only 1 histogram in the array!
    TString mcCovStr = SVD_PlotName(channel, particle, quantity, special, syst, "MCCOV");
    SVD_SetTitles2D(mcCovHist, mcCovStr, quantityTex, quantityTex, "Monte Carlo Covariance", 1);


    // Format Tot COV
    // Note: Here we have only 1 histogram in the array!
    TString totCovStr = SVD_PlotName(channel, particle, quantity, special, syst, "TOTCOV");
    SVD_SetTitles2D(totCovHist, totCovStr, quantityTex, quantityTex, "Monte Carlo Covariance", 1);
     

    // Format D-Distribution 
    TString ddStr = SVD_PlotName(channel, particle, quantity, special, syst, "DD");
    SVD_SetTitles1D(ddHist, ddStr, "Index i", "d-Value d_{i}", numSys+1);


    // Format Singular Values
    TString svStr = SVD_PlotName(channel, particle, quantity, special, syst, "SV");
    SVD_SetTitles1D(svHist, svStr, "Index i", "Singular Value s_{i}", numSys+1);
  
        
    /////////////////////////////////////////////////////////////////// 
    ////////////   M I G R A T I O N   P L O T S    /////////////////// 
    ///////////////////////////////////////////////////////////////////


    // PURITY
    // Note: Purity is set to zero, if number of reconstructed
    // events in a bin is zero
    TH1D* purHist = SVD_CloneHists1D(biniHist, numSys+1);
    SVD_Pur(purHist, mcHist, numSys+1); 
    TString purStr = SVD_PlotName(channel, particle, quantity, special, syst, "PUR");
    SVD_SetTitles1D(purHist, purStr, quantityTex, "Purity", numSys+1);



    // STABILITY
    // Note: Stability is set to zero, if there are no
    // gerenated events in a bin
    // Note: If there is no reconstructed event in this bin,
    // then the stability is naturally zero, too
    TH1D* stabHist = SVD_CloneHists1D(biniHist, numSys+1); 
    SVD_Stab(stabHist, mcHist, numSys+1); 
    TString stabStr = SVD_PlotName(channel, particle, quantity, special, syst, "STAB");
    SVD_SetTitles1D(stabHist, stabStr, quantityTex, "Stability", numSys+1);

 

    // EFFICIENCY
    // Note: If no generated events are available in a bin,
    // then the efficiency is set to zero
    TH1D* effHist = SVD_CloneHists1D(biniHist, numSys+1); 
    SVD_Eff(effHist, mcHist, xiniHist, numSys+1);  
    TString effStr = SVD_PlotName(channel, particle, quantity, special, syst, "EFF"); 
    SVD_SetTitles1D(effHist, effStr, quantityTex, "Efficiency", numSys+1);
    


    // RATIO: Unfolded versus BBB
    TH1D* histRatioUnfBBB = SVD_MakeRatioNum(unfHist, bbbHist, numSys+1);
    SVD_SetTitles1D(histRatioUnfBBB, "RATIO", quantityTex, "Ratio", numSys+1);


 
         
    /////////////////////////////////////////////////////////////////// 
    ////////////   R E F O L D I N G     ////////////////////////////// 
    ///////////////////////////////////////////////////////////////////

 

    // REFOLDING - without Background 
    // Note, here we need to use the weightHist, since the
    // xiniHist contains empty gen level bins
    //TH1D* refoldHist = SVD_Refold(unfHist, xiniHist, mcHist); 
    TH1D* refoldHist = SVD_Refold(weightHist, NULL, mcHist, true, numSys+1); 
    TString refoldStr = SVD_PlotName(channel, particle, quantity, special, syst, "RFLD");
    SVD_SetTitles1D(refoldHist, refoldStr, "Bin i", "Refolded Value d_{i}", numSys+1);


    // RATIO: Refolded versus Data
    TH1D* histRatioRefDat = SVD_MakeRatioDenom(refoldHist, dataHist, numSys+1);
    SVD_SetTitles1D(histRatioRefDat, "RATIO", quantityTex, "Ratio", numSys+1);



    // Calculate Chi2A 
    // For the nominal histo!
    double chi2A = SVD_Chi2A(dataHist, refoldHist);   
    int goodRecBins = SVD_GoodRecBins(dataHist);
    TString chi2AStr = TString::Format("#chi^{2} = %.3f", chi2A); 
    TString nDOFStr = TString::Format("nDOF=%i", goodRecBins);  
    
     
         
    /////////////////////////////////////////////////////////////////// 
    ////////////   E R R O R   P L O T S ////////////////////////////// 
    ///////////////////////////////////////////////////////////////////
 

    // These are done only for the nominal sample!

    // ERROR PLOT (Statistics)
    TString statErrStr = SVD_PlotName(channel, particle, quantity, special, syst, "STATERR");
    TH1D* statErrHist = SVD_Cov2Err(statCovHist, unfHist, statErrStr, quantityTex, "Statistical");

   
    // ERROR PLOT (MC)
    TString mcErrStr = SVD_PlotName(channel, particle, quantity, special, syst, "MCERR");
    TH1D* mcErrHist = SVD_Cov2Err(mcCovHist, unfHist, mcErrStr, quantityTex, "MC");



    // ERROR PLOT (Total)
    TString totErrStr = SVD_PlotName(channel, particle, quantity, special, syst, "TOTERR");
    TH1D* totErrHist = SVD_Cov2Err(totCovHist, unfHist, totErrStr, quantityTex, "Total");
 


    // ERROR PLOT (BBB)
    TH1D* bbbErrHist = (TH1D*) unfHist->Clone("bbbErrHist");
    for ( int i = 1 ; i <= nbins ; i++ ) {
        double errorBBBAbs = bbbHist->GetBinError(i);
        double valueBBB = bbbHist->GetBinContent(i);
        double error = 0.;
        if ( valueBBB > 0. ) error = 100* errorBBBAbs / valueBBB;
        bbbErrHist->SetBinContent(i, error);
    } 
    TString bbbErrStr = SVD_PlotName(channel, particle, quantity, special, syst, "BBBERR");
    bbbErrHist->SetName(bbbErrStr);
    bbbErrHist->SetTitle(bbbErrStr);
    SVD_SetTitles1D(bbbErrHist, bbbErrStr, quantityTex, "Statistical Error in \%");


    // RATIO: UnfErrors versus BBBErrors
    TH1D* histRatioErrors = SVD_MakeRatioZero(statErrHist, bbbErrHist);
    SVD_SetTitles1D(histRatioErrors, "RATIO", quantityTex, "Ratio");


    // CORRELATION STAT
    TString statCorrStr = SVD_PlotName(channel, particle, quantity, special, syst, "STATCORR");
    TH2D* statCorrHist = SVD_Cov2Corr(statCovHist, statCorrStr, quantityTex, "Statistical");


    // CORRELATION MC    
    TString mcCorrStr = SVD_PlotName(channel, particle, quantity, special, syst, "MCCORR");
    TH2D* mcCorrHist = SVD_Cov2Corr(mcCovHist, mcCorrStr, quantityTex, "MC");


    // CORRELATION TOT
    TString totCorrStr = SVD_PlotName(channel, particle, quantity, special, syst, "TOTCORR");
    TH2D* totCorrHist = SVD_Cov2Corr(totCovHist, totCorrStr, quantityTex, "Total");

 
    // GLOBAL CORRELATION
    // Attention: Do not use the side bins for the computation
    // of the global correlation !!!    
    // The global correlation in the side bins will be set 
    // to zero!
    TH1D* glcHist = SVD_CalcGlobCorr(statCovHist);
    TString glcStr = SVD_PlotName(channel, particle, quantity, special, syst, "GLOBC");
    glcHist->SetName(glcStr);
    glcHist->SetTitle(glcStr);
    SVD_SetTitles1D(glcHist, glcStr, quantityTex, "Glob. Corr. in \%");



    // Systematic Shifts with Unfolding
    TH1D* unfShiftHist = SVD_ArrayToShifts(unfHist, numSys+1);
    SVD_SetTitles1D(unfShiftHist, "SHIFT", quantityTex, "Syst. Shift in \%", numSys);
    
    
    // Systematic Shifts with BBB
    TH1D* bbbShiftHist = SVD_ArrayToShifts(bbbHist, numSys+1);
    SVD_SetTitles1D(bbbShiftHist, "SHIFT", quantityTex, "Syst. Shift in \%", numSys);
    
    
    // Comparison of systematic shifts
    TH1D* ratioShiftHist = SVD_MakeRatioZero(unfHist, bbbHist, numSys);
    SVD_SetTitles1D(ratioShiftHist, "SHIFTRATIO", quantityTex, "Ratio of Syst. Shifts", numSys);
    
    


    ///////////////////////////////////////////////////////////
    ///////////     P S    F I L E   //////////////////////////
    /////////////////////////////////////////////////////////// 

 

 
    // DRAW IT ALL
    if ( plotsToPs == true ) {
        
        // Do not associate histograms with a directory
        TH1::AddDirectory(kFALSE); 
        
        // Setup Style
        setHHStyle(*gStyle);
        gStyle->SetPadTopMargin(0.15);
        gStyle->SetPadRightMargin(0.2);
        gStyle->SetPaintTextFormat(".0f");

        // Setup Canvas
        TCanvas canvas("Unfolding", "Unfolding");
        gROOT->ForceStyle();
        TGaxis::SetMaxDigits(3);


        // Output Plot File Name and Path 
        TString outputfilename = psFile;                
        TString outputfilenameRoot = rootFile;    
         
 
        // Make Output Path
        TString outputpath = "";
        bool makeFolder = false;
        if ( outputpath.CompareTo("") == 0 ) outputpath.Append(psFile);
        if ( outputpath.CompareTo("") == 0 ) outputpath.Append(rootFile);
        bool foundSlash = false;
        while ( foundSlash == false ) {
            if ( outputpath.EndsWith("/") == true ) {
                foundSlash = true;
                makeFolder = true;
            }
            if ( foundSlash == false ) outputpath.Chop();
        }
        if ( makeFolder == true) { 
            TString mkdirCommand = "mkdir -p ";
            mkdirCommand.Append(outputpath);
            mkdirCommand.Append(" 2> /dev/null");
            gSystem->Exec(mkdirCommand);
        } 

        // Channel, Particle and Quantity
        TString CPQtex = ""; 
        CPQtex.Append(channelTex); 
        CPQtex.Append(", "); 
        CPQtex.Append(particleTex);
        CPQtex.Append(", ");
        CPQtex.Append(quantityTex);     

        // Tex for the Systematics
        TString SystTex = syst;
        SystTex = systTex;


 
        // Draw Response Matrix
        SVD_Draw2D(mcHist, "COLZ");
        canvas.Print(outputfilename.Copy().Append("("));


        // Draw Input Distributions
        TLegend* legendinp = SVD_NewLegend(CPQtex, SystTex); 
        THStack* stackinp = new THStack("",""); 
        SVD_Array2Stack(stackinp, xiniHist, "E", 4, numSys+1);
        SVD_Array2Stack(stackinp, biniHist, "E", 2, numSys+1);
        SVD_Array2Stack(stackinp, dataHist, "E", 1, numSys+1);
        SVD_Array2Legend(legendinp, xiniHist, "Gen", "", numSys+1);
        SVD_Array2Legend(legendinp, biniHist, "Rec", "", numSys+1);
        SVD_Array2Legend(legendinp, dataHist, "Dat", "", numSys+1); 
        SVD_DrawStack(stackinp, quantityTex, "Entries", "", 0); //421);
        legendinp->Draw("SAME");
        canvas.Print(outputfilename);         
 

        // Draw Background related Distributions
        TLegend* legendbgr = SVD_NewLegend(CPQtex, SystTex); 
        THStack* stackbgr = new THStack("",""); 
        SVD_Array2Stack(stackbgr, dataHist, "E", 1, numSys+1);
        SVD_Array2Stack(stackbgr, rawHist, "HIST E", 2, 1); // Only 1 Histogram
        SVD_Array2Stack(stackbgr, bgrHist, "P", 4, numSys+1);
        SVD_Array2Legend(legendbgr, dataHist, "Data", "", numSys+1);
        SVD_Array2Legend(legendbgr, rawHist, "Raw", "", 1); // Only 1 Histogram
        SVD_Array2Legend(legendbgr, bgrHist, "Bgr", "", numSys+1); 
        SVD_DrawStack(stackbgr, quantityTex, "Entries", "", 0); //, 124);
        legendbgr->Draw("SAME");
        canvas.Print(outputfilename);
        dataHist->Draw(); 

        // Draw Weight distributions         
        SVD_ArrayScale(weightHist, 1./lumiScaleFactor, numSys+1);
        TString weightHistLegendEntry = "Weights w_{i}"; 
        TLegend* legendweight = SVD_NewLegend(CPQtex, SystTex, regPar, (int) doUseTau);
        THStack* stackweight = new THStack("", "");   
        SVD_Array2Stack(stackweight, weightHist, "HIST", 1, numSys+1);
        SVD_Array2Legend(legendweight, weightHist, "Weights", "", numSys+1); 
        SVD_DrawStack(stackweight, quantityTex, "Weights", "", 0); //, 134);
        legendweight->Draw("SAME");
        canvas.Print(outputfilename);



        // Draw Unfolded distributions         
        TLegend* legendunf = SVD_NewLegend(CPQtex, SystTex, regPar, (int) doUseTau);
        THStack* stackunf = new THStack("", ""); 
        SVD_Array2Stack(stackunf, unfHist, "E", 1, numSys+1);
        SVD_Array2Stack(stackunf, dataHist, "E", 3, numSys+1);
        SVD_Array2Stack(stackunf, bbbHist, "E", 4, numSys+1);
        SVD_Array2Legend(legendunf, unfHist, "Unfolded", "", numSys+1);
        SVD_Array2Legend(legendunf, dataHist, "Measured", "", numSys+1);
        SVD_Array2Legend(legendunf, bbbHist, "BBB", "", numSys+1); 
        SVD_DrawStack(stackunf, quantityTex, "Entries", "", 0);  
        legendunf->Draw("SAME");
        canvas.Print(outputfilename);
     
     
        // RATIO: Unfolded versus BBB 
        TLegend* legendRatioUnfBBB = SVD_NewLegend(CPQtex, SystTex, regPar, (int) doUseTau); 
        THStack* stackRatioUnfBBB = new THStack("", ""); 
        SVD_Array2Stack(stackRatioUnfBBB, histRatioUnfBBB, "E", 1, numSys+1);
        SVD_Array2Legend(legendRatioUnfBBB, histRatioUnfBBB, "Unf/BBB", "", numSys+1);
        SVD_DrawRange(histRatioUnfBBB, 0.7, 1.4, "", 0); 
        SVD_DrawStackRange(stackRatioUnfBBB, quantityTex, "Entries", 0.7, 1.4, "", 0);  
        legendRatioUnfBBB->Draw("SAME");
        canvas.Print(outputfilename);
     
    
        // Draw Refolded Distribution 
        TLegend* legendrefold = SVD_NewLegend(CPQtex, SystTex, regPar, (int) doUseTau);
        THStack* stackrefold = new THStack("", ""); 
        SVD_Array2Stack(stackrefold, refoldHist, "HIST", 3, numSys+1);
        SVD_Array2Stack(stackrefold, dataHist, "E", 1, numSys+1); 
        SVD_Array2Legend(legendrefold, refoldHist, "Refolded", "", numSys+1);
        SVD_Array2Legend(legendrefold, dataHist, "Measured", "", numSys+1);  
        SVD_DrawStack(stackrefold, quantityTex, "Entries", "", 0); //, 134);
        legendrefold->Draw("SAME");
        canvas.Print(outputfilename); 
           
    
    
        // RATIO: Refolded versus Data 
        TLegend* legendRatioRefDat = SVD_NewLegend(CPQtex, SystTex, regPar, (int) doUseTau);
        THStack* stackRatioRefDat = new THStack("", "");   
        SVD_Array2Stack(stackRatioRefDat, histRatioRefDat, "E", 1, numSys+1);
        SVD_Array2Legend(legendRatioRefDat, histRatioRefDat, "Ref/Data", "", numSys+1);
        SVD_DrawStackRange(stackRatioRefDat, quantityTex, "Entries", 0.7, 1.5, "", 0);  
        legendRatioRefDat->Draw("SAME");
        canvas.Print(outputfilename);
    
      
        // Draw D-Plot 
        TLegend* legenddd = SVD_NewLegend(CPQtex, SystTex); 
        THStack* stackdd = new THStack("", "");
        gPad->SetLogy(true);
        SVD_Array2Stack(stackdd, ddHist, "HIST", 1, numSys+1);
        SVD_Array2Legend(legenddd, ddHist, "d-Values", "", numSys+1); 
        SVD_DrawStack(stackdd, quantityTex, "d-Values", "", 0);  
        legenddd->Draw("SAME");
        canvas.Print(outputfilename);
        gPad->SetLogy(false);
     
    
        // Draw SV Plot
        TLegend* legendsv = SVD_NewLegend(CPQtex, SystTex); 
        THStack* stacksv = new THStack("", "");
        gPad->SetLogy(true);
        SVD_Array2Stack(stacksv, svHist, "HIST", 1, numSys+1);
        SVD_Array2Legend(legendsv, svHist, "Sing. Values", "", numSys+1); 
        SVD_DrawStack(stacksv, quantityTex, "Sing. Values", "", 0);  
        legendsv->Draw("SAME");
        canvas.Print(outputfilename);
        gPad->SetLogy(false); 
     
    
    
        // Draw Stab, Eff, Pur 
        TLegend* legendspe = SVD_NewLegend(CPQtex, SystTex);  
        THStack* stackspe = new THStack("", ""); 
        SVD_EmptySideBins1D(effHist);
        SVD_Array2Stack(stackspe, purHist, "HIST", 3, numSys+1);
        SVD_Array2Stack(stackspe, stabHist, "HIST", 2, numSys+1);
        SVD_Array2Stack(stackspe, effHist, "HIST", 1, numSys+1);
        SVD_Array2Legend(legendspe, purHist, "Pur.", "", numSys+1); 
        SVD_Array2Legend(legendspe, stabHist, "Stab.", "", numSys+1); 
        SVD_Array2Legend(legendspe, effHist, "Eff.", "", numSys+1);  
        SVD_DrawStack(stackspe, quantityTex, "Pur., Stab., Eff. in \%", "", 0);
        legendspe->Draw("SAME");
        canvas.Print(outputfilename);
    
    
        // Draw BBB Efficiency 
        TLegend* legendeff = SVD_NewLegend(CPQtex, SystTex);  
        THStack* stackEff = new THStack("", ""); 
        SVD_EmptySideBins1D(beffHist); 
        SVD_Array2Stack(stackEff, beffHist, "HIST", 2, numSys+1);
        SVD_Array2Stack(stackEff, effHist, "HIST", 1, numSys+1);
        SVD_Array2Legend(legendeff, beffHist, "BBB-Eff.", "", numSys+1); 
        SVD_Array2Legend(legendeff, effHist, "Efficiency", "", numSys+1);  
        SVD_DrawStack(stackEff, quantityTex, "Efficiency \%", "", 0);
        legendeff->Draw("SAME");
        canvas.Print(outputfilename);
    
    
        // Covariance Matrix (DATA)
        // Only for the nominal sample
        SVD_Draw2D(dataCovHist, "COLZ");
        canvas.Print(outputfilename);
    
    
        // Covariance Matrix (STAT)
        // Only for the nominal sample
        SVD_Draw2D(statCovHist, "COLZ");
        canvas.Print(outputfilename);
    
    
        // Covariance Matrix (MC)
        // Only for the nominal sample
        SVD_Draw2D(mcCovHist, "COLZ");
        canvas.Print(outputfilename);
    
    
        // Covariance Matrix (Total)
        // Only for the nominal sample
        SVD_Draw2D(totCovHist, "COLZ");
        canvas.Print(outputfilename);
     
    
        // Correlation Matrix (STAT)
        // Only for the nominal sample
        SVD_Draw2D(statCorrHist, "COLZ TEXT");
        canvas.Print(outputfilename);
    
    
        // Correlation Matrix (MC)
        // Only for the nominal sample
        SVD_Draw2D(mcCorrHist, "COLZ TEXT");
        canvas.Print(outputfilename);
    
    
        // Correlation Matrix (Total)
        // Only for the nominal sample
        SVD_Draw2D(totCorrHist, "COLZ TEXT");
        canvas.Print(outputfilename);
         
    
     
        // GLOBAL CORRELATION STAT
        // Only for the nominal sample
        glcHist->UseCurrentStyle(); 
        TLegend* legendglc = SVD_NewLegend(CPQtex, "", regPar, (int) doUseTau); 
        THStack* stackglc = new THStack("", "");  
        legendglc->AddEntry(glcHist, "Glob. Corr. #rho_{i} in \%"); 
        stackglc->Add(glcHist); 
        SVD_DrawStack(stackglc, quantityTex, "Glob. Corr. #rho_{i} in \%", "HIST ", 4);
        canvas.Print(outputfilename);


    
    
        // Errors (STAT, BBB)
        // Only for the nominal sample
        TLegend* legenderr1 = SVD_NewLegend(CPQtex, "", regPar, (int) doUseTau);
        THStack* stackerr1 = new THStack("", ""); 
        legenderr1->AddEntry(statErrHist, "Unf. Unc.");
        legenderr1->AddEntry(bbbErrHist, "BBB Unc.");
        stackerr1->Add(statErrHist);
        stackerr1->Add(bbbErrHist);
        SVD_DrawStack(stackerr1, quantityTex, "Error in \%", "HIST ", 34); 
        legenderr1->Draw("SAME");
        canvas.Print(outputfilename);
    
    
        // Errors (STAT, MC, TOTAL)
        // Only for the nominal sample
        TLegend* legenderr2 = SVD_NewLegend(CPQtex, "", regPar, (int) doUseTau);
        THStack* stackerr2 = new THStack("", ""); 
        legenderr2->AddEntry(totErrHist, "Tot. Unc.");
        legenderr2->AddEntry(statErrHist, "Unf. Unc.");
        legenderr2->AddEntry(mcErrHist, "MC Unc.");
        stackerr2->Add(totErrHist);
        stackerr2->Add(statErrHist);
        stackerr2->Add(mcErrHist);
        SVD_DrawStack(stackerr2, quantityTex, "Error in \%", "HIST ", 134);
        legenderr2->Draw("SAME");
        canvas.Print(outputfilename);
    
    
        // RATIO: UnfErrors versus BBBErrors
        // Only for the nominal sample
        TLegend* legendRatioErrors = SVD_NewLegend(CPQtex, "", regPar, (int) doUseTau); 
        TString legendentryRatioErrors = "Err. Ratio";
        legendRatioErrors->AddEntry(histRatioErrors, legendentryRatioErrors);
        SVD_DrawRange(histRatioErrors, 0.3, 3., "p", 0);
        legendRatioErrors->Draw("SAME");
        canvas.Print(outputfilename);
        
        
        
        // Systematics Plots
        if ( doSystematics == true ) {
         
            // Syst Shifts in Comparison
            TLegend* legendSysShift = SVD_NewLegend(CPQtex, SystTex, regPar, (int) doUseTau);
            THStack* stackSysShift = new THStack("", ""); 
            SVD_Array2Stack(stackSysShift, unfShiftHist, "HIST", 1, numSys);
            SVD_Array2Stack(stackSysShift, bbbShiftHist, "HIST", 2, numSys);
            SVD_Array2Legend(legendSysShift, unfShiftHist, "Unfolding", "", numSys);
            SVD_Array2Legend(legendSysShift, bbbShiftHist, "BBB", "", numSys);
            SVD_DrawStackRange(stackSysShift, quantityTex, "Syst. Shift", 0.7, -1.4, "", 0); 
            legendSysShift->Draw("SAME");
            canvas.Print(outputfilename);
        
            // Shift Hist as Ratio
            TLegend* legendSysShiftRatio = SVD_NewLegend(CPQtex, SystTex, regPar, (int) doUseTau);
            THStack* stackSysShiftRatio = new THStack("", ""); 
            SVD_Array2Stack(stackSysShiftRatio, ratioShiftHist, "HIST", 1, numSys);
            SVD_Array2Legend(legendSysShiftRatio, ratioShiftHist, "Shift Unf/BBB", "", numSys);
            SVD_DrawStackRange(stackSysShiftRatio, quantityTex, "Syst. Shift Ratio", 0.7, -1.4, "", 0); 
            legendSysShiftRatio->Draw("SAME");
            canvas.Print(outputfilename);
            
            
        }    
    
        // K Scan Plots 
        // Only for the nominal sample
        if ( doKScan == true  ) {
         
             
            // Draw Unfolded distributions   
            TLegend* k_legunf = SVD_NewLegendK();
            THStack* k_stackunf = new THStack("", "");
            int kscancounter = 0;
            for ( int tmpK = 2 ; tmpK <= nScanSingularValues ; tmpK++ ) {  
                TH1D* tmpUnfResult = arrK_Mean + kscancounter;
                k_stackunf->Add(tmpUnfResult);
                k_legunf->AddEntry(tmpUnfResult, TString::Format("k=%i", tmpK));
                kscancounter++;
            }
            SVD_DrawStack(k_stackunf, quantityTex, "Unfolding Result x_{i}", "HIST ", -1);
            k_legunf->Draw("SAME");
            unfHist->SetMarkerColor(1);
            unfHist->Draw("SAME P");
            canvas.Print(outputfilename); 
            
            
         
             
            // Draw Error distributions   
            TLegend* k_legerr = SVD_NewLegendK();
            THStack* k_stackerr = new THStack("", "");
            kscancounter = 0;
            for ( int tmpK = 2 ; tmpK <= nScanSingularValues ; tmpK++ ) {  
                TH1D* tmpErr = arrK_StatError + kscancounter;
                k_stackerr->Add(tmpErr);
                k_legerr->AddEntry(tmpErr, TString::Format("k=%i", tmpK));
                kscancounter++;
            }
            SVD_DrawStack(k_stackerr, quantityTex, "Stat. Unc. #delta x_{i} in %", "HIST ", -1);
            k_legerr->Draw("SAME");
            statErrHist->SetMarkerColor(1);
            statErrHist->Draw("SAME P");
            canvas.Print(outputfilename); 
         
             
            // Draw Glob Corr distributions   
            TLegend* k_legglc = SVD_NewLegendK();
            THStack* k_stackglc = new THStack("", "");
            kscancounter = 0;
            for ( int tmpK = 2 ; tmpK <= nScanSingularValues ; tmpK++ ) {  
                TH1D* tmpGlC = arrK_GlC + kscancounter;
                k_stackglc->Add(tmpGlC);
                k_legglc->AddEntry(tmpGlC, TString::Format("k=%i", tmpK));
                kscancounter++;
            }
            SVD_DrawStack(k_stackglc, quantityTex, "Global Correlation #rho_{i} in %", "HIST ", -1);
            k_legglc->Draw("SAME");
            glcHist->SetMarkerColor(1);
            glcHist->Draw("SAME P");
            canvas.Print(outputfilename); 
            
            
            
         
             
            // Draw Weight distributions   
            TLegend* k_legweight = SVD_NewLegendK();
            THStack* k_stackweight = new THStack("", "");
            kscancounter = 0;
            for ( int tmpK = 2 ; tmpK <= nScanSingularValues ; tmpK++ ) {  
                TH1D* tmpWeights = arrK_Weight + kscancounter;
                k_stackweight->Add(tmpWeights);
                k_legweight->AddEntry(tmpWeights, TString::Format("k=%i", tmpK));
                kscancounter++;
            }
            SVD_DrawStack(k_stackweight, quantityTex, "Weights w_{i}", "HIST ", -1);
            k_legweight->Draw("SAME");
            weightHist->SetMarkerColor(1);
            weightHist->Draw("SAME P");
            canvas.Print(outputfilename); 
            
            
            // Delete all the obsolete objects
            // delete[] arrK_StatError;
            // delete[] arrK_Weight;
            // delete[] arrK_GlC;
            // delete[] arrK_Mean;
            // delete k_stackerr;
            // delete k_stackweight;
            // delete k_stackglc;
            // delete k_stackunf;

        }
    
        // Scan Plots
        // Only for the nominal sample
        if ( doScan == true && scanPlots == true ) {
                  
            // Logscale
            gPad->SetLogx(true); 
                  
            // Global Correlation Plot
            canvas.Clear();
            TH1D* bgrHisto = NULL;
            TGraph* gGlobCorr = SVD_Vect2Graph(vScanPoints, vGlobCorr); 
            SVD_DrawGraph(gGlobCorr,  bgrHisto, "P", 1);
            TString gGlobCorrStr = SVD_PlotName(channel, particle, quantity, special, syst, "scanGLOBC");
            SVD_SetTitles1D(bgrHisto, gGlobCorrStr, "Parameter #tau", "Averaged Global Correlation  #bar{#rho}  in %"); 
            TGraph* bestPoint = SVD_Point2Graph(optimalTauX, optimalTauY);
            SVD_DrawGraph(bestPoint,  bgrHisto, "P", 2); 
            bestPoint->SetMarkerSize(2.5); 
            bestPoint->SetMarkerStyle(3);
            SVD_DrawVertLines(bgrHisto, &vSingularValues, 2);
            TString textBestPoint = TString::Format("#tau = %.3f", optimalTauX);
            int textOrientationBestPoint = 23;
            TLatex* latexBestPoint = new TLatex();
            latexBestPoint->SetTextSize(0.03);
            latexBestPoint->SetTextColor(2); 
            double textPosBestPointX =  SVD_TextPosX(bgrHisto, optimalTauX, gPad->GetLogx(), textOrientationBestPoint);
            double textPosBestPointY =  SVD_TextPosY(bgrHisto, optimalTauY, gPad->GetLogy(), textOrientationBestPoint);
            SVD_DrawText(textBestPoint, textPosBestPointX, textPosBestPointY, textOrientationBestPoint, latexBestPoint); 
            canvas.Print(outputfilename); 
            delete gGlobCorr;
            delete bestPoint; 
            delete bgrHisto;
            delete latexBestPoint;
                  
                  
            // Chi Squared
            canvas.Clear();
            bgrHisto = NULL;
            TGraph* gChiSq = SVD_Vect2Graph(vScanPoints, vChiSq);
            SVD_DrawGraph(gChiSq,  bgrHisto, "P", 4); 
            bgrHisto->SetMaximum(2.*optimalChiSq); // Range 
            TString gChiSqStr = SVD_PlotName(channel, particle, quantity, special, syst, "scanCHI2A");
            SVD_SetTitles1D(bgrHisto, gChiSqStr, "Parameter #tau", "#chi^{2}");
            bestPoint = SVD_Point2Graph(optimalTauX, optimalChiSq);
            SVD_DrawGraph(bestPoint,  bgrHisto, "P", 2); 
            bestPoint->SetMarkerSize(2.5); 
            bestPoint->SetMarkerStyle(3);
            SVD_DrawVertLines(bgrHisto, &vSingularValues, 2);
            textBestPoint = TString::Format("#tau = %.3f", optimalTauX);
            textOrientationBestPoint = 31;
            latexBestPoint = new TLatex();
            latexBestPoint->SetTextSize(0.03);
            latexBestPoint->SetTextColor(2); 
            textPosBestPointX =  SVD_TextPosX(bgrHisto, optimalTauX, gPad->GetLogx(), textOrientationBestPoint);
            textPosBestPointY =  SVD_TextPosY(bgrHisto, optimalChiSq, gPad->GetLogy(), textOrientationBestPoint); 
            SVD_DrawText(textBestPoint, textPosBestPointX, textPosBestPointY, textOrientationBestPoint, latexBestPoint);  
            canvas.Print(outputfilename);
            delete gChiSq;
            delete bestPoint; 
            delete bgrHisto;
            delete latexBestPoint; 
                  
                  
            // Curvature
            canvas.Clear();
            bgrHisto = NULL;
            TGraph* gCurv = SVD_Vect2Graph(vScanPoints, vCurv);
            SVD_DrawGraph(gCurv,  bgrHisto, "P", 7); 
            TString gCurvStr = SVD_PlotName(channel, particle, quantity, special, syst, "scanCURV");
            SVD_SetTitles1D(bgrHisto, gCurvStr, "Parameter #tau", "Curvature x^{T}Cx");
            bestPoint = SVD_Point2Graph(optimalTauX, optimalCurv);
            SVD_DrawGraph(bestPoint,  bgrHisto, "P", 2); 
            bestPoint->SetMarkerSize(2.5); 
            bestPoint->SetMarkerStyle(3);
            SVD_DrawVertLines(bgrHisto, &vSingularValues, 2);
            textBestPoint = TString::Format("#tau = %.3f", optimalTauX);
            textOrientationBestPoint = 11;
            latexBestPoint = new TLatex();
            latexBestPoint->SetTextSize(0.03);
            latexBestPoint->SetTextColor(2); 
            textPosBestPointX =  SVD_TextPosX(bgrHisto, optimalTauX, gPad->GetLogx(), textOrientationBestPoint);
            textPosBestPointY =  SVD_TextPosY(bgrHisto, optimalCurv, gPad->GetLogy(), textOrientationBestPoint); 
            SVD_DrawText(textBestPoint, textPosBestPointX, textPosBestPointY, textOrientationBestPoint, latexBestPoint);  
            canvas.Print(outputfilename);
            delete gCurv;
            delete bestPoint; 
            delete bgrHisto;
            delete latexBestPoint;  
                  
                  
                  
                  
            // Avg Squared Error
            canvas.Clear();
            bgrHisto = NULL;
            TGraph* gAvgSqErr = SVD_Vect2Graph(vScanPoints, vAvgSqErr);
            SVD_DrawGraph(gAvgSqErr,  bgrHisto, "P", 3); 
            TString gAvgSqErrStr = SVD_PlotName(channel, particle, quantity, special, syst, "scanAVGERR");
            SVD_SetTitles1D(bgrHisto, gAvgSqErrStr, "Parameter #tau", "Avg. Sq. Stat. Error");
            bestPoint = SVD_Point2Graph(optimalTauX, optimalAvgSqErr);
            SVD_DrawGraph(bestPoint,  bgrHisto, "P", 2); 
            bestPoint->SetMarkerSize(2.5); 
            bestPoint->SetMarkerStyle(3);
            SVD_DrawVertLines(bgrHisto, &vSingularValues, 2);
            SVD_DrawHorizLine(bgrHisto, bbbAvgSqErr, 3);
            textBestPoint = TString::Format("#tau = %.3f", optimalTauX);
            textOrientationBestPoint = 11;
            latexBestPoint = new TLatex();
            latexBestPoint->SetTextSize(0.03);
            latexBestPoint->SetTextColor(2); 
            textPosBestPointX =  SVD_TextPosX(bgrHisto, optimalTauX, gPad->GetLogx(), textOrientationBestPoint);
            textPosBestPointY =  SVD_TextPosY(bgrHisto, optimalAvgSqErr, gPad->GetLogy(), textOrientationBestPoint); 
            SVD_DrawText(textBestPoint, textPosBestPointX, textPosBestPointY, textOrientationBestPoint, latexBestPoint);  
            canvas.Print(outputfilename);
            delete gAvgSqErr;
            delete bestPoint; 
            delete bgrHisto;
            delete latexBestPoint;
                  
                  
                  
                  
            // Avg Mean
            canvas.Clear();
            bgrHisto = NULL;
            TGraph* gAvgMean = SVD_Vect2Graph(vScanPoints, vAvgMean);
            SVD_DrawGraph(gAvgMean,  bgrHisto, "P", 6); 
            TString gAvgMeanStr = SVD_PlotName(channel, particle, quantity, special, syst, "scanAVGMEAN");
            SVD_SetTitles1D(bgrHisto, gAvgMeanStr, "Parameter #tau", "Average Bin Content");
            bestPoint = SVD_Point2Graph(optimalTauX, optimalAvgMean);
            SVD_DrawGraph(bestPoint,  bgrHisto, "P", 2); 
            bgrHisto->SetMaximum(1.3*(*vAvgMean).Max()); // Range 
            bgrHisto->SetMinimum(0.8*(*vAvgMean).Min()); // Range 
            bestPoint->SetMarkerSize(2.5); 
            bestPoint->SetMarkerStyle(3);
            SVD_DrawVertLines(bgrHisto, &vSingularValues, 2);
            SVD_DrawHorizLine(bgrHisto, bbbAvgMean, 3);
            textBestPoint = TString::Format("#tau = %.3f", optimalTauX);
            textOrientationBestPoint = 23;
            latexBestPoint = new TLatex();
            latexBestPoint->SetTextSize(0.03);
            latexBestPoint->SetTextColor(2); 
            textPosBestPointX =  SVD_TextPosX(bgrHisto, optimalTauX, gPad->GetLogx(), textOrientationBestPoint);
            textPosBestPointY =  SVD_TextPosY(bgrHisto, optimalAvgMean, gPad->GetLogy(), textOrientationBestPoint); 
            SVD_DrawText(textBestPoint, textPosBestPointX, textPosBestPointY, textOrientationBestPoint, latexBestPoint);  
            canvas.Print(outputfilename);
            delete gAvgMean;
            delete bestPoint; 
            delete bgrHisto;
            delete latexBestPoint;   
                  
                  
            // Logscale
            gPad->SetLogx(false);
        } 
        
 
        // Last page empty
        canvas.Clear();
        canvas.Print(outputfilename.Copy().Append(")"));
    
    
        // Reset Style
        setHHStyle(*gStyle); 
        TGaxis::SetMaxDigits(2);
    
    
        // Delete Legends
        delete legendinp;
        delete legendbgr;
        delete legendweight;
        delete legendunf;
        delete legendRatioUnfBBB;
        delete legendrefold; 
        delete legendRatioRefDat;
        delete legenddd;
        delete legendsv;
        delete legendspe;
        delete legendeff;
        delete legendglc;
        delete legenderr1;
        delete legenderr2;
        delete legendRatioErrors;
    
        // Delete Stacks
        delete stackinp;
        delete stackbgr;
        delete stackweight;
        delete stackunf;
        delete stackrefold;
        delete stackspe;
        delete stackEff;
        delete stackerr1;
        delete stackerr2; 
            
            
            
        // Delete Canvas
        //canvas.Clear(); 
        

    }
  
    //////////////////////////////////////////////////////////
    ///////////   SAVE TO ROOT FILE //////////////////////////
    //////////////////////////////////////////////////////////


    // Save all relevant Plots in ROOT File
    if ( plotsToRoot == true ) {
    
       
        // Open a ROOT file 
        TFile* file = new TFile(rootFile, "RECREATE");
    
    
        // Save Histograms
        rawHist->Write();
        bgrHist->Write();
        dataHist->Write();
        mcHist->Write();
        xiniHist->Write();
        biniHist->Write();
        beffHist->Write();        
        bbbHist->Write();
        dataCovHist->Write();
        unfHist->Write();
        statCovHist->Write();
        mcCovHist->Write();
        totCovHist->Write();
        purHist->Write();
        stabHist->Write();        
        effHist->Write(); 
        histRatioUnfBBB->Write();
        refoldHist->Write();
        histRatioRefDat->Write();
        ddHist->Write();
        svHist->Write();
        statErrHist->Write();
        mcErrHist->Write();
        totErrHist->Write();
        histRatioErrors->Write();
        statCorrHist->Write();
        mcCorrHist->Write();
        totCorrHist->Write();
        glcHist->Write();
    
        // Close file
        file->Close();
 
 
    }      
              
    // return 
    return optimalTauX;
                
    // Delete all old histograms
    delete rawHist;
    delete bgrHist;
    delete dataHist;
    delete mcHist;
    delete xiniHist;
    delete biniHist;
    delete beffHist;
    delete bbbHist;
    delete dataCovHist;
    delete unfHist;
    delete statCovHist;
    delete mcCovHist;
    delete totCovHist;
    delete purHist;
    delete stabHist;
    delete effHist;
    delete histRatioUnfBBB;
    delete refoldHist;
    delete histRatioRefDat;
    delete ddHist;
    delete svHist;
    delete statErrHist;
    delete mcErrHist;
    delete totErrHist;
    delete histRatioErrors;
    delete statCorrHist;
    delete mcCorrHist;
    delete totCorrHist;
    delete glcHist;


    // Delete TopSVDUnfold-Objekt
    delete mySVDUnfold;

    // restore gErrorIgnoreLv
    gErrorIgnoreLevel=initialgErrorLv;

    // return 
    return optimalTauX;
      
}
 

 
