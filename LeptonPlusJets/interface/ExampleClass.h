#include "TopAnalysis/TopUtils/interface/BaseMacro.h"

class ExampleClass : public BaseMacro {

 public:
  //
  ExampleClass(const edm::ParameterSet& cfg) : BaseMacro(cfg) {};
  //
  void plot();
  
  
 private:

};
