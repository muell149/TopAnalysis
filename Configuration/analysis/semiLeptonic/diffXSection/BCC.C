#ifndef BCC_CPP_
#define BCC_CPP_

// =============================================================================
//
//  Class for calculating Bin Center Corrections
// 
//   a) - Calculating correction in x as center of gravity for each bin
//      - Calculating statistical error in x
//   b) - Calculating correction in x as intersection between fine binned
//        histogram and flat bin, code copied and adapted from [2]
//        
//        References:
//          [1] G. Lafferty and T. Wyatt, 
// 		"Where to Stick Data Points: 
//               The Treatment of Measurements within Wide Bins"
//              Nucl. Instr. and Methods, A355 (1995) 541
//          [2] https://hypernews.cern.ch/HyperNews/CMS/get/ewk/610.html
//  
//      - error in x is symmetric and half a bin width
//   
//   c) - In case of errors default values are geometrical bin center
//   
//  Input: 
//   
//   - ROOT-file with data tree
//   - std::vector<TString> with data branches to access
//   - Information if top and antitop branches shall be merged
// 
//  Output (accessible by public get-functions):
//  
//   - Corrected bin centers:
//     std::map<TString, std::vector<double> >
//   - Error on corrected bin centers:
//     std::map<TString, std::vector<double> >
//   - error code (definiton below)
//
//  Error Codes:
// 
//    0: No error found
//   -1: Input file not found
//   -2: Error in configuration file: 
//       number of binning-vectors and variables not corresponding
//   -3: Error while data filling into histograms 
//       number of binning-vectors and histograms not corresponding
//
// =============================================================================

#include "BCC.h"
#include "basicFunctions.h"

// ==============
//  Constructors
// ==============

BCC::BCC(){}

BCC::BCC(TString filename, TString pathname, std::vector<TString> vecBranches, bool mergeLepHad)
{
    error_code = 0;
    
    // Please provide your own function 'makeVariableBinning' producing a std::map with your binning
    
    mapBinning  = makeVariableBinning();
           
    // Set variable 'largeMGFile', open file and get tree

    largeMGFile = (filename.Contains("Large")) ? 1 : 0;

    datafile = new TFile(filename,"READ");
    datafile -> cd(pathname); 

    std::cout << filename << " " <<  pathname << std::endl;

    TTree *treeData = (TTree*)gDirectory->Get("tree");
    
    // Local variables

    float tempData = 0;
    std::vector<double> vecBranchData;
    BCCMap mapTempData;

    if (datafile)
    { 
	// fill data from tree into temporary map

	for (std::vector<TString>::iterator iterBranch = vecBranches.begin(); iterBranch != vecBranches.end(); iterBranch++)
	{
	    vecBranchData.clear();

	    std::cout << " Processing Data for .... " << *iterBranch;
	    
	    TString activeBranchName = "";
	    activeBranchName = (*iterBranch);	    

	    std::cout << " --> " << activeBranchName << std::endl;

	    treeData->SetBranchStatus("*",0);
	    treeData->SetBranchStatus(activeBranchName,1);
	    treeData->SetBranchAddress(activeBranchName,(&tempData));
	    
	    for (int j=0; j<treeData->GetEntries(); j++)
	    {	
		treeData->GetEntry(j);
		vecBranchData.push_back(tempData);		
	    }

	    mapTempData[*iterBranch] = vecBranchData; 	    
	}
	
	vecBranchData.clear();

	// Merge data for top- and antitop-quarks if no distinction between them is required

	if (mergeLepHad)
	{
	    TString strNew, strHad, strLep;
	    
	    for (BCCMap::iterator iter = mapTempData.begin(); iter != mapTempData.end(); iter++)
	    {
		vecBranchData.clear();

		// Default values

		strHad = "DefaultHad";
		strLep = "DefaultLep";
		strNew = iter->first;
		vecBranchData = iter->second; 
		
		// Check if data belong to top -> bqq'
		
		if (iter != mapTempData.end() && iter->first.EndsWith("Had"))
		{ 
		    strHad = (iter->first); 
		    iter++;
		}
		
		// Check if immediately following entry in map belongs to top -> blnu 
		// This works because the map is sorted alphabetically -> must be reviewed and fixed if new a branch is added between topxxHad and topxxLep
		
		if (iter != mapTempData.end() && iter->first.EndsWith("Lep"))    strLep = (iter->first); 

		if (strHad != "DefaultHad" && strLep != "DefaultLep" && strHad(0,strHad.Length()-3) == strLep(0,strLep.Length()-3) )
		{
		    strNew = iter->first(0,(iter->first).Length()-3);
		    vecBranchData.insert(vecBranchData.end(),iter->second.begin(),iter->second.end());		    
		}

		mapData[strNew] = vecBranchData;
	    }
	}

	if (mapBinning.size() != mapData.size() )
	{
	    error_code = -2;
	    std::cout << " WARNING ---- Size of maps for binning and data do not correspond!"     << std::endl;
	    std::cout << " WARNING ---- Calculation of corrected bin centres will be suppressed." << std::endl;
	    std::cout << " WARNING ---- Switch to geometrical centres as default values."         << std::endl;
	}
	else
	{
	    for (BCCMap::iterator iter = mapData.begin(); iter != mapData.end(); iter++) 

		std::cout << " Creating new branch .... " << iter->first << " with " << iter->second.size() << " entries." << std::endl;

	    MakeHistos();	    
	}	
    }
    else 
    {
	std::cout << "Input Data File not found. " << std::endl;
	error_code = -1;
    }
}

