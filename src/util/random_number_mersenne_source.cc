#include "random_number_mersenne_source.h"

template<typename T>
RandomNumberMersenneSource<T>::RandomNumberMersenneSource(unsigned int seed)
	: mt(seed)
{}

template<typename T>
std::vector<int> RandomNumberMersenneSource<T>::Generate(size_t n, int min, int max) const
{
	std::uniform_int_distribution<T> dist(min, max);
	std::vector<T> randomNumberArray(n);
	for (auto& r : randomNumberArray) r = dist(mt);
	return randomNumberArray;
}

template<typename T>
int RandomNumberMersenneSource<T>::Generate(int min, int max) const
{
	std::uniform_int_distribution<T> dist(min, max);
	return dist(mt);
}