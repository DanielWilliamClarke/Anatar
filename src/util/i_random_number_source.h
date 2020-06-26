#ifndef I_RANDOM_NUMBER_SOURCE
#define I_RANDOM_NUMBER_SOURCE
#pragma once

#include <vector>

template<typename T>
class IRandomNumberSource
{
public:
	IRandomNumberSource() = default;
	virtual ~IRandomNumberSource() = default;
	virtual std::vector<T> Generate(size_t n, int min, int max) const = 0;
	virtual T Generate(int min, int max) const = 0;
};

#endif // I_RANDOM_NUMBER_SOURCE