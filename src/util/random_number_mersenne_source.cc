#include "random_number_mersenne_source.h"

#include <random>
#include <functional>

template<typename T>
std::vector<T> RandomNumberMersenneSource<T>::Generate(size_t n, int min, int max) const
{
	/* Create device and apply random number engine */
	std::random_device randomDevice;
	std::mt19937 mersenne_engine(randomDevice());
	/* Set distribution of number between 1 and 1000 */
	std::uniform_int_distribution<T> dist(min, max);
	/* Create vector and reserve as many spaces as required */
	std::vector<T> randomNumberArray(n);
	for (auto& r : randomNumberArray) r = dist(mersenne_engine);
	return randomNumberArray;
}

template<typename T>
T RandomNumberMersenneSource<T>::Generate(int min, int max) const
{
	/* Create device and apply random number engine */
	std::random_device randomDevice;
	std::mt19937 mersenne_engine(randomDevice());
	/* Set distribution of number between 1 and 1000 */
	std::uniform_int_distribution<T> dist(min, max);
	return dist(mersenne_engine);
}