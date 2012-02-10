# include "TopSVDFunctions.h"

////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////    Function Definitions  ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////



// SVD Unfolding Helper Function
TString TopSVDFunctions::SVD_CPQS(TString channel, TString particle, TString quantity, TString special)
{
    TString cpq = ""; 
    cpq.Append(channel);
    cpq.Append("_");
    cpq.Append(particle);
    cpq.Append("_");
    cpq.Append(quantity);
    if ( special.CompareTo("") != 0 ) {
    	cpq.Append("_");
        cpq.Append(special);
    }
    return cpq;
}


// Create a name for a plot according to a certain scheme
// This name will be used for saving the histogram in a root file
TString TopSVDFunctions::SVD_PlotName(TString channel, TString particle, TString quantity, TString special, TString plotName)
{
    TString rawStr("SVD_");
    rawStr.Append(SVD_CPQS(channel, particle, quantity, special));
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


// Helper Function to create a nicely formatted
// legend. 
TLegend* TopSVDFunctions::SVD_NewLegend() {

    TLegend *leg = new TLegend();
    leg->SetX1NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength()-0.25);
    leg->SetY1NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength()-0.15);
    leg->SetX2NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength());
    leg->SetY2NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength());
    leg->SetTextFont(42);
    leg->SetTextSize(0.04);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextAlign(12);

    return leg;

} 


// Move Events in OF/UF bins in dedicated side bins.
// Attention: Sidebins need to be created first
// Error recalculated in Poisson manner.
void TopSVDFunctions::SVD_MoveOFBins1D(TH1D* hist){
    int nBins = hist->GetNbinsX();

    // Count OF Events 
    double ufBin = hist->GetBinContent(0);
    ufBin += hist->GetBinContent(1);
    double ofBin = hist->GetBinContent(nBins+1);
    ofBin += hist->GetBinContent(nBins);

    // Set Side Bins
    hist->SetBinContent(0, 0.);
    hist->SetBinContent(1, ufBin);
    hist->SetBinContent(nBins, ofBin);
    hist->SetBinContent(nBins+1, 0.);

    // Set Side Bins / Error
    hist->SetBinError(0, 0.);
    hist->SetBinError(1, 0.);
    hist->SetBinError(nBins, 0.);
    hist->SetBinError(nBins+1, 0.);
    if ( ufBin > 0. ) {
        hist->SetBinError(1, TMath::Sqrt(ufBin));
    }
    if ( ofBin > 0. ) {
        hist->SetBinError(nBins, TMath::Sqrt(ofBin));
    }
}




// Move Events in OF/UF bins in dedicated side bins
// Attention: Sidebins need to be created first
// Error recalculated in Possion manner
void TopSVDFunctions::SVD_MoveOFBins2D(TH2D* hist){
    int nBinsx = hist->GetNbinsX();
    int nBinsy = hist->GetNbinsY();


    // Loop over bins in X direction
    for ( int i = 0 ; i < nBinsx+2 ; i++ ) {

         // Count OF Events
        double ufBin = hist->GetBinContent(i,0);
        ufBin += hist->GetBinContent(i,1);
        double ofBin = hist->GetBinContent(i,nBinsy+1);
        ofBin += hist->GetBinContent(i,nBinsy);
    
        // Set Side Bins
        hist->SetBinContent(i, 0, 0.);
        hist->SetBinContent(i, 1, ufBin);
        hist->SetBinContent(i, nBinsy, ofBin);
        hist->SetBinContent(i, nBinsy+1, 0.);
    
        // Set Side Bins / Error
        hist->SetBinError(i, 0, 0.);
        hist->SetBinError(i, 1, 0.);
        hist->SetBinError(i, nBinsy, 0.);
        hist->SetBinError(i, nBinsy+1, 0.);
        if ( ufBin > 0. ) {
            hist->SetBinError(i, 1, TMath::Sqrt(ufBin));
        }
        if ( ofBin > 0. ) {
            hist->SetBinError(i, nBinsy, TMath::Sqrt(ofBin));
        }
    }

    // Now, loop over bins in Y direction
    // The first and last row should be empty already
    // But this does not hurt
    for ( int i = 0 ; i < nBinsy+2 ; i++ ) {

         // Count OF Events
        double ufBin = hist->GetBinContent(0,i);
        ufBin += hist->GetBinContent(1,i);
        double ofBin = hist->GetBinContent(nBinsx+1,i);
        ofBin += hist->GetBinContent(nBinsx,i);

        // Set Side Bins
        hist->SetBinContent(0, i, 0.);
        hist->SetBinContent(1, i, ufBin);
        hist->SetBinContent(nBinsx,   i, ofBin);
        hist->SetBinContent(nBinsx+1, i, 0.);

        // Set Side Bins / Error
        hist->SetBinError(0, i, 0.);
        hist->SetBinError(1, i, 0.);
        hist->SetBinError(nBinsx, i, 0.);
        hist->SetBinError(nBinsx+1, i, 0.);
        if ( ufBin > 0. ) {
            hist->SetBinError(1, i, TMath::Sqrt(ufBin));
        }
        if ( ofBin > 0. ) {
            hist->SetBinError(nBinsx, i, TMath::Sqrt(ofBin));
        }
    }
}





// This empties the dedicated side bins.
// Should be called for reconstructed quantities.
// Histogram side bins are also emptied.
void TopSVDFunctions::SVD_EmptySideBins1D(TH1D* histo) 
{
    int bins = histo->GetNbinsX();
    histo->SetBinContent(0, 0.);
    histo->SetBinContent(1, 0.);
    histo->SetBinContent(bins, 0.);    
    histo->SetBinContent(bins+1, 0.);
    histo->SetBinError(0, 0.);
    histo->SetBinError(1, 0.);
    histo->SetBinError(bins, 0.);
    histo->SetBinError(bins+1, 0.);
}






