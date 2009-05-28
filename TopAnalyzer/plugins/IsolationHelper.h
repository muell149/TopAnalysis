#ifndef IsolationHelper_h
#define IsolationHelper_h

#include "TopAnalysis/TopAnalyzer/plugins/CorrelationMonitor.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "TopAnalysis/TopUtils/interface/RootSystem.h"
#include "TopAnalysis/TopUtils/interface/RootHistograms.h"

class IsolationHelper {
	//needs TFileService
public:
	enum types {
		kAbsoluteTrack, kRelativeTrack, kAbsoluteCalo, kRelativeCalo, kRelCombIso
	};
	IsolationHelper() {

	}
	IsolationHelper(edm::Service<TFileService> fs) {
		mon = new CorrelationMonitor(fs);
		//		file_ = file;
		fs_ = fs;
		//		abs_caloLimits_[0] = 0.;
		//		abs_caloLimits_[1] = 10.;
		//		abs_trackLimits_[0] = 0.;
		//		abs_trackLimits_[1] = 10.;
		rel_caloLimits_[0] = 0.;
		rel_caloLimits_[1] = 1.;
		rel_trackLimits_[0] = 0.;
		rel_trackLimits_[1] = 1.;
		jetIsoLimits_[0] = 0.;
		jetIsoLimits_[1] = 3.5;
		rel_combLimits_[0] = 0.;
		rel_combLimits_[1] = 1.;
		//		abs_combLimits_[0] = 0.;
		//		abs_combLimits_[1] = 20.;

		//		abs_caloIso_ = abs_trackIso_ = 1000.;
		rel_caloIso_ = rel_trackIso_ = 1000.;
		jetIso_ = 1000.;
		//		rel_combIso_ = abs_combIso_ = 1000.;
		rel_combIso_ = 1000.;

		//		abs_caloBins_ = abs_trackBins_ = 10;
		rel_caloBins_ = rel_trackBins_ = 100;
		jetBins_ = 35;
	}

