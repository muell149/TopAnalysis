#include "KinematicReconstruction_LSroutines.h"
#include <TAttLine.h>
#define printout 0

using namespace std;

KinematicReconstruction_LSroutines::KinematicReconstruction_LSroutines()
{
    mt    = 172.5;
    mtbar = 172.5;
    mb    = 4.8;
    mbbar = 4.8;
    mw    = 80.4;
    mwbar = 80.4; 
    ml    = 0.000511;
    mal    = 0.000511; 
    mv=0;
    mav=0;
    weight_option=0;
    
}

KinematicReconstruction_LSroutines::KinematicReconstruction_LSroutines(double mass_l, double mass_al)
{
    mt    = 172.5;
    mtbar = 172.5;
    mb    = 4.8;
    mbbar = 4.8;
    mw    = 80.4;//mw    = 76.671425; for event  799
    mwbar = 80.4; //mwbar = 80.177391; for event  799 
    ml    = mass_l;
    mal    = mass_al;
    mv=0;
    mav=0;
    weight_option=0;

}

KinematicReconstruction_LSroutines::KinematicReconstruction_LSroutines(double mass_l, double mass_al,double mass_Wp, double mass_Wm)
{
    mt    = 172.5;
    mtbar = 172.5;
    mb    = 4.8;
    mbbar = 4.8;
    mw    = mass_Wp;
    mwbar = mass_Wm; 
    ml    = mass_l;
    mal    = mass_al;
    mv=0;
    mav=0;
   // NeutrinoEventShape = new TF2("landau2D","[0]*TMath::Landau(x,[1],[2],0)*TMath::Landau(y,[3],[4],0)",0,500,0,500);
   // NeutrinoEventShape->SetParameters(30.641,57.941,22.344,57.533,22.232);
   weight_option=0;

}

KinematicReconstruction_LSroutines::KinematicReconstruction_LSroutines(double mass_l, double mass_al,double mass_Wp, double mass_Wm, TH1F* hvE[])
{
    mt    = 172.5;
    mtbar = 172.5;
    mb    = 4.8;
    mbbar = 4.8;
    mw    = mass_Wp;
    mwbar = mass_Wm; 
    ml    = mass_l;
    mal    = mass_al;
    mv=0;
    mav=0;

        for(int i=0;i<6;i++)hneutrino_E[i]= hvE[i];

    //pol4_neutrinoPx = new TF1("pol4_neutrinoPx","pol4",-100,100);
    //((TAttLine*)pol4_neutrinoPx->GetParent())->SetLineWidth(1);
    weight_option=0;
}

KinematicReconstruction_LSroutines::KinematicReconstruction_LSroutines(double mass_l, double mass_al,double mass_Wp, double mass_Wm, TH1F hneutrino)
{
    mt    = 172.5;
    mtbar = 172.5;
    mb    = 4.8;
    mbbar = 4.8;
    mw    = mass_Wp;
    mwbar = mass_Wm; 
    ml    = mass_l;
    mal    = mass_al;
    mv=0;
    mav=0;
    
    hnw_cuts= hneutrino;
    
    //pol4_neutrinoPx = new TF1("pol4_neutrinoPx","pol4",-100,100);
    //((TAttLine*)pol4_neutrinoPx->GetParent())->SetLineWidth(1);
    weight_option=0;
}

KinematicReconstruction_LSroutines::KinematicReconstruction_LSroutines(double mass_top, double mass_b, double mass_w, double mass_l, double mass_al)
{
    mt    = mass_top;
    mtbar = mass_top;
    mb    = mass_b;
    mbbar = mass_b;
    mw    = mass_w;
    mwbar = mass_w;
    ml=mass_l;
    mal=mass_al;
    mv=0;
    mav=0;
   // NeutrinoEventShape = new TF2("landau2D","[0]*TMath::Landau(x,[1],[2],0)*TMath::Landau(y,[3],[4],0)",0,500,0,500);
   // NeutrinoEventShape->SetParameters(30.641,57.941,22.344,57.533,22.232);
    weight_option=0;
}

KinematicReconstruction_LSroutines::~KinematicReconstruction_LSroutines()
{
    //delete NeutrinoEventShape;
}

void KinematicReconstruction_LSroutines::Delete()
{
    delete this;
}

void KinematicReconstruction_LSroutines::ini(double mass_l, double mass_al,double mass_Wp, double mass_Wm)
{
    mt    = 172.5;
    mtbar = 172.5;
    mb    = 4.8;
    mbbar = 4.8;
    mw    = mass_Wp;
    mwbar = mass_Wm; 
    ml    = mass_l;
    mal    = mass_al;
    mv=0;
    mav=0;
    
    
    //weight_option=0;
}

void KinematicReconstruction_LSroutines::SetConstraints(TLorentzVector LV_al, TLorentzVector LV_l, TLorentzVector LV_b, TLorentzVector LV_bbar, double missPx, double missPy)
{
    l  = LV_l;
    al = LV_al;
    b  = LV_b;
    bbar = LV_bbar;
    px_miss = missPx;
    py_miss = missPy;
    DoAll();
}