// This empties the dedicated side bins.
// Should be called for reconstructed quantities,
// which are assumed to be on X axis.
// Histogram side bins are also emptied.
void TopSVDFunctions::SVD_EmptySideBins2D(TH2D* histo)
{
    int binsx = histo->GetNbinsX();
    int binsy = histo->GetNbinsY();

    // Loop over generated bins (on Y axis)
    for ( int j = 0 ; j < binsy+2 ; j++ ) {

        // emtpy it all
        histo->SetBinContent(0, j, 0.);
        histo->SetBinContent(1, j, 0.);
        histo->SetBinContent(binsx, j, 0.);
        histo->SetBinContent(binsx+1, j, 0.);
        histo->SetBinError(0, j, 0.);
        histo->SetBinError(1, j, 0.);
        histo->SetBinError(binsx, j, 0.);
        histo->SetBinError(binsx+1, j, 0.);
    }

}

 


// Rebinning of a 1D Histogram. Creates a new histogram
// on the heap. So dont forget to delete it sometimes.
TH1D* TopSVDFunctions::SVD_Rebin1D(TH1* input, int nbinsx, double* binsx)
{
    // Create new histo on the heap
    TString nameNewHist = input->GetName();
    nameNewHist.Append("Rebinned");
    TH1D* outputhist = new TH1D(nameNewHist, nameNewHist, nbinsx, binsx);
    int nbinsOld =input->GetNbinsX();
    
    // Loop over all bins including OF and UF
    for(int i=0; i<nbinsx+2; ++i){

        // Find bin boundaries in X
        int nxlow = -1;
        int nxhigh = -1;
        if ( i == 0 ) {   // UF bin in X
            nxlow = 0;
            double xhigh = binsx[0];
            nxhigh = input->GetXaxis()->FindBin(xhigh)-1;
        }
        if ( i == nbinsx+1 ) {  // OF bin in X
            double xlow = binsx[nbinsx];
            nxlow = input->GetXaxis()->FindBin(xlow);
            nxhigh = nbinsOld;
        }
        if ( i > 0 && i < nbinsx+1) {
            double xlow = binsx[i-1];
            double xhigh = binsx[i];
            nxlow = input->GetXaxis()->FindBin(xlow);
            nxhigh = input->GetXaxis()->FindBin(xhigh)-1;
        }

        // Integrate over all the original bins
        double integral = 0.;
        if ( nxlow <= nxhigh ) {
            integral = ((TH2D*)input)->Integral(nxlow, nxhigh);
        } else {
            integral = 0.;
        }

        // Save it, thereby transpose if needed
        outputhist->SetBinContent(i, integral);
    }

    // Return it
    return outputhist;
}




