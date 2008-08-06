#include "TopAnalysis/TopAnalyzer/plugins/LeptonCounter.h"
using std::string;
using std::map;
LeptonCounter::LeptonCounter() {
}

void LeptonCounter::addCounter(std::string){

}
void LeptonCounter::addSemiLeptonic(std::string name) {
	map<string, Counter>::iterator iter =counters_.find(name);
	if (iter !=counters_.end()) {
		iter->second[1]++;
	}
}

void LeptonCounter::addDiLeptonic(std::string name) {
	map<string,Counter>::iterator iter =counters_.find(name);
	if (iter !=counters_.end()) {
		iter->second[2]++;
	}
}

void LeptonCounter::addMultiLeptonic(std::string name) {
	map<string,Counter>::iterator iter =counters_.find(name);
	if (iter !=counters_.end()) {
		iter->second[3]++;
	}
}

void LeptonCounter::addPureHadronic(std::string name) {
	map<string,Counter>::iterator iter =counters_.find(name);
		if (iter !=counters_.end()) {
			iter->second[0]++;
		}
}

int LeptonCounter::getSemiLeptonic(std::string name) {
	map<string,Counter>::iterator iter =counters_.find(name);
	if (iter !=counters_.end()) {
		return iter->second[1];
	} else
		return -1;
}

int LeptonCounter::getDiLeptonic(string name) {
	map<string,Counter>::iterator iter =counters_.find(name);
	if (iter !=counters_.end()) {
		return iter->second[2];
	} else
		return -1;
}

int LeptonCounter::getMultiLeptonic(string name) {
	map<string,Counter>::iterator iter =counters_.find(name);
	if (iter !=counters_.end()) {
		return iter->second[3];
	} else
		return -1;
}

int LeptonCounter::getPureHadronic(string name) {
	map<string,Counter>::iterator iter =counters_.find(name);
	if (iter !=counters_.end()) {
		return iter->second[0];
	} else
		return -1;
}
