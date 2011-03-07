#ifndef PDFUncertainty_h
#define PDFUncertainty_h

#include "DataFormats/Candidate/interface/Candidate.h"
#include "TopAnalysis/TopAnalyzer/interface/SingleObject.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

/**
   \class   PDFUncertainty PDFUncertainty.h "TopAnalysis/TopAnalyzer/interface/PDFUncertainty.h"

   \brief   Derived class to analyze PDF uncertainties

   The structure keeps histograms for PDF uncertainty analysis. These histograms are filled
   from the GenEventInfoProduct class. The class is derived from the SingleObject<Collection>
   interface, which makes it usable in full framework or fwlite. 
*/

class PDFUncertainty : public SingleObject< GenEventInfoProduct > {
  
 public:
  /// default constructor for fw lite
  explicit PDFUncertainty();
  /// default constructor for fwfull
  explicit PDFUncertainty(const edm::ParameterSet& configFile);
  /// default destructor
  ~PDFUncertainty(){};

  /**
     The following functions have to be implemented for any class
     derived from SingleObject<Collection>.
  **/
  /// histogramm booking for fwlite 
  void book();
  /// histogramm booking for fw
  void book(edm::Service<TFileService>& fileService);
  /// histogram filling interface for reconstruction level for access with fw or fwlite
  void fill(const GenEventInfoProduct& genEventInfoProduct, const double& weight=1.);
  /// everything which needs to be done after the event loop
  void process(){};
};

#endif
