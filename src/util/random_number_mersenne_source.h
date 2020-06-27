#ifndef RANDOM_NUMBER_MERSENNE_SOURCE
#define RANDOM_NUMBER_MERSENNE_SOURCE
#pragma once

#include <random>

#include "i_random_number_source.h"
template<typename T>
class RandomNumberMersenneSource: public IRandomNumberSource<T>
{
public:
	RandomNumberMersenneSource(unsigned int seed);
	virtual ~RandomNumberMersenneSource() = default;
	virtual std::vector<int> Generate(size_t n, int min, int max) const override;
	virtual int Generate(int min, int max) const override;
private:
	mutable std::mt19937 mt;
};

#endif // RANDOM_NUMBER_MERSENNE_SOURCE