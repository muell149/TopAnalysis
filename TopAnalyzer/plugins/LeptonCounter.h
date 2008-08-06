#ifndef LeptonCounter_h
#define LeptonCounter_h

#include <string>
#include <map>
class LeptonCounter {
public:
	explicit LeptonCounter();

	void addCounter(std::string);

	void addSemiLeptonic(std::string);

	void addDiLeptonic(std::string);

	void addMultiLeptonic(std::string);

	void addPureHadronic(std::string);

	int getSemiLeptonic(std::string);

	int getDiLeptonic(std::string);

	int getMultiLeptonic(std::string);

	int getPureHadronic(std::string);

private:
	//0 = had, 1= semiLep, 2 = diLep, 3= multiLep
	typedef int Counter [4];
	std::map<std::string, Counter> counters_;
};
#endif