void KinematicReconstruction_LSroutines::SetConstraints(LV LV_al, LV LV_l, LV LV_b, LV LV_bbar, double missPx, double missPy)
{
    TLorentzVector temp_al(LV_al.Px(),LV_al.Py(),LV_al.Pz(),LV_al.E());
    TLorentzVector temp_l(LV_l.Px(),LV_l.Py(),LV_l.Pz(),LV_l.E());
    TLorentzVector temp_b(LV_b.Px(),LV_b.Py(),LV_b.Pz(),LV_b.E());
    TLorentzVector temp_bbar(LV_bbar.Px(),LV_bbar.Py(),LV_bbar.Pz(),LV_bbar.E());
        l  = temp_l;
        al = temp_al;
        b  = temp_b;
        bbar = temp_bbar;
        px_miss = missPx;
        py_miss = missPy;
        DoAll();
}

int KinematicReconstruction_LSroutines::GetNsol()
{
  return (int)nSol;
}

void KinematicReconstruction_LSroutines::SetWeightOption(int wo)
{
    weight_option=wo;
}


vector< KinematicReconstruction_LSroutines::TopSolution >* KinematicReconstruction_LSroutines::GetTtSol()
{
    return &ttSol;
}


void KinematicReconstruction_LSroutines::SetTrueInfo(TLorentzVector LV_Top, TLorentzVector LV_AntiTop,TLorentzVector LV_Neutrino, TLorentzVector LV_AntiNeutrino)
{
    true_top         = LV_Top;
    true_topbar      = LV_AntiTop;
    true_neutrino    = LV_Neutrino;
    true_neutrinobar = LV_AntiNeutrino;
    FilldTS();
    FilldR();
    FilldN();
}

void KinematicReconstruction_LSroutines::Print()
{
    for(int i=0;i<(int)ttSol.size();i++)
    {
        printf("\nSol: %d:   vw: %f dTS: %f\n",i+1,ttSol[i].vw,ttSol[i].dTS);
//         ttSol[i].top.Print();
//         ttSol[i].topbar.Print();
           ttSol[i].neutrino.Print();
           ttSol[i].neutrinobar.Print();
        
        
        //printf("vw: %f dTS: %f\n",ttSol[i].vw,ttSol[i].dTS);
        
    }
}

TF1* KinematicReconstruction_LSroutines::GetNeutrinoPxF()
{
    return pol4_neutrinoPx;
}

double KinematicReconstruction_LSroutines::Landau2D(double xv,double xvbar)
{
    return 30.641*TMath::Landau(xv,57.941,22.344,0)*TMath::Landau(xvbar,57.533,22.232,0);   // top_mass = 172.5 GeV  CME = 7 TeV
}

