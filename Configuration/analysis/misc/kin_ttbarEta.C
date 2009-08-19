#include <vector>



TH1F* myHist1a;
TH1F* myHist2a;
TH1F* myHist3a;
TH1F myPurity;
TH1F myStability;

double max[3];


int kin_ttbarEta()
{

// Canvas Style

  gStyle->SetOptStat(0);
  gStyle->SetCanvasColor(10);

  //set proper style
  //gStyle->SetOptStat(0);

  //oeffne files
  TFile* myFile1 = new TFile("analyzeTopQuarks.root", "READ");
  //TFile* myFile2 = new TFile("LM3_gen.root", "READ");
  //TFile* myFile3 = new TFile("ZPrime.root", "READ");

  //Skalierungsfaktoren
  float s1=1.;
  float s2=9530./693.;
  float s3=9530./13323.;

  //lese histogramm aus
  myHist1a = (TH1F*)myFile1->Get("analyzeTopGenKinematics/ttbarEta");
  myHist2a = (TH1F*)myFile1->Get("analyzeTopRecKinematics/ttbarEta");
  myHist3a = (TH1F*)myFile1->Get("analyzeTopRecKinematicsMatched/ttbarEta");

// erzeuge die verteilungsdichte

for (int i=1; i< myHist1a->GetNbinsX()+1 ; i++ )
		{
			myHist1a->SetBinContent(i, myHist1a->GetBinContent(i)/ myHist1a->GetBinWidth(i));
		}

for (int i=1; i< myHist2a->GetNbinsX()+1; i++ )
		{
			myHist2a->SetBinContent(i, myHist2a->GetBinContent(i)/ myHist2a->GetBinWidth(i));
		}

for (int i=1; i< myHist3a->GetNbinsX()+1 ; i++ )
		{
			myHist3a->SetBinContent(i, myHist3a->GetBinContent(i)/ myHist3a->GetBinWidth(i));
		}




  //definiere canvas aussehen
  myHist1a->GetXaxis()->SetTitle("kin_ttbarEta");
  myHist1a->GetYaxis()->SetTitle("event density");
  myHist1a->SetTitle("kin_ttbarEta");  

  //gStyle->SetCanvasColor(10);

  //-----------
  // myhist a
  //-----------
  TCanvas *a=new TCanvas("a","a",1);
  
  //male histogramm
  myHist1a->SetLineColor(4.);
  myHist1a->SetLineWidth(3.);
  myHist1a->SetLineStyle(3);
  //myHist1a->SetFillStyle(3004.);
  //myHist1a->SetFillColor(8.);
  myHist1a->Scale(s1);
  //myHist1a->GetYaxis()->SetRangeUser(0,);
  myHist1a->Draw();
max[0]=myHist1a->GetMaximum();




  myHist2a->SetLineColor(2.);
  myHist2a->SetLineWidth(3.);
  //myHist2a->SetLineStyle(5);
  //myHist2a->SetFillStyle(3004.);
  //myHist2a->SetFillColor(1.);
  myHist2a->Scale(s1);
  //myHist2a->GetYaxis()->SetRangeUser(0,);
  myHist2a->Draw("same");

max[1]= myHist2a -> GetMaximum();



  myHist3a->SetLineColor(1.);
  myHist3a->SetLineWidth(3.);
  //myHist3a->SetLineStyle(5);
  //myHist3a->SetFillStyle(3004.);
  //myHist3a->SetFillColor(1.);
  myHist3a->Scale(s1);
  //myHist3a->GetYaxis()->SetRangeUser(0,);
  myHist3a->Draw("same");

max[2]= myHist3a -> GetMaximum();

double Max = max[0];

int i=0;
   for( ; i < 3 ; ++i)
 	{   
	if (max[i] > Max)
            { 
		Max = max[i];
		} 

   	}

//set Max
myHist1a -> SetMaximum(Max*1.1);
myHist1a -> SetMinimum(0);

leg=new TLegend(0.65,0.65,0.85,0.85);

 	leg->AddEntry(myHist1a,"Gen" ,"l");
	leg->AddEntry(myHist2a,"Reco" ,"l");
	leg->AddEntry(myHist3a,"Match" ,"l");
	leg->Draw("box");


//Stab. & Purity 

TCanvas *b=new TCanvas("b","b",1);




myPurity= (*myHist3a)/(*myHist1a);
myPurity->GetYaxis()->SetRangeUser(0,1);

myPurity->SetLineColor(4.);
myPurity->SetLineWidth(3.);

myPurity->Draw();


myStability= (*myHist3a)/(*myHist2a);
myStability->GetYaxis()->SetRangeUser(0,1);

myStability->SetLineColor(5.);
myStability->SetLineWidth(3.);


myStability->Draw("Same");



legb =new TLegend(0.65,0.65,0.85,0.85);

 	legb->AddEntry( &myStability,"Stability" ,"l");
	legb->AddEntry( &myPurity,"Purity" ,"l");

legb->Draw("box");



  a->SaveAs("kin_ttbarEta.pdf");
  b->SaveAs("kin_ttbarEta2.pdf");
  return 0;
}
