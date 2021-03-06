
#include "KinematicReconstruction_MeanSol.h"


KinematicReconstruction_MeanSol::KinematicReconstruction_MeanSol(double topm):
sum_weight_(0),
max_sum_weight_(0)
{
    mass_top_=topm;
}

KinematicReconstruction_MeanSol::~KinematicReconstruction_MeanSol()
{

}
void KinematicReconstruction_MeanSol::clear()
{
    v_top_.clear();
    v_topbar_.clear();
    v_n_.clear();
    v_nbar_.clear();
    v_weight_.clear();
    sum_weight_=0;
    max_sum_weight_=0;
}

void KinematicReconstruction_MeanSol::add(TLorentzVector top, TLorentzVector topbar,TLorentzVector n,TLorentzVector nbar,double weight,double mbl_weight)
{
    v_top_.push_back(top);
    v_topbar_.push_back(topbar);
    v_n_.push_back(n);
    v_nbar_.push_back(nbar);

    v_weight_.push_back(weight);    
    sum_weight_ = sum_weight_ + weight;
    max_sum_weight_ = max_sum_weight_ + mbl_weight;
}


void KinematicReconstruction_MeanSol::add(TLorentzVector top, TLorentzVector topbar,TLorentzVector n,TLorentzVector nbar,double weight)
{
    v_top_.push_back(top);
    v_topbar_.push_back(topbar);
    v_n_.push_back(n);
    v_nbar_.push_back(nbar);

    v_weight_.push_back(weight);    
    sum_weight_ = sum_weight_ + weight;
    max_sum_weight_ = max_sum_weight_ +weight;
}

void KinematicReconstruction_MeanSol::getMeanVect(TLorentzVector& lv,vector<TLorentzVector> vlv,double mass)
{
    double px_sum=0;
    double py_sum=0;
    double pz_sum=0;
    double px=0;
    double py=0;
    double pz=0;

    for(int i=0;i<((int)vlv.size());i++)
    {
          px_sum=px_sum+v_weight_.at(i)*vlv.at(i).Px();
          py_sum=py_sum+v_weight_.at(i)*vlv.at(i).Py();
          pz_sum=pz_sum+v_weight_.at(i)*vlv.at(i).Pz();          
    }

      px=px_sum/sum_weight_;
      py=py_sum/sum_weight_;
      pz=pz_sum/sum_weight_;
      
      lv.SetXYZM(px,py,pz,mass);

}


void KinematicReconstruction_MeanSol::getMeanSol(TLorentzVector& top, TLorentzVector& topbar, TLorentzVector& n, TLorentzVector& nbar)
{
        getMeanVect(top,v_top_,mass_top_);
        getMeanVect(topbar,v_topbar_,mass_top_);
        getMeanVect(n,v_n_,0);
        getMeanVect(nbar,v_nbar_,0);
        
}

double KinematicReconstruction_MeanSol::getSumWeight()
{
    return sum_weight_; // for 1 weight
//     return max_sum_weight_; // for 2 weights
    
}

int KinematicReconstruction_MeanSol::getNsol()
{
    return (int)v_top_.size();
}

