#include "TopAnalysis/LeptonPlusJets/interface/ExampleClass.h"

void
ExampleClass::finalPlot()
{
  TCanvas* canv = new TCanvas("canv", "examples plot", 600, 600);
  canv->cd();

  /*
    
  */

  //for(int i=0;....){
  hists_["pt"][0]->Draw();
  // draw my legend or my label
  save(*canv, "exampleFile.root");
}