void KinematicReconstruction_LSroutines::DoAll()
{
    
    
    ///load neutrino.root file 
       //TFile frootNeut("/home/korol/top/weight/wneutrino_pt.root");
       //double pt_bins[6]={0,60,100,140,200,500};
        

     //TString data_path_wneutrino_E = ttbar::DATA_PATH();
       //data_path_wneutrino_E.Append("/wneutrino_E.root");
       //TFile frootNeut("/data/user/dolinska/CMSSW_5_3_11/src/TopAnalysis/Configuration/analysis/diLeptonic/data/wneutrino_E.root");
       //TFile frootNeut(data_path_wneutrino_E);
       double pt_bins[6]={0,210,240,330,510,1000};
        
        
//         TFile frootNeut("/home/korol/top/weight/wneutrino_pt_eta.root");
//         double pt_top_bins_2d[3]={0,80,150};
//         double eta_top_bins_2d[4]={-5,-1,1,5};
//         
        TH1F * hvw=0;
    /// ...
    

        FindCoeff(coeffs);
        quartic_equation(coeffs[0],coeffs[1],coeffs[2],coeffs[3],coeffs[4],vect_pxv);
        nSol=vect_pxv[0];
        
            for(int i=1;i<=nSol;i++)
            {
                TopRec(vect_pxv[i]);
                 //printf("Sol: %d: \n",i);
                 //top.Print();
                 //topbar.Print();
                TopSolution TS_temp;
                TS_temp.ttPt=tt.Pt();
                TS_temp.TopPt=top.Pt();
                TS_temp.AntiTopPt=topbar.Pt();
                TS_temp.NeutrinoPx=neutrino.Px();
                TS_temp.AntiNeutrinoPx=neutrinobar.Px();
                TS_temp.mTop=top.M();
                TS_temp.mAntiTop=topbar.M();
                  
                //...
                    double vw1=1,vw2=1;
                    char hvw_name[20];
 //pt 1d                   
//                         for(int i=0;i<5;i++)
//                         {
//                             sprintf(hvw_name,"Eneu_true%d",i+1);
//                             if(top.Pt()>pt_bins[i]&&top.Pt()<=pt_bins[i+1])
//                                 {
//                                     hvw = (TH1F*)frootNeut.Get(hvw_name);
//                                     vw1=hvw->GetBinContent(hvw->FindBin(neutrino.E()));
//                             }
//                             else if(top.Pt()>pt_bins[5])
//                             {
//                                 hvw = (TH1F*)frootNeut.Get("Eneu_true6");
//                                 vw1=hvw->GetBinContent(hvw->FindBin(neutrino.E()));
//                             }
//                             
//                             
//                             if(topbar.Pt()>pt_bins[i]&&topbar.Pt()<=pt_bins[i+1])
//                             {
//                                     hvw = (TH1F*)frootNeut.Get(hvw_name);
//                                     vw2=hvw->GetBinContent(hvw->FindBin(neutrinobar.E()));
//                             }
//                             else if(topbar.Pt()>pt_bins[5])
//                             {
//                                 hvw = (TH1F*)frootNeut.Get("Eneu_true6");
//                                 vw2=hvw->GetBinContent(hvw->FindBin(neutrinobar.E()));
//                             }
//                         }

 //E 1d loaded inside
/*                        for(int i=0;i<5;i++)
                        {
                            sprintf(hvw_name,"Eneu_true%d",i+1);
                            if(top.E()>pt_bins[i]&&top.E()<=pt_bins[i+1])
                                {
                                    hvw = (TH1F*)frootNeut.Get(hvw_name);
                                    vw1=hvw->GetBinContent(hvw->FindBin(neutrino.E()));
                            }
                            else if(top.E()>pt_bins[5])
                            {
                                hvw = (TH1F*)frootNeut.Get("Eneu_true6");
                                vw1=hvw->GetBinContent(hvw->FindBin(neutrino.E()));
                            }
                            
                            
                            if(topbar.E()>pt_bins[i]&&topbar.E()<=pt_bins[i+1])
                            {
                                    hvw = (TH1F*)frootNeut.Get(hvw_name);
                                    vw2=hvw->GetBinContent(hvw->FindBin(neutrinobar.E()));
                            }
                            else if(topbar.E()>pt_bins[5])
                            {
                                hvw = (TH1F*)frootNeut.Get("Eneu_true6");
                                vw2=hvw->GetBinContent(hvw->FindBin(neutrinobar.E()));
                            }
                        }*/
       
// E 1d loaded outside
       
                        for(int i=0;i<5;i++)
                        {
                            if(top.E()>pt_bins[i]&&top.E()<=pt_bins[i+1])
                                {
                                    hvw = hneutrino_E[i];
                                    vw1=hvw->GetBinContent(hvw->FindBin(neutrino.E()));
                            }
                            else if(top.E()>pt_bins[5])
                            {
                                hvw = hneutrino_E[5];
                                vw1=hvw->GetBinContent(hvw->FindBin(neutrino.E()));
                            }
                            
                            
                            if(topbar.E()>pt_bins[i]&&topbar.E()<=pt_bins[i+1])
                            {
                                    hvw = hneutrino_E[i];
                                    vw2=hvw->GetBinContent(hvw->FindBin(neutrinobar.E()));
                            }
                            else if(topbar.E()>pt_bins[5])
                            {
                                hvw = hneutrino_E[5];
                                vw2=hvw->GetBinContent(hvw->FindBin(neutrinobar.E()));
                            }
                        }
//        
       
       
 //pt,eta 2d
//                         int Nptbins=(int)(sizeof(pt_top_bins_2d)/sizeof(pt_top_bins_2d[0]));
//                         int Netabins=(int)(sizeof(eta_top_bins_2d)/sizeof(eta_top_bins_2d[0]))-1;
//                         
//                         for(int i=0;i<Nptbins*Netabins;i++)
//                         {
//                                 sprintf(hvw_name,"Eneu_true%d",i+1);
//                                 hvw = (TH1F*)frootNeut.Get(hvw_name);
//                                 
//                             int i_pt = i/Netabins;
//                             int i_eta = i%Netabins;
// 
//                             if(top.Eta()>eta_top_bins_2d[i_eta]&&top.Eta()<=eta_top_bins_2d[i_eta+1])
//                             {  
//                                 if(i_pt==Nptbins-1&&top.Pt()>pt_top_bins_2d[i_pt])
//                                 {
//                                     vw1=hvw->GetBinContent(hvw->FindBin(neutrino.E()));
//                                 }
//                                 else
//                                 {
//                                     if(top.Pt()>pt_top_bins_2d[i_pt]&&top.Pt()<=pt_top_bins_2d[i_pt+1])
//                                     {
//                                         vw1=hvw->GetBinContent(hvw->FindBin(neutrino.E()));
//                                     }
//                                 }
//                             }
//                             
//                             if(topbar.Eta()>eta_top_bins_2d[i_eta]&&topbar.Eta()<=eta_top_bins_2d[i_eta+1])
//                             {  
//                                 if(i_pt==Nptbins-1&&topbar.Pt()>pt_top_bins_2d[i_pt])
//                                 {
//                                     vw2=hvw->GetBinContent(hvw->FindBin(neutrinobar.E()));
//                                 }
//                                 else
//                                 {
//                                     if(topbar.Pt()>pt_top_bins_2d[i_pt]&&topbar.Pt()<=pt_top_bins_2d[i_pt+1])
//                                     {
//                                         vw2=hvw->GetBinContent(hvw->FindBin(neutrinobar.E()));
//                                     }
//                                 }
//                             }
//                             
//                         }
//                         
                       TS_temp.vw=vw1*vw2;
                  //...
                       
  //neutrino 1d weight
//                     double vw1=1,vw2=1;
//                             vw1=hnw_cuts.GetBinContent(hnw_cuts.FindBin(neutrino.E()));
//                             vw2=hnw_cuts.GetBinContent(hnw_cuts.FindBin(neutrinobar.E()));
//                 TS_temp.vw=vw1*vw2;
  // ...                   
                    
  //mbl 1d weight
//                     double vw1=1,vw2=1;
//                             vw1=hnw_cuts.GetBinContent(hnw_cuts.FindBin((b+neutrinobar).M()));
//                             vw2=hnw_cuts.GetBinContent(hnw_cuts.FindBin((bbar+neutrino).M()));
//                 TS_temp.vw=vw1*vw2;
  // ...   
                    
                    
                
//              TS_temp.vw=Landau2D(neutrino.E(),neutrinobar.E());
                
                    if(weight_option==1)
                    {
//                         TF1 f_nm("f_nm","pol2");f_nm.SetParameters(52.8498,-0.010801,0.000480966);
//                         TF1 f_ns("f_ns","pol2");f_ns.SetParameters(15.8754,0.0274776 ,0.000146676);
//                         TF1 landau_n_temp("landau_n","[0]*TMath::Landau(x,[1],[2])");landau_n_temp.SetParameters(1.0/f_ns.Eval(top.Pt()),f_nm.Eval(top.Pt()),f_ns.Eval(top.Pt()));
//                         TF1 landau_an_temp("landau_an","[0]*TMath::Landau(x,[1],[2])");landau_an_temp.SetParameters(1.0/f_ns.Eval(topbar.Pt()),f_nm.Eval(topbar.Pt()),f_ns.Eval(topbar.Pt()));
                        TF1 landau_n_temp("landau_n","[0]*TMath::Landau(x,[1],[2])");landau_n_temp.SetParameters(1.0/20.3864,59.91,20.3864);
                        TF1 landau_an_temp("landau_an","[0]*TMath::Landau(x,[1],[2])");landau_an_temp.SetParameters(1.0/20.3864,59.91,20.3864);
                        
                        
                        TS_temp.vw=landau_n_temp.Eval(neutrino.E())*landau_an_temp.Eval(neutrinobar.E()); 
                        
                        //TF1 f_mbl("f_mbl","[0]*exp(-(x-[1])*(x-[1])/[2])*([3]+[4]*x)");
                        //f_mbl.SetParameters(-0.000110874,1.90958e+02,7.14791e+03,-9.70099e+02,6.31507e+00);
                        //TS_temp.vw=10000000*NeutrinoEventShape->Eval(neutrino.E(),neutrinobar.E())*f_mbl.Eval((b+al).M())*f_mbl.Eval((bbar+l).M())*landau_n_temp.Eval(neutrino.E())*landau_an_temp.Eval(neutrinobar.E());


                        
                    }
                TS_temp.top = top;
                TS_temp.topbar = topbar;
                TS_temp.wp = w;
                TS_temp.wm = wbar;
                TS_temp.neutrino = neutrino;
                TS_temp.neutrinobar = neutrinobar;
                
                TLorentzVector b_boost_top=b,bbar_boost_topbar=bbar;
                b_boost_top.Boost(-top.BoostVector());
                bbar_boost_topbar.Boost(-topbar.BoostVector());
                TS_temp.cos_bTR_top = cos(top.Vect().Angle(b_boost_top.Vect()));
                TS_temp.cos_bbarTR_topbar = cos(topbar.Vect().Angle(bbar_boost_topbar.Vect()));
                
                TLorentzVector top_boost=top,topbar_boost=topbar,b_boost=b;
                top_boost.Boost(-tt.BoostVector());
                topbar_boost.Boost(-tt.BoostVector());
                
                TS_temp.ttpt_top=top_boost.Pt();
                TS_temp.ttpt_topbar=topbar_boost.Pt();
                
                b_boost.Boost(-tt.BoostVector());
                b_boost.Boost(-top_boost.BoostVector());
                TS_temp.cos1 = cos(top_boost.Vect().Angle(b_boost.Vect()));
                
                TLorentzVector wb = w+b,w_boost=w,al_boost=al;
                //w_boost.Boost(-wb.BoostVector());
                al_boost.Boost(-w.BoostVector());
                //al_boost.Boost(-w_boost.BoostVector());
                
                TS_temp.cos2 = cos(w_boost.Vect().Angle(al_boost.Vect()));
                TS_temp.Mtt = tt.M();
                
                TS_temp.mbl    = (b+al).M();
                TS_temp.mblbar = (bbar+l).M();
                
                
                //if((fabs(top.M()-mt)+fabs(topbar.M()-mtbar))<0.01)
                ttSol.push_back(TS_temp);
                  
            }
        nSol=ttSol.size();
        if(nSol>0)SortTopSol(ttSol);

}

