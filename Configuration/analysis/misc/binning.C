

int binning()
{
  //set proper style
  //gStyle->SetOptStat(0);
using namespace std;
  //oeffne files
  TFile* myFile1 = new TFile("analyzeTopQuarks.root", "READ");
  
  //Skalierungsfaktoren
  float s1=1.;
  float s2=9530./693.;
  float s3=9530./13323.;

TH1F* myHist1a = new TH1F( "Projektion" , "Projektion"  ,   100,   0., 300.);
//TH1F* myHist2a;
TH2F* myHist2d;

 
  myHist2d = (TH2F*)myFile1->Get("analyzeTopMatchKinematics/kin_genRecTopPt");

  //definiere canvas aussehen
 // myHist1a->GetXaxis()->SetTitle("kin_bottomPt");
  //myHist1a->GetYaxis()->SetTitle("events");
 // myHist1a->SetTitle("kin_bottomPt");  

  //gStyle->SetCanvasColor(10);

  //-----------
  // myhist a
  //-----------
  TCanvas *a=new TCanvas("a","a",1);
  
  //male histogramm

  gStyle->SetPalette(1);

  myHist2d->Draw("colz");

  
  
// Bin parameter input x1 x2 integer mod 3

int x1=0;
int x2=0;
int j=0;

cout << "Bitte x1, x2 eingeben (0 - 100) " << endl;
cin >> x1;
cin >> x2;


// for 100 Bins and 300 Pt steps get bin centre

int n = x1+x2;

if (n>100)
	{
	for (  int i=n-100 ; i<101; i++ )
    {
        
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



  myHist1a->SetLineColor(1.);
  myHist1a->SetLineWidth(1.);
  myHist1a->SetLineStyle(0);
  //myHist3a->SetFillStyle(3004.);
  //myHist3a->SetFillColor(1.);
  //myHist3a->Scale(s1);
  //myHist3a->GetYaxis()->SetRangeUser(0,);
    TCanvas *b=new TCanvas("b","b",1);
        
        myHist1a->Draw();
        myHist1a->Fit("gaus");



  a->SaveAs("kin_genRecTopPt.pdf");
  b->SaveAs("kin_genRecTopPt2.pdf");



return 0;
}