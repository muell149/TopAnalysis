#ifndef JetBTag_h
#define JetBTag_h

using namespace std; 

class BJetTag{

 public:

  explicit BJetTag(const edm::ParameterSet&);
  ~BJetTag();

  void book(ofstream&, char*);
  void fill(const pat::Jet&, size_t);
  void evaluate();
  
 private:

  double trkCountHighEffCut_;
  double trkCountHighPurCut_;
  double jetProbCut_;
  double jetBProbCut_;
  double impactParMvaCut_;
  double simpleSvCut_;
  double combSvCut_;
  double combSvMvaCut_;
  double softMuonCut_;
  double softMuonNoIPCut_;
  double softElecCut_;
  vector<double> etaBins_;
  vector<double> ptBins_;  
  
  size_t nBins;
  size_t nJetBins;
  
  TH1F *trkCountHighEffBJetTags_;
  TH1F *trkCountHighPurBJetTags_;  
  TH1F *jetProbBJetTags_;  
  TH1F *jetBProbBJetTags_;  
  TH1F *impactParMvaBJetTags_; 
  TH1F *simpleSvBJetTags_;  
  TH1F *combSvBJetTags_;  
  TH1F *combSvMvaBJetTags_;  
  TH1F *softMuonBJetTags_;  
  TH1F *softMuonNoIPBJetTags_;  
  TH1F *softElecBJetTags_;
    
  vector<TH1F*> etaDiscrTrkCountEff_;  
  vector<TH1F*> etaDiscrTrkCountPur_;     
  vector<TH1F*> etaDiscrJetProb_;    
  vector<TH1F*> etaDiscrJetBProb_;  
  vector<TH1F*> etaDiscrImpactParMva_;    
  vector<TH1F*> etaDiscrSimpleSv_;      
  vector<TH1F*> etaDiscrCombSv_;    
  vector<TH1F*> etaDiscrCombSvMva_;  
  vector<TH1F*> etaDiscrSoftMu_;     
  vector<TH1F*> etaDiscrSoftMuNoIP_;     
  vector<TH1F*> etaDiscrSoftElec_;
  
  vector<TH1F*> ptDiscrTrkCountEff_;        
  vector<TH1F*> ptDiscrTrkCountPur_;       
  vector<TH1F*> ptDiscrJetProb_;
  vector<TH1F*> ptDiscrJetBProb_;   
  vector<TH1F*> ptDiscrImpactParMva_;    
  vector<TH1F*> ptDiscrSimpleSv_;  
  vector<TH1F*> ptDiscrCombSv_;   
  vector<TH1F*> ptDiscrCombSvMva_;   
  vector<TH1F*> ptDiscrSoftMu_;
  vector<TH1F*> ptDiscrSoftMuNoIP_;  
  vector<TH1F*> ptDiscrSoftElec_;   

  vector<TH1F*> njDiscrTrkCountEff_;        
  vector<TH1F*> njDiscrTrkCountPur_;       
  vector<TH1F*> njDiscrJetProb_;
  vector<TH1F*> njDiscrJetBProb_;   
  vector<TH1F*> njDiscrImpactParMva_;    
  vector<TH1F*> njDiscrSimpleSv_;  
  vector<TH1F*> njDiscrCombSv_;   
  vector<TH1F*> njDiscrCombSvMva_;   
  vector<TH1F*> njDiscrSoftMu_;
  vector<TH1F*> njDiscrSoftMuNoIP_;  
  vector<TH1F*> njDiscrSoftElec_; 
        
  TH1F *etaEffTrkCountEff_;
  TH1F *etaEffTrkCountPur_;  
  TH1F *etaEffJetProb_;  
  TH1F *etaEffJetBProb_;  
  TH1F *etaEffImpactParMva_;  
  TH1F *etaEffSimpleSv_;  
  TH1F *etaEffCombSv_;  
  TH1F *etaEffCombSvMva_;  
  TH1F *etaEffSoftMu_;  
  TH1F *etaEffSoftMuNoIP_;  
  TH1F *etaEffSoftElec_;    
  
  TH1F *ptEffTrkCountEff_;
  TH1F *ptEffTrkCountPur_;  
  TH1F *ptEffJetProb_;  
  TH1F *ptEffJetBProb_;  
  TH1F *ptEffImpactParMva_;  
  TH1F *ptEffSimpleSv_;  
  TH1F *ptEffCombSv_;  
  TH1F *ptEffCombSvMva_;  
  TH1F *ptEffSoftMu_;  
  TH1F *ptEffSoftMuNoIP_;    
  TH1F *ptEffSoftElec_;
  
  TH1F *njEffTrkCountEff_;
  TH1F *njEffTrkCountPur_;  
  TH1F *njEffJetProb_;  
  TH1F *njEffJetBProb_;  
  TH1F *njEffImpactParMva_;  
  TH1F *njEffSimpleSv_;  
  TH1F *njEffCombSv_;  
  TH1F *njEffCombSvMva_;  
  TH1F *njEffSoftMu_;  
  TH1F *njEffSoftMuNoIP_;    
  TH1F *njEffSoftElec_;    
  
  TH2F *impParSimpleSvCorr_;
  TH2F *impParCombSvMvaCorr_;
       
  double binomError(double, double);  
  void   fillEfficencyHist(TH1F*, vector<TH1F*>, size_t, double);
};

#endif