	void makeSummaryPlots(std::string prefix = "") {
		//for each histo, make 2 plots for correlation
		map<string, TH1F*>::iterator iter;
		unsigned int x = 0;
		//		string abs_caloName = prefix + "abs_caloCorrSummary";
		//		string abs_trackName = prefix + "abs_trackCorrSummary";
		string rel_caloName = prefix + "rel_caloCorrSummary";
		string rel_trackName = prefix + "rel_trackCorrSummary";
		string jetIsoName = prefix + "jet_isoCorrSummary";
		string rel_combName = prefix + "rel_combCorrSummary";
		//		string abs_combName = prefix + "abs_combCorrSummary";

		//book histos for summary
		NameScheme nam("var");
		//open the file and don't delete the content (append)
		//		ofstream off(file_.c_str(), std::ios::app);
		//		summary_abs_Calo_ = fs_->make<TH1F> (nam.name(abs_caloName.c_str()), nam.name(abs_caloName.c_str()),
		//				histos_.size(), -1., 1.);
		//		summary_abs_Track_ = fs_->make<TH1F> (nam.name(abs_trackName.c_str()), nam.name(abs_trackName.c_str()),
		//				histos_.size(), -1., 1.);

		summary_rel_Calo_ = fs_->make<TH1F> (nam.name(rel_caloName.c_str()), nam.name(rel_caloName.c_str()),
				histos_.size(), -1., 1.);
		summary_rel_Track_ = fs_->make<TH1F> (nam.name(rel_trackName.c_str()), nam.name(rel_trackName.c_str()),
				histos_.size(), -1., 1.);
		summary_jet_iso_ = fs_->make<TH1F> (nam.name(jetIsoName.c_str()), nam.name(jetIsoName.c_str()), histos_.size(),
				-1., 1.);
		//		summary_abs_Comb_= fs_->make<TH1F> (nam.name(rel_combName.c_str()), nam.name(rel_combName.c_str()),
		//				histos_.size(), -1., 1.);
		summary_rel_Comb_ = fs_->make<TH1F> (nam.name(rel_combName.c_str()), nam.name(rel_combName.c_str()),
				histos_.size(), -1., 1.);

		for (iter = histos_.begin(); iter != histos_.end(); ++iter) {
			std::string varname = iter->first;
			//			double abs_caloCorr = mon->getCorrelationFactor(varname + "_vs_AbsCalo");
			//			double abs_trackCorr = mon->getCorrelationFactor(varname + "_vs_AbsTrack");
			double rel_caloCorr = mon->getCorrelationFactor(varname + "_vs_RelCalo");
			double rel_trackCorr = mon->getCorrelationFactor(varname + "_vs_RelTrack");
			double jetIsoCorr = mon->getCorrelationFactor(varname + "_vs_JetIso");
			//			double abs_CombCorr = mon->getCorrelationFactor(varname + "_vs_AbsComb");
			double rel_CombCorr = mon->getCorrelationFactor(varname + "_vs_RelComb");

			//			double abs_caloCorr = mon->getCorrelationFactor(varname + "_vs_AbsCalo");
			//			double abs_trackCorr = mon->getCorrelationFactor(varname + "_vs_AbsTrack");
			double rel_caloCorrErr = mon->getCorrelationError(varname + "_vs_RelCalo");
			double rel_trackCorrErr = mon->getCorrelationError(varname + "_vs_RelTrack");
			double jetIsoCorrErr = mon->getCorrelationError(varname + "_vs_JetIso");
			//			double abs_CombCorr = mon->getCorrelationFactor(varname + "_vs_AbsComb");
			double rel_CombCorrErr = mon->getCorrelationError(varname + "_vs_RelComb");

			x++;
			//			summary_abs_Calo_->SetBinContent(x, abs_caloCorr);
			//			summary_abs_Track_->SetBinContent(x, abs_trackCorr);
			//			summary_abs_Calo_->GetXaxis()->SetBinLabel(x, varname.c_str());
			//			summary_abs_Track_->GetXaxis()->SetBinLabel(x, varname.c_str());

			summary_rel_Calo_->SetBinContent(x, rel_caloCorr);
			summary_rel_Calo_->SetBinError(x, rel_caloCorrErr);

			summary_rel_Track_->SetBinContent(x, rel_trackCorr);
			summary_rel_Track_->SetBinError(x, rel_trackCorrErr);

			summary_rel_Calo_->GetXaxis()->SetBinLabel(x, varname.c_str());
			summary_rel_Track_->GetXaxis()->SetBinLabel(x, varname.c_str());

			summary_jet_iso_->SetBinContent(x, jetIsoCorr);
			summary_jet_iso_->SetBinError(x, jetIsoCorrErr);
			//			summary_abs_Comb_->SetBinContent(x, abs_CombCorr);
			//			summary_abs_Comb_->SetBinError(x, abs_CombCorr);
			summary_rel_Comb_->SetBinContent(x, rel_CombCorr);
			summary_rel_Comb_->SetBinError(x, rel_CombCorrErr);

			summary_jet_iso_->GetXaxis()->SetBinLabel(x, varname.c_str());
			//			summary_abs_Comb_->GetXaxis()->SetBinLabel(x, varname.c_str());
			summary_rel_Comb_->GetXaxis()->SetBinLabel(x, varname.c_str());
		}
	}

	void addHistogram(std::string name, unsigned int numberOfBins, double min, double max) {
		NameScheme nam("var");
		//		ios_base::openmode mode;
		//rewrite the file when the first histogramm is written
		//		if (histos_.size() == 0) {
		//			mode = std::ios::out;
		//		} else {//otherwise append the histogramm to the hist file
		//			mode = std::ios::app;
		//			//cout << "hierjeztzt" << endl;
		//		}
		//		ofstream off(file_.c_str(), mode);
		std::string norm = "norm_" + name;
		TH1F *hist = fs_->make<TH1F> (nam.name(name.c_str()), nam.name(name.c_str()), numberOfBins, min, max);
		//deprecated! but might be useful
		histos_.insert(make_pair(name, hist));
		//adding correlation histogramms
		//		mon->addHist(name + "_vs_AbsCalo", numberOfBins, min, max, abs_caloBins_, abs_caloLimits_[0],
		//				abs_caloLimits_[1]);
		//		mon->addHist(name + "_vs_AbsTrack", numberOfBins, min, max, abs_trackBins_, abs_trackLimits_[0],
		//				abs_trackLimits_[1]);
		mon->addHist(name + "_vs_JetIso", numberOfBins, min, max, jetBins_, jetIsoLimits_[0], jetIsoLimits_[1]);
		mon->addHist(name + "_vs_RelCalo", numberOfBins, min, max, rel_caloBins_, rel_caloLimits_[0],
				rel_caloLimits_[1]);
		mon->addHist(name + "_vs_RelTrack", numberOfBins, min, max, rel_trackBins_, rel_trackLimits_[0],
				rel_trackLimits_[1]);
		mon->addHist(name + "_vs_RelComb", numberOfBins, min, max, rel_combBins_, rel_combLimits_[0],
				rel_combLimits_[1]);
		//		mon->addHist(name + "_vs_AbsComb", numberOfBins, min, max, abs_combBins_, abs_combLimits_[0],
		//				abs_combLimits_[1]);
	}