// ============
//  Destructor
// ============

BCC::~BCC(){}

// ============
//  Error Code
// ============

int BCC::getErrorCode()
{
  return error_code;
}

// =================================================
//  Set Default Values to Maps (error handling)
// =================================================

void BCC::setDefValues()
{
    std::cout << "Accessing Default Function." << std::endl;
    
    std::vector<double> vecTempBCCs;
    std::vector<double> vecTempBCCErrors;

    for (BCCMap::iterator iter = mapBinning.begin(); iter !=  mapBinning.end(); iter++ )
    {  
	std::vector<double>& refVecTempBinning = mapBinning[iter->first];  // required for ROOT purposes

	for (unsigned int bin = 1; bin < refVecTempBinning.size(); bin++)
	{
	    vecTempBCCs.push_back(refVecTempBinning[bin-1]+0.5*(refVecTempBinning[bin]-refVecTempBinning[bin-1])); 
	    vecTempBCCErrors.push_back(0.5*(refVecTempBinning[bin]-refVecTempBinning[bin-1]));
	}	

	mapCorrBinCentersInX[iter->first]      = vecTempBCCs;
	mapCorrBinCenterErrorsInX[iter->first] = vecTempBCCErrors;
	
	vecTempBCCs.clear();
	vecTempBCCErrors.clear();       
    }
}
// =================================================
//  Set Theory Histos
// =================================================

void BCC::MakeHistos()
{
  TString hname = "";
  double binmin = 0.0;
  double binmax = 1.0;
	
  // Can be replaced by a non-static way of finding an optimal binning
	
  std::map<TString,double> BinWidthScaler;
  std::map<TString,int>    HistoBins; 
  std::map<TString,int>    HistoSmoothingValue;

  BinWidthScaler["lepEta"]    = 20.0;
  BinWidthScaler["lepPt"]     =  0.4;
  BinWidthScaler["topPt"]     =  0.2;
  BinWidthScaler["topY"]      = 20.0;
  BinWidthScaler["ttbarMass"] =  0.2;
  BinWidthScaler["ttbarPt"]   =  0.5;
  BinWidthScaler["ttbarY"]    = 20.0;
  BinWidthScaler["bqPt"]      =  0.2;
  BinWidthScaler["bqEta"]     = 20.0;

  HistoBins["lepEta"]    = 200;
  HistoBins["lepPt"]     = 160;
  HistoBins["topPt"]     = 160;
  HistoBins["topY"]      = 200;
  HistoBins["ttbarMass"] = 240;
  HistoBins["ttbarPt"]   = 300;
  HistoBins["ttbarY"]    = 200;
  HistoBins["bqPt"]      = 160;
  HistoBins["bqEta"]     = 200;

  HistoSmoothingValue["lepEta"]    = (largeMGFile) ? 1 :  4;
  HistoSmoothingValue["lepPt"]     = (largeMGFile) ? 0 :  0;
  HistoSmoothingValue["topPt"]     = (largeMGFile) ? 1 : 10;
  HistoSmoothingValue["topY"]      = (largeMGFile) ? 1 :  5;
  HistoSmoothingValue["ttbarMass"] = (largeMGFile) ? 1 : 10;
  HistoSmoothingValue["ttbarPt"]   = (largeMGFile) ? 1 :  5;
  HistoSmoothingValue["ttbarY"]    = (largeMGFile) ? 0 :  2;
  HistoSmoothingValue["bqPt"]      = (largeMGFile) ? 0 :  0;
  HistoSmoothingValue["bqEta"]     = (largeMGFile) ? 2 :  2;

  for (BCCMap::iterator iter = mapData.begin(); iter != mapData.end(); iter++)
  {
    std::vector<double>& refVecTempBinning = mapBinning[iter->first];  // required for ROOT purposes
    std::vector<double>& refVecTempData    = iter->second;	       // required for ROOT purposes
    
    std::vector<double>::iterator iterVecData;
    
    hname  = iter->first;
    binmin = refVecTempBinning[0];
    binmax = refVecTempBinning[refVecTempBinning.size()-1];
    
    TH1F temphisto(hname,hname, BinWidthScaler[hname]*(binmax-binmin),binmin,binmax);
    //TH1F temphisto(hname,hname, HistoBins[hname], binmin, binmax);
    
    for (iterVecData = refVecTempData.begin(); iterVecData != refVecTempData.end(); iterVecData++ )
      temphisto.Fill(*iterVecData);

    temphisto.Smooth(HistoSmoothingValue[hname]);
    mapHistos[hname] = temphisto;
  }
  
  if (mapBinning.size() != mapHistos.size() )
  {
    error_code = -3;
    std::cout << " WARNING ---- Size of maps for binning and histograms do not correspond!" << std::endl;
    std::cout << " WARNING ---- Calculation of corrected bin centres will be suppressed."   << std::endl;
    std::cout << " WARNING ---- Switch to geometrical centres as default values."           << std::endl;
  }
  else
  {
    for (std::map<TString, TH1F>::iterator iterHistos = mapHistos.begin(); iterHistos != mapHistos.end(); iterHistos++)
          
      std::cout << " Creating new histo .... " << (iterHistos->first) << " with " << (iterHistos->second).GetEntries() << " entries." << std::endl;
  }	
}

