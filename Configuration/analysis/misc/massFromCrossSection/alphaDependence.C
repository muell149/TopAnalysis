#include <fstream>
#include <iostream>

#include "TAxis.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TF1.h"
#include "TGraph.h"
#include "TLine.h"

enum TheoryType { kMoch, kMitov };
enum PdfType { kMSTW, kHERA, kABM, kNNPDF, kCT };

void printInfo()
{
  std::cout << "Usage: alphaDep THEORY SCHEME PDF" << std::endl
	    << "With THEORY    : \"moch\" or \"mitov\"" << std::endl
	    << "     SCHEME    : \"pole\" or \"msbar\"" << std::endl
	    << "     PDF       : \"mstw\", \"hera\", \"abm\", \"nnpdf\" or \"ct\"" << std::endl;
}

int alphaDep(const TheoryType theory, const bool pole, const PdfType pdf, const TString& fileName)
{
  const TString theoName = (theory ? "Top++ 2.0" : "Hathor 1.3");

  const TString massName = (pole ? "m_{t}^{pole}" : "m_{t}^{#bar{MS}}");

  TString pdfName;
  unsigned nPointsAlpha = 0;

  switch(pdf) {
  case kMSTW:
    pdfName = "MSTW2008"  ; nPointsAlpha = 21; break;
  case kHERA:
    pdfName = "HERAPDF1.5"; nPointsAlpha = 9 ; break;
  case kABM:
    pdfName = "ABM11"     ; nPointsAlpha = 17; break;
  case kNNPDF:
    pdfName = "NNPDF2.3"  ; nPointsAlpha = 11; break;
  case kCT:
    pdfName = "CT10"      ; nPointsAlpha = 21; break;
  }

  const unsigned minMass = 130;
  const unsigned maxMass = 220;
  const unsigned nPointsMass = maxMass - minMass + 1;
  const unsigned iMassCentral = (nPointsMass-1)/2;

  const unsigned iAlphaCentral = (nPointsAlpha-1)/2;

  ifstream inFile;
  inFile.open("theories_7TeV/"+fileName+".tab");
  
  if(!inFile) {
    std::cerr << "Can't find input file 'theories_7TeV/" << fileName << ".tab'!" << std::endl;
    return 66;
  }
  else if(inFile.eof())
    return 65;

  double alpha[nPointsAlpha];
  for(unsigned iAlpha=0; iAlpha<nPointsAlpha; iAlpha++)
    inFile >> alpha[iAlpha];

  char yTitle[99];
  sprintf(yTitle, "#sigma_{t#bar{t}} (#alpha_{S}) / #sigma_{t#bar{t}} (#alpha_{S} = %.3f)", alpha[iAlphaCentral]);

  TGraph graph[nPointsMass];

  TCanvas canvas("canvas", "canvas", 900, 600);
  canvas.Print(fileName + ".ps[");

  int iMass=-1;

  while( !inFile.eof() ) {
    double mt;
    double xsec[nPointsAlpha];
    inFile >> mt;
    for(unsigned i=0; i<nPointsAlpha; i++)
      inFile >> xsec[i];

    if( inFile.eof() )
      break;

    iMass++;

    for(unsigned iAlpha=0; iAlpha<nPointsAlpha; iAlpha++) {
      if(iAlpha==iAlphaCentral)
	continue;
      xsec[iAlpha] = xsec[iAlpha] / xsec[iAlphaCentral];
    }
    xsec[iAlphaCentral] = 1.;

    char title[99];
    sprintf(title, "NNLO+NNLL from %s with %s and %s = %.0f GeV", theoName.Data(), pdfName.Data(), massName.Data(), mt);

    std::cout << "mt: " << mt << std::endl;

    graph[iMass] = TGraph(nPointsAlpha, alpha, xsec);
    graph[iMass].SetTitle(title);
    graph[iMass].GetXaxis()->SetTitle("#alpha_{S}");
    graph[iMass].GetYaxis()->SetTitle(yTitle);
    graph[iMass].Draw("A*");
    graph[iMass].Fit("pol1", "Q");
    if(graph[iMass].GetFunction("pol1")) {
      graph[iMass].GetFunction("pol1")->SetLineStyle(2);
      graph[iMass].GetFunction("pol1")->SetLineColor(kBlue);
    }
    graph[iMass].Fit("pol2", "+");

    TLine line_hori(graph[iMass].GetXaxis()->GetXmin(), 1., alpha[iAlphaCentral], 1.);
    line_hori.SetLineStyle(3);
    line_hori.Draw();
    TLine line_vert(alpha[iAlphaCentral], graph[iMass].GetYaxis()->GetXmin(), alpha[iAlphaCentral], 1.);
    line_vert.SetLineStyle(3);
    line_vert.Draw();

    canvas.Print(fileName + ".ps");
    if(mt==173)
      canvas.Print(fileName + "_173.eps");
  }

  inFile.close();

  if(graph[0].GetFunction("pol2")) {
    char title[99];
    sprintf(title, "NNLO+NNLL from %s with %s and %s = %.0f-%.0f GeV",
	    theoName.Data(), pdfName.Data(), massName.Data(), (double)minMass, (double)maxMass);
    graph[0].GetFunction("pol2")->SetTitle(title);
    graph[0].GetFunction("pol2")->GetXaxis()->SetTitle("#alpha_{S}");
    graph[0].GetFunction("pol2")->GetYaxis()->SetTitle(yTitle);
    graph[0].GetFunction("pol2")->Draw("");
  }
  for(unsigned m=1; m<nPointsMass; m++)
    if(graph[m].GetFunction("pol2"))
      graph[m].GetFunction("pol2")->Draw("same");
  if(graph[iMassCentral].GetFunction("pol2")) {
    graph[iMassCentral].GetFunction("pol2")->SetLineColor(kBlack);
    graph[iMassCentral].GetFunction("pol2")->Draw("same");
  }
  if(graph[0].GetFunction("pol2")) {
    graph[0].GetFunction("pol2")->SetLineColor(kBlue);
    graph[0].GetFunction("pol2")->Draw("same");
  }
  if(graph[nPointsMass-1].GetFunction("pol2")) {
    graph[nPointsMass-1].GetFunction("pol2")->SetLineColor(kGreen);
    graph[nPointsMass-1].GetFunction("pol2")->Draw("same");
  }
  canvas.Print(fileName + ".ps");
  canvas.Print(fileName + ".png");

  double mass[nPointsMass];
  double par[3][nPointsMass];
  for(unsigned i=0; i<nPointsMass; i++) {
    mass[i] = minMass+i;
    if(!graph[i].GetFunction("pol2"))
      abort();
    for(unsigned p=0; p<3; p++)
      par[p][i] = graph[i].GetFunction("pol2")->GetParameter(p);
  }

  TFile outFile("theories_7TeV/"+fileName+".root", "RECREATE");

  TGraph graph_par[3];
  for(unsigned p=0; p<3; p++) {
    graph_par[p] = TGraph(nPointsMass, mass, par[p]);
    char title[99];
    sprintf(title, "NNLO+NNLL from %s with %s", theoName.Data(), pdfName.Data());
    graph_par[p].SetTitle(title);
    graph_par[p].GetXaxis()->SetTitle(massName + " [GeV]");
    char parName[99];
    sprintf(parName, "p_{%i}", p);
    graph_par[p].GetYaxis()->SetTitle(parName);
    graph_par[p].Draw("A*");
    if(pdf==kNNPDF)
      graph_par[p].Fit("pol1", "Q", "", 156., 174.);
    else
      graph_par[p].Fit("pol1", "Q");
    if(graph_par[p].GetFunction("pol1")) {
      graph_par[p].GetFunction("pol1")->SetLineStyle(2);
      graph_par[p].GetFunction("pol1")->SetLineColor(kBlue);
    }
    if(pdf==kNNPDF)
      graph_par[p].Fit("pol2", "+", "", 156., 174.);
    else
      graph_par[p].Fit("pol2", "+");
    sprintf(parName, "graph_p%i", p);
    graph_par[p].Write(parName);
    canvas.Print(fileName + ".ps");
    canvas.Print(fileName + "_" + parName +".eps");
  }

  outFile.Close();

  canvas.Print(fileName + ".ps]");

  return 0;
}

