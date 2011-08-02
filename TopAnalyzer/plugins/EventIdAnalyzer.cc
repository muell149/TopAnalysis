#include "TopQuarkAnalysis/Examples/plugins/EventIdAnalyzer.h"


EventIdAnalyzer::EventIdAnalyzer(const edm::ParameterSet& cfg):
  verbose_(cfg.getParameter<bool>                ("verbose")),
  textFileName_(cfg.getParameter<std::string>    ("textFileName"))
{
  edm::Service<TFileService> fs;
  
  if(textFileName_!="") myfile.open (textFileName_.c_str());
  
    tree = fs->make<TTree>("EventIdTree","EventIdTree",0);
    tree->Branch("run", &run);
    tree->Branch("lumi", &lumi);
    tree->Branch("event", &event);


}

EventIdAnalyzer::~EventIdAnalyzer()
{
}

void
EventIdAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{

  // produce printout if desired
  
  if (verbose_)         std::cout << evt.eventAuxiliary().id() << std::endl;
  if (textFileName_!="") myfile << evt.eventAuxiliary().id() << std::endl;
  
  run   = (unsigned int) evt.id().run();
  lumi  = (unsigned int) evt.id().luminosityBlock();
  event = (unsigned int) evt.id().event();
  
  tree -> Fill();

}

void EventIdAnalyzer::beginJob()
{
}

void EventIdAnalyzer::endJob()
{
  if(textFileName_!="")  myfile.close();
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( EventIdAnalyzer );