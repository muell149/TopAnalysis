#define BTagEff_cxx

#include "BTagEff.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include "TLorentzVector.h"
#include <fstream>
#include <iostream>
#include <TMath.h>
#include <TSystem.h>
#include <set>
#include <stdio.h>


void BTagEff::Begin(TTree * /*tree*/)
{

  TString option = GetOption();
  //  totalEventCount=0;

  EventCounter=0;

//   ifstream insample("syst.txt",std::ios::in);
//   insample>>systematic;
// 
  ifstream inviatau("viaTau.txt",std::ios::in);
  inviatau>>viaTau;
  viaTau = "Nominal";

  // bTag Working point!!!
  //CSV Loose working point
  BtagWP = 0.244;
  
  gStyle->SetOptStat(0);
  
  //Double_t ptbins[] = {0.,30.,40.,50.,60.,70.,80.,100.,120.,160.,210.,260.,320.,400.,500.,670.};
  Double_t ptbins[] = {0.,30.,40.,50.,60.,70.,80.,100.,120.,160.,210.,260.,320.,400.,500.,670.,1000.,2000.};
  //Double_t etabins[] = {0.0,0.5,1.0,1.5,2.4};
  Double_t etabins[] = {0.0,0.5,1.0,1.5,2.0,2.4,3.0};
  
  h_bjets = new TH2D("bjets2D", "unTagged Bjets", 17, ptbins, 6, etabins);              h_bjets->Sumw2();
  h_btaggedjets = new TH2D("bjetsTagged2D", "Tagged Bjets", 17, ptbins, 6, etabins);    h_btaggedjets->Sumw2();
  h_cjets = new TH2D("cjets2D", "unTagged Cjets", 17, ptbins, 6, etabins);              h_cjets->Sumw2();
  h_ctaggedjets = new TH2D("cjetsTagged2D", "Tagged Cjets", 17, ptbins, 6, etabins);    h_ctaggedjets->Sumw2();
  h_ljets = new TH2D("ljets2D", "unTagged Ljets", 17, ptbins, 6, etabins);              h_ljets->Sumw2();
  h_ltaggedjets = new TH2D("ljetsTagged2D", "Tagged Ljets", 17, ptbins, 6, etabins);    h_ltaggedjets->Sumw2();
  
  gStyle->SetOptStat(0);

}

void BTagEff::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

}


