#include <stdio.h>

#include "TopAnalysis/TopAnalyzer/interface/FullHadTreeWriter.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
//#include "DataFormats/Candidate/interface/Candidate.h"
//#include "DataFormats/Candidate/interface/LeafCandidate.h"
#include "AnalysisDataFormats/TopObjects/interface/TtFullHadEvtPartons.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

/// default constructor
FullHadTreeWriter::FullHadTreeWriter(const edm::ParameterSet& cfg) :
  JetSrc_(cfg.getParameter<edm::InputTag>("JetSrc")),
  FitSrc_(cfg.getParameter<edm::InputTag>("FitSrc")),
  GenSrc_(cfg.getParameter<edm::InputTag>("GenSrc")),
  bTagName_(cfg.getParameter<std::vector<std::string> >("bTagName")),
  bTagVal_ (cfg.getParameter<std::vector<std::string> >("bTagVal" )),
  kMAX(50),
  kBTagMAX(cfg.getParameter<unsigned int>("bTagParams")),
  doPDFUncertainty(false)
{
}

/// default destructor
FullHadTreeWriter::~FullHadTreeWriter()
{
}

/// initiate histograms
void
FullHadTreeWriter::beginJob()
{
  // define TFileService which takes care of writing contents to root file
  edm::Service<TFileService> fs;
  if( !fs ) throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  // define the tree and make it known to the TFileService
  tree = fs->make<TTree>("tree","tree",0);

  // event identifiers
  runNumber = 0;
  tree->Branch("runNumber", &runNumber, "runNumber/i");
  luminosityBlockNumber = 0;
  tree->Branch("luminosityBlockNumber", &luminosityBlockNumber, "luminosityBlockNumber/i");
  eventNumber= 0;
  tree->Branch("eventNumber", &eventNumber, "eventNumber/i");

  // event weight
  weight = -1.;
  tree->Branch("weight", &weight, "weight/F");

  /// jets

  // 4-vectors of jets
  jets = new TClonesArray("TLorentzVector", kMAX);
  tree->Branch("jets", &jets, 32000, -1);
  jets->BypassStreamer();

  // number of jets in events
  Njet = -1;
  tree->Branch("Njet", &Njet, "Njet/I");

  // b-tag discriminators of jets
  bTag_TCHE     = new float[(kBTagMAX+1)*kMAX];
  bTag_TCHP     = new float[(kBTagMAX+1)*kMAX];
  bTag_SSVHE    = new float[(kBTagMAX+1)*kMAX];
  bTag_SSVHP    = new float[(kBTagMAX+1)*kMAX];
  bTag_CSV      = new float[kMAX];
  bTag_CSVMVA   = new float[kMAX];
  pdgId         = new short[kMAX];
  partonFlavour = new short[kMAX];
  for(unsigned short i = 0; i < kMAX; ++i) {
    for(unsigned short j = 0; j < kBTagMAX+1; ++j) {
      bTag_TCHE  [i*j+j] = -100.;
      bTag_TCHP  [i*j+j] = -100.;
      bTag_SSVHE [i*j+j] = -100.;
      bTag_SSVHP [i*j+j] = -100.;
    }
    bTag_CSV     [i] = -100.;
    bTag_CSVMVA  [i] = -100.;
    pdgId        [i] =    0 ;
    partonFlavour[i] =    0 ;
  }
  char buffer[7];
  sprintf(buffer, "[%i]/F", kBTagMAX+1);
  //std::cout << (std::string("bTag_TCHE[Njet]") + std::string(buffer)).c_str() << std::endl;
  tree->Branch("bTag_TCHE"    , bTag_TCHE    , (std::string("bTag_TCHE[Njet]" ) + std::string(buffer)).c_str() );
  tree->Branch("bTag_TCHP"    , bTag_TCHP    , (std::string("bTag_TCHP[Njet]" ) + std::string(buffer)).c_str() );
  tree->Branch("bTag_SSVHE"   , bTag_SSVHE   , (std::string("bTag_SSVHE[Njet]") + std::string(buffer)).c_str() );
  tree->Branch("bTag_SSVHP"   , bTag_SSVHP   , (std::string("bTag_SSVHP[Njet]") + std::string(buffer)).c_str() );
  tree->Branch("bTag_CSV"     , bTag_CSV     , "bTag_CSV[Njet]/F"     );
  tree->Branch("bTag_CSVMVA"  , bTag_CSVMVA  , "bTag_CSVMVA[Njet]/F"  );
  tree->Branch("pdgId"        , pdgId        , "pdgId[Njet]/S"        );
  tree->Branch("partonFlavour", partonFlavour, "partonFlavour[Njet]/S");

  measureMap["BTAGBEFF"]=PerformanceResult::BTAGBEFF;
  measureMap["BTAGBERR"]=PerformanceResult::BTAGBERR;
  measureMap["BTAGCEFF"]=PerformanceResult::BTAGCEFF;
  measureMap["BTAGCERR"]=PerformanceResult::BTAGCERR;
  measureMap["BTAGLEFF"]=PerformanceResult::BTAGLEFF;
  measureMap["BTAGLERR"]=PerformanceResult::BTAGLERR;
  measureMap["BTAGNBEFF"]=PerformanceResult::BTAGNBEFF;
  measureMap["BTAGNBERR"]=PerformanceResult::BTAGNBERR;
  measureMap["BTAGBEFFCORR"]=PerformanceResult::BTAGBEFFCORR;
  measureMap["BTAGBERRCORR"]=PerformanceResult::BTAGBERRCORR;
  measureMap["BTAGCEFFCORR"]=PerformanceResult::BTAGCEFFCORR;
  measureMap["BTAGCERRCORR"]=PerformanceResult::BTAGCERRCORR;
  measureMap["BTAGLEFFCORR"]=PerformanceResult::BTAGLEFFCORR;
  measureMap["BTAGLERRCORR"]=PerformanceResult::BTAGLERRCORR;
  measureMap["BTAGNBEFFCORR"]=PerformanceResult::BTAGNBEFFCORR;
  measureMap["BTAGNBERRCORR"]=PerformanceResult::BTAGNBERRCORR;
  measureMap["BTAGNBERRCORR"]=PerformanceResult::BTAGNBERRCORR;
  measureMap["MUEFF"]=PerformanceResult::MUEFF;
  measureMap["MUERR"]=PerformanceResult::MUERR;
  measureMap["MUFAKE"]=PerformanceResult::MUFAKE; 
  measureMap["MUEFAKE"]=PerformanceResult::MUEFAKE;

  /// kinFit properties

  // probability and chi2 of kinematic fit
  prob    = -1.;
  chi2    = -1.;
  topMass = -1.;
  comboTypeValue = 0;
  tree->Branch("prob"     , &prob          , "prob/F"     );
  tree->Branch("chi2"     , &chi2          , "chi2/F"     );
  tree->Branch("topMass"  , &topMass       , "topMass/F"  );
  tree->Branch("comboType", &comboTypeValue, "comboType/s");

  // jet-parton assignments
  fitAssigns = new short[6];
  for(short i = 0; i < 6; ++i){
    fitAssigns[i] = -1;
  }
  tree->Branch("fitAssigns", fitAssigns , "fitAssigns[6]/S");

  // 4-vectors of kinFit
  fitVecs = new TClonesArray("TLorentzVector", 6);
  tree->Branch("fitVecs", &fitVecs, 32000, -1);
  fitVecs->BypassStreamer();

  /// genEvent information for PDF uncertainty

  id1 = -100;
  id2 = -100;
  Q   = -1.;
  x1  = -1.;
  x2  = -1.;

  // genEvent information not saved to tree if not needed
  if(GenSrc_.label() == "") return;

  doPDFUncertainty = true;

  tree->Branch("id1", &id1, "id1/I");
  tree->Branch("id2", &id2, "id2/I");
  tree->Branch("Q"  , &Q  , "Q/F"  );
  tree->Branch("x1" , &x1 , "x1/D" );
  tree->Branch("x2" , &x2 , "x2/D" );

}

