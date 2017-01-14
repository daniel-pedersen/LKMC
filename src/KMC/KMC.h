// Copyright (c) 2017 Daniel Pedersen. Subject to the GNU GPLv3.

#ifndef __kmc__kmc__
#define __kmc__kmc__

#include <vector>

class KMC {
public:
	KMC();
	KMC(const std::vector<double>& rates);

	void addRate(double rate);
	void removeRate(size_t index);
	void setRates(const std::vector<double>& rates);
    void clearRates();

	size_t nextState();
	double time();

private:
	std::vector<double> m_R;
	double m_t;
};

#endif
