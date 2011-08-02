#ifndef BCC_CPP_
#define BCC_CPP_

// ======================================================================
//
//  Class for calculating Bin Center Corrections
// 
//   - Calculating correction in x as center of gravity for each bin
//   - Calculating statistical error in x
//   - In case of errors default values are geometrical bin center
//   
//  Input: 
//   
//   - ROOT-file with data tree
//   - std::vector<TString> with data branches to access
//   - Information if top and antitop branches shall be merged
// 
//  Output:
//  
//   - Corrected bin centers:
//     std::map<TString, std::vector<double> >
//   - Statistical error on corrected bin centers:
//     std::map<TString, std::vector<double> >
//
//  Error Codes:
// 
//    0: no error found
//   -1: input file not found
//   -2: error in configuration file: 
//       number of binning-vectors and variables not corresponding
//
// ======================================================================

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
           
    // Open file and get tree
    datafile = new TFile(filename,"READ");
    datafile -> cd(pathname); 

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

	    std::cout << " Processing Data for .... " << *iterBranch << std::endl;

	    treeData->SetBranchStatus("*",0);
	    treeData->SetBranchStatus(*iterBranch,1);
	    treeData->SetBranchAddress((*iterBranch),(&tempData));
	    
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
		
		if (iter != mapTempData.end() && iter->first.EndsWith("Lep")) strLep = (iter->first); 
		
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

// ==================================
//  Get Beam Centre Corrections in x
// ==================================

void BCC::setBCCinX()
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

// Statistical error on corrected bin centers

BCCMap BCC::getMapWithCenterErrorsInX()
{
    return mapCorrBinCenterErrorsInX;  
}

void BCC::runBCCCalculation()
{
    if (error_code == 0) setBCCinX(); 
    else setDefValues();
}

#endif
