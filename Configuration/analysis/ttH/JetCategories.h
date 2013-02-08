#ifndef JetCategories_h
#define JetCategories_h

#include <vector>

#include "TString.h"

class JetCategories{

private:
    struct JetCategory{
        JetCategory();
	JetCategory(int numberOfJets, int numberOfBjets, bool greaterEqualJetNumber =false, bool greaterEqualBjetNumber =false);
	
	int numberOfJets_;
	int numberOfBjets_;
	bool greaterEqualJetNumber_;
	bool greaterEqualBjetNumber_;
    };

public:
    JetCategories();
    ~JetCategories();
    void addCategory(int numberOfJets, int numberOfBjets, bool greaterEqualJetNumber =false, bool greaterEqualBjetNumber =false);
    int numberOfCategories();
    int categoryId(int numberOfJets, int numberOfBjets);
    void clear();
    
    std::vector<TString> binLabels();
    
private:
    std::vector<JetCategory> v_jetCategory_;
};

#endif // JetCategories_h