Bool_t BTagEff::Process(Long64_t entry){
    
    if(EventCounter%100000 ==0){cout<<"EventCounter = "<<EventCounter<<endl;}
    EventCounter++;
    
    //Load standard & Signal branches from the Ntuple
    BTagEff::GetAllBranches(entry);
   
    if(viaTau=="viaTau"){
        if((MCSample->find("ttbarsignal")!=string::npos) && (decayMode>40 || (decayMode%10 > 4))){
            MCSample->clear();
            MCSample->append("ttbarbgviatau");
        }
        else{return kTRUE;}
    }
    else if(viaTau == "Nominal"){
        if((MCSample->find("ttbarsignal")!=string::npos) &&(decayMode>40 || (decayMode%10 > 4))){return kTRUE;}
    }
    else{cout<<"Something went wrong"<<endl;}

    std::vector<float> VLepton;
    std::vector<TLorentzVector> LVlepton;
    std::vector<TLorentzVector> LVjet;
    
    //Create & Fill Hypothesis TLorentzVector vectors
    std::vector<TLorentzVector> LVHypTop;
    std::vector<TLorentzVector> LVHypAntiTop;
    std::vector<TLorentzVector> LVHypBJet;
    std::vector<TLorentzVector> LVHypAntiBJet;
    std::vector<TLorentzVector> LVHypLepton;
    std::vector<TLorentzVector> LVHypAntiLepton;

    for(int i=0; i<jet_; i++){
        TLorentzVector jettemp(jetpX[i],jetpY[i],jetpZ[i],jetE[i]);
        LVjet.push_back(jettemp);
    }
    for(int i=0; i<HypTop_;i++){ 
        TLorentzVector antitoptemp(HypAntiToppX[i], HypAntiToppY[i], HypAntiToppZ[i], HypAntiTopE[i]);
        TLorentzVector toptemp(HypToppX[i], HypToppY[i], HypToppZ[i], HypTopE[i]);
        TLorentzVector antibtemp(HypAntiBpX[i], HypAntiBpY[i], HypAntiBpZ[i], HypAntiBE[i]);
        TLorentzVector btemp(HypBpX[i], HypBpY[i], HypBpZ[i], HypBE[i]);
        TLorentzVector antileptontemp(HypAntiLeptonpX[i], HypAntiLeptonpY[i], HypAntiLeptonpZ[i], HypAntiLeptonE[i]);
        TLorentzVector leptontemp(HypLeptonpX[i], HypLeptonpY[i], HypLeptonpZ[i], HypLeptonE[i]);
        
        LVHypAntiTop.push_back(antitoptemp);        LVHypTop.push_back(toptemp);
        LVHypAntiBJet.push_back(antibtemp);         LVHypBJet.push_back(btemp);
        LVHypAntiLepton.push_back(antileptontemp);  LVHypLepton.push_back(leptontemp);
    }

    for(int i=0; i<lepton_;i++){
        TLorentzVector leptemp(leptonpX[i], leptonpY[i], leptonpZ[i], leptonE[i]);
        LVlepton.push_back(leptemp);
    }
    
    //Check the jet index for b-tagged jets
    vector<int> BJetIndex;
    for(vector<double>::iterator it = jetBTagCSV->begin(); it<jetBTagCSV->end(); it++){
        if(*it > BtagWP){BJetIndex.push_back(*it);}
    }
    
    //Should we just look for two Bjets above 0.244 or the two highest bjets?:: Make this a function
    int solutionIndex = 0;
    bool oneTag = false;
    bool twoTag = false;
    for(int i =0; i<HypTop_; i++){
        if((*jetBTagCSV)[(*HypJet0index)[i]] > BtagWP && (*jetBTagCSV)[(*HypJet1index)[i]]>BtagWP){
            solutionIndex = i; 
            twoTag = true;
            break;
        }
        if(oneTag == false && ((*jetBTagCSV)[(*HypJet0index)[i]] > BtagWP || (*jetBTagCSV)[(*HypJet1index)[i]]>BtagWP)){
            solutionIndex = i; 
            oneTag=true;
        }
    }  

    //check triggers for ttbarsignal
    if(MCSample->find("ttbarsignal")!=string::npos){  
        if(channel->find("emu")!=string::npos && ((triggerBits & 0x1000) || (triggerBits & 0x100) || (triggerBits & 0x200))){int emutrig;}
        else if(channel->find("ee")!=string::npos && ((triggerBits & 0x40000)))                                             {int eetrig;}
        else if(channel->find("mumu")!=string::npos && ((triggerBits & 2)))                                                 {int eetrig;}
        else{return kTRUE;}
    }
    
    double dimass = 0.0;
    int LeadLeptonNumber = 0;
    int NLeadLeptonNumber = 0;
    if(lepton_>1){
        if(channel->find("emu")!=string::npos){//quick and DIRTY!
            for(int i = 1; i<lepton_; i++){
                if(((*lepQ)[0]!=(*lepQ)[i]) && ((*lepType)[0]!=(*lepType)[i])){
                    LeadLeptonNumber = 0;
                    NLeadLeptonNumber = i;
                    break;
                }
            }//set dimass to first two highest pT oppositely charged leptons
        }
        if(channel->find("ee")!=string::npos){//quick and DIRTY!
            for(int i = 0; i<lepton_; i++){
                if((*lepType)[i]<0){
                    LeadLeptonNumber=i;
                    break;
                }
            }
            for(int i = LeadLeptonNumber+1; i<lepton_; i++){
                if(((*lepQ)[LeadLeptonNumber]!=(*lepQ)[i]) && (*lepType)[i]<0){
                    NLeadLeptonNumber = i;
                    break;
                }
            }//set dimass to first two highest pT oppositely charged leptons
        }
        if(channel->find("mumu")!=string::npos){//quick and DIRTY!
            for(int i = 0; i<lepton_; i++){
                if((*lepType)[i]>0){
                    LeadLeptonNumber=i;
                    break;
                }
            }
            for(int i = LeadLeptonNumber+1; i<lepton_; i++){
                if(((*lepQ)[LeadLeptonNumber]!=(*lepQ)[i]) && (*lepType)[i]>0){
                    NLeadLeptonNumber = i;
                    break;
                }
            }//set dimass to first two highest pT oppositely charged leptons
        }
        dimass = (LVlepton[LeadLeptonNumber]+LVlepton[NLeadLeptonNumber]).M();
    }
    
    if(lepton_>1 && dimass>12.0 && NLeadLeptonNumber!=0 && jet_>1 && BJetIndex.size()>0 && HypTop_){  //two isolated leptons create dimass out of highest pt pair
        
        if ((int) LVjet.size()!=(int) jet_ || (int) LVjet.size()!=(int) (*jetBTagCSV).size() || (int) jet_!=(int) (*jetBTagCSV).size()){
            cout<<"WARNING!!!!!"<<endl;
            cout<<"LVjet.size() != jet_     OR     LVjet.size() != jetBTagCSV.size()    OR    jet_!= jetBTagCSV.size()"<<endl;
            return kTRUE;
        }
        //emu channel
        if (channel->find("emu")!=string::npos){
            int bjets=0, btagjets=0;
            int cjets=0, ctagjets=0;
            int ljets=0, ltagjets=0;
            for (int i=0; i< (int) jet_; ++i){
                if (LVjet[i].Pt()>30 && TMath::Abs(LVjet[i].Eta())<2.4){
                    if((*jetType)[i] == 2){//b-quark
                        h_bjets->Fill(LVjet[i].Pt(), TMath::Abs(LVjet[i].Eta()));
                        bjets++;
                        if((*jetBTagCSV)[i]>BtagWP){
                            h_btaggedjets->Fill(LVjet[i].Pt(), TMath::Abs(LVjet[i].Eta()));
                            btagjets++;
                        }
                    }
                    else if((*jetType)[i] == 1){//c-quark
                        h_cjets->Fill(LVjet[i].Pt(), TMath::Abs(LVjet[i].Eta()));
                        cjets++;
                        if((*jetBTagCSV)[i]>BtagWP){
                            h_ctaggedjets->Fill(LVjet[i].Pt(), TMath::Abs(LVjet[i].Eta()));
                            ctagjets++;
                        }
                    }
                    else if((*jetType)[i] == 0){//l-quark
                        h_ljets->Fill(LVjet[i].Pt(), TMath::Abs(LVjet[i].Eta()));
                        ljets++;
                        if((*jetBTagCSV)[i]>BtagWP){
                            h_ltaggedjets->Fill(LVjet[i].Pt(), TMath::Abs(LVjet[i].Eta()));
                            ltagjets++;
                        }
                    }
                    else {cout<<"I found a jet in event "<<eventNumber<<" which is not b, c nor ligth"<<endl; return kFALSE;}
                }
            };
        }
        else if ((dimass<76.0 || dimass > 106.0) && *(metEt->begin()) > 30 ){//ee && mumu channels
            int bjets=0, btagjets=0;
            int cjets=0, ctagjets=0;
            int ljets=0, ltagjets=0;
            for (int i=0; i< (int) jet_; ++i){
                if (LVjet[i].Pt()>30 && TMath::Abs(LVjet[i].Eta())<2.4){
                    if((*jetType)[i] == 2){//b-quark
                        h_bjets->Fill(LVjet[i].Pt(), TMath::Abs(LVjet[i].Eta()));
                        bjets++;
                        if((*jetBTagCSV)[i]>BtagWP){
                            h_btaggedjets->Fill(LVjet[i].Pt(), TMath::Abs(LVjet[i].Eta()));
                            btagjets++;
                        }
                    }
                    else if((*jetType)[i] == 1){//c-quark
                        h_cjets->Fill(LVjet[i].Pt(), TMath::Abs(LVjet[i].Eta()));
                        cjets++;
                        if((*jetBTagCSV)[i]>BtagWP){
                            h_ctaggedjets->Fill(LVjet[i].Pt(), TMath::Abs(LVjet[i].Eta()));
                            ctagjets++;
                        }
                    }
                    else if((*jetType)[i] == 0){//l-quark
                        h_ljets->Fill(LVjet[i].Pt(), TMath::Abs(LVjet[i].Eta()));
                        ljets++;
                        if((*jetBTagCSV)[i]>BtagWP){
                            h_ltaggedjets->Fill(LVjet[i].Pt(), TMath::Abs(LVjet[i].Eta()));
                            ltagjets++;
                        }
                    }
                    else {cout<<"I found a jet in event "<<eventNumber<<" which is not b, c nor ligth"<<endl; return kFALSE;}
                }
            };
        }
    }

    
    return kTRUE;
}




