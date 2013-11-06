#include "TopAnalysis/HiggsUtils/interface/JetProperties.h"




JetProperties::JetProperties():
jetChargeGlobalPtWeighted_(0), jetChargeRelativePtWeighted_(0),
jetAssociatedPartonPdgId_(0), jetAssociatedParton_(math::PtEtaPhiMLorentzVectorD(0,0,0,0)) //NEED TO DISCOVER HOW TO INITIALISE MY VECTORS HERE!!!!!!!!!
{}
    
JetProperties::JetProperties(const double& jetChargeGlobalPtWeighted, const double& jetChargeRelativePtWeighted,
			     const int& jetAssociatedPartonPdgId, const math::PtEtaPhiMLorentzVectorD& jetAssociatedParton, 
			     const std::vector<math::PtEtaPhiMLorentzVectorD>& jetTrack, const std::vector<int>& jetTrackCharge/*,
			     const std::vector<int>& jetTrackIndex*/):
jetChargeGlobalPtWeighted_(jetChargeGlobalPtWeighted), jetChargeRelativePtWeighted_(jetChargeRelativePtWeighted),
jetAssociatedPartonPdgId_(jetAssociatedPartonPdgId), jetAssociatedParton_(jetAssociatedParton),
jetTrack_(jetTrack), jetTrackCharge_(jetTrackCharge)/*,jetTrackIndex_(jetTrackIndex)*/
{}
    
JetProperties::JetProperties(const JetProperties& jetProperties):
jetChargeGlobalPtWeighted_(jetProperties.jetChargeGlobalPtWeighted_), jetChargeRelativePtWeighted_(jetProperties.jetChargeRelativePtWeighted_),
jetAssociatedPartonPdgId_(jetProperties.jetAssociatedPartonPdgId_), jetAssociatedParton_(jetProperties.jetAssociatedParton_),jetTrack_(jetProperties.jetTrack_), 
jetTrackCharge_(jetProperties.jetTrackCharge_)/*,jetTrackIndex_(jetProperties.jetTrackIndex_)*/
{}
    






double
JetProperties::jetChargeGlobalPtWeighted()const{return jetChargeGlobalPtWeighted_;}



double
JetProperties::jetChargeRelativePtWeighted()const{return jetChargeRelativePtWeighted_;}



int
JetProperties::jetAssociatedPartonPdgId()const{return jetAssociatedPartonPdgId_;}



math::PtEtaPhiMLorentzVectorD
JetProperties::jetAssociatedParton()const{return jetAssociatedParton_;}



std::vector<math::PtEtaPhiMLorentzVectorD>
JetProperties::jetTrack()const{return jetTrack_;}



std::vector<int>
JetProperties::jetTrackCharge()const{return jetTrackCharge_;}



// std::vector<int>
// JetProperties::jetTrackIndex()const{return jetTrackIndex_;}