void KinematicReconstruction_LSroutines::FilldTS()
{
    double dellta_alpha;
    double dellta_E;
    for(int i=0;i<nSol;i++)
            {
                dellta_alpha = pow(ttSol[i].top.Angle(true_top.Vect())/TMath::Pi(),2) + pow(ttSol[i].topbar.Angle(true_topbar.Vect())/TMath::Pi(),2);
                dellta_E = pow((ttSol[i].top.E()-true_top.E())/true_top.E(),2) + pow((ttSol[i].topbar.E()-true_topbar.E())/true_topbar.E(),2);
                //dellta_E = pow((ttSol[i].top.Pt()-true_top.Pt())/true_top.Pt(),2) + pow((ttSol[i].topbar.Pt()-true_topbar.Pt())/true_topbar.Pt(),2);
                ttSol[i].dTS = sqrt(dellta_alpha+dellta_E);
                
                
                
            }
}
void KinematicReconstruction_LSroutines::FilldR()
{
    for(int i=0;i<nSol;i++)
            {
                ttSol[i].dR = sqrt(pow(ttSol[i].top.DeltaR(true_top),2)+pow(ttSol[i].topbar.DeltaR(true_topbar),2));   
            }
}

void KinematicReconstruction_LSroutines::FilldN()
{
    for(int i=0;i<nSol;i++)
       {
           ttSol[i].dN = sqrt(pow((ttSol[i].neutrino.Px()-true_neutrino.Px()),2)+pow((ttSol[i].neutrino.Py()-true_neutrino.Py()),2)+pow((ttSol[i].neutrino.Pz()-true_neutrino.Pz()),2)+pow((ttSol[i].neutrinobar.Px()-true_neutrinobar.Px()),2)+pow((ttSol[i].neutrinobar.Py()-true_neutrinobar.Py()),2)+pow((ttSol[i].neutrinobar.Pz()-true_neutrinobar.Pz()),2));   
           //ttSol[i].dN = sqrt(pow((ttSol[i].neutrino.Px()-true_neutrino.Px()),2)+pow((ttSol[i].neutrinobar.Px()-true_neutrinobar.Px()),2));   
       }
}

