#include "KinematicReconstruction.h"
#include <TAttLine.h>
#define printout 0
#include "KinematicReconstruction_LSroutines.h"
#include "analysisUtils.h"
#include <TLorentzVector.h>


#include <cmath>
#include <cassert>
#include <algorithm>
#include <utility>
#include <cmath>

#include <TLorentzVector.h>
#include <TMath.h>

#include "KinReco.h"
#include "utils.h"
#include "analysisUtils.h"
#include "classes.h"
// #include "TVector3.h"
#include <TRandom3.h>

using namespace std;

KinematicReconstruction::KinematicReconstruction(const LV& leptonMinus, const LV& leptonPlus,const VLV *jets, const std::vector<double> *btags, const LV* met)
{

std::vector<struct_KinematicReconstruction> vect_sol;

	TLorentzVector leptonPlus_tlv = ttbar::LVtoTLV(leptonPlus);
	TLorentzVector leptonMinus_tlv = ttbar::LVtoTLV(leptonMinus);
	TLorentzVector met_tlv = ttbar::LVtoTLV(*met);
	
	    std::vector<TLorentzVector> jets_tlv;
    		for (const auto& jet : *jets) {
        		jets_tlv.push_back(ttbar::LVtoTLV(jet));
    		}

    vector<int> b1_id;
    vector<int> b2_id;
    vector<double> btag_ww;
    vector<int> nb_tag;

	for(int i=0;i<(int)btags->size();i++)
	{
    		for(int j=0;j<(int)btags->size();j++)
    		{
        		double wi = btags->at(i);
        		double wj = btags->at(j);
        		//if(i==j||(wi<0.244&&wj<0.244)||(wi<0||wj<0))continue;
        		if(i==j||(wi<0.244&&wj<0.244))continue;
        		btag_ww.push_back(wi+wj);

			if(wi>0.244&&wj>0.244){nb_tag.push_back(2);}
			else{nb_tag.push_back(1);}

        		b1_id.push_back(i);
        		b2_id.push_back(j);
    		}
	}

 if(b1_id.size()<2){nSol=0;}
 else
 {
			for(int i=0;i<(int)btag_ww.size()-1;i++)
			{
        			if(btag_ww[i]<btag_ww[i+1])
        			{
		       		double aux = btag_ww[i];
            			btag_ww[i] = btag_ww[i+1];
            			btag_ww[i+1] = aux;
            			int aix = b1_id[i];
            			b1_id[i] = b1_id[i+1];
				b1_id[i+1] = aix;
            			aix = b2_id[i];
            			b2_id[i] = b2_id[i+1];
            			b2_id[i+1] = aix;
				aix = nb_tag[i];
				nb_tag[i] = nb_tag[i+1];
				nb_tag[i+1] = aix;

            			i=-1;
        			}
			}
			

			            ///jets loop
		
		nSol=0;
            for(int ib=0;ib<(int)b1_id.size();ib++)
            {
                int j1=b1_id[ib];
                int j2=b2_id[ib];
                        //if((*jets)[j1].Pt()<30||(*jets)[j2].Pt()<30)continue;
                        //if(fabs((*jets)[j1].Eta())>2.4||fabs((*jets)[j2].Eta())>2.4)continue;
                        TLorentzVector l_temp,al_temp,b_temp,bbar_temp,met_temp;
                        l_temp=leptonMinus_tlv;
                        al_temp=leptonPlus_tlv;
                        b_temp=jets_tlv.at(j1);
                        bbar_temp=jets_tlv.at(j2);
                        met_temp.SetXYZM(met->Px(),met->Py(),0,0);
                        //if((al_temp+b_temp).M()>180||(l_temp+bbar_temp).M()>180)continue;

				/*smearing*/
//                                 TF1 fJet("fJet","[0]*pow((x-0),0.5)+[1]");
//                                     fJet.SetParameters(4.18432,-24.8944);
//                                 TF1 fLep("fLep","[0]*pow((x-0),0.5)+[1]");
//                                     fLep.SetParameters(0.575716,-3.11214);
// 
// 
//                             TRandom3 r(0);  ///random seed
// //                              TF1 f1("f1","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x",30,580);
// //                              f1.SetParameters(1.06517e+01,3.58131e-02,7.44249e-04,-1.70968e-06,1.21316e-09);
//                              double bRMS=fJet.Eval(b_temp.E())/b_temp.E(); //%
//                              double bbarRMS=fJet.Eval(bbar_temp.E())/bbar_temp.E(); //%
//                              double lRMS=fLep.Eval(l_temp.E())/l_temp.E(); //%
//                              double alRMS=fLep.Eval(al_temp.E())/al_temp.E(); //%
// 
//                              TVector3 vX_reco = -b_temp.Vect()-bbar_temp.Vect()-l_temp.Vect()-al_temp.Vect()-met_temp.Vect();
// 
//                              double xRMS=20/vX_reco.Pt(); //%
// 			  double vw_max=0;
//                         for(int sm=0;sm<100;sm++)
//                         {  
//                            TLorentzVector b_sm=b_temp;
//                            TLorentzVector bbar_sm=bbar_temp;
//                            TLorentzVector met_sm=met_temp;
//                            TLorentzVector l_sm=l_temp;
//                            TLorentzVector al_sm=al_temp;
// 
// 
//                            double fB=r.Gaus(1,bRMS);
//                            double xB=sqrt((fB*fB*b_sm.E()*b_sm.E()-b_sm.M2())/(b_sm.P()*b_sm.P()));
//                            double fBbar=r.Gaus(1,bbarRMS);
//                            double xBbar=sqrt((fBbar*fBbar*bbar_sm.E()*bbar_sm.E()-bbar_sm.M2())/(bbar_sm.P()*bbar_sm.P()));
// 
//                            double fL=r.Gaus(1,lRMS);
//                            double xL=sqrt((fL*fL*l_sm.E()*l_sm.E()-l_sm.M2())/(l_sm.P()*l_sm.P()));
//                            double faL=r.Gaus(1,alRMS);
//                            double xaL=sqrt((faL*faL*al_sm.E()*al_sm.E()-al_sm.M2())/(al_sm.P()*al_sm.P()));
// 
//                            double xX=r.Gaus(1,xRMS);
// 
//                            //met_sm.SetXYZM(((b_sm.Px()*(1-xB)+bbar_sm.Px()*(1-xBbar))/(met_sm.Px())+1)*met_sm.Px(),((b_sm.Py()*(1-xB)+bbar_sm.Py()*(1-xBbar))/(met_sm.Py())+1)*met_sm.Py(),0,0); // tollko b-jet
//                            //met_sm.SetXYZM(((b_sm.Px()*(1-xB)+bbar_sm.Px()*(1-xBbar)+l_sm.Px()*(1-xL)+al_sm.Px()*(1-xaL))/(met_sm.Px())+1)*met_sm.Px(),((b_sm.Py()*(1-xB)+bbar_sm.Py()*(1-xBbar)+l_sm.Py()*(1-xL)+al_sm.Py()*(1-xaL))/(met_sm.Py())+1)*met_sm.Py(),0,0); //only b-jet and lep
//                            met_sm.SetXYZM(((b_sm.Px()*(1-xB)+bbar_sm.Px()*(1-xBbar)+l_sm.Px()*(1-xL)+al_sm.Px()*(1-xaL)+vX_reco.Px()*(1-xX))/(met_sm.Px())+1)*met_sm.Px(),((b_sm.Py()*(1-xB)+bbar_sm.Py()*(1-xBbar)+l_sm.Py()*(1-xL)+al_sm.Py()*(1-xaL)+vX_reco.Py()*(1-xX))/(met_sm.Py())+1)*met_sm.Py(),0,0); //all
// 
//                            b_sm.SetXYZT(b_sm.Px()*xB,b_sm.Py()*xB,b_sm.Pz()*xB,b_sm.E()*fB);
//                            bbar_sm.SetXYZT(bbar_sm.Px()*xBbar,bbar_sm.Py()*xBbar,bbar_sm.Pz()*xBbar,bbar_sm.E()*fBbar);
// 
//                            l_sm.SetXYZT(l_sm.Px()*xL,l_sm.Py()*xL,l_sm.Pz()*xL,l_sm.E()*fL);
//                            al_sm.SetXYZT(al_sm.Px()*xaL,al_sm.Py()*xaL,al_sm.Pz()*xaL,al_sm.E()*faL);
// 
//                            KinematicReconstruction_LSroutines tp_sm(172.5,4.8,80.4,0.0,0.0);  
//                            tp_sm.SetConstraints(al_sm,l_sm,b_sm,bbar_sm,met_sm.Px(),met_sm.Py());
// 
//                               if(!(tp_sm.GetNsol()<1||tp_sm.GetNsol()==1||tp_sm.GetNsol()==3))
//                               { 
//                                 if(tp_sm.GetTtSol()->at(0).vw>vw_max)
//                                     { 
// 					nSol++;
// 
//                                         vw_max=tp_sm.GetTtSol()->at(0).vw;
// 					        sol.jetB = b_temp;
//         					sol.jetBbar = bbar_temp;
//         					sol.lm = leptonMinus_tlv;
// 						sol.lp = leptonPlus_tlv;
//         					sol.met = met_temp;
//         					sol.neutrino = tp_sm.GetTtSol()->at(0).neutrino;
//         					sol.neutrinoBar = tp_sm.GetTtSol()->at(0).neutrinobar;
//         					sol.weight = tp_sm.GetTtSol()->at(0).vw;
//         					sol.Wplus = sol.lp + sol.neutrino;
//         					sol.Wminus = sol.lm + sol.neutrinoBar;
//         					sol.top = sol.Wplus + sol.jetB;
// //						cout << "vw: " << tp_m.GetTtSol()->at(0).vw << "pt: " << sol.top.Pt() << endl;
//         					sol.topBar = sol.Wminus + sol.jetBbar;
//         					sol.ttbar = sol.top + sol.topBar;
// 						sol.jetB_index = j1;
//                         			sol.jetBbar_index = j2;
// 						sol.ntags = nb_tag[ib];
//                                     }
// 
//                               }
// 			}
	/*smearing*/
                        /*mass scan*/

			  double vw_max=0;
                          for(double im=100;im<300.5;im += 1){
                          //if(1) {double im=173;

                              KinematicReconstruction_LSroutines tp_m(im,4.8,80.4,0.0,0.0);

                              tp_m.SetConstraints(al_temp,l_temp,b_temp,bbar_temp,met_temp.Px(),met_temp.Py());

                              if(!(tp_m.GetNsol()<1||tp_m.GetNsol()==1||tp_m.GetNsol()==3))
                              {


                                if(tp_m.GetTtSol()->at(0).vw>vw_max)
                                    {
					nSol++;

                                        vw_max=tp_m.GetTtSol()->at(0).vw;
					        sol.jetB = b_temp;
        					sol.jetBbar = bbar_temp;
        					sol.lm = leptonMinus_tlv;
						sol.lp = leptonPlus_tlv;
        					sol.met = met_temp;
        					sol.neutrino = tp_m.GetTtSol()->at(0).neutrino;
        					sol.neutrinoBar = tp_m.GetTtSol()->at(0).neutrinobar;
        					sol.weight = tp_m.GetTtSol()->at(0).vw;
        					sol.Wplus = sol.lp + sol.neutrino;
        					sol.Wminus = sol.lm + sol.neutrinoBar;
        					sol.top = sol.Wplus + sol.jetB;
//						cout << "vw: " << tp_m.GetTtSol()->at(0).vw << "pt: " << sol.top.Pt() << endl;
        					sol.topBar = sol.Wminus + sol.jetBbar;
        					sol.ttbar = sol.top + sol.topBar;
						sol.jetB_index = j1;
                        			sol.jetBbar_index = j2;
						sol.ntags = nb_tag[ib];
                                    }
				
                              }

                           }

                      /*mass scan*/

if(vw_max>0){vect_sol.push_back(sol);
//jeka
 //cout << "N tags:  " << sol.ntags << endl;
}

    } ///end jets loop   
if(nSol>0){

    std::nth_element(begin(vect_sol), begin(vect_sol), end(vect_sol),
        [](const struct_KinematicReconstruction& a, const struct_KinematicReconstruction& b){
            return  b.ntags < a.ntags
                    ||
                    (b.ntags == a.ntags && b.weight < a.weight);
        });

	sol=vect_sol[0];


	}
 } //end else



}

int KinematicReconstruction::GetNSol()
{
	return nSol;	
}
struct_KinematicReconstruction KinematicReconstruction::GetSol()
{
	return sol;
}
