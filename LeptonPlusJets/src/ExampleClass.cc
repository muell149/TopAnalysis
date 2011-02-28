#include "TopAnalysis/LeptonPlusJets/interface/ExampleClass.h"

ExampleClass::finalPlot()
{
  TCanvas* canv = new TCanvas("canv", "examples plot", 600, 600);
  canv->cd();

  /*
    
  */

  //for(int i=0;....){
  hist_[0]->Draw();
  hist_[1]->Draw("same");
  // draw my legend or my label
  save(*canv, "exampleFile.root")
}