void KinematicReconstruction_LSroutines::SWAPtopSol(KinematicReconstruction_LSroutines::TopSolution& sol1, KinematicReconstruction_LSroutines::TopSolution& sol2)
{
    KinematicReconstruction_LSroutines::TopSolution aux = sol1;
    sol1 = sol2;
    sol2 = aux;
}

void KinematicReconstruction_LSroutines::SortBy(string ch)
{
    
    if(ch=="dTS"&&ttSol.size()>0)
    {
     for(uint i=0;i<ttSol.size()-1;i++)
        {
            if(ttSol[i].dTS > ttSol[i+1].dTS){ SWAPtopSol(ttSol[i],ttSol[i+1]);i=-1;}
        }   
    }
    if(ch=="dR"&&ttSol.size()>0)
    {
     for(uint i=0;i<ttSol.size()-1;i++)
        {
            if(ttSol[i].dR > ttSol[i+1].dR){ SWAPtopSol(ttSol[i],ttSol[i+1]);i=-1;}
        }   
    }
    if(ch=="dN"&&ttSol.size()>0)
    {
     for(uint i=0;i<ttSol.size()-1;i++)
        {
            if(ttSol[i].dN > ttSol[i+1].dN){ SWAPtopSol(ttSol[i],ttSol[i+1]);i=-1; }
        }   
    }
    if(ch=="dRN"&&ttSol.size()>0)
    {
     for(uint i=0;i<ttSol.size()-1;i++)
        {
            if(ttSol[i].dN*ttSol[i].dR > ttSol[i+1].dN*ttSol[i+1].dR){ SWAPtopSol(ttSol[i],ttSol[i+1]);i=-1; }
        }   
    }
    
}

void KinematicReconstruction_LSroutines::SortTopSol(vector< KinematicReconstruction_LSroutines::TopSolution >& v)
{
    //std::vector< KinematicReconstruction_LSroutines::TopSolution > result;
    for(uint i=0;i<v.size()-1;i++)
    {
      if(v[i].vw < v[i+1].vw){ SWAPtopSol(v[i],v[i+1]);i=-1;}
    }
    
    //v.swap(result);
}




void KinematicReconstruction_LSroutines::TopRec(double sol)
{
  double pxp, pyp, pzp, pup, pvp, pwp;
  
  d0=d00;
  d1=d11+d10*sol;
  d2=d22+d21*sol+d20*sol*sol;
  
  c0=c00;
  c1=c11+c10*sol;
  c2=c22+c21*sol+c20*sol*sol;
  
  
  pup = sol;
  pvp = (c0*d2-c2*d0)/(c1*d0-c0*d1);
  pwp = (-1)*(a1+a2*pup+a3*pvp)/a4;
  
  pxp = px_miss-pup;   
  pyp = py_miss-pvp;
  pzp = (-1)*(b1+b2*pxp+b3*pyp)/b4;
  
  neutrinobar.SetXYZM(pxp, pyp, pzp, mav);
  neutrino.SetXYZM(pup, pvp, pwp, mv);
      
  top = b + al + neutrino;
  topbar = bbar + l + neutrinobar; 
  tt=top+topbar;
  w = al + neutrino;
  wbar = l + neutrinobar;
  
}


