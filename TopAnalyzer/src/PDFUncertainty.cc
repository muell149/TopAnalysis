#include "TopAnalysis/TopAnalyzer/interface/PDFUncertainty.h"

#include "LHAPDF/LHAPDF.h"

/// default constructor for fw lite
PDFUncertainty::PDFUncertainty()
{
  LHAPDF::initPDFSet(1, "cteq66.LHgrid");
  tree = 0;
}

/// default constructor for full fw
PDFUncertainty::PDFUncertainty(const edm::ParameterSet& cfg)
{
  LHAPDF::initPDFSet(1, "cteq66.LHgrid");
  tree = 0;
}

/// histogramm booking for fwlite 
void PDFUncertainty::book()
{
  /** 
      Add needed histogramms from full fw list of histogramms
  **/
}

/// histogramm booking for fw
void PDFUncertainty::book(edm::Service<TFileService>& fs)
{
  /** 
      histograms to keep PDF uncertainty information
  **/

  for(unsigned i=1; i <=44; ++i) {
    // name PDFs
    TString nam = "pdf"; nam+=i;
    std::string name = nam.Data();
    // histograms with event weights
    bookVariable( fs, name.c_str(),  500,  0. , 5. , false );
    // tree branches with event weights
    bookVariable( fs, name.c_str() );
  }
}

/// histogram filling interface for reconstruction level for access with fwlite or full framework
void
PDFUncertainty::fill(const GenEventInfoProduct& genEventInfoProduct, const double& weight)
{
  float Q   = genEventInfoProduct.pdf()->scalePDF;
  int id1   = genEventInfoProduct.pdf()->id.first;
  int id2   = genEventInfoProduct.pdf()->id.second;
  double x1 = genEventInfoProduct.pdf()->x.first;
  double x2 = genEventInfoProduct.pdf()->x.second;
  double w0 = 0.;
  for(unsigned i=0; i <=44; ++i) {
    TString nam = "pdf"; nam+=i;
    std::string name = nam.Data();
    LHAPDF::usePDFMember(1,i);
    double xpdf1 = LHAPDF::xfx(1, x1, Q, id1);
    double xpdf2 = LHAPDF::xfx(1, x2, Q, id2);
    if(i<1)
      w0 = xpdf1 * xpdf2;
    else
      fillValue(name , xpdf1 * xpdf2 / w0, weight);
  }
  // fill the tree, if any variable should be put in
  if(treeVars_.size()) tree->Fill();
}
