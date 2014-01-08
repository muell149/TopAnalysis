#include "../interface/bTagBase.h"
#include <stdexcept>
#include "TRandom3.h"

namespace ztop {
/**
 * constructor does nothing in particular
 */
bTagBase::bTagBase() {

    init_ = false;
    makeeffs_ = true;
    histp_ = 0;
    effhistp_ = 0;
    syst_ = nominal;
    is2011_ = false;
    TH1::AddDirectory(kFALSE);
    nancount_=0;

    wp_ = csvl_wp;
    showWarnings = true;
    debug = false;

    sumStuffEff_ = 0.9999999;
    sumStuffSfEff_ = 0.9999999;
    wpvals_.resize(workingPoints::length_wp, 0);
    minpt_.resize(workingPoints::length_wp, 0);
    maxpt_.resize(workingPoints::length_wp, 0);

}
/**
 * sets the sample name. It can be used as a unique identifier when
 * reading or writing the histograms/data
 * If input is read, the name is used to identify the right set of
 * histograms (e.g. different for each sample but in the same bTagBase
 * object)
 */
int bTagBase::setSampleName(const std::string & samplename) {
    //set pointers
    initWorkingpoints();

    std::map<std::string, std::vector<TH2D> >::iterator sampleit = histos_.find(
            samplename);
    if (sampleit != histos_.end())
        histp_ = &(sampleit->second);
    else
        histp_ = 0;
    std::map<std::string, std::vector<TH2D> >::iterator effit = effhistos_.find(
            samplename);
    if (effit != effhistos_.end())
        effhistp_ = &(effit->second);
    else
        effhistp_ = 0;

    if (!makeeffs_ && effhistp_ && histp_) {
        std::cout << "loaded b-tag efficiency histos for " << samplename
                << std::endl;
        return 1;
    } else if (!makeeffs_ && !effhistp_) {
        std::cout << " bTagBase::setSampleName: efficiency for " << samplename
                << " not derived, yet! exit." << std::endl;
        return -1;
    }

    // efficiencies not determined yet -> prepare efficiency histos
    // bool adddirtemp=TH1::AddDirectory;
    TH1::AddDirectory(kFALSE); //prevent some weird root behaviour
    std::cout << "preparing b-tag efficiency histos for " << samplename
            << std::endl;

    //////// put in algorithm to automatically rebin in case of low statistics !! then use a fine (equals btv binning) binning

    float effptbins[] = { 20., 50., 70., 100., 160., 210., 800. };
    unsigned int npt = 7;
    float effetabins[] = { 0.0, 0.5, 1.0, 2.5 };
    unsigned int neta = 4;

    //probably there will be less statistics for the light jets, so histos might need a coarser binning

    float l_effptbins[] = { 20., 70., 120., 800. };
    unsigned int l_npt = 4;
    float l_effetabins[] = { 0.0, 1.5, 3.0 };
    unsigned int l_neta = 3;

    TH2D bjets = TH2D((TString) ("bjets2D_"), "unTagged Bjets", npt - 1,
            effptbins, neta - 1, effetabins);
    bjets.Sumw2();
    TH2D bjetstagged = TH2D((TString) ("bjetsTagged2D_"), "Tagged Bjets",
            npt - 1, effptbins, neta - 1, effetabins);
    bjetstagged.Sumw2();
    TH2D cjets = TH2D((TString) ("cjets2D_"), "unTagged Cjets", npt - 1,
            effptbins, neta - 1, effetabins);
    cjets.Sumw2();
    TH2D cjetstagged = TH2D((TString) ("cjetsTagged2D_"), "Tagged Cjets",
            npt - 1, effptbins, neta - 1, effetabins);
    cjetstagged.Sumw2();
    TH2D ljets = TH2D((TString) ("ljets2D_"), "unTagged Ljets", l_npt - 1,
            l_effptbins, l_neta - 1, l_effetabins);
    ljets.Sumw2();
    TH2D ljetstagged = TH2D((TString) ("ljetsTagged2D_"), "Tagged Ljets",
            l_npt - 1, l_effptbins, l_neta - 1, l_effetabins);
    ljetstagged.Sumw2();

    std::vector<TH2D> temp;
    temp << bjets << bjetstagged << cjets << cjetstagged << ljets
            << ljetstagged;
    histos_[samplename] = temp;
    histp_ = &(histos_.find(samplename)->second);

    TH2D beff = TH2D((TString) ("beff2D_"), "Bjets eff", npt - 1, effptbins,
            neta - 1, effetabins);
    beff.Sumw2();
    TH2D ceff = TH2D((TString) ("ceff2D_"), "Cjets eff", npt - 1, effptbins,
            neta - 1, effetabins);
    ceff.Sumw2();
    TH2D leff = TH2D((TString) ("leff2D_"), "Ljets eff", l_npt - 1, l_effptbins,
            l_neta - 1, l_effetabins);
    leff.Sumw2();

    temp.clear();
    temp << beff << ceff << leff;
    effhistos_[samplename] = temp;
    effhistp_ = &(effhistos_.find(samplename)->second);

    return 0;

}
/**
 * adds an entry for a jet with p4, genpartonFlavour, bDiscrValue  and PUweight
 * to the efficiency histograms
 */
void bTagBase::fillEff(const float& pt, const float&abs_eta,
        const int &genPartonFlavour, const float &bDiscrVal,
        const float &puweight) {
    if (!makeeffs_)
        return;
    if (!histp_) { //protection
        std::cout
        << "bTagBase::fillEff: you have to set a samplename before filling efficiency histograms!"
        << std::endl;
        throw std::runtime_error(
                "bTagBase::fillEff: you have to set a samplename before filling efficiency histograms!");
    }
    if (genPartonFlavour == 0)
        return;

    jetTypes jettype=jetType(genPartonFlavour);

    if (jettype == bjet) { // b jets
        histp_->at(0).Fill(pt, abs_eta, puweight);
        if (bDiscrVal > wpvals_[wp_])
            histp_->at(1).Fill(pt, abs_eta, puweight);
    } else if (jettype == cjet) { // c jets

        histp_->at(2).Fill(pt, abs_eta, puweight);
        if (bDiscrVal > wpvals_[wp_])
            histp_->at(3).Fill(pt, abs_eta, puweight);
    } else if (jettype == lightjet) { // light jets (including gluon jets)
        histp_->at(4).Fill(pt, abs_eta, puweight);
        if (bDiscrVal > wpvals_[wp_])
            histp_->at(5).Fill(pt, abs_eta, puweight);
    }
}
/**
 * creates efficiency histograms, to be run after all are filled
 */
void bTagBase::makeEffs() {
    if (!makeeffs_)
        return;
    if (!histp_ || !effhistp_) {
        std::cout << "bTagBase::makeEffs: you have to set a samplename!"
                << std::endl;
        throw std::runtime_error(
                "bTagBase::makeEffs: you have to set a samplename!");
    }

    for (unsigned int i = 0; i < effhistp_->size(); i++) {
        for (int binx = 1; binx <= effhistp_->at(i).GetNbinsX() + 1; binx++) {
            for (int biny = 1; biny <= effhistp_->at(i).GetNbinsY() + 1;
                    biny++) {
                //
                //uses histos at 2i and 2i+1
                float cont = 1;
                float err = 0.99; //to avoid zeros!
                if (histp_->at(2 * i).GetBinContent(binx, biny) > 0) {
                    cont = histp_->at(2 * i + 1).GetBinContent(binx, biny)
                                                                                                                            / histp_->at(2 * i).GetBinContent(binx, biny);
                    if (debug)
                        std::cout << "makeEffs: content: " << cont;
                    err = sqrt(
                            cont * (1 - cont)
                            / histp_->at(2 * i).GetBinContent(binx,
                                    biny));
                    if (debug)
                        std::cout << " error: " << err << "  " << binx << " "
                        << biny << std::endl;
                }
                if (err > 0.02 && err != 0.99) {
                    if (showWarnings)
                        std::cout
                        << "bTagBase::makeEffs: warning. error in bin ("
                        << binx << ", " << biny << ") for histogram "
                        << effhistp_->at(i).GetName()
                        << " is larger than 0.02" << std::endl;

                    //here there is space for automatic rebinning!! just bool binok, if not merge 2 bins - maybe in second step, here performance is not crucial

                }
                effhistp_->at(i).SetBinContent(binx, biny, cont);
                effhistp_->at(i).SetBinError(binx, biny, err);
            }
        }
    }
}

void bTagBase::countJet(const float & pt, const float& abs_eta,
        const int & genPartonFlavor) { //pt and eta not const & for a purpose

    if(makeeffs_) return;
    if (genPartonFlavor == 0)
        return;

    jetTypes jettype=jetType(genPartonFlavor);
    float sf = 1;
    float eff = 0;
    sf=jetSF(pt, abs_eta,jettype);
    eff=jetEff(pt, abs_eta,jettype);
    /*
    unsigned int effh = 100;


    if (jettype == bjet) { // b jets
        effh = 0;
        sf = BJetSF(pt, abs_eta);
    } else if (jettype == cjet) { // c jets
        effh = 1;
        sf = CJetSF(pt, abs_eta);
    } else { // (including gluon jets)
        effh = 2;
        sf = LJetSF(pt, abs_eta);
    }

    int ptbin = 0;
    int etabin = 0;
    int bla = 0;

    effhistp_->at(effh).GetBinXYZ(effhistp_->at(effh).FindBin(pt, abs_eta),
            ptbin, etabin, bla);
    eff = effhistp_->at(effh).GetBinContent(ptbin, etabin);

    if (!(0 <= eff && eff <= 1 && sf >= 0 && sf <= 100))
        std::cout << "warning SF: " << sf << "   eff(" << pt << " GeV, "
        << abs_eta << "): " << eff << "\t genflav: " << genPartonFlavor
        << "\teffh " << effh << std::endl;
     */
    sumStuffEff_ = sumStuffEff_ * (1 - eff);
    sumStuffSfEff_ = sumStuffSfEff_ * (1 - sf * eff);

}
bool bTagBase::changeJetTag(const float & pt, const float& abs_eta,
        const int & genPartonFlavor, const float & tagValue, const float & seed) const {

    jetTypes jettype=jetType(genPartonFlavor);
    const bool isBTagged = tagValue > wpvals_[wp_];
    const double Btag_eff = jetEff(pt, abs_eta, jettype);
    const double Btag_SF = jetSF(pt, abs_eta, jettype);
    const float coin = TRandom3(seed).Uniform(1.0);

    if ( Btag_SF > 1. ) {  // use this if SF>1
        if ( !isBTagged ) {
            // fraction of jets that need to be upgraded
            const float mistagPercent = (1.0 - Btag_SF) / (1.0 - (1.0/Btag_eff) );

            //upgrade to tagged
            if( coin < mistagPercent ) return true;
        }
    }
    else if ( Btag_SF < 1. ) {  // use this if SF<1
        // downgrade tagged to untagged
        if ( isBTagged && coin > Btag_SF ) return false;
    }
    else {  // no change if exactly SF==1
        return isBTagged;
    }
    return isBTagged;

}
float bTagBase::getEventSF() {
    if(makeeffs_) return 1.;
    float sf = (1 - sumStuffSfEff_) / (1 - sumStuffEff_);
    if(sf!=sf){
        sf=1;
        ++nancount_;
    }
    resetCounter();
    return sf;
}

float bTagBase::jetSF(const float &pt, const float& abs_eta,const jetTypes & jettype) const{
    if(jettype==bjet) return BJetSF(pt, abs_eta);
    if(jettype==cjet) return CJetSF(pt, abs_eta);
    if(jettype==lightjet) return LJetSF(pt, abs_eta);
    else return 1.;
}

float bTagBase::jetEff(const float &pt, const float& abs_eta,const jetTypes & jettype) const{
    if(jettype == undefined)
        return 1;
    unsigned int effh = 100;
    if(jettype==bjet)  effh = 0;
    else if(jettype==cjet)  effh = 1;
    else if(jettype==lightjet)  effh = 2;

    int ptbin = 0;
    int etabin = 0;
    int bla = 0;

    effhistp_->at(effh).GetBinXYZ(effhistp_->at(effh).FindBin(pt, abs_eta),
            ptbin, etabin, bla);
    return effhistp_->at(effh).GetBinContent(ptbin, etabin);
}
// ///////////////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////// BTagPOG INPUT //////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////////////

/*
 * For each tagger or working point, the input from the BTag POG needs to be implemented
 * as follows:
 *
 * Add the tagger name including the working point to the enum workingPoints in bTagBase.h
 * You can find the definition right on top of the class declaration. Do not touch the last entry.
 *
 * 1. Add the working point discriminator value to the function initWorkingpoints()
 *    as wpvals_.at(<your_new_enum)= discriminatorvalue;
 *    and the pt range the SF are defined in
 *    minpt_.at(<your_new_enum)=?;
 *    maxpt_.at(<your_new_enum)=?;
 *
 *
 * 2. Add the corresponding scale factors for B jets to the function BJetSF
 *    - copy the full entry starting with "if(wp_== csvl_wp){"
 *    - paste it right before the marker --END OF WORKING POINTS---
 *    - edit the comments where the SF come from, give a link etc
 *    - adapt numbers and WP definition, change "if" to "else if"
 *    - don't change the parts marked as "don't change"
 *      (--->   <region> <---- indicates a region not to be changed)
 * 3. Add the scale factors to the function CJetSF/LJetSF
 *    - similar to BJetSF
 *
 */

void bTagBase::initWorkingpoints() {
    // Please give some information about the SF here. E.g
    // -------
    // SF from:
    // https://twiki.cern.ch/twiki/pub/CMS/BtagPOG/SFb-pt_NOttbar_payload_EPS13.txt  (EPS 2013 prescription)
    //  CSVL
    // -------
    wpvals_.at(csvl_wp) = 0.244;
    minpt_.at(csvl_wp) = 20;
    maxpt_.at(csvl_wp) = 800;

}

float bTagBase::BJetSF(const float & pt, const float& abs_eta,
        float multiplier) const { //multiplier not const for a reason!

    float x = pt;

    if (is2011_) { //for 7 TeV !!!!

    } else { //this is for 8 TeV!!!
        if (wp_ == csvl_wp) {

            // Please give some information about the SF here. E.g
            // -------
            // SF from:
            // https://twiki.cern.ch/twiki/pub/CMS/BtagPOG/SFb-pt_NOttbar_payload_EPS13.txt  (EPS 2013 prescription)
            // -------

            // please use the UPPER bin boundaries array given in the BTagPOG payload and then
            // add the lowest bin (e.g. 20) at front
            // make sure to use "static"

            static float ptbins[] = { 20, 30, 40, 50, 60, 70, 80, 100, 120, 160,
                    210, 260, 320, 400, 500, 600, 800 };

            //pu the errors to the corresponding SF here (copy/paste from BTagPOG payload)
            //make sure to use static and that it has the same size as ptbins!!!
            static float SFb_error[] = { 0.033408, 0.015446, 0.0146992,
                    0.0183964, 0.0185363, 0.0145547, 0.0176743, 0.0203609,
                    0.0143342, 0.0148771, 0.0157936, 0.0176496, 0.0209156,
                    0.0278529, 0.0346877, 0.0350101 };

            //don't change ---------------------------->
            static size_t ptbinsSize = sizeof(ptbins) / sizeof(ptbins[0]);
            static size_t SFb_errorSize = sizeof(SFb_error)
                                                                                                                    / sizeof(SFb_error[0]);
            if (SFb_errorSize != ptbinsSize - 1) {
                std::cout
                << "bTagBase::BJetSF: Size of SFb_error should be one less than of ptbins. throwing exception!"
                << std::endl;
                throw std::logic_error(
                        "bTagBase::BJetSF: Size of SFb_error should be one less than of ptbins.");
            }
            //force range according to BTagPOG input (dont change)
            if (x < ptbins[0]) {
                x = ptbins[0];
                multiplier *= 2;
            } else if (x >= ptbins[ptbinsSize - 1]) {
                x = ptbins[ptbinsSize - 1] - 0.0001;
                multiplier *= 2;
            }
            // <---------------------------- don't change

            //put the parametrization of the scale factor here (copy/paste from BTagPOG payload)
            //do NOT use static (should not compile anyway)
            float SF = 1.00572
                    * ((1. + (0.013676 * x)) / (1. + (0.0143279 * x)));

            //don't change:
            //takes care of systematic variations (if any)
            return calcHeavySF(ptbins, SFb_error, ptbinsSize, x, SF, multiplier);
        }

        //----------------END OF WORKING POINTS-----------------//
        else { //never reached
            throw std::logic_error(
                    "bTagBase: no working point set (this should never happen so someone has screwed up the code)");
        }

    }
    return 0; //never reached
}

float bTagBase::CJetSF(const float &pt, const float &abs_eta,
        float multiplier) const {
    if (wp_ == csvl_wp) {
        // Please give some information about the SF here. E.g
        // -------
        // SF from:
        // https://twiki.cern.ch/twiki/pub/CMS/BtagPOG (EPS 2013 prescription)
        // -------
        //
        // the same scale factor is supposed to be used with twice the uncertainty (multiplier*=2)
        return BJetSF(pt, abs_eta, multiplier * 2.);
    }

    //----------------END OF WORKING POINTS-----------------//
    return 0;
}

float bTagBase::LJetSF(const float& pt, const float& abs_eta,
        float multiplier) const {

    float x = pt;

    if (is2011_) {
        if (x >= 670)
            x = 669; //approx but should be ok for ttbar/Z etc
        //for eta > 2.4, the value for 2.4 is taken (should also be ok)
        return 1;
    }

    else {
        if (wp_ == csvl_wp) {
            // Please give some information about the SF here. E.g
            // -------
            // SF from:
            // https://twiki.cern.ch/twiki/pub/CMS/BtagPOG (EPS 2013 prescription)
            // From https://twiki.cern.ch/twiki/pub/CMS/BtagPOG/SFlightFuncs_EPS2013.C  (EPS 2013 prescription)
            // -------
            //
            // make sure, the range is appropriate (check the prescription)

            if (x > 800 && abs_eta <= 1.5)
                x = 800;
            else if (x > 700 && abs_eta > 1.5)
                x = 700;

            // Please copy-paste the formulas here. Check the correct eta range
            // systematics are handled directly here. use "else if" where applicable

            if (syst_ != lightdown && syst_ != lightup) { //don't change
                if (abs_eta <= 0.5)
                    return ((1.01177 + (0.0023066 * x))
                            + (-4.56052e-06 * (x * x)))
                            + (2.57917e-09 * (x * (x * x)));
                else if (abs_eta <= 1.0)
                    return ((0.975966 + (0.00196354 * x))
                            + (-3.83768e-06 * (x * x)))
                            + (2.17466e-09 * (x * (x * x)));
                else if (abs_eta <= 1.5)
                    return ((0.93821 + (0.00180935 * x))
                            + (-3.86937e-06 * (x * x)))
                            + (2.43222e-09 * (x * (x * x)));
                else
                    return ((1.00022 + (0.0010998 * x))
                            + (-3.10672e-06 * (x * x)))
                            + (2.35006e-09 * (x * (x * x)));
            } else if (syst_ == lightdown) { //don't change
                if (abs_eta <= 0.5)
                    return ((0.977761 + (0.00170704 * x))+ (-3.2197e-06 * (x * x)))+ (1.78139e-09 * (x * (x * x)));
                else if (abs_eta <= 1.0)
                    return ((0.945135 + (0.00146006 * x))
                            + (-2.70048e-06 * (x * x)))
                            + (1.4883e-09 * (x * (x * x)));
                else if (abs_eta <= 1.5)
                    return ((0.911657 + (0.00142008 * x))
                            + (-2.87569e-06 * (x * x)))
                            + (1.76619e-09 * (x * (x * x)));
                else
                    return ((1.03039 + (0.0013358 * x))
                            + (-3.89284e-06 * (x * x)))
                            + (3.01155e-09 * (x * (x * x)));
            } else if (syst_ == lightup) { //don't change
                if (abs_eta <= 0.5)
                    return ((1.04582 + (0.00290226 * x))
                            + (-5.89124e-06 * (x * x)))
                            + (3.37128e-09 * (x * (x * x)));
                else if (abs_eta <= 1.0)
                    return ((1.00683 + (0.00246404 * x))
                            + (-4.96729e-06 * (x * x)))
                            + (2.85697e-09 * (x * (x * x)));
                else if (abs_eta <= 1.5)
                    return ((0.964787 + (0.00219574 * x))
                            + (-4.85552e-06 * (x * x)))
                            + (3.09457e-09 * (x * (x * x)));
                else
                    return ((1.1388 + (0.000468418 * x))
                            + (-1.36341e-06 * (x * x)))
                            + (1.19256e-09 * (x * (x * x)));
            }
        }

        //----------------END OF WORKING POINTS-----------------//

    }
    return 0; //never reached
}

}