void KinematicReconstruction_LSroutines::FindCoeff(double* koeficienty)
{
    a1 = ((b.E()+al.E())*(mw*mw-mal*mal-mv*mv)-al.E()*(mt*mt-mb*mb-mal*mal-mv*mv)+2*b.E()*al.E()*al.E()-2*al.E()*(al.Vect().Dot(b.Vect())))/(2*al.E()*(b.E()+al.E()));
    a2 = 2*(b.E()*al.Px()-al.E()*b.Px())/(2*al.E()*(b.E()+al.E()));
    a3 = 2*(b.E()*al.Py()-al.E()*b.Py())/(2*al.E()*(b.E()+al.E()));
    a4 = 2*(b.E()*al.Pz()-al.E()*b.Pz())/(2*al.E()*(b.E()+al.E()));
        
    //printf("Koefs ai: %f %f %f %f\n",a1,a2,a3,a4);//printout
    
    b1 = ((bbar.E()+l.E())*(mwbar*mwbar-ml*ml-mav*mav)-l.E()*(mtbar*mtbar-mbbar*mbbar-ml*ml-mav*mav)+2*bbar.E()*l.E()*l.E()-2*l.E()*(l.Vect().Dot(bbar.Vect())))/(2*l.E()*(bbar.E()+l.E()));
    b2 = 2*(bbar.E()*l.Px()-l.E()*bbar.Px())/(2*l.E()*(bbar.E()+l.E()));
    b3 = 2*(bbar.E()*l.Py()-l.E()*bbar.Py())/(2*l.E()*(bbar.E()+l.E()));
    b4 = 2*(bbar.E()*l.Pz()-l.E()*bbar.Pz())/(2*l.E()*(bbar.E()+l.E()));
    
     //printf("Koefs bi: %f %f %f %f\n",b1,b2,b3,b4);//printout
    
        c22 = (sqr((mw*mw-mal*mal-mv*mv))-4*(sqr(al.E())-sqr(al.Pz()))*sqr(a1/a4)-4*(mw*mw-mal*mal-mv*mv)*al.Pz()*(a1/a4))/sqr(2*(b.E()+al.E())); 
        c21 = (4*(mw*mw-mal*mal-mv*mv)*(al.Px()-al.Pz()*(a2/a4))-8*(sqr(al.E())-sqr(al.Pz()))*(a1*a2/sqr(a4))-8*al.Px()*al.Pz()*(a1/a4))/sqr(2*(b.E()+al.E())); 
        c20 = (-4*(sqr(al.E())-sqr(al.Px()))-4*(sqr(al.E())-sqr(al.Pz()))*sqr(a2/a4)-8*al.Px()*al.Pz()*(a2/a4))/sqr(2*(b.E()+al.E())); 
        c11 = (4*(mw*mw-mal*mal-mv*mv)*(al.Py()-al.Pz()*(a3/a4))-8*(sqr(al.E())-sqr(al.Pz()))*(a1*a3/sqr(a4))-8*al.Py()*al.Pz()*(a1/a4))/sqr(2*(b.E()+al.E())); 
        c10 = (-8*(sqr(al.E())-sqr(al.Pz()))*(a2*a3/sqr(a4)) + 8*al.Px()*al.Py() - 8*al.Px()*al.Pz()*(a3/a4) - 8*al.Py()*al.Pz()*(a2/a4))/sqr(2*(b.E()+al.E()));
        c00 = (-4*(sqr(al.E())-sqr(al.Py())) -4*(sqr(al.E())-sqr(al.Pz()))*sqr(a3/a4)-8*al.Py()*al.Pz()*(a3/a4))/sqr(2*(b.E()+al.E()));
      
       // printf("Koefs ci: %f %f %f %f %f %f\n",c22,c21/c22,c11/c22,c20/c22,c10/c22,c00/c22);//printout
        
        

        double d22_,d21_,d20_,d11_,d10_,d00_;
        d22_ = (sqr((mwbar*mwbar-ml*ml-mav*mav))-4*(sqr(l.E())-sqr(l.Pz()))*sqr(b1/b4)-4*(mwbar*mwbar-ml*ml-mav*mav)*l.Pz()*(b1/b4))/sqr(2*(bbar.E()+l.E())); 
        d21_ = (4*(mwbar*mwbar-ml*ml-mav*mav)*(l.Px()-l.Pz()*(b2/b4))-8*(sqr(l.E())-sqr(l.Pz()))*(b1*b2/sqr(b4))-8*l.Px()*l.Pz()*(b1/b4))/sqr(2*(bbar.E()+l.E())); 
        d20_ = (-4*(sqr(l.E())-sqr(l.Px()))-4*(sqr(l.E())-sqr(l.Pz()))*sqr(b2/b4)-8*l.Px()*l.Pz()*(b2/b4))/sqr(2*(bbar.E()+l.E())); 
        d11_ = (4*(mwbar*mwbar-ml*ml-mav*mav)*(l.Py()-l.Pz()*(b3/b4))-8*(sqr(l.E())-sqr(l.Pz()))*(b1*b3/sqr(b4))-8*l.Py()*l.Pz()*(b1/b4))/sqr(2*(bbar.E()+l.E())); 
        d10_ = (-8*(sqr(l.E())-sqr(l.Pz()))*(b2*b3/sqr(b4)) + 8*l.Px()*l.Py() - 8*l.Px()*l.Pz()*(b3/b4) - 8*l.Py()*l.Pz()*(b2/b4))/sqr(2*(bbar.E()+l.E()));
        d00_  = (-4*(sqr(l.E())-sqr(l.Py())) -4*(sqr(l.E())-sqr(l.Pz()))*sqr(b3/b4)-8*l.Py()*l.Pz()*(b3/b4))/sqr(2*(bbar.E()+l.E()));
        
        //printf("Koefs di_: %f %f %f %f %f %f\n",d22_,d21_/d22_,d11_/d22_,d20_/d22_,d10_/d22_,d00_/d22_);//printout
        
        
        d22 = d22_+sqr(px_miss)*d20_+sqr(py_miss)*d00_+px_miss*py_miss*d10_+px_miss*d21_+py_miss*d11_;
        d21 = -d21_-2*px_miss*d20_-py_miss*d10_;
        d20 = d20_;
        d11 = -d11_-2*py_miss*d00_-px_miss*d10_;
        d10 = d10_;
        d00  = d00_;
        
        //printf("Koefs di: %f %f %f %f %f %f\n",d22, d21/d22, d11/d22, d20/d22, d10/d22, d00/d22);//printout
                

        koeficienty[4] = sqr(c00)*sqr(d22)+c11*d22*(c11*d00-c00*d11)+c00*c22*(sqr(d11)-2*d00*d22)+c22*d00*(c22*d00-c11*d11);
        koeficienty[3] = c00*d21*(2*c00*d22-c11*d11)+c00*d11*(2*c22*d10+c21*d11)+c22*d00*(2*c21*d00-c11*d10)-c00*d22*(c11*d10+c10*d11)-2*c00*d00*(c22*d21+c21*d22)-d00*d11*(c11*c21+c10*c22)+c11*d00*(c11*d21+2*c10*d22);
        koeficienty[2] = sqr(c00)*(2*d22*d20+sqr(d21))-c00*d21*(c11*d10+c10*d11)+c11*d20*(c11*d00-c00*d11)+c00*d10*(c22*d10-c10*d22)+c00*d11*(2*c21*d10+c20*d11)+(2*c22*c20+sqr(c21))*sqr(d00)-2*c00*d00*(c22*d20+c21*d21+c20*d22)+c10*d00*(2*c11*d21+c10*d22)-d00*d10*(c11*c21+c10*c22)-d00*d11*(c11*c20+c10*c21);
       // koeficienty[1] = c00*d21*(2*c00*d20-c10*d10)-c00*d20*(c11*d10+c10*d11)+c00*d10*(c21*d10+2*c20*d11)-2*c00*d00*(c21*d20+c20*d21)+c10*d00*(2*c11*d20+c10*d21)-c20*d00*(2*c21*d00-c10*d11)-d00*d10*(c11*c20+c10*c21);
        koeficienty[1] = c00*d21*(2*c00*d20-c10*d10)-c00*d20*(c11*d10+c10*d11)+c00*d10*(c21*d10+2*c20*d11)-2*c00*d00*(c21*d20+c20*d21)+c10*d00*(2*c11*d20+c10*d21)+c20*d00*(2*c21*d00-c10*d11)-d00*d10*(c11*c20+c10*c21);
        koeficienty[0] = sqr(c00)*sqr(d20)+c10*d20*(c10*d00-c00*d10)+c20*d10*(c00*d10-c10*d00)+c20*d00*(c20*d00-2*c00*d20);
        //printf("Koefs_in_f: %15.15f %f %f %f %f\n",koeficienty[0],koeficienty[1],koeficienty[2],koeficienty[3],koeficienty[4]); //printout

}



