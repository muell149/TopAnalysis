#ifndef JetBTag_h
#define JetBTag_h

using namespace std; 

class BJetTag{

 public:

  explicit BJetTag(const edm::ParameterSet&);
  ~BJetTag();

  void book(ofstream&, char*);
  void fill(const pat::Jet&, double);
  void evaluate();
  
 private:

  string algorithm_;
  double cut_;
  vector<double> etaBin_;
  vector<double> ptBin_;  
  
  TH1F *trkCountHighEffBJetTags_;
  TH1F *trkCountHighPurBJetTags_;  
  TH1F *jetProbBJetTags_;  
  TH1F *jetBProbBJetTags_;  
  TH1F *impactParMVABJetTags_; 
  TH1F *simpleSvBJetTags_;  
  TH1F *combSvBJetTags_;  
  TH1F *combSvMvaBJetTags_;  
  TH1F *softMuonBJetTags_;  
  TH1F *softMuonNoIPBJetTags_;  
  TH1F *softElecBJetTags_;
    
  vector<TH1F*> etaHist_;
  vector<TH1F*> ptHist_;
  
  TH1F *etaEff_;
  TH1F *ptEff_;
    
  double binomerror(double, double);  
};

#endif
