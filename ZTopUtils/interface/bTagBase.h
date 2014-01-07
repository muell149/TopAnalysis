#ifndef BTAGBASE_H
#define BTAGBASE_H

#include <map>
#include "TH2D.h"
//#include "TString.h"
#include "../interface/miscUtils.h"
#include <iostream>
#include <string>

#include "mathdefs.h"

/*
 workflow:
 -create object
 -set sample name              setSampleName(name)
 -fill efficiencies with jets  fillEff(p4,genPartonFlavour,PUweight)
 ---- get your event weight with your wrapper class!! ----
 ---functions to do that:
 - resetCounter()
 - countJet() (in jet loop)
 - getEventSF() (after jet loop - also resets the counter) returns 1 here


 -after event loop run makeEffs() once to create histograms
 - input / output should be organized by your wrapper class!

 -load from file or use already filled object (implement in your wrapper!)
 -setMakeEff(false)
 -(fillEff,makeEffs etc can remain in the loop/at the end of the loop, does nothing now)
 ---- get your event weight with your wrapper class!! ----
 ---functions to do that:
 - resetCounter()
 - countJet() (in jet loop)
 - getEventSF() (after jet loop - also resets the counter) now returns the proper SF!




 WHATEVER you add as functions, please don't use exit() in case an error occurs.
 replace it with either:
 - throw an exception (throw std::logic_error("sometext") or std::runtime_error("");)
 - return something (-1 or another int for dubugging)

 */
namespace ztop {

class bTagBase {
public:
    /**
     * constructor does nothing in particular
     */
    bTagBase();
    /**
     * destructor, does nothing special but setting pointer to 0
     */
    ~bTagBase() {
        cleanptr();
    }

    /**
     * enum for working points
     * should be named <tagger><wp>_wp
     *
     */
    enum workingPoints {
        csvm_wp, csvl_wp,
        /* some other WP/taggers ..*/
        //
        /*don't touch this: */
        length_wp
    };

    /**
     * enum for systematic variations
     */
    enum systematics {
        nominal, heavyup, heavydown, lightup, lightdown
    };

    /**
     *
     */
    void setWorkingpoint(workingPoints wp) {
        wp_ = wp;
    }
    ;
    workingPoints getWorkingpoint() const {
        return wp_;
    }
    ;
    /**
     * switches on SF for 7 TeV data
     */
    void setIs2011(bool is) {
        is2011_ = is;
    }


    void setSystematic(systematics sys) {
        syst_ = sys;
    }
    systematics getSystematic() {
        return syst_;
    }

    /**
     * sets the sample name. It can be used as a unique identifier when
     * reading or writing the histograms/data
     * If input is read, the name is used to identify the right set of
     * histograms (e.g. different for each sample but in the same bTagBase
     * object)
     */
    int setSampleName(const std::string &); //checks if effs should be made, if sample exists,..

    /**
     * enables the filling of histograms for efficiencies and disables
     * scale factor output
     */
    void setMakeEff(bool makee) {
        makeeffs_ = makee;
    }
    bool getMakeEff() {
        return makeeffs_;
    }

    /**
     * adds an entry for a jet with p4, genpartonFlavour, bDiscrValue  and PUweight
     * to the efficiency histograms
     */
    void fillEff(const float &, const float&, const int &, const float &,
            const float&);

    /**
     * creates efficiency histograms, to be run after all are filled
     */
    void makeEffs();

    /**
     * returns the number of nan sf
     */
    size_t getNanCount(){return nancount_;}

    bool showWarnings;
    bool debug;

protected:

    std::map<std::string, std::vector<TH2D> > histos_; //! bjets, btagged, cjets, ctagged, ljets, ltagged
    std::map<std::string, std::vector<TH2D> > effhistos_;   //! beff, ceff, leff

    // functions to be used in the wrapper classes inheriting from this class
    // example implementation:
    /*
     resetCounter();
     for(size_t i=0;i<jets.size();i++){
     ztop::NTJet *jet=jets.at(i);
     countJet(jet->p4(),jet->genPartonFlavour());
     }
     return getEventSF();
     */

    void resetCounter() {
        sumStuffEff_ = 0.99999999;
        sumStuffSfEff_ = 0.99999999;
    }
    void countJet(const float&, const float&, const int & genPartonFlavor);
    /**
     *
     */
    float getEventSF();

    bool changeJetTag(const float&, const float&, const int & genPartonFlavor,
            const float & tagValue) const; // to be implmented

    void cleanptr() {
        histp_ = 0;
        effhistp_ = 0;
    }

private:

    bool init_;

    workingPoints wp_;
    bool is2011_;
    systematics syst_;

    std::vector<float> wpvals_, minpt_, maxpt_;

    bool makeeffs_;

    std::string tempsamplename_;
    std::vector<TH2D> * histp_;
    std::vector<TH2D> * effhistp_;

    float sumStuffEff_;
    float sumStuffSfEff_;

    //counts the fraction of nans
    size_t nancount_;

    float calcHeavySF(float *, float *, const size_t &, const float &,
            const float &, const float &) const;


    //SFs btv input
    float BJetSF(const float &pt, const float& abs_eta,
            float multiplier = 1) const;
    float CJetSF(const float &pt, const float &abs_eta,
            float multiplier = 1) const;
    float LJetSF(const float &pt, const float &abs_eta,
            float multiplier = 1) const;

    void initWorkingpoints();

};

///inlined functions for performance reasons:

inline float bTagBase::calcHeavySF(float* ptbins, float * SFb_error,
        const size_t & ptbinsSize, const float & pt, const float & SF,
        const float & multiplier) const {

    if (syst_ != heavyup && syst_ != heavydown)
        return SF;

    //this uses the standard histogram bin range definition from root
    size_t ptbin = std::lower_bound(ptbins, ptbins + ptbinsSize, pt)
            - &ptbins[0];
    if (ptbins[ptbin] == pt)
        --ptbin;

    if (syst_ == heavyup)
        return SF + (multiplier * SFb_error[ptbin]);
    if (syst_ == heavydown)
        return SF - (multiplier * SFb_error[ptbin]);

    return 0;    //never reaches
}

}    //namespace
////////////////////////////////////
#endif