double KinematicReconstruction_LSroutines::sqr(double x)
{
    return (x*x);
}

void KinematicReconstruction_LSroutines::SWAP(double& realone, double& realtwo)
{
      if (realtwo < realone) {
    double aux = realtwo;
    realtwo = realone;
    realone = aux;
  }
}

int KinematicReconstruction_LSroutines::sign(long double ld)
{
        
        if(fabs(ld)<0.0000000000001) return 0;
        return (ld>0)?1:-1;
}

void KinematicReconstruction_LSroutines::quartic_equation(double h0, double h1, double h2, double h3, double h4, std::vector< double >& v)
{
     std::vector<double> result;
    
    //printf("Koefs_in_f: %f %f %f %f %f\n",h0,h1,h2,h3,h4); //printout
    //printf("Koefs_norm_in_f: %f %f %f %f %f\n",h0/h0,h1/h0,h2/h0,h3/h0,h4/h0); //printout


        if(sign(a4)==0||sign(b4)==0)
        {
            result.push_back(0);
            v.swap(result);    
        }
        else
        {
               //printf("else1\n"); //printout
            if(sign(h0)==0)
            {
                cubic_equation(h1,h2,h3,h4,result);
                v.swap(result);
            }
           else
            {
                //printf("else2\n"); //printout
                if(sign(h4)==0)
                {
                    cubic_equation(h0,h1,h2,h3,result);
                    result[0]=result[0]+1;
                    result.push_back(0);
                    v.swap(result);
                }
                else
                {
                   //printf("else3\n"); //printout
                    
                     double H1=h1/h0;
                     double H2=h2/h0;
                     double H3=h3/h0;
                     double H4=h4/h0;
                   double K1 = H2 -3*sqr(H1)/8;
                   double K2 = H3 + H1*sqr(H1)/8-H1*H2/2;
                   double K3 = H4-3*sqr(sqr(H1))/256+sqr(H1)*H2/16-H1*H3/4;
                    //printf("Koefs Ki: %f %f %10.10f\n",K1,K2,K3);//printout
                    if(sign(K3)==0)
                    {
                       cubic_equation(1,0,K1,K2,result);
                       for(int i=1;i<=result[0];i++)
                       {
                           result[i]=result[i]-H1/4;
                       }
                        result[0]=result[0]+1;
                        result.push_back(-H1/4);
                        v.swap(result);
                       
                    }
                    else
                    {
                        //printf("else4\n"); //printout
                        std::vector<double> result_t12;
                        
                        std::vector<double> result_t1;
                            result_t1.push_back(0);
                        std::vector<double> result_t2;
                            result_t2.push_back(0);
                        
                        cubic_equation(1,2*K1,(K1*K1-4*K3),(-1)*K2*K2,result_t12); 
                        
                        //std::cout << "hehehe:  " << result_t12[0]  <<  std::endl; //printout
                        
                        
                        for(int i=1;i<=result_t12[0];i++)
                        {
                            //std::cout << "heh:  " << result_t12[i]  << std::endl; //printout
                            
                            if(result_t12[i]>=0)
                            {
                                result_t1[0]=result_t1[0]+2;
                                result_t1.push_back(sqrt(result_t12[i]));
                                result_t1.push_back((-1)*sqrt(result_t12[i]));
                                result_t2[0]=result_t2[0]+2;
                                result_t2.push_back((K1+result_t12[i]-K2/sqrt(result_t12[i]))/2);
                                result_t2.push_back((K1+result_t12[i]+K2/sqrt(result_t12[i]))/2);                                
                            }
                        }  
                        
                        //std::cout  << std::endl;
                        
                        
                        std::vector<double> pre_result1;

                        result.push_back(0);
                        for(int i=1;i<=result_t1[0];i++)
                        {
                            //std::cout << "quadric_equation:   " << i << " " << result_t1[i] << " " << result_t2[i] << std::endl; //printout
                             
                             quadratic_equation(1,result_t1[i],result_t2[i],pre_result1);
                             
                             for(int j=1;j<=pre_result1[0];j++)
                             {
                                // if(pre_result1[0]==2)std::cout << "quadric_equation:   " << i << " " << pre_result1[1] << " " << pre_result1[2] << std::endl; //printout

                                 int flag=1;
                                for(int r=1;r<=result[0];r++)
                                {
                                 if(fabs(result[r]-pre_result1[j])<0.01)flag=0;
                                 //printf("Result-result: %10.10f  \n",result[r]-pre_result1[j]);
                                }
                                if(flag)
                                {
                                    result[0]=result[0]+1;
                                    result.push_back(pre_result1[j]);
                                }
                             }
                            pre_result1.clear();                          
                        }                          
                       for(int k=1;k<=result[0];k++)
                       {
                           
                           //printf("Result: %f   %f \n",H1/4,h1/4); //printout
                           result[k]=result[k]-H1/4;
                           
                       }
                       v.swap(result);   
                    }
                }
            }
        }
}