/// produce n-tuple
void
FullHadTreeWriter::analyze(const edm::Event& event, const edm::EventSetup& iSetup)
{
  // Event
  edm::EventAuxiliary aux = event.eventAuxiliary();
  runNumber             = aux.run();
  luminosityBlockNumber = aux.luminosityBlock();
  eventNumber           = aux.event();

  edm::Handle<edm::View< pat::Jet > > jets_h;
  event.getByLabel(JetSrc_, jets_h);
  
  edm::Handle<TtFullHadronicEvent> fullHadEvent_h;
  event.getByLabel(FitSrc_, fullHadEvent_h);
  
  edm::Handle<GenEventInfoProduct> genEventInfo_h;
  event.getByLabel(GenSrc_, genEventInfo_h);
  
  edm::ESHandle<BtagPerformance> bTagPerf_h;

  if(jets_h.isValid()){
    Njet = (int)jets_h->size();

    unsigned short i = 0;
    jets->Delete();
    for(edm::View< pat::Jet >::const_iterator jet = jets_h->begin(); jet != jets_h->end(); ++jet, ++i){
      new((*jets)[i]) TLorentzVector(jet->px(), jet->py(), jet->pz(), jet->energy());
      bTag_TCHE  [i*(kBTagMAX+1)] = jet->bDiscriminator("trackCountingHighEffBJetTags");
      bTag_TCHP  [i*(kBTagMAX+1)] = jet->bDiscriminator("trackCountingHighPurBJetTags");
      bTag_SSVHE [i*(kBTagMAX+1)] = jet->bDiscriminator("simpleSecondaryVertexHighEffBJetTags");
      bTag_SSVHP [i*(kBTagMAX+1)] = jet->bDiscriminator("simpleSecondaryVertexHighPurBJetTags");
      bTag_CSV     [i]            = jet->bDiscriminator("combinedSecondaryVertexBJetTags");
      bTag_CSVMVA  [i]            = jet->bDiscriminator("combinedSecondaryVertexMVABJetTags");
      pdgId        [i]            = (jet->genParticle()) ? jet->genParticle()->pdgId() : 0;
      partonFlavour[i]            = jet->partonFlavour();
      
      if(kBTagMAX > 0){ 
	unsigned short arrayCount = 0;
	for( size_t ibTag = 0; ibTag < bTagName_.size(); ++ibTag , ++arrayCount ){

	  if(arrayCount == kBTagMAX) arrayCount = 0;

	  iSetup.get<BTagPerformanceRecord>().get( bTagName_[ibTag],bTagPerf_h);
	  const BtagPerformance & bTagPerf = *(bTagPerf_h.product());

	  BinningPointByMap measurePoint;
	  measurePoint.insert(BinningVariables::JetEt,jet->et());
	  measurePoint.insert(BinningVariables::JetAbsEta,std::abs(jet->eta()));

	  if     (bTagName_[ibTag].find("TCHEM" )!=std::string::npos) bTag_TCHE [i*(kBTagMAX+1)+arrayCount+1] = bTagPerf.getResult( measureMap[bTagVal_[ibTag]], measurePoint);
	  else if(bTagName_[ibTag].find("TCHPT" )!=std::string::npos) bTag_TCHP [i*(kBTagMAX+1)+arrayCount+1] = bTagPerf.getResult( measureMap[bTagVal_[ibTag]], measurePoint);
	  else if(bTagName_[ibTag].find("SSVHEM")!=std::string::npos) bTag_SSVHE[i*(kBTagMAX+1)+arrayCount+1] = bTagPerf.getResult( measureMap[bTagVal_[ibTag]], measurePoint);
	  else if(bTagName_[ibTag].find("SSVHPT")!=std::string::npos) bTag_SSVHP[i*(kBTagMAX+1)+arrayCount+1] = bTagPerf.getResult( measureMap[bTagVal_[ibTag]], measurePoint);

	}
      }
      /*
      //////////
      

      for( size_t ibTag = 0; ibTag < bTagName_.size(); ++ibTag )
	{
	  std::cout << "Testing: " << bTagName_[ ibTag ] << " of type " << bTagVal_[ ibTag ] << std::endl;

	  //Setup our measurement
	  iSetup.get<BTagPerformanceRecord>().get( bTagName_[ ibTag ],bTagPerf_h);
	  const BtagPerformance & bTagPerf = *(bTagPerf_h.product());

	  //Working point
	  std::cout << "Working point: " << bTagPerf.workingPoint().cut() << std::endl;
	  //Setup the point we wish to test!
	  BinningPointByMap measurePoint;
	  measurePoint.insert(BinningVariables::JetEt,jet->pt());
	  measurePoint.insert(BinningVariables::JetAbsEta,std::abs(jet->eta()));

	  std::cout << "Is it OK? " << bTagPerf.isResultOk( measureMap[ bTagVal_[ ibTag] ], measurePoint)
		    << " result at "<< jet->pt() << " GeV, " << std::abs(jet->eta()) << " |eta| " << bTagPerf.getResult( measureMap[ bTagVal_[ ibTag] ], measurePoint)
		    << std::endl;

	  std::cout << "Error checking!" << std::endl;
	  measurePoint.reset();
	  measurePoint.insert(BinningVariables::JetEt,0);
	  measurePoint.insert(BinningVariables::JetAbsEta,10);

	  std::cout << "Is it OK? " << bTagPerf.isResultOk( measureMap[ bTagVal_[ ibTag] ], measurePoint)
		    << " result at 0 GeV, 10 |eta| " << bTagPerf.getResult( measureMap[ bTagVal_[ ibTag] ], measurePoint)
		    << std::endl;
	  std::cout << std::endl;
	}

      //std::cout << "Values: " << PerformanceResult::BTAGNBEFF << " " << PerformanceResult::MUERR << " " << std::endl;

      
      //////////
      */
    }
  }
  
  // reset variables of kinFit
  prob = -1.;
  chi2 = -1.;
  comboTypeValue = 0;
  for(short i = 0; i < 6; ++i){
    fitAssigns[i] = -1;
  }
  fitVecs->Delete();

  if( fullHadEvent_h.isValid() && fullHadEvent_h->isHypoValid("kKinFit") ){
    prob    = fullHadEvent_h->fitProb();
    chi2    = fullHadEvent_h->fitChi2();
    topMass = fullHadEvent_h->top("kKinFit")->mass();

    fitAssigns[TtFullHadEvtPartons::LightQ   ] = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightQ   ];
    fitAssigns[TtFullHadEvtPartons::LightQBar] = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightQBar];
    fitAssigns[TtFullHadEvtPartons::B        ] = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::B        ];
    fitAssigns[TtFullHadEvtPartons::LightP   ] = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightP   ];
    fitAssigns[TtFullHadEvtPartons::LightPBar] = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightPBar];
    fitAssigns[TtFullHadEvtPartons::BBar     ] = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::BBar     ];

    new((*fitVecs)[TtFullHadEvtPartons::LightQ   ]) TLorentzVector(fullHadEvent_h->lightQ   ("kKinFit")->px(),
								   fullHadEvent_h->lightQ   ("kKinFit")->py(),
								   fullHadEvent_h->lightQ   ("kKinFit")->pz(),
								   fullHadEvent_h->lightQ   ("kKinFit")->energy());
    new((*fitVecs)[TtFullHadEvtPartons::LightQBar]) TLorentzVector(fullHadEvent_h->lightQBar("kKinFit")->px(),
								   fullHadEvent_h->lightQBar("kKinFit")->py(),
								   fullHadEvent_h->lightQBar("kKinFit")->pz(),
								   fullHadEvent_h->lightQBar("kKinFit")->energy());
    new((*fitVecs)[TtFullHadEvtPartons::B        ]) TLorentzVector(fullHadEvent_h->b        ("kKinFit")->px(),
								   fullHadEvent_h->b        ("kKinFit")->py(),
								   fullHadEvent_h->b        ("kKinFit")->pz(),
								   fullHadEvent_h->b        ("kKinFit")->energy());
    new((*fitVecs)[TtFullHadEvtPartons::LightP   ]) TLorentzVector(fullHadEvent_h->lightP   ("kKinFit")->px(),
								   fullHadEvent_h->lightP   ("kKinFit")->py(),
								   fullHadEvent_h->lightP   ("kKinFit")->pz(),
								   fullHadEvent_h->lightP   ("kKinFit")->energy());
    new((*fitVecs)[TtFullHadEvtPartons::LightPBar]) TLorentzVector(fullHadEvent_h->lightPBar("kKinFit")->px(),
								   fullHadEvent_h->lightPBar("kKinFit")->py(),
								   fullHadEvent_h->lightPBar("kKinFit")->pz(),
								   fullHadEvent_h->lightPBar("kKinFit")->energy());
    new((*fitVecs)[TtFullHadEvtPartons::BBar     ]) TLorentzVector(fullHadEvent_h->bBar     ("kKinFit")->px(),
								   fullHadEvent_h->bBar     ("kKinFit")->py(),
								   fullHadEvent_h->bBar     ("kKinFit")->pz(),
								   fullHadEvent_h->bBar     ("kKinFit")->energy());
    if( fullHadEvent_h->isHypoValid("kGenMatch") )
      comboTypeValue = comboType(fullHadEvent_h);
    if( !fullHadEvent_h->isHypoValid("kGenMatch") )
      comboTypeValue = 5;

  }
  
  if(doPDFUncertainty && genEventInfo_h.isValid()){

    Q   = genEventInfo_h->pdf()->scalePDF;
    id1 = genEventInfo_h->pdf()->id.first;
    id2 = genEventInfo_h->pdf()->id.second;
    x1  = genEventInfo_h->pdf()->x.first;
    x2  = genEventInfo_h->pdf()->x.second;

  }

  tree->Fill();
}

