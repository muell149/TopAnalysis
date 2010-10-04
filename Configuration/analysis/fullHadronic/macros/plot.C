#include "TPlot.h"

void plot(){

  prepareEverything(false); // shape normalization

  addCanvs("Stats dipl"); // Kin_0 Kin_1 Shap_0 Shap_1 Spec_0 Spec_1 Qual_0 Qual_1 Stats dipl ... see TPlot.h
  getFiles(3.07180); // luminosity in pb-1 (only needed if NOT normalized to shape)
  fillHistograms("pf"); // pf calo mad_pf mad_calo ... see TPlot.h

  drawMC();
  drawData();

  //saveToPng();
  //saveToPs();

  printCutFlow();

  std::cout << "Successfully finished program execution!" << std::endl;
}