void KinematicReconstruction_LSroutines::cubic_equation(double a, double b, double c, double d, std::vector< double >& v)
{
        
    std::vector<double> result;
    if(a==0)
    {
        quadratic_equation(b,c,d,result);
        v.swap(result);
    }
    else
    {
       double s1 = b/a;
       double s2 = c/a;
       double s3 = d/a;
       
       double q = (s1*s1-3*s2)/9;
       double q3 = q*q*q;
       double r = (2*s1*s1*s1-9*s1*s2+27*s3)/54;
       double r2 = r*r;
       double S = r2-q3;
       if(sign(S)<0)
       {
           
           result.push_back(3);
           double F = acos(r/sqrt(q3));
           result.push_back(-2*sqrt(fabs(q))*cos(F/3)-s1/3);
           result.push_back(-2*sqrt(fabs(q))*cos((F+2*TMath::Pi())/3)-s1/3);
           result.push_back(-2*sqrt(fabs(q))*cos((F-2*TMath::Pi())/3)-s1/3);  
           v.swap(result);
           
       }
       else 
       {
           if(sign(S)==0)
           {
                long double A = r+sqrt(fabs(r2-q3));
                A = A<0 ? pow(fabs(A),(long double)1.0/3) : -pow(fabs(A),(long double)1.0/3);
                long double B = sign(A) == 0 ? 0 : q/A; 
                result.push_back(2);
                result.push_back(A+B-s1/3);
                result.push_back(-0.5*(A+B)-s1/3);  //!!!
                v.swap(result);
           }
           else
           {
               long double A = r+sqrt(fabs(r2-q3));
               A = A<0 ? pow(fabs(A),(long double)1.0/3) : -pow(fabs(A),(long double)1.0/3);
               long double B = sign(A) == 0 ? 0 : q/A; 
               result.push_back(1);
               result.push_back(A+B-s1/3);
               v.swap(result);
           }
       }
       
    }
}

void KinematicReconstruction_LSroutines::quadratic_equation(double a, double b, double c, std::vector< double >& v)
{
     std::vector<double> result;
     //printf("a: %10.10f\n",a);//printout
    if(a==0)
    {
        linear_equation(b,c,result);
        v.swap(result);
    }
    else
    {
        double D = b*b-4*a*c;
        //printf("D: %10.10f\n",D);//printout
        if(sign(D)<0)
        {
            result.push_back(0);
            v.swap(result);
        }
        else 
        {
            if(sign(D)==0)
            {
                result.push_back(1);
                result.push_back((-1)*b/(2*a));
                v.swap(result);
            }
            else
            {
                result.push_back(2);
                result.push_back((-b-sqrt(D))/(2*a));
                result.push_back((-b+sqrt(D))/(2*a));
                v.swap(result);
            }
        }
    }
}

void KinematicReconstruction_LSroutines::linear_equation(double a, double b, std::vector< double >& v)
{
        std::vector<double> result;
    if(a==0)
    {
        result.push_back(0);
        v.swap(result);
    }
    else
    {
        result.push_back(1);
        result.push_back((-1)*(b/a));
        v.swap(result);
    }
}