// Rebinning of a 2D Histogram. Creates a new histogram
// on the heap. So dont forget to delete it sometimes.
// If needed, you can transpose the matrix, too. 
TH2D* TopSVDFunctions::SVD_Rebin2D(TH1* input, int nbinsx, double* binsx, int nbinsy, double* binsy, bool transpose)
{
    // Create new histo on the heap
    TString nameNewHist = input->GetName();
    nameNewHist.Append("Rebinned");
    TH2D* outputhist = new TH2D(nameNewHist, nameNewHist, nbinsx, binsx, nbinsy, binsy);
    int nbinsGenRecX =input->GetNbinsX();
    int nbinsGenRecY =input->GetNbinsY();

    // Loop over all bins including OF and UF
    for(int i=0; i<nbinsx+2; ++i){
        for(int j=0; j<nbinsy+2; ++j){

            // Find bin boundaries in X
            int nxlow = -1;
            int nxhigh = -1;
            if ( i == 0 ) {   // UF bin in X
                nxlow = 0;
                double xhigh = binsx[0];
                nxhigh = input->GetXaxis()->FindBin(xhigh)-1;
            }
            if ( i == nbinsx+1 ) {  // OF bin in X
                double xlow = binsx[nbinsx];
                nxlow = input->GetXaxis()->FindBin(xlow);
                nxhigh = nbinsGenRecX;
            }
            if ( i > 0 && i < nbinsx+1) {
                double xlow = binsx[i-1];
                double xhigh = binsx[i];
                nxlow = input->GetXaxis()->FindBin(xlow);
                nxhigh = input->GetXaxis()->FindBin(xhigh)-1;
            }

            // Find bin boundaries in Y
            int nylow = -1;
            int nyhigh = -1;
            if ( j == 0 ) {  // UF bin in Y
                nylow = 0;
                double yhigh = binsy[0];
                nyhigh = input->GetYaxis()->FindBin(yhigh)-1;

            }
            if ( j == nbinsy+1 ) {   // UF bin in Y
                double ylow = binsy[nbinsy];
                nylow = input->GetYaxis()->FindBin(ylow);
                nyhigh = nbinsGenRecY;
            }
            if ( j > 0 && j < nbinsy+1) {
                double ylow = binsy[j-1];
                double yhigh = binsy[j];
                nylow = input->GetYaxis()->FindBin(ylow);
                nyhigh = input->GetYaxis()->FindBin(yhigh)-1;
            }

            // Integrate over all the original bins
            double integral = 0.;
            if ( nxlow <= nxhigh && nylow <= nyhigh ) {
                integral = ((TH2D*)input)->Integral(nxlow, nxhigh, nylow, nyhigh);
            } else {
                integral = 0.;
            }

            // Save it, thereby transpose if needed
            if ( transpose == true ) {
                outputhist->SetBinContent(j, i, integral);
            } else {
                outputhist->SetBinContent(i, j, integral);
            }
        }
    }

    // return it
    return outputhist;
                	
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
TH1D* TopSVDFunctions::SVD_MakeRatioNum(TH1D* numerator, TH1D* denominator)
{

    // Create new Histogram
    TH1D* hist = (TH1D*) numerator->Clone("ratio");


    // Fill Histogram
    int numbins = hist->GetNbinsX();
    for ( int i = 0 ; i < numbins ; i++) {
        double num = numerator->GetBinContent(i);
        double denom = denominator->GetBinContent(i);
        double abs = numerator->GetBinError(i);
        double val = 0.;
        double err = 0.;
        if ( denom != 0. && num != 0.) {
            val = num / denom;
            err = abs / num;
        }
        hist->SetBinContent(i, val);
        hist->SetBinError(i, err);
    }

    
    return hist;

}        


// SVD Unfolding Helper FUnction
// Creates a Ratio plot of two histograms
// Errors: relative errors from the DENOMINATOR are taken
// Boundaries: If ymax < ymin, then range will be set automatically
TH1D* TopSVDFunctions::SVD_MakeRatioDenom(TH1D* numerator, TH1D* denominator)
{

    // Create new Histogram
    TH1D* hist = (TH1D*) numerator->Clone("ratio");


    // Fill Histogram
    int numbins = hist->GetNbinsX();
    for ( int i = 0 ; i < numbins ; i++) {
        double num = numerator->GetBinContent(i);
        double denom = denominator->GetBinContent(i);
        double abs = denominator->GetBinError(i);
        double val = 0.;
        double err = 0.;
        if ( denom != 0. ) {
            val = num / denom;
            err = abs / denom;
        }
        hist->SetBinContent(i, val);
        hist->SetBinError(i, err);
    }


    return hist;

}
             




// Formats a Stack of Histos to the current style
// The last argument takes integers between 1 and 9 for the colors, i.e.
// cols=243 means: First Histogram red, second blue, and third green 
// cols<=0 means: Standard palette. Do not fill a stack with more than nine histograms
void TopSVDFunctions::SVD_DrawStack(THStack* stack, TString xTitle, TString yTitle, TString options, int cols)
{
    
    // Calculate Colors
    int theColors[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    if ( cols > 0 ) { 
        // Get Num Digits
        int numdigits = 1;
        int colstmp1 = cols;
        while ( (colstmp1=colstmp1/10)>0 ) { numdigits++; }
        // Loop over digits
        int colstmp2 = cols;
        for ( int i = 0 ; i < numdigits ; i++ ) {
            if ( i >= 9 ) break; 
            int position = numdigits-1-i;
            int lastdigit = colstmp2 % 10;
            theColors[position] = lastdigit;
            colstmp2=colstmp2/10;
        }
    }


    // Loop over all histos
    // Set Colors and make cosmetic changes 
    TH2D* histo = NULL;
    int cnt = 0;
    TList* listHistos = stack->GetHists();
    TListIter iter(listHistos);
    while ( (histo = (TH2D*) iter.Next()) != NULL ) {
         histo->UseCurrentStyle();
         if ( cnt < 9 ) histo->SetLineColor(theColors[cnt]);
         if ( cnt < 9 ) histo->SetMarkerColor(theColors[cnt]);
         cnt++;
    } 


    // Draw it
    stack->Draw(options);

    // Style
    stack->GetHistogram()->UseCurrentStyle();

    // Titles
    stack->GetHistogram()->GetXaxis()->SetTitle(xTitle);
    stack->GetHistogram()->GetYaxis()->SetTitle(yTitle);

    // Y Range
    double ymin = stack->GetHistogram()->GetMinimum();
    double ymax = stack->GetHistogram()->GetMaximum();
    double newYRange = 1.3 * (ymax -ymin);
    stack->SetMaximum(ymin+newYRange);

}



// Set Name, Title and Axis Titles
// note: The Title is set to the value of name
void TopSVDFunctions::SVD_SetTitles1D(TH1D* histo, TString name, TString xTitle, TString yTitle)
{
    histo->SetName(name);
    histo->SetTitle(name);
    histo->GetXaxis()->SetTitle(xTitle);
    histo->GetYaxis()->SetTitle(yTitle);

}




// Set Name, Title and Axis Titles
// note: The Title is set to the value of name
void TopSVDFunctions::SVD_SetTitles2D(TH2D* histo, TString name, TString xTitle, TString yTitle, TString zTitle)
{
    histo->SetName(name);
    histo->SetTitle(name);
    histo->GetXaxis()->SetTitle(xTitle);
    histo->GetYaxis()->SetTitle(yTitle);
    histo->GetZaxis()->SetTitle(zTitle);
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



// PERFORM UNFOLDING 
// Note: This function can do both, BBB and SVD Unfolding.
// If kreg > 0:
//       SVD Unfolding is done with 'kreg'
//       and the result of SVD Unfolding is returned in 'unfolded'
// If kreg <= 0:
//       BBB Unfolding is returned in 'unfolded' 
// If you specify filenames, plots will be drawn and saved.
int TopSVDFunctions::SVD_Unfold(
        TH1* dataInputHist,                     // Data Input (RAW Data including the background)
        TH1* bgrInputHist,                      // Background (will be substracted from data)
        TH1* genInputHist,                      // Generated MC
        TH1* recInputHist,                      // Reconstructed MC
        TH1* respInputHist,                     // Response Matrix 
        const double thebins[],                 // Binning for the unfolding
        const int numbins,                      // Number of bins for unfolding (not counting OF bins !!!)
        int kreg,                               // Regularization parameter
        TH1D*& unfolded,                        // Returned: Unfolded Distribution.
        TString channel,                        // Specify Name for the Channel ("mumu", "emu", "ee" ...)
        TString particle,                       // Specify Name for the Physics Object ("Top", "Jets", "Leptons")
        TString quantity,                       // Specify Name for the Quantity ("Eta", "Pt", or "Mass");
        TString special,                        // Specify Name for special run of unfolding
        TString channelTex,                     // Nicely formatted name for the channel
        TString particleTex,                    // Nicely formatted name for the physics object
        TString quantityTex,                    // Nicely formatted name for ithe quantity
        TString specialTex,                     // Nicely formatted name indicating some special condition 
        TString rootFile,                       // If specified, plots will be saved in ROOT File
        TString psFile                          // If specified, plots will be saved in PS File
)
{

    // Number of Pseudo Experiments for the error calculation    
    int nExperiments = 1000;
     

    // BBB or SVD? 
    bool doSVD = false;
    if ( kreg > 0 ) doSVD = true;


    // Plotting flags
    bool plotsToRoot = false;
    if ( !rootFile.CompareTo("")==0 ) plotsToRoot = true;
    bool plotsToPs = false;
    if ( !psFile.CompareTo("")==0 ) plotsToPs = true;
    bool doAllPlots = false;
    if ( plotsToRoot == true || plotsToPs == true ) doAllPlots = true;


    // Prepare the binning 
    int nbins = numbins + 2;
    double bins[nbins+1];
    double binwidthup = thebins[numbins] - thebins[numbins-1];
    double binwidthdown = thebins[1] - thebins[0];
    bins[0]       = thebins[0] - binwidthdown;
    bins[nbins]   = thebins[numbins] + binwidthup;
    for ( int i = 1 ; i < nbins ; i++ ) {
        bins[i]   = thebins[i-1];
    }


     
    //////////////////////////////////////////////////////
    /////////  P R E P A R E    I N P U T   //////////////
    //////////////////////////////////////////////////////



    // DATA rebinned, with background
    TH1D* rawHist = SVD_Rebin1D(dataInputHist, nbins, bins);
    SVD_EmptySideBins1D(rawHist);



    // BACKGROUND SIGNAL
    TH1D* bgrHist = SVD_Rebin1D((TH1D*) bgrInputHist, nbins, bins);
    SVD_EmptySideBins1D(bgrHist);


    
    // BACKGROUND SUBSTRACTION FROM DATA
    TH1D* dataHist = (TH1D*) rawHist->Clone("dataHist");
    dataHist->Add(bgrHist, -1.);
    SVD_EmptySideBins1D(dataHist);



    // REBINNING of Response Matrix
    // ... thereby transposing it
    TH2D* mcHist = SVD_Rebin2D((TH2D*) respInputHist, nbins, bins, nbins, bins, true); 
    SVD_MoveOFBins2D(mcHist);
    SVD_EmptySideBins2D(mcHist);


 
    // XINI (MC truth) rebinned 
    TH1D* xiniHist = SVD_Rebin1D((TH1D*) genInputHist, nbins, bins);
    SVD_MoveOFBins1D(xiniHist);

    

    // BINI (reconstructed MC signal) rebinned
    TH1D* biniHist = SVD_Rebin1D((TH1D*) recInputHist, nbins, bins);
    SVD_EmptySideBins1D(biniHist);



    ///////////////////////////////////////////////////////////////////
    ////////////   U N F O L D I N G //////////////////////////////////
    ///////////////////////////////////////////////////////////////////

 

    // BBB-Efficiency
    TH1D* beffHist = (TH1D*) biniHist->Clone("beffHist");
    for ( int i = 1 ; i < nbins+1 ; i++ ) {
        double numerator = biniHist->GetBinContent(i);
        double denominator = xiniHist->GetBinContent(i);
        double numeratorErr = biniHist->GetBinError(i);
        double denominatorErr = xiniHist->GetBinError(i);
        double bbbeff = 0.;
        double bbbeffErr = 0.;
        if ( denominator > 0. && numerator > 0.) {
            bbbeff = numerator / denominator;
            double bbbeffErrRelSq = 0.;
            bbbeffErrRelSq += TMath::Power(numeratorErr/numerator, 2.);
            bbbeffErrRelSq += TMath::Power(denominatorErr/denominator, 2.);
            bbbeffErr = bbbeff * TMath::Sqrt(bbbeffErrRelSq);
        }
        beffHist->SetBinContent(i,bbbeff);
        beffHist->SetBinError(i,bbbeffErr);
    }


    // First BBB Unfolding  ... use bbb Efficiency  
    TH1D* bbbHist = (TH1D*) dataHist->Clone("bbbHist");
    for ( int i = 1 ; i <= nbins ; i++ ) {
        double numerator = dataHist->GetBinContent(i);
        double denominator = beffHist->GetBinContent(i);
        double numeratorErr = dataHist->GetBinError(i);
        double denominatorErr = beffHist->GetBinError(i);
        double bbbunf = 0.;
        double bbbunfErr = 0.;
        if ( denominator > 0. && numerator > 0.) {
            bbbunf = numerator / denominator;
            double bbbunfErrRelSq = 0.;
            bbbunfErrRelSq += TMath::Power(numeratorErr/numerator, 2.);
            bbbunfErrRelSq += TMath::Power(denominatorErr/denominator, 2.);
            bbbunfErr = bbbunf * TMath::Sqrt(bbbunfErrRelSq);
        }
        bbbHist->SetBinContent(i,bbbunf);
        bbbHist->SetBinError(i,bbbunfErr);
    }
  
 

    // DATA COVARIANCE
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


    // FINALLY ....
    // SETUP UNFOLDING TOOL
    TopSVDUnfold *mySVDUnfold = new TopSVDUnfold(dataHist, biniHist, xiniHist, mcHist);
    mySVDUnfold->SetNormalize(false);



    // THE UNFOLDING with chosen regularization
    cout << "Unfolding " << channel << "/" << quantity << "/" << particle << "/" << special << " with k=" << TMath::Abs(kreg) << " ... " << endl;
    TH1D* unfHist = mySVDUnfold->Unfold(TMath::Abs(kreg));
    cout << "Unfolding done!" << endl;


    // Calculate TOTAL COVARIANCE
    TH2D* statCovHist = mySVDUnfold->GetUnfoldCovMatrix(dataCovHist , nExperiments);
    TH2D* mcCovHist = mySVDUnfold->GetAdetCovMatrix(nExperiments);
    TH2D* totCovHist = (TH2D*) statCovHist->Clone("totCovHist");
    totCovHist->Add(mcCovHist);


    // STAT ERROR ON RESULT
    // Save the diagonal elements of the statistical
    // covariance matrix in the histogram with
    // with the results ('unfHist')
    for ( int i = 1 ; i <= nbins ; i++ ) {
        double errorsq = statCovHist->GetBinContent(i,i);
        double error = 0.;
        if ( errorsq > 0. ) {
            error = TMath::Sqrt(errorsq);
        }
        unfHist->SetBinError(i, error);
    }




    /////////////////////////////////////////////////////
    ////////////   FORMATTING   /////////////////////////
    /////////////////////////////////////////////////////
 
 
    // Strings
    if ( channel.CompareTo("") == 0 ) channel.Append("channel");
    if ( particle.CompareTo("") == 0 ) particle.Append("particle");
    if ( quantity.CompareTo("") == 0 ) quantity.Append("quantity");
    if ( special.CompareTo("") == 0 ) quantity.Append("");
    if ( channelTex.CompareTo("") == 0 ) channelTex.Append("channelTex");
    if ( particleTex.CompareTo("") == 0 ) particleTex.Append("particleTex");
    if ( quantityTex.CompareTo("") == 0 ) quantityTex.Append("quantityTex");
    if ( specialTex.CompareTo("") == 0 ) specialTex.Append("");
 
   
    // Format BBB Plot
    TString bbbStr = SVD_PlotName(channel, particle, quantity, special, "BBB");
    SVD_SetTitles1D(bbbHist, bbbStr, quantityTex, "Events");

    
    // Format SVD Plot
    TString unfStr = SVD_PlotName(channel, particle, quantity, special, "UNF");
    SVD_SetTitles1D(unfHist, unfStr, quantityTex, "Events");
 

    // Set Pointer
    if ( doSVD == true ) unfolded = (TH1D*) unfHist->Clone(unfStr.Append("_Returned"));
    if ( doSVD == false ) unfolded = (TH1D*) bbbHist->Clone(bbbStr.Append("_Returned"));



    // RETURN 
    // If no more plots are needed, return now 
    if ( doAllPlots == false ) return 0;


    // Format Covariance Matrix
    TString dataCovStr = SVD_PlotName(channel, particle, quantity, special, "DATACOV");
    SVD_SetTitles2D(dataCovHist, dataCovStr, quantityTex, quantityTex, "Covariance on Measurements"); 
    

    // Format Raw Data
    TString rawStr = SVD_PlotName(channel, particle, quantity, special, "YRAW");
    SVD_SetTitles1D(rawHist, rawStr, quantityTex, "Events");


    // Format Bgr  
    TString bgrStr = SVD_PlotName(channel, particle, quantity, special, "YBGR");
    SVD_SetTitles1D(bgrHist, bgrStr, quantityTex, "Events");


    // Format Data
    TString dataStr = SVD_PlotName(channel, particle, quantity, special, "YDAT");
    SVD_SetTitles1D(dataHist, dataStr, quantityTex, "Events");


    // Format Response Matrix
    TString mcStr = SVD_PlotName(channel, particle, quantity, special, "AA");
    TString mcStrX = quantityTex;
    mcStrX.Append(" (Reconstructed)");
    TString mcStrY = quantityTex;
    mcStrY.Append(" (Generated)");
    TString mcStrZ("Entries");
    SVD_SetTitles2D(mcHist, mcStr, mcStrX, mcStrY, mcStrZ);


    // Format Gen MC
    TString xiniStr = SVD_PlotName(channel, particle, quantity, special, "XGEN");
    SVD_SetTitles1D(xiniHist, xiniStr, quantityTex, "Events");
 

    // Format Rec MC
    TString biniStr = SVD_PlotName(channel, particle, quantity, special, "XREC");
    SVD_SetTitles1D(biniHist, biniStr, quantityTex, "Events");


    // Format BBB Eff
    TString beffStr = SVD_PlotName(channel, particle, quantity, special, "BBBEFF");    
    SVD_SetTitles1D(beffHist, beffStr, quantityTex, "Bin by Bin Efficiency");

    
    // Format Stat COV
    TString statCovStr = SVD_PlotName(channel, particle, quantity, special, "STATCOV");
    SVD_SetTitles2D(statCovHist, statCovStr, quantityTex, quantityTex, "Statistical Covariance");


    // Format MC COV 
    TString mcCovStr = SVD_PlotName(channel, particle, quantity, special, "MCCOV");
    SVD_SetTitles2D(mcCovHist, mcCovStr, quantityTex, quantityTex, "Monte Carlo Covariance");


    // Format Tot COV
    TString totCovStr = SVD_PlotName(channel, particle, quantity, special, "TOTCOV");
    SVD_SetTitles2D(totCovHist, totCovStr, quantityTex, quantityTex, "Monte Carlo Covariance");

    
    ///////////////////////////////////////////////////////////////
    ////////   E X T R A     P L O T S    /////////////////////////
    ///////////////////////////////////////////////////////////////


    // PURITY
    // Note: Purity is set to zero, if number of reconstructed
    // events in a bin is zero
    TString purStr = SVD_PlotName(channel, particle, quantity, special, "PUR");
    TH1D* purHist = (TH1D*) biniHist->Clone(purStr);
    for ( int i = 1 ; i < nbins+1 ; i++ ) {
        double numerator = mcHist->GetBinContent(i, i);

        // Sum over all Gen Level bins INCLUDING OF bins
        double denominator = 0.;
        for ( int j = 1 ; j < nbins+1 ; j++ ) {
            denominator += mcHist->GetBinContent(i, j);
        }

        //double denominator = biniHist->GetBinContent(i);
        double purity = SVD_Divide(numerator, denominator);
        purHist->SetBinContent(i,purity);
        purHist->SetBinError(i, 0.);
    }
    SVD_SetTitles1D(purHist, purStr, quantityTex, "Purity");



    // STABILITY
    // Note: Stability is set to zero, if there are no
    // gerenated events in a b_Unfoldin.
    // Note: If there is no reconstructed event in this bin,
    // then the stability is naturally zero, too
    TString stabStr = SVD_PlotName(channel, particle, quantity, special, "STAB");
    TH1D* stabHist = (TH1D*) biniHist->Clone(stabStr);
    for ( int i = 1 ; i < nbins+1 ; i++ ) {
        double numerator = mcHist->GetBinContent(i, i);

        // Sum over all Rec Level bins EXCEPT OF bins
        double denominator = 0.;
        for ( int j = 1 ; j < nbins+1 ; j++ ) {
            if ( j == 1 ) continue;
            if ( j == nbins ) continue;
            denominator += mcHist->GetBinContent(j, i);
        }

        //double denominator = xiniHist->GetBinContent(i);
        double stability = SVD_Divide(numerator, denominator);
        stabHist->SetBinContent(i,stability);
        stabHist->SetBinError(i, 0.);
    }
    SVD_SetTitles1D(stabHist, stabStr, quantityTex, "Stability");



    // EFFICIENCY
    // Note: If no generated events are available in a bin,
    // then the efficiency is set to zero
    TString effStr = SVD_PlotName(channel, particle, quantity, special, "EFF");
    TH1D* effHist = (TH1D*) biniHist->Clone(effStr);
    for ( int i = 1 ; i <= nbins ; i++ ) {
        double denominator = xiniHist->GetBinContent(i);
        double numerator = 0.;
        for ( int j = 1; j <= nbins ; j++ ) {
            // Sum over all Rec Level Bins EXEPT OF bins!
            // So Please, please, please do not forget to exclude
            // the side bins
            // Note: Rec Level bins are on x axis of mcHist
            double elem = mcHist->GetBinContent(j, i);
            if ( j == 1 ) elem = 0.;
            if ( j == nbins ) elem = 0.;
            numerator += elem;
        }
        double efficiency = SVD_Divide(numerator,denominator);
        double effErr = SVD_BinomialError(numerator, denominator);
        effHist->SetBinContent(i,efficiency);
        effHist->SetBinError(i, effErr);
    }
    SVD_SetTitles1D(effHist, effStr, quantityTex, "Efficiency");




    // RATIO: Unfolded versus BBB
    TH1D* histRatioUnfBBB = SVD_MakeRatioNum(unfHist, bbbHist);
    SVD_SetTitles1D(histRatioUnfBBB, "RATIO", quantityTex, "Ratio");



    // REFOLDING - without Background
    // Note: Divide by "xini", then refold with "event matrix" 
    // Catch: If there are no generated events in a generator bin, then
    // the division by "xini" doesnt work. But there is a way out:
    // In such a case, the whole column of the event matrix will be empty! 
    // Multiplication of x/xini with the event matrix will give zero.
    // This justifies, that those bins can just be skipped in the sum!
    // Isn't life great?
    // Overflow bins: Remember, all side bins are in regular binning.
    // Indexing: i=Rec=(xAxis in mcHist), j=Gen=(yAxis in mcHist) 
    TH1D* refoldHist = (TH1D*) unfHist->Clone("Refolded");
    for ( int i = 1 ; i <= nbins ; i++ ) { 
	double refoldedvalue = 0.;
        for ( int j = 1 ; j <= nbins ; j++ ) { 
            double denominator = xiniHist->GetBinContent(j);
            double numerator = unfHist->GetBinContent(j); 
            double matrixelement = mcHist->GetBinContent(i,j); 
            double current = 0.; 
            if ( denominator > 0. ) {  
                current = matrixelement * ( numerator / denominator );
            } else {
                current = 0.;
            }
            refoldedvalue += current;
	}
        refoldHist->SetBinContent(i, refoldedvalue);
        refoldHist->SetBinError(i, 0.);
    }
    TString refoldStr = SVD_PlotName(channel, particle, quantity, special, "RFLD");
    SVD_SetTitles1D(refoldHist, refoldStr, "Bin i", "Refolded Value d_{i}");


    // RATIO: Refolded versus Data
    TH1D* histRatioRefDat = SVD_MakeRatioDenom(refoldHist, dataHist);
    SVD_SetTitles1D(histRatioRefDat, "RATIO", quantityTex, "Ratio");



    // Calculate Chi2A et. al.
    double chi2A = SVD_Chi2A(dataHist, refoldHist); 
    //int nDOF = SVD_Ndof(dataHist, xiniHist);
    int goodGenBins = SVD_GoodGenBins(xiniHist);
    int goodRecBins = SVD_GoodRecBins(dataHist);
    TString chi2AStr = TString::Format("#chi^{2} = %.3f", chi2A); 
    TString nDOFStr = TString::Format("nDOF=%i-%i", goodRecBins,goodGenBins);
    //TString goodRecStr = TString::Format("RecBins = %i", goodRecBins);
    //TString goodGenStr = TString::Format("GenBins = %i", goodGenBins);    

    // Get the D-Distribution
    TH1D* ddHist = mySVDUnfold->GetD();
    TString ddStr = SVD_PlotName(channel, particle, quantity, special, "DD");
    SVD_SetTitles1D(ddHist, ddStr, "Index i", "d-Value d_{i}");


    // Get the singular Values
    TH1D* svHist = mySVDUnfold->GetSV();
    TString svStr = SVD_PlotName(channel, particle, quantity, special, "SV");
    SVD_SetTitles1D(svHist, svStr, "Index i", "Singular Value s_{i}");
   
 

    // ERROR PLOT (Statistics)
    TString statErrStr = SVD_PlotName(channel, particle, quantity, special, "STATERR");
    TH1D* statErrHist = SVD_Cov2Err(statCovHist, unfHist, statErrStr, quantityTex, "Statistical");



    // ERROR PLOT (MC)
    TString mcErrStr = SVD_PlotName(channel, particle, quantity, special, "MCERR");
    TH1D* mcErrHist = SVD_Cov2Err(mcCovHist, unfHist, mcErrStr, quantityTex, "MC");



    // ERROR PLOT (Total)
    TString totErrStr = SVD_PlotName(channel, particle, quantity, special, "TOTERR");
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
    TString bbbErrStr = SVD_PlotName(channel, particle, quantity, special, "BBBERR");
    bbbErrHist->SetName(bbbErrStr);
    bbbErrHist->SetTitle(bbbErrStr);
    SVD_SetTitles1D(bbbErrHist, bbbErrStr, quantityTex, "Statistical Error in \%");


    // RATIO: UnfErrors versus BBBErrors
    TH1D* histRatioErrors = SVD_MakeRatioNum(statErrHist, bbbErrHist);
    SVD_SetTitles1D(histRatioErrors, "RATIO", quantityTex, "Ratio");


    // CORRELATION STAT
    TString statCorrStr = SVD_PlotName(channel, particle, quantity, special, "STATCORR");
    TH2D* statCorrHist = SVD_Cov2Corr(statCovHist, statCorrStr, quantityTex, "Statistical");


    // CORRELATION MC  
    TString mcCorrStr = SVD_PlotName(channel, particle, quantity, special, "MCCORR");
    TH2D* mcCorrHist = SVD_Cov2Corr(mcCovHist, mcCorrStr, quantityTex, "MC");


    // CORRELATION TOT
    TString totCorrStr = SVD_PlotName(channel, particle, quantity, special, "TOTCORR");
    TH2D* totCorrHist = SVD_Cov2Corr(totCovHist, totCorrStr, quantityTex, "Total");


    // GLOBAL CORRELATION
    // Attention: Do not use the side bins for the computation
    // of the global correlation !!!  
    // The global correlation in the side bins will be set 
    // to zero!
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
    double detStatCovMat[1];
    TMatrixDSym statCovMatInv = statCovMat;
    statCovMatInv.Invert(detStatCovMat);
    TH1D* glcHist = (TH1D*) unfHist->Clone("glcHist"); 
    TString glcStr = SVD_PlotName(channel, particle, quantity, special, "GLOBC");
    glcHist->SetName(glcStr);
    glcHist->SetTitle(mcErrStr);
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
            cout << "for plot " <<  glcStr << ", Bin " << i << endl;
            cout << "Reason: Statistical Covariance Matrix is singular." << endl;
        }
        glcHist->SetBinContent(i, glc); 
    }
    SVD_SetTitles1D(glcHist, glcStr, quantityTex, "Glob. Corr. in \%");



    ///////////////////////////////////////////////////////////
    ///////////   SAVE IT ALL TO PS  //////////////////////////
    /////////////////////////////////////////////////////////// 



    // DRAW IT ALL
    if ( plotsToPs == true ) {
	
        // Donot associate histograms with a directory
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
        CPQtex.Append(particleTex);   



        // Draw Response Matrix
        SVD_Draw2D(mcHist, "COLZ");
        canvas.Print(outputfilename.Copy().Append("("));


        // Draw Input Distributions
        TLegend* legendinp = SVD_NewLegend();
        legendinp->SetHeader(CPQtex);
        THStack* stackinp = new THStack("","");
        stackinp->Add(xiniHist);
        stackinp->Add(biniHist);
        stackinp->Add(dataHist);
        legendinp->AddEntry(xiniHist, "Gen");
        legendinp->AddEntry(biniHist, "Rec");
        legendinp->AddEntry(dataHist, "Dat");
        SVD_DrawStack(stackinp, quantityTex, "Entries", "e nostack", 421);
        legendinp->Draw("SAME");
        canvas.Print(outputfilename);
	

        // Draw Background related Distributions
        TLegend* legendbgr = SVD_NewLegend();
        legendbgr->SetHeader(CPQtex);
        THStack* stackbgr = new THStack("","");
        stackbgr->Add(dataHist);
        stackbgr->Add(rawHist);
        stackbgr->Add(bgrHist);
        legendbgr->AddEntry(rawHist, "Raw");
        legendbgr->AddEntry(bgrHist, "Bgr");
        legendbgr->AddEntry(dataHist, "Data");
        SVD_DrawStack(stackbgr, quantityTex, "Entries", "e nostack", 124);
        legendbgr->Draw("SAME");
        canvas.Print(outputfilename);
        dataHist->Draw();


        // Draw Unfolded distributions	
        TString unfHistLegendEntry = "Unf.";
        unfHistLegendEntry.Append(" k=");
        unfHistLegendEntry.Append(TString::Format("%i", TMath::Abs(kreg))); 
        TLegend* legendout = SVD_NewLegend();
        THStack* stackout = new THStack("", "");
        legendout->SetHeader(CPQtex);
        legendout->AddEntry(unfHist, unfHistLegendEntry);
        legendout->AddEntry(dataHist, "Measured");
        legendout->AddEntry(bbbHist, "BBB");
        stackout->Add(dataHist);
        stackout->Add(bbbHist);
        stackout->Add(unfHist);
        SVD_DrawStack(stackout, quantityTex, "Entries", "e nostack", 134);
        legendout->Draw("SAME");
        canvas.Print(outputfilename);


        // RATIO: Unfolded versus BBB
        TLegend* legendRatioUnfBBB = SVD_NewLegend();
        legendRatioUnfBBB->SetHeader(CPQtex);
        TString legendentryRatioUnfBBB = TString::Format("Unf/BBB");
        SVD_DrawRange(histRatioUnfBBB, 0.3, 3., "", 0);
        legendRatioUnfBBB->AddEntry(histRatioUnfBBB, legendentryRatioUnfBBB);
        legendRatioUnfBBB->Draw("SAME");
        canvas.Print(outputfilename);
 

        // Draw Refolded Distribution
        TString refoldHistLegendEntry = "Rfld.";
        refoldHistLegendEntry.Append(" k=");
        refoldHistLegendEntry.Append(TString::Format("%i", TMath::Abs(kreg)));
        TLegend* legendrefold = SVD_NewLegend();
        THStack* stackrefold = new THStack("", "");
        legendrefold->SetHeader(CPQtex);
        legendrefold->AddEntry(refoldHist, refoldHistLegendEntry);
        legendrefold->AddEntry(dataHist, "Measured"); 
        legendrefold->AddEntry((TObject*) NULL, chi2AStr, "");
        //legendrefold->AddEntry((TObject*) NULL, goodRecStr, "");
        //legendrefold->AddEntry((TObject*) NULL, goodGenStr, "");
        legendrefold->AddEntry((TObject*) NULL, nDOFStr, "");
        stackrefold->Add(dataHist); //dataHist
        stackrefold->Add(refoldHist);
        SVD_DrawStack(stackrefold, quantityTex, "Entries", "e nostack", 134);
        legendrefold->Draw("SAME");
        canvas.Print(outputfilename);
       


        // RATIO: Refolded versus Data
        TLegend* legendRatioRefDat = SVD_NewLegend();
        legendRatioRefDat->SetHeader(CPQtex);
        TString legendentryRatioRefDat = TString::Format("Ref/Data");
        SVD_DrawRange(histRatioRefDat, 0.3, 3., "p", 0);
        legendRatioRefDat->AddEntry(histRatioRefDat, legendentryRatioRefDat);
        legendRatioRefDat->Draw("SAME");
        canvas.Print(outputfilename);

 
        // Draw D-Plot
        TLegend* legenddd = SVD_NewLegend();
        legenddd->SetHeader(CPQtex);
        legenddd->AddEntry(ddHist, "d-Values");
        SVD_Draw1D(ddHist, "", 1);
        legenddd->Draw("SAME");
        canvas.Print(outputfilename);


        // Draw SV Plot
        TLegend* legendsv = SVD_NewLegend();
        legendsv->SetHeader(CPQtex);
        gPad->SetLogy(true);
        legendsv->AddEntry(ddHist, "Sing. Values");
        SVD_Draw1D(svHist, "", 1);
        legendsv->Draw("SAME");
        canvas.Print(outputfilename);
        gPad->SetLogy(false);



        // Draw Stab, Eff, Pur
        TLegend* legendspe = SVD_NewLegend(); legendspe->SetHeader(CPQtex);
        THStack* stackspe = new THStack("", ""); 
        legendspe->AddEntry(purHist, "Pur.");
        legendspe->AddEntry(stabHist, "Stab."); 
        legendspe->AddEntry(effHist, "Eff.");
        SVD_EmptySideBins1D(effHist);
        stackspe->Add(stabHist); 
        stackspe->Add(purHist); 
        stackspe->Add(effHist);
        SVD_DrawStack(stackspe, quantityTex, "\%", "nostack", 321);
        legendspe->Draw("SAME");
        canvas.Print(outputfilename);


        // Draw BBB Efficiency
        TLegend* legendeff = SVD_NewLegend(); 
        legendeff->SetHeader(CPQtex);
        THStack* stackEff = new THStack("", ""); 
        beffHist->UseCurrentStyle();
        effHist->UseCurrentStyle();
        SVD_EmptySideBins1D(beffHist); 
        legendeff->AddEntry(beffHist, "BBB-Eff.");
        legendeff->AddEntry(effHist, "Efficiency"); 
        stackEff->Add(beffHist);
        stackEff->Add(effHist); 
        SVD_DrawStack(stackEff, quantityTex, "Efficiency \%", "nostack", 21);
        legendeff->Draw("SAME");
        canvas.Print(outputfilename);


        // Covariance Matrix (DATA)
        SVD_Draw2D(dataCovHist, "COLZ");
        canvas.Print(outputfilename);


        // Covariance Matrix (STAT)
        SVD_Draw2D(statCovHist, "COLZ");
        canvas.Print(outputfilename);


        // Covariance Matrix (MC)
        SVD_Draw2D(mcCovHist, "COLZ");
        canvas.Print(outputfilename);


        // Covariance Matrix (Total)
        SVD_Draw2D(totCovHist, "COLZ");
        canvas.Print(outputfilename);


        // Correlation Matrix (STAT)
        SVD_Draw2D(statCorrHist, "COLZ TEXT");
        canvas.Print(outputfilename);


        // Correlation Matrix (MC)
        SVD_Draw2D(mcCorrHist, "COLZ TEXT");
        canvas.Print(outputfilename);


        // Correlation Matrix (Total)
        SVD_Draw2D(totCorrHist, "COLZ TEXT");
        canvas.Print(outputfilename);
     

 
        // GLOBAL CORRELATION STAT
        glcHist->UseCurrentStyle(); 
        TLegend* legendglc = SVD_NewLegend(); 
        THStack* stackglc = new THStack("", ""); 
        legendglc->SetHeader(CPQtex);
        legendglc->AddEntry(glcHist, "Glob. Corr. #rho_{i}"); 
        stackglc->Add(glcHist); 
        SVD_DrawStack(stackglc, quantityTex, "Glob. Corr. #rho_{i}", "HIST nostack", 4);
        canvas.Print(outputfilename);




        // Errors (STAT, BBB)
        TLegend* legenderr1 = SVD_NewLegend();
        THStack* stackerr1 = new THStack("", "");
        legenderr1->SetHeader(CPQtex);
        legenderr1->AddEntry(statErrHist, "Unf. Unc.");
        legenderr1->AddEntry(bbbErrHist, "BBB Unc.");
        stackerr1->Add(statErrHist);
        stackerr1->Add(bbbErrHist);
        SVD_DrawStack(stackerr1, quantityTex, "Error in \%", "HIST nostack", 34);
        legenderr1->Draw("SAME");
        canvas.Print(outputfilename);


        // Errors (STAT, MC, TOTAL)
        TLegend* legenderr2 = SVD_NewLegend();
        THStack* stackerr2 = new THStack("", "");
        legenderr2->SetHeader(CPQtex);
        legenderr2->AddEntry(totErrHist, "Tot. Unc.");
        legenderr2->AddEntry(statErrHist, "Unf. Unc.");
        legenderr2->AddEntry(mcErrHist, "MC Unc.");
        stackerr2->Add(totErrHist);
        stackerr2->Add(statErrHist);
        stackerr2->Add(mcErrHist);
        SVD_DrawStack(stackerr2, quantityTex, "Error in \%", "HIST nostack", 134);
        legenderr2->Draw("SAME");
        canvas.Print(outputfilename);


        // RATIO: UnfErrors versus BBBErrors
        TLegend* legendRatioErrors = SVD_NewLegend();
        legendRatioErrors->SetHeader(CPQtex);
        TString legendentryRatioErrors = "Err Ratio";
        legendRatioErrors->AddEntry(histRatioErrors, legendentryRatioErrors);
        SVD_DrawRange(histRatioErrors, 0.3, 3., "p", 0);
        legendRatioErrors->Draw("SAME");
        canvas.Print(outputfilename);

	    // Last page empty
        canvas.Clear();
	    canvas.Print(outputfilename.Copy().Append(")"));


        // Reset Style
        setHHStyle(*gStyle); 
        TGaxis::SetMaxDigits(2);


        // Delete Legends
        delete legendinp;
        delete legendbgr;
        delete legendout;
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
        delete stackout;
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
  
    return 0;  
        
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


    // Return 
    return 0;
}
 

 
