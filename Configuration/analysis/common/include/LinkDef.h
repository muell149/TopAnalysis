#ifndef ROOT_TREE_VECTOR_LINKDEF_H 
#define ROOT_TREE_VECTOR_LINKDEF_H 1

#ifdef __CINT__

#pragma link off all classes;

#pragma link C++ class std::vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > >+;
#pragma link C++ class std::map<std::string, std::vector<TH1*> >+;
#pragma link C++ class std::map<std::string, std::pair<TH1*, std::vector<std::map<std::string, TH1*> > > >+;
#pragma link C++ class AnalysisBase+;
#pragma link C++ class std::vector<std::vector<int> >+;
#pragma link C++ class PUReweighter+;

#endif

#endif // ROOT_TREE_VECTOR_LINKDEF_H

