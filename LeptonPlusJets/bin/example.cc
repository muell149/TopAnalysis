#include "FWCore/ParameterSet/interface/ProcessDesc.h"
#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"
#include "TopAnalysis/LeptonPlusJets/interface/BaseMacro.h"

int main(int argc, char* argv[])
{
  /*
  if ( argc < 2 ) {
    std::cout << "Usage : " << argv[0] << " [parameters.py]" << std::endl;
    return 0;
  }
  // Get the python configuration
  PythonProcessDesc builder(argv[1]);
  edm::ParameterSet const& fwliteParameters = builder.processDesc()->getProcessPSet()->getParameter<edm::ParameterSet>("FWLiteParams");
  */

  BaseMacro myClass(readoutConfig());
  //fwliteParameters.getParameter<edm::ParameterSet>("ExampleMacro"));
  myClass.finalPlot();
  return 1;
}
