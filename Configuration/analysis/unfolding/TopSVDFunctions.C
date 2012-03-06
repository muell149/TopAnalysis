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
        if ( special.BeginsWith("_") == true ) special.Remove(0,1); 
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



// Empties all bins and all errors in a histogram
void TopSVDFunctions::SVD_EmptyHistogram1D(TH1D* histo)
{
	int nbins = histo->GetNbinsX();
	for ( int i = 0 ; i < nbins ; i++ ) {
		histo->SetBinContent(i, 0.);
		histo->SetBinError(i, 0.);
	}
}



// Empties all bins and all errors in a histogram
void TopSVDFunctions::SVD_EmptyHistogram2D(TH2D* histo)
{
	int nbinsx = histo->GetNbinsX();
	int nbinsy = histo->GetNbinsY();
	int nbins = (nbinsx+2) * (nbinsy+2);
	for ( int i = 0 ; i < nbins ; i++ ) {
		histo->SetBinContent(i, 0.);
		histo->SetBinError(i, 0.);
	}
}



// Empties all errors in a histogram
void TopSVDFunctions::SVD_EmptyHistoErrors1D(TH1D* histo)
{
	int nbins = histo->GetNbinsX();
	for ( int i = 0 ; i < nbins ; i++ ) { 
		histo->SetBinError(i, 0.);
	}
}



