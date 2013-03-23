#ifndef JetCategories_h
#define JetCategories_h

#include <vector>

class TString;


/// Class for administration of jet categories, i.e. separation via number of jets and b-jets
class JetCategories{

private:
    
    /// Struct holding definition of jet category in (number of jets, number of b-jets)
    struct JetCategory{
        /// Empty constructor
        JetCategory();
        
        /// Setting up jet category
        JetCategory(const int numberOfJets, const int numberOfBjets,
                    const bool greaterEqualJetNumber =false, const bool greaterEqualBjetNumber =false);
        
        /// Get label in format [>=]numberOfJets, [>=]numberOfBjets
        TString binLabel(const bool rootLabel=true)const;
        
        /// number of jets
        int numberOfJets_;
        
        /// number of b-jets
        int numberOfBjets_;
        
        /// require number of jets exactly(=) or at least(>=)
        bool greaterEqualJetNumber_;
        
        /// require number of b-jets exactly(=) or at least(>=)
        bool greaterEqualBjetNumber_;
    };
    
    
    
public:
    
    /// Default constructor
    JetCategories();
    
    /// Destructor
    ~JetCategories();
    
    /// Add a new category
    /// Gets sorted by increasing number of jets, subsorted by increasing number of b-jets
    void addCategory(const int numberOfJets, const int numberOfBjets,
                     const bool greaterEqualJetNumber =false, const bool greaterEqualBjetNumber =false);
    
    /// Get number of defined categories
    int numberOfCategories();
    
    /// Get the category ID (position in vector) for a given number of jets and b-jets
    int categoryId(const int numberOfJets, const int numberOfBjets);
    
    /// Clear categories
    void clear();
    
    /// Get the category labels to assign them to histogram bins
    std::vector<TString> binLabels();
    
    
    
private:
    
    /// Check whether a category is illdefined in any way
    bool ambiguousCategory(const JetCategory& jetCategory);
    
    /// Check whether a category has overlap with an already existing one
    bool hasOverlap(const int numberOfJets1, const bool greaterEqualJetNumber1,
                    const int numberOfJets2, const bool greaterEqualJetNumber2);
    
    
    
    /// Vector holding the jet categories
    std::vector<JetCategory> v_jetCategory_;
};



#endif // JetCategories_h