// =======================================================
//  Set Beam Centre Corrections in x where coarsely 
//  binned histogram intersects smooth curve
// =======================================================

void BCC::setBCCinX_IntersectionInBin()
{
  for (std::map<TString, TH1F>::iterator iterHistos = mapHistos.begin(); iterHistos != mapHistos.end(); iterHistos++)
  {
    TH1F& refHisto                     = iterHistos->second;	         // required for ROOT purposes
    std::vector<double>& refVecBinning = mapBinning[iterHistos->first];  // required for ROOT purposes
    
    //Note that the bins of the theory histogram should be sub-bins of the corr. data histogram
    
    const int NBinsTheory = refHisto.GetNbinsX();
    const int NBinsData   = refVecBinning.size()-1;  // -1 because refVecBinning contains bin boundaries
    
    std::cout << " Processing BCC for " << iterHistos->first << " .... NBinsTheory: " << NBinsTheory << " and NBinsData: " << NBinsData << std::endl;
    
    double weight = 0.0;
    double sumWeights[NBinsData];
    double integral[NBinsData];
    double average[NBinsData];
    double avXvalues[NBinsData]; 
    
    std::vector<double> vecTempBCCs;
    std::vector<double> vecTempBCCErrors;
    
    int NTheoryBinsPerDataBin[NBinsData];
    
    // Reset variables:
    
    for(int jBinData=0; jBinData < NBinsData; jBinData++)
    {
      sumWeights[jBinData] = 0.0;
      integral[jBinData]   = 0.0;
      average[jBinData]    = 0.0;
      NTheoryBinsPerDataBin[jBinData] = 0;
      avXvalues[jBinData]  = 0.0;
    }
    
    // Loop over bins of theory histogram and check into which data this falls
    // Calculate expressions needed for the weighted average
    
    for (int jBinTheory = 1; jBinTheory <= NBinsTheory; jBinTheory++)
    {
      double xTheory = refHisto.GetBinCenter(jBinTheory);
      
      for(int jBinData = 0; jBinData < NBinsData; jBinData++)
      {
	if (xTheory > refVecBinning[jBinData] && xTheory < refVecBinning[jBinData+1])
	{
	  weight                = refHisto.GetBinContent(jBinTheory);  // y-value of theory bin
	  integral[jBinData]   += weight * xTheory;                    // integral over theory histogram 
	  sumWeights[jBinData] += weight;			       // will later be used for mean value over data bin	
	  NTheoryBinsPerDataBin[jBinData]++;
	}	
      }			
    }
    
    // Determine x-values at which mean y-entry in data bin intersects y-value of theory histogram
    
    double min  = 0.0;
    
    for (int jBinData = 0; jBinData < NBinsData; jBinData++)
    {
      if(sumWeights[jBinData] > 0.0)
      {
	min = (double)LONG_MAX;
	
	average[jBinData] = sumWeights[jBinData]/NTheoryBinsPerDataBin[jBinData];
	
	for(int jBinTheory = 1; jBinTheory <= NBinsTheory; jBinTheory++)
	{
	  double xTheory     = refHisto.GetBinCenter(jBinTheory);
	  double diff        = fabs(average[jBinData] - refHisto.GetBinContent(jBinTheory));
	  
	  if ( (xTheory > refVecBinning[jBinData] && xTheory < refVecBinning[jBinData+1]) && diff < min ) 
	  {
	    min = diff;
	    avXvalues[jBinData] = refHisto.GetBinCenter(jBinTheory);					
	  }
	}
      }			
      
      std::cout << Form(" Bin %1.2f .... %1.2f : mean data = %1.4f and mean x = %1.2f",
      			  refVecBinning[jBinData], refVecBinning[jBinData+1], average[jBinData], avXvalues[jBinData]) << std::endl;			
      
      vecTempBCCs.push_back(avXvalues[jBinData]);
      vecTempBCCErrors.push_back(0.5*refHisto.GetXaxis()->GetBinWidth(1));
    }
    
    mapCorrBinCentersInX[iterHistos->first]      = vecTempBCCs;
    mapCorrBinCenterErrorsInX[iterHistos->first] = vecTempBCCErrors;
    
    vecTempBCCs.clear();
    vecTempBCCErrors.clear();
  }	
}