/// function to find types of jet-combinations in KinFits (1 right, 2 branches right, but inner-branche particles mixup, 3 inter-branch mixup, 4 missing jet)
int
FullHadTreeWriter::comboType(edm::Handle<TtFullHadronicEvent> fullHadEvent_h)
{
  /// vector to store the jet indices
  std::vector<int> jetIndex(12);
  /// store position in jetIndex vector with corresponding particle name
  enum whichParticle{LQ, LQBar, B, BBar, LP, LPBar, LQ_Gen, LQBar_Gen, B_Gen, BBar_Gen, LP_Gen, LPBar_Gen};

  int lightQFit    = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightQ   ];
  int lightQBarFit = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightQBar];
  int bFit         = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::B        ];
  int bBarFit      = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::BBar     ];
  int lightPFit    = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightP   ];
  int lightPBarFit = fullHadEvent_h->jetLeptonCombination("kKinFit")[TtFullHadEvtPartons::LightPBar];

  int lightQGen    = fullHadEvent_h->jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::LightQ   ];
  int lightQBarGen = fullHadEvent_h->jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::LightQBar];
  int bGen         = fullHadEvent_h->jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::B        ];
  int bBarGen      = fullHadEvent_h->jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::BBar     ];
  int lightPGen    = fullHadEvent_h->jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::LightP   ];
  int lightPBarGen = fullHadEvent_h->jetLeptonCombination("kGenMatch")[TtFullHadEvtPartons::LightPBar];

  jetIndex[LQ   ] = lightQFit;
  jetIndex[LQBar] = lightQBarFit;
  jetIndex[B    ] = bFit;
  jetIndex[BBar ] = bBarFit;
  jetIndex[LP   ] = lightPFit;
  jetIndex[LPBar] = lightPBarFit;

  jetIndex[LQ_Gen   ] = lightQGen;
  jetIndex[LQBar_Gen] = lightQBarGen;
  jetIndex[B_Gen    ] = bGen;
  jetIndex[BBar_Gen ] = bBarGen;
  jetIndex[LP_Gen   ] = lightPGen;
  jetIndex[LPBar_Gen] = lightPBarGen;

  std::list<int> fit;
  std::list<int> fitBar;
  std::list<int> gen;
  std::list<int> genBar;

  fit.push_back(jetIndex[LQ]);
  fit.push_back(jetIndex[LQBar]);
  fit.push_back(jetIndex[B]);

  fitBar.push_back(jetIndex[LP]);
  fitBar.push_back(jetIndex[LPBar]);
  fitBar.push_back(jetIndex[BBar]);

  gen.push_back(jetIndex[LQ_Gen]);
  gen.push_back(jetIndex[LQBar_Gen]);
  gen.push_back(jetIndex[B_Gen]);

  genBar.push_back(jetIndex[LP_Gen]);
  genBar.push_back(jetIndex[LPBar_Gen]);
  genBar.push_back(jetIndex[BBar_Gen]);

  if( ( bFit == bGen && bBarFit == bBarGen ) || ( bFit == bBarGen && bBarFit == bGen ) ) {

    if( bFit == bGen &&
	( ( lightQFit == lightQGen    && lightQBarFit == lightQBarGen ) ||
	  ( lightQFit == lightQBarGen && lightQBarFit == lightQGen    ) ) &&
	( ( lightPFit == lightPGen    && lightPBarFit == lightPBarGen ) ||
	  ( lightPFit == lightPBarGen && lightPBarFit == lightPGen    ) ) )
      return 1;
    
    if( bBarFit == bGen &&
	( ( lightPFit == lightQGen    && lightPBarFit == lightQBarGen ) ||
	  ( lightPFit == lightQBarGen && lightPBarFit == lightQGen    ) ) &&
	( ( lightQFit == lightPGen    && lightQBarFit == lightPBarGen ) ||
	  ( lightQFit == lightPBarGen && lightQBarFit == lightPGen    ) ) )
      return 1;
  }

  fit.sort();
  fitBar.sort();
  gen.sort();
  genBar.sort();

  if( ( fit == gen && fitBar == genBar ) || ( fit == genBar && fitBar == gen ) ) return 2;

  fit.splice(fit.end(),fitBar);
  gen.splice(gen.end(),genBar);

  fit.sort();
  fitBar.sort();

  if( fit == gen ) return 3;

  return 4;
}

void
FullHadTreeWriter::endJob()
{
  delete[] bTag_TCHE;
  delete[] bTag_TCHP;
  delete[] bTag_SSVHE;
  delete[] bTag_SSVHP;
  delete[] bTag_CSV;
  delete[] bTag_CSVMVA;

  delete[] fitAssigns;
  delete[] pdgId;

  jets->Delete();
  fitVecs->Delete();
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( FullHadTreeWriter );
