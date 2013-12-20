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
        TString binLabel(const bool rootLabel =true)const;
        
        /// number of jets
        int numberOfJets_;
        
        /// number of bjets
        int numberOfBjets_;
        
        /// require number of jets exactly(=) or at least(>=)
        bool greaterEqualJetNumber_;
        
        /// require number of bjets exactly(=) or at least(>=)
        bool greaterEqualBjetNumber_;
    };
    
    
    
public:
    
    /// Default constructor
    JetCategories();
    
    /// Constructor for categories based on minimum and maximum number of jets and bjets:
    /// Creates all categories starting from (min_jet, min_bjet),
    /// filling up all possible combinations reaching (max_jet, max_bjet)
    JetCategories(const int minNumberOfJets, const int maxNumberOfJets,
                  const int minNumberOfBjets, const int maxNumberOfBjets,
                  const bool greaterEqualJetNumber =false, const bool greaterEqualBjetNumber =false);
    
    /// Destructor
    ~JetCategories();
    
    /// Add a new category
    /// Gets sorted by increasing number of jets, subsorted by increasing number of bjets
    void addCategory(const int numberOfJets, const int numberOfBjets,
                     const bool greaterEqualJetNumber =false, const bool greaterEqualBjetNumber =false);
    
    /// Get number of defined categories
    int numberOfCategories()const;
    
    /// Get the category ID (position in vector) for a given number of jets and bjets
    int categoryId(const int numberOfJets, const int numberOfBjets)const;
    
    /// Clear categories
    void clear();
    
    /// Get the category labels to assign them to histogram bins
    std::vector<TString> binLabels(const bool rootLabel =true)const;
    
    
    
private:
    
    /// Check whether a category is illdefined in any way
    bool ambiguousCategory(const JetCategory& jetCategory)const;
    
    /// Check whether a category has overlap with an already existing one
    bool hasOverlap(const int numberOfJets1, const bool greaterEqualJetNumber1,
                    const int numberOfJets2, const bool greaterEqualJetNumber2)const;
    
    
    
    /// Vector holding the jet categories
    std::vector<JetCategory> v_jetCategory_;
};



#endif // JetCategories_h