// =======================================================
//  Set Beam Centre Corrections in x as mean over bin
// =======================================================

void BCC::setBCCinX_MeanOverBin()
{		
  double sum, error;
  int NEVE;

  for (BCCMap::iterator iter = mapData.begin(); iter != mapData.end(); iter++)
  {	
    std::vector<double>& refVecTempBinning = mapBinning[iter->first];  // required for ROOT purposes
    std::vector<double>& refVecTempData    = iter->second;	           // required for ROOT purposes
    std::vector<double>  vecTempBCCs;
    std::vector<double>  vecTempBCCErrors;
    
    std::cout << iter->first                << ": ";
    std::cout << refVecTempBinning.size()-1 << " bins, ";
    std::cout << refVecTempData.size()      << " events." << std::endl;
    
    // Sort vector to ease comparision to bin boundaries (think of 'binning' the vector)
    
    std::sort(refVecTempData.begin(),refVecTempData.end());
    
    // ======================================================
    //  Get Corrected Bin Centre - center of gravity per bin
    // ======================================================
    
    // Get Mean Value
    
    unsigned int indexData = 0;
    
    for (indexData = 0; indexData < refVecTempData.size();)
    {
      for (unsigned int bin = 1; bin < refVecTempBinning.size(); bin++)
      {
	// std::cout << "Upper Bin Boundary: " << refVecTempBinning[bin]; 
	
	sum  = 0;
	NEVE = 0;
	
	while (refVecTempData[indexData] < refVecTempBinning[bin] && indexData < refVecTempData.size() )
	{
	  sum += refVecTempData[indexData];
	  indexData++;
	  NEVE++;
	}
	
	// std::cout << " " <<(sum/(double)NEVE) << " " << NEVE << std::endl;
	
	(NEVE > 0) ? vecTempBCCs.push_back(sum/(double)NEVE) : vecTempBCCs.push_back(refVecTempBinning[bin-1]+0.5*(refVecTempBinning[bin]-refVecTempBinning[bin-1]));  // fill vector with corrected bin centers 
	
	//  compensation of endless loop for data which would be assigned to the overflow bin
	
	while (refVecTempData[indexData] > refVecTempBinning[refVecTempBinning.size()-1] && indexData < refVecTempData.size() ) indexData++; 
      }	    
    }
    
    // Get Statistical Error
    
    indexData = 0;
	
    for (unsigned int bin = 1; bin < refVecTempBinning.size(); bin++)
    {
      error = 0;
      NEVE  = 0;
      
      while (refVecTempData[indexData] < refVecTempBinning[bin] && indexData < refVecTempData.size() )
      {
	error += pow(refVecTempData[indexData]-vecTempBCCs[bin-1],2);
	indexData++;
	NEVE++;
      }
      
      // std::cout << " " << sqrt(error)/(double)NEVE << " " << NEVE << std::endl; 
      
      (NEVE != 0) ? vecTempBCCErrors.push_back(sqrt(error)/(double)NEVE) : vecTempBCCErrors.push_back(0);  // fill vector with statistical errors on corrected bin centers
    }
    
    // fill maps
    
    mapCorrBinCentersInX[iter->first]      = vecTempBCCs;
    mapCorrBinCenterErrorsInX[iter->first] = vecTempBCCErrors;
    
    vecTempBCCs.clear();
    vecTempBCCErrors.clear();       
  }
}

// ================================================
//  Functions to pass results to external calls
// ================================================

// Corrected bin centers

BCCMap BCC::getMapWithCorrectedCentersInX()
{
    return mapCorrBinCentersInX;  
}

// Error on corrected bin centers

BCCMap BCC::getMapWithCenterErrorsInX()
{
    return mapCorrBinCenterErrorsInX;  
}

// ================================================
//  Main test routine
// ================================================

void BCC::runBCCCalculation()
{
  if (error_code == 0)
  { 
    setBCCinX_IntersectionInBin();
    //setBCCinX_MeanOverBin(); 
  }
  else setDefValues();    
}

#endif
