#ifndef RANDOM_NUMBER_MERSENNE_SOURCE
#define RANDOM_NUMBER_MERSENNE_SOURCE
#pragma once

#include "i_random_number_source.h"

template<typename T>
class RandomNumberMersenneSource: public IRandomNumberSource<T>
{
public:
	RandomNumberMersenneSource() = default;
	virtual ~RandomNumberMersenneSource() = default;
	virtual std::vector<T> Generate(size_t n, int min, int max) const override;
	virtual T Generate(int min, int max) const override;
};

#endif // RANDOM_NUMBER_MERSENNE_SOURCE