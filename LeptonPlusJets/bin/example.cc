#include "iostream"
#include "TopAnalysis/LeptonPlusJets/interface/ExampleClass.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"

int main(int argc, char* argv[])
{
  
  if ( argc < 2 ) {
    std::cout << "Usage : " << argv[0] << " [parameters.py]" << std::endl;
    return 0;
  }
  else{
    std::cout << "+ +++" << std::endl;
    std::cout << "+ reading input file from " << argv[1] << std::endl; 
    std::cout << "+ +++" << std::endl;
  }
  if( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("plot") ){
    std::cout << " ERROR: ParametersSet 'plot' is missing in your configuration file" << std::endl; exit(0);
  }
  
  ExampleClass myClass(edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("plot"));
  myClass.plot();
  return 1;
}