void BTagEff::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.

}

void BTagEff::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

//   if(viaTau=="viaTau"){
//     MCSample->clear();
//     MCSample->append("ttbarbgviatau");
//   }

//   string f_savename = "selectionRoot";
//   gSystem->MakeDirectory(f_savename.c_str());
//   f_savename.append("/BTagEff");
//   gSystem->MakeDirectory(f_savename.c_str());
  string f_savename = "BTagEff";
  gSystem->MakeDirectory(f_savename.c_str());
  f_savename.append("/");
  f_savename.append(systematic); 
  gSystem->MakeDirectory(f_savename.c_str());
  f_savename.append("/");
  f_savename.append(*channel); 
  gSystem->MakeDirectory(f_savename.c_str());
  f_savename.append("/");
  f_savename.append(*MCSample);
  f_savename.append(".root");
  

  std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!Finishing: "<<*MCSample<<"!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;

  TFile *f = new TFile(f_savename.c_str(),"RECREATE");

  h_bjets->Write();
  h_btaggedjets->Write();
  h_cjets->Write();
  h_ctaggedjets->Write();
  h_ljets->Write();
  h_ltaggedjets->Write();
  
  
  TH1D *btaggedPt = (TH1D*)h_btaggedjets->ProjectionX(); TH1D *btaggedEta = (TH1D*)h_btaggedjets->ProjectionY();
  TH1D *ctaggedPt = (TH1D*)h_ctaggedjets->ProjectionX(); TH1D *ctaggedEta = (TH1D*)h_ctaggedjets->ProjectionY();
  TH1D *ltaggedPt = (TH1D*)h_ltaggedjets->ProjectionX(); TH1D *ltaggedEta = (TH1D*)h_ltaggedjets->ProjectionY();
  
  TH1D *bUntaggedPt = (TH1D*)h_bjets->ProjectionX(); TH1D *bEta = (TH1D*)h_bjets->ProjectionY();
  TH1D *cUntaggedPt = (TH1D*)h_cjets->ProjectionX(); TH1D *cEta = (TH1D*)h_cjets->ProjectionY();
  TH1D *lUntaggedPt = (TH1D*)h_ljets->ProjectionX(); TH1D *lEta = (TH1D*)h_ljets->ProjectionY();
  
  //Calculate the medians and save them in a txt file
  FILE * pFile;
  pFile = fopen ("BJetMedians.txt","a");
  double PtMedian= Median(btaggedPt);
  double EtaMedian= Median(btaggedEta);
  fprintf(pFile, "-------------------------------\n");
  fprintf(pFile, "Pt  median = %.3f (%s channel)\n", PtMedian, channel->c_str());
  fprintf(pFile, "Eta median = %.3f (%s channel)\n", EtaMedian, channel->c_str());
  fclose(pFile);
  //end median calculations
  
  TH1D *beffPt =(TH1D*) btaggedPt->Clone("beffPt");
  TH1D *ceffPt =(TH1D*) ctaggedPt->Clone("ceffPt");
  TH1D *leffPt =(TH1D*) ltaggedPt->Clone("leffPt");
  
  TH1D *beffEta =(TH1D*) btaggedEta->Clone("beffEta");  
  TH1D *ceffEta =(TH1D*) ctaggedEta->Clone("ceffEta");  
  TH1D *leffEta =(TH1D*) ltaggedEta->Clone("leffEta");  

  
  //Calculate Efficiency: N_tageed/N_all
  beffPt->Divide(btaggedPt, bUntaggedPt, 1, 1, "B"); 
  ceffPt->Divide(ctaggedPt, cUntaggedPt, 1, 1, "B"); 
  leffPt->Divide(ltaggedPt, lUntaggedPt, 1, 1, "B");
  beffEta->Divide(btaggedEta, bEta, 1, 1, "B"); 
  ceffEta->Divide(ctaggedEta, cEta, 1, 1, "B"); 
  leffEta->Divide(ltaggedEta, lEta, 1, 1, "B"); 
  h_btaggedjets->Divide(h_btaggedjets, h_bjets, 1, 1, "B"); 
  h_ctaggedjets->Divide(h_ctaggedjets, h_cjets, 1, 1, "B"); 
  h_ltaggedjets->Divide(h_ltaggedjets, h_ljets, 1, 1, "B"); 

  //Calculate 1D distributions' error
  //start with pT efficiencies
  for (int i=1; i<=(int) beffPt->GetNbinsX(); ++i){
      if(beffPt->GetNbinsX() != ceffPt->GetNbinsX() || beffPt->GetNbinsX() != leffPt->GetNbinsX() || beffPt->GetNbinsX() != bUntaggedPt->GetNbinsX()){
          cout<<"WARNING!!! b-, c- & l-pT efficiency histograms have different axis range"<<endl;
          return;
      }
      beffPt->SetBinError(i, 0);
      ceffPt->SetBinError(i, 0);
      leffPt->SetBinError(i, 0);

      //if eff=a/b  ==>  eff_error=sqrt(eff*(1-eff)/b)
      if(bUntaggedPt->GetBinContent(i)<1.e-6){beffPt->SetBinError(i,0);}
      else{beffPt->SetBinError(i, TMath::Sqrt(beffPt->GetBinContent(i)*(1-beffPt->GetBinContent(i))/bUntaggedPt->GetBinContent(i)));}
      if(cUntaggedPt->GetBinContent(i)<1.e-6){ceffPt->SetBinError(i,0);}
      else{ceffPt->SetBinError(i, TMath::Sqrt(ceffPt->GetBinContent(i)*(1-ceffPt->GetBinContent(i))/cUntaggedPt->GetBinContent(i)));}
      if(lUntaggedPt->GetBinContent(i)<1.e-6){leffPt->SetBinError(i,0);}
      else{leffPt->SetBinError(i, TMath::Sqrt(leffPt->GetBinContent(i)*(1-leffPt->GetBinContent(i))/lUntaggedPt->GetBinContent(i)));}
  }
  
  //start with Eta efficiencies
  for (int i=1; i<=(int) beffEta->GetNbinsX(); ++i){
      if(beffEta->GetNbinsX() != ceffEta->GetNbinsX() || beffEta->GetNbinsX() != leffEta->GetNbinsX() || beffEta->GetNbinsX() != bEta->GetNbinsX()){
          cout<<"WARNING!!! b-, c- & l-pT efficiency histograms have different axis range"<<endl;
          return;
      }
      beffEta->SetBinError(i, 0);
      ceffEta->SetBinError(i, 0);
      leffEta->SetBinError(i, 0);
      
      //if eff=a/b  ==>  eff_error=sqrt(eff*(1-eff)/b)
      if(bEta->GetBinContent(i)<1.e-6){beffEta->SetBinError(i,0);}
      else{beffEta->SetBinError(i, TMath::Sqrt(beffEta->GetBinContent(i)*(1-beffEta->GetBinContent(i))/bEta->GetBinContent(i)));}
      if(cEta->GetBinContent(i)<1.e-6){ceffEta->SetBinError(i,0);}
      else{ceffEta->SetBinError(i, TMath::Sqrt(ceffEta->GetBinContent(i)*(1-ceffEta->GetBinContent(i))/cEta->GetBinContent(i)));}
      if(lEta->GetBinContent(i)<1.e-6){leffEta->SetBinError(i,0);}
      else{leffEta->SetBinError(i, TMath::Sqrt(leffEta->GetBinContent(i)*(1-leffEta->GetBinContent(i))/lEta->GetBinContent(i)));}
  }
  
  
  //Save histograms in ROOT file
  beffPt->Write("BEffPt"); 
  ceffPt->Write("CEffPt"); 
  leffPt->Write("LEffPt"); 
  beffEta->Write("BEffEta"); 
  ceffEta->Write("CEffEta"); 
  leffEta->Write("LEffEta"); 
  h_btaggedjets->Write("BEffPerJet");
  h_ctaggedjets->Write("CEffPerJet");
  h_ltaggedjets->Write("LEffPerJet");
  
  f->Close();
  
  fstream text;
  text.open("BTagJetEff.txt", fstream::out | fstream::app);
  text<<f_savename<<endl;
  text.close();
  
  
  cout<<"Created: "<<f_savename<<endl;
}
