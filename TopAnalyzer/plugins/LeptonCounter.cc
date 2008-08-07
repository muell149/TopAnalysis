#include "TopAnalysis/TopAnalyzer/plugins/LeptonCounter.h"
#include <iostream>
using std::string;
using std::map;
using std::cout;
LeptonCounter::LeptonCounter() {
}

void LeptonCounter::addCounter(std::string name) {
	Counter t = {0.,0.,0.,0.};
	counters_[name] = &t;
}
void LeptonCounter::addSemiLeptonic(std::string name) {
	addSemiLeptonic(name,1);
}

void LeptonCounter::addDiLeptonic(std::string name) {
	addDiLeptonic(name,1);
}

void LeptonCounter::addMultiLeptonic(std::string name) {
	addMultiLeptonic(name,1);
}

void LeptonCounter::addPureHadronic(std::string name) {
	addPureHadronic(name,1);
}

void LeptonCounter::addSemiLeptonic(std::string name, double weight) {
	map<string, Counter*>::iterator iter = counters_.find(name);
	if (iter != counters_.end()) {
		(*iter->second)[1]+= 1*weight;
	}
}

void LeptonCounter::addDiLeptonic(std::string name, double weight) {
	map<string, Counter*>::iterator iter = counters_.find(name);
	if (iter != counters_.end()) {
		(*iter->second)[2]+= 1*weight;
	}
}

void LeptonCounter::addMultiLeptonic(std::string name, double weight) {
	map<string, Counter*>::iterator iter = counters_.find(name);
	if (iter != counters_.end()) {
		(*iter->second)[3] += 1*weight;
	}
}

void LeptonCounter::addPureHadronic(std::string name, double weight) {
	map<string, Counter*>::iterator iter = counters_.find(name);
	if (iter != counters_.end()) {
		(*iter->second)[0]+= 1*weight;
	}
}

double LeptonCounter::getSemiLeptonic(std::string name) {
	map<string, Counter*>::iterator iter = counters_.find(name);
	if (iter != counters_.end()) {
		return (*iter->second)[1];
	} else
		return -1.;
}

double LeptonCounter::getDiLeptonic(string name) {
	map<string, Counter*>::iterator iter = counters_.find(name);
	if (iter != counters_.end()) {
		return (*iter->second)[2];
	} else
		return -1.;
}

double LeptonCounter::getMultiLeptonic(string name) {
	map<string, Counter*>::iterator iter = counters_.find(name);
	if (iter != counters_.end()) {
		return (*iter->second)[3];
	} else
		return -1.;
}

double LeptonCounter::getPureHadronic(string name) {
	map<string, Counter*>::iterator iter = counters_.find(name);
	if (iter != counters_.end()) {
		return (*iter->second)[0];
	} else
		return -1.;
}
