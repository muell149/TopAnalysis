#include "TopAnalysis/LeptonPlusJets/interface/ExampleClass.h"

void
ExampleClass::plot()
{
  unsigned int ibin=0;
  std::vector<TCanvas*> canvs;
  for(HistMap::const_iterator hist=hists_.begin(); hist!=hists_.end(); ++hist, ++ibin){
    std::cout << "hist  = " << hist->first << std::endl;
    canvs.push_back(new TCanvas(TString::Format("canv_%d", ibin), "example plot", 600, 600)); canvs.back()->cd();
    for(std::map<std::string, TH1*>::const_iterator sample=hist->second.begin(); sample!=hist->second.end(); ++sample){
      std::cout << "sample = " << sample->first << std::endl;
      sample==hist->second.begin() ? sample->second->Draw() : sample->second->Draw("same");
    }
    canvs.back()->Update();
  }
  save(canvs, std::string("example"));
}
