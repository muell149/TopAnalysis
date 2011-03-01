#include "iostream"
#include "TopAnalysis/LeptonPlusJets/interface/ExampleClass.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"

int main(int argc, char* argv[])
{
  
  if ( argc < 2 ) {
    std::cout << "Usage : " << argv[0] << " [parameters.py]" << std::endl;
    return 0;
  }
  // Get the python configuration
  const edm::ParameterSet& params = *(edm::readPSetsFrom(argv[1]));
  
  //BaseMacro myClass(readoutConfig());
  //fwliteParameters.getParameter<edm::ParameterSet>("ExampleMacro"));
  //myClass.finalPlot();
  return 1;
}
