#include "TopAnalysis/LeptonPlusJets/interface/ExampleClass.h"

void
ExampleClass::plot()
{
  unsigned int ibin=0;
  std::vector<TCanvas*> canvs;
  for(HistMap::const_iterator hist=hists_.begin(); hist!=hists_.end(); ++hist, ++ibin){
    canvs.push_back(new TCanvas(TString::Format("canv_%d", ibin), "example plot", 600, 600)); canvs.back()->cd();
    for(std::vector<TH1*>::const_iterator sample=hist->second.begin(); sample!=hist->second.end(); ++sample){
      sample==hist->second.begin() ? (*sample)->Draw() : (*sample)->Draw("same");
    }
  }
  save(canvs, std::string("example"));
}