// Empties all errors in a histogram
void TopSVDFunctions::SVD_EmptyHistoErrors2D(TH2D* histo)
{
	int nbinsx = histo->GetNbinsX();
	int nbinsy = histo->GetNbinsY();
	int nbins = (nbinsx+2) * (nbinsy+2);
	for ( int i = 0 ; i < nbins ; i++ ) { 
		histo->SetBinError(i, 0.);
	}
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

 


// Rebinning of a 1D Histogram. 
// ATTENTION! ATTENTION! ATTENTION! ATTENTION! ATTENTION!
// (1) Creates a new histogram on the heap. 
//     So dont forget to delete it sometimes. 
// (2) In 'binsx' the bin boundaries are specified!
//     'nbinsx' gives the number of specified bins!
// (3) The first and last bin in 'binsx' are considered
//     as overflow bins, all other bins as center bins!
//     The overflow bins will get all events that cannot be
//     assigned a center bin. The TH2D-side-bins will not be used
//     for the output-histogram.
// (5) Each (but the first and last) bin boundary in 'binsx'  
//     MUST match one in the input-histogram, otherwise double counting 
//     will occur.
TH1D* TopSVDFunctions::SVD_Rebin1D(TH1* input, int nbinsx, double* binsx)
{
    // Create new histo on the heap
    TString nameNewHist = input->GetName();
    nameNewHist.Append("Rebinned");
    TH1D* outputhist = new TH1D(nameNewHist, nameNewHist, nbinsx, binsx); 
    int nbinsGenRecX =input->GetNbinsX();
 
    // Empty the bins
    SVD_EmptyHistogram1D(outputhist); 
    

    // Do NOT use the side bins of th TH2D-Class! 
    for(int i=1; i<=nbinsx; ++i){ 
    
     
        // Find bin boundaries in X
        int nxlow = -1;
        int nxhigh = -1;
        if ( i == 1 ) {   // UF bin in X
            nxlow = 0;
            double xhigh = binsx[1]; 
            nxhigh = SVD_FindBin(input->GetXaxis(), xhigh) - 1;  
        }
        if ( i == nbinsx ) {  // OF bin in X
            double xlow = binsx[nbinsx-1]; 
            nxlow = SVD_FindBin(input->GetXaxis(), xlow);
            nxhigh = nbinsGenRecX+1;
        }
        if ( i > 0 && i < nbinsx) { // Center bin in X
            double xlow = binsx[i-1];
            double xhigh = binsx[i];
            nxlow = SVD_FindBin(input->GetXaxis(), xlow);
            nxhigh = SVD_FindBin(input->GetXaxis(), xhigh) - 1;  
        }

        // Integrate over all the original bins
        double sum = 0.;
        double sumErrSq = 0.;
        if ( nxlow <= nxhigh ) {
        	for ( int b = nxlow ; b <= nxhigh ; b++ ) {
        		double binContent = ((TH1D*) input)->GetBinContent(b);
        		double binError = ((TH1D*) input)->GetBinError(b);
        		sum += binContent;
        		sumErrSq += binError*binError;
        	}
        } else {
            sum = 0.;
            sumErrSq = 0.;
        }

        // Save it
        outputhist->SetBinContent(i, sum);
        outputhist->SetBinError(i, TMath::Sqrt(sumErrSq));
    }

    // Return it
    return outputhist;
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
TH2D* TopSVDFunctions::SVD_Rebin2D(TH1* input, int nbinsx, double* binsx, int nbinsy, double* binsy, bool transpose)
{
    // Create new histo on the heap
    TString nameNewHist = input->GetName();
    nameNewHist.Append("Rebinned");
    TH2D* outputhist = new TH2D(nameNewHist, nameNewHist, nbinsx, binsx, nbinsy, binsy);
    int nbinsGenRecX =input->GetNbinsX();
    int nbinsGenRecY =input->GetNbinsY();
 
    // Empty the bins
    SVD_EmptyHistogram2D(outputhist); 

    // Do NOT use the side bins of th TH2D-Class! 
    for(int i=1; i<=nbinsx; ++i){ 
        for(int j=1; j<=nbinsy; ++j){ 

            // Find bin boundaries in X
            int nxlow = -1;
            int nxhigh = -1;
            if ( i == 1 ) {   // UF bin in X
                nxlow = 0;
                double xhigh = binsx[1];
                nxhigh = SVD_FindBin(input->GetXaxis(), xhigh) - 1; 
            }
            if ( i == nbinsx ) {  // OF bin in X
                double xlow = binsx[nbinsx-1];
                nxlow = SVD_FindBin(input->GetXaxis(), xlow);
                nxhigh = nbinsGenRecX+1; 
            }
            if ( i > 1 && i < nbinsx) { // Center bin in X
                double xlow = binsx[i-1];
                double xhigh = binsx[i];
                nxlow = SVD_FindBin(input->GetXaxis(), xlow);
                nxhigh = SVD_FindBin(input->GetXaxis(), xhigh) - 1; 
            }

            // Find bin boundaries in Y
            int nylow = -1;
            int nyhigh = -1;
            if ( j == 1 ) {  // UF bin in Y
                nylow = 0;
                double yhigh = binsy[1]; 
                nyhigh = SVD_FindBin(input->GetYaxis(), yhigh) - 1; 

            }
            if ( j == nbinsy) {   // UF bin in Y
                double ylow = binsy[nbinsy-1]; 
                nylow = SVD_FindBin(input->GetYaxis(), ylow);
                nyhigh = nbinsGenRecY+1; 
            }
            if ( j > 1 && j < nbinsy ) { // Center bin in Y
                double ylow = binsy[j-1];
                double yhigh = binsy[j]; 
                nylow = SVD_FindBin(input->GetYaxis(), ylow);
                nyhigh = SVD_FindBin(input->GetYaxis(), yhigh) - 1; 
            }

            // Integrate over all the original bins        
            double sum = 0.;
      	    double sumErrSq = 0.;
            if ( nxlow <= nxhigh && nylow <= nyhigh ) {
            	for ( int bx = nxlow ; bx <= nxhigh ; bx++ ) {
            		for ( int by = nylow ; by <= nyhigh ; by++ ) { 
        				double binContent = ((TH1D*) input)->GetBinContent(bx, by);
        				double binError = ((TH1D*) input)->GetBinError(bx, by);
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
      			outputhist->SetBinContent(j, i, sum);
        		outputhist->SetBinError(j, i, TMath::Sqrt(sumErrSq)); 
            } else { 
      			outputhist->SetBinContent(i, j, sum);
        		outputhist->SetBinError(i, j, TMath::Sqrt(sumErrSq)); 
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
             

// SVD Unfolding Helper FUnction
// Creates a Ratio plot of two histograms
// Errors of ratio plot are all set to zero
// Boundaries: If ymax < ymin, then range will be set automatically
TH1D* TopSVDFunctions::SVD_MakeRatioZero(TH1D* numerator, TH1D* denominator)
{

    // Create new Histogram
    TH1D* hist = (TH1D*) numerator->Clone("ratio");


    // Fill Histogram
    int numbins = hist->GetNbinsX();
    for ( int i = 0 ; i < numbins ; i++) {
        double num = numerator->GetBinContent(i);
        double denom = denominator->GetBinContent(i);
        double val = 0.;
        double err = 0.;
        if ( denom != 0. && num != 0.) {
            val = num / denom; 
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
// Attention: We do not use the side bins for the computation
// of the global correlation !!!  
// The global correlation in the side bins will be set 
// to zero!
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
TH1D* TopSVDFunctions::SVD_Refold(TH1D* unfHist, TH1D* xiniHist, TH2D* mcHist, bool useWeights) 
{
	// Make a new Histogram
    TH1D* refoldHist = (TH1D*) unfHist->Clone("Refolded");
    int nbins = unfHist->GetNbinsX(); 
    
    // Important Check:
    // Make sure that generator level bins
    // with empty xiniHist-bins
    // have also empty mcHist-rows
    // GenLevelIndex=j, DetLevelIndex=i
    if ( useWeights == false ) {
	    for ( int j = 1 ; j <= nbins ; j++ ) {
	    	double numerator = xiniHist->GetBinContent(j);
	    	if ( numerator > 0. ) continue; 
	    	bool doWarning = true;
	        for ( int i = 1 ; i <= nbins ; i++ ) {  
	            double matrixelement = mcHist->GetBinContent(i,j); 
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
            	xini = xiniHist->GetBinContent(j);
            }
            double unf = unfHist->GetBinContent(j); 
            double matrixelement = mcHist->GetBinContent(i,j); 
            double current = 0.; 
            if ( xini > 0. ) {  
                current = matrixelement * ( unf / xini );
            } else {
                current = 0.;
            }
            refoldedvalue += current;
	    }
        refoldHist->SetBinContent(i, refoldedvalue);
        refoldHist->SetBinError(i, 0.);
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
//        a "center value" for tau, to be specified in 'regpar' .
//        Note: The scan may take a while!     
// (5) regMode=4 is SVD Unfolding. A scan for the optimal tau
//        parameter is performed. The scan is performed around
//        a "center value" for k, to be specified in 'regpar'    
//        Note: The scan may take a while!     
// If you specify filenames, plots will be drawn and saved.
// Return value: Best value of tau if scan is performed, -1. otherwise
double TopSVDFunctions::SVD_Unfold(
        // Data Input (RAW Data including the background)
        TH1* dataInputHist,   
	// Background (reco level, all BG, will be substracted from data)
        TH1* bgrInputHist,
	// ttbar background only (used to calculate a ttbar signal 
	// fraction instead of subtracting the yield which depends 
	// on the inclusive ttbar cross section.) 
	// Note: if 0 pointer is handed over 
	TH1* ttbgrInputHist, 
	// Generated signal MC
        TH1* genInputHist,
	// Reconstructed signal MC
        TH1* recInputHist,        
	// Response Matrix 
        TH1* respInputHist,   
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
	// Specify Name for the Channel ("mumu", "emu", "ee" ...)
        TString channel,  
	// Specify Name for the Physics Object ("Top", "Jets", "Leptons")
        TString particle, 
	// Specify Name for the Quantity ("Eta", "Pt", or "Mass");
        TString quantity,
	// Specify Name for special run of unfolding
        TString special,
	// Nicely formatted name for the channel
        TString channelTex,
	// Nicely formatted name for the physics object
        TString particleTex,
	// Nicely formatted name for ithe quantity
        TString quantityTex,
	// Nicely formatted name indicating some special condition 
        TString specialTex,
	// If specified, plots will be saved in ROOT File
        TString rootFile,
	// If specified, plots will be saved in PS File 
        TString psFile,
	// parameter to control amount of output
	// verbose=0: no output at all
	// verbose=1: standard output
	// verbose=2: debug output	
	int verbose
)
{
    // adapt gErrorIgnoreLevel to reduce output
    int initialgErrorLv=gErrorIgnoreLevel;
    if(verbose==1) gErrorIgnoreLevel=kWarning;
    if(verbose==0) gErrorIgnoreLevel=kFatal;

    // Number of Pseudo Experiments for the error calculation    
    int nExperiments = 1000;
     

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


    ////////////////////////////////
    // REBINNING INPUT HISTOGRAMS //
    ////////////////////////////////

    // data (including background)
    TH1D* rawHist = SVD_Rebin1D(dataInputHist, nbins, bins);
    SVD_EmptySideBins1D(rawHist);

    // all background
    // Set errors to zero!
    TH1D* bgrHist = SVD_Rebin1D((TH1D*) bgrInputHist, nbins, bins); 
    SVD_EmptyHistoErrors1D(bgrHist);
    SVD_EmptySideBins1D(bgrHist);
    
    // ttbar background only
    TH1D* ttbgrHist;
    if ( ttbgrInputHist != NULL ) {
      ttbgrHist= SVD_Rebin1D((TH1D*) ttbgrInputHist, nbins, bins); 
      SVD_EmptyHistoErrors1D(ttbgrHist);
      SVD_EmptySideBins1D   (ttbgrHist);
    }
    
    // Response Matrix
    // ... thereby transposing it
    TH2D* mcHist = SVD_Rebin2D((TH2D*) respInputHist, nbins, bins, nbins, bins, true);  
    //SVD_MoveOFBins2D(mcHist);
    //SVD_EmptySideBins2D(mcHist);


    // ttbar (MC truth signal)
    TH1D* xiniHist = SVD_Rebin1D((TH1D*) genInputHist, nbins, bins);
    SVD_MoveOFBins1D(xiniHist);
    

    // ttbar (reconstructed MC signal)
    TH1D* biniHist = SVD_Rebin1D((TH1D*) recInputHist, nbins, bins);
    SVD_EmptySideBins1D(biniHist);


    // BACKGROUND SUBSTRACTION FROM DATA
    // ATTENTION! Errors from background
    // will be neglected.
    // You thought about this once!
    // Dont mess this up!
    // Note: if ttbar BG plot is handed over, 
    //       a multiplicative approach is used
    //       to deal with ttbar BG instead of 
    //       subracting the (xSec dependend) yield
    TH1D* dataHist = (TH1D*) rawHist->Clone("dataHist");
    // loop bins
    for ( int i = 0 ; i < nbins + 1 ; i++) {
      // get bin and errors
      double value_data = rawHist->GetBinContent(i);
      double value_bgr = bgrHist->GetBinContent(i);
      double err_data = rawHist->GetBinError(i);
      //double err_bgr = bgrHist->GetBinError(i);
      // feasibility check 
      if(value_data<value_bgr){
	std::cout << "ERROR in TopSVDFunctions::SVD_Unfold: " << std::endl;
	std::cout << "N_MC BG > N_data in bin " << i << std::endl;
	std::cout << "(" << value_bgr << ">" << value_data << ")" << std::endl;
	exit(0);
      }
      double value_new = value_data - value_bgr;
      //double err_bgr = bgrHist->GetBinError(i);
      //double err_new = TMath::Sqrt(err_data*err_data + err_bgr*err_bgr);
      double err_new = err_data; 
      // debug output
      if(verbose>=2){
	std::cout << std::endl << "bin " << i << std::endl;
	std::cout << "value_data: " << value_data << std::endl;
	std::cout << "value_bgr: "  <<  value_bgr << std::endl;
	std::cout << "err_data: "   << err_data << std::endl;
      }
      // use ttbar signal fraction if ttbar BG plot exists
      if ( ttbgrInputHist != NULL ) {
	double value_ttSig=biniHist->GetBinContent(i);
	double value_ttBgr=ttbgrHist->GetBinContent(i);
	// feasibility check 
	if(value_ttBgr>value_bgr){
	  std::cout << "ERROR in TopSVDFunctions::SVD_Unfold: " << std::endl;
	  std::cout << "N_{MC ttbar BG} > N_{MC all BG} in bin " << i << std::endl;
	  std::cout << "(" << value_ttBgr << ">" << value_bgr << ")" << std::endl;
	  exit(0);
	}
	// don't subtract ttbar BG
	value_bgr-=value_ttBgr;
	// calculate signal fraction
	double sigFrac=value_ttSig/(value_ttSig+value_ttBgr);
	// debug output
	if(verbose>=2){
	  std::cout << "value_ttBgr: " << value_ttBgr << std::endl;
	  std::cout << "value_bgr(no ttbar): " << value_bgr << std::endl;
	  std::cout << "value_ttSig: " << value_ttSig << std::endl;
	  std::cout << "sigFrac: " << sigFrac << std::endl;
	}
	// use ttbar signal fraction
	value_new = (value_data - value_bgr)*sigFrac;
	err_new = err_data*sigFrac; 
      }
      // debug output
      if(verbose>=2){
	std::cout << "data_value_new: " << value_new << std::endl;
	std::cout << "data_err_new: "   << err_new   << std::endl;
      }
      dataHist->SetBinContent(i, value_new);
      dataHist->SetBinError(i, err_new); 
    }  
    SVD_EmptySideBins1D(dataHist);



    ///////////////////////////////////////////////////////////////////
    ////////////   U N F O L D I N G //////////////////////////////////
    ///////////////////////////////////////////////////////////////////

 

    // BBB-Efficiency
    TH1D* beffHist = (TH1D*) biniHist->Clone("beffHist");
    for ( int i = 1 ; i < nbins+1 ; i++ ) {  
        // Sum over all Gen Level bins Including OF bins
        double numerator = 0.;
        for ( int j = 1 ; j < nbins+1 ; j++ ) { 
            numerator += mcHist->GetBinContent(i, j);
        }
    	double numeratorErr = SVD_Sqrt(numerator); 
        double denominator = xiniHist->GetBinContent(i); 
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


    // First BBB Unfolding 
    // ATTENTION:
    // (1) Use BBB Efficiency.
    // (2) Although this might be tempting,
    //     do not include the error from the efficiency.
    //     This would bust any serious BBB / SVD comparison.
    //     Instead, add the error on the uncertainty
    //     later on as a systematic MC uncertainty! 
    TH1D* bbbHist = (TH1D*) dataHist->Clone("bbbHist");
    for ( int i = 1 ; i <= nbins ; i++ ) {
        double data = dataHist->GetBinContent(i);
        double bbbeff  = beffHist->GetBinContent(i);
        double dataErr = dataHist->GetBinError(i);
        double bbbunf = 0.;
        double bbbunfErr = 0.;
        if ( data > 0. && bbbeff > 0.) {
            bbbunf = data / bbbeff;
            bbbunfErr = dataErr / bbbeff;
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


    // Setup Unfolding Tool
    TopSVDUnfold *mySVDUnfold = new TopSVDUnfold(dataHist, biniHist, xiniHist, mcHist);
    mySVDUnfold->SetNormalize(false);


    // Setup Regularization
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
    mySVDUnfold->SetTau(theTau);
    
    
    // Output
    if(verbose>0){
      cout << "Unfolding " << channel << "/" << quantity << "/" << particle;
      if ( ! special.CompareTo("") == 0 ) cout << "/" << special;
      if ( doUseTau == true ) cout << " with tau=" << theTau;
      if ( doUseTau == false ) cout << " with k=" << theKReg;
      cout << endl;
    }
	
    // Get Lumi SCale Factor
    double lumiScaleFactor =  SVD_LumiScaleFactor(dataHist, biniHist); 
    
    
    // THE UNFOLDING 
    TH1D* unfHist = (TH1D*) mySVDUnfold->Unfold(theKReg)->Clone("unfHist"); 
      
    // Get More Output
    TH1D* weightHist = (TH1D*) mySVDUnfold->GetWeights()->Clone("weightHist"); 
    TH1D* svHist = (TH1D*) mySVDUnfold->GetSV()->Clone("svHist"); 
    TH1D* ddHist = (TH1D*) mySVDUnfold->GetD()->Clone("ddHist"); 
    
    // Output
    if(verbose>0) cout << "Unfolding done!" << endl;


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

    /////////////////////////////////////////////////////
    ////////////   SCANNING     /////////////////////////
    /////////////////////////////////////////////////////

   

	// Save Singular Values in TVector 
    int nSingularValues = 0;
    for ( int i = 0 ; i < svHist->GetNbinsX() ; i++ ) {
    	double sv = svHist->GetBinContent(i+1);
    	if ( sv > 0. ) nSingularValues++ ;
    }  
    TVectorD vSingularValues(nSingularValues);
    for ( int i = 0 ; i < svHist->GetNbinsX() ; i++ ) {
    	double sv = svHist->GetBinContent(i+1);  
    	if ( sv > 0. ) vSingularValues[i] = sv; 
    }
      

    // Create Scan Vectors
	TVectorD* vScanPoints = NULL; 
	TVectorD* vGlobCorr = NULL; 
	TVectorD* vChiSq = NULL; 
	TVectorD* vCurv = NULL;  
	TVectorD* vAvgSqErr = NULL;
	TVectorD* vAvgMean = NULL;  
    double optimalTauX = -1.;
    double optimalTauY = -1.;
    int optimalTauPos = -1; 
 
    // Doubles for BBB values
	double bbbAvgSqErr = 0.;
	double bbbAvgMean = 0.; 

    if ( doScan == true ) {
    	
    	
    	// Steer Scan
  		double rangefactor = 100.;
   		int nScanPoints = 100;
    	
    	
    	// Find interesting singular value 
    	// Limit the kReg to the Modes which are actually there! 
    	int effectiveKReg = theKReg;
    	if ( effectiveKReg >= nSingularValues ) effectiveKReg = nSingularValues-1;
    	double singularValueK =  vSingularValues[effectiveKReg];
    	
    	
    	// Range for Scan
    	double lowTau = 0.;
    	double highTau = 0.;
    	if ( doUseTau == false ) {
    	    lowTau = (1./rangefactor) * singularValueK;
    	    highTau = rangefactor * singularValueK;
    	} else {
    		lowTau = (1./rangefactor) * theTau;
    		highTau = rangefactor * theTau;
    	}
    	  
    	// Get the Scan Points
    	vScanPoints = SVD_CalcScanPoints(lowTau, highTau, nScanPoints);
    	   
    	// Create the vectors
    	vGlobCorr = new TVectorD(nScanPoints);
		vChiSq = new TVectorD(nScanPoints);
		vCurv = new TVectorD(nScanPoints);
	    vAvgSqErr = new TVectorD(nScanPoints);
	    vAvgMean = new TVectorD(nScanPoints);
    	 
    	  
    	// Perform the Scan
    	cout << "Perform Tau Scan from " << lowTau << " to " << highTau << endl;  
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
		    cout << "    done for Tau = " << tau << endl;
		    
		    // delete things
		    delete tmpUnfResult;
		    delete tmpWeights;
		    delete tmpCovHist;
	 		
		}	 
    	 
    	// Find optimal tau
    	optimalTauPos = SVD_FindMinimum(vScanPoints, vGlobCorr, optimalTauX, optimalTauY); 
    	cout << "Optimal Tau = " << optimalTauX << " at scan position " << optimalTauPos << endl;
 
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

    
    // Format SVD Plot (Weights)
    TString weightStr = SVD_PlotName(channel, particle, quantity, special, "WGT");
    SVD_SetTitles1D(weightHist, weightStr, quantityTex, "Events");
    
    
    // Format SVD Plot
    TString unfStr = SVD_PlotName(channel, particle, quantity, special, "UNF");
    SVD_SetTitles1D(unfHist, unfStr, quantityTex, "Events");
 

    // Set Pointer
    if ( doSVD == true ) unfolded = (TH1D*) unfHist->Clone(unfStr.Append("_Returned"));
    if ( doSVD == false ) unfolded = (TH1D*) bbbHist->Clone(bbbStr.Append("_Returned"));
 


    // RETURN 
    // If no more plots are needed, return now 
    if ( doAllPlots == false ) return optimalTauX; 


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
    // gerenated events in a bin
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
    // Note, here we need to use the weightHist, since the
    // xiniHist contains empty gen level bins
    //TH1D* refoldHist = SVD_Refold(unfHist, xiniHist, mcHist); 
    TH1D* refoldHist = SVD_Refold(weightHist, NULL, mcHist, true); 
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
    TString ddStr = SVD_PlotName(channel, particle, quantity, special, "DD");
    SVD_SetTitles1D(ddHist, ddStr, "Index i", "d-Value d_{i}");


    // Get the singular Values
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
    TH1D* histRatioErrors = SVD_MakeRatioZero(statErrHist, bbbErrHist);
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
    TH1D* glcHist = SVD_CalcGlobCorr(statCovHist);
    TString glcStr = SVD_PlotName(channel, particle, quantity, special, "GLOBC");
    glcHist->SetName(glcStr);
    glcHist->SetTitle(glcStr);
    SVD_SetTitles1D(glcHist, glcStr, quantityTex, "Glob. Corr. in \%");



    ///////////////////////////////////////////////////////////
    ///////////   SAVE IT ALL TO PS  //////////////////////////
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


        // Draw Weight distributions	
        weightHist->Scale(1./lumiScaleFactor);
        TString weightHistLegendEntry = "Weights w_{i}"; 
        TLegend* legendweight = SVD_NewLegend();
        THStack* stackweight = new THStack("", "");
        legendweight->SetHeader(CPQtex);
        legendweight->AddEntry(weightHist, weightHistLegendEntry, "l");  
        stackweight->Add(weightHist);
        SVD_DrawStack(stackweight, quantityTex, "Weights", "e nostack", 134);
        legendweight->Draw("SAME");
        canvas.Print(outputfilename);


        // Draw Unfolded distributions	
        TString unfHistLegendEntry = "Unf.";
        unfHistLegendEntry.Append(" k=");
        unfHistLegendEntry.Append(TString::Format("%i", TMath::Abs(theKReg))); 
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
        SVD_DrawRange(histRatioUnfBBB, 0.7, 1.4, "", 0);
        legendRatioUnfBBB->AddEntry(histRatioUnfBBB, legendentryRatioUnfBBB);
        legendRatioUnfBBB->Draw("SAME");
        canvas.Print(outputfilename);
 

        // Draw Refolded Distribution
        TString refoldHistLegendEntry = "Rfld.";
        refoldHistLegendEntry.Append(" k=");
        refoldHistLegendEntry.Append(TString::Format("%i", TMath::Abs(theKReg)));
        TLegend* legendrefold = SVD_NewLegend();
        THStack* stackrefold = new THStack("", "");
        legendrefold->SetHeader(CPQtex);
        legendrefold->AddEntry(refoldHist, refoldHistLegendEntry);
        legendrefold->AddEntry(dataHist, "Measured"); 
        legendrefold->AddEntry((TObject*) NULL, chi2AStr, "");
        //legendrefold->AddEntry((TObject*) NULL, goodRecStr, "");
        //legendrefold->AddEntry((TObject*) NULL, goodGenStr, "");
        //legendrefold->AddEntry((TObject*) NULL, nDOFStr, "");
        stackrefold->Add(dataHist); //dataHist
        stackrefold->Add(refoldHist);
        SVD_DrawStack(stackrefold, quantityTex, "Entries", "e nostack", 134);
        legendrefold->Draw("SAME");
        canvas.Print(outputfilename);
       


        // RATIO: Refolded versus Data
        TLegend* legendRatioRefDat = SVD_NewLegend();
        legendRatioRefDat->SetHeader(CPQtex);
        TString legendentryRatioRefDat = TString::Format("Ref/Data");
        SVD_DrawRange(histRatioRefDat, 0.7, 1.5, "p", 0);
        legendRatioRefDat->AddEntry(histRatioRefDat, legendentryRatioRefDat);
        legendRatioRefDat->Draw("SAME");
        canvas.Print(outputfilename);

  
        // Draw D-Plot
        TLegend* legenddd = SVD_NewLegend();
        legenddd->SetHeader(CPQtex);
        gPad->SetLogy(true);
        legenddd->AddEntry(ddHist, "d-Values");
        SVD_Draw1D(ddHist, "", 1);
        legenddd->Draw("SAME");
        canvas.Print(outputfilename);
        gPad->SetLogy(false);
 

        // Draw SV Plot
        TLegend* legendsv = SVD_NewLegend();
        legendsv->SetHeader(CPQtex);
        gPad->SetLogy(true);
        legendsv->AddEntry(svHist, "Sing. Values");
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
        SVD_DrawStack(stackspe, quantityTex, "Pur., Stab., Eff. in \%", "nostack", 321);
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
        legendglc->AddEntry(glcHist, "Glob. Corr. #rho_{i} in \%"); 
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
        TString legendentryRatioErrors = "Err. Ratio";
        legendRatioErrors->AddEntry(histRatioErrors, legendentryRatioErrors);
        SVD_DrawRange(histRatioErrors, 0.3, 3., "p", 0);
        legendRatioErrors->Draw("SAME");
        canvas.Print(outputfilename);
        
         
        // Scan Plots
        if ( doScan == true ) {
        	
			// Logscale
    		gPad->SetLogx(true); 
        	
        	// Global Correlation Plot
        	canvas.Clear();
        	TH1D* bgrHisto = NULL;
        	TGraph* gGlobCorr = SVD_Vect2Graph(vScanPoints, vGlobCorr); 
        	SVD_DrawGraph(gGlobCorr,  bgrHisto, "P", 1);
        	TString gGlobCorrStr = SVD_PlotName(channel, particle, quantity, special, "scanGLOBC");
        	SVD_SetTitles1D(bgrHisto, gGlobCorrStr, "Parameter #tau", "Averaged Global Correlation  #bar{#rho}  in %"); 
        	TGraph* bestPoint = SVD_Point2Graph(optimalTauX, (*vGlobCorr)[optimalTauPos]);
        	SVD_DrawGraph(bestPoint,  bgrHisto, "P", 2); 
        	bestPoint->SetMarkerSize(2.5); 
        	bestPoint->SetMarkerStyle(3);
        	SVD_DrawVertLines(bgrHisto, &vSingularValues, 2);
        	TString textBestPoint = TString::Format("log_{10} #tau = %.3f", optimalTauX);
        	int textOrientationBestPoint = 23;
        	TLatex* latexBestPoint = new TLatex();
        	latexBestPoint->SetTextSize(0.03);
        	latexBestPoint->SetTextColor(2); 
        	double textPosBestPointX =  SVD_TextPosX(bgrHisto, (*vScanPoints)[optimalTauPos], gPad->GetLogx(), textOrientationBestPoint);
        	double textPosBestPointY =  SVD_TextPosY(bgrHisto,   (*vGlobCorr)[optimalTauPos], gPad->GetLogy(), textOrientationBestPoint); 
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
        	bgrHisto->SetMaximum(2.*(*vChiSq)[optimalTauPos]); // Range 
        	TString gChiSqStr = SVD_PlotName(channel, particle, quantity, special, "scanCHI2A");
        	SVD_SetTitles1D(bgrHisto, gChiSqStr, "Parameter #tau", "#chi^{2}");
        	bestPoint = SVD_Point2Graph(optimalTauX, (*vChiSq)[optimalTauPos]);
        	SVD_DrawGraph(bestPoint,  bgrHisto, "P", 2); 
        	bestPoint->SetMarkerSize(2.5); 
        	bestPoint->SetMarkerStyle(3);
        	SVD_DrawVertLines(bgrHisto, &vSingularValues, 2);
        	textBestPoint = TString::Format("log_{10} #tau = %.3f", optimalTauX);
        	textOrientationBestPoint = 31;
        	latexBestPoint = new TLatex();
        	latexBestPoint->SetTextSize(0.03);
        	latexBestPoint->SetTextColor(2); 
        	textPosBestPointX =  SVD_TextPosX(bgrHisto, (*vScanPoints)[optimalTauPos], gPad->GetLogx(), textOrientationBestPoint);
        	textPosBestPointY =  SVD_TextPosY(bgrHisto,      (*vChiSq)[optimalTauPos], gPad->GetLogy(), textOrientationBestPoint); 
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
        	TString gCurvStr = SVD_PlotName(channel, particle, quantity, special, "scanCURV");
        	SVD_SetTitles1D(bgrHisto, gCurvStr, "Parameter #tau", "Curvature x^{T}Cx");
        	bestPoint = SVD_Point2Graph(optimalTauX, (*vCurv)[optimalTauPos]);
        	SVD_DrawGraph(bestPoint,  bgrHisto, "P", 2); 
        	bestPoint->SetMarkerSize(2.5); 
        	bestPoint->SetMarkerStyle(3);
        	SVD_DrawVertLines(bgrHisto, &vSingularValues, 2);
        	textBestPoint = TString::Format("log_{10} #tau = %.3f", optimalTauX);
        	textOrientationBestPoint = 11;
        	latexBestPoint = new TLatex();
        	latexBestPoint->SetTextSize(0.03);
        	latexBestPoint->SetTextColor(2); 
        	textPosBestPointX =  SVD_TextPosX(bgrHisto, (*vScanPoints)[optimalTauPos], gPad->GetLogx(), textOrientationBestPoint);
        	textPosBestPointY =  SVD_TextPosY(bgrHisto,      (*vCurv)[optimalTauPos], gPad->GetLogy(), textOrientationBestPoint); 
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
        	TString gAvgSqErrStr = SVD_PlotName(channel, particle, quantity, special, "scanAVGERR");
        	SVD_SetTitles1D(bgrHisto, gAvgSqErrStr, "Parameter #tau", "Avg. Sq. Stat. Error");
        	bestPoint = SVD_Point2Graph(optimalTauX, (*vAvgSqErr)[optimalTauPos]);
        	SVD_DrawGraph(bestPoint,  bgrHisto, "P", 2); 
        	bestPoint->SetMarkerSize(2.5); 
        	bestPoint->SetMarkerStyle(3);
        	SVD_DrawVertLines(bgrHisto, &vSingularValues, 2);
        	SVD_DrawHorizLine(bgrHisto, bbbAvgSqErr, 3);
        	textBestPoint = TString::Format("log_{10} #tau = %.3f", optimalTauX);
        	textOrientationBestPoint = 11;
        	latexBestPoint = new TLatex();
        	latexBestPoint->SetTextSize(0.03);
        	latexBestPoint->SetTextColor(2); 
        	textPosBestPointX =  SVD_TextPosX(bgrHisto, (*vScanPoints)[optimalTauPos], gPad->GetLogx(), textOrientationBestPoint);
        	textPosBestPointY =  SVD_TextPosY(bgrHisto,      (*vAvgSqErr)[optimalTauPos], gPad->GetLogy(), textOrientationBestPoint); 
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
        	TString gAvgMeanStr = SVD_PlotName(channel, particle, quantity, special, "scanAVGMEAN");
        	SVD_SetTitles1D(bgrHisto, gAvgMeanStr, "Parameter #tau", "Average Bin Content");
        	bestPoint = SVD_Point2Graph(optimalTauX, (*vAvgMean)[optimalTauPos]);
        	SVD_DrawGraph(bestPoint,  bgrHisto, "P", 2); 
        	bgrHisto->SetMaximum(1.3*(*vAvgMean).Max()); // Range 
        	bgrHisto->SetMinimum(0.8*(*vAvgMean).Min()); // Range 
        	bestPoint->SetMarkerSize(2.5); 
        	bestPoint->SetMarkerStyle(3);
        	SVD_DrawVertLines(bgrHisto, &vSingularValues, 2);
        	SVD_DrawHorizLine(bgrHisto, bbbAvgMean, 3);
        	textBestPoint = TString::Format("log_{10} #tau = %.3f", optimalTauX);
        	textOrientationBestPoint = 23;
        	latexBestPoint = new TLatex();
        	latexBestPoint->SetTextSize(0.03);
        	latexBestPoint->SetTextColor(2); 
        	textPosBestPointX =  SVD_TextPosX(bgrHisto, (*vScanPoints)[optimalTauPos], gPad->GetLogx(), textOrientationBestPoint);
        	textPosBestPointY =  SVD_TextPosY(bgrHisto,      (*vAvgMean)[optimalTauPos], gPad->GetLogy(), textOrientationBestPoint); 
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
        delete stackweight;
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
 

 