	//	void fill(std::string name, double var, double caloIso, double trackIso, double jetIso, double weight) {
	//		map<string, TH1F*>::iterator iter = histos_.find(name);
	//		if (iter != histos_.end()) {
	//			iter->second->Fill(var, weight);
	//			mon->fill(name + "_vs_AbsCalo", var, caloIso, weight);
	//			mon->fill(name + "_vs_AbsTrack", var, trackIso, weight);
	//			mon->fill(name + "_vs_JetIso", var, jetIso, weight);
	//		}
	//		map<string, TH1F*>::iterator itern = normhistos_.find(name);
	//		if (itern != normhistos_.end()) {
	//			itern->second->Fill(var, weight);
	//		}
	//	}

	void fill(std::string name, double var) {
		map<string, TH1F*>::iterator iter = histos_.find(name);
		if (iter != histos_.end()) {
			iter->second->Fill(var, weight_);
			//			mon->fill(name + "_vs_AbsCalo", var, abs_caloIso_, weight_);
			//			mon->fill(name + "_vs_AbsTrack", var, abs_trackIso_, weight_);
			mon->fill(name + "_vs_JetIso", var, jetIso_, weight_);
			mon->fill(name + "_vs_RelCalo", var, rel_caloIso_, weight_);
			mon->fill(name + "_vs_RelTrack", var, rel_trackIso_, weight_);
			mon->fill(name + "_vs_RelComb", var, rel_combIso_, weight_);
			//			mon->fill(name + "_vs_AbsComb", var, abs_combIso_, weight_);
		}
	}

	//	void setAbsCaloIso(double caloIso) {
	//		abs_caloIso_ = caloIso;
	//	}
	//
	//	void setAbsTrackIso(double trackIso) {
	//		abs_trackIso_ = trackIso;
	//	}

	void setRelCaloIso(double caloIso) {
		rel_caloIso_ = caloIso;
	}

	void setRelTrackIso(double trackIso) {
		rel_trackIso_ = trackIso;
	}

	void setJetIso(double jetiso) {
		jetIso_ = jetiso;
	}

	//	void setAbsCombIso(double iso) {
	//		abs_combIso_ = iso;
	//	}

	void setRelCombIso(double iso) {
		rel_combIso_ = iso;
	}

	void setWeight(double weight) {
		weight_ = weight;
	}

private:
	//for 2D correlation plots
	CorrelationMonitor *mon;
	//1D histos for the distribution of the variables
	std::map<string, TH1F*> histos_;
	//	TH1F * summary_abs_Calo_, *summary_abs_Track_, *summary_rel_Calo_, *summary_rel_Track_;
	//	TH1F *summary_jet_iso_, *summary_abs_Comb_, *summary_rel_Comb_;
	TH1F *summary_jet_iso_, *summary_rel_Comb_, *summary_rel_Calo_, *summary_rel_Track_;
	edm::Service<TFileService> fs_;
	//	unsigned int abs_caloBins_, abs_trackBins_, rel_caloBins_, rel_trackBins_, jetBins_;
	//	unsigned int abs_combBins_, rel_combBins_;
	unsigned int rel_combBins_, rel_caloBins_, rel_trackBins_, jetBins_;
	//	double abs_caloLimits_[2], abs_trackLimits_[2], rel_caloLimits_[2], rel_trackLimits_[2], jetIsoLimits_[2];
	//	double abs_combLimits_[2], rel_combLimits_[2];
	double rel_combLimits_[2], rel_caloLimits_[2], rel_trackLimits_[2], jetIsoLimits_[2];
	//	double abs_caloMin_, abs_caloMax_, abs_trackMin_, abs_trackMax_, jetMin_, jetMax_;
	//	double abs_caloIso_, abs_trackIso_, rel_caloIso_, rel_trackIso_, jetIso_, weight_;
	//	double rel_combIso_, abs_combIso_;
	double rel_combIso_, rel_caloIso_, rel_trackIso_, jetIso_, weight_;
	//	std::string file_;
};
#endif

