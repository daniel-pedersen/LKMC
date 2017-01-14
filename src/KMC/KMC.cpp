// Copyright (c) 2017 Daniel Pedersen. Subject to the GNU GPLv3.

#include "KMC.h"
#include "random.h"

using namespace std;

KMC::KMC() :
	m_R(),
	m_t(0)
{ }

KMC::KMC(const vector<double>& rates) :
	m_R(rates),
	m_t(0)
{
	for (int i = 1; i < m_R.size(); ++i)
		m_R[i] += m_R[i - 1];
}

void KMC::addRate(double rate)
{
	if (m_R.empty())
		m_R.push_back(rate);
	else
		m_R.push_back(m_R.back() + rate);
}

void KMC::removeRate(size_t index)
{
	if (m_R.empty())
		return;
	m_R.erase(m_R.begin() + index);
}

void KMC::setRates(const std::vector<double>& rates)
{
	m_R.clear();
	if (rates.empty()) return;
	m_R.push_back(rates.front());
	for (int i = 1; i < rates.size(); ++i)
		m_R.push_back(rates[i] + m_R[i - 1]);
}

void KMC::clearRates()
{
    m_R.clear();
}

size_t KMC::nextState()
{
	if (m_R.empty()) return 0;
	double threshold = urand() * m_R.back();
	size_t state = 0, i;
	if (m_R.front() < threshold) {
		for (i = 1; i < m_R.size(); ++i) {
			if (m_R[i] > threshold) {
				state = i;
				break;
			}
		}
	}
	m_t += kmcrand(m_R.back());
	return state;
}

double KMC::time()
{
	return m_t;
}
