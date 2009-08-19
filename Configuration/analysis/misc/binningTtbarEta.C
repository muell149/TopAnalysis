#include <sstream>
#include <string>

int binningTtbarEta()
{

using namespace std;
  //oeffne files
  TFile* myFile1 = new TFile("analyzeTopQuarks.root", "READ");
  


cout << "Set Bin Number" << endl;
int binN;
cin >> binN;


// define arrays for binsetting and std
int bins[20]; 
float sigma[20]; 


// user input 
cout << binN<< endl;
cout << "Define bin-setting  (Bin Number +1 )" << endl;


for (int i=0 ; i< binN+1 ; i++)
		{
                      			
                        cout <<  i << "-th border: "; 
			cin >> bins[i] ;
		}



// get 2D Hist.

TH2F* myHist2d;

 
  myHist2d = (TH2F*)myFile1->Get("analyzeTopRecKinematicsMatched/ttbarEta_");

 



// loop over all bins 

for (int k=0; k< binN ; k++)
 		{

TH1F* myHist1a = new TH1F( "Projektion" , "Projektion"  ,  100,   -3., 3.);

// for 100 Bins and 300 Pt steps get bin centre
// bins[k]+bins[k+1] gives 2*center -> diagonal over the canvas to estimate the distribution

int n = bins[k]+bins[k+1];

if (n>100)
	{
	for (  int i=n-100 ; i<101; i++ )
    {
        int j=0;
        j=n-i+1;
        myHist1a->SetBinContent(i,myHist2d->GetBinContent(i,j) );

    }	
	}
else 
	{

 for (  int i=1 ; i<n+1; i++ )
    {
        
        j=n-i+1;
        myHist1a->SetBinContent(i,myHist2d->GetBinContent(i,j) );

    }
	}

// Fit gaus disribution to estimate std.
        
       		TCanvas *a=new TCanvas("a","a",1);
		myHist1a->Draw();
       		myHist1a->Fit("gaus");
		cout << gaus->GetParameter(2) << endl;
		sigma[k] = gaus->GetParameter(2);

delete myHist1a; 
delete a; 
		
     		

		}


//output of the std related to the corresponding bin-setting

//cout << " all values in GeV units "  << endl;

for (int k=0; k< binN ; k++)
 		{

		if (k<binN/2) {cout << "2*Sigma:     "<< 2*sigma[k] << "        Binsize:  "<< (bins[k+1]-bins[k])*(6./100.) <<  "      Binsetting:  " << "-"<<3.-bins[k]*(6./100.) << "  -  "<< "-" <<3.-bins[k+1]*(6./100.) << endl;  } 
		
		else {cout << "2*Sigma:     "<< 2*sigma[k] << "        Binsize:  "<< (bins[k+1]-bins[k])*(6./100.) <<  "      Binsetting:  " << bins[k]*(6./100.)-3. << "  -  "<< bins[k+1]*(6./100.)-3. << endl; }

		
		}





  //2d histogramm

 TCanvas *a=new TCanvas("2DTtbarEta","2DTtbarEta",1);
  // set canvas style 
  gStyle->SetPalette(1);
  myHist2d->Draw("colz");
  myHist2d->GetXaxis()->SetTitle("Ttbar Eta Gen");
  myHist2d->GetYaxis()->SetTitle("Ttbar Eta Rec");


// Get Correlation Coefficient
  cout << "Correlation Factor  "<< myHist2d->GetCorrelationFactor() << endl; 

a->SaveAs("kin_genRecTtbarEta.pdf");


return 0;
}