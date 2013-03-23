#include "src/JetCategories.h"

#include <iostream>

#include <TString.h>



void testJetCategories(){
    JetCategories jetCategories;
    
    
    
    jetCategories.addCategory(2,2);
    jetCategories.addCategory(3,2);
    jetCategories.addCategory(4,2);
    jetCategories.addCategory(2,0);
    jetCategories.addCategory(2,1);
    jetCategories.addCategory(3,0);
    jetCategories.addCategory(3,1);
    jetCategories.addCategory(3,3);
    jetCategories.addCategory(4,0);
    jetCategories.addCategory(4,1);
    jetCategories.addCategory(4,3);
    jetCategories.addCategory(4,4);
    jetCategories.addCategory(5,1,true);
    jetCategories.addCategory(5,4,true);
    jetCategories.addCategory(5,3,true);
    jetCategories.addCategory(5,2,true);
    jetCategories.addCategory(5,5,true,true);
    
    std::cout<<"\nNumber of categories: "<<jetCategories.numberOfCategories()<<"\n";
    
    std::vector<TString> v_binLabel(jetCategories.binLabels());
    std::cout<<"\nBinLabels\n";
    for(std::vector<TString>::const_iterator i_label = v_binLabel.begin(); i_label != v_binLabel.end(); ++i_label)
        std::cout<<*i_label<<"\n";
    
    std::cout<<"\nCheck categories:\n";
    std::cout<<"0,0: "<<jetCategories.categoryId(0,0)<<"\n";
    std::cout<<"2,1: "<<jetCategories.categoryId(2,1)<<"\n";
    std::cout<<"3,2: "<<jetCategories.categoryId(3,2)<<"\n";
    std::cout<<"5,4: "<<jetCategories.categoryId(5,4)<<"\n";
    std::cout<<"7,6: "<<jetCategories.categoryId(7,6)<<"\n";
    std::cout<<"8,9: "<<jetCategories.categoryId(8,9)<<"\n";
    std::cout<<"4,1: "<<jetCategories.categoryId(4,1)<<"\n";
    std::cout<<"4,2: "<<jetCategories.categoryId(4,2)<<"\n";
    std::cout<<"3,3: "<<jetCategories.categoryId(3,3)<<"\n";
    std::cout<<"11,111: "<<jetCategories.categoryId(11,111)<<"\n";
    std::cout<<"4,2: "<<jetCategories.categoryId(4,2)<<"\n";
}
