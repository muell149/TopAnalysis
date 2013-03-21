#define JetCategogies_cxx

#include "JetCategories.h"

#include <sstream>


// only for development:
# include <iostream>


JetCategories::JetCategories(){}


JetCategories::~JetCategories(){}


JetCategories::JetCategory::JetCategory(){}


JetCategories::JetCategory::JetCategory(int numberOfJets, int numberOfBjets, bool greaterEqualJetNumber, bool greaterEqualBjetNumber):
numberOfJets_(numberOfJets), numberOfBjets_(numberOfBjets), greaterEqualJetNumber_(greaterEqualJetNumber), greaterEqualBjetNumber_(greaterEqualBjetNumber)
{}


void
JetCategories::addCategory(int numberOfJets, int numberOfBjets, bool greaterEqualJetNumber, bool greaterEqualBjetNumber){
    JetCategory jetCategory(numberOfJets, numberOfBjets, greaterEqualJetNumber, greaterEqualBjetNumber);
    for(std::vector<JetCategory>::iterator i_jetCategory = v_jetCategory_.begin(); i_jetCategory != v_jetCategory_.end(); ++i_jetCategory){
	if(numberOfJets<i_jetCategory->numberOfJets_){v_jetCategory_.insert(i_jetCategory, jetCategory);return;}
	else if(numberOfJets==i_jetCategory->numberOfJets_ && numberOfBjets<i_jetCategory->numberOfBjets_){v_jetCategory_.insert(i_jetCategory, jetCategory);return;}
    }
    v_jetCategory_.push_back(jetCategory);
}


void
JetCategories::clear(){
    v_jetCategory_.clear();
}



int
JetCategories::numberOfCategories(){return v_jetCategory_.size();}



int
JetCategories::categoryId(int numberOfJets, int numberOfBjets){
    // Events belonging to specific category should get value >=0
    // If the category definition is bad, it should end up in the underflow (return value <0, depending on error)
    // If the category definition is fine, but the event does not belong to any category, it should end up in the overflow (return value +999)
    
    if(v_jetCategory_.size()==0)return -1;
    bool alreadyInCategory(false);
    int position(-99);
    std::vector<JetCategory>::iterator i_jetCategory;
    for(i_jetCategory = v_jetCategory_.begin(); i_jetCategory != v_jetCategory_.end(); ++i_jetCategory){
	if(numberOfJets<i_jetCategory->numberOfJets_)continue;
	if(!i_jetCategory->greaterEqualJetNumber_ && numberOfJets>i_jetCategory->numberOfJets_)continue;
	if(numberOfBjets<i_jetCategory->numberOfBjets_)continue;
	if(!i_jetCategory->greaterEqualBjetNumber_ && numberOfBjets>i_jetCategory->numberOfBjets_)continue;
	if(alreadyInCategory){
	    std::cout<<"Bad jet category definition, event with (# jets = "<<numberOfJets<<", # bjets = "<<numberOfBjets<<") fits in more than one category!!!\n";
	    return -2;
	}
	position = std::distance(v_jetCategory_.begin(), i_jetCategory);
	//std::cout<<"Position in vector: "<<position<<"\n";
	alreadyInCategory = true;
    }
    // is event contained in any category?
    if(!alreadyInCategory)return +999;
    return position;
}


std::vector<TString>
JetCategories::binLabels(){
    std::vector<TString> v_label;
    for(std::vector<JetCategory>::const_iterator i_jetCategory = v_jetCategory_.begin(); i_jetCategory != v_jetCategory_.end(); ++i_jetCategory){
        std::stringstream ss_label;
	if(i_jetCategory->greaterEqualJetNumber_)ss_label<<"#geq"; //char(242);
	ss_label<<i_jetCategory->numberOfJets_<<",";
	if(i_jetCategory->greaterEqualBjetNumber_)ss_label<<"#geq";
	ss_label<<i_jetCategory->numberOfBjets_;
	
	v_label.push_back(ss_label.str().c_str());
    }
    return v_label;
}





// TString
// JetCategories::binLabels(){
//     std::stringstream ss_label;
//     for(std::vector<JetCategory>::const_iterator i_jetCategory = v_jetCategory_.begin(); i_jetCategory != v_jetCategory_.end(); ++i_jetCategory){
//         //std::stringstream ss_label;
// 	if(i_jetCategory->greaterEqualJetNumber_)ss_label<<"#geq"; //char(242);
// 	ss_label<<i_jetCategory->numberOfJets_<<",";
// 	if(i_jetCategory->greaterEqualBjetNumber_)ss_label<<"#geq";
// 	ss_label<<i_jetCategory->numberOfBjets_<<"\n";
//     }
//     return ss_label.str().c_str();
// }









