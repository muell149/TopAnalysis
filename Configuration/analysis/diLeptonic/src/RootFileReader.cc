#include <string>
#include <algorithm>

#include <TString.h>
#include <TFile.h>
#include <TList.h>
#include <TH1.h>

#include "RootFileReader.h"





RootFileReader::~RootFileReader()
{
//     std::cout << "Deleting RootFileReader\n";
//     for (const auto& i : fileMap) {
//         delete i.second;
//     }
//     for (const auto& i : accessed) {
//         std::cout << "accessed: " << i.first << " " << i.second << std::endl;
//     }
//     for (const auto& i : opened) {
//         std::cout << "opened: " << i.first << " " << i.second << std::endl;
//     }
//     
}



TObject *RootFileReader::GetObj(const char* filename, const char* histoname, const bool allowNonexisting)
{
    auto& file = fileMap_[filename];
    if (!file) {
        file = TFile::Open(filename);
        if (!file) {
            if (allowNonexisting) return nullptr;
            std::cerr << "\n\n******************* ERROR ******************* ERROR ******************* ERROR *******************\n\n"
                      << "The file " << filename << " does not exist, thus cannot get histogram " << histoname 
                      << "\n\n******************* ERROR ******************* ERROR ******************* ERROR *******************\n"
                      << std::endl;
            exit(1);
        }
        ++opened_[filename];
    } else {
        fileOrder_.erase(std::remove_if(begin(fileOrder_), end(fileOrder_), 
                         [=](const TString &str){ return str == filename;}),
                         end(fileOrder_));
    }
    
    fileOrder_.push_back(filename);
    ++accessed_[filename];
    //at max, keep 20 files open
    if (fileMap_.size() > 20) {
        //delete 0th element
        delete fileMap_[fileOrder_[0]];
        fileMap_.erase(fileOrder_[0]);
        fileOrder_.erase(fileOrder_.begin());
    }
    TObject* result = file->Get(histoname);
    TH1* as_histo = dynamic_cast<TH1*>(result);
    if (as_histo) as_histo->SetDirectory(file);
    return result;
}



std::vector<TString> RootFileReader::findHistos(const char* filename, const char* histonameFragment, const bool fragmentAtBegin)
{
    
    TFile* file = TFile::Open(filename);
    if (!file) {
        const std::string helpText(fragmentAtBegin ? "beginning with: " : "containing: ");
        std::cerr << "\n\n******************* ERROR ******************* ERROR ******************* ERROR *******************\n\n"
                  << "The file "<<filename<<" does not exist, thus cannot search for histogram "<<helpText<<histonameFragment
                  << "\n\n******************* ERROR ******************* ERROR ******************* ERROR *******************\n"
                  << std::endl;
        exit(1);
    }
    std::vector<TString> result;
    TList* histoList = file->GetListOfKeys();
    for(int i=0; i<histoList->GetSize(); ++i){
        TObject* i_histoList = histoList->At(i);
        TString* histoName(0);
        histoName = new TString(i_histoList->GetName());
        //std::cout<<"\n\tName of object: "<<*histoName<<"\n\n";
        if(fragmentAtBegin){
            if(histoName->BeginsWith(histonameFragment)) result.push_back(*histoName);
        }
        else{
            if(histoName->Contains(histonameFragment)) result.push_back(*histoName);
        }
    }
    return result;
}



RootFileReader* RootFileReader::getInstance()
{
    static RootFileReader instance;
    return &instance;
}






