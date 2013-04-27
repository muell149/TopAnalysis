#ifndef storeTemplate_h
#define storeTemplate_h

#include <iostream>
#include <cstdlib>

#include <TSelectorList.h>





namespace ttbar{
    
    /** Store a TObject in a given TSelectorList and return it
     * 
     * @param obj a pointer to a TObject (or any type inheriting from TObject)
     * @param selectorList a pointer to the TSelectorList where to store the TObject
     * @return returns the parameter (and the same type)
     * 
     * This function just adds a histogram or other object to the output list and returns 
     * it in a typesafe way.
     */
    template<class T> T* store(T* obj, TSelectorList* selectorList);
}





template<class T> T* ttbar::store(T* obj, TSelectorList* selectorList)
{
    if(!obj){
        std::cerr<<"ERROR in function store()!\n"
                 <<"Object to be stored in selector list does not exist"
                 <<"\n...break\n"<<std::endl;
        exit(72);
    }
    if(!selectorList){
        std::cerr<<"ERROR in function store()!\n"
                 <<"Selector list does not exist, so cannot store object with name: "<<obj->GetName()
                 <<"\n...break\n"<<std::endl;
        exit(73);
    }
    selectorList->Add(obj);
    return obj;
}





#endif