int main(const int argc, const char** argv)
{
  if(argc!=4) {
    std::cout << "Wrong number of arguments!" << std::endl;
    printInfo();
    return 64;
  }

  TheoryType theory;

  if(!strcmp(argv[1],"moch"))
    theory=kMoch;
  else if (!strcmp(argv[1],"mitov"))
    theory=kMitov;
  else {
    std::cout << "Unkown argument: " << argv[1] << std::endl;
    printInfo();
    return 64;
  }

  bool pole = true;

  if(!strcmp(argv[2],"msbar"))
    pole=false;
  else if (strcmp(argv[2],"pole")) {
    std::cout << "Unkown argument: " << argv[2] << std::endl;
    printInfo();
    return 64;
  }

  PdfType pdf;

  if(!strcmp(argv[3],"mstw"))
    pdf=kMSTW;
  else if (!strcmp(argv[3],"hera"))
    pdf=kHERA;
  else if (!strcmp(argv[3],"abm"))
    pdf=kABM;
  else if (!strcmp(argv[3],"nnpdf"))
    pdf=kNNPDF;
  else if (!strcmp(argv[3],"ct"))
    pdf=kCT;
  else {
    std::cout << "Unkown argument: " << argv[3] << std::endl;
    printInfo();
    return 64;
  }

  char fileName[99];
  //  sprintf(fileName, "%s_%s_%s_off_alphaDep", argv[1], argv[2], argv[3]);
  sprintf(fileName, "%s_%s_%s_alphaDep", argv[1], argv[2], argv[3]);

  return alphaDep(theory, pole, pdf, (TString)fileName);
}
